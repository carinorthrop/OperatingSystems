// Caroline Northrop 
// Part 5 server
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
#include <sys/mman.h>

int main(int argc, char * argv[]) 
{
    const int MAXLINE = 1024;
    char line[MAXLINE];
    int input_fd;
    int * tmp;
    char * msg;

    // open input file
    if ((input_fd = open("testfile.txt", O_RDWR | O_CREAT)) < 0)
    {
        printf("Unnable to open file\n");
        exit(1);
    }

    ftruncate(input_fd, MAXLINE);

    // mmap input
    if ((tmp = (int*) mmap(0, MAXLINE, PROT_READ, MAP_SHARED, input_fd, 0)) == MAP_FAILED){
        printf("Error with mmap input\n");
        exit(1);
    }

    msg = (char*) tmp + 4;

    // read
    int n = -1; // ensure a change first time through loop

    while (1) 
    {
        if (n == tmp[0]) 
        {
            continue;
            printf("%s", msg);
        }
        n = tmp[0];

        if (strcmp(msg, "STOP") == 0)
        {
            break;
        }
    }
    unlink("testfile.txt");
}