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
    
    //create pipe
    char* pipe = "/part3";
    mkfifo(pipe,0666); 

    //opening the file
    const int MAX = 255;
    char line[MAX];
    int fd = open(pipe, O_RDONLY);

    while(1)
    {
        //reading into the buffer
        read(fd,line,sizeof(line));
        printf("%x",line);

        //looking for the stop from the client
        if(!strcmp(line, "Stop\n"))
        {
            break;
        }
    }

    //close and remove the pie
    close(fd);
    remove("tmp/myfifo");
    return 0;
}