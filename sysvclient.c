// Caroline Northrop
// Homework 3 sysv client
// Due Febuary 28th
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
#include <sys/mman.h>

void upper_string(char []);
const int SHM_SIZE = 1024;  /* make it a 1K shared memory segment */
const char FILE_NAME[] = "hwtest.txt";


int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    char *data;
    int n;
    const int MAXLINE = 255;
    char line[MAXLINE];

    /* make the key: */
    if ((key = ftok(FILE_NAME, 1)) == -1) {
        perror("ftok");
        exit(1);
    }

    /* connect to (and possibly create) the segment: */
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }
     /* attach to the segment to get a pointer to it: */
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    /* modify the segment, based on the command line: */
    FILE *fp;
    fp = fopen(argv[1],"r");


    strncpy(data, fgets(line,MAXLINE,fp), SHM_SIZE);
    sleep(5);

    upper_string(line);
    strncpy(data, line, SHM_SIZE);
    sleep(5);

    /* detach from the segment: */
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
    return 0;
}

void upper_string(char s[])
{
				int c=0;
				while (s[c] != '\0'){
					if (s[c] >= 'a' && s[c] <= 'z'){
						s[c] = s[c] - 32;
						}
					c++;
					}
}
