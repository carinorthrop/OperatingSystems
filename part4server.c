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
const char FILE_NAME[] = "hwtest.txt";

int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    char *data;
    int n;

    //Create Key
    if ((key = ftok(FILE_NAME, 1)) == -1) {
        perror("ftok");
        exit(1);
    }

    //connect to (and possibly create) the segment:
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
    //attach to the segment to get a pointer to it
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }
    //Read the segment
    n = 0;
    while ( (n < 10) && (strcmp(data, "STOP") != 0) )
    {
        printf("%s", data);
        sleep(5);   /* Sleep 5 seconds) */
        n++;
    }
    //detach from the segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
    //Delete the structure 
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
