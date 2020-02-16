// Caroline Northrop 
// Part 3 server
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
    const int MAXLINE = 255;
    char line[MAXLINE];
    int output_fd;
    char* pipe = "/part3";
    
    //Create Named Pipe
    mkfifo(pipe,0666); 

    output_fd = open(pipe, O_RDONLY);

    while(1)
    {
        read(output_fd,line,sizeof(line));
        printf("%s",line);

        if(!strcmp(line, "Stop\n"))
        {
            break;
        }
    }


    close(output_fd);
    remove("/myfifo");
    return 0;
}