#include "buzzer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>

Buzzer::Buzzer(QWidget *parent) : QMainWindow(parent), buzzer_fd(-1)
{
    buzzer_fd = open(buzzer_device.toStdString().c_str(), O_RDWR);
    if (buzzer_fd < 0) {
        qDebug() << "fail to open" << buzzer_device;
    } else {
        qDebug() << "open mybuzzer success";
    }
}

int Buzzer::buzzer_write(char buf)
{
    // 1.fd合法性检查
    if (buzzer_fd < 0) {
        qDebug() << "buzzer fd invalid";
        return -1;
    }

    // 2.状态去重（核心优化！）
    static char last_state = -1;
    if (buf == last_state) {
        return 0;  // 状态没变，不重复写
    }
    last_state = buf;

    // 3.写设备
    int ret = write(buzzer_fd, &buf, 1);
    if (ret < 0) {
        qDebug() << "buzzer write failed";
    } else {
        if (buf == 0)
            qDebug() << "buzzer ON";
        else
            qDebug() << "buzzer OFF";
    }

    return ret;
}
