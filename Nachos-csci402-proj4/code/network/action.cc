#include "action.h"


#define SSMailBox 1
#define SCMailBox 0

//int myMachineID;
     //PERROR used initilise  systsem.cc ln 265 & post.cc 178 &


Lock* PendingQLock;
Lock* lockTableLock;
Lock* CVTableLock;
Lock* MVTableLock;
/* List * PendingQ;
Lock* RqIDBitMapLock;
BitMap* RqIDBitMap;  */
map< string,PendingQElement* > PendingQ;   //PERROR you may declre it void* to avoid getting called destructors in erase
map<string,PendingQElement*>::iterator PendingQiterator;


void initialiseDSS()
{
	PendingQLock =new Lock("PendingQLock");
	lockTableLock=new Lock("lockTableLock");
	CVTableLock=new Lock("CVTableLock");
	MVTableLock=new Lock("MVTableLock");

	//cout<<"\nIn Initilise DSS with myMachineID "<<myMachineID<<endl;
	//cout<<"\nIn Initilise DSS with totalServers "<<totalServers<<endl;
	//myMachineID=myMachineID;
}


PendingQElement::PendingQElement()
   {
   	//cout<<"\nIn PendingQ Element !!!!\n";
   	exactOneYes=false;
   	totalCorreResponses=0;
   	ownerServer=-1;
   	pendingDYHCreateMsgs=new List;
 }


void StructToString(char* DYHRqStructPtr,char* destbuf)
{
	for(unsigned int i=0;i<sizeof(DYHRq);i++)
	     {
				destbuf[i]=DYHRqStructPtr[i];
	     }
	destbuf[sizeof(DYHRq)]='\0';
}

void StringToStruct(char* DYHRqStructPtr,char* destbuf)
{
	for(unsigned int i=0;i<sizeof(DYHRq);i++)
	     {
				destbuf[i]=DYHRqStructPtr[i];
	     }
	//destbuf[sizeof(DYHRq)]='\0';
}

string GenerateKey(string  nameOfEntity,OpCode opcode)
{	char suffix[15];
	//string nameOfEntity = nameOfEntityPtr;
	string key;
	switch(opcode)
			{
				case DYHC_LOCKs:		sprintf(suffix,"%u",DYHC_LOCKs);//PERROR
													break;
				case DYHC_CVs:	        sprintf(suffix,"%u",DYHC_CVs);//PERROR
													break;
				case DYHC_MVs:	        sprintf(suffix,"%u",DYHC_MVs);//PERROR
													 break;

				case DYHA_LOCKs:     sprintf(suffix,"%u",DYHA_LOCKs);//PERROR
													break;
				case DYHR_LOCKs:      sprintf(suffix,"%u",DYHR_LOCKs);//PERROR
													break;

				case DYHW_CVs:			    sprintf(suffix,"%u",DYHW_CVs);//PERROR
													break;

				case DYHS_CVs:			    sprintf(suffix,"%u",DYHS_CVs);//PERROR
																	break;

				case DYHB_CVs:			    sprintf(suffix,"%u",DYHB_CVs);//PERROR
																					break;

				case DYHR_LOCKs_WAIT:			sprintf(suffix,"%u",DYHR_LOCKs_WAIT);//PERROR
																	break;

				case DYHA_LOCKs_SIG:			sprintf(suffix,"%u",DYHA_LOCKs_SIG);//PERROR
																	break;
				case DYHA_LOCKs_BROAD:			sprintf(suffix,"%u",DYHA_LOCKs_BROAD);//PERROR
																					break;

				case DYHG_MVs:			sprintf(suffix,"%u", DYHG_MVs);//PERROR
													break;
				case DYHS_MVs:			sprintf(suffix,"%u", DYHS_MVs );//PERROR
													break;

				//default:
						   	   	   	   	   	   	   //ASSERT(false);
			}
	key = nameOfEntity + "---" + suffix ; //PERROR
	return key;
}

