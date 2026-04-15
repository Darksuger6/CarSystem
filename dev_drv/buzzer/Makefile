KERN_DIR = /home/syw/100ask_imx6ull-sdk/Linux-4.9.88

all:
	make -C $(KERN_DIR) M=`pwd` modules 
	$(CROSS_COMPILE)gcc -o buzzer_test buzzer_test.c

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -f buzzer_test modules.order

obj-m += buzzer_drv.o