#include "syscall.h"

#define GlobalnoOfGroups 7
#define GlobalGroupNormalCustSize 3

int main()
{
	int i;

	for(i=0;i<GlobalnoOfGroups;i++)
	{
		Exec("../test/customerHead",20);
	}

	for(i=0;i<GlobalnoOfGroups*GlobalGroupNormalCustSize;i++)
	{
		Exec("../test/customer",16);
	}

	Exit(0);
}
