










#include "syscall.h"

int A[1024];	/* size of physical memory; with code, we'll run out of space!*/






int
main()
{
	int i, j, tmp;

		 Print("\nSort A 1\n",1,1,1);
		for (i = 0; i < 1024; i++)
		        A[i] = 1024 - i;

		Print("\nSort A 2\n",1,1,1);
		    for (i = 0; i < 1023; i++)
		        for (j = i; j < (1023 - i); j++)
			   if (A[j] > A[j + 1]) {	/* out of order -> need to swap ! */
			      tmp = A[j];
			      A[j] = A[j + 1];
			      A[j + 1] = tmp;
		    	   }

		    Print("\nSort Answer::%d\n",A[0],1,1);
		Exit(A[0]);




}
