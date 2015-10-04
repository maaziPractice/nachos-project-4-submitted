/*
a) If an userprog creates a lock that is already created, then it gets the index of that lock instead of creating a new one.
b) If an userprog creates a cv that is already created, then it gets the index of that cv instead of creating a new one.
c) If a user goes on wait by a particular lock, then he can be woken up by another userprog on the same cv having the same lock.
*/

#include "syscall.h"

void main()
{
	int lck1,cv1;
	
	Print("\nTC1_1 :: Checking Correct Working of Creating & Deleting of Locks and CV.\n",1,1,1);

	lck1 = CreateLock("lock1", 5);			
	Print("\nTC1_1 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);
	
	cv1 = CreateCV("cv1", 3);				
	Print("\nTC1_1 :: CV name 'cv1' Created. The Index is '%d'.\n",cv1,1,1);
	
	Acquire(lck1);							
	
	Print("\nTC1_1 :: Going on wait on 'cv1' using 'lock1'. Now run the 'tc1_2' file.\n",1,1,1);
	Wait(cv1,lck1);
	Print("\nTC1_1 :: Have been signalled on 'cv1' using 'lock1'.\n",1,1,1);

	Release(lck1);							

	DeleteCV(cv1);						

	DeleteLock(lck1);	
	
	Print("\nTC1_1 :: Reached end.\n",lck1,1,1);
	Exit(0);
}
