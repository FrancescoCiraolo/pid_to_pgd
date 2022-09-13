obj-m += pid_to_pgd.o

#generate the path
CURRENT_PATH:=$(shell pwd)

#the current kernel version number
LINUX_KERNEL:=$(shell uname -r)

#the absolute path
LINUX_KERNEL_PATH:=/usr/src/linux-headers-$(LINUX_KERNEL)

all: kernel

kernel:
	@echo $(LINUX_KERNEL_PATH)
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules

#clean
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
