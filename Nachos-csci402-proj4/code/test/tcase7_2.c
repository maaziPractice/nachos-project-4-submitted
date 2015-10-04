/*	tcase7_2

	NEGATIVE TESTCASE (3 files).

	a) If a userprog tries to go on wait on a cv with a DIFFERENT lock, then he gets an error.
	b) If a userprog tries to signal somebody with a DIFFERENT lock, then he gets an error.

*/

#include "syscall.h"

void main()
{
	Print("\n tcase7_2: THIS FILE DOES NOT GO ON WAIT AS THE LOCK IS DIFFERENT. \n",1,1,1);

	CreateLock("lock2");
/*	Print("\n tcase7_2: lock2 Has Been Created. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase7_2: cv1 Has Been Created. \n",1,1,1); */
	
	Acquire("lock2");
/*	Print("\n tcase7_2: lock 2 Has Been Acquired. \n",1,1,1); */

	Print("\n tcase7_2: Going on wait on 'cv1' using 'lock2' that is not the correct lock for that CV (Not the First Waiter). \n",1,1,1);
	Print("\n Will Not go on wait. \n",1,1,1);

	Wait("cv1","lock2");

	Print("\n ERROR - tcase7_2: Could not be Signalled AS DID NOT GO ON WAIT on 'cv1' using 'lock2'.\n",1,1,1);

	Release("lock2");
/*	Print("\n tcase7_2: lock 2 Has Been Released. \n",1,1,1); */

/*	Print("\n tcase7_2: Requesting to Delete 'cv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteCV("cv1");

	Print("\n tcase7_2: Requesting to Delete 'lock2', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock2");
*/

	Print("\n tcase7_2: Reached end. Now run the 'tc7_3' file.\n",1,1,1);
	Exit(0);
}
