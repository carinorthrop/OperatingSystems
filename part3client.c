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
    const int MAX = 300;
    char line[MAX];

    //create the pipe
    char* pipe = "/tmp/part3";
    mkfifo(pipe, 0666); 

    int input = open(pipe, O_WRONLY);

    //error checking opening file
    /*
    if (input == -1)
    {
        printf("There was a problem opening the file \n");
        exit(0);
    }*/

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

    //once input has been read and converted to uppercase, send stop over to server
    write(input, "Stop\n", MAX);

    //close out pipe and file
    close(input);
    fclose(fd);

    return 0;
}