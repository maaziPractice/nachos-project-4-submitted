/*	testCase_6
	+tive Test Case
	Checking Correct Working of Forking of Waiting Thread & Signalling Thread.
	Waiter Goes to wait unconditionally, but it signals Signaller before going to sleep since Signaller MAY have gone to Sleep
	So in some context switching, signal can be wasted
	This test case tests working of Syscalls-Wait,Signal,DeleteCV,DeleteLock
	
*/

#include "syscall.h"

int lck1=1;
int cv1=1, cv2=2;
int cnt=1;
int lck2;

void waiter()
{  

	Print("\nIn Waiter\n\0",1,1,1);
	Acquire(lck1);						Print("\n lck1 Has Been Acquired (By Waiter) in testCase_6. \n\0",1,1,1);
	
	cnt--;
										Print("\n Calling Signal (By waiter) For cv2 For lck1 in testCase_6. \n\0",1,1,1);
	Signal(cv2,lck1);
										Print("\n Calling Wait (By waiter) on cv1 For lck1 in testCase_6. \n\0",1,1,1);
	Wait(cv1,lck1);
   											 Print("\nWaiter Came out of Wait\n\0",1,1,1);
	Release(lck1);						Print("\n lck1 Has Been Released (By waiter) in testCase_6. \n\0",1,1,1);
	
	
	DeleteCV(cv1);							Print("\n cv1 Has Been Deleted in testCase_6. \n\0",1,1,1);
	DeleteCV(cv2);							Print("\n cv2 Has Been Deleted in testCase_6. \n\0",1,1,1);
	DeleteLock(lck1);						Print("\n lck1 Has Been Deleted in testCase_6. \n\0",1,1,1);
	/*DeleteLock(lck1);
	lck2=CreateLock("lock1", 5);*/	
	
	Exit(0);
}

void signaller()
{	Print("\nIn Signaller\n\0",1,1,1);
	Acquire(lck1);						Print("\n lck1 Has Been Acquired (By signaller) in testCase_6. \n\0",1,1,1);

	if (cnt==0)
	{									
		Print("\n Calling Signal (By signaller) For cv1 For lck1 in testCase_6. \n\0",1,1,1);
		Signal(cv1,lck1);
	}
	else
	{
										Print("\n Calling Wait  (By signaller) on cv2 For lck1 in testCase_6. \n\0",1,1,1);
		Wait(cv2,lck1);
										Print("\n Calling Signal (By signaller) For cv1 For lck1 in testCase_6. \n\0",1,1,1);
		Signal(cv1,lck1);
	}
	Release(lck1);						Print("\n lck1 Has Been Released (By signaller) in testCase_6. \n\0",1,1,1);
			

	Exit(0);
}

void main()
{
	lck1 = CreateLock("lock1", 5);			Print("\nLock lck1 Has Been Created in testCase_6. \n\0",1,1,1);

	cv1 = CreateCV("cv1", 3);				Print("\nCV cv1 Has Been Created in testCase_6. \n\0",1,1,1);
	cv2 = CreateCV("cv2", 3);				Print("\nCV cv2 Has Been Created in testCase_6. \n\0",1,1,1);

											Print("\n Forking waiter in testCase_6. \n\0",1,1,1);
	Fork(waiter);
											Print("\n Forking signaller in testCase_6. \n\0",1,1,1);
	Fork(signaller);
	
	/*Exec("../test/TestCase8",17); */

	/*DeleteCV(cv1);							Print("\n cv1 Has Been Deleted in testCase_6. \n\0",1,1,1);
	DeleteCV(cv2);							Print("\n cv2 Has Been Deleted in testCase_6. \n\0",1,1,1);

	DeleteLock(lck1);						Print("\n lck1 Has Been Deleted in testCase_6. \n\0",1,1,1);
	*/
	Exit(0);
}
