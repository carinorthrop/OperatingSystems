// Caroline Northrop 
// Homework 1 Question 2 
// Due Febuary 3rd
// OS 4029

#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>


int main(int argc, char ** argv)
{
    //check parameters
    //file_name is not included 
    if (argc < 2)
    {
        printf("Parameters are not specified. Please enter the file_name (Usage: ./HW1Q2 hw1textfile) \n");
        exit(0);
    }

    //too many parameters 
    if (argc > 2)
    {
        printf("There were too many parameters entered. Please enter the file_name. (Usage: ./HW1Q2 hw1textfile) \n");
        exit(0);
    }
    // if parameters are correct, continue with the program 
    else 
    {
        //file_name is taken in as a parameter
        const char * file_name = argv[1];

        //child process 1 
        if (fork() == 0) 
        {
            //execl system command 
            execl("/bin/ls", "ls", "-l", file_name, 0); 
            exit(0); 
        }

        //
        else
        {
            wait(0); // wait until first child exit
            if(fork() == 0)
            {
                execl("/bin/ps", "ps", "-ef", 0);
                exit(0);
            }

            else
            {
                wait(0);
                if(fork() == 0)
                {
                    execl("/bin/more", "more", filename, 0);
                    exit(0);
                }

                else
                {
                    printf("PID - %d\n", getpid());
                    wait(0); 
                }               
            }
        }   
        
    }

    return(0);
}
