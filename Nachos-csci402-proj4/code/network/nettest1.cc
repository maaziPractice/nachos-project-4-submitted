#include "action.h"
#include "copyright.h"

#include "system.h"
#include "network.h"
#include "post.h"
#include "interrupt.h"


using namespace std;

#define IdntHaveIt -1
#define NOTHING 0

void AddToPendingQ(string passedValue,char* buffer,short int opcode,ClientInfo* addressInformation,int cvIndex)
{
	//cout<<"Inside AddToPendingQ... passedValue: "<<passedValue<<endl;
	 string entityName= GenerateKey(passedValue,(OpCode)opcode);
	//cout<<"Inside AddToPendingQ... entityName: "<<entityName<<endl;
	 PendingQLock->Acquire();
				 if( PendingQ.count(entityName) == 0) //first entry
				 {
					 DYHRq* myDYHRq =new DYHRq;

					 myDYHRq->ReqRep = true;
					 /*
					 RqIDBitMapLock->Acquire();
									myDYHRq->RqID = RqIDBitMap->Find();
					 RqIDBitMapLock->Release();
                     */
					 //ASSERT( strlen(passedValue.c_str()) < 25);
					 strcpy(myDYHRq->nameOfEntity,passedValue.c_str());
					 //ASSERT(	strcmp( myDYHRq->nameOfEntity , passedValue.c_str()) == 0);

					 myDYHRq->opcode=(short int)opcode;

					struct timeval tv;
					struct timezone tz;
					struct tm *tm;
					gettimeofday(&tv, &tz);
					tm=localtime(&tv.tv_sec);
					unsigned int myTimestamp = ((unsigned int)(tv.tv_usec + tv.tv_sec*1000000));
					myDYHRq->timestamp=myTimestamp;
					//cout<<"value of timestamp set in the request is "<<myDYHRq->timestamp<<endl;


					 myDYHRq->CMachID=0;
					 myDYHRq->CmailBOX=0;
					 if( ( opcode == DYHR_LOCKs_WAIT  )   ||     (DYHA_LOCKs_SIG == opcode) ||(DYHA_LOCKs_BROAD== opcode))
					 {  myDYHRq->CMachID = addressInformation->machineId;
						//cout<<"\n Add to PendiQ "<<addressInformation->machineId <<endl;
						 myDYHRq->CmailBOX =addressInformation->mailboxNo;
					 }
					
					int fMachID=addressInformation->machineId;
					int fMailBoxNum=addressInformation->mailboxNo;

					 //printf("Opcode being sent is %u",myDYHRq->opcode);
					 //cout<<"\nIf AddToPendingQ  with myMachineID "<<myMachineID<<"with entityName as "<<entityName<<endl;

					 SendDYH(myDYHRq); //send messages to every other server
					 //delete destDYHRqBuf;
					 //delete myDYHRq;
					 //add to your pendingQ
					 PendingQElement* pendQE=new PendingQElement();
					 //ASSERT(pendQE->totalCorreResponses == 0);
					// pendQE->totalCorreResponses = 0;

					 //ASSERT(pendQE->exactOneYes == false);
					 //pendQE->exactOneYes = false;

					 pendQE->clientInfoQ = new List;
					 pendQE->clientInfoQ->Append((void *)addressInformation);
					 pendQE->myDYHRq = myDYHRq;
					 pendQE->origCliMsg = buffer ; //PERROR

					 pendQE->fMachID=fMachID;
					 pendQE->fMailBoxNum=fMailBoxNum;

					pendQE->cvIndex=cvIndex;

					 //ASSERT((pendQE->origCliMsg).size() == strlen(buffer));
					 //ASSERT(	strcmp(	(pendQE->origCliMsg).c_str()		,buffer )	== 0	);

					 PendingQ.insert(	pair<string,PendingQElement*>(entityName,pendQE)	);

				 }
				 else // I am already in fuzzy state for this Entity
				 {
					 //ASSERT(PendingQ.count(entityName) == 1);
					//printf("\nmyMachineID %d:: Else of AddToPendingQ for Entity %s\n ",myMachineID, entityName.c_str());
					// getchar();
					PendingQElement* pendQE=PendingQ.find(entityName)->second ;
					(pendQE->clientInfoQ)->Append((void *)addressInformation);

					//cout<<"\n pendQE->origCliMsg "<<pendQE->origCliMsg<<endl;
					//cout<<"\n buffer from Client "<<buffer<<endl;
					//ASSERT(	strcmp(	(pendQE->origCliMsg).c_str(),buffer )	== 0		);
				 }

	PendingQLock->Release();


}



