#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
if(argc != 2) // stop user if not proper argument
{
printf("Usage: you_program_name file_name\n");
return 0;
}
const char * filename = argv[1]; // take second argument as a filename
if(fork() == 0) // create first child process
{
execl("/bin/ls","ls","-l",filename,NULL); // exicute command using execl
exit(0); // exit after compliting process
}
else
{
wait(0); // wait until first child exit
if(fork() == 0)
{
execl("/bin/ps","ps","-ef",NULL);
exit(0);
}
else
{
wait(0);
if(fork() == 0)
{
execl("/bin/more","more",filename,NULL);
exit(0);
}
else
{

printf("PID - %d\n",getpid()); //print parent PID
wait(0); // wait till last child exit
}
}
}
}