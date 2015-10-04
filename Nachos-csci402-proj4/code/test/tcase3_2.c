/*	tcase3_3

	Signalling User Program.

*/

void main()
{	
	int cntLocal=0;

	Print("\n tcase3_3: In Signaller. \n",1,1,1);

	CreateLock("lock1");
/*	Print("\n tcase3_2: Lock 1 Has Been Created. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase3_2: cv1 Has Been Created. \n",1,1,1); */

	CreateMV("cnt",1);
/*	Print("\n tcase3_2: MV cnt Has Been Created. \n",1,1,1); */

	Acquire("lock1");
/*	Print("\n tcase3_2: lock1 Has Been Acquired (By signaller). \n",1,1,1); */

	cntLocal = GetMV("cnt",0);
	Print("\n tcase3_2: Value for mv1 Returned By Get: '%d'. \n",cntLocal,1,1);

	Print("\n tcase3_2: Calling Signal (By signaller) For cv1 For lock1. \n",1,1,1);
	Signal("cv1","lock1");

	Release("lock1");
/*	Print("\n tcase3_2: lock1 Has Been Released (By signaller). \n",1,1,1); */

/*	Print("\n tcase3_2: Requesting to Delete 'cv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteCV("cv1");

	Print("\n tcase3_2: Requesting to Delete 'lock1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock1");

	Print("\n tcase3_2: Requesting to Delete 'mv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteMV("mv1");
*/
	Exit(0);
}
