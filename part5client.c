// Caroline Northrop 
// Part 5 client
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

    // open input file
    FILE *fp = fopen(argv[1], "r"); 
    if (fp == NULL) {
        printf("File not found.");
        exit(1);
    }
    // open/create output file
    if ((output_fd = open("middleman", O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
    {
        printf("Unable to open file\n");
        exit(1);
    }
          
    ftruncate(output_fd, MAXLINE);

    // mmap output
    if ((tmp = (int*) mmap(0, MAXLINE, PROT_READ | PROT_WRITE, MAP_SHARED, output_fd, 0)) == MAP_FAILED){
        printf("Error with mmap output\n");
        exit(1);
    }
       
	char* str = (char *)tmp + sizeof(int);
	*tmp = 0;

	char* line;
	size_t length = 0;

    //read in input file 
	while (getline(&line, &length, fp) != -1) 
    {
        //convert to uppercase 
		for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }       
		strcpy(str, line);
		(*tmp)++; 
        printf("%s", line);
		sleep(1);
	}

    strncpy(msg, "Stop\n", 5);
    ++*tmp;
    puts("STOP");
    


}