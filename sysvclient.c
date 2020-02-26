// Caroline Northrop
// Homework 3 sysv client
// Due Febuary 28th
// OS 4029

#include <errno.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/types.h>

const int SHM_SIZE = 1024;
const char FILE_NAME[] = "txt.txt";

int main(int argc, char* argv[]) 
{
    //parameter checking
    if (argc != 2) 
    {
		printf("The correct parameters were not entered. Usage: file_name");
		exit(1);
	}

	//create a key
	key_t key; 
	if ((key =ftok(FILE_NAME, 1)) == -1) 
    {
		perror("ftok");
		exit(1);
	}

	//create memory space
	int semid;
	if ((semid = semget(key, SHM_SIZE, 0644|IPC_CREAT)) == -1) 
    {
		perror("semget");
		exit(1);
	}

	//attach
	char* data = semat(semid, (void *)0, 0);
	if (data == (char *)(-1)) 
    {
		perror("semat");
		exit(1);
	}

	//open
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) 
    {
		perror(argv[1]);
		exit(1);
	}

	char* str = (char *)data + sizeof(int);
	*data = 0;
	char* line;
	size_t length = 0;

    //read in input
	while (getline(&line, &length, file) != -1) 
    {
        //convert to uppercase
		for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }

		strcpy(str, line);
		(*data)++; 
		sleep(1);
	}

	//tell server to break out of loop
	strcpy(str, "Stop\n");
	(*data)++;

	//detach 
	if (semdt(data) == -1) 
	{
        perror("semdt");
        exit(1);
    }

	//delete
	semdt(str);
}