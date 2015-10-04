/*
Positive working of Create, Set & Get MV.
*/

#include "syscall.h"

void main()
{
	int lck1, lck2,cv1,cv2, mv1, setMvValue=-1, getMvValue =-1, arrayIndex=1;

	Print("\n TC9:: Checking Correct Working of Create, Set & Get MV. \n\0",1,1,1);

	lck1 = CreateLock("lock1", 5);

	Acquire(lck1);

	cv1 = CreateCV("cv1", 3);

	mv1 = CreateMV("mv1", 3, 10);			Print("\n TC9:: MV name 'mv1' having Index '%d', of Array Size 1 Created. \n\0",mv1,1,1);

	Print("\n TC9:: Setting value for MV name 'mv1' at location '%d', at its Array Index '4'\n\0",mv1,1,1);
	SetMV(mv1, 4, 50);						

	Print("\n TC10_1:: Getting value for 'mv1' at location '%d', for its Array Index '3' (Value not SET, will give the default value '0')",mv1,1,1);
	getMvValue = GetMV(mv1, 3);				
	Print("\n TC9:: GetMV gets: %d, for mv1. \n\0",getMvValue,1,1);

	Print("\n TC10_1:: Getting value for 'mv1' at location '%d', for its Array Index '4' (Value is SET)",mv1,1,1);
	getMvValue = GetMV(mv1, 4);				
	Print("\n TC9:: GetMV gets: %d, for mv1. \n\0",getMvValue,1,1);

	
	Release(lck1);

	Print("\n TC9:: Reached end. value returned is %d\n\0",lck1,1,1);
	Exit(0);
}
