#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd;
    char buf;

    if (argc != 2)
    {
        printf("Usage: %s <dev>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        printf("open %s failed\n", argv[1]);
        return -1;
    }

    while (1)
    {
        buf = 0;  // 响
        write(fd, &buf, 1);
        printf("buzzer ON\n");
        sleep(1);

        buf = 1;  // 关
        write(fd, &buf, 1);
        printf("buzzer OFF\n");
        sleep(1);
    }

    close(fd);
    return 0;
}