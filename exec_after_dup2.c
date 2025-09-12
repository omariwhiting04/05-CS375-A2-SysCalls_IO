#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s output_file\n", argv[0]);
        return 1;
    }

    int newfd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (newfd < 0) { perror("open"); return 1; }

    printf("Writing output of the command ls to %s\n", argv[1]);

    // redirect 
    dup2(newfd, STDOUT_FILENO);
    close(newfd);

    char *cmd[] = { "/bin/ls", "-al", "/", NULL };
    execvp(cmd[0], cmd);
    perror("execvp"); // only runs if exec fails
    return 1;
}