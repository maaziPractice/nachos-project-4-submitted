#include "syscall.h"

#define GlobalnoOfTT 3


int main()
{
	int i;

	for(i=0;i<GlobalnoOfTT;i++)
	{
		Exec("../test/ticketTaker",19);
	}

	Exit(0);
}
