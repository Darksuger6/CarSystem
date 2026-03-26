#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/gpio.h>

#define DEVICE_NAME "mybuzzer"

/* 修改为你实际使用的GPIO */
#define BUZZER_GPIO  (1*32 + 3)   // GPIO1_IO03

static int major;
static struct class *buzzer_class;

/* 写操作控制蜂鸣器 */
static ssize_t buzzer_write(struct file *file,
                            const char __user *buf,
                            size_t count, loff_t *ppos)
{
    char kbuf[2];

    if (copy_from_user(kbuf, buf, 1))
        return -EFAULT;

    if (kbuf[0] == '1') {
        gpio_set_value(BUZZER_GPIO, 1);
    } else {
        gpio_set_value(BUZZER_GPIO, 0);
    }

    return count;
}

static struct file_operations buzzer_fops = {
    .owner = THIS_MODULE,
    .write = buzzer_write,
};

static int __init buzzer_init(void)
{
    int ret;

    /* 申请GPIO */
    ret = gpio_request(BUZZER_GPIO, "buzzer_gpio");
    if (ret) {
        printk("gpio request failed\n");
        return -1;
    }

    /* 设置为输出 */
    gpio_direction_output(BUZZER_GPIO, 0);

    /* 注册字符设备 */
    major = register_chrdev(0, DEVICE_NAME, &buzzer_fops);

    buzzer_class = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(buzzer_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

    printk("buzzer driver init\n");
    return 0;
}

static void __exit buzzer_exit(void)
{
    gpio_set_value(BUZZER_GPIO, 0);
    gpio_free(BUZZER_GPIO);

    device_destroy(buzzer_class, MKDEV(major, 0));
    class_destroy(buzzer_class);
    unregister_chrdev(major, DEVICE_NAME);
}

module_init(buzzer_init);
module_exit(buzzer_exit);

MODULE_LICENSE("GPL");