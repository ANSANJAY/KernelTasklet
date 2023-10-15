state field
-------------

It can be 
	a) 0
	b) TASKLET_STATE_SCHED
	c) TASKLET_STATE_RUN

TASKLET_STATE_SCHED denotes a tasklet that is scheduled to run
TASKLET_STATE_RUN denotes a tasklet that is running

TASKLET_STATE_RUN is used only on multiprocessor machines.
It is used to protect tasklets against concurrent execution on several processors.

count field
------------

used as a reference count for the tasklet
count = 0 		the tasklet is enabled and can run if marked pending
count = nonzero		the tasklet is disabled and cannot run

