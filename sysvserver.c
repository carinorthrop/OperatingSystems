// Caroline Northrop
// Homework 3 sysv server
// Due Febuary 28th
// OS 4029
// referenced "synchronization" lecture slides

#include <errno.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ipc.h>

const int FILE_SIZE = 1024;
const char FILE_NAME[] = "temp.txt";

//define union semun
union semun 
{
    int value;
    struct semid_ds *buf;
    ushort *array;
} arg;


int main() 
{ 
    arg.value = 1;

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
	if ((fd = open(FILE_NAME, O_RDWR|O_CREAT|O_TRUNC, 0600)) == -1) 
    {
		perror("open");
		exit(1);
	}

    //change file size
    int result;
	if ((result = lseek(fd, FILE_SIZE - 1, SEEK_SET)) == -1) 
    {
		perror("lseek");
		exit(1);
	}

	//write an empty bit to the file size 
	if ((result = write(fd, "", 1)) != 1)
    {
		perror("write");
		exit(1);
	}

    //mmap
	int* data;
	if ((data = (int *)mmap(NULL, FILE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) 
    {
		perror("mmap");
		exit(1);
    }

    //get/create semaphore ID
	int semaid;
	if ((semaid = semget(key, 1, 0660|IPC_CREAT)) == -1) 
    {
		perror("semget");
		exit(1);
	}

    //set up semaphore 
	int semc;
	if ((semc = semctl(semaid, 0, SETVAL, arg)) == -1) 
    {
		perror("semctl");
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
			printf("\n%s", str);
		}
	}

	//clean up
    remove(FILE_NAME);
	munmap(data, FILE_SIZE);
	close(fd);
    semctl(semaid, 0, IPC_RMID, 0);
}