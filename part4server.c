// Caroline Northrop 
// Part 4 server
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

int main() 
{

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

    int n = 0;
    while ( (n < 10) && (strcmp(data, "STOP") != 0) )
    {
        printf("%s", data);
        sleep(1);   /* Sleep 5 seconds) */
        n++;
    }

	//delete 
	shmctl(shmid, IPC_RMID, NULL);

    return 0;
}