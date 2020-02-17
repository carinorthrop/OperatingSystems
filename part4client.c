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
    
    int n;
    const int MAX = 300;
    char line[MAX];

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
    
    //attach to segament
    char *data;
    data = (char *)shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) 
    {
        perror("shmat");
        exit(1);
    }

    //open the file
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror(argv[1]);
        exit(1);
    }
    
    char *line;
    int length= 0;
    //convert to uppercase and read in file
    while(getline(&line, &length, fp) != -1)
    {
        for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
            strncpy(data, line, SHM_SIZE);
        }
           sleep(1);
    }
    
    //send stop over to server
    strncpy(data, "Stop\n", SHM_SIZE);

    //detach from segment
    shmdt(data);

    return 0;
}