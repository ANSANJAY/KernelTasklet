#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/slab.h>

#define SHARED_IRQ 19
static int irq = SHARED_IRQ, my_dev_id, irq_counter = 0;
module_param(irq, int, S_IRUGO);

static struct tasklet_struct *my_tasklet;
static irqreturn_t my_interrupt(int irq, void *dev_id)
{
	irq_counter++;
	pr_info("In the ISR: counter = %d\n", irq_counter);
	tasklet_schedule(my_tasklet);
	return IRQ_NONE;	/* we return IRQ_NONE because we are just observing */
}

void tasklet_function(unsigned long data)
{
	pr_info("starting tasklet function\n");
	mdelay(10000);
	pr_info("ending tasklet function\n");
        return;
}


static int __init my_init(void)
{
	my_tasklet = kmalloc(sizeof(struct tasklet_struct), GFP_KERNEL);
	tasklet_init(my_tasklet, tasklet_function, NULL);

	if (request_irq
	    (irq, my_interrupt, IRQF_SHARED, "my_interrupt", &my_dev_id)) {
		pr_info("Failed to reserve irq %d\n", irq);
		return -1;
	}
	pr_info("Successfully loading ISR handler\n");
	return 0;
}

static void __exit my_exit(void)
{
	synchronize_irq(irq);
	free_irq(irq, &my_dev_id);
	tasklet_disable(my_tasklet);
	kfree(my_tasklet);
	pr_info("Successfully unloading,  irq_counter = %d\n", irq_counter);
}

MODULE_LICENSE("GPL");
module_init(my_init);
module_exit(my_exit);
