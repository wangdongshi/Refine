# The samplest makefile for linux driver program

ifneq ($(KERNELRELEASE),) # call from kernel build system

scull-objs := main.o access.o pipe.o
obj-m	   := scull.o

else # call from command line

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif



clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions
	rm -rf *.order *.symvers

depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend


ifeq (.depend,$(wildcard .depend))

include .depend

endif

