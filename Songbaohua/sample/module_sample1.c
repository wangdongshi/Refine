#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

int add_integer(int a, int b)
{
	return a + b;
}

EXPORT_SYMBOL(add_integer);
