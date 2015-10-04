/*      OutOfRange.c delete 14

        Each of KernelCVTable &KernelLockTable have been implemeted as arrays of struct KernelCV & KernelLock respectively
        LockID & CVID returned by the CreateLock &CreateCV  sys calls are index into these arrays
        So if user passes LockID/LockHandle OR CVID/CVHandle which is beyond the size of the arrays 
        that is if it is negaitve or greater that MAX_LOCKS or MAX_LOCKS
		
*/

#include "syscall.h"

void main()
{
        int lck1=1, lck2=2, lck3=3, lck4=4, lck5=5, lck6=6;
        int cv1=1, cv2=2, cv3=3, cv4=4, cv5=5, cv6=6;

        Acquire(-1);
                                                                                       
        Release(-2);

        lck1 = CreateLock("lock1", 5);
        cv1 = CreateCV("cv1", 3);
                                                                                        
        Wait(-3,lck1);
        DeleteCV(cv1);
        DeleteLock(lck1);

        lck2 = CreateLock("lock2", 5);
        cv2 = CreateCV("cv2", 3);
                                                                                        
        Wait(cv2,-4);
        DeleteCV(cv2);
        DeleteLock(lck2);

        lck4 = CreateLock("lock4", 5);
        cv4 = CreateCV("cv4", 3);
                                                                                       
        Signal(-5,lck4);
        DeleteCV(cv4);
        DeleteLock(lck4);

        lck5 = CreateLock("lock5", 5);
        cv5 = CreateCV("cv5", 3);
                                                                                        
        Signal(cv5,-6);
        DeleteCV(cv5);
       DeleteLock(lck5);
                                                                                      
        DeleteLock(3000);
        
       DeleteCV(-12);							 /*giving wrong value for CVid or CV handler*/
       Broadcast(10000,10);               /*giving wrong value for CVid or CV handler*/
       Broadcast(10,100000);			/*giving wrong value for lockid or lock handler*/
       
        Exit(0);
}