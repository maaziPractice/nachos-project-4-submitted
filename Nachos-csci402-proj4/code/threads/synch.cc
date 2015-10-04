// synch.cc 
//	Routines for synchronizing threads.  Three kinds of
//	synchronization routines are defined here: semaphores, locks 
//   	and condition variables (the implementation of the last two
//	are left to the reader).
//
// Any implementation of a synchronization routine needs some
// primitive atomic operation.  We assume Nachos is running on
// a uniprocessor, and thus atomicity can be provided by
// turning off interrupts.  While interrupts are disabled, no
// context switch can occur, and thus the current thread is guaranteed
// to hold the CPU throughout, until interrupts are reenabled.
//
// Because some of these routines might be called with interrupts
// already disabled (Semaphore::V for one), instead of turning
// on interrupts at the end of the atomic operation, we always simply
// re-set the interrupt state back to its original value (whether
// that be disabled or enabled).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synch.h"
#include "system.h"
#include "iostream.h"
#include "scheduler.h"

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	Initialize a semaphore, so that it can be used for synchronization.
//
//	"debugName" is an arbitrary name, useful for debugging.
//	"initialValue" is the initial value of the semaphore.
//----------------------------------------------------------------------

Semaphore::Semaphore(char* debugName, int initialValue)
{
    name = debugName;
    value = initialValue;
    queue = new List;
}

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	De-allocate semaphore, when no longer needed.  Assume no one
//	is still waiting on the semaphore!
//----------------------------------------------------------------------

Semaphore::~Semaphore()
{
    delete queue;
}

//----------------------------------------------------------------------
// Semaphore::P
// 	Wait until semaphore value > 0, then decrement.  Checking the
//	value and decrementing must be done atomically, so we
//	need to disable interrupts before checking the value.
//
//	Note that Thread::Sleep assumes that interrupts are disabled
//	when it is called.
//----------------------------------------------------------------------

void
Semaphore::P()
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    
    while (value == 0) { 			// semaphore not available
	queue->Append((void *)currentThread);	// so go to sleep
	currentThread->Sleep();
    } 
    value--; 					// semaphore available, 
						// consume its value
    
    (void) interrupt->SetLevel(oldLevel);	// re-enable interrupts
}

//----------------------------------------------------------------------
// Semaphore::V
// 	Increment semaphore value, waking up a waiter if necessary.
//	As with P(), this operation must be atomic, so we need to disable
//	interrupts.  Scheduler::ReadyToRun() assumes that threads
//	are disabled when it is called.
//----------------------------------------------------------------------

void
Semaphore::V()
{
    Thread *thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    thread = (Thread *)queue->Remove();
    if (thread != NULL)	   // make thread ready, consuming the V immediately
	scheduler->ReadyToRun(thread);
    value++;
    (void) interrupt->SetLevel(oldLevel);
}

// Dummy functions -- so we can compile our later assignments 
// Note -- without a correct implementation of Condition::Wait(), 
// the test case in the network assignment won't work!
Lock::Lock(char* debugName) 
{
     lockStatus = FALSE;
     name=debugName;
     //waitingQueue=NULL;
     waitingQueue=new List;
     lockOwner=new Thread("lockOwner");
}

Lock::~Lock() 
{
    delete lockOwner;
    delete waitingQueue;
}
 
bool Lock::Acquire() 
{
     IntStatus old = interrupt->SetLevel(IntOff);   

     if (currentThread == lockOwner)
     {
		//Trying to Acquire the lock which 1 already holds.
	cout<<"I "<<currentThread->name<<" am the lock owner  !! "<< this->name <<endl;
	interrupt->SetLevel(old);
	return false;	 
     }

     if (lockStatus == FALSE)
     {
	lockStatus=TRUE;
	lockOwner=currentThread;
     }
     else
     {
	//cout<<"Lock is BUSY. Come after sometime..\n";
	waitingQueue->Append((void *)currentThread);
	currentThread->Sleep();
     }

     interrupt->SetLevel(old);
     return true;
}


bool Lock::Release() 
{
     IntStatus old = interrupt->SetLevel(IntOff);
     
     if (currentThread!=lockOwner)
     {
	 cout<<"You are not the Lock owner!!\n";
	 interrupt->SetLevel(old);
	 return false;
     }
     
     if ((waitingQueue->IsEmpty())==FALSE)	
     {
	 Thread *nextOwner=(Thread *)waitingQueue->Remove();
	 scheduler->ReadyToRun(nextOwner);
	 lockOwner=nextOwner;

	 lockStatus=TRUE;
     }

     else
     {
	lockStatus=FALSE;
	lockOwner=NULL;
     }

     interrupt->SetLevel(old);
     return true;
}

Condition::Condition(char* debugName) 
{
     name=debugName;
     waitingLock= new Lock ("waitingLock");
     waitingLock=NULL;
     conditionQueue= new List;
}

Condition::~Condition() 
{
	delete conditionQueue;
}

void Condition::Wait(Lock* conditionLock) 
{
     IntStatus old = interrupt->SetLevel(IntOff);
     if (conditionLock == NULL)
     {
	 cout<<"The lock passed was NULL. You cannot go to the wait State.\n";
	 interrupt->SetLevel(old);
         return;
     }

     if (waitingLock==NULL)
     {
	 //cout<<"This is the first thread calling wait.\n";
	 waitingLock=conditionLock;
     }

     if (waitingLock!=conditionLock)
     {
	 cout<<"The waiting Lock is not same as the condition Lock.\n";
	 interrupt->SetLevel(old);
         return;
     }

     conditionLock->Release();

     conditionQueue->Append(currentThread);

     currentThread->Sleep();
     conditionLock->Acquire();
     interrupt->SetLevel(old);
     return;

     ASSERT(FALSE);	
}

void Condition::Signal(Lock* conditionLock) 
{
     IntStatus old = interrupt->SetLevel(IntOff);     
     if ((conditionQueue->IsEmpty())==TRUE)
     {
	 // If signalling somebody who is not on wait
     interrupt->SetLevel(old);
	 //cout<<"CV Queue Empty..\n";
	 return;	 
     }

     if (waitingLock != conditionLock)
     {
		 //If signalling somebody by a different lock
	 cout<<"The lock passed is not the same waiting Lock so the thread cannot be woken up.\n";
         interrupt->SetLevel(old);
	 return;	
     }

     Thread *nextOwner=(Thread *)conditionQueue->Remove();
     
     scheduler->ReadyToRun(nextOwner);

     if ((conditionQueue->IsEmpty())==TRUE)
     {
	 waitingLock=NULL;
     }
     interrupt->SetLevel(old);
     return;
}

void Condition::Broadcast(Lock* conditionLock) 
{
	//Calls multiple Signals to make the queue empty 
     while((conditionQueue->IsEmpty())==FALSE)
     {
	 Signal(conditionLock);
     }
}
