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
    if (argc != 2) 
    {
        printf("The correct parameters were not entered. Usage: file_name");
        exit(1);
    }
    const int MAX = 255;
    char line[MAX];

    //create the pipe
    char* pipe = "/tmp/part3";
    mkfifo(pipe, 0666); 

    int input = open(pipe, O_WRONLY);

    if (input == NULL)
    {
        printf("Error opening file");
        exit(0);
    }

    FILE *fd = fopen(argv[1], "r");

    //convert to uppercase
    while(fgets(line, MAX, fd) != NULL)
    {
        for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }
        write(input, line, MAX);
        printf("%s", line);
    }

    //send stop over to server
    write(input, "Stop\n", MAX);

    //close out pipe and file
    fclose(fd);
    close(input);
    return 0;
}