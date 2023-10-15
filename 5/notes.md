Scheduling Tasklets
--------------------

The kernel maintains two per-CPU tasklet linked lists for queuing scheduled tasklets

kernel/softirq.c

static DEFINE_PER_CPU(struct tasklet_head, tasklet_vec);
static DEFINE_PER_CPU(struct tasklet_head, tasklet_hi_vec);

tasklet_vec : for regular tasklets, run by TASKLET_SOFTIRQ and 
tasklet_hi_vec : for high-priority tasklets, run by HI_SOFTIRQ

Both of these structures are linked lists of tasklet_struct structures.

Each tasklet_struct structure in the list represents a different tasklet.

struct tasklet_head {
        struct tasklet_struct *head;
        struct tasklet_struct **tail;
};

Tasklets are scheduled via the tasklet_schedule() and tasklet_hi_schedule()

static inline void tasklet_schedule(struct tasklet_struct *t)
{
        if (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state))
                __tasklet_schedule(t);
}

The above function checks whether the tasklet is already scheduled, if not it atomically sets the state to
TASKLET_STATE_SCHED and invokes __tasklet_schedule to add the tasklet into the pending queue.
