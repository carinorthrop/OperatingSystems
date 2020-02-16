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

int main(int argc, char *argv[])

{
    //parameter checking
    if (argc != 2) 
    {
        printf("The correct parameters were not entered. Usage: file_name");
        exit(1);
    }
    
    key_t key;
    int shmid;
    char *data;
    int n;
    const int MAXLINE = 255;
    char line[MAXLINE];

    //create a key
    if ((key = ftok(FILE_NAME, 1)) == -1) 
    {
        perror("ftok");
        exit(1);
    }

    //connect and create segament
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) 
    {
        perror("shmget");
        exit(1);
    }
    
    //attach to segament
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) 
    {
        perror("shmat");
        exit(1);
    }

    //modify the segment
    FILE *fp = fopen(argv[1], "r");
    strncpy(data, fgets(line,MAXLINE,fp), SHM_SIZE);
    sleep(5);

    //convert to uppercase
    for (int i = 0; i < strlen(line); i++) 
    {
            line[i] = toupper(line[i]);
    }
    strncpy(data, line, SHM_SIZE);
    sleep(5);

    //send stop over to server
    strncpy(data, "STOP\n");

    //detach from segment
    shmdt(data);

    return 0;
}