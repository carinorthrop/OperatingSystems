// Caroline Northrop
// Homework 3 sysv server
// Due Febuary 28th
// OS 4029

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

    //union struct
    struct semun
    {
        int val;
        struct semid_ds *buf;
        ushort *array;
    }
    //special semaphore structure to use the operations
    struct sembuf
    {
        int sem_num;
        short sem_op;
        short sem_flg;
    }


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

	//requests a semaphore structure
	int semaid;
    int numsems = 1; //number of semaphores need to set it
	if ((semaid = semget(key, numsems, IPC_CREAT | 0600)) == -1) 
    {
		perror("semget");
		exit(1);
	}

    union semun arg;
    int arr[2];
    arr[0] = 1;
    arr[1] = 5;
    arg.array = arr;

    //define basic operations 
    struct sembuf WAIT[1], SIGNAL[1];

    WAIT[0].sem_num = 0;
    WAIT[0].sem_op = 0;
    WAIT[0].sem_flg = SEM_UNDO;

    SIGNAL[0].sem_num = 0;
    SIGNAL[0].sem_op = 0;
    SIGNAL[0].sem_flg = SEM_UNDO;

    //entry section
    semop(semaid, WAIT, 1);

	char* str = (char *)data + sizeof(int);

	//read in input 
	int old = *data;
	while (1) 
    {
		
		if (old != *data) 
        {
			old = *data; 
			printf("%s", str);}
		}
	}

    //exit section
    semop(semaid, SIGNAL, 1);

	//delete
	semctl(semaid, 0, IPC_RMID, 0);
}