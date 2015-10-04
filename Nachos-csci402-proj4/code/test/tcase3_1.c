/*	tcase3_2

	Positive Test Case

	Checking Correct Working of Executing of Waiting Thread (user program) & Signalling Thread (user program).
	Checking Correct Working of Setting value of MV by one user program & Getting value by another user program.

	Waiting User Program.

*/

void main()
{  
	int cntLocal=0;

	CreateLock("lock1");
/*	Print("\n tcase3_1: Lock 1 Has Been Created. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase3_1: cv1 Has Been Created. \n",1,1,1); */

	CreateMV("cnt",1);
/*	Print("\n tcase3_1: MV cnt Has Been Created. \n",1,1,1); */

	Acquire("lock1");
	Print("\n tcase3_1: lock1 Has Been Acquired (By Waiter). \n",1,1,1);
	
	cntLocal = GetMV("cnt",0);
	Print("\n tcase3_1: Value for mv1 Returned By Get: '%d'. \n",cntLocal,1,1);

	SetMV("cnt",0,5);
	Print("\n tcase3_1: MV Value for cnt Has Been Set To 5. \n",1,1,1);

	Print("\n tcase3_1: Calling Wait (By waiter) on cv1 For lock1. Now run the 'tcase3_2' file.\n",1,1,1);
	Wait("cv1","lock1");

	Print("\n tcase3_1: Waiter Came out of Wait\n",1,1,1);

	Release("lock1");
	Print("\n tcase3_1: lock1 Has Been Released (By waiter). \n",1,1,1);

/*	Print("\n tcase3_1: Requesting to Delete 'cv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteCV("cv1");

	Print("\n tcase3_1: Requesting to Delete 'lock1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock1");

	Print("\n tcase3_1: Requesting to Delete 'mv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteMV("mv1");
*/
	Exit(0);
}
