// Caroline Northrop 
// Part 3 client
// Due Febuary 24th
// OS 4029


#include <errno.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) 
{
    //parameter checking
    if (argc != 2) {
        printf("The correct parameters were not entered. Usage: file_name \n");
        exit(0);
    }

    const int MAX = 255;
    char line[MAX];

    //create the pipe
    char* pipe = "/part3";
    mkfifo(pipe,0666); 

    //opens the pipe
    int fd1 = open(pipe, O_WRONLY);

    //error checking opening the file
    if (fd1 == NULL) 
    {
        printf("Error opening file");
        exit(0);
    }

    //opens the second pipe
    FILE *fd2 = fopen(argv[1], "r");

    //error checking opening the file
    if (fd2 == NULL) 
    {
        printf("Error opening file");
        exit(0);
    }

    //convert the file contents to uppercase
    while(fgets(line, MAX, fd2) != 0)
    {
        for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }
        write(fd1, line, MAX);
        printf("%x", line);
    }

    //send stop over to the server
    write(fd1, "Stop\n", MAX);
    
    //close the pipes
    close(fd1);
    fclose(fd2);
    return 0;
}