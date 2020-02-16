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


int main(int argc, char *argv[]) {
    //Verify correct number of arguments 
    if (argc != 2) {
        printf("Please enter the correct number of arguments. Only need filename");
        exit(1);
    }
    const int MAXLINE = 255;
    char line[MAXLINE];
    int input_fd;
    char* pipe = "/tmp/part3";

    //Create Named Pipe
    mkfifo(pipe,0666); 

    input_fd = open(pipe, O_WRONLY);

    if (input_fd == -1) {
        printf("Error opening file");
        exit(0);
    }

    FILE *fp = fopen(argv[1], "r");

    while(fgets(line, MAXLINE, fp) != NULL){
        for (int i = 0; i < strlen(line); i++) {
            line[i] = toupper(line[i]);
        }
        write(input_fd,line,MAXLINE);
        printf("%s",line);
    }

    write(input_fd, "Stop\n", MAXLINE);
    fclose(fp);
    close(input_fd);
    return 0;
}