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
    char* pipe = "tmp/part3";

    //create the named pipe
    mkfifo(pipe, 0666); 
    int input = open(pipe, O_WRONLY);

    //open the file 
    FILE *fd = fopen(argv[1], "r");

    //reads the file and converts to upper case 
    while(fgets(line, MAX, fd) != NULL)
    {
        for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }
        write(input, line, MAX);
        printf("%s", line);
    }

    //once the file is read send a stop to the server
    write(input, "Stop\n", MAX);
    
    //close pipes and files 
    close(input);
    fclose(fd);
    return 0;
}