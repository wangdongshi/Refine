#include <linux/init.h>
#include <linux/module.h>

static int num = 4000;

static int hello_init(void)
{
	printk("Hello Linux driver! (num = %d)\n", num);
	return 0;
}

static void hello_exit(void)
{
	printk("Bye-bye Linux driver!\n");
	return;
}

module_init(hello_init);
module_exit(hello_exit);

module_param(num, int, S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("WANGYU");
MODULE_DESCRIPTION("Just for test Linux driver.");
MODULE_ALIAS("Demo");
