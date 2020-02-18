// Caroline Northrop 
// Part 4 client
// Due Febuary 24th
// OS 4029


#include <errno.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

const int SHM_SIZE = 1024;
const char FILE_NAME[] = "testfile.txt";

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
    if ((key = ftok(FILE_NAME, 1)) == -1) 
    {
        perror("ftok");
        exit(1);
    }

	//make segament
    int shmid;
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) 
    {
        perror("shmget");
        exit(1);
    }

	//attach to memory 
    char *data;
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) 
    {
        perror("shmat");
        exit(1);
    }

	//open file 
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) 
    {
		perror(argv[1]);
		exit(1);
	}

    
	char* str = (char *)data + sizeof(int);
	*data = 0;

	char* line;
	size_t length = 0;

    //read in input file 
	while (getline(&line, &length, fp) != -1) 
    {
        //convert to uppercase 
		for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }       
		strcpy(str, line);
		(*data)++; 
        printf("%s", line);
		sleep(1);
	}

	//send stop signal to client  
	strcpy(str, "Stop\n");
	(*data)++;

	//detached 
	shmdt(str);
    
    return 0;
}