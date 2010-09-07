obj-m =rcu_stack.o
obj-m +=rcu_reader1.o
obj-m +=rcu_reader2.o
obj-m +=rcu_writer.o

KDIR= /lib/modules/$(shell uname -r)/build
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm -rf $(wildcard  *.o *.ko *.mod.* .c* .t* *.symver *.order *.symvers *.markers)
