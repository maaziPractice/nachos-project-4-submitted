
/*	tcase8_1.c

	POSITIVE TESTCASE

	Multiple creation of same MV by diff userprog's of same ArraySize.
*/

#include "syscall.h"

void main()
{
	int getMvValue=0;
	
	Print("\n tcase8_1: Multiple creation and deletion of same Montior Variables of same arraysize by diff userprog's. \n",1,1,1);

	CreateLock("lock1");
/*	Print("\n tcase8_1: lock1 Has Been Created. \n",1,1,1); */

	Acquire("lock1");
/*	Print("\n tcase8_1: lock 1 Has Been Acquired. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase8_1: cv1 Has Been Created. \n",1,1,1); */

	CreateMV("mv1", 1);
	Print("\n tcase8_1: 'mv1' of Array Size 1 Created. \n",1,1,1);

	Print("\n tcase8_1: Setting value '5' for MV name 'mv1' at Array Index '0'. \n",1,1,1);
	SetMV("mv1", 0, 5);

	getMvValue = GetMV("mv1", 0);
	Print("\n tcase8_1: GetMV gets: '%d' for 'mv1', Array Index '0'. \n\0",getMvValue,1,1);

	Print("\n tcase8_1: Going on wait on 'cv1' using 'lock1' that is acquired. Now run the 'tc8_2' file. \n",1,1,1);
	Wait("cv1","lock1");
	Print("\n tcase8_1: Have been signalled on 'cv1' using 'lock1'.\n",1,1,1);

	Release("lock1");
/*	Print("\n tcase8_1: lock 1 Has Been Released. \n",1,1,1); */
	
/*	Print("\n tcase8_1: Requesting to Delete 'cv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteCV("cv1");

	Print("\n tcase8_1: Requesting to Delete 'lock1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock1");

	Print("\n tcase8_1: Requesting to Delete 'mv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteMV(mv1);
*/

	Exit(0);
}
