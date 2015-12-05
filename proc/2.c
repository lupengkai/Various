#include <linux/module.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#define STRINGLEN 1024

char gbuffer[STRINGLEN];
struct proc_dir_entry *mydir, *lu_file, *pengkai_file, *symlink;

int
proc_read_lu(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int len;
	try_module_get(THIS_MODULE);
	len = sprintf(page, "current process message: \nname: %s \npid: %d\n", current->comm, current->pid);
	module_put(THIS_MODULE);
	return len;
}

int
proc_read_pengkai(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int len;
	try_module_get(THIS_MODULE);
	len = sprintf(page, "pengkai messages: %s\nwrite:%s\n", current->comm, gbuffer);
	module_put(THIS_MODULE);
	return len;
}
int
proc_write_pengkai(struct file *file, const char *buffer, unsigned long count, void *data)
{
	int len;
	try_module_get(THIS_MODULE);
	if(count >= STRINGLEN)
		len = STRINGLEN - 1;
	else
		len = count;
	copy_from_user(gbuffer, buffer, len);
	gbuffer[len] = '\0';
	printk("%s",gbuffer);
	module_put(THIS_MODULE);
	return len;
}

static int
init(void)
{
	mydir = proc_mkdir("13130120135",NULL);
	lu_file = create_proc_read_entry("lu", 0666, mydir,proc_read_lu, NULL);
	pengkai_file = create_proc_entry("pengkai", 0644, mydir);
	strcpy(gbuffer, "hello 13130120135");
	pengkai_file->read_proc = proc_read_pengkai;
	pengkai_file->write_proc = proc_write_pengkai;
	symlink = proc_symlink("lu.link",mydir,"lu");
	return 0;
}

static void
final(void)
{
	remove_proc_entry("lu.link", mydir);
	remove_proc_entry("pengkai", mydir);
	remove_proc_entry("lu", mydir);
	remove_proc_entry("13130120135",NULL);

}
module_init(init);
module_exit(final);

MODULE_AUTHOR("LuPengkai");
MODULE_LICENSE("GPL");
