/*
a) If an userprog creates a lock that is already created, then it gets the index of that lock instead of creating a new one.
b) If an userprog creates a cv that is already created, then it gets the index of that cv instead of creating a new one.
c) If a user goes on wait by a particular lock, then he can be woken up by another userprog on the same cv having the same lock.
*/

#include "syscall.h"

void main()
{
	int lck1,cv1;
	
	Print("\nTC1_2 :: Checking Correct Working of Creating & Deleting of Locks and CV.\n",1,1,1);

	lck1 = CreateLock("lock1", 5);			
	Print("\nTC1_2 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);
	
	cv1 = CreateCV("cv1", 3);				
	Print("\nTC1_2 :: CV name 'cv1' Created. The Index is '%d'.\n",cv1,1,1);
	
	Acquire(lck1);							
	
	Print("\nTC1_2 :: Going to signal on 'cv1'. The waiter on 'cv1' will be woken up.\n",1,1,1);
	Signal(cv1,lck1);


	Release(lck1);							

	DeleteCV(cv1);						

	DeleteLock(lck1);						

	Print("\nTC1_2 :: Reached end.\n",lck1,1,1);
	Exit(0);
}
