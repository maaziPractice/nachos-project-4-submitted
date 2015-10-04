// onettest.cc
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
#include <cstring>

using namespace std;

//ClientInfo *addressInformation;

int funcCreateLock1(string, ClientInfo*);
int funcCreateCV1(string, ClientInfo*);
void funcSend1(int, int, string);
int funcAcquire1(string, ClientInfo*);
int funcRelease1(string, ClientInfo*);
int funcWait1(string, string, ClientInfo*);
int funcSignal1(string, string, ClientInfo*);
int funcBroadcast1(string, string, ClientInfo*);
int funcDeleteLock1(int, ClientInfo*);
int funcDeleteCV1(int, ClientInfo*);

int funcCreateMV1(string, int, ClientInfo*);
int funcSetMV1(string, int, int, ClientInfo*);
int funcGetMV1(string, int, ClientInfo*);
int funcDeleteMV1(int, ClientInfo*);

// Test out message delivery, by doing the following:
//	1. send a message to the machine with ID "farAddr", at mail box #0
//	2. wait for the other machine's message to arrive (in our mailbox #0)
//	3. send an acknowledgment for the other machine's message
//	4. wait for an acknowledgement from the other machine to our
//	    original message

void myServerFunc1()
{

	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char *ack = "$";
    int retVal=-1;
	std::string passedValue,typeIdentifier,ackString,lockPassedValue,cvPassedValue;

	int flagLockCV;
	char buffer[MaxMailSize]={'\0'};
	int tempi,buflen;
	int flagIndexName;
	int lockIndex, cvIndex;
	bool success;

	string lockToBeAcquiredName="";
	string lockToBeReleasedName="";

	string mvLengthPassedValue="";
	string mvArraySizePassedValue="";
	string mvIDPassedValue="";
	string mvNamePassedValue="";

	string mvArrayIndexPassedValue="";
	string mvAssignValuePassedValue="";

	int flagLengthSizeName=0;
	int flagLengthIndexNameValue=0;
	int flagMVNotCreated=0;

	int mvArrayIndexInt=-1;
	int mvAssignValueInt=-1;
	int mvLengthInt=-1;
	int mvArraySizeInt=-1;
	int mvIDPassedValueInt=-1;

	int countMVNotCreated=0;
	int returnBroadcast;

	while(1)
	{
		postOffice->Receive(0, &inPktHdr, &inMailHdr, buffer);
		typeIdentifier="";
		typeIdentifier=typeIdentifier+buffer[0]+buffer[1];
		passedValue="";
		buflen=strlen(buffer);

		for(tempi=2;tempi<buflen;tempi++)
			passedValue=passedValue+buffer[tempi];

		//cout<<"Got "<<passedValue<<" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;
		//cout<<"typeIdentifier is "<<typeIdentifier<< endl;
		fflush(stdout);
		int indentifyVal=atoi(typeIdentifier.c_str());
		//cout <<"indentifyVal is "<<indentifyVal<<endl;

		ClientInfo *addressInformation;
		addressInformation=new ClientInfo;
		addressInformation->machineId=inPktHdr.from;
		addressInformation->mailboxNo=inMailHdr.from;	//CHECK ON THIS..............................................

		switch(indentifyVal)
		{
			case 1:		//Create Lock

			//cout<<"Got LockName \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;
			retVal=funcCreateLock1(passedValue, addressInformation);
			if(retVal != -1)
			{
				ackString="";
				sprintf(ack,"%d",retVal);
				for(unsigned int i=0;i<strlen(ack);i++)
				{
					ackString+=ack[i];
				}

			}
			else
			{
				ackString="-1";		//Failure scenario
			}

			//cout<<"CreateLock- Index being returned is: "<<ackString<<endl;
			funcSend1(inPktHdr.from, inMailHdr.from, ackString);

			break;		//End of create Lock case

			case 2:		//Acquire Lock

			//cout<<"Acquire- Got LockName \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;
			//int lockToBeAcquiredIndex=atoi(passedValue.c_str());
			lockToBeAcquiredName=passedValue;

			int retAcquire=funcAcquire1(lockToBeAcquiredName, addressInformation);

			if(retAcquire==1 || retAcquire==3)
			{
				ackString="-1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}
			else if (retAcquire==2)
			{
				ackString="1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}

			break;
			//case 2 ends

			case 3:		//Release Lock

			//cout<<"Release- Got LockName \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;
			//int lockToBeReleasedIndex=atoi(passedValue.c_str());
			lockToBeReleasedName=passedValue;

			int retRelease=funcRelease1(lockToBeReleasedName, addressInformation);

			if(retRelease==1 || retRelease==2 || retRelease==4)
			{
				ackString="-1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}
			else if (retRelease==3)
			{
				ackString="1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}

			break;
			//case 3 ends

			case 4:		//Create CV

			//cout<<"Got CVName \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;
			retVal=funcCreateCV1(passedValue, addressInformation);

			if(retVal != -1)
			{
				ackString="";
				sprintf(ack,"%d",retVal);
				for(unsigned int i=0;i<strlen(ack);i++)
				{
					ackString+=ack[i];
				}

			}
			else
			{
				ackString="-1";
			}

			funcSend1(inPktHdr.from, inMailHdr.from, ackString);

			break;
			//case 4 CreateCV ends


			case 5:		//Wait

			//cout<<"Wait- Got LockIndex \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;
			cvPassedValue="";
			lockPassedValue="";
			flagLockCV=0;

			//Segregating the lock and cv id
			for(unsigned int i=0;i<passedValue.size();i++)
			{
				if(passedValue[i]=='+')
				{
					flagLockCV=1;
					continue;
				}

				if(flagLockCV==0)
				{
					cvPassedValue+=passedValue[i];
				}
				else
				{
					lockPassedValue+=passedValue[i];
				}
			}
			//cout<<"Wait- Got CVIndex \""<<cvPassedValue<<"\" and LockIndex \""<<lockPassedValue<<"\""<<endl;

			//converting lock id and cv id to integers
			//lockIndex=atoi(lockPassedValue.c_str());
			//cvIndex=atoi(cvPassedValue.c_str());
			//string ackString;
			int retWaitVal = funcWait1(lockPassedValue, cvPassedValue, addressInformation);

			if (retWaitVal==-1)
			{
				ackString="-1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}


			break;	//case5 Wait ends


			case 6:		//Signal

			//cout<<"Signal- Got string \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;

			cvPassedValue="";
			lockPassedValue="";
			flagLockCV=0;

			//Segregating the lock and cv id
			for(unsigned int i=0;i<passedValue.size();i++)
			{
				if(passedValue[i]=='+')
				{
					flagLockCV=1;
					continue;
				}

				if(flagLockCV==0)
				{
					cvPassedValue+=passedValue[i];
				}
				else
				{
					lockPassedValue+=passedValue[i];
				}
			}
			//cout<<"Signal- Got CVIndex \""<<cvPassedValue<<"\" and LockIndex \""<<lockPassedValue<<"\""<<endl;

			//converting lock id and cv id to integers
			//lockIndex=atoi(lockPassedValue.c_str());
			//cvIndex=atoi(cvPassedValue.c_str());

			int retSigVal = funcSignal1(lockPassedValue, cvPassedValue, addressInformation);

			if(retSigVal==2)
			{
				ackString="1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}
			else if (retSigVal==1)
			{
				ackString="-1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}

			break;	//case6 Signal ends

			case 7:	//Broadcast

			//cout<<"Broadcast- Got string \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;

			cvPassedValue="";
			lockPassedValue="";
			flagLockCV=0;

			//Segregating the lock and cv id
			for(unsigned int i=0;i<passedValue.size();i++)
			{
				if(passedValue[i]=='+')
				{
					flagLockCV=1;
					continue;
				}

				if(flagLockCV==0)
				{
					cvPassedValue+=passedValue[i];
				}
				else
				{
					lockPassedValue+=passedValue[i];
				}
			}
			//cout<<"Signal- Got CVIndex \""<<cvPassedValue<<"\" and LockIndex \""<<lockPassedValue<<"\""<<endl;

			//converting lock id and cv id to integers
			//lockIndex=atoi(lockPassedValue.c_str());
			//cvIndex=atoi(cvPassedValue.c_str());

				cout<<"\nBroadcast- Going to broadcast in cv '"<<cvPassedValue<<"' by lock '"<<lockPassedValue<<"'"<<endl;
							cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

			returnBroadcast=funcBroadcast1(lockPassedValue, cvPassedValue, addressInformation);


			if(returnBroadcast != 2)
				ackString="-1";
			else
				ackString="1";

			funcSend1(inPktHdr.from, inMailHdr.from, ackString);

			break;	//case7 Broadcast ends

			case 8:		//delete lock

			//cout<<"DeleteLock- Got LockIndex \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;
			int lockToBeDeletedIndex=atoi(passedValue.c_str());

			int retDeleteLock=funcDeleteLock1(lockToBeDeletedIndex, addressInformation);

			if(retDeleteLock==1)
			{
				ackString="-1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}
			else if (retDeleteLock==0)
			{
				ackString="1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}

			break;		//end of delete lock

			case 9:		//delete cv

			//cout<<"DeleteCV- Got CVIndex \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;
			int cvToBeDeletedIndex=atoi(passedValue.c_str());

			int retDeleteCV=funcDeleteCV1(cvToBeDeletedIndex, addressInformation);

			if(retDeleteCV==1)
			{
				ackString="-1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}
			else if (retDeleteCV==0)
			{
				ackString="1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}

			break;		//end of delete cv

			case 10:	// CreateMV

			cout<<"\n CreateMV: Got String: "<<passedValue<<" From "<<inPktHdr.from<<", Box: "<<inMailHdr.from<<endl;

			//mvLengthPassedValue="";
			mvArraySizePassedValue="";
			mvNamePassedValue="";

			flagLengthSizeName=0;

			for(unsigned int i=0;i<passedValue.size();i++)
			{
				if(passedValue[i]=='=')
				{
					flagLengthSizeName=2;
					continue;
				}


				if(flagLengthSizeName==0)
				{
					mvNamePassedValue+=passedValue[i];
				}
				else if (flagLengthSizeName==2)
				{
					mvArraySizePassedValue+=passedValue[i];
				}
			}

			//mvLengthInt=atoi(mvLengthPassedValue.c_str());
			mvArraySizeInt=atoi(mvArraySizePassedValue.c_str());

			//cout<<"\n CreateMV: Got MV Name: "<<mvNamePassedValue<<endl;
			//cout<<"\n CreateMV: Got MV Array Size: "<<mvArraySizeInt<<endl;

			// Code: if it already has been created, just return the corresponding nextServerMVLocation & return.

			retVal=funcCreateMV1(mvNamePassedValue, mvArraySizeInt, addressInformation);
			if(retVal != -1)
			{
				ackString="";
				sprintf(ack,"%d",retVal);
				for(unsigned int i=0;i<strlen(ack);i++)
				{
					ackString+=ack[i];
				}

			}
			else
			{
				ackString="-1";
			}
			//cout<<"CreateLock- Index being returned is: "<<ackString<<endl;
			funcSend1(inPktHdr.from, inMailHdr.from, ackString);


			break;

			case 11:	// SetMV

			//cout<<"\n nettest SetMV: Got String: "<<passedValue<<" From "<<inPktHdr.from<<", Box: "<<inMailHdr.from<<endl;

			mvIDPassedValue="";
			mvArrayIndexPassedValue="";
			mvAssignValuePassedValue="";
			flagLengthIndexNameValue=0;


			for(unsigned int i=0;i<passedValue.size();i++)
			{
				if(passedValue[i]=='=')
				{
					flagLengthIndexNameValue=2;
					continue;
				}

				else if (passedValue[i]=='@')
				{
					flagLengthIndexNameValue=3;
					continue;
				}

				if(flagLengthIndexNameValue==0)
				{
					mvIDPassedValue+=passedValue[i];
				}

				else if (flagLengthIndexNameValue==2)
				{
					mvArrayIndexPassedValue+=passedValue[i];
				}

				else if (flagLengthIndexNameValue==3)
				{
					mvAssignValuePassedValue+=passedValue[i];
				}
			}

			//mvIDPassedValueInt=atoi(mvIDPassedValue.c_str());
			mvArrayIndexInt=atoi(mvArrayIndexPassedValue.c_str());
			mvAssignValueInt=atoi(mvAssignValuePassedValue.c_str());

			//cout<<"\n nettest SetMV: Got MV NAme: "<<mvIDPassedValue<<endl;
			//cout<<"\n nettest SetMV: Got MV Array Index: "<<mvArrayIndexInt<<endl;
			//cout<<"\n nettest SetMV: Got MV Assign Value: "<<mvAssignValueInt<<endl;

			int retSetVal = funcSetMV1(mvIDPassedValue, mvArrayIndexInt, mvAssignValueInt, addressInformation);

			if(retSetVal != -1)
			{
				ackString="1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);

			}
			else
			{
				ackString="-1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}

			break;

			case 12:	// GetMV

			//cout<<"\n nettest GetMV: Got String: "<<passedValue<<" From "<<inPktHdr.from<<", Box: "<<inMailHdr.from<<endl;

			mvIDPassedValue="";
			mvArrayIndexPassedValue="";
			flagIndexName=0;

			for(unsigned int i=0;i<passedValue.size();i++)
			{

				if(passedValue[i]=='=')
				{
					flagIndexName=2;
					continue;
				}


				if(flagIndexName==0)
				{
					mvIDPassedValue+=passedValue[i];
				}

				else if (flagIndexName==2)
				{
					mvArrayIndexPassedValue+=passedValue[i];
				}

			}

			//mvIDPassedValueInt=atoi(mvIDPassedValue.c_str());
			mvArrayIndexInt=atoi(mvArrayIndexPassedValue.c_str());

			//cout<<"\n nettest GetMV: Got MV ID: "<<mvIDPassedValueInt<<endl;
			//cout<<"\n nettest GetMV: Got MV Array Index: "<<mvArrayIndexInt<<endl;

			int retGetVal= funcGetMV1(mvIDPassedValue, mvArrayIndexInt, addressInformation);

			if(retGetVal != -100)
			{
				//ackString="GET_SSUCCES";
				ackString="";
				sprintf(ack,"%d",retGetVal);
				for(unsigned int i=0;i<strlen(ack);i++)
				{
					ackString+=ack[i];
				}

				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}

			else
			{
				ackString="-100";

				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}

			break;		//get MV end

			case 13:		//delete mv

			int mvToBeDeletedIndex=atoi(passedValue.c_str());

			int retDeleteMV=funcDeleteMV1(mvToBeDeletedIndex, addressInformation);

			if(retDeleteMV==1)
			{
				ackString="-1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}
			else if (retDeleteMV==0)
			{
				ackString="1";
				funcSend1(inPktHdr.from, inMailHdr.from, ackString);
			}

			break;		//end of delete cv
		}
   }
    // Then we're done!
	interrupt->Halt();

}


int funcCreateLock1(string passedValue, ClientInfo *addressInformation)
{
	//Search for that lock name in the database of locks
	for (int i=0;i<nextServerLockLocation ;i++ )
	{
		if(lock[i] != NULL)
		{
			if (lock[i]->name==passedValue)
			{
				lock[i]->countOfCreateLock++;
				cout<<"\nCreateLock- The Lock by name '"<<passedValue<<"' already Exists. The index being returned is '"<<i;
							cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
				return i;
			}
		}
	}

	//Create Lock actually... object creation
	if (nextServerLockLocation >= MAX_LOCKS)
	{
		printf("\nERROR:: CreateLock- Max locks limit reached");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}
	else
	{
		lock[nextServerLockLocation]=new ServerLock(passedValue);

		cout<<"\nCreateLock- New Lock is created by the name '"<<lock[nextServerLockLocation]->name<<"' at index "<<nextServerLockLocation;
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		fflush(stdout);
	}

	//Increment the counter for next lock creation
	nextServerLockLocation++;
	//return the index of the created lock
	return nextServerLockLocation-1;
}

int funcCreateCV1(string passedValue, ClientInfo *addressInformation)
{

	//Search for that cv name in the database of CVs
	for (int i=0;i<nextServerCVLocation ;i++ )
	{
		if(cv[i] != NULL)
		{
			if (cv[i]->name==passedValue)
			{
				cv[i]->countOfCreateCV++;
				cout<<"\nCreateCV- The CV by name '"<<passedValue<<"' already Exists. The index is being returned is "<<i;
							cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
				return i;
			}
		}
	}

	//Create Lock actually... object creation
	if (nextServerCVLocation >= MAX_CVS)
	{
		printf("\nERROR:: CreateCV- Max CV limit reached");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}
	else
	{
		cv[nextServerCVLocation]=new ServerCV(passedValue);
		cout<<"\nCreateCV- New CV is created by the name '"<<cv[nextServerCVLocation]->name<<"' at index "<<nextServerCVLocation;
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

		fflush(stdout);
	}

	nextServerCVLocation++;
	return nextServerCVLocation-1;
}


void funcSend1(int inPktHdrFromVal, int inMailHdrFromVal, string ackString)
{
	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
	char *ack = (char*)ackString.c_str();
	outPktHdr.from = myMachineID;
	outPktHdr.to = inPktHdrFromVal;
	outMailHdr.to = inMailHdrFromVal;
	outMailHdr.from = 0;
	//ack="ACQUIRE_FAILURE";
	outMailHdr.length = strlen(ack) + 1;
	bool success = postOffice->Send(outPktHdr, outMailHdr, ack);
	if ( !success )
	{
		  printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
		  interrupt->Halt();
	}
}

int funcAcquire1(string lockToBeAcquiredName, ClientInfo *addressInformation)
{
	int lockToBeAcquiredIndex=-1;
	for (int i=0;i<nextServerLockLocation ;i++ )
	{
		if(lock[i] != NULL)
		{
			if (lock[i]->name==lockToBeAcquiredName)
			{

				cout<<"\nAcquire- The Lock by name '"<<lockToBeAcquiredName<<"' FOUND. The index being returned is '"<<i;
							cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
				lockToBeAcquiredIndex=i;
				break;
			}
		}
	}

	if(lockToBeAcquiredIndex==-1)
	{
		cout<<"\nERROR:: Acquire- LockName:"<<lockToBeAcquiredName<<" is Invalid.. Has not been created";
		cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}


	else
	{
		if(lock[lockToBeAcquiredIndex]->lockState==0)	//lock is free
		{
			lock[lockToBeAcquiredIndex]->lockState=1;
			lock[lockToBeAcquiredIndex]->ownerInfo=addressInformation;

			cout<<"\nAcquire- Lock: '"<<lockToBeAcquiredName<<"' has been acquired";
			cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

			return 2;

		}
		//If he is already the owner
		else if (lock[lockToBeAcquiredIndex]->ownerInfo->machineId==addressInformation->machineId && lock[lockToBeAcquiredIndex]->ownerInfo->mailboxNo==addressInformation->mailboxNo)
		{
			cout<<"\nERROR:: Acquire- For Lock: '"<<lockToBeAcquiredName<<"'. You are already the owner..";
			cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
			return 3;
		}
		else
		{
			//cout<<"The User trying to acquire Lock: '"<<lockToBeAcquiredName<<"' appended in the waiting queue.."<<endl;
			lock[lockToBeAcquiredIndex]->waitingQueue->Append((void*)addressInformation);
		}
	}
	return 0;
}



int funcRelease1(string lockToBeReleasedName, ClientInfo *addressInformation)
{
	int lockToBeReleasedIndex=-1;

	for (int i=0;i<nextServerLockLocation ;i++ )
	{
		if(lock[i] != NULL)
		{
			if (lock[i]->name==lockToBeReleasedName)
			{
				cout<<"\nRelease- The Lock by name '"<<lockToBeReleasedName<<"' FOUND. The index is '"<<i;
				cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
				lockToBeReleasedIndex=i;
				break;
			}
		}
	}

	//If he is the Lock owner- success condition
	bool userWaiting=false;
	ClientInfo *waitingUserInformation;

	if(lockToBeReleasedIndex==-1)
	{
		cout<<"\nERROR:: Release- LockName:"<<lockToBeReleasedName<<" is Invalid.. Has not been created";
		cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}

	if(lock[lockToBeReleasedIndex]->lockState==0)
	{
		cout<<"\nERROR: Release- LockName: '"<<lockToBeReleasedName<<"' has not been Acquired";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 2;
	}
	else if (lock[lockToBeReleasedIndex]->ownerInfo->machineId==addressInformation->machineId && lock[lockToBeReleasedIndex]->ownerInfo->mailboxNo==addressInformation->mailboxNo)
	{
		//If the releasing user is the same who acquired it

		if ((lock[lockToBeReleasedIndex]->waitingQueue->IsEmpty())==FALSE)
		{
			cout<<"\nRelease- LockName: '"<<lockToBeReleasedName<<"' has been released";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

			waitingUserInformation = (ClientInfo*)lock[lockToBeReleasedIndex]->waitingQueue->Remove();

			lock[lockToBeReleasedIndex]->ownerInfo=waitingUserInformation;

			//Important -Explicit Acquire statement in release for the threadd who just acquired the lock, after this one has released it
			cout<<"\nAcquire- LockName: '"<<lockToBeReleasedName<<"' has been acquired";
			cout<<" for machine: "<<waitingUserInformation->machineId<<" box: "<<waitingUserInformation->mailboxNo<<endl;
			//End of Important -Explicit Acquire statement in release for the threadd who just acquired the lock, after this one has released it

			string ackString="1";			//ACQUIRE_SUCCESS
			funcSend1(waitingUserInformation->machineId, waitingUserInformation->mailboxNo, ackString);
		}
		else
		{
			lock[lockToBeReleasedIndex]->lockState=0;
			lock[lockToBeReleasedIndex]->ownerInfo=NULL;
			cout<<"\nRelease- LockName: '"<<lockToBeReleasedName<<"' has been released";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		}

		return 3;
	}
	else	//error condition
	{
		//If the releasing user is NOT the same who acquired it
		cout<<"\nERROR:: Release- LockName: '"<<lockToBeReleasedName<<"'. You are not the lock Owner";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 4;
	}
	return 0;
}



int funcWait1(string lockName, string cvName, ClientInfo *addressInformation)
{
	int lockIndex=-1, cvIndex=-1;

	for (int i=0;i<nextServerLockLocation ;i++ )
	{
		if(lock[i] != NULL)
		{
			if (lock[i]->name==lockName)
			{
				//cout<<"\nWait- The Lock by name '"<<lockName<<"' exists. The index is "<<i;
				//cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
				lockIndex=i;
				break;
			}
		}
	}

	if(lockIndex==-1)
	{
		cout<<"\nERROR:: Wait- Lock by Name:"<<lockName<<" is Invalid.. Has not been created";
		cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}

	for (int i=0;i<nextServerCVLocation ;i++ )
	{
		if(cv[i] != NULL)
		{
			if (cv[i]->name==cvName)
			{
				//cout<<"\nWait- The CV by name '"<<cvName<<"' exists. The index is "<<i;
				//			cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
				cvIndex=i;
				break;
			}
		}
	}

	if(cvIndex==-1)
	{
		cout<<"\nERROR:: Wait- CV by Name:"<<cvName<<" is Invalid.. Has not been created";
		cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}



	if (lock[lockIndex]->ownerInfo->machineId != addressInformation->machineId && lock[lockIndex]->ownerInfo->mailboxNo != addressInformation->mailboxNo)
	{
		cout<<"\nWait- ERROR:: You are not the lock owner..";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}

	if (cv[cvIndex]->waitingLock1 == -1)		//Not an Error Condition, since first thread calling wait
	{
		 //cout<<"This is the first thread calling wait.\n";
		 cv[cvIndex]->waitingLock1=lockIndex;
	}

	if (cv[cvIndex]->waitingLock1!=lockIndex)
	{
		cout<<"\nWait- ERROR:: The waiting Lock is not same as the condition Lock";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}

	//Releasing the lock before going to wait
	cout<<"\nWait- Going to Wait on CV name: '"<<cvName<<"' so will release the lock name '"<<lockName<<"'";
				cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

	int releaseOnWait=funcRelease1(lockName, addressInformation);	//$$$$$$CHANGED THE LINE

	if(releaseOnWait==3)
	{
		//printf("\nWait- lockIndex '%d' released successfully. Now going to wait\n",lockIndex);
		cv[cvIndex]->conditionQueue->Append((void*)addressInformation);
	}
	else
	{
		cout<<"\nWait- ERROR:: lockName '"<<lockName<<"' CANNOT be released. NOT going on wait";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}
	return 1;
}




int funcSignal1(string lockName, string cvName, ClientInfo *addressInformation)
{
	int lockIndex=-1, cvIndex=-1;

	for (int i=0;i<nextServerLockLocation ;i++ )
	{
		if(lock[i] != NULL)
		{
			if (lock[i]->name==lockName)
			{
				//cout<<"\nSignal- The Lock by name '"<<lockName<<"' exists. The index is "<<i;
				//cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
				lockIndex=i;
				break;
			}
		}
	}

	if(lockIndex==-1)
	{
		cout<<"\nERROR:: Signal- Lock by Name:"<<lockName<<" is Invalid.. Has not been created";
		cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}

	for (int i=0;i<nextServerCVLocation ;i++ )
	{
		if(cv[i] != NULL)
		{
			if (cv[i]->name==cvName)
			{
				//cout<<"\nSignal- The CV by name '"<<cvName<<"' exists. The index is "<<i;
				//			cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
				cvIndex=i;
				break;
			}
		}
	}

	if(cvIndex==-1)
	{
		cout<<"\nERROR:: Signal- CV by Name:"<<cvName<<" is Invalid.. Has not been created";
		cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}


	if (lock[lockIndex]->ownerInfo->machineId != addressInformation->machineId && lock[lockIndex]->ownerInfo->mailboxNo != addressInformation->mailboxNo)
	{
		cout<<"\nERROR - Signal :: You are not the lock owner..";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}

	if ((cv[cvIndex]->conditionQueue->IsEmpty())==TRUE)		//Not an Error Condition, since signal on an empty cv
	{
		 cout<<"\nERROR - Signal :: No waiting threads in the queue..";
		 			cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		 return 1;
	}

	if (cv[cvIndex]->waitingLock1!=lockIndex)
	{
		cout<<"\nERROR - Signal :: The waiting Lock is not same as the condition Lock";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}

	cout<<"\nSignal- Signalled on CV Name '"<<cvName<<"' with Lock Name '"<<lockName<<"'";
				cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

	ClientInfo *waitingUserOnCVInformation = (ClientInfo*)cv[cvIndex]->conditionQueue->Remove();

	//Letting waiting user Acquire the same lock with which I signalled him
	int acquireOnSignal=funcAcquire1(lockName, waitingUserOnCVInformation);

	if(acquireOnSignal==0)
	{
		//printf("\nSignal- User wanting lockIndex '%d' has been put in the lock waiting queue.\n",lockIndex);
		return 2;

	}
	else
	{
		cout<<"\nSignal- ERROR:: User wanting Lock Name '"<<lockName<<"' after being Signalled CANNOT be put on its waiting queue";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;

	}
}


int funcBroadcast1(string lockName, string cvName, ClientInfo *addressInformation)
{
	int cvIndex=-1,returnBroadcast=2;	//2 since uccess return of sognal is 2
	for (int i=0;i<nextServerCVLocation ;i++ )
	{
		if(cv[i] != NULL)
		{
			if (cv[i]->name==cvName)
			{
				//cout<<"\nBro- The CV by name '"<<cvName<<"' exists. The index is "<<i;
							//cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
				cvIndex=i;
				break;
			}
		}
	}

	if(cvIndex==-1)
	{
		cout<<"\nERROR:: Broadcast- CV by Name:"<<cvName<<" is Invalid.. Has not been created";
		cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}

	while((cv[cvIndex]->conditionQueue->IsEmpty())==FALSE)
	{
		returnBroadcast=funcSignal1(lockName, cvName, addressInformation);

		if(returnBroadcast != 2)
			break;
	}
	return returnBroadcast;

}


int funcDeleteLock1(int lockToBeDeletedIndex, ClientInfo *addressInformation)
{
	if(lockToBeDeletedIndex<0 || lockToBeDeletedIndex>=nextServerLockLocation)
	{
		printf("\nERROR:: DeleteLock- Invalid Index of the lock.. Not been created");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}
	else if(lock[lockToBeDeletedIndex]==NULL)
	{
		printf("\nERROR:: DeleteLock- Invalid Lock Index..NULL value ..");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}
	else
	{
		lock[lockToBeDeletedIndex]->countOfCreateLock--;
		if(lock[lockToBeDeletedIndex]->countOfCreateLock==0)	//lock is free
		{

			delete lock[lockToBeDeletedIndex];
			lock[lockToBeDeletedIndex]=NULL;

			cout<<"\nDeleteLock- The lock with LockIndex: '"<<lockToBeDeletedIndex<<"' has been deleted";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		}
		else
		{
			cout<<"\nDeleteLock- The lock with LockIndex: '"<<lockToBeDeletedIndex<<"' cannot be deleted as someone else might be using it";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		}

	}
	return 0;
}


int funcDeleteCV1(int cvToBeDeletedIndex, ClientInfo *addressInformation)
{
	if(cvToBeDeletedIndex<0 || cvToBeDeletedIndex>=nextServerCVLocation)
	{
		printf("\nERROR:: DeleteCV- Invalid Index of the cv.. Not been created");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}
	else if(cv[cvToBeDeletedIndex]==NULL)
	{
		printf("\nERROR:: DeleteCV- Invalid CV Index..NULL value ..");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}
	else
	{
		cv[cvToBeDeletedIndex]->countOfCreateCV--;
		if(cv[cvToBeDeletedIndex]->countOfCreateCV==0)	//cv is free
		{

			delete cv[cvToBeDeletedIndex];
			cv[cvToBeDeletedIndex]=NULL;
			cout<<"\nDeleteCV- The CV with Index: '"<<cvToBeDeletedIndex<<"' has been deleted";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
			//cout<<"DeleteLock- Checking...print name: '"<<lock[lockToBeDeletedIndex]->name<<"' printed."<<endl;
		}
		else
		{
			cout<<"\nDeleteCV- The CV with Index: '"<<cvToBeDeletedIndex<<"' cannot be deleted as someone else might be using it";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		}

	}
	return 0;
}


int funcCreateMV1(string passedValue, int mvArraySizeInt, ClientInfo *addressInformation)
{

	for (int i=0;i<nextServerMVLocation ;i++ )
	{
		if(mv[i]!=NULL)
		{
			if (mv[i]->name==passedValue)
			{
				if(mv[i]->mvSize==mvArraySizeInt)
				{
					mv[i]->countOfCreateMV++;
					//cout<<"\nCreateMV- MV by name: '"<<passedValue<<"' already Exists. The index: "<<i<<", is being returned";
					//			cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
					//return i;
					return 2;	//To say that I have not created the MV
				}
				else
				{
					cout<<"\nERROR:: CreateMV- MV by name: "<<passedValue<<", already Exists but the array size is different";
								cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
					return -1;
				}
			}
		}
	}

	if (nextServerMVLocation >= MAX_MVS)
	{
		printf("\nERROR:: CreateMV- Max MV limit reached");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}
	else
	{
		mv[nextServerMVLocation]=new ServerMV(passedValue,mvArraySizeInt);
		cout<<"\nCreateMV- New MV is created by the name '"<<mv[nextServerMVLocation]->name<<"' at index "<<nextServerMVLocation;
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

		//cout<<"Created in nextServerMVLocation "<<nextServerMVLocation<<endl;
		nextServerMVLocation++;
		//return nextServerMVLocation-1;
		return 1;		//To say that I have created the MV
	}
}



int funcSetMV1(string mvName, int mvIndexArray, int mvValueAssign, ClientInfo *addressInformation)
{
	int mvToBeUsedIndex=-1;

	for (int i=0;i<nextServerMVLocation ;i++ )
	{
		if(mv[i]!=NULL)
		{
			if (mv[i]->name==mvName)
			{
				if(mvIndexArray >= 0 && mvIndexArray < mv[i]->mvSize)
				{
					//cout<<"\nSetMV- MV by name: '"<<mvName<<"' Exists. The index: "<<i<<", is being used";
					//			cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
					mvToBeUsedIndex=i;
					break;
				}
				else
				{
					cout<<"\nERROR:: SetMV- MV by name: "<<mvName<<", already Exists but the index passed is outside the array size range";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
					return -1;
				}
			}
		}
	}

	//cout <<"\nmvToBeUsedIndex: "<<mvToBeUsedIndex<<" mvIndexArray: "<<mvIndexArray<<" mvValueAssign: "<<mvValueAssign<<endl;
	if(mvToBeUsedIndex==-1)
	{
		cout<<"\nERROR:: SET- MV by Name:"<<mvName<<" is Invalid.. Has not been created";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}
	else
	{
		//cout<<"\n Setting Value. \n";
		mv[mvToBeUsedIndex]->mvValue[mvIndexArray]=mvValueAssign;
		cout<<"\nSetMV- Value being set in '"<<mv[mvToBeUsedIndex]->name<<"' at its array index: "<<mvIndexArray<<" is: "<<mvValueAssign;
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		//cout<<"\nSetMV- Value being set for "<<mv[mvToBeUsedIndex]->name<<" is "<<mv[mvToBeUsedIndex]->mvValue[mvIndexArray]<<endl;
	}
	return 1;
}


int funcGetMV1(string mvName, int mvIndexArray, ClientInfo *addressInformation)
{
	int mvToBeUsedIndex=-1;

	for (int i=0;i<nextServerMVLocation ;i++ )
	{
		if(mv[i]!=NULL)
		{
			if (mv[i]->name==mvName)
			{
				if(mvIndexArray >= 0 && mvIndexArray < mv[i]->mvSize)
				{
					cout<<"\nGetMV- MV by name: '"<<mvName<<"' Exists. The index: "<<i<<", is being used";
								cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
					mvToBeUsedIndex=i;
					break;
				}
				else
				{
					cout<<"\nERROR:: GetMV- MV by name: "<<mvName<<", already Exists but the index passed is outside the array size range";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
					return -100;
				}
			}
		}
	}

	if(mvToBeUsedIndex==-1)
	{
		cout<<"\nERROR:: GET- MV by Name:"<<mvName<<" is Invalid.. Has not been created";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -100;
	}
	else
	{
		cout<<"\nGetMV- Value being returned is: "<<mv[mvToBeUsedIndex]->mvValue[mvIndexArray];
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return mv[mvToBeUsedIndex]->mvValue[mvIndexArray];
	}

}

int funcDeleteMV1(int mvToBeDeletedIndex, ClientInfo *addressInformation)
{
	if(mvToBeDeletedIndex<0 || mvToBeDeletedIndex>=nextServerMVLocation)
	{
		printf("\nERROR:: DeleteMV- Invalid Index of the mv.. Not been created");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}
	else if(mv[mvToBeDeletedIndex]==NULL)
	{
		printf("\nERROR:: DeleteMV- Invalid MV Index..NULL value ..");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}
	else
	{
		mv[mvToBeDeletedIndex]->countOfCreateMV--;
		if(mv[mvToBeDeletedIndex]->countOfCreateMV==0)	//mv is free
		{
			delete mv[mvToBeDeletedIndex];
			mv[mvToBeDeletedIndex]=NULL;

			cout<<"\nDeleteMV- The MV with Index: '"<<mvToBeDeletedIndex<<"' has been deleted";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		}
		else
		{
			cout<<"\nDeleteMV- The MV with Index: '"<<mvToBeDeletedIndex<<"' cannot be deleted as someone else might be using it";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		}
	}
	return 0;
}

