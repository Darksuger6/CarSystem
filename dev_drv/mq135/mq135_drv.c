#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>

#define DEVICE_NAME "mymq135"

static int major;
static struct class *mq135_class;

/* ADC sysfs路径 */
#define ADC_PATH "/sys/bus/iio/devices/iio:device0/in_voltage4_raw"

static ssize_t mq135_read(struct file *file, char __user *buf,
                          size_t count, loff_t *ppos)
{
    char adc_buf[32];
    int value = 0;
    struct file *fp;
    mm_segment_t old_fs;

    /* 打开ADC sysfs */
    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fp = filp_open(ADC_PATH, O_RDONLY, 0);
    if (IS_ERR(fp)) {
        set_fs(old_fs);
        return -1;
    }

    kernel_read(fp, adc_buf, sizeof(adc_buf), &fp->f_pos);
    filp_close(fp, NULL);

    set_fs(old_fs);

    value = simple_strtol(adc_buf, NULL, 10);

    return copy_to_user(buf, &value, sizeof(value)) ? -EFAULT : sizeof(value);
}

static struct file_operations mq135_fops = {
    .owner = THIS_MODULE,
    .read  = mq135_read,
};

static int __init mq135_init(void)
{
    major = register_chrdev(0, DEVICE_NAME, &mq135_fops);

    mq135_class = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(mq135_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);

    printk("mq135 driver init\n");
    return 0;
}

static void __exit mq135_exit(void)
{
    device_destroy(mq135_class, MKDEV(major, 0));
    class_destroy(mq135_class);
    unregister_chrdev(major, DEVICE_NAME);
}

module_init(mq135_init);
module_exit(mq135_exit);

MODULE_LICENSE("GPL");