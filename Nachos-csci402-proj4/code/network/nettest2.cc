#include "action.h"


#define SSMailBox 1
#define IdntHaveIt -1



void ServeReqeusts(int farSerMachiID,DYHRq* msgObj)
{			bool ans;

			string nameOfEntity="";
			string key="";
			//IMP- CORRECT THIS
			string lockName(msgObj->nameOfEntity);
			string cvName(msgObj->nameOfEntity);
			string mvName(msgObj->nameOfEntity);
			 switch(msgObj->opcode)
									 {
											 case DYHA_LOCKs:   // DYH Non Create Type Acquire,Release
											 case DYHR_LOCKs:
																		 lockTableLock->Acquire();
																			 lockName=msgObj->nameOfEntity;
																			 if( IdntHaveIt == lookUpforLock(lockName))    ans=false; else ans=true;
																		 lockTableLock->Release();
																			//we are using the same object since its a pointer
																			//meaning its a reply
																			msgObj->DIHEntity = ans;

																			//printf("\nFROM myMachineID %d:: Calling Reply To DYH in Response to %d\n",myMachineID,farSerMachiID);
																			//getchar();
																			ReplyToDYH(farSerMachiID,msgObj);
																		break;

											 case DYHW_CVs:
											 case DYHS_CVs:
											 case DYHB_CVs:
												 	 	 	 	 	 CVTableLock->Acquire();
												 							 cvName=msgObj->nameOfEntity;
																			int CVIndex = lookUpforCV(cvName);
																					if( IdntHaveIt == CVIndex)    ans=false; else ans=true;
																	CVTableLock->Release();
																			msgObj->DIHEntity = ans;
																	       ReplyToDYH(farSerMachiID,msgObj);
												 	 	 	 	 	 	 break;
											 case DYHG_MVs:
											 case DYHS_MVs:
												 	 	 	 	 	 	 MVTableLock->Acquire();
																				 mvName=msgObj->nameOfEntity;
																				 //cout<<"\n MV being searched is "<<mvName<<endl;
																				  int MVIndex = lookUpforMV(mvName);
																				  //cout<<"\n MVIndex "<< MVIndex <<endl;
																		 if( IdntHaveIt == MVIndex)    ans=false; else ans=true;
																		MVTableLock->Release();
																				msgObj->DIHEntity = ans;
																			   ReplyToDYH(farSerMachiID,msgObj);
																		break;
											 case DYHR_LOCKs_WAIT:
												 	 	 	 	 	 	 lockTableLock->Acquire();
												 	 	 	 	 	 	 lockName=msgObj->nameOfEntity;
																				  // int retVal;
												 	 	 	 	 	 	 //printf("\nIn DYHR_LOCKs_WAIT of ServeRequests\n");
																				   if( IdntHaveIt == lookUpforLock(lockName))    ans=false; else ans=true;
																				   if(ans == true)
																						   {
																					   	   	   	   int lockToBeReleasedIndex =lookUpforLock(lockName) ;
																					   	   	   	   if (lock[lockToBeReleasedIndex]->ownerInfo->machineId== msgObj->CMachID && lock[lockToBeReleasedIndex]->ownerInfo->mailboxNo== msgObj->CmailBOX)
																					   	   	   	   {

																					   	   	   	   }
																					   	   	   	   else msgObj->CMachID = -90;

																					   	   	   	   //Effi delete ownerInfo;
																						   }
												 	 	 	 	 	     lockTableLock->Release();
												 	 	 	 	 	     	  msgObj->DIHEntity = ans;
												 	 	 	 	 	          ReplyToDYH(farSerMachiID,msgObj);
												 	 	 	 	 	 	 break;

									         case DYHA_LOCKs_SIG:
									         case DYHA_LOCKs_BROAD:
																		 lockTableLock->Acquire();
																		 lockName=msgObj->nameOfEntity;
																				  // int retVal;
																		 //printf("\nIn DYHA_LOCKs_SIG of ServeRequests\n");
																				   if( IdntHaveIt == lookUpforLock(lockName))    ans=false; else ans=true;
																				   if(ans == true)
																						   {
																								   int lockToBeReleasedIndex =lookUpforLock(lockName) ;
																								   //cout<<"\nlock[lockToBeReleasedIndex]->ownerInfo->machineId "<<lock[lockToBeReleasedIndex]->ownerInfo->machineId<<endl;
																								   //cout<<"\nlock[lockToBeReleasedIndex]->ownerInfo->mailboxNo "<<lock[lockToBeReleasedIndex]->ownerInfo->mailboxNo <<endl;
																								   //cout<<"\nmsgObj->CMachID "<<msgObj->CMachID<<endl;
																								   //cout<<"\nmsgObj->CmailBOX "<<msgObj->CmailBOX<<endl;

																								   if (lock[lockToBeReleasedIndex]->ownerInfo->machineId== msgObj->CMachID && lock[lockToBeReleasedIndex]->ownerInfo->mailboxNo== msgObj->CmailBOX)
																								   {

																								   }
																								   else msgObj->CMachID = -90;

																								   //Effi delete ownerInfo;
																						   }
																		 lockTableLock->Release();
																			  msgObj->DIHEntity = ans;
																			  ReplyToDYH(farSerMachiID,msgObj);
																		 break;


										case DYHC_LOCKs:
														 lockTableLock->Acquire();
																//string lockName(msgObj->nameOfEntity);
																 if( IdntHaveIt == lookUpforLock(lockName))
																	 ans=false;
																 else
																	 ans=true;
															//	printf("\nReached the case of DYHC_LOCKS in Serve Requests\n");

															 lockTableLock->Release();

															if(ans==true)
															{
																msgObj->DIHEntity = ans;
																//printf("\nFROM myMachineID %d:: Giving Yes Reply To CreateLock DYH in Response to %d\n",myMachineID,farSerMachiID);
																ReplyToDYH(farSerMachiID,msgObj);

															}
															else
															{
																msgObj->DIHEntity = ans;
																//printf("\nFROM myMachineID %d:: Giving No Reply To CreateLock DYH in Response to %d\n",myMachineID,farSerMachiID);

																//Looking in my pending request table

																nameOfEntity=msgObj->nameOfEntity;
																key = GenerateKey(nameOfEntity,(OpCode)msgObj->opcode);

																//printf("\nReached in the else part of Serve Requests\n");

																//Lock Added later
																PendingQLock->Acquire();
																if(PendingQ.count(key) > 0)
																{
																	//printf("\nIn the if  part of object IS found in map value. Map Count: %d\n",PendingQ.count(key));
																	//Entry for same Entity name with same opcode
																	//printf("\nI have got the entry for key '%s'  in my pendingQ table so now comparing the timestamp.\n",key);
																	PendingQElement* pendQE = PendingQ.find(key)->second;

																	printf("\nGoing to compare timestamp values for the CREATE LOCK. Values: My 'Server:%d' TS: %u.  Received Request 'Server:%d' TS: %u\n",myMachineID,pendQE->myDYHRq->timestamp,farSerMachiID,msgObj->timestamp);
																	if(pendQE->myDYHRq->timestamp > msgObj->timestamp)
																	{
																		printf("\nMy timestamp is LATER, I 'Serverid: %d' should reply no..\n",myMachineID);
																		ReplyToDYH(farSerMachiID,msgObj);	//If my timestamp is later, then reply NO.
																	}
																	else if(pendQE->myDYHRq->timestamp < msgObj->timestamp)
																	{
																		printf("\nMy timestamp is earlier, then I 'Serverid: %d' should queue the request..\n",myMachineID);
																		//If my timestamp is earlier, then I should queue the request
																		pendQE->pendingDYHCreateMsgs->Append((void *)farSerMachiID);
																	}
																	else
																	{
																		printf("\nBoth the timestamps are same..Tie breaker on the basis of Machine Id..\n");

																		if(myMachineID > farSerMachiID)
																		{
																			printf("\nMy MachineID is LATER, then I should reply no..\n");
																			ReplyToDYH(farSerMachiID,msgObj);	//If my timestamp is later, then reply NO.
																		}
																		else
																		{
																			printf("\nMy MachineID is earlier, then I should queue the request..\n");
																			//If my timestamp is earlier, then I should queue the request
																			pendQE->pendingDYHCreateMsgs->Append((void *)farSerMachiID);
																		}
																	}


																}
																else
																{
																	//printf("\nNo same entry of object found in map. Map Count: %d\n",PendingQ.count(key));
																	ReplyToDYH(farSerMachiID,msgObj);
															    }
																//Added later
																PendingQLock->Release();
															}
												break;


										case DYHC_CVs:
														 CVTableLock->Acquire();
																//string lockName(msgObj->nameOfEntity);
																 if( IdntHaveIt == lookUpforCV(cvName))
																	 ans=false;
																 else
																	 ans=true;

															 CVTableLock->Release();

															if(ans==true)
															{
																msgObj->DIHEntity = ans;
																//printf("\nFROM myMachineID %d:: Giving Yes Reply To CreateCV DYH in Response to %d\n",myMachineID,farSerMachiID);
																ReplyToDYH(farSerMachiID,msgObj);

															}
															else
															{
																msgObj->DIHEntity = ans;

																//Looking in my pending request table

																nameOfEntity=msgObj->nameOfEntity;
																key = GenerateKey(nameOfEntity,(OpCode)msgObj->opcode);

																//cout<<"In ServeRequests CV case.. nameOfEntity: "<<nameOfEntity<<" key: "<<key<<endl;

																//printf("\nReached in the else part of Serve Requests\n");

																//Lock Added later
																PendingQLock->Acquire();
																if(PendingQ.count(key) > 0)
																{
																	//printf("\nIn the if  part of object IS found in map value. Map Count: %d\n",PendingQ.count(key));
																	//Entry for same Entity name with same opcode
																	//printf("\nI have got the entry for key '%s'  in my pendingQ table so now comparing the timestamp.\n",key);
																	PendingQElement* pendQE = PendingQ.find(key)->second;

																	//printf("\nGoing to compare timestamp values for the CREATE LOCK. Values: My TS: %u.  Received Request TS: %u\n",pendQE->myDYHRq->timestamp,msgObj->timestamp);
																	printf("\nGoing to compare timestamp values for the CREATE CV. Values: My 'Server:%d' TS: %u.  Received Request 'Server:%d' TS: %u\n",myMachineID,pendQE->myDYHRq->timestamp,farSerMachiID,msgObj->timestamp);
																	if(pendQE->myDYHRq->timestamp > msgObj->timestamp)
																	{
																		printf("\nMy timestamp is LATER, I 'Serverid: %d' should reply no..\n",myMachineID);
																		ReplyToDYH(farSerMachiID,msgObj);	//If my timestamp is later, then reply NO.
																	}
																	else if(pendQE->myDYHRq->timestamp < msgObj->timestamp)
																	{
																		printf("\nMy timestamp is earlier, then I 'Serverid: %d' should queue the request..\n",myMachineID);
																		//If my timestamp is earlier, then I should queue the request
																		pendQE->pendingDYHCreateMsgs->Append((void *)farSerMachiID);
																	}
																	else
																	{
																		printf("\nBoth the timestamps are same..Tie breaker on the basis of Machine Id..\n");
																		//ASSERT(myMachineID==farSerMachiID);
																		if(myMachineID > farSerMachiID)
																		{
																			printf("\nMy MachineID is LATER, then I should reply no..\n");
																			ReplyToDYH(farSerMachiID,msgObj);	//If my timestamp is later, then reply NO.
																		}
																		else
																		{
																			printf("\nMy MachineID is earlier, then I should queue the request..\n");
																			//If my timestamp is earlier, then I should queue the request
																			pendQE->pendingDYHCreateMsgs->Append((void *)farSerMachiID);
																		}
																	}


																}
																else
																{
																	//printf("\nNo same entry of object found in map. Map Count: %d\n",PendingQ.count(key));
																	ReplyToDYH(farSerMachiID,msgObj);
															    }
																//Added later
																PendingQLock->Release();
															}
													break;



										 case DYHC_MVs:
														 MVTableLock->Acquire();
																//string lockName(msgObj->nameOfEntity);
																 if( IdntHaveIt == lookUpforMVCreate(mvName))
																	 ans=false;
																 else
																	 ans=true;

															 MVTableLock->Release();

															if(ans==true)
															{
																msgObj->DIHEntity = ans;
																//printf("\nFROM myMachineID %d:: Giving Yes Reply To CreateMV DYH in Response to %d\n",myMachineID,farSerMachiID);
																ReplyToDYH(farSerMachiID,msgObj);

															}
															else
															{
																msgObj->DIHEntity = ans;

																//Looking in my pending request table

																nameOfEntity=msgObj->nameOfEntity;
																key = GenerateKey(nameOfEntity,(OpCode)msgObj->opcode);

															//	cout<<"In ServeRequests MV case.. nameOfEntity: "<<nameOfEntity<<" key: "<<key<<endl;

																//printf("\nReached in the else part of Serve Requests\n");

																//Lock Added later
																PendingQLock->Acquire();
																if(PendingQ.count(key) > 0)
																{
																	//printf("\nIn the if  part of object IS found in map value. Map Count: %d\n",PendingQ.count(key));
																	//Entry for same Entity name with same opcode
																	//printf("\nI have got the entry for key '%s'  in my pendingQ table so now comparing the timestamp.\n",key);
																	PendingQElement* pendQE = PendingQ.find(key)->second;

																	//printf("\nGoing to compare timestamp values for the CREATE LOCK. Values: My TS: %u.  Received Request TS: %u\n",pendQE->myDYHRq->timestamp,msgObj->timestamp);
																	printf("\nGoing to compare timestamp values for the CREATE MV. Values: My 'Server:%d' TS: %u.  Received Request 'Server:%d' TS: %u\n",myMachineID,pendQE->myDYHRq->timestamp,farSerMachiID,msgObj->timestamp);
																	if(pendQE->myDYHRq->timestamp > msgObj->timestamp)
																	{
																		printf("\nMy timestamp is LATER, I 'Serverid: %d' should reply no..\n",myMachineID);
																		ReplyToDYH(farSerMachiID,msgObj);	//If my timestamp is later, then reply NO.
																	}
																	else if(pendQE->myDYHRq->timestamp < msgObj->timestamp)
																	{
																		printf("\nMy timestamp is earlier, then I 'Serverid: %d' should queue the request..\n",myMachineID);
																		//If my timestamp is earlier, then I should queue the request
																		pendQE->pendingDYHCreateMsgs->Append((void *)farSerMachiID);
																	}
																	else
																	{
																		printf("\nBoth the timestamps are same..Tie breaker on the basis of Machine Id..\n");
																		//ASSERT(myMachineID==farSerMachiID);
																		if(myMachineID > farSerMachiID)
																		{
																			printf("\nMy MachineID is LATER, then I should reply no..\n");
																			ReplyToDYH(farSerMachiID,msgObj);	//If my timestamp is later, then reply NO.
																		}
																		else
																		{
																			printf("\nMy MachineID is earlier, then I should queue the request..\n");
																			//If my timestamp is earlier, then I should queue the request
																			pendQE->pendingDYHCreateMsgs->Append((void *)farSerMachiID);
																		}
																	}


																}
																else
																{
																	//printf("\nNo same entry of object found in map. Map Count: %d\n",PendingQ.count(key));
																	ReplyToDYH(farSerMachiID,msgObj);
															    }
																//Added later
																PendingQLock->Release();
															}
												  break;

										 //default:
																	//ASSERT(false);


									 }

}

