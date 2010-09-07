obj-m :=char_driver_ioctlrw.o
obj-m +=char_driver_ioctlvar.o

KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf $(wildcard *.o *.ko mo* Mo* *.mod.c )
