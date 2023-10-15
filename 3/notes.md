Declaring Tasklets
===================

Static Initialization
----------------------

DECLARE_TASKLET

	#define DECLARE_TASKLET(name, func, data) \
	struct tasklet_struct name = { NULL, 0, ATOMIC_INIT(0), func, data }

DECLARE_TASKLET_DISABLED

	#define DECLARE_TASKLET_DISABLED(name, func, data) \
	struct tasklet_struct name = { NULL, 0, ATOMIC_INIT(1), func, data }

Both these macros statically create a struct tasklet_struct with the given name.
When the tasklet is scheduled, the given function func is executed and passed data as argument.

The difference between the two macros is the initial reference count.

Dynamic
--------

void tasklet_init(struct tasklet_struct *t,
                         void (*func)(unsigned long), unsigned long data);

