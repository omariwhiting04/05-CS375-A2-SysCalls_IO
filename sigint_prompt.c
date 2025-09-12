#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sigint_handler(int sig) {
    (void)sig;
    char c;
    const char *q = "Do you really want to quit [y/n]? ";
    write(STDOUT_FILENO, q, 33);          
    if (read(STDIN_FILENO, &c, 1) == 1) { 
        if (c == 'y' || c == 'Y') _exit(0);
    }
    // keep running if not 'y'
}

int main(void) {
    signal(SIGINT, sigint_handler); 
    for (;;) pause();               
}