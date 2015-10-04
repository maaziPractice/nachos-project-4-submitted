/*
If an userprog acquires a lock and meanwhile another userprogram requests to acquire it, 
then he has to wait until the first program releases that lock.
*/


#include "syscall.h"

void main()
{
	int lck1,lck2,cv1;
	
	Print("\nTC2_2 :: Checking Correct Working of Creating & Deleting of Locks and CV.\n",1,1,1);

	lck1 = CreateLock("lock1", 5);			
	Print("\nTC2_2 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);
	
	lck2 = CreateLock("lock2", 5);			
	Print("\nTC2_2 :: Lock name 'lock2' Created. The Index is '%d'.\n",lck2,1,1);

	cv1 = CreateCV("cv1", 3);				
	Print("\nTC2_2 :: CV name 'cv1' Created. The Index is '%d'.\n",cv1,1,1);
	
	Acquire(lck1);				
	Print("\nTC2_2 :: Lock 'lock1' has been Acquired.\n",1,1,1);
	
	Print("\nTC2_2 :: Going to signal on 'cv1'.\n",1,1,1);
	Signal(cv1,lck1);

	Release(lck1);							
	Print("\nTC2_2 :: Lock 'lock1' has been Released.\n",1,1,1);	

	Print("\nTC2_2 :: Now trying to acquire 'lock2'. It will acquired after tc2_1 releases it. \n",1,1,1);
	Acquire(lck2);
	Print("\nTC2_2 :: Lock 'lock2' has been Acquired.\n",1,1,1);

	DeleteCV(cv1);						

	DeleteLock(lck1);						
	Release(lck2);
	Print("\nTC2_2 :: Lock 'lock2' has been Released.\n",1,1,1);

	Print("\nTC2_2 :: Reached end.\n",lck1,1,1);
	Exit(0);
}
