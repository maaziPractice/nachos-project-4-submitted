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

#include "action.h"

#include "system.h"
#include "network.h"
#include "post.h"
#include "interrupt.h"
#include "timer.h"

#include <cstring>

void ThreadZero(int a)
{
	// printf("\nIn threadZero\n");
	while(true) CurrentRequestServent();
}

void ThreadOne(int a)
{
	//printf("\nIn ThreadOne\n");
	ServerToServer();
}


/*

void pingFunction()
{
//	int pingTimer=0;
	int i=0;
	
	time_t timer = time(NULL);

	if(timer-pingTimer>=5)
	{
		pingTimer = timer;
		
//		printf("\n Current Time: '%s' ", ctime(&timer));
		printf("\n Current Time int: '%d' ", timer);

		printf("\n Inside pingFunction. ");

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
					printf("\n Lock with index '%d' has state busy. Pinging the user program that has acquired it. ",i);

					PacketHeader outPktHdr, inPktHdr;
					MailHeader outMailHdr, inMailHdr;

					printf("\n 1. pingData: '%s' ", pingData);

					outPktHdr.to = lock[i]->ownerInfo->machineId;
					outMailHdr.to = 99;
					outMailHdr.from = 3;
					outPktHdr.from =myMachineID;

					outMailHdr.length = strlen(pingData) + 1;

					printf("\n 2. pingData: '%s' ", pingData);

					bool success = postOffice->Send(outPktHdr, outMailHdr, pingData);

					if (success) 
					{
						printf("\n user program having lock '%d' alive, will ping again in 5 seconds. ");
					}

					if ( !success ) 
					{
						printf("The postOffice Send failed. Nachos instance has exited without releasing a lock. \n");
						
						//
						
						if ((lock[i]->waitingQueue->IsEmpty())==FALSE)
						{
							printf("\n pingFunction- LockIndex '%d' has been released",i);

							nextQualifyingMemberForLock = (ClientInfo*)lock[i]->waitingQueue->Remove();
							
							lock[i]->ownerInfo=nextQualifyingMemberForLock;

							//Important
							//Explicit Acquire statement in pingFunction for the thread who gets the lock
							//After the server takes the lock from the thread that exited & assigns to this one
							
							cout<<"\n Acquire- LockIndex: '"<<i<<"' has been acquired";
							cout<<" for machine: "<<nextQualifyingMemberForLock->machineId<<" box: "<<nextQualifyingMemberForLock->mailboxNo<<endl;
							
							//End of Important
							
							string ackString="1";			//ACQUIRE_SUCCESS
							funcSend(nextQualifyingMemberForLock->machineId, nextQualifyingMemberForLock->mailboxNo, ackString);	
						}

						else
						{
							lock[i]->lockState=0;
							lock[i]->ownerInfo=NULL;
							printf("\n pingFunction- LockIndex '%d' has been released (status changed to free)",i);
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
	printf("\n Inside timerFunc. ");

	int a=100;
	bool isRandom = false;
	
	Timer *tmr = new Timer((VoidFunctionPtr) pingFunction,a,isRandom);

	return;
}
*/

void myServerFunc(){
	//Thread *t;
	
	//t = new Thread("timerFunc");
	//t->Fork((VoidFunctionPtr) timerFunc, 0);	

			if(totalServers > 1)
			{
					initialiseDSS();
					Thread* threadZero=new Thread("threadZero");
					threadZero->Fork(ThreadZero,0);

					Thread* threadOne=new Thread("threadOne");
					threadOne->Fork(ThreadOne,0);
			}
			else
			{
				//printf("\nIn Calling myServerFunc1\n");
				myServerFunc1();
			}
}
	


