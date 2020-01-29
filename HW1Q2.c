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

int main(int argc, char** argv)
{
    //check parameters
    //N not specified
    if (argc < 2)
    {
        printf("N is not specified. Please enter one number for N. (i.e. ./HW1Q1 3) \n");
        exit(0);
    }
    //parameter is not a number
    if (!isdigit(*argv[1]))
    {
        printf("The parameter entered for N is not a number. Please enter one number for N. (i.e. ./HW1Q1 3) \n");
        exit(0); 
    }
    //too many parameters
    if (argc > 2)
    {
        printf("There were too many parameters entered for N. Please enter one number for N. (i.e. ./HW1Q1 3) \n");
        exit(0);
    }
    else 
    {
        childprocesses(atoi(argv[1]));
    }

    return(0);
}
