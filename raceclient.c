// Caroline Northrop
// Homework 3 race client
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

int main(int argc, char * argv[]) 
{
    //parameter checking 
    if (argc != 2) 
    {
        printf("Please enter the correct number of arguments. Only need filename");
        exit(1);
    }

    const int MAXLINE = 1024;
    char line[MAXLINE];
    int output_fd;
    int * tmp;
    char * msg;

    //open file 
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) 
    {
        printf("The file was not found.");
        exit(1);
    }

    //open output file
    if ((output_fd = open("middleman", O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
    {
        printf("There was a problem openin this file");
        exit(1);
    }

    ftruncate(output_fd, MAXLINE);

    //mmap
    if ((tmp = (int*) mmap(0, MAXLINE, PROT_READ | PROT_WRITE, MAP_SHARED, output_fd, 0)) == MAP_FAILED)
    {
        printf("There was a problem with mmap");
        exit(1);
    }

    msg = (char*) tmp + 4;

    //mmap input
    while(fgets(line, MAXLINE, fp) != NULL) 
    {
        //conver to upper case
        for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }
        // write to memory
        strncpy(msg, line, MAXLINE);
        puts(msg);
        (*tmp)++;
        sleep(1); 
    }

    strncpy(msg, "STOP", 5);
    (*tmp)++;
    puts("STOP");
}