void UpdatePendQ(int farSerMachiID,DYHRq* msgObj)
{
	string nameOfEntity=msgObj->nameOfEntity;
	string key = GenerateKey(nameOfEntity,(OpCode)msgObj->opcode);   //a ? b : c


	PendingQLock->Acquire();
	//cout<<"UpdatePendQ:: myMachineID :"<< myMachineID <<" Received message from "<<farSerMachiID<<" for the key is "<< key << endl;
	//ASSERT(PendingQ.count(key) > 0) ;
			PendingQElement* pendQE = PendingQ.find(key)->second;
			(pendQE->totalCorreResponses)++;
			//ASSERT( strcmp((pendQE->myDYHRq)->nameOfEntity , msgObj->nameOfEntity) == 0);
			if(msgObj->DIHEntity == true)
				{
				   //ASSERT(pendQE->exactOneYes == false);
				   pendQE->exactOneYes=true;
				   pendQE->ownerServer=farSerMachiID;
				  // ASSERT((pendQE->myDYHRq->CMachID > 0 && msgObj->opcode == DYHR_LOCKs_WAIT && msgObj->CMachID <= 0)  || (pendQE->myDYHRq->CMachID == 0 && msgObj->opcode != DYHR_LOCKs_WAIT && msgObj->CMachID == 0));
				   pendQE->myDYHRq->CMachID=msgObj->CMachID; //PERROR ??
				   //ASSERT(pendQE->ownerServer  < totalServers);
				}
	PendingQLock->Release();
}

