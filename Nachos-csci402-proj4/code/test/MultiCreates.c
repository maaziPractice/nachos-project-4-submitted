#include "syscall.h"

void main()
{

	Print("\n1-4 Processes are being EXEC of the same file so that the 'CREATE' requests of the LOCKs, CVs & MVs each of same name is encountered and created only ONCE at any server.\n",1,1,1);

	Exec("../test/MultiCreatesFile",24);
	Exec("../test/MultiCreatesFile",24);
	Exec("../test/MultiCreatesFile",24);
	Exec("../test/MultiCreatesFile",24);

	Exit(0);
	
}
