// Caroline Northrop 
// Part 5 server
// Due Febuary 24th
// OS 4029


#include <errno.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

const int MAX = 1024;
char line[MAX];

int main(int argc, char * argv[]) 
{
    //open file
    int input;
    if ((input = open("test", O_RDWR | O_CREAT)) < 0)
    {
        printf("There was a problem opening the file\n");
        exit(1);
    }

    ftruncate(input, MAX);

    //mmap
    int * file;
    if ((file = (int*) mmap(0, MAX, PROT_READ, MAP_SHARED, input, 0)) == MAP_FAILED)
    {
        printf("There was a problem with the mmap input\n");
        exit(1);
    }
    
    char * msg;
    msg = (char*)file + 4;

    // read in input 
    int n = -1; 

    while (1)
    {
        if (n == file[0]) 
        {
            continue;
        }
        n = file[0];

        //checking for a stop from the client 
        if (strcmp(msg, "Stop\n") == 0)
        {
            break;
        }

        printf("%s", msg);
    }

    unlink("test");
    return 0;
}