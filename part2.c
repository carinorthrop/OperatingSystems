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
	int fdFind[2];
	int fdTz[2];

	const int BUFFSIZE = 100;
	char buffer[BUFFSIZE];

	FILE *fp = popen("find . -name '*.c'", "r");
	FILE *fp2 = popen("tr a-z A-Z", "w");
	while (fgets(buffer, BUFFSIZE, fp) != NULL) {
		fputs(&buffer[0], fp2);
	}
	pclose(fp);
	pclose(fp2);
}
