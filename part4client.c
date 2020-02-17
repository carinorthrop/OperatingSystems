// Caroline Northrop 
// Part 4 client
// Due Febuary 24th
// OS 4029


#include <errno.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

const int SHM_SIZE = 1024;
const char FILENAME[] = "testfile.txt";

//parameter checking
int main(int argc, char* argv[])
 {
	if (argc != 2) 
    {
		printf("The correct parameters were not entered. Usage: file_name");
		exit(1);
	}

    //create a key
    key_t key;
    if ((key = ftok(FILE_NAME, 1)) == -1) 
    {
        perror("ftok");
        exit(1);
    }

	//make segament
    int shmid;
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) 
    {
        perror("shmget");
        exit(1);
    }

	//attach to memory
    char *data;
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) 
    {
        perror("shmat");
        exit(1);
    }

	// Create a reference for where to store the string
	char* str = (char *)count + sizeof(int);
	*count = 0;

	// Open the text file
	FILE* sourceFile = fopen(argv[1], "r");
	if (sourceFile == NULL) {
		perror(argv[1]);
		exit(1);
	}

	// Begin reading the lines from the source file
	char* line;
	size_t len = 0;

	while (getline(&line, &len, sourceFile) != -1) 
    {
		for (int i = 0; i < strlen(line); i++) 
        {
            line[i] = toupper(line[i]);
        }       
		strcpy(str, line); //move the line to the memory for the string
		(*data)++; // update the count
        printf("%s", line);
		sleep(1);
	}

	// Send signal to the server to die
	strcpy(str, "Stop\n");
	(*data)++;

	// Detach segments
	shmdt(str);
}