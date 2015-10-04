/* tcase4_2

	POSITIVE TESTCASE

	a) Broadcast signals all the waiting members on that cv. (can be 4 clients on wait, 1 signaller).
	b) If 4 user programs create the same lock, and on exit everybody does a delete lock, but that lock is deleted only when after the last userprog deletes it.
	c) If 4 user programs create the same cv, and on exit everybody does a delete cv, but that cv is not deleted until the last userprog deletes it.

	Waiter Thread.

*/

#include "syscall.h"

void main()
{
	CreateLock("lock1");
/*	Print("\n tcase4_1: lock1 Has Been Created. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase4_1: cv1 Has Been Created. \n",1,1,1); */
	
	Acquire("lock1");
/*	Print("\n tcase4_1: lock 1 Has Been Acquired. \n",1,1,1); */

	Print("\n tcase4_1: Going on wait on 'cv1' using 'lock1'. Run the same 'tcase4_1' file multiple times (in different nachos instances).",1,1,1);
	Print(" Then run the 'tcase4_2' file. \n",1,1,1);
	Wait("cv1","lock1");

	Print("\n tcase4_1: Have been Signalled on 'cv1' using 'lock1'.\n",1,1,1);

	Release("lock1");
/*	Print("\n tcase4_1: lock 1 Has Been Released. \n",1,1,1); */

/*	Print("\n tcase4_1: Requesting to Delete 'cv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteCV("cv1");

	Print("\n tcase4_1: Requesting to Delete 'lock1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock1");
*/

	Exit(0);
}
