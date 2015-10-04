/*	tcase5_1

	POSITIVE TESTCASE

	If an userprog acquires a lock and meanwhile another userprogram requests to acquire it, 
	then he has to wait until the first program releases that lock.

	There are 2 locks created acquired and released to ensure proper functionality.
*/


#include "syscall.h"

void main()
{
	Print("\n tcase5_1: Checking Correct Working of Creating & Deleting of Locks and CV.\n",1,1,1);

	CreateLock("lock1");
/*	Print("\n tcase5_1: lock1 Has Been Created. \n",1,1,1); */

	CreateLock("lock2");
/*	Print("\n tcase5_1: lock2 Has Been Created. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase5_1: cv1 Has Been Created. \n",1,1,1); */
	
	Acquire("lock2");
/*	Print("\n tcase5_1: lock 2 Has Been Acquired. \n",1,1,1); */
	
	Acquire("lock1");
/*	Print("\n tcase5_1: lock 1 Has Been Acquired. \n",1,1,1); */
	
	Print("\n tcase5_1: Going on wait on 'cv1'. Now run the 'tc2_2' file.\n",1,1,1);
	Wait("cv1","lock1");

	Print("\n tcase5_1: Have been Signalled on 'cv1' using 'lock1'.\n",1,1,1);

	Release("lock1");
/*	Print("\n tcase5_1: lock 1 Has Been Released. \n",1,1,1); */

	Print("\n tcase5_1: Releasing 'lock2'. Now tc2_2 can acquire it. \n",1,1,1);

	Release("lock2");
/*	Print("\n tcase5_1: lock 2 Has Been Released. \n",1,1,1); */
	

/*	Print("\n tcase5_1: Requesting to Delete 'cv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteCV("cv1");

	Print("\n tcase5_1: Requesting to Delete 'lock1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock1");
	
	Print("\n tcase5_1: Requesting to Delete 'lock2', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock2");
*/
	Exit(0);
}
