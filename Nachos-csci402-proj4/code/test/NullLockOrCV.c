/*      NullLockOrCV.c 

      This is NEGATIVE Test
    */


/* This test Case tests that User is notified if trie to access or manipulate Cvs or Locks that have not been created
    It also tests that it throws error to user if it gives file name for executable which does not exists, or gives negative length of filename or lockname or CVname

*/

#include "syscall.h"

void main()
{
        int lck1=1, lck2=2, lck3=3, lck4=4, lck5=5, lck6=6;
        int cv1=1, cv2=2, cv3=3, cv4=4, cv5=5, cv6=6;
                      
        lck4=CreateLock("lck4",4);                                                                  
        Acquire(1); /*trying to acquire null lock*/                                                                                        
        Release(2);/*trying to release null lock*/       
       
        Acquire(lck4);
        Wait(3,lck4); /*null CV*/
       Release(lck4);       
        cv2 = CreateCV("cv2", 3);                                                                                        
        Wait(cv2,4);/*trying to wait on NULL lock in Wait*/   
        DeleteCV(cv2);  
        
        Acquire(lck4);
        Signal(5,lck4);/*trying to Signal on NULL CV signal*/
        Release(lck4);           
        cv5 = CreateCV("cv5", 3);
        Signal(cv5,6);/*null lock*/
        DeleteCV(cv5);        
                                                                                        
       DeleteLock(3);       /*trying to delete null lock*/  
       DeleteCV(3);			  /*trying to delete null CV*/ 			
       
       	Acquire(lck4);
       Broadcast(3,lck4);  /*trying to Broadcast on NULL CV */
       Release(lck4);  
        cv1 = CreateCV("cv1", 3);        
       Broadcast(cv1,lck1);		/*trying to Broadcast with NULL lock */ 
       
       lck3=CreateLock("lck4",4);
       Release(lck3);   /*trying to release the lock without acquiring it*/
        Wait(cv2,lck4);   /*trying to go on wait without */
         Signal(cv2,lck4);
         Broadcast(cv2,lck4);
         
         Exec("../test/xyzm",12);/*giving filename which does not exist*/
         Exec("../test/xyzm",-12);/*giving filename which does not exist*/
         
         CreateLock("lck2",-2);
         CreateCV("cv3",-3);
        Exit(0);
}