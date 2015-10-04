/*
If an userprog acquires a lock and meanwhile another userprogram requests to acquire it, 
then he has to wait until the first program releases that lock.
*/


#include "syscall.h"

void main()
{
	int lck1,lck2,cv1;
	
	Print("\nTC2_1 :: Checking Correct Working of Creating & Deleting of Locks and CV.\n",1,1,1);

	lck1 = CreateLock("lock1", 5);			
	Print("\nTC2_1 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);

	lck2 = CreateLock("lock2", 5);			
	Print("\nTC2_1 :: Lock name 'lock2' Created. The Index is '%d'.\n",lck2,1,1);

	cv1 = CreateCV("cv1", 3);				
	Print("\nTC2_1 :: CV name 'cv1' Created. The Index is '%d'.\n",cv1,1,1);
	
	Acquire(lck2);	
	Print("\nTC2_1 :: Lock 'lock2' has been acquired.\n",1,1,1);
	
	Acquire(lck1);							
	Print("\nTC2_1 :: Lock 'lock1' has been acquired.\n",1,1,1);
	
	Print("\nTC2_1 :: Going on wait on 'cv1'. Now run the 'tc2_2' file.\n",1,1,1);
	Wait(cv1,lck1);

	Release(lck1);							
	Print("\nTC2_1 :: Lock 'lock1' has been Released.\n",1,1,1);

	Print("\nTC2_1 :: Releasing 'lock2'. Now tc2_2 can acquire it. \n",1,1,1);
	Release(lck2);
	Print("\nTC2_1 :: Lock 'lock2' has been Released.\n",1,1,1);
	
	DeleteCV(cv1);						

	DeleteLock(lck1);						

	Print("\nTC2_1 :: Reached end.\n",lck1,1,1);
	Exit(0);
}
