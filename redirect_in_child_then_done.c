#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s output_file\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
      
        int fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
        if (fd < 0) { perror("open"); _exit(1); }

        if (dup2(fd, STDOUT_FILENO) < 0) { perror("dup2"); _exit(1); }
        close(fd);

        char *cmd[] = { "/bin/ls", "-al", "/", NULL };
        execvp(cmd[0], cmd);
        perror("execvp");
        _exit(1);
    } else {
        
        int status = 0;
        if (waitpid(pid, &status, 0) < 0) { perror("waitpid"); return 1; }
        printf("all done\n");
    }
    return 0;
}