# CarSystem
车载中控系统

# run
/media/music和/media/videos要copy到可执行文件目录下

# driver device

## 温湿度传感器dht11
    /dev/mydht11
引脚:
    out === gpio2

## 超声波传感器sr04
    /dev/mysr04
引脚:
    trig === gpio0
    echo === gpio1

## 蜂鸣器buzzer
    /dev/mybuzzer

## led灯
    /dev/myled

## 气体传感器mq135(读取方式ADC)
    /sys/bus/iio/devices/iio:device0/in_voltage3_raw
