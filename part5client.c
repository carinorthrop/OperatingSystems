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
    int output_fd;
    int * tmp;
    const int FILE_SIZE = sizeof(char) + sizeof(int);
    const char FILE_NAME[] = "testfile.txt";

    // open the file
    if ((output_fd = open(FILE_NAME, O_RDWR | O_CREAT | O_TRUNC, 0644)) != -1)
    {
        printf("There was a problem opening this file.\n");
        exit(1);
    }

    //open the map  
    if ((tmp = (int*) mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, output_fd, 0)) == MAP_FAILED){
        printf("There was a problem opening the map.\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r"); 
    if (fp == NULL) 
    {
        printf("File not found.");
        exit(1);
    }

	char* str = (char *)tmp + sizeof(int);
	char* line;
	size_t len = 0;
    
    //reading in input
    while(getline(&line, &len, fp) != -1) 
    {
        for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }
        // write to memory
        strcpy(str, line);
        ++*tmp;
        sleep(1); // pauses for one second
    }

    strcpy(str, "Stop\n");
    ++*tmp;
    
    
    munmap(tmp, FILE_SIZE);
	close(output_fd);
	fclose(fp);
    


}