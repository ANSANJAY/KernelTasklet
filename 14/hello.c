#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/sched.h>


MODULE_LICENSE("GPL");


char tasklet_data[] = "linux kernel is very easy";



void tasklet_function(unsigned long data)
{
	pr_info("%s:data:%s\n", __func__, (char *)data);
	pr_info("current pid : %d , current process : %s\n",current->pid, current->comm);
	return;
}


static struct tasklet_struct *my_tasklet;

static int test_tasklet_init(void)
{
        pr_info("%s: In init\n", __func__);
	my_tasklet = kmalloc(sizeof(struct tasklet_struct), GFP_KERNEL);
	tasklet_init(my_tasklet, tasklet_function, tasklet_data);
	tasklet_schedule(my_tasklet);	
	return 0;
}

static void test_tasklet_exit(void)
{
        pr_info("%s: In exit\n", __func__);
	kfree(my_tasklet);
}

module_init(test_tasklet_init);
module_exit(test_tasklet_exit);
