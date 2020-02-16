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

    //open the file
    int output = open(pipe, O_RDONLY);
    const int MAX = 300;
    char line[MAX];

    while(1)
    {
        //read in
        read(output, line, sizeof(line));
        printf("%s",line);

        //check to see if there is a stop from client 
        if(!strcmp(line, "Stop\n"))
        {
            break;
        }
    }

    //close and delete 
    close(output);
    remove("/myfifo");
    return 0;
}