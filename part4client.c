// Caroline Northrop 
// Part 4 client
// Due Febuary 24th
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

const int SHM_SIZE = 1024;
const char FILE_NAME[] = "hwtest.txt";

int main(int argc, char *argv[]){
    //Verify correct number of arguments 
    if (argc != 2) {
        printf("Please enter the correct number of arguments. Only need filename");
        exit(1);
    }
    
    key_t key;
    int shmid;
    char *data;
    int n;
    const int MAXLINE = 255;
    char line[MAXLINE];

    //Create Key
    if ((key = ftok(FILE_NAME, 1)) == -1) {
        perror("ftok");
        exit(1);
    }

    //Connect and make the segment 
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

    //modify the segment, based on the command line
    FILE *fp = fopen(argv[1], "r");
    strncpy(data, fgets(line,MAXLINE,fp), SHM_SIZE);
    sleep(5);
    for (int i = 0; i < strlen(line); i++) {
            line[i] = toupper(line[i]);
    }
    strncpy(data, line, SHM_SIZE);
    sleep(5);
    strncpy(data, "STOP", SHM_SIZE);

    //detach from segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
    return 0;
}