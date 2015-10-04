
/*	tcase8_2.c

	POSITIVE TESTCASE

	Multiple creation of same MV by diff userprog's of same ArraySize.
*/

#include "syscall.h"

void main()
{
	int getMvValue=0;
	
	Print("\n tcase8_2: Multiple creation of same Montior Variables of same arraysize by diff userprog's. \n\0",1,1,1);

	CreateLock("lock1");
/*	Print("\n tcase8_2: lock1 Has Been Created. \n",1,1,1); */

	Acquire("lock1");
/*	Print("\n tcase8_2: lock 1 Has Been Acquired. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase8_2: cv1 Has Been Created. \n",1,1,1); */

	Print("\n tcase8_2: Requesting to create 'mv1' of Array Size 1. \n",1,1,1);
	CreateMV("mv1", 1);

	getMvValue = GetMV("mv1", 0);
	Print("\n tcase8_2: GetMV gets: '%d' for 'mv1', Array Index '0'. \n\0",getMvValue,1,1);

	Print("\n tcase8_2: Requesting to create 'mv1' of Array Size 2. \n",1,1,1);
	CreateMV("mv1", 2);
	Print("\n ERROR - tcase8_2: Cannot create 'mv1' of Array Size 2. \n",1,1,1);

	Print("\n tcase8_2: Going on Signal on 'cv1' using 'lock1'. \n",1,1,1);
	Signal("cv1","lock1");
	Print("\n tcase8_2: Signalled on 'cv1' using 'lock1'.\n",1,1,1);

	Release("lock1");
/*	Print("\n tcase8_2: lock 1 Has Been Released. \n",1,1,1); */

/*	Print("\n tcase8_2: Requesting to Delete 'cv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteCV("cv1");

	Print("\n tcase8_2: Requesting to Delete 'lock1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock1");

	Print("\n tcase8_2: Requesting to Delete 'mv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteMV(mv1);
*/

	Exit(0);
}
