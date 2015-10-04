/*	tcase7_3.c

	NEGATIVE TESTCASE (3 files).

	a) If a userprog tries to go on wait on a cv with a DIFFERENT lock, then he gets an error.
	b) If a userprog tries to signal somebody with a DIFFERENT lock, then he gets an error.
	c) If a userprog tries to broadcast somebody with a DIFFERENT lock, then he gets an error.

	THIS FILE BROADCASTS ON THAT CV, FIRST WITH THE INCORRECT LOCK, THEN SIGNALS ON THAT CV, WITH THE INCORRECT LOCK AND THEN AGAIN WITH THE CORRECT LOCK.
*/

#include "syscall.h"

void main()
{
	Print("\n tcase7_3: THIS FILE BROADCASTS ON THAT CV, FIRST WITH THE INCORRECT LOCK, THEN SIGNALS ON THAT CV, WITH THE INCORRECT LOCK AND THEN AGAIN WITH THE CORRECT LOCK. \n",1,1,1);

	CreateLock("lock1");
/*	Print("\n tcase7_3: lock1 Has Been Created. \n",1,1,1); */

	CreateLock("lock2");
/*	Print("\n tcase7_3: lock2 Has Been Created. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase7_3: cv1 Has Been Created. \n",1,1,1); */
	
	Acquire("lock2");
/*	Print("\n tcase7_3: lock 2 Has Been Acquired. \n",1,1,1); */
	
	Print("\n tcase7_3: Broadcasting on 'cv1' using 'lock2' that is the INCORRECT lock. Will not Broadcast.\n",1,1,1);
	Broadcast("cv1","lock2");
	Print("\n ERROR - tcase7_3: Could not Broadcast on 'cv1' using 'lock2'.\n",1,1,1);

	Print("\n tcase7_3: Signalling on 'cv1' using 'lock2' that is the INCORRECT lock. Will not Signal.\n",1,1,1);
	Signal("cv1","lock2");
	Print("\n ERROR - tcase7_3: Could not Signal on 'cv1' using 'lock2'.\n",1,1,1);

	Release("lock2");
/*	Print("\n tcase7_3: lock 2 Has Been Released. \n",1,1,1); */

	Acquire("lock1");
/*	Print("\n tcase7_3: lock 1 Has Been Acquired. \n",1,1,1); */

	Print("\n tcase7_3: Signalling on 'cv1' using 'lock1' that is the CORRECT lock.\n",1,1,1);
	Signal("cv1","lock1");
	Print("\n tcase7_3: Signalled  on 'cv1' using 'lock1'.\n",1,1,1);

	Release("lock1");
/*	Print("\n tcase7_3: lock 1 Has Been Released. \n",1,1,1); */


/*	Print("\n tcase7_3: Requesting to Delete 'cv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteCV("cv1");

	Print("\n tcase7_3: Requesting to Delete 'lock1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock1");

	Print("\n tcase7_3: Requesting to Delete 'lock2', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock2");
*/

	Exit(0);
}
