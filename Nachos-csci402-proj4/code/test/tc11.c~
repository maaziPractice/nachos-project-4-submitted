/*
Negative working of Create, Set & Get MV.
*/

#include "syscall.h"

void main()
{
	int lck1, lck2,cv1,cv2, mv1, setMvValue=-1, getMvValue =-1, arrayIndex=1;

	Print("\n TC11:: Checking Negative Working of Create, Set & Get MV. \n\0",1,1,1);

	lck1 = CreateLock("lock1", 5);

	Acquire(lck1);

	cv1 = CreateCV("cv1", 3);

/*	mv1 = CreateMV("mv1", 3, 1);			Print("\n TC1:: MV name 'mv1' having Index '%d', of Array Size 1 Created. \n\0",mv1,1,1);
*/
	setMvValue = SetMV("mv1", 3, 1, 5);		Print("\n TC11:: MV Value: %d, Has Been Set for mv1. \n\0",setMvValue,1,1);

	getMvValue = GetMV("mv1", 3, 1);		Print("\n TC11:: GetMV gets: %d, for mv1. \n\0",getMvValue,1,1);

	Release(lck1);

	Print("\n TC11:: Reached end. value returned is %d\n\0",lck1,1,1);
	Exit(0);
}