void ReadSSMailBOX()
{
	PacketHeader outPktHdr, inPktHdr;
	MailHeader outMailHdr, inMailHdr;
	char recBuffer[MaxMailSize]={'\0'};

	//ASSERT(MaxMailSize == sizeof(DYHRq));
	//ASSERT( strlen(recBuffer) == 0);

	postOffice->Receive(SSMailBox, &inPktHdr, &inMailHdr, recBuffer);
	int farSerMachiID=inPktHdr.from;
	//int farSerMailBOX=inMailHdr.from;

	DYHRq* msgObj=new DYHRq;
	StringToStruct(recBuffer,(char *)msgObj);

	if(msgObj->ReqRep == true) // its a request to me
	{
		//printf("\nmyMachineID %d:Received Something on MailBox 1\n",myMachineID);
		ServeReqeusts(farSerMachiID,msgObj);
	}
	else // its a reply my OLD DYH,sent by my SC Thread
	{
		UpdatePendQ(farSerMachiID,msgObj);
	}

	//  delete msgObj; EFFI


}

void ServePendingQ()
{
	PendingQElement* pendQE;
	int pendingLaterTSserverMachineId=-1;
	//printf("\nmyMachineID %d::Before Lock Acquiration in PendingQ of ServePendingQ function\n",myMachineID);
	PendingQLock->Acquire();
			 for ( PendingQiterator=PendingQ.begin() ; PendingQiterator != PendingQ.end(); PendingQiterator++ )//basically iterate thru map & serve all PE which can be
			 {
				 pendQE = (*PendingQiterator).second;
				 if( pendQE->totalCorreResponses == (totalServers-1) ) // I have consistent Distributed System State
						 {
								 short int opcodeOfPE= (pendQE->myDYHRq)->opcode;
								 switch(opcodeOfPE)
								 {
										 case DYHA_LOCKs:   // DYH Non Create Type Acquire,Release
										 case DYHR_LOCKs:

											 						if(pendQE->exactOneYes == true)	
																	 { 
																	 //printf("\nSending Original Message of Client\n");
																	 SendAsIfFromClient(pendQE);  
																	 }
																	 else 					 	 	 	 	 	           
																	{  
																		 SendErrorToClients(pendQE); 
																		 cout<<"\nERROR: No such LOCK Exists:: "<< (pendQE->myDYHRq)->nameOfEntity  <<"\n"; 
																		 //ASSERT(false);
																	}
																	 PendingQ.erase(PendingQiterator);
																	 break;

										 case DYHW_CVs:
										 case DYHS_CVs:
										 case DYHB_CVs:
											 						if(pendQE->exactOneYes == true)	
																	 { 
																	 //printf("\nSending Original Message of Client\n");
																	 SendAsIfFromClient(pendQE);  
																	 }
																	 else 					 	 	 	 	 	           
																	{  
																		 SendErrorToClients(pendQE); 
																		 cout<<"\nERROR: No such CV Exists:: "<< (pendQE->myDYHRq)->nameOfEntity  <<"\n"; 
																		 //ASSERT(false);
																	}
																	 PendingQ.erase(PendingQiterator);
																	 break;
										 case DYHS_MVs:
																	 if(pendQE->exactOneYes == true)	
																	 { 
																	 //printf("\nSending Original Message of Client\n");
																	 SendAsIfFromClient(pendQE);  
																	 }
																	 else 					 	 	 	 	 	           
																	{  
																		 SendErrorToClients(pendQE); 
																		 cout<<"\nERROR: No such MV Exists.."<<endl; 
																		 //ASSERT(false);
																	}
																	 PendingQ.erase(PendingQiterator);
																	 break;

										 case DYHG_MVs:
																	 if(pendQE->exactOneYes == true)	
																	 { 
																		//printf("\nSending Original Message of Client\n");
																		SendAsIfFromClient(pendQE);  
																	 }
																	 else
																	 {  
																		 SendGetMVErrorToClients(pendQE); 
																		 cout<<"\nERROR: No such MV Exists.."<<endl; 
																		 //ASSERT(false);
																	 }
																	 PendingQ.erase(PendingQiterator);
																	 break;

										 case DYHR_LOCKs_WAIT:

											 	 	 	 	 	 	 if(pendQE->exactOneYes == true)
											 	 	 	 	 	 	 	 	 {   
																		 if( pendQE->myDYHRq->CMachID == -90)
																						 {  
																		 SendErrorToClients(pendQE);  
																		 cout<<"\nERROR: in Release of Wait- Lock Ownership Issues Exists for Lock :: "<< (pendQE->myDYHRq)->nameOfEntity  <<"\n"; 
																		 //ASSERT(false);
																		 }
																				 else
																					 {	 /* ASSERT((pendQE->myDYHRq->CMachID == 1) && (pendQE->myDYHRq->CMachID == 3));
																							 printf("\nBefore Remote Wait\n");       */
																							 CVTableLock->Acquire();
																							// ASSERT(pendQE->clientInfoQ->IsEmpty() ==  false);
																									 ClientInfo* clientInfo =  (ClientInfo*)pendQE->clientInfoQ->Remove();
																									// printf("\nAppended Client to CVs Q\n");
																									 cv[pendQE->cvIndex]->waitingLock = pendQE->myDYHRq->nameOfEntity;
																									 cv[pendQE->cvIndex]->conditionQueue->Append((void*)clientInfo);
																									 SendAsIfFromSpecClient(clientInfo, pendQE->ownerServer,"RemoteRelease",pendQE->myDYHRq->nameOfEntity);
																										 // funcWait(-1, pendQE->cvIndex, (ClientInfo*)pendQE->clientInfoQ->Remove());
																							 CVTableLock->Release();
																							 //funcWait(pendQE->CVName, (ClientInfo*)pendQE->clientInfoQ->Remove());
																					 }
											 	 	 	 	 	 	 	 	 }
											 	 	 	 	 	 	 else
											 	 	 	 	 	 	 {  
																		 SendErrorToClients(pendQE);  
																		cout<<"\nERROR: in Release of Wait- No such Lock Exists:: "<< (pendQE->myDYHRq)->nameOfEntity  <<"\n"; 
																		//ASSERT(false);
																	 }
											 	 	 	 	 	 	 PendingQ.erase(PendingQiterator); //PERROR $$$$$$$$
											 	 	 	 	 	 	 break;

										case DYHA_LOCKs_SIG:

											 //printf("\nIn DYHA_LOCKs_SIG of ServePendingQ \n");
																 if(pendQE->exactOneYes == true)
																		 {
																	 	 	 //printf("\nI am inside inteded IF\n");
																	 	 	 if( pendQE->myDYHRq->CMachID == -90)
																					 {  
																				 cout<<"\nERROR: in Acquire of Signal- Lock Ownership is not with Signal-er, Issues Exists for Lock :: "<< (pendQE->myDYHRq)->nameOfEntity  <<"\n";SendErrorToClients(pendQE);   
																				// ASSERT(false);
																				 }
																			 else
																				 {	 /* ASSERT((pendQE->myDYHRq->CMachID == 1) && (pendQE->myDYHRq->CMachID == 3));
																						 printf("\nBefore Remote Wait\n");       */
																						 CVTableLock->Acquire();
																						// ASSERT(pendQE->clientInfoQ->IsEmpty() ==  false);
																						 if(cv[pendQE->cvIndex]->conditionQueue->IsEmpty() == false)
																						 {	     ClientInfo* waiterGettingISgnalled =(ClientInfo*)	cv[pendQE->cvIndex]->conditionQueue->Remove();
																								 SendAsIfFromSpecClient(waiterGettingISgnalled, pendQE->ownerServer,"RemoteAcquire",pendQE->myDYHRq->nameOfEntity);
																						 }
																						 ClientInfo* Signaller = (ClientInfo*)pendQE->clientInfoQ->Remove();
																						 //Delay ???
																						 //printf("\nServe Pending Q:: Signaller Machine ID %d mailBox %d\n",Signaller->machineId,Signaller->mailboxNo);
																						 funcSend(Signaller->machineId, Signaller->mailboxNo, "1");
																									 // funcWait(-1, pendQE->cvIndex, (ClientInfo*)pendQE->clientInfoQ->Remove());
																						 CVTableLock->Release();
																						 //funcWait(pendQE->CVName, (ClientInfo*)pendQE->clientInfoQ->Remove());
																				 }
																		 }
																 else
																		 {  
																	 cout<<"\nERROR: in Acquire of Signal- No such Lock Exists:: "<< (pendQE->myDYHRq)->nameOfEntity  <<"\n"; SendErrorToClients(pendQE);  
																	// ASSERT(false);
																	 }

																 PendingQ.erase(PendingQiterator);  //PERROR $$$$$$$$
																 break;
							   case DYHA_LOCKs_BROAD:
								  						if(pendQE->exactOneYes == true)
																	 {
																		 //printf("\nI am inside inteded IF of DYHA_LOCKs_BROAD\n");
																		 if( pendQE->myDYHRq->CMachID == -90)
																				 {  
																			 cout<<"\nERROR: in Acquire of DYHA_LOCKs_BROAD- Lock Ownership is not with Signal-er, Issues Exists for Lock :: "<< (pendQE->myDYHRq)->nameOfEntity  <<"\n";
																			 SendErrorToClients(pendQE);   
																			 //ASSERT(false);
																			 }
																		 else
																			 {	 /* ASSERT((pendQE->myDYHRq->CMachID == 1) && (pendQE->myDYHRq->CMachID == 3));
																					 printf("\nBefore Remote Wait\n");       */
																					 CVTableLock->Acquire();
																					// ASSERT(pendQE->clientInfoQ->IsEmpty() ==  false);
																					 while(cv[pendQE->cvIndex]->conditionQueue->IsEmpty() == false)
																					 {	     ClientInfo* waiterGettingISgnalled =(ClientInfo*)	cv[pendQE->cvIndex]->conditionQueue->Remove();
																							 SendAsIfFromSpecClient(waiterGettingISgnalled, pendQE->ownerServer,"RemoteAcquire",pendQE->myDYHRq->nameOfEntity);
																					 }
																					 ClientInfo* Signaller = (ClientInfo*)pendQE->clientInfoQ->Remove();
																					 //Delay ???
																					 //printf("\nServe Pending Q:: Signaller Machine ID %d mailBox %d\n",Signaller->machineId,Signaller->mailboxNo);
																					 funcSend(Signaller->machineId, Signaller->mailboxNo, "1");
																								 // funcWait(-1, pendQE->cvIndex, (ClientInfo*)pendQE->clientInfoQ->Remove());
																					 CVTableLock->Release();
																					 //funcWait(pendQE->CVName, (ClientInfo*)pendQE->clientInfoQ->Remove());
																			 }
																	 }
																	 else
																			 {  
																		 cout<<"\nERROR: in Acquire of DYHA_LOCKs_BROAD- No such Lock Exists:: "<< (pendQE->myDYHRq)->nameOfEntity  <<"\n"; 
																		 SendErrorToClients(pendQE);  
																		 //ASSERT(false);
																		 }
								  									PendingQ.erase(PendingQiterator);
								   	   	   	   	   	   	   	   	   break;
								case DYHC_LOCKs:		//Case for Lock
													if(pendQE->exactOneYes == true)
													{
														//printf("\nGot 1 yes from somebody..so replying to client directly\n");
														SendCreateMessageToClients(pendQE,"1");	// "1" is the success ack

														//I must send NO to all clients in my pending queue.

														DYHRq* noRepObj=new DYHRq;
														noRepObj->DIHEntity=false;
														noRepObj->opcode=pendQE->myDYHRq->opcode;
														strcpy(noRepObj->nameOfEntity, pendQE->myDYHRq->nameOfEntity);

														while(pendQE->pendingDYHCreateMsgs->IsEmpty() == false)
														{
															pendingLaterTSserverMachineId=(int) pendQE->pendingDYHCreateMsgs->Remove();

															//Send
															ReplyToDYH(pendingLaterTSserverMachineId,noRepObj);
														}
														//EFFI delete
													}
													else
													{
														//printf("\nGot no from every server..So I must create it\n");

									lockTableLock->Acquire();
														HandleCreateLock(pendQE);
									lockTableLock->Release();
														//cout<<"Locks-Before sending yes to queued ppl...My name of Entity is.."<<pendQE->myDYHRq->nameOfEntity<<endl;
														//I should send YES to all clients in my pending queue since I have created it just now.
														DYHRq* yesRepObj=new DYHRq;

														yesRepObj->DIHEntity=true;
														yesRepObj->opcode=pendQE->myDYHRq->opcode;
														strcpy(yesRepObj->nameOfEntity, pendQE->myDYHRq->nameOfEntity);

														//cout<<"Locks-Printing the name of enntity after strcpy: "<<yesRepObj->nameOfEntity<<endl;

														while(pendQE->pendingDYHCreateMsgs->IsEmpty() == false)
														{
															pendingLaterTSserverMachineId=(int) pendQE->pendingDYHCreateMsgs->Remove();
															//cout<<"Member waiting in pendingDYHCreateMsgs queue of machineId:"<<pendingLaterTSserverMachineId<<endl;
															//Send
															ReplyToDYH(pendingLaterTSserverMachineId,yesRepObj);
														}
														//EFFI delete
													}
													PendingQ.erase(PendingQiterator);
													break;


													case DYHC_CVs:		//case for CV
													if(pendQE->exactOneYes == true)
													{
														//printf("\nGot 1 yes from somebody..so replying to client directly\n");
														SendCreateMessageToClients(pendQE,"1");	// "1" is the success ack

														//I must send NO to all clients in my pending queue.

														DYHRq* noRepObjCV=new DYHRq;
														noRepObjCV->DIHEntity=false;
														noRepObjCV->opcode=pendQE->myDYHRq->opcode;
														strcpy(noRepObjCV->nameOfEntity, pendQE->myDYHRq->nameOfEntity);

														while(pendQE->pendingDYHCreateMsgs->IsEmpty() == false)
														{
															pendingLaterTSserverMachineId=(int) pendQE->pendingDYHCreateMsgs->Remove();

															//Send
															ReplyToDYH(pendingLaterTSserverMachineId,noRepObjCV);
														}
														//EFFI delete
													}
													else
													{
														//printf("\nGot no from every server..So I must create it\n");

									CVTableLock->Acquire();
														HandleCreateCV(pendQE);
									CVTableLock->Release();

														//cout<<"CV-Before sending yes to queued ppl...My name of Entity is.."<<pendQE->myDYHRq->nameOfEntity<<endl;
														//I should send YES to all clients in my pending queue since I have created it just now.
														DYHRq* yesRepObjCV=new DYHRq;

														yesRepObjCV->DIHEntity=true;
														yesRepObjCV->opcode=pendQE->myDYHRq->opcode;
														strcpy(yesRepObjCV->nameOfEntity, pendQE->myDYHRq->nameOfEntity);

														//cout<<"CV-Printing the name of enntity after strcpy: "<<yesRepObjCV->nameOfEntity<<endl;

														while(pendQE->pendingDYHCreateMsgs->IsEmpty() == false)
														{
															pendingLaterTSserverMachineId=(int) pendQE->pendingDYHCreateMsgs->Remove();
															//cout<<"Member waiting in pendingDYHCreateMsgs queue of machineId:"<<pendingLaterTSserverMachineId<<endl;
															//Send
															ReplyToDYH(pendingLaterTSserverMachineId,yesRepObjCV);
														}
														//EFFI delete
													}
													PendingQ.erase(PendingQiterator);
													break;




						case DYHC_MVs:		//case for MV
													if(pendQE->exactOneYes == true)
													{
														//printf("\nGot 1 yes from somebody..so replying to client directly\n");
														SendCreateMessageToClients(pendQE,"2");	// "1" is the success ack

														//I must send NO to all clients in my pending queue.

														DYHRq* noRepObjMV=new DYHRq;
														noRepObjMV->DIHEntity=false;
														noRepObjMV->opcode=pendQE->myDYHRq->opcode;
														strcpy(noRepObjMV->nameOfEntity, pendQE->myDYHRq->nameOfEntity);

														while(pendQE->pendingDYHCreateMsgs->IsEmpty() == false)
														{
															pendingLaterTSserverMachineId=(int) pendQE->pendingDYHCreateMsgs->Remove();

															//Send
															ReplyToDYH(pendingLaterTSserverMachineId,noRepObjMV);
														}
														//EFFI delete
													}
													else
													{
														//printf("\nGot no from every server..So I must create it\n");

									MVTableLock->Acquire();
														HandleCreateMV(pendQE);
									MVTableLock->Release();

														//cout<<"MV-Before sending yes to queued ppl...My name of Entity is.."<<pendQE->myDYHRq->nameOfEntity<<endl;
														//I should send YES to all clients in my pending queue since I have created it just now.
														DYHRq* yesRepObjMV=new DYHRq;

														yesRepObjMV->DIHEntity=true;
														yesRepObjMV->opcode=pendQE->myDYHRq->opcode;
														strcpy(yesRepObjMV->nameOfEntity, pendQE->myDYHRq->nameOfEntity);

														//cout<<"MV-Printing the name of enntity after strcpy: "<<yesRepObjMV->nameOfEntity<<endl;

														while(pendQE->pendingDYHCreateMsgs->IsEmpty() == false)
														{
															pendingLaterTSserverMachineId=(int) pendQE->pendingDYHCreateMsgs->Remove();
															//cout<<"Member waiting in pendingDYHCreateMsgs queue of machineId:"<<pendingLaterTSserverMachineId<<endl;
															//Send
															ReplyToDYH(pendingLaterTSserverMachineId,yesRepObjMV);
														}
														//EFFI delete
													}
													PendingQ.erase(PendingQiterator);
													break;



										// default:
										 						   	//ASSERT(false);


								 }

						}
			 }
    PendingQLock->Release();
    //printf("\nmyMachineID %d::After Lock Release in PendingQ of ServePendingQ function\n",myMachineID);
}

void ServerToServer()
{
	//printf("\nmyMachineID %d::In ServerToServer\n",myMachineID);
	while(true)
	{
		    ServePendingQ();
		    ReadSSMailBOX();
	}

}
