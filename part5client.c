
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <string.h>
#include <sys/mman.h>
#include <ctype.h>

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
    const char FILE_SIZE = sizeof(char) + sizeof(int);

    // open input file
    FILE *fp = fopen(argv[1], "r"); 
    if (fp == NULL) 
    {
        printf("File not found.");
        exit(1);
    }
    // open/create output file
    if ((output_fd = open("middleman", O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
    {
        printf("Unable to open file\n");
        exit(1);
    }

	//file_size
    int empty;
	if ((empty = lseek(output_fd, FILE_SIZE - 1, SEEK_SET)) == -1) 
    {
		perror("Problem with the size");
		exit(1);
	}

	//write and empty bit 
	if ((empty = write(output_fd, "", 1)) != 1) 
    {
		perror("Problem with writing an empty bit");
		exit(1);
	}
          
    ftruncate(output_fd, MAXLINE);

    // mmap output
    if ((tmp = (int*) mmap(0, MAXLINE, PROT_READ | PROT_WRITE, MAP_SHARED, output_fd, 0)) == MAP_FAILED)
    {
        printf("Error with mmap output\n");
        exit(1);
    }
       
    msg = (char*) tmp + 4;

    //reading in
    
	char* line;
	size_t len = 0;

    char* str = (char *)tmp + sizeof(int);

	while (getline(&line, &len, fp) != -1) 
    {
		makeupper(line); // convert to uppercase
		strcpy(str, line); //move the line to the memory for the string
		++*tmp; // update the count

		sleep(1);
	}







    /*while(fgets(line, MAXLINE, fp) != NULL) 
    {
        for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }
        // write to memory
        strncpy(msg, line, MAXLINE);
        puts(msg);
        ++*tmp;
        sleep(1); // pauses for one second
    }*/

    strncpy(msg, "STOP", 5);
    puts("STOP");
    


}