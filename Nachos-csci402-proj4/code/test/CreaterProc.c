/*      CreateProc.c 

       This is Negative test Case
       Here a Process Creater Proc Creates various locks & CVs 
       Then it execs executable IllegalUser which tries to attempt to use these locks & CV which does not belong to it
       
       Please note since IDs or handlers for locks & CV are nothing but Indices of KernelLockCvTable Array & KernelCvTable array,
       hence  IDs of locks or CVs are predictable & same are supplied to IllegalUser, hence they are hardcoded there
	    Here Yield() Sys Call is tested
*/

#include "syscall.h"

void main()
{
        int lck1=1, lck2=2, lck3=3, lck4=4, lck5=5, lck6=6,i=0;
        int cv1=1, cv2=2, cv3=3, cv4=4, cv5=5, cv6=6;

 		lck1=CreateLock("lock1", 5);       /*Nachos will generate the handle/ID for lck1 as 0 */
 		lck2=CreateLock("lock2", 5);		/*Nachos will generate the handle/ID for lck2 as 1 */
 		lck3=CreateLock("lock3", 5);		/*Nachos will generate the handle/ID for lck3 as 2 */
        
        cv1 = CreateCV("cv1", 3);		/*Nachos will generate the handle/ID for cv1 as 0 */
		cv2 = CreateCV("cv2", 3);		/*Nachos will generate the handle/ID for cv2 as 1*/
		cv3 = CreateCV("cv3", 3);		/*Nachos will generate the handle/ID for cv3 as 2 */
		cv4 = CreateCV("cv4", 3);		/*Nachos will generate the handle/ID for cv4 as 3 */
        
        Exec("../test/IllegalUser",19);
        for(i=0;i<100;i++)
         		{		Yield();     } 
        Exit(0);
 }