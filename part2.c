// Caroline Northrop 
// Part 2
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

int main() 
{
    int MAX = 80;
    char line[MAX];

    //Finds all the files with .c 
    FILE *fp1 = popen("find . -name '*.c'", "r");

    //Makes files uppercase 
    FILE *fp2 = popen("tr 'a-z' 'A-Z'", "w");
    
    while (fgets(line, MAX, fp1) != 0)
    {
        fputs(&line[0], fp2);
    }

    //closes pipes
    pclose(fp1);
    pclose(fp2);
}
