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

void process(const char * file_name)
{

        //child process 1 
        if (fork() == 0) 
        {
            //shows directory 
            execl("/bin/ls", "ls", "-l", file_name, NULL); 
            exit(0); 
        }

        else
        {
            wait(0); 
            if(fork() == 0)
            {
                //shows processes running
                execl("/bin/ps", "ps", "-ef", NULL);
                exit(0);
            }

            else
            {
                wait(0);
                if(fork() == 0)
                {
                    //shows file contects 
                    execl("/bin/more", "more", file_name, NULL);
                    exit(0);
                }

                else
                {
                    //print the PID only once
                    printf("PID - %d\n", getpid());
                    wait(0); 
                }               
            }
        }   
}


int main(int argc, char ** argv)
{
    //check parameters
    //file_name is not included 
    if (argc < 2)
    {
        printf("Parameters are not specified. Please enter the file_name (Usage: ./part2 hw1textfile) \n");
        exit(0);
    }

    //too many parameters 
    if (argc > 2)
    {
        printf("There were too many parameters entered. Please enter the file_name. (Usage: ./part2 hw1textfile) \n");
        exit(0);
    }
    // if parameters are correct, continue with the program 
    else 
    {
      process(argv[1]);  
    }

    return(0);
}
