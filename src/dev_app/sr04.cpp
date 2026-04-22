#include "sr04.h"
#include <QDebug>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <QTimer>

Sr04::Sr04(QWidget *parent) : QMainWindow(parent)
{
    sr04_fd = open(sr04_device.toStdString().c_str(),O_RDONLY | O_NONBLOCK);
    if(sr04_fd < 0){
        qDebug() << "fail to open /dev/mysr04\n";
        return;
    }
    else{
        qDebug() << "open mysr04 success";
    }
    sr04_timer = new QTimer(this);
    sr04_timer->setInterval(500);
    connect(sr04_timer,&QTimer::timeout,this,&Sr04::timeto_read_sr04data);
    sr04_timer->start();
}

void Sr04::sr04_read(int *buf)
{
    read(sr04_fd, buf, 4);
}

void Sr04::timeto_read_sr04data()
{
    ioctl(sr04_fd, CMD_TRIG);
    emit readyto_read_sr04data();
}
