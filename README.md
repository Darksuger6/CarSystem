# CarSystem
车载中控系统

# run
/media/music和/media/videos要copy到可执行文件目录下

# driver device

## 温湿度传感器
    /dev/mydht11

## 超声波传感器
    /dev/mysr04

## 蜂鸣器
    /dev/mybuzzer

## led灯
    /dev/myled

## 气体传感器(读取方式ADC)
    /sys/bus/iio/devices/iio:device0/in_voltage3_raw