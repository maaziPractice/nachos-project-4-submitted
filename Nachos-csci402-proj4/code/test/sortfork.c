/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */

#include "syscall.h"

int A[1024];	/* size of physical memory; with code, we'll run out of space!*/
int B[1024];

void add()
{
	 int i, j, tmp;


	for (i = 0; i < 1024; i++)
	        A[i] = 1024 - i;

	    for (i = 0; i < 1023; i++)
	        for (j = i; j < (1023 - i); j++)
		   if (A[j] > A[j + 1]) {	/* out of order -> need to swap ! */
		      tmp = A[j];
		      A[j] = A[j + 1];
		      A[j + 1] = tmp;
	    	   }

	    Print("\nSort Answer-1 ::%d\n",A[0],1,1);
	Exit(0);
}

void add1()
{
	 int i, j, tmp;


	 for (i = 0; i < 1024; i++)
	        B[i] = 1024 - i;


	    for (i = 0; i < 1023; i++)
	        for (j = i; j < (1023 - i); j++)
		   if (B[j] > B[j + 1]) {	/* out of order -> need to swBp ! */
		      tmp = B[j];
		      B[j] = B[j + 1];
		      B[j + 1] = tmp;
	    	   }

	    Print("\nSort Answer-2 ::%d\n",B[0],1,1);
	Exit(0);
}

int 
main()
{
    int i, j, tmp;

    Fork(add); 
    Fork(add1);
   
}
