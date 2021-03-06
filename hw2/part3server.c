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
    const int MAX = 300;
    char line[MAX];
    
    //create pipe
    char* pipe = "/tmp/part3";
    mkfifo(pipe, 0666); 
    
    int output = open(pipe, O_RDONLY);

    //create loop until client sends stop
    while(1)
    {
        //read through content of the input
        read(output, line, sizeof(line));
        printf("%s", line);

        //checks to see if client sent stop
        if(strcmp(line, "Stop\n") == 0)
        {
            break;
        }
    }

    //close and remove the pipe
    close(output);
    remove("tmp/myfifo");
}