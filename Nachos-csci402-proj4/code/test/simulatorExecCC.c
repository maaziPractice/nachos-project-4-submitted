#include "syscall.h"

#define GlobalnoOfCC 5


int main()
{
	int i;

	for(i=0;i<GlobalnoOfCC;i++)
	{
		Exec("../test/concessionClerk",23);
	}

	Exit(0);
}
