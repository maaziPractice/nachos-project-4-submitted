/*
a) If a userprog tries to go on wait on a cv with a different lock, then he gets an error.
b) If a userprog tries to signal somebody with a different lock, then he gets an error.
*/

#include "syscall.h"

void main()
{
	int lck1,cv1,lck2;
	
	Print("\nTC6_2 :: Checking Working of Wait and Signal. \n",1,1,1);

	lck2 = CreateLock("lock2", 5);			
	Print("\nTC6_2 :: Lock name 'lock2' Created. The Index is '%d'.\n",lck1,1,1);

	cv1 = CreateCV("cv1", 3);				
	Print("\nTC6_2 :: CV name 'cv1' Created. The Index is '%d'.\n",cv1,1,1);
	
	Acquire(lck2);

	Print("\nTC6_2 :: Going on wait on 'cv1' using 'lock2' that is not the correct lock for that CV (Not the First Waiter). Will Not go on wait. \n",1,1,1);
	Wait(cv1,lck2);
	Print("\nERROR- TC6_2 :: Could not be Signalled AS DID NOT GO ON WAIT on 'cv1' using 'lock2'.\n",1,1,1);

	Release(lck2);

	DeleteCV(cv1);						

	DeleteLock(lck2);

	Print("\nTC6_2 :: Reached end. Now run the 'tc6_3' file.\n",lck1,1,1);
	Exit(0);
}
