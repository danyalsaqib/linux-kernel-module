#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

// Defining various variables
#define mem_size 8
dev_t dev = 0;
static struct class *dev_class;
static struct cdev my_cdev;
int8_t *kernel_buffer;


// Function Prototypes
static int func_init(void);
static void func_exit(void);
static int cTD_open(struct inode *inode, struct file *file);
static ssize_t cTD_read(struct file *filep, char __user *buf, size_t len, loff_t *off);
static ssize_t cTD_write(struct file *filep, const char *buf, size_t len, loff_t *off);
static int cTD_release(struct inode *inode, struct file *file);


// File Operation Structure Definition
static struct file_operations fops = {

	.owner 		= THIS_MODULE,
	.open		= cTD_open,
	.read		= cTD_read,
	.write		= cTD_write,
	.release	= cTD_release

};


// Defining file operations
static int cTD_open(struct inode *inode, struct file *file)
{
	// Allocate some memory for the Kernel Buffer
	if((kernel_buffer = kmalloc(mem_size, GFP_KERNEL)) == 0){
		printk(KERN_ALERT "Could not allocate a Kernel Buffer for the device\n");
		return -1;
	}
	printk(KERN_ALERT "Successfully opened file\n");
	return 0;
}
static ssize_t cTD_read(struct file *filep, char __user *buf, size_t len, loff_t *off)
{
	copy_to_user(buf, kernel_buffer, mem_size);
	printk(KERN_ALERT "Successfully read from file\n");
	return mem_size;
}
static ssize_t cTD_write(struct file *filep, const char *buf, size_t len, loff_t *off)
{
	memcpy(kernel_buffer, buf, len);
	printk(KERN_ALERT "Data has been successfully written to Kernel Buffer\n");
	printk(KERN_ALERT "Printing Kernel Buffer Data:");
	int i = 0;
	for (i = 0; i < mem_size; i++)
	{
		printk(KERN_ALERT "Contents of buffer: index %d = %d\n", i, kernel_buffer[i]);
	}
	return len;

}
static int cTD_release(struct inode *inode, struct file *file)
{
	kfree(kernel_buffer);
	printk(KERN_ALERT "Successfully closed file\n");
	return 0;

}


static int func_init(void)
{
	// Dynamically allocate Major Number
	if((alloc_chrdev_region(&dev, 0, 1, "deviceRegionCustom\n")) < 0){
		printk(KERN_ALERT "Could not allocate Major Number\n");
		return -1;
	}

	printk(KERN_ALERT "Successfully Allocated Major Number\n");
	printk(KERN_ALERT "Major Number: %d, Minor Number: %d\n", MAJOR(dev), MINOR(dev));


	// Create new CDEV structure, initialize it, and register it with the kernel
		cdev_init(&my_cdev, &fops);
		if((cdev_add(&my_cdev, dev, 1)) < 0){
			printk(KERN_ALERT "Unable to add CDEV to Kernel\n");
			goto r_class;
		}

		printk(KERN_ALERT "Successfully registered character device with Kernel\n");

		
		// Create new struct class, and use it to create a device (node)
		if((dev_class = class_create(THIS_MODULE, "chr_class")) == NULL){
			printk(KERN_ALERT "Failed to create struct class\n");
			goto r_class;
		}

		if((device_create(dev_class, NULL, dev, NULL, "chr_device")) == NULL){
			printk(KERN_ALERT "Failed to create device node\n");
			goto r_device;
		}
	
	printk(KERN_ALERT "Successfully added device node for user-space access\n");
	printk(KERN_ALERT "Successfully completed device driver setup\n");
	return 0;


r_class:
	unregister_chrdev_region(dev, 1);
	printk(KERN_ALERT "Unregistered Character Driver Region\n");
	return -1;

r_device:
	class_destroy(dev_class);
	printk(KERN_ALERT "Destroyed Struct Class\n");
	return -1;

}


void func_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev, 1);
	printk(KERN_ALERT "Device Driver has been removed successfully\n");
}


module_init(func_init);
module_exit(func_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Danyal Saqib");
MODULE_DESCRIPTION("Character Device Driver");
