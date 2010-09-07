#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xa7672d5a, "module_layout" },
	{ 0x8f2874c8, "cdev_alloc" },
	{ 0xba13492, "cdev_del" },
	{ 0x74450b25, "cdev_init" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0xb72397d5, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0xed24100d, "cdev_add" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "229BFB21BD7760AF0FF253E");
