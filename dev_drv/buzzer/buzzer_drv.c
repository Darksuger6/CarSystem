#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/uaccess.h>

static int major;
static struct class *buzzer_class;

#define BUZZER_GPIO  118

/* write: 控制蜂鸣器 */
static ssize_t buzzer_write(struct file *file, const char __user *buf,
                            size_t count, loff_t *ppos)
{
    char val;
    int ret;

    if (count != 1)
        return -EINVAL;

    ret = copy_from_user(&val, buf, 1);
    if (ret)
        return -EFAULT;

    if (val == 0)
    {
        gpio_set_value(BUZZER_GPIO, 0);  // 响（低电平触发）
    }
    else
    {
        gpio_set_value(BUZZER_GPIO, 1);  // 关闭
    }

    return 1;
}

static int buzzer_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int buzzer_release(struct inode *inode, struct file *file)
{
    return 0;
}

static struct file_operations buzzer_fops = {
    .owner = THIS_MODULE,
    .open = buzzer_open,
    .write = buzzer_write,
    .release = buzzer_release,
};

/* 初始化 */
static int __init buzzer_init(void)
{
    int ret;

    printk("buzzer init\n");

    /* 申请 GPIO */
    ret = gpio_request(BUZZER_GPIO, "mybuzzer");
    if (ret)
    {
        printk("gpio_request failed\n");
        return ret;
    }

    /* 设置为输出 */
    gpio_direction_output(BUZZER_GPIO, 1);  // 默认关闭

    /* 注册字符设备 */
    major = register_chrdev(0, "mybuzzer", &buzzer_fops);

    buzzer_class = class_create(THIS_MODULE, "mybuzzer_class");
    device_create(buzzer_class, NULL, MKDEV(major, 0), NULL, "mybuzzer");

    return 0;
}

/* 卸载 */
static void __exit buzzer_exit(void)
{
    printk("buzzer exit\n");

    device_destroy(buzzer_class, MKDEV(major, 0));
    class_destroy(buzzer_class);
    unregister_chrdev(major, "mybuzzer");

    gpio_free(BUZZER_GPIO);
}

module_init(buzzer_init);
module_exit(buzzer_exit);

MODULE_LICENSE("GPL");