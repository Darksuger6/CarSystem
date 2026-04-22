#include "mq135.h"
#include <fcntl.h>
#include <unistd.h>
#include <QDebug>
#include <QTimer>

Mq135::Mq135(QWidget *parent) : QMainWindow(parent)
{
    raw_fd = open(dev_path.toStdString().c_str(), O_RDONLY);
    if (raw_fd < 0) {
        qDebug() << "fail to open" << dev_path;
    } else {
        qDebug() << "open mq135 success";
    }

    mq135_timer = new QTimer(this);
    mq135_timer->setInterval(1000);   // 1秒刷新
    connect(mq135_timer, &QTimer::timeout,
            this, &Mq135::timeto_read_mq135data);
    mq135_timer->start();
}

void Mq135::mq135_read(char *buf)
{
    if (raw_fd < 0) return;

    // 关键：sysfs必须重置偏移
    lseek(raw_fd, 0, SEEK_SET);

    int len = read(raw_fd, buf, 30);
    if (len > 0) {
        buf[len] = '\0';
    } else {
        qDebug() << "mq135 read failed";
    }
}

void Mq135::timeto_read_mq135data()
{
    emit readyto_read_mq135data();
}
