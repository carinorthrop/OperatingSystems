// Caroline Northrop 
// Part 3 client
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

//Ashley Wilhelm 
//Homework 2: Part 3 Client

#include <sys/types.h>
#include <sys/stat.h>   
#include <unistd.h>   
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>   
#include <errno.h>
#include <string.h>
#include <ctype.h>

// Helper function to convert a string to upper case.
//   Loops through the characters of a string and makes them uppercase
void makeupper(char* str) {
	while (*str) {
		*str = toupper((unsigned char) *str);
		str++;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s file-to-read\n", argv[0]);
		exit(1);
	}

	// Open the file to read from
	FILE* sourceFile = fopen(argv[1], "r");
	if (sourceFile == NULL) {
		perror(argv[1]);
		exit(1);
	}

	// Create & open the named pipe
	char* fifo = "./fifo";
	mkfifo(fifo, 0666);

	int fd = open(fifo, O_WRONLY);

	// Begin reading the lines from the source file
	char* line;
	size_t len = 0;

	while (getline(&line, &len, sourceFile) != -1) {
		makeupper(line); // convert to uppercase
		write(fd, line, len); // write to the pipe
		sleep(1); //wait a sec
	}

	// We've read the whole file. Let's send a stop to the server, then close our pipe and file
	write(fd, "Stop\n", 6);

	close(fd);
	fclose(sourceFile);
}