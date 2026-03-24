CC := $(CROSS_COMPILE)gcc
MODE_NAME = sr04
FILE_NAME = $(MODE_NAME)_test
DRIVER_NAME = $(MODE_NAME)_drv
# 定义NFS根文件系统目录  
FS_FILE = ~/nfs/
 
KERN_DIR = /home/syw/100ask_imx6ull-sdk/Linux-4.9.88 # 板子所用内核源码的目录
 
# 默认目标  
all:  
	@echo "Starting build process..."  
	@echo "Building kernel modules..."  
	make -C $(KERN_DIR) M=$(PWD) modules  
	@echo "Building $(FILE_NAME) test program..."  
	$(CC) -o $(FILE_NAME) $(FILE_NAME).c  
 
# 安装目标  
install:  
	@echo "Installing $(DRIVER_NAME).ko to $(FS_FILE)..."  
	cp ./$(DRIVER_NAME).ko $(FS_FILE)  
	@echo "$(DRIVER_NAME).ko installed."  
	@echo "Installing $(FILE_NAME) to $(FS_FILE)..."  
	cp ./$(FILE_NAME) $(FS_FILE)  
	@echo "$(FILE_NAME) installed."  
 
uninstall:
	rm -rf $(FS_FILE)$(FILE_NAME)
	rm -rf $(FS_FILE)$(DRIVER_NAME).ko
 
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order  $(FILE_NAME)
 
# 参考内核源码drivers/char/ipmi/Makefile
# 要想把a.c, b.c编译成ab.ko, 可以这样指定:
# ab-y := a.o b.o
# obj-m += ab.o
 
obj-m += $(DRIVER_NAME).o
# 声明伪目标  
.PHONY: all clean install uninstall
