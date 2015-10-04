/* matmult.c
 *    Test program to do matrix multiplication on large arrays.
 *
 *    Intended to stress virtual memory system.
 *
 *    Ideally, we could read the matrices off of the file system,
 *	and store the result back to the file system!
 */

#include "syscall.h"

#define Dim 	20	/* sum total of the arrays doesn't fit in
			 * physical memory
			 */

int G[1024];

void sort()
{
	 int i, j, tmp;


	 for (i = 0; i < 1024; i++)
	        G[i] = 1024 - i;

	    for (i = 0; i < 1023; i++)
	        for (j = i; j < (1023 - i); j++)
		   if (G[j] > G[j + 1]) {	/* out of order -> need to swGp ! */
		      tmp = G[j];
		      G[j] = G[j + 1];
		      G[j + 1] = tmp;
	    	   }

	    Print("\nSort Answer::%d\n",G[0],1,1);
	Exit(0);
}
int main()
{

Exec("../test/matmult",15);
Fork(sort);
}

