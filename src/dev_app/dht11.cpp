#include "dht11.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <QDebug>
#include <QTimer>

DHT11::DHT11(QWidget *parent) : QMainWindow(parent)
{
    dht11_fd = open(dht11_device.toStdString().c_str(),O_RDONLY);
    if(dht11_fd < 0){
        qDebug() << "fail to open /dev/mydht11\n";
        return;
    }else{
        qDebug() << "open mydht11 success";
    }
    dht11_timer = new QTimer(this);
    dht11_timer->setInterval(2000);
    connect(dht11_timer,&QTimer::timeout,this,&DHT11::timeto_read_dht11data);
    dht11_timer->start();
}

void DHT11::dht11_read(char *buf)
{
    int ret = read(dht11_fd, buf, 2);

    if (ret != 2) {
        // qDebug() << "dht11 read error" << ret;
        buf[0] = 0xFF;
        buf[1] = 0xFF;
    }
}

void DHT11::timeto_read_dht11data()
{
    // 通知内核驱动开始采集（驱动内部会拉低 18ms + 解析 40bit）
    ioctl(dht11_fd, CMD_DATA);

    // 通知 UI 层可以 read 了
    emit readyto_read_dht11data();
}
