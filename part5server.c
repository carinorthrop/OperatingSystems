
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <string.h>
#include <sys/mman.h>

int main(int argc, char * argv[]) 
{
    const int MAXLINE = 1024;
    char line[MAXLINE];
    int input_fd;
    int * tmp;
    char * msg;

    const char FILE_SIZE = sizeof(char) + sizeof(int);

    // open input file
    if ((input_fd = open("middleman", O_RDWR | O_CREAT | O_TRUNC)) < 0)
    {
        printf("Unnable to open file\n");
        exit(1);
    }

    // mmap input
    if ((tmp = (int*) mmap(0, FILE_SIZE, PROT_READ, MAP_SHARED, input_fd, 0)) == MAP_FAILED)
     {
        printf("Error with mmap input\n");
        exit(1);
    }
	//file_size
    int empty;
	if ((empty = lseek(input_fd, FILE_SIZE - 1, SEEK_SET)) == -1) 
    {
		perror("Problem with the size");
		exit(1);
	}

	//write and empty bit 
	if ((empty = write(input_fd, "", 1)) != 1) 
    {
		perror("Problem with writing an empty bit");
		exit(1);
	}

    msg = (char*) tmp + 4;

    // read in the input 
    int n = -1; // ensure a change first time through loop
    while (1)
     {
        if (n == tmp[0]) 
        {
            continue;
        }
        n = tmp[0];
        if (strcmp(msg, "STOP") == 0)
        {
            break;
        }
        printf("%s", msg);
    }
    unlink("middleman");
}