/*======================================================================
    A globalfifo driver as an example of char device drivers

    The initial developer of the original code is Baohua Song
    <author@linuxdriver.cn>. All Rights Reserved.
======================================================================*/



#include <linux/version.h>

#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>

//  error: implicit declaration of function `kfree`
#if LINUX_VERSION_CODE <= KERNEL_VERSION(3, 19, 0)
#include <asm/system.h>
#else
#include <linux/slab.h>
#endif

#include <asm/uaccess.h>

#define GLOBALFIFO_SIZE      0x1000            /*  全局内存最大4K字节          */
//#define MEM_CLEAR           0x1               /*  清0全局内存                 */
#define GLOBALFIFO_MAJOR     230               /*  预设的globalfifo的主设备号   */
#define GLOBALFIFO_MAGIC     'g'
#define MEM_CLEAR	    _IO(GLOBALFIFO_MAGIC, 0)

/*  globalfifo的设备号   */
static int globalfifo_major = GLOBALFIFO_MAJOR;
module_param(globalfifo_major, int, S_IRUGO);


/*  globalfifo设备结构体 */
struct globalfifo_dev
{

    struct cdev cdev;                         /*  cdev结构体  */
    unsigned int current_len;
    unsigned char mem[GLOBALFIFO_SIZE];        /*  全局内存    */
    struct mutex mutex;
    wait_queue_head_t r_wait;
    wait_queue_head_t w_wait;

};

struct globalfifo_dev *globalfifo_devp;         /*  设备结构体指针    */


/*  文件打开函数    */
int globalfifo_open(struct inode *inode, struct file *filp)
{
    /*    将设备结构体指针赋值给文件私有数据指针  */
    filp->private_data = globalfifo_devp;

    return 0;
}

/*  文件释放函数    */
int globalfifo_release(struct inode *inode, struct file *filp)
{
    return 0;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36)
/* ioctl设备控制函数 */
static int globalfifo_ioctl(
        struct inode *inodep,
        struct file *filp,
        unsigned int cmd,
        unsigned long arg)
{
#else
//long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
//long (*compat_ioctl) (struct file *file, unsigned int cmd, unsigned long arg)
static long globalfifo_compat_ioctl(
        struct file *filp,
        unsigned int cmd,
        unsigned long arg)
{
    //struct inode *inode = file->f_dentry->d_inode;
    struct inode *inode = inode = file_inode(filp);
#endif

    struct globalfifo_dev *dev = filp->private_data;/*获得设备结构体指针*/

    switch (cmd)
    {
        case MEM_CLEAR:
        {
            mutex_lock(&dev->mutex);
            memset(dev->mem, 0, GLOBALFIFO_SIZE);
            mutex_unlock(&dev->mutex);
            
            printk(KERN_INFO "globalfifo is set to zero\n");
            break;
        }

        default:
        {
            return  - EINVAL;
        }
    }

    return 0;
}

/*读函数*/
static ssize_t globalfifo_read(
        struct file *filp,
        char __user *buf,
        size_t      count,
        loff_t      *ppos)
{
    int                     ret = 0;
    struct globalfifo_dev   *dev = filp->private_data; /*获得设备结构体指针*/
    DECLARE_WAITQUEUE(wait, current);

    mutex_lock(&dev->mutex);
    add_wait_queue(&dev->r_wait, &wait);

    while (dev->current_len == 0) {
        if (filp->f_flags & O_NONBLOCK) {
            ret = -EAGAIN;
            goto out;
        }
    
        __set_current_state(TASK_INTERRUPTIBLE);
        mutex_unlock(&dev->mutex);

        schedule();
        if (signal_pending(current)) {
            ret = -ERESTARTSYS;
            goto out2;
        }

        mutex_lock(&dev->mutex);
    }

    if (count > dev->current_len) { 
        count = dev->current_len;
    }

    /*  内核空间->用户空间
     *
     *  将dev->mem中偏移p为起始的内存区域的数据, 拷贝count个字节到用户的buf中
     *  */
    if (copy_to_user(buf, (void*)(dev->mem), count))
    {
        ret =  - EFAULT;
        goto out;
    }
    else
    {
        memcpy(dev->mem, dev->mem+count, dev->current_len-count);
        dev->current_len -= count;
        printk(KERN_INFO "read %d bytes(s) from %d\n", (unsigned int)count, 
            (unsigned int)dev->current_len);

        wake_up_interruptible(&dev->w_wait);
        
        ret = count;
    }

out:
    mutex_unlock(&dev->mutex);

out2:
    remove_wait_queue(&dev->r_wait, &wait);
    set_current_state(TASK_RUNNING);
    return ret;
}

/*写函数*/
static ssize_t globalfifo_write(
        struct file         *filp,
        const char __user   *buf,
        size_t              count,
        loff_t              *ppos)
{
    int ret = 0;
    struct globalfifo_dev *dev = filp->private_data; /*获得设备结构体指针*/
    DECLARE_WAITQUEUE(wait, current);

    mutex_lock(&dev->mutex);
    add_wait_queue(&dev->w_wait, &wait);

    while (dev->current_len == GLOBALFIFO_SIZE) {
        if (filp->f_flags & O_NONBLOCK) {
            ret = -EAGAIN;
            goto err;
        }
    
        __set_current_state(TASK_INTERRUPTIBLE);
        mutex_unlock(&dev->mutex);

        schedule();
        if (signal_pending(current)) {
            ret = -ERESTARTSYS;
            goto err2;
        }

        mutex_lock(&dev->mutex);
    }

    if (count > GLOBALFIFO_SIZE - dev->current_len)
    {
        count = GLOBALFIFO_SIZE - dev->current_len;
    }

    /*  用户空间->内核空间*/
    if (copy_from_user(dev->mem + dev->current_len, buf, count) != 0)
    {
        ret =  - EFAULT;
        goto err;
    } else {
        dev->current_len += count;
        printk(KERN_INFO "written %d bytes(s) from %d\n", (unsigned int)count, 
            dev->current_len);

        wake_up_interruptible(&dev->r_wait);
        ret = count;
    }

err:
    mutex_unlock(&dev->mutex);
err2:
    remove_wait_queue(&dev->w_wait, &wait);
    set_current_state(TASK_RUNNING);
    return ret;
}

/* seek文件定位函数 */
static loff_t globalfifo_llseek(
        struct file *filp,
        loff_t      offset,
        int         orig)
{
    loff_t ret = 0;
    switch (orig)
    {
        case 0:   /*相对文件开始位置偏移*/
            if (offset < 0)
            {
                ret =  - EINVAL;
                break;
            }

            if ((unsigned int)offset > GLOBALFIFO_SIZE)
            {
                ret =  - EINVAL;
                break;
            }

            filp->f_pos = (unsigned int)offset;

            ret = filp->f_pos;

            break;

        case 1:   /*相对文件当前位置偏移*/
            if ((filp->f_pos + offset) > GLOBALFIFO_SIZE)
            {
                ret =  - EINVAL;
                break;
            }
            if ((filp->f_pos + offset) < 0)
            {
                ret =  - EINVAL;
                break;
            }

            filp->f_pos += offset;
            ret = filp->f_pos;

            break;

        default:

            ret =  - EINVAL;
            break;
    }

    return ret;
}

/*文件操作结构体*/
static const struct file_operations globalfifo_fops =
{
    .owner = THIS_MODULE,
    .llseek = globalfifo_llseek,
    .read = globalfifo_read,
    .write = globalfifo_write,

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36)
    .ioctl = globalfifo_ioctl,
#else
    //.unlocked_ioctl = globalfifo_ioctl,
    .compat_ioctl = globalfifo_compat_ioctl,
#endif

    .open = globalfifo_open,
    .release = globalfifo_release,
};

