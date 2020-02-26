// Caroline Northrop
// Homework 3 sysv server
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
#include <sys/shm.h>
#include <sys/types.h>


const int SHM_SIZE = 1024;
const char FILE_NAME[] = "txt.txt";


int main() 
{
	//create a key
	key_t key;
	if ((key = ftok(FILE_NAME, 1)) == -1) 
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

	char* str = (char *)data + sizeof(int);

	//read in input 
	int old = *data;
	while (1) 
    {
		
		if (old != *data) 
        {
			old = *data; 
			printf("%s", str);

			//listening for stop from client 
			if (strcmp(str, "Stop\n") == 0) 
            {
				break;
			}
		}
	}

	//detach 
    if (semdt(data) == -1) 
	{
        perror("semdt");
        exit(1);
    }

	//delete
	semctl(semid, IPC_RMID, NULL);
}