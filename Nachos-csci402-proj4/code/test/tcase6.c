/*	tcase6

	NEGATIVE TESTCASE

	a) If an userprog tries to go on wait by a lock of which he is not the owner then he gets an error.
	b) If an userprog tries to signal by a lock of which he is not the owner then he gets an error.
	c) If an userprog tries to go on wait where cv is not created then he gets an error.
	d) If an userprog tries to signal on a cv where its not created then he gets an error.

*/

#include "syscall.h"

void main()
{
	Print("\n tcase6: Checking Working of Wait and Signal. \n",1,1,1);

	CreateLock("lock1");
/*	Print("\n tcase6: lock1 Has Been Created. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase6: cv1 Has Been Created. \n",1,1,1); */

	Print("\n tcase6: Going on wait on 'cv1' using 'lock1' that is not acquired. Will not go on wait.\n",1,1,1);
	Wait("cv1","lock1");
	Print("\nERROR - tcase6: Could not go on wait on 'cv1' using 'lock1'.\n",1,1,1);

	Print("\n tcase6: Signalling on 'cv1' using 'lock1' that is not acquired. Will not Signal.\n",1,1,1);
	Signal("cv1","lock1");
	Print("\nERROR - tcase6: Could not Signal on 'cv1' using 'lock1'.\n",1,1,1);


	Acquire("lock1");
/*	Print("\n tcase6: lock 1 Has Been Acquired. \n",1,1,1); */

	Print("\n tcase6: Going on wait on 'cv2' that is not created using 'lock1'. Will not go on wait.\n",1,1,1);
	Wait("cv2","lock1");
	Print("\n ERROR - tcase6: Could not go on wait on 'cv1' using 'lock2'.\n",1,1,1);

	Print("\n tcase6: Signalling on 'cv2' that is not created using 'lock1'. Will not Signal.\n",1,1,1);
	Signal("cv2","lock1");
	Print("\nERROR - tcase6: Could not Signal on 'cv1' using 'lock1'.\n",1,1,1);

	Release("lock1");
/*	Print("\n tcase6: lock 1 Has Been Released. \n",1,1,1); */

/*	DeleteCV("cv1");
	Print("\n tcase6: cv1 Has Been Deleted. \n",1,1,1);

	DeleteLock("lock1");
	Print("\n tcase6: Lock 1 Deleted. \n",1,1,1);

	DeleteLock("lock2");
	Print("\n tcase6: Lock 2 Deleted. \n",1,1,1);
*/

	Exit(0);
}
