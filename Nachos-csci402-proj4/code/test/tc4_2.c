/*
a) If an userprog tries to goes on wait by a lock of which he is not the owner then he gets an error.
b) If an userprog tries to signal somebody by a lock of which he is not the owner then he gets an error.
*/

#include "syscall.h"

void main()
{
	int lck1,cv1,lck2;
	
	Print("\nTC4_2 :: Checking Working of Wait and Signal. \n",1,1,1);

	lck1 = CreateLock("lock1", 5);			
	Print("\nTC4_2 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);

	lck2 = CreateLock("lock2", 5);			
	Print("\nTC4_2 :: Lock name 'lock2' Created. The Index is '%d'.\n",lck1,1,1);


	cv1 = CreateCV("cv1", 3);				
	Print("\nTC4_2 :: CV name 'cv1' Created. The Index is '%d'.\n",cv1,1,1);
	
	Acquire(lck1);							
	
	Print("\nTC4_2 :: Signalling on 'cv1' using 'lock2' that is not acquired. Will not Signal.\n",1,1,1);
	Signal(cv1,lck2);
	Print("\nERROR - TC4_2 :: Could not Signal on 'cv1' using 'lock2'.\n",1,1,1);

	Print("\nTC4_2 :: Signalling on 'cv1' using 'lock1' that is acquired. \n",1,1,1);
	Signal(cv1,lck1);
	Print("\nTC4_2 :: Signalled on 'cv1' using 'lock1'.\n",1,1,1);

	Release(lck1);							

	DeleteCV(cv1);						

	DeleteLock(lck1);
	DeleteLock(lck2);

	Print("\nTC4_2 :: Reached end.\n",lck1,1,1);
	Exit(0);
}
