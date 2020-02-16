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
    char* pipe = "/part3";

    //create the named pipe
    mkfifo(pipe,0666); 

    int input = open(pipe, O_WRONLY);

    //open the file 
    FILE *fd = fopen(argv[1], "r");

    //error checking on the file
    if (input == -1) 
    {
        printf("There was a problem opening the file.");
        exit(0);
    }


    while(fgets(line, MAX, fd) != NULL)
    {
        for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }
        write(input, line, MAX);
        printf("%s", line);
    }

    write(input, "Stop\n", MAX);
    fclose(fd);
    close(input);
    return 0;
}