void SendAsIfFromClient(PendingQElement* pendQE)
{
	PacketHeader outPktHdr; MailHeader outMailHdr;
	ClientInfo* clientInfo;

	char *origCliMsg=new char[	strlen((pendQE->origCliMsg).c_str())	 + 1	];
	strcpy(	origCliMsg,(pendQE->origCliMsg).c_str()	);
	//ASSERT((pendQE->clientInfoQ)->IsEmpty() == false);
	int ownerServer=pendQE->ownerServer;
		  while(	(pendQE->clientInfoQ)->IsEmpty() == false )
		  {
					clientInfo  =(ClientInfo*) (pendQE->clientInfoQ)->Remove();
							outMailHdr.to = SCMailBox;
							outMailHdr.from = clientInfo->mailboxNo;	 //Client's mailBox #
							outPktHdr.to = ownerServer;
							outPktHdr.from= clientInfo->machineId; 		//Client's machine ID
							outMailHdr.length =strlen(origCliMsg)+1;


							//printf("\noutMailHdr.from =%d & outPktHdr.from=%d\n", outMailHdr.from,outPktHdr.from);
					//delete clientInfo;   //PERROR

					bool success = postOffice->Send(outPktHdr, outMailHdr, origCliMsg);
			  		if ( !success )
			  		{
			  			  printf("\nSendAsIfFromClient::	The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
			  			  interrupt->Halt();
			  		}

		  }

	//delete[] origCliMsg;
	//delete pendQE->clientInfoQ;
	//delete pendQE->myDYHRq;
	//delete pendQE;     // PERROR make sure erase does not call destructor again

}


void SendAsIfFromSpecClient(ClientInfo* clientInfo,int ownerServer,char* opcode, char* entityName)
{
	char data[MaxMailSize]={'\0'};
	PacketHeader outPktHdr; MailHeader outMailHdr;

	if(strcmp(opcode,"RemoteRelease") == 0)
		strcpy(data,"14");
	else if(strcmp(opcode,"RemoteAcquire") == 0)
		strcpy(data,"15");

	strcat(data,entityName);

	outMailHdr.to = SCMailBox;
	outMailHdr.from = clientInfo->mailboxNo;	 //Client's mailBox #
	outPktHdr.to = ownerServer;
	outPktHdr.from= clientInfo->machineId; 		//Client's machine ID
	outMailHdr.length = strlen(data) + 1;

	 //printf("\nSendAsIfFromSpecClient::\n");
	bool success = postOffice->Send(outPktHdr, outMailHdr, data);
		if ( !success )
		{
			  printf("\nSendAsIfFromSpecClient::	The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
			  interrupt->Halt();
		}
}


void SendErrorToClients(PendingQElement* pendQE)
{
	ClientInfo* clientInfo;
		  while(	(pendQE->clientInfoQ)->IsEmpty() == false )
		  {
					clientInfo  =(ClientInfo*) (pendQE->clientInfoQ)->Remove();
					string ackString="-1";
					funcSend(clientInfo->machineId, clientInfo->mailboxNo, ackString);
					//delete  clientInfo;   //PERROR
		  }
	//delete[] pendQE->origCliMsg;
	//delete  pendQE->clientInfoQ;
	//delete  pendQE->myDYHRq;
	//delete  pendQE;     // PERROR make sure erase does not call destructor again
}


void SendGetMVErrorToClients(PendingQElement* pendQE)
{
	ClientInfo* clientInfo;
		  while(	(pendQE->clientInfoQ)->IsEmpty() == false )
		  {
					clientInfo  =(ClientInfo*) (pendQE->clientInfoQ)->Remove();
					string ackString="-100";
					funcSend(clientInfo->machineId, clientInfo->mailboxNo, ackString);
					//delete  clientInfo;   //PERROR
		  }
}

void SendCreateMessageToClients(PendingQElement* pendQE, string ackString)
{
	ClientInfo* clientInfo;
	while((pendQE->clientInfoQ)->IsEmpty() == false)
	{
		clientInfo  =(ClientInfo*) (pendQE->clientInfoQ)->Remove();
		funcSend(clientInfo->machineId, clientInfo->mailboxNo, ackString);
		//delete  clientInfo;
	}

	//delete pendQE->clientInfoQ;
	//delete pendQE->myDYHRq;
	//delete pendQE;
}


int lookUpforLock(string lockName)
{

int lockIndex=-1;
for (int i=0;i<nextServerLockLocation ;i++ )
	{
		if(lock[i] != NULL)
		{
			if (lock[i]->name==lockName)
			{
				//lock[i]->countOfCreateLock++;
				//cout<<"\nCreateLock- The Lock by name '"<<lockName<<"' already Exists. The index being returned is '"<<i;
							//cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
				lockIndex=i;
				break;
			}
		}
	}


	return lockIndex;
}

int lookUpforCV(string cvName)
{
	int cvIndex=-1;
	for (int i=0;i<nextServerCVLocation ;i++ )
		{
			if(cv[i] != NULL)
			{
				if (cv[i]->name==cvName)
				{
					//cout<<"\nWait- The CV by name '"<<cvName<<"' exists. The index is "<<i<<endl;
						//		cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
					cvIndex=i;
					break;
				}
			}
		}

return cvIndex;

}

int lookUpforMV(string passedValue)
{
	string mvIDPassedValue="" ,	mvArrayIndexPassedValue="",	mvAssignValuePassedValue=""; int flagLengthIndexNameValue=0;
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
						}	else if (flagLengthIndexNameValue==2)
						{
							mvArrayIndexPassedValue+=passedValue[i];
						}	else if (flagLengthIndexNameValue==3)
						{
							mvAssignValuePassedValue+=passedValue[i];
						}
			}
	int mvToBeUsedIndex=-1;

		for (int i=0;i<nextServerMVLocation ;i++ )
		{
			if(mv[i]!=NULL)
			{
				if (mv[i]->name==mvIDPassedValue)
				{

						mvToBeUsedIndex=i;
					   // ASSERT(false);
						break;

				}
			}
		}

	return mvToBeUsedIndex;

}




