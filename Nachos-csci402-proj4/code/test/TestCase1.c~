#include "syscall.h"

void main()
{
	int lck1, lck2,cv1,cv2;
											Print("\nChecking Correct Working of Acquiring & Releaseing of Locks. \n\0",1,1,1);

	lck1 = CreateLock("lock1", 5);			/*Print("\nLock  1 Created in testCase_1.c. \n\0",1,1,1);*/
	Acquire(lck1);							Print("\nLock  1 Acquired in testCase_1.c. \n\0",1,1,1);

/*	lck2 = CreateLock("lock2", 5);			Print("\n Lock  2 Created in testCase_1.c. \n\n\0",1,1,1);*/

	cv1 = CreateCV("cv1", 3);			Print("\nCV  1 Created in testCase_1.c. \n\0",1,1,1);
	/*cv2 = CreateCV("cv2", 3);			Print("\nCV  2 Created in testCase_1.c. \n\0",1,1,1);*/

	
	/*Acquire(lck2);							Print("\nLock  2 Acquired in testCase_1.c. \n\n\0",1,1,1);*/
	
	Wait(cv1,lck1);

	Release(lck1);							Print("\nLock  1 Released in testCase_1.c. \n\0",1,1,1);
/*	Release(lck2);							Print("\nLock  2 Released in testCase_1.c. \n\n\0",1,1,1);*/

	





	/*lck1 = CreateLock("lock1", 5);			*/
	DeleteCV(cv1);						Print("\n CV  1 Deleted in testCase_1.c. \n\0",1,1,1);

	DeleteLock(lck1);						Print("\n Lock  1 Deleted in testCase_1.c. \n\0",1,1,1);
/*	DeleteLock(lck2);						Print("\n Lock  2 Deleted in testCase_1.c. \n\0",1,1,1);
*/
	Print("\n Reached end. value returned is %d\n\0",lck1,1,1);
	Exit(0);

	
}
