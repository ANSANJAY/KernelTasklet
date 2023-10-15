Enabling/Disabling Tasklets
------------------------------

Disable tasklet
	tasklet_disable()
	tasklet_disable_nosync()

Enable tasklet
	tasklet_enable()

tasklet_disable() will wait if the tasklet is currently running and return only after it has finished execution
tasklet_disable_nosync() will not wait for the tasklet to complete prior to returning

static inline void tasklet_disable_nosync(struct tasklet_struct *t)
{
        atomic_inc(&t->count);
        smp_mb__after_atomic();
}

static inline void tasklet_disable(struct tasklet_struct *t)
{
        tasklet_disable_nosync(t);
        tasklet_unlock_wait(t);
        smp_mb();
}

static inline void tasklet_enable(struct tasklet_struct *t)
{
        smp_mb__before_atomic();
        atomic_dec(&t->count);
}


