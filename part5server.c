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

const int FILE_SIZE = sizeof(char) + sizeof(int);
const char FILE_NAME[] = "temp.txt";

int main() 
{

	//open file
	int fd;
	if ((fd = open(FILE_NAME, O_RDWR|O_CREAT|O_TRUNC, 0600)) == -1) 
    {
		perror("There was a problem opening the file.\n");
		exit(1);
	}

	//change file size
    int result;
	if ((result = lseek(fd, FILE_SIZE - 1, SEEK_SET)) == -1) 
    {
		perror("There was a problem with changing the file size");
		exit(1);
	}

	//write an empty bit to the file size 
	if ((result = write(fd, "", 1)) != 1)
    {
		perror("There was a problem with writing the empty bits to the file size");
		exit(1);
	}

	//mmap
	int* data;
	if ((data = (int *)mmap(NULL, FILE_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) 
    {
		perror("There was a problem with mmap");
		exit(1);
	}

	char* str = (char *)data + sizeof(int);
    int old = *data;

	while (1) 
    {
		if (old != *data) 
        {
			old = *data;
			printf("%s", str);

			//listening stop from counter
			if (strcmp(str, "\nStop\n") == 0) 
            {
				break;
			}
		}
	}

	//cleanup 
    remove(FILE_NAME);
	munmap(data, FILE_SIZE);
	close(fd);
}