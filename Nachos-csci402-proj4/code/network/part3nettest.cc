// nettest.cc 
//	Test out message delivery between two "Nachos" machines,
//	using the Post Office to coordinate delivery.
//
//	Two caveats:
//	  1. Two copies of Nachos must be running, with machine ID's 0 and 1:
//		./nachos -m 0 -o 1 &
//		./nachos -m 1 -o 0 &
//
//	  2. You need an implementation of condition variables,
//	     which is *not* provided as part of the baseline threads 
//	     implementation.  The Post Office won't work without
//	     a correct implementation of condition variables.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#include "system.h"
#include "network.h"
#include "post.h"
#include "interrupt.h"

#include "timer.h"

#include <cstring>

using namespace std;

extern void myServerFunc1();
extern void funcSend1(int, int, string);

// Test out message delivery, by doing the following:
//	1. send a message to the machine with ID "farAddr", at mail box #0
//	2. wait for the other machine's message to arrive (in our mailbox #0)
//	3. send an acknowledgment for the other machine's message
//	4. wait for an acknowledgement from the other machine to our 
//	    original message


void pingFunction()
{
//	int pingTimer=0;
	int i=0;
	
	time_t timer = time(NULL);

	if(timer-pingTimer>=5)
	{
		pingTimer = timer;
		
//		printf("\n Current Time: '%s' ", ctime(&timer));
//		printf("\n Current Time int: '%d' ", timer);

//		printf("\n Inside pingFunction. ");

//		code for finding if a user program died taking a lock, if so then assign the lock to the next waiting member (if there is one), else make the lock free.

		char *pingData = "ping";

		//int x = addressInformationClient->machineId;
		
		ClientInfo *nextQualifyingMemberForLock;

		for(i=0;i<nextServerLockLocation;i++)
		{
			if(lock[i]!=NULL)
			{
				if (lock[i]->lockState==1)
				{
					cout<<"\n Lock Name: '"<<lock[i]->name<<"' has state busy. Pinging the user program that has acquired it. \n";

					PacketHeader outPktHdr, inPktHdr;
					MailHeader outMailHdr, inMailHdr;

//					printf("\n 1. pingData: '%s' ", pingData);

					outPktHdr.to = lock[i]->ownerInfo->machineId;
					outMailHdr.to = 9;
					outMailHdr.from = 3;

					outMailHdr.length = strlen(pingData) + 1;

//					printf("\n 2. pingData: '%s' ", pingData);

					bool success = postOffice->Send(outPktHdr, outMailHdr, pingData);

					if (success) 
					{
						cout<<"\n User program having Lock Name: '"<<lock[i]->name<<"'  alive, will ping again in 5 seconds. \n";
					}

					if ( !success ) 
					{
						printf("\n The postOffice Send failed. Nachos instance has exited without releasing a lock. \n");
						
						//
						
						if ((lock[i]->waitingQueue->IsEmpty())==FALSE)
						{
							cout<<"\n pingFunction- Lock Name: '"<<lock[i]->name<<"' has been released. \n";

							nextQualifyingMemberForLock = (ClientInfo*)lock[i]->waitingQueue->Remove();
							
							lock[i]->ownerInfo=nextQualifyingMemberForLock;

							//Important
							//Explicit Acquire statement in pingFunction for the thread who gets the lock
							//After the server takes the lock from the thread that exited & assigns to this one
							
							cout<<"\n Acquire- Lock name: '"<<lock[i]->name<<"' has been acquired \n";
							cout<<" for machine: "<<nextQualifyingMemberForLock->machineId<<" box: "<<nextQualifyingMemberForLock->mailboxNo<<endl;
							
							//End of Important
							
							string ackString="1";			//ACQUIRE_SUCCESS
							funcSend1(nextQualifyingMemberForLock->machineId, nextQualifyingMemberForLock->mailboxNo, ackString);	
						}

						else
						{
							lock[i]->lockState=0;
							lock[i]->ownerInfo=NULL;
							cout<<"\n pingFunction- Lock Name: '"<<lock[i]->name<<"' has been released (status changed to free) \n";
						}						
						//
					}
	
				}
			}
		}
	}



//	End of code for finding if a user program died taking a lock, if so then assign the lock to the next waiting member (if there is one), else make the lock free.

	else
	{
		return;
	}
	return;
	
}

void timerFunc()
{
//	printf("\n Inside timerFunc. ");

	int a=100;
	bool isRandom = false;
	
	Timer *tmr = new Timer((VoidFunctionPtr) pingFunction,a,isRandom);

	return;
}

void myServerFunc3()
{
	Thread *t;
	
	t = new Thread("serverFunc");
	t->Fork((VoidFunctionPtr) myServerFunc1, 0);
	
	t = new Thread("timerFunc");
	t->Fork((VoidFunctionPtr) timerFunc, 0);
}

