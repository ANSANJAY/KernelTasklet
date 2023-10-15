obj-m := hello.o

all:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/linuxtrainer/raspberrypi/linux M=$(PWD) modules
clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/linuxtrainer/raspberrypi/linux M=$(PWD) clean
