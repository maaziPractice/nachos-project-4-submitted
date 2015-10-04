/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */

#include "syscall.h"

int A[10];	/* size of physical memory; with code, we'll run out of space!*/

void add()
{
   int abc[50];
   
	Write("\n\nSort 1: Add Function\n\n",24,ConsoleOutput);
	Exec("../test/matmult",15);
	Exit(0);
}


int 
main()
{
    int i, j, tmp;
    
    Fork(add); 
   Write("\n\nSort: Your Exec is running\n\n",30,ConsoleOutput);
   
    /* first initialize the array, in reverse sorted order 
    for (i = 0; i < 1024; i++)		
        A[i] = 1024 - i;

     then sort! 
    for (i = 0; i < 1023; i++)
        for (j = i; j < (1023 - i); j++)
	   if (A[j] > A[j + 1]) {	/* out of order -> need to swap ! 
	      tmp = A[j];
	      A[j] = A[j + 1];
	      A[j + 1] = tmp;
    	   }
    Exit(A[0]);		 and then we're done -- should be 0! */
}
