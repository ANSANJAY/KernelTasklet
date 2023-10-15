Can i sleep in tasklet handler?
--------------------------------

As tasklets are based on softirqs, you cannot sleep.

You cannot use semaphores or other blocking functions in tasklet handler
