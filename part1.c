// Caroline Northrop 
// Part 1 
// Due Febuary 24th
// OS 4029

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
 {
    //parameter checking  
    if (argc != 3)
    {
        printf("The correct parameters were not entered. Usage: program_name file_name \n");
        exit(0);

    }
    else
    {
        int child = fork();
        if (child == -1)
        {
            printf("Error forking");
            exit(0);
        }
            else if(child == 0)
            {
                //open the file
                int fd = open(argv[2], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

                //send stdout to the file
                dup2(fd, 1);

                //close the file
                close(fd);

                //execute the file
                execl(argv[1], argv[1], (char*)0);
            }
    }
    return 0;
}
