#include <asm/unistd.h>
#include <linux/highmem.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/dirent.h>
#include <linux/string.h>
#include <linux/fdtable.h>
#include <linux/moduleparam.h>

unsigned long *sys_call_table = (unsigned long*)0xc0583110;
static unsigned int ocr0;
unsigned int clear_cr0(){    
unsigned int cr0 = read_cr0();    
write_cr0(cr0 & 0xfffeffff);    
return cr0;
}

asmlinkage int testsyscall(int num) {
	printk("new syscall created by module  13130120135\n");
	printk("hello %d\n",num);
	return num;
}

static int hello_init(void) {
	ocr0 = clear_cr0(); 
	sys_call_table[223] = testsyscall;
	printk("module init\n");
	write_cr0(ocr0);
	return 0;
}

static void hello_exit(void) {
	printk("Goodbye,13130120135\n");
	ocr0 = clear_cr0();
	write_cr0(ocr0);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
