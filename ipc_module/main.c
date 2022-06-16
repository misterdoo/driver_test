#define _GNU_SOURCE 1
#include <linux/version.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0)
#define HAVE_PROC_OPS
#endif

int simple_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "Hello simple proc\n");
	return 0;
}

int simple_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, simple_proc_show, NULL);
}

#ifdef HAVE_PROC_OPS
static const struct proc_ops simple_proc_fops = {
	.proc_open		= simple_proc_open,
	.proc_read		= seq_read,
	.proc_lseek		= seq_lseek,
	.proc_release	= single_release
};
#else
static const struct file_operations simple_proc_fops = {
	.owner		= THIS_MODULE,
	.open		= simple_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};
#endif

int __init simple_init(void)
{
	proc_create("simple_test", 0, NULL, &simple_proc_fops);
	return 0;
}

void __exit simple_exit(void)
{
	remove_proc_entry("simple", NULL);
}

module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
