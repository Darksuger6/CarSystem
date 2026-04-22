#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MQ135_PATH "/sys/bus/iio/devices/iio:device0/in_voltage4_raw"

int main(void)
{
    int fd;
    char buf[32];

    fd = open(MQ135_PATH, O_RDONLY);
    if (fd < 0) {
        perror("open failed");
        return -1;
    }

    while (1) {
        memset(buf, 0, sizeof(buf));

        // ⭐ 关键：每次读之前必须重置偏移
        lseek(fd, 0, SEEK_SET);

        int ret = read(fd, buf, sizeof(buf) - 1);
        if (ret < 0) {
            perror("read failed");
            break;
        }

        printf("MQ135 Value: %s", buf);

        // 控制采样频率（1秒一次）
        sleep(1);
    }

    close(fd);
    return 0;
}