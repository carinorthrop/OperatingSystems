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

int main(int argc, char *argv[])
{
    //create a key 
    key_t key;
    if ((key = ftok(FILE_NAME, 1)) == -1) 
    {
        perror("ftok");
        exit(1);
    }

    //connect and create shared memory space 
    int shmid;
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) 
    {
        perror("shmget");
        exit(1);
    }

    //attach memory
    char *data;
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) 
    {
        perror("shmat");
        exit(1);
    }

    //go through segament 
    int x = 0;
    while (1 && x < 10)
    {
        printf("%s", data);
        x++;

        //checks to see if there is a stop from client 
        if(strcmp(data, "Stop\n") == 0)
        {
            break;
        }
    }

    //detach memory 
    if (shmdt(data) == -1) 
    {
        perror("shmdt");
        exit(1);
    }

    //delete memory 
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
