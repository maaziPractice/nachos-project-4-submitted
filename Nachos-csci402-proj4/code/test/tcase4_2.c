/*	tcase4_3

	Broadcast Thread.

*/

#include "syscall.h"

void main()
{
	CreateLock("lock1");
/*	Print("\n tcase4_2: lock1 Has Been Created. \n",1,1,1); */

	CreateCV("cv1");
/*	Print("\n tcase4_2: cv1 Has Been Created. \n",1,1,1); */
	
	Acquire("lock1");
/*	Print("\n tcase4_2: lock 1 Has Been Acquired. \n",1,1,1); */

	Print("\n tcase4_2: Broadcasting on 'cv1' using 'lock1'. \n",1,1,1);
	Broadcast("cv1","lock1");

	Print("\n tcase4_2: Broadcasted  on 'cv1' using 'lock1'. \n",1,1,1);

	Release("lock1");
/*	Print("\n tcase4_2: lock 1 Has Been Released. \n",1,1,1); */

/*	Print("\n tcase4_2: Requesting to Delete 'cv1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteCV("cv1");

	Print("\n tcase4_2: Requesting to Delete 'lock1', but will delete only if it is the last userprog deleting it.\n",1,1,1);
	DeleteLock("lock1");
*/

	Exit(0);
}
