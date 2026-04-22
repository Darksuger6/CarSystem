#include <linux/module.h>
#include <linux/iio/iio.h>
#include <linux/iio/sysfs.h>
#include <linux/platform_device.h>

struct mq135_data {
    int value;
};

static int mq135_read_raw(struct iio_dev *indio_dev,
                         struct iio_chan_spec const *chan,
                         int *val,
                         int *val2,
                         long mask)
{
    struct mq135_data *data = iio_priv(indio_dev);

    switch (mask) {
    case IIO_CHAN_INFO_RAW:
        *val = data->value;
        return IIO_VAL_INT;
    default:
        return -EINVAL;
    }
}

static const struct iio_info mq135_info = {
    .read_raw = mq135_read_raw,
};

static const struct iio_chan_spec mq135_channels[] = {
    {
        .type = IIO_VOLTAGE,
        .indexed = 1,
        .channel = 4,  // 对应 in_voltage4_raw
        .info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
    },
};

static int mq135_probe(struct platform_device *pdev)
{
    struct iio_dev *indio_dev;
    struct mq135_data *data;

    indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*data));
    if (!indio_dev) {
        dev_err(&pdev->dev, "iio_device_alloc failed\n");
        return -ENOMEM;
    }

    data = iio_priv(indio_dev);
    data->value = 1000; // 初始值（可改成ADC读取）

    indio_dev->info = &mq135_info;
    indio_dev->channels = mq135_channels;
    indio_dev->num_channels = ARRAY_SIZE(mq135_channels);
    indio_dev->name = "mq135";
    indio_dev->modes = INDIO_DIRECT_MODE;

    int ret = devm_iio_device_register(&pdev->dev, indio_dev);
    if (ret) {
        dev_err(&pdev->dev, "iio_device_register failed\n");
        return ret;
    }

    dev_info(&pdev->dev, "mq135 driver loaded successfully\n");
    return 0;
}

static int mq135_remove(struct platform_device *pdev)
{
    dev_info(&pdev->dev, "mq135 driver removed\n");
    return 0;
}

static struct platform_driver mq135_driver = {
    .driver = {
        .name = "mq135",
    },
    .probe = mq135_probe,
    .remove = mq135_remove,
};

module_platform_driver(mq135_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("you");
MODULE_DESCRIPTION("MQ135 IIO Driver");