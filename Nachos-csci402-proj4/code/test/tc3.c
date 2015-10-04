/*
a)If an userprogram tries to release the lock that has not been acquired , then he gets an 
error.
b) If an userprogram tries to acquire the lock he already owns then also he gets an error.
*/


#include "syscall.h"

void main()
{
	int lck1;
	
	Print("\nTC3 :: Checking the Working of Acquire and Release of Locks.\n",1,1,1);

	lck1 = CreateLock("lock1", 5);			
	Print("\nTC3 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);

	Release(lck1);							
	Print("\nTC3 :: Lock 'lock2' has NOT been Released as it is not Acquired.\n",1,1,1);

	Acquire(lck1);	
	Print("\nTC3 :: Lock 'lock2' has been acquired.\n",1,1,1);
	
	Acquire(lck1);							
	Print("\nTC3 :: Acquiring Lock 'lock1' again. It is an error.\n",1,1,1);
	
	Release(lck1);							
	Print("\nTC3 :: Lock 'lock1' has been Released.\n",1,1,1);

	DeleteLock(lck1);						

	Print("\nTC3 :: Reached end.\n",lck1,1,1);
	Exit(0);
}
