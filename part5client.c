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

const int MAX = 1024;
char line[MAX];

int main(int argc, char * argv[]) 
{
    //input checking  
    if (argc != 2) 
    {
        printf("The correct parameters were not entered. Usage: file_name");
        exit(1);
    }

    //open file 
    FILE *fp = fopen(argv[1], "r"); 
    if (fp == NULL) 
    {
        printf("The file was not found\n");
        exit(1);
    }

    //create file
    int output;
    if ((output = open("test", O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
    {
        printf("The file cannot be opened\n");
        exit(1);
    } 

    ftruncate(output, MAX);

    //mmap
    int * file;
    if ((file = (int*) mmap(0, MAX, PROT_READ | PROT_WRITE, MAP_SHARED, output, 0)) == MAP_FAILED)
    {
        printf("There is a problem with mmap output\n");
        exit(1);
    }

    char * tmp;    
    tmp = (char*) file + 4;

    //read in 
    while(fgets(line, MAX, output) != NULL) 
    {
        //convert to uppercase
        for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }

        // write to memory
        strncpy(tmp, line, MAX);
        puts(tmp);
        ++*file;
        sleep(1); // pauses for one second
    }

    strncpy(tmp, "Stop\n", 5);
    ++*file;
    puts("Stop");

    return 0;
}