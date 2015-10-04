/*	testCase_4

	Checking Wrong Working of Releaseing of Locks
*/

#include "syscall.h"

void main()
{
	int lck1=1, lck2=2, lck3=3;
													Print("\n Checking Wrong Working of Releaseing of Locks. \n\0",1,1,1);

	lck1 = CreateLock("lock1", 5);					Print("\n lck1 Has Been Created in testCase_4. \n\0",1,1,1);
	lck2 = CreateLock("lock2", 5);					Print("\n lck2 Has Been Created in testCase_4. \n\0",1,1,1);

	Acquire(lck1);									Print("\n lck1 Has Been Acquired in testCase_4. \n\0",1,1,1);
	Acquire(lck2);									Print("\n lck2 Has Been Acquired in testCase_4. \n\0",1,1,1);

	Release(lck1);									Print("\n lck1 Has Been Released in testCase_4. \n\0",1,1,1);
	Release(lck2);									Print("\n lck2 Has Been Released in testCase_4. \n\0",1,1,1);

													Print("\n Error Should Print That lck3 Does Not Exist. \n\0",1,1,1);
	Release(lck3);							

	DeleteLock(lck1);								Print("\n lck1 Has Been Deleted in testCase_4. \n\0",1,1,1);
	DeleteLock(lck2);								Print("\n lck2 Has Been Deleted in testCase_4. \n\0",1,1,1);
	
	Exit(0);
}
