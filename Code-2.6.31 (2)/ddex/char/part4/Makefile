obj-m :=chr_drv_complete.o
obj-m +=chr_drv_sema.o
obj-m +=chr_drv_wait_event.o
obj-m +=chr_drv_waitexcl.o
obj-m +=chr_drv_killable.o

KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf $(wildcard *.o *.ko mo* Mo* *.mod.c )
