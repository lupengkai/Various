#include <linux/module.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#define  DEVICE_NAME  "rwbuf"
#define  RWBUF_CLEAR   0x909090     // IO Ctrl Command


// rwbuf.c,  driver for virtual char-device

static int inuse=0;	// only one process permited at the same time
static int  rwbuf_open ( struct inode *inode,  struct file * filep )  {
    if (inuse >= 1)  return  -1;
    inuse = 1;

   try_module_get(THIS_MODULE);	// increase the use count in struct module
   return 0;
}

static int rwbuf_close( struct inode *inode,  struct file * filep ) {
	inuse  =  0;
	module_put(THIS_MODULE);
	return 0;
}


#define  rwbuf_size  1024                 // MAX size of buffer
static char  rwbuf[rwbuf_size]={"13130120135"};

static int     rwlen = 0;  // length of string

static ssize_t rwbuf_write ( struct file * filep, const char *buf, size_t count, loff_t * ppos )
{
	if (count >= rwbuf_size)
		rwlen = rwbuf_size-1;
	else
		rwlen = count;

	copy_from_user(rwbuf, buf, rwlen);
   //  print some message by printk();
	printk(buf);
	return count;
}

// rwbuf.c,  driver for virtual char-device

static ssize_t rwbuf_read( struct file* filep,   char * buf, size_t count, loff_t* ppos)
{
        
	copy_to_user( buf, rwbuf, count);
	printk("%s",rwbuf);
	return count;
}


// rwbuf.c,  driver for virtual char-device

static int  rwbuf_ioctl  (  struct inode *inode,  struct file * filep,
			unsigned int cmd, unsigned long arg )
{
	if ( cmd == RWBUF_CLEAR )  {
		rwlen = 0;	// clear buf by set its len to zero
		printk("rwbuf in kernel zero-ed\n");
		//break;
	};

	return 0;
}



// rwbuf.c,  driver for virtual char-device


static struct file_operations rwbuf_fops =
{
	open:     rwbuf_open,
	release: rwbuf_close,
	read:      rwbuf_read,
	write:     rwbuf_write,
	ioctl:      rwbuf_ioctl,
};

int init_module()
{
      printk("Hello world\n");
      if(register_chrdev(60,DEVICE_NAME,&rwbuf_fops))		
      {  printk("register error\n");
         return -1; 
      }


     printk("register ok\n");


     return 0;
}

void cleanup_module()
{
	unregister_chrdev(60,DEVICE_NAME);
    printk("bye\n");
 }
