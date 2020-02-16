// Caroline Northrop 
// Part 1 
// Due Febuary 24th
// OS 4029

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>


void processes(char* programname, char* filename){
    int child = (int) fork();
    //Verify we have a child 
    if (child == -1){
        printf("Error forking");
        exit(0);
    }else if (child == 0){
        //Open the file
        int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        //stdout to the file
        dup2(fd, 1);
        //stderr to the file
        dup2(fd, 2);
        //close fd
        close(fd);
        //execute the file
        execl(programname,programname, (char*)NULL);
        exit(0);
    }else{
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    //Check to make sure there are the right parameters 
    if (argc > 3){
        printf("Too many parameters please only enter program name and a file name.\n");
        exit(0);
    }else if(argc < 3){
        printf("Please enter a program name and a file name when calling program \n");
        exit(0);
    }else{
        //Call function
        processes(argv[1], argv[2]);
    }
    return 0;
}
