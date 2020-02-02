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

void childprocess(const char * file_name)
{
    if (fork() == 0) 
    {
        //shows directory 
        printf("Directory:");
        execl("/bin/ls", "ls", "-l", NULL); 
        exit(0); 
    }

    else
    {
        wait(0); 

        if(fork() == 0)  
        {
            //shows processes running
            printf("Processes Running: ");
            execl("/bin/ps", "ps", "-ef", NULL);
            exit(0);
        }

        else
        {
            wait(0);

            if(fork() == 0)
            {
                //shows file contents 
                printf("File Contents: ");
                execl("/bin/more", "more", file_name, NULL);
                exit(0);
            }

            else
            {
                //print the PID only once
                printf("PID: %x ", getpid());
                wait(0); 
            }               
        }
    } 
    printf("Main process terminates \n");  
}


int main(int argc, char ** argv)
{
    //check parameters
    //file_name is not included 
    if (argc < 2)
    {
        printf("Parameters are not specified. Please enter the file_name (Usage: ./HW1Q2 file_name) \n");
        exit(0);
    }
    //too many parameters 
    if (argc > 2)
    {
        printf("There were too many parameters entered. Please enter the file_name. (Usage: ./HW1Q2 file_name) \n");
        exit(0);
    }
    //file does not exist 
     if(access(argv[1], F_OK) == -1)
    {
        printf("This file does not exist");
        exit(0);
    }
    // if parameters are correct, continue with the program 
    else 
    {
      childprocess(argv[1]);  
    }
    return(0);
}
