#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x972f93ab, "module_layout" },
	{ 0x215f7233, "cdev_del" },
	{ 0xc8ab5383, "device_destroy" },
	{ 0xad39bb2b, "class_destroy" },
	{ 0x712605e5, "device_create" },
	{ 0x5b54da1d, "__class_create" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xa89d7d2, "cdev_add" },
	{ 0xe3b72f06, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x69acdf38, "memcpy" },
	{ 0xdc80a8de, "kmem_cache_alloc_trace" },
	{ 0xbdbfaccb, "kmalloc_caches" },
	{ 0xc5850110, "printk" },
	{ 0x37a0cba, "kfree" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "40632EE2A240B74C6F56ECC");
