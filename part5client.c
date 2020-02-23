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

const int FILE_SIZE = sizeof(char) + sizeof(int);
const char FILE_NAME[] = "temp.txt";

int main(int argc, char* argv[]) 
{
    //parameter checking
	if (argc != 2) 
    {
		printf("The correct parameters were not entered. Usage: file_name");
		exit(1);
	}

	//open file
	int fd;
	if ((fd = open(FILE_NAME, O_RDWR|O_CREAT|O_TRUNC, 0600)) == -1) 
    {
		perror("open");
		exit(1);
	}

	//mmap
	int* data;
	if ((data = (int *)mmap(NULL, FILE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) 
    {
		perror("mmap");
		exit(1);
    }

    //open file 
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) 
    {
		perror(argv[1]);
		exit(1);
	}

	char* str = (char *)data + sizeof(int);
	char* line;
	size_t length = 0;

    //read in file
	while (getline(&line, &length, fp) != -1) 
    {
		//convert to uppercase 
		for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }  

		strcpy(str, line);
		(*data)++; 
		sleep(1);
	}

	//send stop signal to client 
	strcpy(str, "Stop\n");
	(*data)++;

    //clean up
	munmap(data, FILE_SIZE);
    fclose(fp);
	close(fd);
}