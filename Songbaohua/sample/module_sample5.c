#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DEV_FIFO_MAJOR		350
#define DEV_FIFO_SIZE		0x1000

typedef struct {
	unsigned char buffer[DEV_FIFO_SIZE];
	struct cdev cdev;
} MY_CHAR_DEV;

#if 0
struct class*	cls;
#endif
static dev_t	devno;
MY_CHAR_DEV*	dev;

static int dev_fifo_open(struct inode *inode, struct file *file);
static int dev_fifo_release(struct inode *inode, struct file *file);
static ssize_t dev_fifo_read(struct file *filp, char __user *user_buf, size_t size, loff_t *ppos);
static ssize_t dev_fifo_write(struct file *file, const char __user *user_buf, size_t size, loff_t *ppos);
int dev_fifo_init(void);
void dev_fifo_exit(void);

static const struct file_operations dev_operations = {
	.owner	= THIS_MODULE,
	.open	= dev_fifo_open,
	.release= dev_fifo_release,
	.read	= dev_fifo_read,
	.write	= dev_fifo_write,
};

module_init(dev_fifo_init);
module_exit(dev_fifo_exit);

static int dev_fifo_open(struct inode *inode, struct file *file)
{	
	printk("Open FIFO device successfully!\n");
	return 0;
}

static int dev_fifo_release(struct inode *inode, struct file *file)
{
	printk("Release FIFO device successfully!\n");
	return 0;
}

static ssize_t dev_fifo_read(struct file *filp, char __user *user_buf, size_t size, loff_t *ppos)
{
	int		n;
	int		ret;
	char*	kernel_buf;

	if (*ppos > DEV_FIFO_SIZE) return -ENXIO;

	if (size > DEV_FIFO_SIZE - *ppos) n = DEV_FIFO_SIZE - *ppos;
	else n = size;
	kernel_buf = dev->buffer + *ppos;
	ret = copy_to_user(user_buf, kernel_buf, n); // here is key operation
	if (ret != 0) return -EFAULT;
	*ppos += n;

	printk("Read from FIFO device successfully!\n");
	return n;
}

static ssize_t dev_fifo_write(struct file *file, const char __user *user_buf, size_t size, loff_t *ppos)
{
	int		n;
	int		ret;
	char*	kernel_buf;

	if (*ppos > DEV_FIFO_SIZE) return -ENXIO;

	if (size > DEV_FIFO_SIZE - *ppos) n = DEV_FIFO_SIZE - *ppos;
	else n = size;
	kernel_buf = dev->buffer + *ppos;
	ret = copy_from_user(kernel_buf, user_buf, n); // here is key operation
	if (ret != 0) return -EFAULT;
	*ppos += n;

	printk("Write to FIFO device successfully!\n");
	return n;
}

int dev_fifo_init(void)
{
	int ret;
	
	// Step1 : prepare for device driver (alloc memory for my charactor device)
	dev = kmalloc(sizeof(MY_CHAR_DEV), GFP_KERNEL);
	if (!dev) {
		printk("Fail to alloc the memory of device [fifodev].\n");
		return -ENOMEM;
	}
	memset(dev, 0, sizeof(MY_CHAR_DEV));
	
	// Step2 : register device number
	devno = MKDEV(DEV_FIFO_MAJOR, 0);
	ret = register_chrdev_region(devno, 1, "fifodev");
	if (ret < 0) {
		ret =  alloc_chrdev_region(&devno, 0, 1, "fifodev");
		if (ret < 0) {
			printk("Fail to register the driver of device [fifodev].\n");
			goto err_register_chrdev_region;
		}
	}
	
#if 0
	// Step3 : create device class (create interface in /sys/class/fifodev folder)
	cls = class_create(THIS_MODULE, "fifodev");
	if (IS_ERR(cls)) {
		printk("Fail to create the driver class of device [fifodev].\n");
		unregister_chrdev_region(devno, 1);
		goto err_class_create;
	}
#endif
	
	// Step4 : initialize charactor device (just operat in software, there is not error)
	cdev_init(&dev->cdev, &dev_operations);

	// Step5 : add device to OS
	ret = cdev_add(&dev->cdev, devno, 1);
	if (ret < 0) {
		printk("Fail to add the device [fifodev] driver to system.\n");
#if 0
		goto err_cdev_add;
#else
		goto err_class_create;
#endif
	}
	
#if 0
	// Step6 : export device information to user space (/sys/class/class_name/device_name)
	device = device_create(cls, NULL, devno, NULL, "fifodev",);
	if (IS_ERR(device)) {
		ret = PTR_ERR(device);
		printk("Fail to export device [fifodev] information to user space.\n");
		goto err_device_create; 
	}
#endif
	
	printk("Register device [fifodev] driver to system!\n");
	return 0;

#if 0
err_device_create:
	cdev_del(&dev->cdev);

err_cdev_add:
	class_destroy(cls);
#endif

err_class_create:
	unregister_chrdev_region(devno, 1);

err_register_chrdev_region:
	return ret;
}

void dev_fifo_exit(void)
{
#if 0
	device_destroy(cls, devno);
	class_destroy(cls);
#endif
	cdev_del(&dev->cdev);
	unregister_chrdev_region(devno, 1);
	kfree(dev);

	return;
}

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("WANGYU");
MODULE_DESCRIPTION("Just for test Linux driver.");
MODULE_ALIAS("FIFO");
