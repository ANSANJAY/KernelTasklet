#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");


char tasklet_data[] = "linux kernel is very easy";

void tasklet1_function(unsigned long data)
{
	pr_info("TASKLET_SOFTIRQ start\n");
	pr_info("TASKLET_SOFTIRQ end\n");
	return;
}

void tasklet2_function(unsigned long data)
{
	pr_info("HI_SOFTIRQ start\n");
	pr_info("HI_SOFTIRQ end\n");
	return;
}

DECLARE_TASKLET(my_tasklet1, tasklet1_function, (unsigned long)&tasklet_data);
DECLARE_TASKLET(my_tasklet2, tasklet2_function, (unsigned long)&tasklet_data);

static int test_tasklet_init(void)
{
        pr_info("%s: In init\n", __func__);
	tasklet_schedule(&my_tasklet1);	
	tasklet_hi_schedule(&my_tasklet2);
	return 0;
}

static void test_tasklet_exit(void)
{
        pr_info("%s: In exit\n", __func__);
}

module_init(test_tasklet_init);
module_exit(test_tasklet_exit);
