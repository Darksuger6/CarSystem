#include "hardware.h"
#include "ui_hardware.h"
#include <QDebug>
#include <QUrl>

Hardware::Hardware(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hardware)
{
    ui->setupUi(this);

    dht11 = new DHT11(this);
    sr04 = new Sr04(this);
    buzzer = new Buzzer(this);
    led = new Led(this);
    mq135 = new Mq135(this);
}

Hardware::~Hardware()
{
    delete ui;
}

void Hardware::dht11_handler()
{
    unsigned char data[2] = {0};

    dht11->dht11_read((char*)data);

    // 判断是否读取失败
    if (data[0] == 0xFF || data[1] == 0xFF) {
        // qDebug() << "DHT11 read failed";
        // ui->Temp_label->setText("--");
        // ui->Humi_label->setText("--");
        return;
    }

    // qDebug() << "湿度:" << (int)data[0];
    // qDebug() << "温度:" << (int)data[1];

    ui->Humi_label->setNum((int)data[0]);
    ui->Temp_label->setNum((int)data[1]);
}

void Hardware::sr04_handler()
{
    int time_ns;
    char buf = 1;   // 必须在函数顶部声明，不要放 if 里

    sr04->sr04_read(&time_ns);

    // ns → cm
    float f = time_ns * 340.0f / 2 / 1000000000.0f * 100.0f;
    QString s = QString::number(f, 'f', 1);

    qDebug() << "sr04 distance:" << s;

    ui->Sr04_label->setText(s);

    if (f < 30)
    {
        QPixmap pixmap(":/images/car-chose.png");
        ui->label_3->setPixmap(pixmap.scaled(QSize(91, 111), Qt::KeepAspectRatio));
        ui->Sr04labal->setStyleSheet("color: red;");

        buf = 0;
        buzzer->buzzer_write(buf);
        QPixmap pixmap2(":/images/buzzer-chose.png");
        ui->buzzer->setPixmap(pixmap2.scaled(QSize(120, 120), Qt::KeepAspectRatio));
    }
    else
    {
        QPixmap pixmap(":/images/car.png");
        ui->label_3->setPixmap(pixmap.scaled(QSize(91, 111), Qt::KeepAspectRatio));
        ui->Sr04labal->setStyleSheet("color: rgb(85, 170, 255);");

        buf = 1;
        buzzer->buzzer_write(buf);
        QPixmap pixmap2(":/images/buzzer.png");
        ui->buzzer->setPixmap(pixmap2.scaled(QSize(120, 120), Qt::KeepAspectRatio));
    }
}

void Hardware::mq135_handler()
{
    char raw[30] = {};
    int tmp_raw;
    float conc;
    char led_buf[2];
    led_buf[0] = 0;
    memset(raw, 0, sizeof(raw));
    mq135->mq135_read(raw);
    tmp_raw = atoi(raw);
    conc = ((float)tmp_raw / 4095.f) * 100.f;
    QString strValue = QString::number(conc, 'f', 1);
    ui->fumes_label->setText(strValue);
    if(tmp_raw > 2880){
        QPixmap pixmap(":/images/air-chose.png");
        pixmap = pixmap.scaled(QSize(90, 110), Qt::KeepAspectRatio);
        ui->label_5->setPixmap(pixmap);
        ui->Humilabel_3->setStyleSheet("color: red;");
        if(tmp_raw == 4095){
            QString strValue = QString::number(conc, 'f', 0);
            ui->fumes_label->setText(strValue);
        }
        QPixmap pixmap1(":/images/led-chose.png");
        pixmap1 = pixmap1.scaled(QSize(120, 120), Qt::KeepAspectRatio);
        led_buf[1] = 0;
        led->led_write(led_buf);
        ui->led->setPixmap(pixmap1);
    }else{
        QPixmap pixmap(":/images/air.png");
        pixmap = pixmap.scaled(QSize(90, 110), Qt::KeepAspectRatio);
        ui->label_5->setPixmap(pixmap);
        ui->Humilabel_3->setStyleSheet("color: rgb(85, 255, 0);");
        QPixmap pixmap1(":/images/led.png");
        pixmap1 = pixmap1.scaled(QSize(120, 120), Qt::KeepAspectRatio);
        led_buf[1] = 1;
        led->led_write(led_buf);
        ui->led->setPixmap(pixmap1);
    }
}

void Hardware::hardware_working()
{
    connect(dht11,&DHT11::readyto_read_dht11data,this,&Hardware::dht11_handler);
    connect(sr04,&Sr04::readyto_read_sr04data,this,&Hardware::sr04_handler);
    connect(mq135,&Mq135::readyto_read_mq135data,this,&Hardware::mq135_handler);
}

void Hardware::on_back1_clicked()
{
    emit back1();
}
