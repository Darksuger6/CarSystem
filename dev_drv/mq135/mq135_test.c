#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int value;

    fd = open("/dev/mymq135", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    while (1) {
        read(fd, &value, sizeof(value));

        printf("MQ135 ADC = %d\n", value);

        usleep(500000);
    }

    close(fd);
    return 0;
}