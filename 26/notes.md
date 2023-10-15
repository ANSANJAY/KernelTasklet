Softirqs vs tasklets
----------------------
			Softirqs			Tasklets	
		
Allocation:		Allocated at compile time	Can be dynamically registered

Reentrancy:		Yes, same softirqs can run	No, Same tasklet will not be scheduled
			on different processors		on different processors



	
