/*
Broadcast signals all the waiting members on that cv. (can be 4 clients on wait, 1 signaller)
*/

#include "syscall.h"

void main()
{
	int lck1,cv1,lck2;
	
	Print("\nTC7_2 :: Checking Working of Wait and Signal. \n",1,1,1);

	lck1 = CreateLock("lock1", 5);			
	Print("\nTC7_2 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);

	cv1 = CreateCV("cv1", 3);				
	Print("\nTC7_2 :: CV name 'cv1' Created. The Index is '%d'.\n",cv1,1,1);
	
	Acquire(lck1);							

	Print("\nTC7_2 :: Broadcasting on 'cv1' using 'lock1'. \n",1,1,1);
	Broadcast(cv1,lck1);
	Print("\nTC7_2 :: Broadcasted  on 'cv1' using 'lock1'. \n",1,1,1);

	Release(lck1);							

	DeleteCV(cv1);						

	DeleteLock(lck1);

	Print("\nTC7_2 :: Reached end.\n",lck1,1,1);
	Exit(0);
}
