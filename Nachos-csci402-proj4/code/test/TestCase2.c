/*	testCase_2

	Checking Wrong Working of Destroying a Lock
*/



#include "syscall.h"

void main()
{
	int lck1, lck2,i,lck3;
	int cv1,cv2,cv3,cv4,cv5;


lck1 = CreateLock("lock1", 5);			/*Print("\nLock  1 Created in testCase_1.c. \n\0",1,1,1);*/
lck2 = CreateLock("lock2", 5);			Print("\n Lock  2 Created in testCase_2.c. \n\n\0",1,1,1);
cv1 = CreateCV("cv1", 3);				Print("\nCV  1 Created in testCase_2.c. \n\0",1,1,1);


	Acquire(lck1);							Print("\nLock 1 Acquired in testCase_2.c. \n\0",1,1,1);

	Broadcast(cv1,lck1);
	
	Release(lck1);							Print("\nLock 1 Released in testCase_2.c. \n\0",1,1,1);

	DeleteCV(cv1);						Print("\n CV  1 Deleted in testCase_2.c. \n\0",1,1,1);

	DeleteLock(lck1);						Print("\n Lock  1 Deleted in testCase_2.c. \n\0",1,1,1);


	Print("\n Reached end. value returned is %d\n\0",lck1,1,1);
	Exit(0);

	
}


/*
#include "syscall.h"

void main()
{
	int lck1=1, lck2=2, lck3=3;
											Print("\n Checking Wrong Working of Destroying a Lock. \n\0",1,1,1);

	lck1 = CreateLock("lock1", 5);			Print("\n lck1 Has Been Created in testCase_2. \n\0",1,1,1);
	lck2 = CreateLock("lock2", 5);			Print("\n lck2 Has Been Created in testCase_2. \n\0",1,1,1);

	Acquire(lck1);							Print("\n lck1 Has Been Acquired in testCase_2. \n\0",1,1,1);
	Acquire(lck2);							Print("\n lck2 Has Been Acquired in testCase_2. \n\0",1,1,1);

	Release(lck1);							Print("\n lck1 Has Been Released in testCase_2. \n\0",1,1,1);
	Release(lck2);							Print("\n lck2 Has Been Released in testCase_2. \n\0",1,1,1);

	DeleteLock(lck1);						Print("\n lck1 Has Been Deleted in testCase_2. \n\0",1,1,1);
	DeleteLock(lck2);						Print("\n lck2 Has Been Deleted in testCase_2. \n\0",1,1,1);

											Print("\n Error Should Print That lck3 Does Not Exist. \n\0",1,1,1);
	DeleteLock(lck3);		

	Exit(0);
}
*/