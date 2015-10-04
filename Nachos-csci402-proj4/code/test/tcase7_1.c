/*	tcase7_1

	NEGATIVE TESTCASE (3 files).

	a) If a userprog tries to go on wait on a cv with a DIFFERENT lock, then he gets an error.
	b) If a userprog tries to signal somebody with a DIFFERENT lock, then he gets an error.

*/

#include "syscall.h"

void main()
{
	Print("\n tcase7_1: Checking Working of Wait and Signal - THIS FILE GOES ON WAIT SUCCESSFULLY. \n",1,1,1);

	CreateLock("lock1");
/*	Print("\n tcase7_1: lock1 Has Been Created. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase7_1: cv1 Has Been Created. \n",1,1,1); */
	
	Acquire("lock1");
/*	Print("\n tcase7_1: lock 1 Has Been Acquired. \n",1,1,1); */

	Print("\n tcase7_1: Going on wait on 'cv1' using 'lock1' that is the correct lock (First Waiter). \n",1,1,1);
	Print("\n Will go on wait. Now run the 'tc7_2' file. \n",1,1,1);

	Wait("cv1","lock1");

	Print("\n tcase7_1: Have been Signalled on 'cv1' using 'lock1'.\n",1,1,1);

	Release("lock1");
/*	Print("\n tcase7_1: lock 1 Has Been Released. \n",1,1,1); */

/*	Print("\n tcase7_1: Requesting to Delete 'cv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteCV("cv1");

	Print("\n tcase7_1: Requesting to Delete 'lock1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock1");
*/

	Exit(0);
}