int lookUpforMVCreate(string passedValue)
{
//Segregating mv name and its array size
	string mvArraySizePassedValue="";
	string mvName="";

	int flagLengthSizeName=0;

	for(unsigned int i=0;i<passedValue.size();i++)
	{
		if(passedValue[i]=='=')
		{
			flagLengthSizeName=2;
			continue;
		}


		if(flagLengthSizeName==0)
		{
			mvName+=passedValue[i];
		}
		else if (flagLengthSizeName==2)
		{
			mvArraySizePassedValue+=passedValue[i];
		}
	}

	//mvLengthInt=atoi(mvLengthPassedValue.c_str());
	int mvArraySizeInt=atoi(mvArraySizePassedValue.c_str());
//End of Segregating mv name and its array size

	int mvToBeUsedIndex=-1;

		for (int i=0;i<nextServerMVLocation ;i++ )
		{
			if(mv[i]!=NULL)
			{
				if (mv[i]->name==mvName)
				{

						mvToBeUsedIndex=i;
						break;

				}
			}
		}

	return mvToBeUsedIndex;

}

void HandleCreateLock(PendingQElement* pendQE)
{
	string ackString="";
	char *ack=new char[5];
	int lengthPassedValue=strlen(pendQE->myDYHRq->nameOfEntity);
	string passedValue="";
	for(int i=0;i<lengthPassedValue;i++)
		passedValue=passedValue+pendQE->myDYHRq->nameOfEntity[i];

	ClientInfo *addressInformation=new ClientInfo;

addressInformation->machineId=pendQE->fMachID;
addressInformation->mailboxNo=pendQE->fMailBoxNum;

	int retVal=-1;
	retVal=funcCreateLock(passedValue, addressInformation);
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
	//Sending to client the acknowledge message
	SendCreateMessageToClients(pendQE, ackString);

}

