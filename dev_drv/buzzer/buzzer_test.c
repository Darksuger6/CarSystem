#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;

    fd = open("/dev/mybuzzer", O_RDWR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    while (1) {
        write(fd, "1", 1);
        usleep(500000);

        write(fd, "0", 1);
        usleep(500000);
    }

    close(fd);
    return 0;
}