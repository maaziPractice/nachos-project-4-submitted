#include "syscall.h"

void main()
{

	int noOfSimulations;
	Print("\nEnter the number of Simulations of Movie Theater [1-2]\n",1,1,1);

	while(1)
	{	
	noOfSimulations=Scan();
	if(noOfSimulations >=1 && noOfSimulations <=2)
	{
		break;
	}
	else
	{
		Print("\nInvalid Valueof No. of Simulations. Please enter within range i.e. [1-2]\n",1,1,1);
		continue;
	}
	}


	if (noOfSimulations==1)
	{
		Exec("../test/hammer1",15);
	}
	else
	{
		Exec("../test/hammer1",15);
		Exec("../test/hammer1",15);
	}
	Exit(0);
}