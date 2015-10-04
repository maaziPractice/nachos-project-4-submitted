/*	tcase1

	Positive Test Case.
	
	Checking Correct Working of Creating, Acquiring & Releaseing of Locks.
	Checking Correct Working of Creating & Destroying CV & MV.
	Checking Correct Working of Getting & Setting value of MV.
*/

#include "syscall.h"

void main()
{
	int local=0;

	Print("\n tcase1: Checking Correct Working of Creating, Acquiring & Releaseing of Locks. \n",1,1,1);
	Print("\n tcase1: Checking Correct Working of Creating & Destroying CV & MV. \n",1,1,1);

	CreateLock("lock1");
	Print("\n tcase1: Lock 1 Has Been Created. \n",1,1,1);

	Acquire("lock1");
	Print("\n tcase1: Lock 1 Has Been Acquired. \n",1,1,1);

	Release("lock1");
	Print("\n tcase1: Lock 1 Has Been Released. \n",1,1,1);

/*	DeleteLock("lock1");
	Print("\n tcase1: Lock 1 Deleted. \n",1,1,1); */

	CreateCV("cv1");
	Print("\n tcase1: cv1 Has Been Created. \n",1,1,1);

/*	DeleteCV("cv1");
	Print("\n tcase1: cv1 Has Been Deleted. \n",1,1,1); */

	CreateMV("mv1",1);
	Print("\n tcase1: mv1 Has Been Created. \n",1,1,1);

	SetMV("mv1",0,local+1);
	Print("\n tcase1: Value for mv1 is Set To Be: '%d'. \n",local+1,1,1);

	local = GetMV("mv1",0);
	Print("\n tcase1: Value for mv1 Returned By Get: '%d'. \n",local,1,1);

/*	DeleteMV("mv1");
	Print("\n tcase1: mv1 Has Been Deleted. \n",1,1,1); */

	Exit(0);
}
