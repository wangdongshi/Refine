#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
	printk(KERN_ALERT "Hello World module inserted.\n");
	return 0;
}
module_init(hello_init);

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Hello World module exit.\n");
}
module_exit(hello_exit);

MODULE_AUTHOR("Wang Yu");
MODULE_LICENSE("Dual BSD/GPL");
