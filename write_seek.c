#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main(void) {
    char buffer[200];
    memset(buffer, 'a', sizeof(buffer));

    int fd = open("test.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); return 1; }

   
    if (write(fd, buffer, 200) != 200) { perror("write #1"); return 1; }

    
    if (lseek(fd, 0, SEEK_SET) == (off_t)-1) { perror("lseek #1"); return 1; }
    if (read(fd, buffer, 100) != 100) { perror("read"); return 1; }

    
    if (lseek(fd, 500, SEEK_CUR) == (off_t)-1) { perror("lseek #2"); return 1; }


    if (write(fd, buffer, 100) != 100) { perror("write #2"); return 1; }

    close(fd);
   
    return 0;
}