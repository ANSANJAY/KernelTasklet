tasklet_kill
----------------

void tasklet_kill(struct tasklet_struct *t);

The function removes a tasklet from the pending queue.

void tasklet_kill(struct tasklet_struct *t)
{
        if (in_interrupt())
                pr_notice("Attempt to kill tasklet from interrupt\n");

        while (test_and_set_bit(TASKLET_STATE_SCHED, &t->state)) {
                do {
                        yield();
                } while (test_bit(TASKLET_STATE_SCHED, &t->state));
        }
        tasklet_unlock_wait(t);
        clear_bit(TASKLET_STATE_SCHED, &t->state);
}

This function must not be used from interrupt context because it sleeps

If the tasklet specified is already scheduled by the time this call is invoked, then this function waits until its execution completes