int funcCreateLock(string passedValue, ClientInfo *addressInformation)
{

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









int funcAcquire(string lockToBeAcquiredName, ClientInfo *addressInformation)
{
	int lockToBeAcquiredIndex=-1;
	for (int i=0;i<nextServerLockLocation ;i++ )
	{
		if(lock[i] != NULL)
		{
			if (lock[i]->name==lockToBeAcquiredName)
			{

				//cout<<"\nAcquire- The Lock by name '"<<lockToBeAcquiredName<<"' FOUND. The index being returned is '"<<i;
				//			cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
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

			cout<<"\nAcquire- Lock: '"<<lock[lockToBeAcquiredIndex]->name<<"' has been acquired";
			cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

			return 2;

		}
		//If he is already the owner
		else if (lock[lockToBeAcquiredIndex]->ownerInfo->machineId==addressInformation->machineId && lock[lockToBeAcquiredIndex]->ownerInfo->mailboxNo==addressInformation->mailboxNo)
		{
			//printf("\nlock[lockToBeAcquiredIndex]->ownerInfo->machineId = %d,  lock[lockToBeAcquiredIndex]->ownerInfo->mailboxNo =%d \n",lock[lockToBeAcquiredIndex]->ownerInfo->machineId,lock[lockToBeAcquiredIndex]->ownerInfo->mailboxNo);
			cout<<"\nERROR:: Acquire- For Lock '"<<lock[lockToBeAcquiredIndex]->name<<"'. You are already the owner..";
			cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
			return 3;
		}
		else
		{
			//cout<<"The User trying to acquire LockIndex:"<<lockToBeAcquiredIndex<<"appended in the waiting queue.."<<endl;
			lock[lockToBeAcquiredIndex]->waitingQueue->Append((void*)addressInformation);
		}
	}
	return 0;
}

int funcRelease(string lockToBeReleasedName, ClientInfo *addressInformation)
{
	int lockToBeReleasedIndex=lookUpforLock(lockToBeReleasedName);

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
			cout<<"\nERROR: Release- Lock '"<<lock[lockToBeReleasedIndex]->name<<"' has not been Acquired";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 2;
	}
	else if (lock[lockToBeReleasedIndex]->ownerInfo->machineId==addressInformation->machineId && lock[lockToBeReleasedIndex]->ownerInfo->mailboxNo==addressInformation->mailboxNo)
	{
		//If the releasing user is the same who acquired it


		//printf("\nRealese 1 lock[lockToBeReleasedIndex]->ownerInfo->machineId = %d,  lock[lockToBeReleasedIndex]->ownerInfo->mailboxNo =%d \n",lock[lockToBeReleasedIndex]->ownerInfo->machineId,lock[lockToBeReleasedIndex]->ownerInfo->mailboxNo);

		if ((lock[lockToBeReleasedIndex]->waitingQueue->IsEmpty())==FALSE)
		{
			cout<<"\nRelease- Lock: '"<<lock[lockToBeReleasedIndex]->name<<"' has been released";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

			waitingUserInformation = (ClientInfo*)lock[lockToBeReleasedIndex]->waitingQueue->Remove();

			lock[lockToBeReleasedIndex]->ownerInfo=waitingUserInformation;
			//printf("\nRealese 2lock[lockToBeReleasedIndex]->ownerInfo->machineId = %d,  lock[lockToBeReleasedIndex]->ownerInfo->mailboxNo =%d \n",lock[lockToBeReleasedIndex]->ownerInfo->machineId,lock[lockToBeReleasedIndex]->ownerInfo->mailboxNo);
			//Important -Explicit Acquire statement in release for the threadd who just acquired the lock, after this one has released it
			cout<<"\nAcquire- Lock: '"<<lock[lockToBeReleasedIndex]->name<<"' has been acquired";
			cout<<" for machine: "<<waitingUserInformation->machineId<<" box: "<<waitingUserInformation->mailboxNo<<endl;
			//End of Important -Explicit Acquire statement in release for the threadd who just acquired the lock, after this one has released it

			string ackString="1";			//ACQUIRE_SUCCESS
			funcSend(waitingUserInformation->machineId, waitingUserInformation->mailboxNo, ackString);

		}
		else
		{
			lock[lockToBeReleasedIndex]->lockState=0;
			lock[lockToBeReleasedIndex]->ownerInfo=NULL;
			cout<<"\nRelease- Lock: '"<<lock[lockToBeReleasedIndex]->name<<"' has been released";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		}

		return 3;
	}
	else	//error condition
	{
		//If the releasing user is NOT the same who acquired it
		cout<<"\nERROR:: Release- Lock: "<<lock[lockToBeReleasedIndex]->name<<" cannot be released. You are not the lock Owner";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 4;
	}
	return 0;
}








void SendDYH(DYHRq* myDYHRq)
{

	char DYHMessage[ sizeof(DYHRq) + 1 ];  //PERROR

	StructToString((char *) myDYHRq, DYHMessage);

	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
	char *dyh = DYHMessage;
	outMailHdr.to = SSMailBox;
	outMailHdr.from = SCMailBox;
	//ack="ACQUIRE_FAILURE";
	outMailHdr.length = sizeof(DYHRq);//strlen(dyh) + 1;
//	ASSERT(	outMailHdr.length == (sizeof(DYHRq) + 1)	);
	//int fromMachineID=myMachineID;

	outPktHdr.from= myMachineID;  // machine ID sending server
	 for(int i=0;i<totalServers;i++)
		 {
			 if(i != myMachineID)
			 {
				 outPktHdr.to = i; // machine ID of destination server
				 //printf("\nSendDYH::myMachineID %d::  sending to machineID- %d\n",myMachineID,i);
				 bool success = postOffice->Send(outPktHdr, outMailHdr, dyh);
					if ( !success )
					{
						  printf("\nSendDYH:: The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
						  interrupt->Halt();
					}
			 }

		 }
}

void ReplyToDYH(int farSerMachiID,DYHRq* myDYHRq)
{
	PacketHeader outPktHdr; MailHeader outMailHdr;

	char DYHMessage[ sizeof(DYHRq) + 1 ];  //PERROR
	myDYHRq->ReqRep=false;
	StructToString((char *) myDYHRq, DYHMessage);

	char *dyh = DYHMessage;
	outMailHdr.length = sizeof(DYHRq);//strlen(dyh) + 1;
//	ASSERT(	outMailHdr.length == (sizeof(DYHRq) + 1)	);

	outMailHdr.to = SSMailBox;
	outMailHdr.from = SSMailBox;
	outPktHdr.to = farSerMachiID;
	outPktHdr.from= myMachineID; //my machine ID

	//printf("\nThe postOffice Send ReplyToDYH\n");
	bool success = postOffice->Send(outPktHdr, outMailHdr, dyh);
	if ( !success )
	{
		  printf("\nReplyToDYH::: The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
		  interrupt->Halt();
	}

}

void funcSend(int inPktHdrFromVal, int inMailHdrFromVal, string ackString)
{
	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
	char *ack = (char*)ackString.c_str();
	outPktHdr.to = inPktHdrFromVal;

	outMailHdr.to = inMailHdrFromVal;
	outMailHdr.from = SCMailBox;
	//ack="ACQUIRE_FAILURE";
	outMailHdr.length = strlen(ack) + 1;

	outPktHdr.from= myMachineID;
	bool success = postOffice->Send(outPktHdr, outMailHdr, ack);
	if ( !success )
	{
		  printf("\nfuncSend:: The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
		  interrupt->Halt();
	}

}





void HandleCreateCV(PendingQElement* pendQE)
{
	string ackString="";
	char *ack=new char[5];
	int lengthPassedValue=strlen(pendQE->myDYHRq->nameOfEntity);
	string passedValue="";
	for(int i=0;i<lengthPassedValue;i++)
		passedValue=passedValue+pendQE->myDYHRq->nameOfEntity[i];

	ClientInfo *addressInformation=new ClientInfo;

addressInformation->machineId=pendQE->fMachID;
addressInformation->mailboxNo=pendQE->fMailBoxNum;

	int retVal=-1;
	retVal=funcCreateCV(passedValue, addressInformation);
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
	//Sending to client the acknowledge message
	SendCreateMessageToClients(pendQE, ackString);

}


int funcCreateCV(string passedValue, ClientInfo *addressInformation)
{

	//Create CV actually... object creation
	if (nextServerCVLocation >= MAX_CVS)
	{
		printf("\nERROR:: CreateCV- Max CV limit reached");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}
	else
	{
		cv[nextServerCVLocation]=new ServerCV(passedValue);
		cout<<"\nCreateCV- New CV is created by the name '"<<cv[nextServerCVLocation]->name<<"' at location index "<<nextServerCVLocation;
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

		fflush(stdout);
	}

	nextServerCVLocation++;
	return nextServerCVLocation-1;
}



void HandleCreateMV(PendingQElement* pendQE)
{
	string ackString="";
	char *ack=new char[5];
	int lengthPassedValue=strlen(pendQE->myDYHRq->nameOfEntity);
	string passedValue="";
	for(int i=0;i<lengthPassedValue;i++)
		passedValue=passedValue+pendQE->myDYHRq->nameOfEntity[i];


	string mvArraySizePassedValue="";
	string mvNamePassedValue="";

	int flagLengthSizeName=0;

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
	int mvArraySizeInt=atoi(mvArraySizePassedValue.c_str());


	ClientInfo *addressInformation=new ClientInfo;

addressInformation->machineId=pendQE->fMachID;
addressInformation->mailboxNo=pendQE->fMailBoxNum;

	int retVal=-1;
	retVal=funcCreateMV(mvNamePassedValue, mvArraySizeInt, addressInformation);
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
	//Sending to client the acknowledge message
	SendCreateMessageToClients(pendQE, "1");

}



int funcCreateMV(string passedValue, int mvArraySizeInt, ClientInfo *addressInformation)
{

	if (nextServerMVLocation >= MAX_MVS)
	{
		printf("\nERROR:: CreateMV- Max MV limit reached");
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}
	else
	{
		mv[nextServerMVLocation]=new ServerMV(passedValue,mvArraySizeInt);
		cout<<"\nCreateMV- New MV is created by the name '"<<mv[nextServerMVLocation]->name<<"' at location Index "<<nextServerMVLocation;
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

		//cout<<"Created in nextServerMVLocation "<<nextServerMVLocation<<endl;
		nextServerMVLocation++;
		//return nextServerMVLocation-1;
		return 1;		//To say that I have created the MV
	}
}









int funcWait(int lockIndex, int cvIndex, ClientInfo *addressInformation)
{


	if (lock[lockIndex]->ownerInfo->machineId != addressInformation->machineId && lock[lockIndex]->ownerInfo->mailboxNo != addressInformation->mailboxNo)
	{
		cout<<"\nWait- ERROR:: You are not the lock owner..";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return -1;
	}

	if (cv[cvIndex]->waitingLock == "")		//Not an Error Condition, since first thread calling wait
	{
		 //cout<<"This is the first thread calling wait.\n";
		 cv[cvIndex]->waitingLock=lock[lockIndex]->name;
	}

	//Releasing the lock before going to wait
	cout<<"\nWait- Going to Wait on CV '"<<cv[cvIndex]->name<<"' so will release the lockIndex '"<<lock[lockIndex]->name<<"'";
				cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;


		int releaseOnWait=funcRelease(lock[lockIndex]->name, addressInformation);
		if(releaseOnWait==3)
		{
			//printf("\nWait- lockIndex '%d' released successfully. Now going to wait\n",lockIndex);
			cv[cvIndex]->conditionQueue->Append((void*)addressInformation);
		}
		else
		{
			cout<<"\nWait- ERROR:: Lock '"<<lock[lockIndex]->name<<"' CANNOT be released. NOT going on wait";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
			return -1;
		}

	return 1;
}


int funcSignal(int lockIndex, int cvIndex, ClientInfo *addressInformation)
{

	if (lock[lockIndex]->ownerInfo->machineId != addressInformation->machineId && lock[lockIndex]->ownerInfo->mailboxNo != addressInformation->mailboxNo)
	{
		cout<<"\nERROR - Signal :: You are not the lock owner..";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		return 1;
	}

	cout<<"\nSignal- Signalled on CV Name '"<<cv[cvIndex]->name<<"' with Lock Name '"<<lock[lockIndex]->name<<"'";
				cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

	if(cv[cvIndex]->conditionQueue->IsEmpty() == false)
		 {
						ClientInfo *waitingUserOnCVInformation = (ClientInfo*)cv[cvIndex]->conditionQueue->Remove();
						//Letting waiting user Acquire the same lock with which I signalled him
						int acquireOnSignal=funcAcquire(lock[lockIndex]->name, waitingUserOnCVInformation);

						if(acquireOnSignal==0)
						{
							//printf("\nSignal- User wanting lockIndex '%d' has been put in the lock waiting queue.\n",lockIndex);
							return 2;

						}
						else
						{
							//ASSERT(acquireOnSignal !=2 && acquireOnSignal!=3);
							cout<<"\nSignal- ERROR:: User wanting lock '"<<lock[lockIndex]->name<<"' after being Signalled CANNOT be put on its waiting queue";
										cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
							return 1;

						}
			}
	else
		return 2; //wasted signal

}


/*
int lookUpforMV(string passedValue)
{
	for (int i=0;i<nextServerMVLocation ;i++ )
		{
			if(mv[i]!=NULL)
			{
				if (mv[i]->name==passedValue)
				{
					return i;
				}
			}
		}

	//cout<<"\n No such MV with name "<< passedValue <<" exists at this server"<<endl;
	return -1;
} */

void funcSetMV(int mvIndex, int mvIndexArray, int mvValueAssign, ClientInfo *addressInformation)
{
		mv[mvIndex]->mvValue[mvIndexArray]=mvValueAssign;
		cout<<"\nSetMV- Value being set in '"<<mv[mvIndex]->name<<"' at its array index: "<<mvIndexArray<<" is: "<<mvValueAssign;
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
}

int funcBroadcast(int lockIndex, int cvIndex, ClientInfo *addressInformation)
{

	if (lock[lockIndex]->ownerInfo->machineId != addressInformation->machineId && lock[lockIndex]->ownerInfo->mailboxNo != addressInformation->mailboxNo)
	{
		cout<<"\nERROR - Signal :: You are not the lock owner..";
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
		//ASSERT(false);
		return 1;
		
	}

	int returnBroadcast=2;
	while((cv[cvIndex]->conditionQueue->IsEmpty())==FALSE)
	{
		returnBroadcast=funcSignal(lockIndex, cvIndex, addressInformation);

		if(returnBroadcast != 2)
			{
			//ASSERT(false);
			break;
			}
	}
	return returnBroadcast;

}


