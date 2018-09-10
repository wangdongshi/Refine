// A "seond" device driver as an example of kernel timer

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <asm/io.h>
#include <asm/switch_to.h>
//#include <asm/system.h>
//#include <asm/uaccess.h>
#include <linux/timer.h> /* must */
#include <asm/atomic.h> 

#define SECOND_MAJOR 259

static int second_major = SECOND_MAJOR;

/* sencond charactor device struct */
struct second_dev
{
  struct cdev cdev;
  atomic_t counter; /* total seconds */
  struct timer_list s_timer; /* timer of device */
};

struct second_dev *second_devp; /* device struct pointer */

/* timer function */
static void second_timer_handle(unsigned long arg)
{
  mod_timer(&second_devp->s_timer,jiffies + HZ);
  atomic_inc(&second_devp->counter);
  
  printk(KERN_NOTICE "current jiffies is %ld\n", jiffies);
}

/* device open function */
int second_open(struct inode *inode, struct file *filp)
{
  /* init timer */
  init_timer(&second_devp->s_timer);
  second_devp->s_timer.function = &second_timer_handle;
  second_devp->s_timer.expires = jiffies + HZ;
  
  add_timer(&second_devp->s_timer); /* add timer */
  
  atomic_set(&second_devp->counter,0); /* clear conter*/

  return 0;
}

/* device release */
int second_release(struct inode *inode, struct file *filp)
{
  del_timer(&second_devp->s_timer);
  
  return 0;
}

/* globalfifo reading function */
static ssize_t second_read(struct file *filp, char __user *buf, size_t count,
  loff_t *ppos)
{  
  int counter;
  
  counter = atomic_read(&second_devp->counter);
  if(put_user(counter, (int*)buf))
  	return - EFAULT;
  else
  	return sizeof(unsigned int);  
}

/* file opt strct */
static const struct file_operations second_fops =
{
  .owner = THIS_MODULE, 
  .open = second_open, 
  .release = second_release,
  .read = second_read,
};

/* init and register function */
static void second_setup_cdev(struct second_dev *dev, int index)
{
  int err, devno = MKDEV(second_major, index);

  cdev_init(&dev->cdev, &second_fops);
  dev->cdev.owner = THIS_MODULE;
  dev->cdev.ops = &second_fops;
  err = cdev_add(&dev->cdev, devno, 1);
  if (err)
    printk(KERN_NOTICE "Error %d adding LED%d", err, index);
}

/* device driver module loading function */
int second_init(void)
{
  int ret;
  dev_t devno = MKDEV(second_major, 0);

  /* apply device number */
  if (second_major)
    ret = register_chrdev_region(devno, 1, "second");
  else  /* dynamic apply device number */
  {
    ret = alloc_chrdev_region(&devno, 0, 1, "second");
    second_major = MAJOR(devno);
  }
  if (ret < 0)
    return ret;
  /* dynamic apply device struct */
  second_devp = kmalloc(sizeof(struct second_dev), GFP_KERNEL);
  if (!second_devp)    /* failed to apply */
  {
    ret =  - ENOMEM;
    goto fail_malloc;
  }

  memset(second_devp, 0, sizeof(struct second_dev));

  second_setup_cdev(second_devp, 0);

  return 0;

  fail_malloc: unregister_chrdev_region(devno, 1);
}

/* module unloading function */
void second_exit(void)
{
  cdev_del(&second_devp->cdev);   /* delete cdev */
  kfree(second_devp);     /* release device struct */
  unregister_chrdev_region(MKDEV(second_major, 0), 1); /* release device number */
}

MODULE_AUTHOR("Wang Yu");
MODULE_LICENSE("Dual BSD/GPL");

module_param(second_major, int, S_IRUGO);

module_init(second_init);
module_exit(second_exit);
