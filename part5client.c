
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <string.h>
#include <sys/mman.h>
#include <ctype.h>

int main(int argc, char * argv[]) {
    //Verify correct number of arguments 
    if (argc != 2) {
        printf("Please enter the correct number of arguments. Only need filename");
        exit(1);
    }
    const int MAXLINE = 1024;
    char line[MAXLINE];
    int output_fd;
    int * tmp;
    char * msg;

    // open input file
    FILE *fp = fopen(argv[1], "r"); 
    if (fp == NULL) {
        printf("File not found.");
        exit(1);
    }
    // open/create output file
    if ((output_fd = open("middleman", O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0){
        printf("Unable to open file\n");
        exit(1);
    }
          
    ftruncate(output_fd, MAXLINE);

    // mmap output
    if ((tmp = (int*) mmap(0, MAXLINE, PROT_READ | PROT_WRITE, MAP_SHARED, output_fd, 0)) == MAP_FAILED){
        printf("Error with mmap output\n");
        exit(1);
    }
       
    msg = (char*) tmp + 4;

    // mmap input
    while(fgets(line, MAXLINE, fp) != NULL) {
        for (int i = 0; i < strlen(line); i++) {
            line[i] = toupper(line[i]);
        }
        // write to memory
        strncpy(msg, line, MAXLINE);
        puts(msg);
        ++*tmp;
        sleep(1); // pauses for one second
    }

    strncpy(msg, "STOP", 5);
    ++*tmp;
    puts("STOP");
    


}