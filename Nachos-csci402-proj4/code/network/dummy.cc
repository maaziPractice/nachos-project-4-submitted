/*
 * d.cc
 *
 *  Created on: Nov 16, 2011
 *      Author: Mayur
 */




int funcWait(string lockName, string cvName, ClientInfo *addressInformation)
{

	if(cv[CVIndex]->waitingLock != "")//CV yet does not belong to any monitor or Lock
					{
							if (cv[CVIndex]->waitingLock != lockPassedValue)
							{//Send Error to Client
									ackString="-1";
									funcSend(inPktHdr.from, inMailHdr.from, ackString);
									delete addressInformation;
									CVTableLock->Release();
									break;
							}
					}







/*ask other server & get this info by sending out DYH for Lock & its ownership !!, one repying yes will send both in its reply
	if (lock[lockIndex]->ownerInfo->machineId != addressInformation->machineId && lock[lockIndex]->ownerInfo->mailboxNo != addressInformation->mailboxNo)
		{
			cout<<"\nWait- ERROR:: You are not the lock owner..";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
			return -1;
		}

		if (cv[cvIndex]->waitingLock == -1)		//Not an Error Condition, since first thread calling wait
		{
			 //cout<<"This is the first thread calling wait.\n";
			 cv[cvIndex]->waitingLock=lockIndex;
		}

		if (cv[cvIndex]->waitingLock!=lockIndex)
		{
			cout<<"\nWait- ERROR:: The waiting Lock is not same as the condition Lock";
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
			return -1;
		}

		//Releasing the lock before going to wait
		printf("\nWait- Going to Wait on CV Index '%d' so will release the lockIndex '%d'",cvIndex,lockIndex);
					cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;

		int releaseOnWait=funcRelease(lockName, addressInformation);	//$$$$$$CHANGED THE LINE

		if(releaseOnWait==3)
		{
			//printf("\nWait- lockIndex '%d' released successfully. Now going to wait\n",lockIndex);
			cv[cvIndex]->conditionQueue->Append((void*)addressInformation);
		}
		else
		{
			printf("\nWait- ERROR:: lockIndex '%d' CANNOT be released. NOT going on wait",lockIndex);
						cout<<" for machine: "<<addressInformation->machineId<<" box: "<<addressInformation->mailboxNo<<endl;
			return -1;
		}
		return 1;








}
