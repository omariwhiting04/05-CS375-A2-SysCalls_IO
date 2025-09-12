#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void) {
    int newfd = open("output_file.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (newfd < 0) return 1;

    printf("Luke, I am your...\n"); // goes to terminal

    dup2(newfd, STDOUT_FILENO);     
    printf("father\n");             

    close(newfd);
    return 0;
}