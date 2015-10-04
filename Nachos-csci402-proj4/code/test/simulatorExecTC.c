#include "syscall.h"

#define GlobalnoOfTC 5

int main()
{
	int i;

	for(i=0;i<GlobalnoOfTC;i++)
	{
		Exec("../test/ticketClerk",19);
	}

	Exit(0);
}
