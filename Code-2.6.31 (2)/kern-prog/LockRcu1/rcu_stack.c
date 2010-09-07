#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/rcupdate.h>
#include<linux/rculist.h>
#include<linux/list.h>
#include "my_rcu.h"

struct node *p;
LIST_HEAD(head);

EXPORT_SYMBOL(head);

void add_entry_stack(int num1,int num2)  
{
	p=kmalloc(sizeof(*p),GFP_KERNEL);
	p->data_item1=num1;
	p->data_item2=num2;
	list_add_rcu(&p->list,&head);
}

int __init init_rcu_stack(void) 
{
	printk(KERN_INFO "%s module is inserted\n", __func__);
	add_entry_stack(10,100);
	add_entry_stack(20,200);
	add_entry_stack(30,300);
	add_entry_stack(40,400);
	return 0;
}
void __exit cleanup_rcu_stack(void) {
	printk(KERN_INFO "%s module is removed\n", __func__);
}

module_init(init_rcu_stack);
module_exit(cleanup_rcu_stack);

MODULE_AUTHOR("TEAM VEDA");
MODULE_DESCRIPTION("RCU STACK MODULE");
MODULE_LICENSE("GPL");
