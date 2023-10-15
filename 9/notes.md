Steps performed by tasklet softirq handlers
--------------------------------------------

Handlers: tasklet_action()/tasklet_hi_action()

1. Disable local interrupt delivery and get the tasklet_vec or tasklet_hi_vec list for this processor

2. Clear the list for this processor by setting it equal to NULL.

3. Enable local interrupt delivery.

        struct tasklet_struct *list;

        local_irq_disable();
        list = tl_head->head;
        tl_head->head = NULL;
        tl_head->tail = &tl_head->head;
        local_irq_enable();

4. Loop over each pending tasklet in the retrieved list.

5. Check for a zero count value, to ensure the tasklet is not disabled. If the tasklet is disabled, skip it and go to the next pending tasklet.

6. Run the tasklet handler.

7. Repeat the next pending tasklet, until there are no more scheduled tasklets waiting to run.

        while (list) {
                struct tasklet_struct *t = list;

                list = list->next;

                if (tasklet_trylock(t)) {
                        if (!atomic_read(&t->count)) {
                                if (!test_and_clear_bit(TASKLET_STATE_SCHED,
                                                        &t->state))
                                        BUG();
                                t->func(t->data);
                                tasklet_unlock(t);
                                continue;
                        }
                        tasklet_unlock(t);
                }

                local_irq_disable();
                t->next = NULL;
                *tl_head->tail = t;
                tl_head->tail = &t->next;
                __raise_softirq_irqoff(softirq_nr);
                local_irq_enable();
        }

