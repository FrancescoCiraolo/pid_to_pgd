obj-m += pid_to_pgd.o

#generate the path
CURRENT_PATH:=$(shell pwd)

#the current kernel version number
LINUX_KERNEL:=$(shell uname -r)

#the absolute path
LINUX_KERNEL_PATH:=/home/fciraolo/BU/research/xilinx_setup_new/xilinx_setup/linux-xlnx

DIST_PATH:=dist

all: kernel

kernel:
	@echo $(LINUX_KERNEL_PATH)
	make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

#clean
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
