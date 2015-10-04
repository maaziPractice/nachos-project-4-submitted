/*
a) If a userprog tries to go on wait on a cv with a different lock, then he gets an error.
b) If a userprog tries to signal somebody with a different lock, then he gets an error.
*/

#include "syscall.h"

void main()
{
	int lck1,cv1,lck2;
	
	Print("\nTC6_1 :: Checking Working of Wait and Signal. \n",1,1,1);

	lck1 = CreateLock("lock1", 5);			
	Print("\nTC6_1 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);

	cv1 = CreateCV("cv1", 3);				
	Print("\nTC6_1 :: CV name 'cv1' Created. The Index is '%d'.\n",cv1,1,1);
	
	Acquire(lck1);												

	Print("\nTC6_1 :: Going on wait on 'cv1' using 'lock1' that is the correct lock (First Waiter). Will go on wait. Now run the 'tc6_2' file. \n",1,1,1);
	Wait(cv1,lck1);
	Print("\nTC6_1 :: Have been Signalled on 'cv1' using 'lock2'.\n",1,1,1);

	Release(lck1);							

	DeleteCV(cv1);						

	DeleteLock(lck1);						

	Print("\nTC6_1 :: Reached end.\n",lck1,1,1);
	Exit(0);
}
