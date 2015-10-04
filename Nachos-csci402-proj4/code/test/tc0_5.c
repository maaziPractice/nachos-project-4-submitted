/*
Testing for p4p3
*/

#include "syscall.h"

void main()
{
	int lck1;
	int i,j;
	
	Print("\nTC0_5 :: Testing for p4p3. \n",1,1,1);

	lck1 = CreateLock("lock1");			
	Print("\nTC0_5 :: Lock name 'lock1' Created. The Index is '%d'.\n",lck1,1,1);
	
	Acquire("lock1");							
	Print("\nTC0_5 :: Has acquired lock 'lock1' with index: '%d'. \n",lck1,1,1);

	Release("lock1");
	Print("\nTC0_5 :: Has released lock 'lock1' with index: '%d' & is now EXITING. \n",lck1,1,1);

/*	DeleteLock(lck1); */
	
	Exit(0);
}
