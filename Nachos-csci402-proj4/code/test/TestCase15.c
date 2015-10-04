/*      testCase_15

        Checking Correct Working of Broadcast SysCall 

*/

#include "syscall.h"
  
int cntlck;
int cntCVw;
int cntCVb;
int cnt=2;
/* Here waiter1 & waiter2 are 2 threads going on wait BEFORE thread broadcaster boradcasts them, all of  them have been forked by main thread*/
/* waiter go on wait on different CV, 7 broadcaster on another one*/
/* this is posititve test case for Sys calls Boradcast,Signal,wait,acquire,release*/
void waiter1()
{
                                                                                        Print("\n Waiter1 Has Been Forked,since Control Has Reached in Waiter1 function in testCase_15. \n\0",1,1,1);

        Acquire(cntlck);                               Print("\n  Lock cntlck Has Been Acquired (By waiter1) in testCase_15. \n\0",1,1,1);
        cnt--;
        if(cnt==0)
        {
                                                                                        Print("\n Calling Signal (By waiter1) on cv b For lck in testCase_15. \n\0",1,1,1);
                Signal(cntCVb,cntlck);
        }
                                                                                        Print("\n Calling Wait (By waiter1) on CV of Waiters For lck in testCase_15. \n\0",1,1,1);
        Wait(cntCVw,cntlck);
                                                                                        Print("\n Lock cntlck Has Been Released (By waiter1) in testCase_15. \n\0",1,1,1);
        Release(cntlck);
        
        Exit(0);
}

void waiter2()
{
                                                                                        Print("\n Waiter2 Has Been Forked, Control Has Reached in waiter2 function in testCase_15. \n\0",1,1,1);

        Acquire(cntlck);                               Print("\n Lock cntlck Has Been Acquired (By waiter1) in testCase_15. \n\0",1,1,1);
        cnt--;
        if(cnt==0)
        {                                                                               Print("\n Calling Signal (By waiter2) on cntCVb with cntlck in testCase_15. \n\0",1,1,1);
                Signal(cntCVb,cntlck);
        }
                                                                                        Print("\n Calling Wait (By waiter2) on cntCVw with lock cntlck in testCase_15. \n\0",1,1,1);
        Wait(cntCVw,cntlck);

        Release(cntlck);                                Print("\n Lock cntlck Has Been Released (By waiter2) in testCase_15. \n\0",1,1,1);
        
        Exit(0);
}


void broadcaster()
{       
                                                                                                                Print("\n Broacaster Has Been Forked since Control Has Reached in broadcaster function in testCase_15. \n\0",1,1,1);

        Acquire(cntlck);                                                       Print("\n Lock cntlck Has Been Acquired (By broadcaster) in testCase_15. \n\0",1,1,1);
        if (cnt==0)
        {                                                                                                       Print("\n Calling Broadcast (By broadcaster) on cntCVw with lock cntlck in testCase_15. \n\0",1,1,1);
                Broadcast(cntCVw,cntlck);
        }
        else
        {
                                                                                                                Print("\n Calling Wait (By waiter2) on cntCVb with with lock cntlck in testCase_15. \n\0",1,1,1);
                Wait(cntCVb,cntlck);
                 Print("\nGot Out of Wait BroadCaster\n",1,1,1);                                                                                         Print("\n Calling Broadcast (By broadcaster) For cntCVw with lock cntlck in testCase_15. \n\0",1,1,1);
                Broadcast(cntCVw,cntlck);
        }
        Release(cntlck);                                                        Print("\n Lock cntlck Has Been Released (By broadcaster) in testCase_15. \n\0",1,1,1);

        Exit(0);
}


void main()
{                                                                                                               Print("\n Checking Correct Working of Broadcast SysCall. \n\0",1,1,1);

        cntlck = CreateLock("Count_Lock", 10);          Print("\n A lock-cntlck Has Been Created in testCase_15. \n\0",1,1,1);

        cntCVw = CreateCV("cv1", 3);                            Print("\nCV of Waiters-cntCVw Has Been Created in testCase_15. \n\0",1,1,1);
        cntCVb = CreateCV("cv2", 3);                            Print("\n CV of Broadcaster-cntCVb Has Been Created in testCase_15. \n\0",1,1,1);

                                                                                                                Print("\n Forking waiter1 in testCase_15. \n\0",1,1,1);
        Fork(waiter1);
                                                                                                                Print("\n Forking waiter2 in testCase_15. \n\0",1,1,1);
        Fork(waiter2);
                                                                                                                Print("\n Forking broadcaster in testCase_15. \n\0",1,1,1);
        Fork(broadcaster);                                                                      

/*      DeleteCV(cntCVw);                                                       Print("\n cv w Has Been Deleted in testCase_15. \n\0",1,1,1);
        DeleteCV(cntCVb);                                                       Print("\n cv b Has Been Deleted in testCase_15. \n\0",1,1,1);
        
        DeleteLock(cntlck);                                                     Print("\n lck Has Been Deleted in testCase_15. \n\0",1,1,1);
*/
        Exit(0);
}