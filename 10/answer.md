How kernel avoids running the same tasklet on multiple processors
------------------------------------------------------------------

tasklet_trylock

tasklet_unlock

static inline int tasklet_trylock(struct tasklet_struct *t)
{
        return !test_and_set_bit(TASKLET_STATE_RUN, &(t)->state);
}

static inline void tasklet_unlock(struct tasklet_struct *t)
{
        smp_mb__before_atomic();
        clear_bit(TASKLET_STATE_RUN, &(t)->state);
}

On a multiprocessor machine, the kernel checks whether TASKLET_STATE_RUN is set (which means another processor is running this tasklet).

	If set, do not execute now and skip to the next pending tasklet
	Else set the TASKLET_STATE_RUN flag so that another processor cannot execute
	After the tasklet completes, clear the TASKLET_STATE_RUN flag
