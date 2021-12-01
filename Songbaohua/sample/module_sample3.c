#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

static dev_t			dev_no;
static struct cdev		dev;

static int dev_open(struct inode * nodep, struct file * filep)
{
    printk("Open device. (Major=%d, Minor=%d)\n", MAJOR(nodep->i_rdev), MINOR(nodep->i_rdev));
    return 0;
}

static int dev_release(struct inode * nodep, struct file * filep)
{
    printk("Close device. (Major=%d, Minor=%d)\n", MAJOR(nodep->i_rdev), MINOR(nodep->i_rdev));
    return 0;
}

static ssize_t dev_write(struct file *filep, const char __user *u, size_t sz, loff_t *off)
{
	unsigned char buf[1000];
	copy_from_user(buf, u, sz);
    printk("Execute device writing.\n");
    return 0;
}

static const struct file_operations dev_operations = {
    .owner		= THIS_MODULE,
    .open		= dev_open,
    .release	= dev_release,
    .write		= dev_write,
};

static int dev_init(void)
{
    int ret;
	
	// Step1 : register device number
    dev_no = MKDEV(340, 0);
	ret = register_chrdev_region(dev_no, 1, "test_dev");
	if (ret < 0) {
		ret = alloc_chrdev_region(&dev_no, 0, 1, "test_dev");
		if (ret < 0) return ret;
	}
	
	// Step2 : initialize charactor device
	cdev_init(&dev, &dev_operations);
	
	// Step3 : add device to OS
    ret = cdev_add(&dev, dev_no, 1);
    if (ret < 0) return ret;
	
    printk("Device [test_dev] driver has been registered to system!\n");
    return 0;
}

static void dev_exit(void)
{
    cdev_del(&dev);
    unregister_chrdev_region(dev_no, 1);
	
    printk("Device [test_dev] driver has been remove from system!\n");
	return;
}

module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("WANGYU");
MODULE_DESCRIPTION("Just for test Linux driver.");
MODULE_ALIAS("TEST");
