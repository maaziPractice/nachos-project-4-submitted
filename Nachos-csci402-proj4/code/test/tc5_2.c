/*
a) If an userprog tries to goes on wait on a cv where its not created then he gets  an error.
b) If an userprog tries to signal somebody on the cv which is not created then he gets an error.
*/

#include "syscall.h"

void main()
{
	int lck1,cv1=-1,lck2;
	
	Print("\nTC5_2 :: Checking Working of Wait and Signal. \n",1,1,1);

	lck1 = CreateLock("lock1", 5);			
	Print("\nTC5_2 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);

	Acquire(lck1);							
	
	Print("\nTC5_2 :: Signalling on 'cv1' that is not created using 'lock1'. Will not Signal.\n",1,1,1);
	Signal(cv1,lck1);
	Print("\nERROR - TC5_2 :: Could not Signal on 'cv1' using 'lock1'.\n",1,1,1);

	cv1 = CreateCV("cv1", 3);				
	Print("\nTC5_2 :: CV name 'cv1' Created. The Index is '%d'.\n",cv1,1,1);
	
	Print("\nTC5_2 :: Signalling on 'cv1' that is now created using 'lock1'. \n",1,1,1);
	Signal(cv1,lck1);
	Print("\nTC5_2 :: Signalled on 'cv1' using 'lock1'.\n",1,1,1);

	Release(lck1);							

	DeleteCV(cv1);						

	DeleteLock(lck1);						
	
	Print("\nTC5_2 :: Reached end.\n",lck1,1,1);
	Exit(0);
}
