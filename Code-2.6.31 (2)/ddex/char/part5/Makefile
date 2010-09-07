obj-m :=interrupt.o
obj-m +=timer.o
obj-m +=hrexamp.o
obj-m +=wrkqueue.o
obj-m +=mytasklet.o

KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf $(wildcard *.o *.ko mo* Mo* *.mod.c )
