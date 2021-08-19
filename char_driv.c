
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/semaphore.h>
#include<linux/rwsem.h>

#define NAME chardevice
DEFINE_SEMAPHORE(sem);
struct rw_semaphore;

int NAME_open(struct inode *inode,struct file *filp);
int NAME_release(struct inode *inode,struct file *filp);
ssize_t NAME_write(struct file *filp,const char __user *ubuff,size_t count,loff_t *offp);
ssize_t NAME_read(struct file *filp,char __user *ubuff,size_t count,loff_t *offp);
struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = NAME_open,
	.read = NAME_read,
	.write = NAME_write,
	.release=NAME_release,
};
dev_t mydev;
struct cdev *my_cdev;

static int __init chardevice_init(void)
{
	int result;
	int MAJOR,MINOR;
	mydev = MKDEV(255,0);
	MAJOR=MAJOR(mydev);
	MINOR=MINOR(mydev);
	printk("major number is :%d and minor number is :%d\n ",MAJOR,MINOR);
	result = register_chrdev_region(mydev,1,"chardevice");
	if(result<0)
	{
		printk("the region request is not obtained\n");
		return(-1);
	}
	my_cdev=cdev_alloc();
	my_cdev->ops=&fops;
	result=cdev_add(my_cdev,mydev,1);
	if(result<0)
	{
		printk("char device is not created\n");
		unregister_chrdev_region(mydev,1);
		return(-1);
	}
	return 0;
}

static void __exit chardevice_exit(void)
{
	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk("bye");
	return 0;
}
int NAME_open(struct inode *inode,struct file *filp)
{
	printk("kernel open call \n");
	return 0;
}
int NAME_release(struct inode *inode,struct file *filp)
{
	printk("kernel close and bye");
	return 0;
}
ssize_t NAME_read(struct file *filp,char __user *ubuff,size_t count,loff_t *offp);

{
	void down_read(struct rw_semaphore *);


	char kbuff[50]="this is embedded";
	unsigned long result;
	ssize_t retval;
	result=copy_to_user((char *)ubuff,(char *)kbuff,count);
	if(result==0)
	{
		printk("data successful read \n");
		retval=count;
		return retval;
		void up_read(struct rw_semaphore *);
	}
	else if(result>0)
	{
		retval=(count-result);
		return retval;
	}
	else 
	{
		printk("error writing data \n");
	       retval=-EFAULT;
       return retval;
	}
}
ssize_t NAME_write(struct file *filp,const char __user *ubuff,size_t count,loff_t *offp);
{
 	void down_write(struct rw_semaphore);

	char kbuff[100];
	unsigned long result;
	ssize_t retval;
	result=copy_from_user((char *)kbuff,(char *)ubuff,count);
	if(result==0)
	{
		printk("received from user :%s\n",kbuff);
		retval=count;
		return retval;
		void up_write(struct rw_semaphore *);
	}

	else 
	{
		printk("error in writing data \n");
		reval=-EFAULT;
		return retval;
	}
}
module_init(chardevice_init);
module_exit(chardevice_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMKI");













