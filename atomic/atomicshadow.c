#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

int main()
{
    int fd[2];
    int status;
    pid_t pid;
    char arr1[] = "I am shadow";
    char arr2[] = "I am atomic";
    char read_msg[256];

    if(pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    pid = fork();
    if(pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid == 0)
    {
        read(fd[0], read_msg, sizeof(read_msg));
        printf("%s\n", read_msg);
        write(fd[1], arr2, strlen(arr2) + 1);
        exit(EXIT_SUCCESS);
    }
    else
    {
        write(fd[1], arr1, strlen(arr1) + 1);
        wait(&status);
        read(fd[0], read_msg, sizeof(read_msg));
        printf("%s\n", read_msg);
    }
}