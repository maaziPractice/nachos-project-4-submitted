/*      IllegalUser.c 

       

*/

#include "syscall.h"
#define PRINTMETOO *65536+
int myLock;

void main()
{
        Acquire(0);
        
        Release(0);
         
        Wait(0,0);

	    Signal(0,0);
        
       Broadcast(0,0);
       
       myLock=CreateLock("myLock", 6);
     /*  if(myLock==3)
        Print("\n\nmy LOck is %d \n\n",myLock,1,1); */
        
       Acquire(myLock);
       Wait(0,myLock);

		Signal(0,myLock);
        
        Broadcast(0,myLock); 
        
       DeleteLock(0);
        
       DeleteCV(0);	
        
        Exit(0);
        
}