/*初始化并注册cdev*/
static void globalfifo_setup_cdev(struct globalfifo_dev *dev, int index)
{
    int err, devno = MKDEV(globalfifo_major, index);

    cdev_init(&dev->cdev, &globalfifo_fops);

    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &globalfifo_fops;

    err = cdev_add(&dev->cdev, devno, 1);
    if (err)
    {
        printk(KERN_NOTICE "Error %d adding LED%d", err, index);
    }
}

/*  设备驱动模块加载函数    */
int globalfifo_init(void)
{
    int result;
    dev_t devno = MKDEV(globalfifo_major, 0);

    /*  申请设备号  */
    if (globalfifo_major != 0)
    {
        result = register_chrdev_region(devno, 1, "globalfifo");
        printk(KERN_INFO "register char device drivers [globalfifo], MAJOR = %d\n", globalfifo_major);
    }
    else  /* 动态申请设备号 */
    {
        result = alloc_chrdev_region(&devno, 0, 1, "globalfifo");
        globalfifo_major = MAJOR(devno);
        printk(KERN_INFO "alloc char device drivers [globalfifo], MAJOR = %d\n", globalfifo_major);
    }

    if (result < 0)
    {
        return result;
    }

    /* 动态申请设备结构体的内存*/
    globalfifo_devp = kmalloc(sizeof(struct globalfifo_dev), GFP_KERNEL);
    if (!globalfifo_devp)    /*  申请失败    */
    {
        result =  - ENOMEM;
        unregister_chrdev_region(devno, 1);

        return result;
    }
    memset(globalfifo_devp, 0, sizeof(struct globalfifo_dev));
    
    globalfifo_setup_cdev(globalfifo_devp, 0);

    mutex_init(&globalfifo_devp->mutex);
    init_waitqueue_head(&globalfifo_devp->r_wait);
    init_waitqueue_head(&globalfifo_devp->w_wait);

    return 0;
}

/*模块卸载函数*/
void globalfifo_exit(void)
{
    cdev_del(&globalfifo_devp->cdev);   /*注销cdev*/

    kfree(globalfifo_devp);     /*释放设备结构体内存*/

    unregister_chrdev_region(MKDEV(globalfifo_major, 0), 1); /*释放设备号*/
}


//Driver Information
#define DRIVER_VERSION  "1.0.0"
#define DRIVER_AUTHOR   "Gatieme @ AderStep Inc..."
#define DRIVER_DESC     "Linux input module for Elo MultiTouch(MT) devices"
#define DRIVER_LICENSE  "Dual BSD/GPL"

// Kernel Module Information
MODULE_VERSION(DRIVER_VERSION);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE(DRIVER_LICENSE);


module_init(globalfifo_init);
module_exit(globalfifo_exit);