void CurrentRequestServent()
{

	    PacketHeader outPktHdr, inPktHdr;
	    MailHeader outMailHdr, inMailHdr;
	    char *ack = "$";
	    //int retVal=-1;
		std::string passedValue,typeIdentifier,ackString,lockPassedValue,cvPassedValue;

		int flagLockCV;
		char buffer[MaxMailSize]={'\0'};
		int tempi,buflen;
		int flagIndexName;

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
		int returnBroadcast=-1;
		int mvIndex=-1;
		//printf("\nCurrentRequestServent\n");

//while(1)
    	{
			        postOffice->Receive(0, &inPktHdr, &inMailHdr, buffer);
					typeIdentifier="";
					typeIdentifier=typeIdentifier+buffer[0]+buffer[1];
					passedValue="";
					buflen=strlen(buffer);      // PERROR ask Shubham,search for strlen(buffer)

					//ASSERT(buflen > 3);
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
					//ASSERT(addressInformation->machineId==inPktHdr.from;);
					addressInformation->mailboxNo=inMailHdr.from;	//CHECK ON THIS..............................................
					int lockIndex=-1, CVIndex=-1, MVIndex=-1; //int lockIndex, cvIndex;

						switch(indentifyVal)
								{
									case 1:		//Create Lock
																lockTableLock->Acquire();
																	lockIndex = lookUpforLock(passedValue);
																lockTableLock->Release();

																if(lockIndex != IdntHaveIt)
																{
																	//I have the lock, so i can straightaway reply to client
																	ackString="1";
																	funcSend(inPktHdr.from, inMailHdr.from, ackString);
																}
																else
																{
																	//I don't have the lock, so I have to put the request to pending queue.
																	AddToPendingQ(passedValue,buffer,DYHC_LOCKs,addressInformation,NOTHING);
																}
																break;

									case 15:
										//printf("\n\nHURRRRRRRRRRRRRRRRRRRAYYYYYYYYYYYY of Remote Acquire\n\n");
									case 2:    //Acquire Lock
												lockTableLock->Acquire();
													lockIndex = lookUpforLock(passedValue);
													//cout<<"Acquire- Got LockName \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;
												if(lockIndex != IdntHaveIt)
													{	//int lockToBeAcquiredIndex=atoi(passedValue.c_str());
														lockToBeAcquiredName=passedValue;

														int retAcquire=funcAcquire(lockToBeAcquiredName, addressInformation);
														if(indentifyVal == 2)
														{
																	if(retAcquire==1 || retAcquire==3)
																				{
																					ackString="-1";
																					//ASSERT(retAcquire==3);
																					funcSend(inPktHdr.from, inMailHdr.from, ackString);
																				}
																				else if (retAcquire==2)  //when Lock is free
																				{
																					ackString="1";
																					funcSend(inPktHdr.from, inMailHdr.from, ackString);
																				}
														}

														lockTableLock->Release();
														//delete addressInformation;  Since you are going to store it in owner Information of the Lock
												}
												else  //I d'nt have the Lock so send DYHA_LOCKs
												{
													lockTableLock->Release();
													lockToBeAcquiredName=passedValue; //PERROR ask why to Shubham??
													AddToPendingQ(lockToBeAcquiredName,buffer,DYHA_LOCKs,addressInformation,NOTHING);
												}


										break;

									case 14:
												//printf("\n\nHURRRRRRRRRRRRRRRRRRRAYYYYYYYYYYYY of Remote Release\n\n");
									case 3: // Release lock DYHR_LOCKs
										lockTableLock->Acquire();
											lockIndex = lookUpforLock(passedValue);
											//cout<<"\nRelease- Got LockName \""<<passedValue<<"\" from "<<inPktHdr.from<<", box "<<inMailHdr.from<< endl;
										if(lockIndex != IdntHaveIt)   //so I have the lock
											{
														//int lockToBeReleasedIndex=atoi(passedValue.c_str());
														lockToBeReleasedName=passedValue;

														int retRelease=funcRelease(lockToBeReleasedName, addressInformation);
														if(indentifyVal == 3)
														{	if(retRelease==1 || retRelease==2 || retRelease==4)
																{
																	ackString="-1";
																	//ASSERT(retRelease != 1);
																	funcSend(inPktHdr.from, inMailHdr.from, ackString);
																}
																else if (retRelease==3)  //check it $$$$$$$$$$$
																{
																	ackString="1";
																	funcSend(inPktHdr.from, inMailHdr.from, ackString);
																}
														}
														lockTableLock->Release();
														//delete addressInformation;    Effi

											}
										else  //I d'nt have the Lock DYHR_LOCKs
											{
											    lockTableLock->Release();
												lockToBeAcquiredName=passedValue; //PERROR ask why to Shubham??
												AddToPendingQ(lockToBeAcquiredName,buffer,DYHR_LOCKs,addressInformation,NOTHING);
											}

										break;

									case 4:		//Create CV
																			CVTableLock->Acquire();
																				CVIndex = lookUpforCV(passedValue);
																			CVTableLock->Release();

																			if(CVIndex != IdntHaveIt) //so create it
																			{
																				//I have the CV, so i can straightaway reply to client
																				ackString="1";
																				funcSend(inPktHdr.from, inMailHdr.from, ackString);
																				}

																			else
																			{
																				//I don't have the CV, so I have to put the request to pending queue.
																				AddToPendingQ(passedValue,buffer,DYHC_CVs,addressInformation,NOTHING);
																			}
																			break;

									case 5:		//Wait
												cvPassedValue="";lockPassedValue="";flagLockCV=0;
													for(unsigned int i=0;i<passedValue.size();i++){  //Segregating the lock and cv id
																if(passedValue[i]=='+')  {
																	flagLockCV=1;
																	continue;
																}
																if(flagLockCV==0){
																	cvPassedValue+=passedValue[i];
																}
																else
																{
																	lockPassedValue+=passedValue[i];
																}
													}
													//printf("\nhey 1\n");
													CVTableLock->Acquire();
													//printf("\nhey 2\n");
														CVIndex = lookUpforCV(cvPassedValue);
													if(CVIndex != IdntHaveIt) //so I have CV
													{

														//printf("\nhey 1\n");
														if(cv[CVIndex]->waitingLock != "")//CV yet does not belong to any monitor or Lock
																		{
																		//printf("\nhey 122\n");
																				if (cv[CVIndex]->waitingLock != lockPassedValue)
																				{
																					printf("\nERROR: Wait- The lock passed is not same as the waiting lock\n");
																				      //Send Error to Client
																						ackString="-1";
																						funcSend(inPktHdr.from, inMailHdr.from, ackString);
																						//delete addressInformation;
																						CVTableLock->Release();
																						break;
																				}
																		}

														lockTableLock->Acquire();
														lockIndex= lookUpforLock(lockPassedValue);
																if(lockIndex != IdntHaveIt)  //so I have Lock
																{
																	//shubham code
																	//printf("\nIn Shubham's Code 123\n");
																	int retWaitVal = funcWait(lockIndex, CVIndex, addressInformation);

																	lockTableLock->Release();
																	CVTableLock->Release();
																				if (retWaitVal==-1)
																				{
																					ackString="-1";
																	//				printf("\nIn Shubham's Code before Send\n");
																					funcSend(inPktHdr.from, inMailHdr.from, ackString);
																				}

																}
																else
																{
																	lockTableLock->Release();
																	CVTableLock->Release();
																	//Remotely Release
																	//ask who has lock,tell him to release it on behalf of client
																	//printf("\nIn proper else\n");
																	AddToPendingQ(lockPassedValue,buffer,DYHR_LOCKs_WAIT,addressInformation,CVIndex);
																}
													}
													else  //I d'nt have the CV DYHA_LOCKs
													{
														CVTableLock->Release();
														//cout<<"I d'nt have the CV DYHA_LOCKs"<<endl;
														string cvName=cvPassedValue; //PERROR ask why to Shubham??
														AddToPendingQ(cvName,buffer,DYHW_CVs,addressInformation,NOTHING);
													}
										break;


									case 6: // Signal
										cvPassedValue="";lockPassedValue="";flagLockCV=0;
											for(unsigned int i=0;i<passedValue.size();i++){  //Segregating the lock and cv id
														if(passedValue[i]=='+')  {
															flagLockCV=1;
															continue;
														}
														if(flagLockCV==0){
															cvPassedValue+=passedValue[i];
														}
														else
														{
															lockPassedValue+=passedValue[i];
														}
											}
											//printf("\nhey 1\n");
											CVTableLock->Acquire();
											//printf("\nhey 2\n");
												CVIndex = lookUpforCV(cvPassedValue);
											if(CVIndex != IdntHaveIt) //so I have CV
											{
												//printf("\nhey 1\n");
												if(cv[CVIndex]->waitingLock != "")//CV yet does not belong to any monitor or Lock
																{
																//printf("\nhey 122\n");
																		if (cv[CVIndex]->waitingLock != lockPassedValue)
																		{
																			printf("\nERROR: SIGNAL- The lock passed is not same as the waiting lock\n");
																			//printf("\nhey 13\n");
																			  //Send Error to Client
																				ackString="-1";
																				funcSend(inPktHdr.from, inMailHdr.from, ackString);
																				//delete addressInformation;
																				CVTableLock->Release();
																				break;
																		}
																}

												lockTableLock->Acquire();
												lockIndex= lookUpforLock(lockPassedValue);
														if(lockIndex != IdntHaveIt)  //so I have Lock
														{
															//shubham code
															//printf("\nIn Shubham's Code 123\n");
															int retSigVal = funcSignal(lockIndex, CVIndex, addressInformation);

															lockTableLock->Release();
															CVTableLock->Release();
															 if(retSigVal==2)
																{
																	ackString="1";
																	funcSend(inPktHdr.from, inMailHdr.from, ackString);
																}
																else if (retSigVal==1)
																{
																	ackString="-1";
																	funcSend(inPktHdr.from, inMailHdr.from, ackString);
																}
														}
														else
														{
															lockTableLock->Release();
															CVTableLock->Release();
															//Remotely Release
															//ask who has lock,tell him to release it on behalf of client
															//printf("\nIn proper else for Signal\n");
															AddToPendingQ(lockPassedValue,buffer,DYHA_LOCKs_SIG,addressInformation,CVIndex);
														}
											}
											else  //I d'nt have the CV DYHA_LOCKs
											{
												CVTableLock->Release();
												//cout<<"I d'nt have the CV DYHA_LOCKs"<<endl;
												string cvName=cvPassedValue; //PERROR ask why to Shubham??
												AddToPendingQ(cvName,buffer,DYHS_CVs,addressInformation,NOTHING);
											}


										break;



									case 7://broadcast
													cvPassedValue="";				lockPassedValue="";			flagLockCV=0;
													for(unsigned int i=0;i<passedValue.size();i++)
													{if(passedValue[i]=='+')						{
															flagLockCV=1;					continue;												}
														if(flagLockCV==0)														{
															cvPassedValue+=passedValue[i];														}
														else														{
															lockPassedValue+=passedValue[i];
														}
													}
													CVTableLock->Acquire();				CVIndex = lookUpforCV(cvPassedValue);
														if(CVIndex != IdntHaveIt) //so I have CV
														{
															if(cv[CVIndex]->waitingLock != "")//CV yet does not belong to any monitor or Lock
																			{
																					if (cv[CVIndex]->waitingLock != lockPassedValue)
																					{
																						
																						  printf("\nERROR: Broadcast waitingLock is not the same lock as of CV \n");
																							ackString="-1";
																							funcSend(inPktHdr.from, inMailHdr.from, ackString);
																							//delete addressInformation;																							
																							CVTableLock->Release();
																							//cout<<"cv[CVIndex]->waitingLock: "<<cv[CVIndex]->waitingLock<< "lockPassedValue: "<<lockPassedValue<<endl;
																							//ASSERT(false);
																							break;
																					}
																			}

															lockTableLock->Acquire();
															lockIndex= lookUpforLock(lockPassedValue);
																	if(lockIndex != IdntHaveIt)  //so I have Lock
																	{
																		//shubham code
																		//printf("\nIn Shubham's Code 123\n");
																		 returnBroadcast = funcBroadcast(lockIndex, CVIndex, addressInformation);
																		lockTableLock->Release();
																		CVTableLock->Release();

																		 if(returnBroadcast !=2)
																			{
																				//cout<<"returnBroadcast: "<<returnBroadcast<<endl;
																				ackString="-1";
																				funcSend(inPktHdr.from, inMailHdr.from, ackString);
																				//ASSERT(false);
																			}
																			else
																			{
																				ackString="1";
																				funcSend(inPktHdr.from, inMailHdr.from, ackString);
																			}
																	}
																	else
																	{
																		lockTableLock->Release();
																		CVTableLock->Release();
																		//Remotely Release
																		//ask who has lock,tell him to release it on behalf of client
																		//printf("\nIn proper else for Broadcast\n");
																		AddToPendingQ(lockPassedValue,buffer,DYHA_LOCKs_BROAD,addressInformation,CVIndex);
																	}
														}
														else  //I d'nt have the CV DYHA_LOCKs
														{
															CVTableLock->Release();
															//cout<<"I d'nt have the CV DYHB_CVs"<<endl;
															string cvName=cvPassedValue; //PERROR ask why to Shubham??
															AddToPendingQ(cvName,buffer,DYHB_CVs,addressInformation,NOTHING);
														}


													break;


									case 10:	// CreateMV

												//cout<<"\n CreateMV: Got String: "<<passedValue<<" From "<<inPktHdr.from<<", Box: "<<inMailHdr.from<<endl;
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

												MVTableLock->Acquire();
													MVIndex = lookUpforMVCreate(passedValue);
												MVTableLock->Release();

												if(MVIndex != IdntHaveIt) //I have it
												{
													//I have the CV, so i can straightaway reply to client
													ackString="2";
													funcSend(inPktHdr.from, inMailHdr.from, ackString);
												}

												else
												{
													//I don't have the MV, so I have to put the request to pending queue.
													AddToPendingQ(passedValue,buffer,DYHC_MVs,addressInformation,NOTHING);
												}
												break;



									case 11:   //setMV
										mvIDPassedValue="";	mvArrayIndexPassedValue="";	mvAssignValuePassedValue=""; flagLengthIndexNameValue=0;
													for(unsigned int i=0;i<passedValue.size();i++)
													{if(passedValue[i]=='=')	{flagLengthIndexNameValue=2;
															continue;
														}else if (passedValue[i]=='@')
														{
															flagLengthIndexNameValue=3;
															continue;
														}if(flagLengthIndexNameValue==0)
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
													mvArrayIndexInt=atoi(mvArrayIndexPassedValue.c_str());
													mvAssignValueInt=atoi(mvAssignValuePassedValue.c_str());
													MVTableLock->Acquire();
															 mvIndex =	lookUpforMV(passedValue);
															if(mvIndex != IdntHaveIt)
															{
																if(mv[mvIndex]->mvSize <= mvArrayIndexInt)
																				{		//send error to client
																					cout<<"\nThe MV Size is lesser than the index passed..";
																						MVTableLock->Release();
																						funcSend(inPktHdr.from, inMailHdr.from, "-1");
																				}
																else
																				{		funcSetMV(mvIndex, mvArrayIndexInt, mvAssignValueInt, addressInformation);
																						MVTableLock->Release();
																						funcSend(inPktHdr.from, inMailHdr.from, "1");
																				}
															}else if(mvIndex == IdntHaveIt)
															{
																MVTableLock->Release();
																//send DYH_MVs
																AddToPendingQ(passedValue,buffer,DYHS_MVs,addressInformation,NOTHING);
															}

										break;

									case 12://GetMV
										mvIDPassedValue="";	mvArrayIndexPassedValue="";	mvAssignValuePassedValue=""; flagIndexName=0;
									for(unsigned int i=0;i<passedValue.size();i++)
									{if(passedValue[i]=='=')
										{	flagIndexName=2;continue;	}
										if(flagIndexName==0)	{	mvIDPassedValue+=passedValue[i];					}
										else if (flagIndexName==2)		{			mvArrayIndexPassedValue+=passedValue[i];		}						}

										mvArrayIndexInt=atoi(mvArrayIndexPassedValue.c_str());
													MVTableLock->Acquire();
															 mvIndex =	lookUpforMV(passedValue);
															if(mvIndex != IdntHaveIt)
															{	if(mv[mvIndex]->mvSize <= mvArrayIndexInt)
																				{		//send error to client
																cout<<"\nThe MV Size is lesser than the index passed..";
																						MVTableLock->Release();
																						funcSend(inPktHdr.from, inMailHdr.from, "-100");
																				//cout<<"mv[mvIndex]->mvSize:"<<mv[mvIndex]->mvSize<<"  mvArrayIndexInt:"<<mvArrayIndexInt<<"mv[mvIndex]->name"<<mv[mvIndex]->name<<endl;
																						//ASSERT(false);
																				}
																else
																				{		int retGetVal= mv[mvIndex]->mvValue[mvArrayIndexInt];
																							ackString="";	sprintf(ack,"%d",retGetVal);//ackString="GET_SSUCCES";
																							for(unsigned int i=0;i<strlen(ack);i++)
																							{			ackString+=ack[i];					}
																							funcSend(inPktHdr.from, inMailHdr.from, ackString);
																						MVTableLock->Release();
																				}
															}else if(mvIndex == IdntHaveIt)
															{
																MVTableLock->Release();				//send DYH_MVs
																AddToPendingQ(passedValue,buffer,DYHG_MVs,addressInformation,NOTHING);
															}

										break;



								}


    	}

}
