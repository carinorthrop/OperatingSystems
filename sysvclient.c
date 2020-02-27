// Caroline Northrop
// Homework 3 sysv client
// Due Febuary 28th
// OS 4029
// referenced "synchronization" lecture slides

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
#include <sys/mman.h>
#include <sys/ipc.h>

const int FILE_SIZE = 1024;
const char FILE_NAME[] = "temp.txt";

int main(int argc, char* argv[]) 
{
    //parameter checking
	if (argc != 2) 
    {
		printf("The correct parameters were not entered. Usage: file_name");
		exit(1);
	}

    //unique semaphore key
	key_t key; 
    const char S_FILE_NAME[] = "semaphore.txt";
	if ((key = ftok(S_FILE_NAME, 1)) == -1) 
    {
		perror("ftok");
		exit(1);
	}

	//open file
	int fd;
	if ((fd = open(FILE_NAME, O_RDWR|O_CREAT|O_TRUNC, 0644)) < 0) 
    {
		perror("open");
		exit(1);
	}

    //get/create semaphore ID
	int semaid;
	if ((semaid = semget(key, 1, 0660|IPC_CREAT)) == -1) 
    {
		perror("semget");
		exit(1);
	}

	//mmap
	int* data;
	if ((data = (int *)mmap(NULL, FILE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) 
    {
		perror("mmap");
		exit(1);
    }

    //open file 
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) 
    {
		perror(argv[1]);
		exit(1);
	}

    //define operations
	struct sembuf WAIT[1], SIGNAL[1];

	WAIT[0].sem_num = 0;
	WAIT[0].sem_op = -1;
	WAIT[0].sem_flg = SEM_UNDO;

	SIGNAL[0].sem_num = 0;
	SIGNAL[0].sem_op = 1;
	SIGNAL[0].sem_flg = SEM_UNDO;

	char* str = 1024;
	char* line;
	size_t length = 0;

    //entry
	semop(semaid, WAIT, 1);

    //read in file
	while (getline(&line, &length, fp) != -1) 
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

    //exit
	semop(semaid, SIGNAL, 1);

    //clean up
	munmap(data, FILE_SIZE);
    fclose(fp);
	close(fd);
}