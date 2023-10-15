tasklet_hi_schedule
------------------------

In addition to normal tasklets, the kernel uses a second kind of tasklet of a higher priority.

HI_SOFTIRQ is used as a softIRQ instead of TASKLET_SOFTIRQ

tasklet_hi_schedule() should be used if the tasklet should  run more urgently than networking, SCSI, timers 
