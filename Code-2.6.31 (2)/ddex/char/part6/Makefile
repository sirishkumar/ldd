obj-m := chr_drv_async.o
obj-m += chr_drv_poll.o

KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm -rf $(wildcard *.o *.ko mo* Mo* *.mod.c *.order)

