/*
a) If a userprog tries to go on wait on a cv with a different lock, then he gets an error.
b) If a userprog tries to signal somebody with a different lock, then he gets an error.
*/

#include "syscall.h"

void main()
{
	int lck1,cv1,lck2;
	
	Print("\nTC6_3 :: Checking Working of Wait and Signal. \n",1,1,1);

	lck1 = CreateLock("lock1", 5);			
	Print("\nTC6_3 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);

	lck2 = CreateLock("lock2", 5);			
	Print("\nTC6_3 :: Lock name 'lock2' Created. The Index is '%d'.\n",lck1,1,1);

	cv1 = CreateCV("cv1", 3);				
	Print("\nTC6_3 :: CV name 'cv1' Created. The Index is '%d'.\n",cv1,1,1);
	
	Acquire(lck2);
	
	Print("\nTC6_3 :: Broadcasting on 'cv1' using 'lock2' that is the INCORRECT lock. Will not Broadcast.\n",1,1,1);
	Broadcast(cv1,lck2);
	Print("\nERROR - TC6_3 :: Could not Broadcast on 'cv1' using 'lock2'.\n",1,1,1);

	Release(lck2);

	Acquire(lck1);							

	Print("\nTC6_3 :: Broadcasting on 'cv1' using 'lock1' that is the CORRECT lock.\n",1,1,1);
	Broadcast(cv1,lck1);
	Print("\nTC6_3 :: Broadcasted  on 'cv1' using 'lock1'.\n",1,1,1);

	Release(lck1);							

	DeleteCV(cv1);						

	DeleteLock(lck1);
	DeleteLock(lck2);

	Print("\nTC6_3 :: Reached end.\n",lck1,1,1);
	Exit(0);
}
