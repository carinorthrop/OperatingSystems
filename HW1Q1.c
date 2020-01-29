// Caroline Northrop 
// Homework 1 Question 1 
// Due Febuary 3rd
// OS 4029

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>

void childprocesses(int N)
{
    //main process
    for(int i = 0; i < N; i++)
    {
        //need to get PID
        pid_t ppid = getpid();
        printf("This is the main process, my PID is %x. \n", (int)ppid);
        sleep(2); 
    }

    //forks parent
    int parent = (int) fork();

    if (parent1 == 0)
    {
        for (int x = 0; x < N; x++)
        {
            printf("This is a child process, my PID is %x, my parent id is %x. \n", (int)getpid(), (int)getppid());
            sleep(2);
        }
    }

    else
    {
        int parent2 = (int) fork();
        if (parent2 == 0)
        {
            for (int x = 0; x < N; x++)
            {
                printf("This is a child process, my PID is %x, my parent id is %x. \n", (int)getpid(), (int)getppid());
                sleep(2);
            } 
        }

        else
        {
            int parent3 = (int) fork();
            if (parent3 == 0)
            {
                for (int x = 0; x < N; x++)
                {
                    printf("This is a child process, my PID is %x, my parent id is %x. \n", (int)getpid(), (int)getppid());
                    sleep(2);
                }    
            }

            else
            {
                wait(NULL);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    //check parameters
    //N not specified 
    if (argc < 2)
    {
        printf("N is not specified in the command prompt. Please enter one number for N.\n");
        exit(0);
    }
    //parameter is not a number
    if (!isdigit(*argv[1]))
    {
        printf("The parameter entered for N is not a number. Please enter one number for N.\n");
        exit(0);
    }
    //too many parameters
    if (argc > 2)
    {
        printf("There were too many parameters entered for N. Please enter one number for N.\n");
        exit(0)
    }
    else 
    {
        childprocesses(atoi(argv[1]));
    }
}
