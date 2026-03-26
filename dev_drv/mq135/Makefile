# 交叉编译器
CC := $(CROSS_COMPILE)gcc

# 模块名称
MODE_NAME = mq135
FILE_NAME = $(MODE_NAME)_test
DRIVER_NAME = $(MODE_NAME)_drv

# NFS目录
FS_FILE = ~/nfs/

# 内核目录
KERN_DIR = /home/syw/100ask_imx6ull-sdk/Linux-4.9.88

# 默认编译
all:
	@echo "===== Building MQ135 Driver ====="
	make -C $(KERN_DIR) M=$(PWD) modules

	@echo "===== Building Test App ====="
	$(CC) -o $(FILE_NAME) $(FILE_NAME).c


# 安装到开发板（NFS）
install:
	@echo "===== Install Driver ====="
	cp ./$(DRIVER_NAME).ko $(FS_FILE)

	@echo "===== Install App ====="
	cp ./$(FILE_NAME) $(FS_FILE)


# 卸载
uninstall:
	rm -rf $(FS_FILE)$(FILE_NAME)
	rm -rf $(FS_FILE)$(DRIVER_NAME).ko


# 清理
clean:
	make -C $(KERN_DIR) M=$(PWD) modules clean
	rm -rf modules.order $(FILE_NAME)


# 驱动编译
obj-m += $(DRIVER_NAME).o

.PHONY: all clean install uninstall