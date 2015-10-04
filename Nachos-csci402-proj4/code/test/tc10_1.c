/*
Multiple creation of same MV by diff userprog's.
*/

#include "syscall.h"

void main()
{
	int lck1, lck2,cv1,cv2, mv1, setMvValue=-1, getMvValue =-1, arrayIndex=1;

	Print("\n  TC10_1 ::Multiple creation of same MV by diff userprog's. \n\0",1,1,1);

	lck1 = CreateLock("lock1", 5);

	Acquire(lck1);

	cv1 = CreateCV("cv1", 3);

	mv1 = CreateMV("mv1", 3, 1);
	Print("\n TC10_1:: MV name 'mv1' having Index '%d', of Array Size 1 Created. \n\0",mv1,1,1);

	Print("\n TC10_1:: Setting value for MV name 'mv1' at location '%d', at its Array Index '0'\n\0",mv1,1,1);
	SetMV(mv1, 0, 5);

	getMvValue = GetMV(mv1, 0);
	Print("\n TC10_1:: GetMV gets: '%d' for 'mv1', Array Index '0'. \n\0",getMvValue,1,1);

	Print("\nTC10_1 :: Going on wait on 'cv1' using 'lock1' that is acquired. Now run the 'tc10_2' file. \n",1,1,1);
	Wait(cv1,lck1);
	Print("\nTC10_1 :: Have been signalled on 'cv1' using 'lock1'.\n",1,1,1);

	Release(lck1);

	DeleteCV(cv1);

	DeleteLock(lck1);

	DeleteMV(mv1);

	Print("\n Reached end. value returned is %d\n\0",lck1,1,1);
	Exit(0);
}
