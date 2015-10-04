/*	tcase2

	Negative Test Case.
	
	Checking Wrong Working of Acquiring, Releasing & Destroying a Lock.
	Checking Wrong Working of Destroying CV & MV.
*/

#include "syscall.h"

void main()
{
	Print("\n tcase2: Checking Wrong Working of Acquiring, Releasing & Destroying a Lock. \n",1,1,1);
	Print("\n tcase2: Checking Wrong Working of Destroying a CV. \n",1,1,1);

	CreateLock("lock1");
	Print("\n tcase2: Lock 1 Has Been Created. \n",1,1,1);

	Acquire("lock1");
	Print("\n tcase2: Lock 1 Has Been Acquired. \n",1,1,1);

	Acquire("lock1");
	Print("\n tcase2: Lock 1 Not Been Acquired As It Is Already Acquired. \n",1,1,1);

	Acquire("lock2");
	Print("\n tcase2: lock2 Not Been Acquired As Lock Is Not Created. \n",1,1,1);

	Release("lock2");
	Print("\n tcase2: lock2 Not Been Released As Lock Is Not Created. \n",1,1,1);

	Release("lock1");
/*	Print("\n tcase2: Lock 1 Has Been Released. \n",1,1,1); */

/*	DeleteLock("lock2");
	Print("\n tcase2: lock2 Not Been Deleted As Lock Is Not Created. \n",1,1,1);

	DeleteCV("cv1");
	Print("\n tcase2: cv1 Not Been Deleted As cv1 Is Not Created. \n",1,1,1);

	DeleteMV("mv1");
	Print("\n tcase2: mv1 Not Been Deleted As mv1 Is Not Created. \n",1,1,1);
*/

	Exit(0);
}
