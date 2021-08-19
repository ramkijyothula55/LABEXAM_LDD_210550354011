

#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include"header.h"
struct module_data
{
	int num1;
	int num2;
	char operator;
};
struct module_data data;
int main()
{
	int fd;
	int value;
	fd=open("/dev/ioctl",O_RDWR,0777);
	if(fd<0)
	{
		printf("error opening device\n");
		exit(1);
	}

	printf("operations to perform\n");
	printf("enter (+) operator to addition\n");
	printf("enter (-) operator to subtract\n");
	printf("enter (*) operator to multiply\n");
	printf("choose your opertor\n");
	scanf("%c",&data.operator);

	printf("enter first:");
	scanf("%d",&data.num1);
	printf("enter second:");
	scanf("%d",&data.num2);
	printf("writing value to driver\n");
	ioctl(fd,module,&data);
	close(fd);
	return 0;
}

