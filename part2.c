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
	int MAX = 100;
	char buffer[MAX];

	//find all files with .c
	FILE *fp = popen("find . -name '*.c'", "w");
    pclose(fp);

    //find all files with .c, make them uppercase
	FILE *fp2 = popen("tr a-z A-Z", "w");

	//close the file
	pclose(fp2);
}
