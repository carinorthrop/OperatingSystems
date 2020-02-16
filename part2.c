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
    int MAXLINE = 80;
    char line[MAXLINE];
    //Finds all the files with .c 
    FILE *fp = popen("find . -name '*.c'", "w");
    pclose(fp);
    //Closes the file
    //Finds all the files with .c and makes them uppercase 
    FILE *fp1 = popen("tr 'a-z' 'A-Z'", "w");
    //Closes the file
    pclose(fp1);
}
