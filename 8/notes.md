Steps performed by tasklet_schedule
------------------------------------

1. Check whether the tasklet’s state is TASKLET_STATE_SCHED.
	If it is, the tasklet is already scheduled to run and the function can immediately return.

2. Call __tasklet_schedule()

3. Save the state of the interrupt system, and then disable local interrupts by calling local_irq_save
	This ensures that nothing on this processor will mess with the tasklet code while tasklet_schedule() is manipulating the tasklets

4. Add the tasklet to be scheduled to the head of the tasklet_vec or tasklet_hi_vec linked list, which is unique to each processor in the system
	 
5. Raise the TASKLET_SOFTIRQ or HI_SOFTIRQ softirq, so do_softirq() executes this tasklet in the near future

6. Restore interrupts to their previous state and return



static void __tasklet_schedule_common(struct tasklet_struct *t,
                                      struct tasklet_head __percpu *headp,
                                      unsigned int softirq_nr)
{
        struct tasklet_head *head;
        unsigned long flags;

        local_irq_save(flags);
        head = this_cpu_ptr(headp);
        t->next = NULL;
        *head->tail = t;
        head->tail = &(t->next);
        raise_softirq_irqoff(softirq_nr);
        local_irq_restore(flags);
}

