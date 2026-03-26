CC := $(CROSS_COMPILE)gcc

MODE_NAME = buzzer
FILE_NAME = $(MODE_NAME)_test
DRIVER_NAME = $(MODE_NAME)_drv

FS_FILE = ~/nfs/
KERN_DIR = /home/syw/100ask_imx6ull-sdk/Linux-4.9.88

all:
	@echo "===== Building BUZZER Driver ====="
	make -C $(KERN_DIR) M=$(PWD) modules

	@echo "===== Building Test App ====="
	$(CC) -o $(FILE_NAME) $(FILE_NAME).c

install:
	cp ./$(DRIVER_NAME).ko $(FS_FILE)
	cp ./$(FILE_NAME) $(FS_FILE)

uninstall:
	rm -rf $(FS_FILE)$(FILE_NAME)
	rm -rf $(FS_FILE)$(DRIVER_NAME).ko

clean:
	make -C $(KERN_DIR) M=$(PWD) modules clean
	rm -rf modules.order $(FILE_NAME)

obj-m += $(DRIVER_NAME).o

.PHONY: all clean install uninstall