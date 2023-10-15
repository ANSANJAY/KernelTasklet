What happens if i call tasklet_schedule twice?
------------------------------------------------

After a tasklet is scheduled, it runs once at some time in the near future. If the same tasklet is scheduled again, before it has had a chance to run, it still runs only once


