
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>
#include"header.h"
struct data 
{
	int a;
	int b;
	char oper;
};
#define NAME chardevice
int a=0,b=0,value=0;
int NAME_open(struct inode *inode,struct file *filp);
long NAME_ioctl(struct file *filp,unsigned int cmd,unsigned long arg);
int NAME_release(struct inode *inode,struct file *filp);

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = NAME_open,
	.read = NAME_read,
	.write = NAME_write,
	.release = NAME_release,
};

dev_t mydev;

struct cdev *my_cdev;

static int __init ioctl_init(void)
{
	int result;
	int MAJOR,MINOR;
	result = alloc_chrdev_region(&mydev,0,1,"chardevice");
	MAJOR=MAJOR(mydev);
	MINOR=MINOR(mydev);
	printk("major is :%d and minor is %d\n",MAJOR,MINOR);
	if(result<0)
	{
		printk("region request is not obtain\n");
		return(-1);
	}
	my_dev=cdev_alloc();
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
static void __exit ioctl_exit(void)
{
	unregister_chrdev_region(mydev,1);
	cdev_del(my_cdev);
	printk("bye");
	return 0;
}
int NAME_open(struct inode *inode,struct file *filp)
{
	printk(""open sys call\n");
	return 0;
}

long NAME_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	struct data *data;
	char ubuff[50];
	switch(cmd)
	{
		case module: data=(struct data*)ubuff;
			     copy_from_user(ubuff,(struct data *)arg,sizeof(struct data));
			     printk("oper=%c\n",data->oper);
			     printk("a=%d\n",data->a);
			     printk("b=%d\n",data->b);
			     if(data->oper=='+')
			     {
				     value=data->a+data->b;
				     printk("add of two numbers is :%d\n",value);
			     }
			     else if(data->oper=='-')
			     {
				     value=data->a-data->b;
				     printk("sub of two numbers is :%d\n",value);
			     }
			     else if(data->oper=='*')
			     {
				     value=data->a*data->b;
				     printk("mul of two numbers is :%d\n",value);
			     }
			     else 
				     break;
	}
	return 0;

}
int NAME_release(struct inode *inode,struct file *filp)
{
	printk("close and bye");
	return 0;
}
module_init(ioctl_init);
module_exit(ioctl_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAMKI");


