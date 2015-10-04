// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

#include <stdio.h>
#include <iostream>

#ifdef NETWORK
#include "post.h"
#endif

#include "network.h"


using namespace std;

int currentTLBIndex=0;
bool pbool[5]={false,false,false,false,false};

int copyin(unsigned int vaddr, int len, char *buf) {
    // Copy len bytes from the current thread's virtual address vaddr.
    // Return the number of bytes so read, or -1 if an error occors.
    // Errors can generally mean a bad virtual address was passed in.
    bool result;
    int n=0;			// The number of bytes copied in
    int *paddr = new int;

    while ( n >= 0 && n < len) {
      result = machine->ReadMem( vaddr, 1, paddr );
      while(!result) // FALL 09 CHANGES
	  {
   			result = machine->ReadMem( vaddr, 1, paddr ); // FALL 09 CHANGES: TO HANDLE PAGE FAULT IN THE ReadMem SYS CALL
	  }	
      
      buf[n++] = *paddr;
     
      if ( !result ) {
	//translation failed
	return -1;
      }

      vaddr++;
    }

    delete paddr;
    return len;
}


int copyout(unsigned int vaddr, int len, char *buf) {
    // Copy len bytes to the current thread's virtual address vaddr.
    // Return the number of bytes so written, or -1 if an error
    // occors.  Errors can generally mean a bad virtual address was
    // passed in.
    bool result;
    int n=0;			// The number of bytes copied in

    while ( n >= 0 && n < len) {
      // Note that we check every byte's address
      result = machine->WriteMem( vaddr, 1, (int)(buf[n++]) );

      if ( !result ) {
	//translation failed
	return -1;
      }

      vaddr++;
    }

    return n;
}



void Create_Syscall(unsigned int vaddr, int len) {
    // Create the file with the name in the user buffer pointed to by
    // vaddr.  The file name is at most MAXFILENAME chars long.  No
    // way to return errors, though...
    char *buf = new char[len+1];	// Kernel buffer to put the name in

    if (!buf) return;

    if( copyin(vaddr,len,buf) == -1 ) {
	printf("%s","Bad pointer passed to Create\n");
	delete buf;
	return;
    }

    buf[len]='\0';

    fileSystem->Create(buf,0);
    delete[] buf;
    return;
}

int Open_Syscall(unsigned int vaddr, int len) {
    // Open the file with the name in the user buffer pointed to by
    // vaddr.  The file name is at most MAXFILENAME chars long.  If
    // the file is opened successfully, it is put in the address
    // space's file table and an id returned that can find the file
    // later.  If there are any errors, -1 is returned.
    char *buf = new char[len+1];	// Kernel buffer to put the name in
    OpenFile *f;			// The new open file
    int id;				// The openfile id

    if (!buf) {
	printf("%s","Can't allocate kernel buffer in Open\n");
	return -1;
    }

    if( copyin(vaddr,len,buf) == -1 ) {
	printf("%s","Bad pointer passed to Open\n");
	delete[] buf;
	return -1;
    }

    buf[len]='\0';

    f = fileSystem->Open(buf);
    delete[] buf;

    if ( f ) {
	if ((id = currentThread->space->fileTable.Put(f)) == -1 )
	    delete f;
	return id;
    }
    else
	return -1;
}


int copyinWithNullEnding(unsigned int vaddr, char *buf) {
    // Copy len bytes from the current thread's virtual address vaddr.
    // Return the number of bytes so read, or -1 if an error occors.
    // Errors can generally mean a bad virtual address was passed in.
    bool result;
    			// The number of bytes copied in
    int *paddr = new int;
     int n=0;
     //int len = 1;
     result = machine->ReadMem( vaddr, 1, paddr );
     result = machine->ReadMem( vaddr, 1, paddr );
          while(!result) // FALL 09 CHANGES
    	  {
       			result = machine->ReadMem( vaddr, 1, paddr ); // FALL 09 CHANGES: TO HANDLE PAGE FAULT IN THE ReadMem SYS CALL
    	  }



    // ASSERT(result);
	 buf[n]= *paddr; 
     while ( buf[n] != '\0') {
	      n++; vaddr++;
	      result = machine->ReadMem( vaddr, 1, paddr );
	      result = machine->ReadMem( vaddr, 1, paddr );
	           while(!result) // FALL 09 CHANGES
	     	  {
	        			result = machine->ReadMem( vaddr, 1, paddr ); // FALL 09 CHANGES: TO HANDLE PAGE FAULT IN THE ReadMem SYS CALL
	     	  }

	// 	  ASSERT(result);
	      buf[n] = *paddr;	    
	      ASSERT(n<300);

     }
    
    delete paddr;
    return n+1;
}



void Sprint_Syscall(unsigned int userString,unsigned int basicName,int index)
{

    char indexString[5], buf[200];
	sprintf(indexString,"%d",index);
//	printf("\n\n%s\n\n",indexString);
	copyinWithNullEnding(basicName,buf);

	strcat(buf,indexString);
	
	int len=strlen(buf);

//	printf("buf after concat :: %s & len is %d",buf,len);
	copyout(userString,len ,buf);
	machine->WriteMem(userString + len,1,0);

	char buf2[200];
	copyinWithNullEnding(userString,buf2);	//can be removed
//	printf("\nI am in Sprint_Syscall: %s\n",buf2);

}



void Print_Syscall(unsigned int vaddr, int int1, int int2,int int3) {
    // Write the buffer to the given disk file.  If ConsoleOutput is
    // the fileID, data goes to the synchronized console instead.  If
    // a Write arrives for the synchronized Console, and no such
    // console exists, create one. For disk files, the file is looked
    // up in the current address space's open file table and used as
    // the target of the write.
    
    char *buf;		// Kernel buffer for output
    int len;
    int arg[5];
    int OnlyOnesMSB=-65536;
    int OnlyOnesLSB=65535;    
   
    arg[0]=int1;
    arg[1]=(int2 & OnlyOnesMSB) >> 16; 
    arg[2]=(int2 & OnlyOnesLSB);
    arg[3]=(int3 & OnlyOnesMSB) >> 16;   // printf("\nwith u=%u  d=%d\n",arg[0],arg[0]);
    arg[4]=(int3 & OnlyOnesLSB) ;
    int argIndex=0;
    if ( !(buf = new char[300]) ) {
	printf("%s","Error allocating kernel buffer for write!\n");
	return;
    } else {
        if ( (len=copyinWithNullEnding(vaddr,buf)) == -1 ) {
	    printf("%s","Tooo Small string Passed to print\n");
	    delete[] buf;
	    return;
	  }
    }
    
   //printf("\n\n\n\nI am in prin2 %s \n\n\n\n\n",buf);
   
      for (int ii=0; ii<len; ii++) {
		
		if(ii==1)
			printf(" Process %d - ",currentThread->space->myPID);
      	
		if((buf[ii]=='%') && (buf[ii+1]=='d'))
      	   {
      	   	printf("%d",arg[argIndex++]);ii++;
      	   }
		else		
		   printf("%c",buf[ii]);
      }
		delete[] buf;
		
} 

    
void Write_Syscall(unsigned int vaddr, int len, int id) {
    
    char *buf;		// Kernel buffer for output
    OpenFile *f;	// Open file for output

    if ( id == ConsoleInput) return;
    
    if ( !(buf = new char[len]) ) {
	printf("%s","Error allocating kernel buffer for write!\n");
	return;
    } else {
        if ( copyin(vaddr,len,buf) == -1 ) {
	    printf("%s","Bad pointer passed to to write: data not written\n");
	    delete[] buf;
	    return;
	}
    }

    if ( id == ConsoleOutput) {
      for (int ii=0; ii<len; ii++) {
	printf("%c",buf[ii]);
      }

    } else {
	if ( (f = (OpenFile *) currentThread->space->fileTable.Get(id)) ) {
	    f->Write(buf, len);
	} else {
	    printf("%s","Bad OpenFileId passed to Write\n");
	    len = -1;
	}
    }

    delete[] buf;
}

int Read_Syscall(unsigned int vaddr, int len, int id) {
    // Write the buffer to the given disk file.  If ConsoleOutput is
    // the fileID, data goes to the synchronized console instead.  If
    // a Write arrives for the synchronized Console, and no such
    // console exists, create one.    We reuse len as the number of bytes
    // read, which is an unnessecary savings of space.
    char *buf;		// Kernel buffer for input
    OpenFile *f;	// Open file for output

    if ( id == ConsoleOutput) return -1;
    
    if ( !(buf = new char[len]) ) {
	printf("%s","Error allocating kernel buffer in Read\n");
	return -1;
    }

    if ( id == ConsoleInput) {
      //Reading from the keyboard
      scanf("%s", buf);

      if ( copyout(vaddr, len, buf) == -1 ) {
	printf("%s","Bad pointer passed to Read: data not copied\n");
      }
    } else {
	if ( (f = (OpenFile *) currentThread->space->fileTable.Get(id)) ) {
	    len = f->Read(buf, len);
	    if ( len > 0 ) {
	        //Read something from the file. Put into user's address space
  	        if ( copyout(vaddr, len, buf) == -1 ) {
		    printf("%s","Bad pointer passed to Read: data not copied\n");
		}
	    }
	} else {
	    printf("%s","Bad OpenFileId passed to Read\n");
	    len = -1;
	}
    }

    delete[] buf;
    return len;
}

void Close_Syscall(int fd) {
    // Close the file associated with id fd.  No error reporting.
    OpenFile *f = (OpenFile *) currentThread->space->fileTable.Remove(fd);

    if ( f ) {
      delete f;
    } else {
      printf("%s","Tried to close an unopen file\n");
    }
}

//Lock & CVs related START, Also Rand included

int Rand_Syscall(int limit) {

   return(rand()%limit);
}


int Scan_Syscall()
{
	int val;
	cout<<"currentThread->myMailboxNum "<<currentThread->myMailboxNum<<endl;
	scanf("%d", &val);
	return val;
}


/*
int CreateLock_Syscall(unsigned int lockName,int length) {
if(length <= 1)
{		printf("\nERROR - CreateLock::Length of Name of a Lock can't be negative\n");
	    return -1;
}
char* buf=new char[length+1];
if(buf==NULL) return -1;

 if(copyin(lockName,length,buf)== -1)
 {
 		printf("\nERROR - CreateLock::Bad pointer passed to CreateLock\n");
	    delete[] buf;
	    return -1;
 }
 buf[length]='\0';
 
int currentLockIndex=-1;
//printf("\nControll reached CreateLock Sys Call 1!!!!\n");


//Acquire Kernel Lock table Lock
osLockTableLock->Acquire();
if(nextLockLocation < MAX_LOCKS)
  {
	  	osLockTable[nextLockLocation]=new KernelLock;

	  	osLockTable[nextLockLocation]->lock=new Lock(buf);
	  	osLockTable[nextLockLocation]->addrSpace=currentThread->space;
	  	osLockTable[nextLockLocation]->isAlreadyDeleted=false;
	  	osLockTable[nextLockLocation]->isToBeDeleted=false;
	  	osLockTable[nextLockLocation]->noOfUsers=0;
	  	//printf("User gave the locks name as %s,  %d",buf,nextLockLocation);
	  	currentLockIndex=nextLockLocation;
	  	nextLockLocation++;
		
		osLockTableLock->Release();
		
		//printf("\nValue being returned is %d\n",currentLockIndex);
		return currentLockIndex;
  }
  else
  {
	  printf("\nERROR - CreateLock:::No NEW Lock can be created!!, as max limit has been reached\n"); 
	  osLockTableLock->Release();
	  return -1;
  }
//make its entry into Kernel Lock table, you should know its empty index entry

}
*/

#ifdef NETWORK

int CreateLock_Syscall(unsigned int lockName)
{

	int length=50;
	//printf("Inside Createlock %d\n",servMachID);

	char* buf=new char[length];

	if(buf==NULL) return -1;

	 if(copyinWithNullEnding(lockName,buf)== -1)
	 {
			printf("\nERROR - CreateLock::Bad pointer passed to CreateLock\n");
			delete[] buf;
			return -1;
	 }
	 buf[length]='\0';

	char* bufNew=new char[length+3];
	bufNew[0]='0';
	bufNew[1]='1';

	for(int i=0;i<length;i++)
	{
		bufNew[i+2]=buf[i];
	}

	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize];

    // construct packet, mail header for original message
    // To: destination machine, mailbox 0
    // From: our machine, reply to: mailbox 1
    
	//SERVER IS ALWAYS MACHINE 1
	int farAddr=1;
	outPktHdr.to = rand()%totalServers;//servMachID;//farAddr;
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(bufNew) + 1;
    outPktHdr.from= myMachineID;

	//printf("Before send\n");
    // Send the first message
    bool success = postOffice->Send(outPktHdr, outMailHdr, bufNew);
	//printf("After send\n");

    if ( !success ) {
      printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
      interrupt->Halt();
    }

	//printf("After send from MailTest1 \n");
    // Wait for the first message from the other machine
    postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);
    //printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
    fflush(stdout);
	int bufferIntVal=atoi(buffer);

	if(bufferIntVal==-1)
		printf("\nERROR: CreateLock_Syscall- LOCK CREATION FAILURE..\n");


	return bufferIntVal;
}
#endif

/*
int Acquire_Syscall(int lockID)
{
	//printf("\nI am in Acquire with lockID as %d\n",lockID);
	if( (lockID > MAX_LOCKS) || (lockID < 0) )
	{
		printf("\nERROR - Acquire::Invalid Lock ID,out of range\n");
		return -1;
	}

	osLockTableLock->Acquire();
	KernelLock* requestedKernelLock=osLockTable[lockID];
	if(requestedKernelLock==NULL)
	{
		printf("\nERROR - Acquire::Invalid Lock ID..NULL value ..\n");
		osLockTableLock->Release();
		return -1;
	}
	
	if(requestedKernelLock->addrSpace != currentThread->space)
	{
		printf("\nERROR - Acquire:: Sorry...This lock does not belong to your process, so you cant acquire it\n");
		osLockTableLock->Release();
		return -1;
	}

	if(requestedKernelLock->lock->lockOwner == currentThread)
	{
		printf("\nERROR - Acquire:: You Already Own the LOCK!!!!!\n");
		osLockTableLock->Release();
		return -1;
	
	}
	//if isToBeDeleted is true do not entertain any new request for acquire of this lock
	(requestedKernelLock->noOfUsers)++;
	    osLockTableLock->Release();


     bool isSuccess=(requestedKernelLock->lock)->Acquire();
     
	 osLockTableLock->Acquire();
	 
	 if(isSuccess==false) (requestedKernelLock->noOfUsers)--;

	 if( (requestedKernelLock->noOfUsers == 0)  &&  (requestedKernelLock->isToBeDeleted==true) )
	 {		 //DestroyLock(lockID);
		//delete requestedKernelLock->Lock;
		 delete requestedKernelLock;
		 osLockTable[lockID]=NULL;
	 }
	osLockTableLock->Release();
	
return 1;

}
*/

#ifdef NETWORK
int Acquire_Syscall(unsigned int lockName)
{
	//printf("CS:vLock Name is  serverID",servMachID);
	int length=50;
	//printf("Inside Acquire_Syscall\n");
	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize], data[MaxMailSize];
	strcpy(data,"02");


	char* buf=new char[length];

	if(buf==NULL) return -1;

	 if(copyinWithNullEnding(lockName,buf)== -1)
	 {
			printf("\nERROR - Acquire::Bad pointer passed.\n");
			delete[] buf;
			return -1;
	 }
	 buf[length]='\0';
	// printf("\nCS:vLock Name is %s & serverID %d\n",(char*)buf,servMachID);

	//sprintf(charLockID,"%d",lockID);
	strcat(data,buf);
//	cout<<"LockID in string is "<<data<<endl;

 	//SERVER IS ALWAYS MACHINE 1
	int farAddr=1;
	outPktHdr.to = rand()%totalServers;//servMachID;// farAddr;
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(data) + 1;
    outPktHdr.from= myMachineID;

  //  printf("Inside Acquire_Syscall BEFORE SEND for MailBox %d\n",currentThread->myMailboxNum);
    bool success = postOffice->Send(outPktHdr, outMailHdr, data); 

    if ( !success ) {
      printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
      interrupt->Halt();
    }

    postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);

    int bufferIntVal=atoi(buffer);
	if(bufferIntVal==-1)
	{
		printf("\nERROR: Acquire_Syscall- ACQUIRE FAILURE. MailBox with ID %d\n",currentThread->myMailboxNum);
	}

	fflush(stdout);
	return 1;
}
#endif

/*
int Release_Syscall(unsigned int lockID)
{
	//printf("\nI am in Release\n");
	
	if( (lockID > MAX_LOCKS) || (lockID < 0) )
	{
	printf("\nERROR - Release::Invalid Lock ID, out of range\n");
	return -1;
	}

	osLockTableLock->Acquire();
	KernelLock* requestedKernelLock=osLockTable[lockID];
	if(requestedKernelLock==NULL)
	{
		printf("\nERROR - Release::Invalid Lock ID, NULL value \n");
		osLockTableLock->Release();
		return -1;
	}
	
	if(requestedKernelLock->addrSpace != currentThread->space)
	{
		printf("\nERROR - Release:: Sorry This lock does not belong to your process, so you cant release it\n");
		osLockTableLock->Release();
		return -1;
	}
	if(requestedKernelLock->lock->lockOwner != currentThread)
		{
			printf("\nERROR - Release:: Cant Release without Acquiring lock of monitor !!!\n");
			osLockTableLock->Release();
			return -1;
		}		


	 bool isSuccess=(requestedKernelLock->lock)->Release();
     if(isSuccess==true) (requestedKernelLock->noOfUsers)--;


//CHECK ON THIS what if Release fails, so you should not decrement the counter

if( (requestedKernelLock->noOfUsers == 0)  &&  (requestedKernelLock->isToBeDeleted==true) )
{		 //DestroyLock(lockID);
		//delete requestedKernelLock->Lock;
		 delete requestedKernelLock;
		 osLockTable[lockID]=NULL;
}

osLockTableLock->Release();
return 1;
}*/

#ifdef NETWORK
int Release_Syscall(unsigned int lockName)
{
	int length=50;

	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize], data[MaxMailSize];
	strcpy(data,"03");
	//sprintf(charLockID,"%d",lockID);
	
	
	char* buf=new char[length];
	if(buf==NULL) return -1;

	 if(copyinWithNullEnding(lockName,buf)== -1)
	 {
			printf("\nERROR - Release::Bad pointer passed.\n");
			delete[] buf;
			return -1;
	 }
	 buf[length]='\0';
	
	strcat(data,buf);
	
	//SERVER IS ALWAYS MACHINE 1
	int farAddr=1;
	outPktHdr.to = rand()%totalServers;//servMachID;//farAddr;
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(data) + 1;
    outPktHdr.from= myMachineID;

    // Send the first message
   // printf("Inside Release_Syscall BEFORE SEND for MailBox %d\n",currentThread->myMailboxNum);
    bool success = postOffice->Send(outPktHdr, outMailHdr, data); 

    if ( !success ) {
      printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
      interrupt->Halt();
    }

	//printf("After send from MailTest1 \n");
    // Wait for the first message from the other machine
    postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);

	int bufferIntVal=atoi(buffer);

//	printf("Release Syscall-- return value is %d",bufferIntVal);

	if(bufferIntVal==-1)
	{
		printf("\nERROR: Release Syscall- Failure for MailBox %d\n",currentThread->myMailboxNum);
	}


    fflush(stdout);
	return 1;
}
#endif
/*
void DeleteLock_Syscall(int lockID)
{
	//printf("\nI am in DeleteLock\n");
	
	if( (lockID > MAX_LOCKS) || (lockID < 0) )
	{
		printf("\nERROR - DeleteLock:Invalid Lock ID out of range\n");
		return;
	}
	osLockTableLock->Acquire();
	KernelLock* requestedKernelLock=osLockTable[lockID];
	if(requestedKernelLock==NULL)
	{
		printf("\nERROR - DeleteLock:Invalid Lock ID,NULL LOCK\n");
		osLockTableLock->Release();
		return;
	}
	
	if(requestedKernelLock->addrSpace != currentThread->space)
	{
		printf("\nERROR - DeleteLock:Sorry...This lock does not belong to your process, so you cant delete it\n");
		osLockTableLock->Release();
		return;
	}

requestedKernelLock->isToBeDeleted=true;

if(requestedKernelLock->noOfUsers == 0 )
{		 //DestroyLock(lockID);
		//delete requestedKernelLock->Lock;
		 delete requestedKernelLock;
		 osLockTable[lockID]=NULL;
}

osLockTableLock->Release();
//return 1;
}
*/

#ifdef NETWORK

void DeleteLock_Syscall(int lockID)
{
	//printf("Inside DeleteLock_Syscall\n");
	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize], data[MaxMailSize], charLockID[MaxMailSize];
	strcpy(data,"08");
	sprintf(charLockID,"%d",lockID);
	strcat(data,charLockID);
	//cout<<"LockID in string is "<<data<<endl;

    // construct packet, mail header for original message
    // To: destination machine, mailbox 0
    // From: our machine, reply to: mailbox 1
    
	//SERVER IS ALWAYS MACHINE 1
	int farAddr=1;
	outPktHdr.to = farAddr;		
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(data) + 1;

    // Send the first message
    bool success = postOffice->Send(outPktHdr, outMailHdr, data); 

    if ( !success ) {
      printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
      interrupt->Halt();
    }

	//printf("After send from MailTest1 \n");
    // Wait for the first message from the other machine
    postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);
    //printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
	
	int bufferIntVal=atoi(buffer);    
	
	if(bufferIntVal==-1)
		printf("\nERROR: DeleteLock_Syscall- DELETE LOCK FAILURE..\n");
	
	fflush(stdout);
	//return 1;
}

#endif



void Yield_Syscall()
{
	currentThread->Yield();
}

/*
int CreateCV_Syscall(unsigned int cvName,int length) {

		if(length <= 1)
		{		printf("\nERROR - CreateCV:::Length of Name of a CV can't be negative\n");
			    return -1;
		}

		char* buf=new char[length+1];
		if(buf==NULL) return -1;

		 if(copyin(cvName,length,buf)== -1)
		 {
				printf("ERROR - CreateCV::Bad pointer passed to CreateCV\n");
				delete[] buf;
				return -1;
		 }
		 buf[length]='\0';
		 
		int currentCVIndex=-1;
		//printf("\nControll reached CreateCV Sys Call 1!!!!\n");


		//Acquire Kernel CV table Lock
		osCVTableLock->Acquire();
		if(nextCVLocation < MAX_CVS)
		  {
				osCVTable[nextCVLocation]=new KernelCV;
				//make its entry into Kernel CV table, you should know its empty index entry
				osCVTable[nextCVLocation]->CV=new Condition(buf);
				osCVTable[nextCVLocation]->addrSpace=currentThread->space;
				osCVTable[nextCVLocation]->isToBeDeleted=false;
				osCVTable[nextCVLocation]->noOfUsers=0;
				//printf("User gave the CVs name as %s,  %d",buf,nextCVLocation);
				currentCVIndex=nextCVLocation;
				nextCVLocation++;
				
				osCVTableLock->Release();
				
				//printf("\nValue being returned is %d\n",currentCVIndex);
				return currentCVIndex;
		  }
		  else
		  {
			  printf("\nERROR - CreateCV::No NEW CV can be created!!, as max limit has been reached\n"); 
			  osCVTableLock->Release();
			  return -1;
		  }
}
*/

#ifdef NETWORK
int CreateCV_Syscall(unsigned int cvName) {

	//printf("Inside CreateCV\n");
	int length=50;

	char* buf=new char[length+1];

	if(buf==NULL) return -1;

	 if(copyinWithNullEnding(cvName,buf)== -1)
	 {
		printf("\nERROR - CreateCV::Bad pointer passed to CreateCV\n");
		delete[] buf;
		return -1;
	 }
	 buf[length]='\0';

	char* bufNew=new char[length+3];
	bufNew[0]='0';
	bufNew[1]='4';

	for(int i=0;i<length;i++)
	{
		bufNew[i+2]=buf[i];
	}

	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize];

    // construct packet, mail header for original message
    // To: destination machine, mailbox 0
    // From: our machine, reply to: mailbox 1
    
	//SERVER IS ALWAYS MACHINE 1
	int farAddr=1;
	outPktHdr.to = rand()%totalServers;//servMachID;//farAddr;
	//outPktHdr.to = farAddr;
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(bufNew) + 1;
    outPktHdr.from= myMachineID;

    // Send the first message
    bool success = postOffice->Send(outPktHdr, outMailHdr, bufNew); 

    if ( !success ) {
      printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
      interrupt->Halt();
    }

	//printf("After send from MailTest1 \n");
    // Wait for the first message from the other machine
    postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);
    //printf("Got CV: \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
    fflush(stdout);
	int bufferIntVal=atoi(buffer);

	if(bufferIntVal==-1)
		printf("\nERROR: CreateCV_Syscall- CV CREATION FAILURE..\n");
	
	//	printf("\nCreateCV_Syscall- CV CREATION SUCCESS..\n");

	return bufferIntVal;
	
}
#endif


// Monitor Variable Syscall

#ifdef NETWORK

int CreateMV_Syscall(unsigned int name, int arraySize)
{
	//printf("\n Inside CreateMV_Syscall. \n");

	char buffer[MaxMailSize], charLen[MaxMailSize], charSize[MaxMailSize];
	int length=50;
	char* buf=new char[length+1];

	if(buf==NULL) return -1;

	if(copyinWithNullEnding(name,buf)== -1)
	{
		printf("\n ERROR - CreateMV:: Bad pointer passed to CreateMV. \n");
		delete[] buf;
		return -1;
	}
	buf[length]='\0';

	char* bufNew=new char[length+7];

	bufNew[0]='1';
	bufNew[1]='0';

	for(int i=0;i<length;i++)
	{
		bufNew[i+2]=buf[i];
	}


	sprintf(charLen,"%d",length);
	sprintf(charSize,"%d",arraySize);

	strcat(bufNew,"=");
	strcat(bufNew,charSize);

	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;

	//cout<<"\n CreateMV_Syscall: String being passed is: "<<bufNew<<endl;

	int farAddr=1;

  	outPktHdr.to = rand()%totalServers;
	//outPktHdr.to = farAddr;

	outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(bufNew) + 1;
    outPktHdr.from= myMachineID;

    bool success = postOffice->Send(outPktHdr, outMailHdr, bufNew); 

    if ( !success )
	{
		printf("\n The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
		interrupt->Halt();
    }


	postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);

	int bufferIntVal=atoi(buffer);

	if(bufferIntVal==-1)
		printf("\nERROR: CreateMV_Syscall- MV CREATION FAILURE.. for %s\n",buf);


	return bufferIntVal;
}

#endif


#ifdef NETWORK

int SetMV_Syscall(unsigned int mvName, int arrayIndex, int assignValue)
{
	//printf("\n Inside SetMV_Syscall. \n");

	char buffer[MaxMailSize], data[MaxMailSize], charArrayIndex[MaxMailSize], charAssignValue[MaxMailSize];

	strcpy(data,"11");
	//sprintf(charMVid,"%d",mvID);
	
	int length=50;
	char* buf=new char[length+1];

	if(buf==NULL) return -1;

	if(copyinWithNullEnding(mvName,buf)== -1)
	{
		printf("\n ERROR - SetMV:: Bad pointer passed.\n");
		delete[] buf;
		return -1;
	}
	buf[length]='\0';
	
	strcat(data,buf);
		
	//sprintf(charLength,"%d",length);
	sprintf(charArrayIndex,"%d",arrayIndex);
	sprintf(charAssignValue,"%d",assignValue);

	/*strcat(bufNew,"+");
	strcat(bufNew,charLength);*/

	strcat(data,"=");
	strcat(data,charArrayIndex);
	strcat(data,"@");
	strcat(data,charAssignValue);

	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;

	//cout<<"\n In SetMV_Syscall: String being passed is: "<<data<<endl;

	int farAddr=1;

	outPktHdr.to = rand() % totalServers;//servMachID;
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(data) + 1;
    outPktHdr.from=myMachineID;
    bool success = postOffice->Send(outPktHdr, outMailHdr, data); 

    if ( !success )
	{
		printf("SetMV_Syscall::The postOffice Send failed. You must not have the other %d Nachos running. Terminating Nachos.\n",outPktHdr.to);
		interrupt->Halt();
    }

	//printf("\n SetMV_Syscall: After send. \n");

	postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);

	int bufferIntVal=atoi(buffer);

	if(bufferIntVal==-1)
		printf("\nERROR: SetMV_Syscall- SET MV FAILURE..\n");
   
	fflush(stdout);
	
	return 0;

}




#endif



#ifdef NETWORK

int GetMV_Syscall(unsigned int mvName, int arrayIndex)
{
	//printf("\n Inside GetMV_Syscall. \n");

	char buffer[MaxMailSize], charMVid[MaxMailSize], data[MaxMailSize], charArrayIndex[MaxMailSize];

	strcpy(data,"12");
	//sprintf(charMVid,"%d",mvID);
	
		int length=50;
	char* buf=new char[length+1];

	if(buf==NULL) return -1;

	if(copyinWithNullEnding(mvName,buf)== -1)
	{
		printf("\n ERROR - GetMV:: Bad pointer passed.\n");
		delete[] buf;
		return -1;
	}
	buf[length]='\0';
	
	strcat(data,buf);
		
	sprintf(charArrayIndex,"%d",arrayIndex);

	strcat(data,"=");
	strcat(data,charArrayIndex);


	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;

	//cout<<"\n In GetMV_Syscall: String being passed is: "<<data<<endl;

	int farAddr=1;

	outPktHdr.to = rand() % totalServers;//servMachID;
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(data) + 1;
    outPktHdr.from=myMachineID;
    bool success = postOffice->Send(outPktHdr, outMailHdr, data); 

    if ( !success )
	{
    	printf("SetMV_Syscall::The postOffice Send failed. You must not have the other %d Nachos running. Terminating Nachos.\n",outPktHdr.to);
		interrupt->Halt();
    }

	postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);

	//printf("\n GetMV_Syscall: Got: \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
   
	fflush(stdout);
	
	int getValue=atoi(buffer);

	if(getValue==-100)
		printf("\nERROR: GetMV_Syscall- GET MV FAILURE..\n");

	return getValue;

}


#endif




/*	int Wait_Syscall(int CVid,int lockID)
    {
		 //printf("\n1-I am in Wait with lockID  as %d\n",lockID);
		if( (CVid > MAX_CVS) || (CVid < 0) )
		{
			printf("\nERROR - Wait::Invalid CV ID,out of range\n");
			return -1;
		}
		if( (lockID > MAX_LOCKS) || (lockID < 0) )
		{
			printf("\nERROR - Wait::Invalid Lock ID,out of range\n");
			return -1;
		}
//Further Lock Checks
		osLockTableLock->Acquire();
		
		KernelLock* requestedKernelLock=osLockTable[lockID];
		if(requestedKernelLock==NULL)
		{
			printf("\nERROR - Wait:: Invalid Lock ID..NULL value ..\n");
			osLockTableLock->Release();
			return -1;
		}
		
		if(requestedKernelLock->addrSpace != currentThread->space)
		{
			printf("\nERROR - Wait:: Sorry...This lock does not belong to your process!!!\n");
			osLockTableLock->Release();
			return -1;
		}

		if(requestedKernelLock->lock->lockOwner != currentThread)
		{
			printf("\nERROR - Wait:: Cant go on wait without Acquiring lock of monitor !!!\n");
			osLockTableLock->Release();
			return -1;
		}

		osLockTableLock->Release();
		
//Further CV Checks
		osCVTableLock->Acquire();
		KernelCV* requestedKernelCV=osCVTable[CVid];
		if(requestedKernelCV==NULL)
		{
			printf("\nERROR - Wait::Invalid CV ID..NULL value ..\n");
			osCVTableLock->Release();
			return -1;
		}
		
		if(requestedKernelCV->addrSpace != currentThread->space)
		{
			printf("\nERROR - Wait:: Sorry...This CV does not belong to your process !!!\n");
			osCVTableLock->Release();
			return -1;
		}//Everything is ALMOST fine, so you can go on wait

		requestedKernelCV->noOfUsers=requestedKernelCV->noOfUsers+1;
		osCVTableLock->Release();

        //printf("\n2-I am in Wait with lockID  as %d\n",lockID);
		(requestedKernelCV->CV)->Wait(requestedKernelLock->lock);

		//He has got up from wait,somebody might have signalled him so decreemnt the counter.
		osCVTableLock->Acquire();

		requestedKernelCV->noOfUsers=requestedKernelCV->noOfUsers-1;

		if(requestedKernelCV->noOfUsers==0 && requestedKernelCV->isToBeDeleted==true)
		{		
		 delete requestedKernelCV;
		 osCVTable[CVid]=NULL;
		}

		osCVTableLock->Release();
        return 1;
}
*/


#ifdef NETWORK
int Wait_Syscall(int cvName,int lockName )
{
	//printf("Inside Wait_Syscall\n");
	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize], data[MaxMailSize], charLockID[MaxMailSize], charCVID[MaxMailSize];
	strcpy(data,"05");
	//sprintf(charLockID,"%d",lockID);
	//sprintf(charCVID,"%d",CVid);
	
	int length=50;
	char* buf=new char[length+1];

//	if(buf==NULL) return -1;

	if(copyinWithNullEnding(cvName,buf)== -1)
	{
		printf("\n ERROR - Wait:: Bad pointer passed.\n");
		delete[] buf;
		//return -1;
	}
	//buf[length]='\0';

	char* buf2=new char[length+1];

//	if(buf2==NULL) return -1;

	if(copyinWithNullEnding(lockName,buf2)== -1)
	{
		printf("\n ERROR - Wait:: Bad pointer passed.\n");
		delete[] buf2;
		//return -1;
	}
	//buf2[length]='\0';
	
	strcat(data,buf);
	strcat(data,"+");
	strcat(data,buf2);
    
	//SERVER IS ALWAYS MACHINE 1
	int farAddr=1;

	outPktHdr.to = rand()%totalServers;
	//outPktHdr.to = servMachID;//farAddr;

	outPktHdr.from=myMachineID;
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(data) + 1;
//printf("\n From Wait- outMailHdr.length is %d\n",outMailHdr.length);
    // Send the first message
    bool success = postOffice->Send(outPktHdr, outMailHdr, data); 
    if ( !success ) {
      printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
      interrupt->Halt();
    }

    postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);

	int bufferIntVal=atoi(buffer);

	if(bufferIntVal==-1)
		printf("\nERROR: Wait_Syscall- WAIT FAILURE..\n");

    fflush(stdout);

    return 1;
}
#endif

/*
void Signal_Syscall(int CVid,int lockID)
   {
		//printf("\nI am going to Signal in CV= %d with lockID= %d\n",CVid,lockID);
		if( (CVid > MAX_CVS) || (CVid < 0) )
		{
			printf("\nERROR -Signal::Invalid CV ID, out of range\n");
			return;
		}
		if( (lockID > MAX_LOCKS) || (lockID < 0) )
		{
			printf("\nERROR -Signal::Invalid Lock ID, out of range\n");
			return;
		}
//Further Lock Checks
		osLockTableLock->Acquire();
		KernelLock* requestedKernelLock=osLockTable[lockID];
		if(requestedKernelLock==NULL)
			{
				printf("\nERROR - Signal:: Invalid Lock ID..NULL value ..\n");
				osLockTableLock->Release();
				return;
			}
			
		if(requestedKernelLock->addrSpace != currentThread->space)
		{
			printf("\nERROR - Signal:: Sorry...This lock does not belong to your process !!!!\n");
			osLockTableLock->Release();
			return;
		}
		if(requestedKernelLock->lock->lockOwner != currentThread)
				{
					printf("\nERROR - Signal:: You Can't Signal without Acquiring lock of monitor !!!\n");
					osLockTableLock->Release();
					return;
				}

		osLockTableLock->Release();

//Further CV Checks
		osCVTableLock->Acquire();
		KernelCV* requestedKernelCV=osCVTable[CVid];
		if(requestedKernelCV==NULL)
		{
			printf("\nERROR - Signal::Invalid CV ID..NULL value ..\n");
			osCVTableLock->Release();
			return;
		}

		
		if(requestedKernelCV->addrSpace != currentThread->space)
		{
			printf("\nERROR - Signal:: Sorry...This CV does not belong to your process !!!\n");
			osCVTableLock->Release();
			return;
		}//Everything is ALMOST fine, so you can go and Signal

		osCVTableLock->Release();
		
(requestedKernelCV->CV)->Signal(requestedKernelLock->lock);
        //printf("Signal:: Just signalled 1 thread");
		//return 1;
}
*/

				  
#ifdef NETWORK
void Signal_Syscall(int cvName,int lockName)
{
	//printf("Inside Signal_Syscall\n");
	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize], data[MaxMailSize], charLockID[MaxMailSize], charCVID[MaxMailSize];
	strcpy(data,"06");
	//sprintf(charLockID,"%d",lockID);
	//sprintf(charCVID,"%d",CVid);
	
	int length=50;
	char* buf=new char[length+1];

	//if(buf==NULL) return -1;

	if(copyinWithNullEnding(cvName,buf)== -1)
	{
		printf("\n ERROR - Signal:: Bad pointer passed.\n");
		delete[] buf;
		//return -1;
	}
	buf[length]='\0';

	char* buf2=new char[length+1];

	//if(buf2==NULL) return -1;

	if(copyinWithNullEnding(lockName,buf2)== -1)
	{
		printf("\n ERROR - Signal:: Bad pointer passed.\n");
		delete[] buf2;
		//return -1;
	}
	buf2[length]='\0';
	
	strcat(data,buf);
	strcat(data,"+");
	strcat(data,buf2);

    
	//SERVER IS ALWAYS MACHINE 1
	int farAddr=1;

	outPktHdr.to = rand()%totalServers;
	//outPktHdr.to = servMachID;

    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(data) + 1;
    outPktHdr.from=myMachineID;

    // Send the first message
    bool success = postOffice->Send(outPktHdr, outMailHdr, data); 
    if ( !success ) {
      printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
      interrupt->Halt();
    }

    postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);
	int bufferIntVal=atoi(buffer);

	if(bufferIntVal==-1)
		printf("\nERROR: Signal_Syscall- SIGNAL FAILURE..\n");


    fflush(stdout);

}

#endif





/*
void Broadcast_Syscall(int CVid,int lockID)
   {
		//printf("\nI am in Broadcast with lockID as %d\n",CVid);
		if( (CVid > MAX_CVS) || (CVid < 0) )
		{
			printf("\nERROR - Broadcast::Invalid CV ID, out of range\n");
			return;
		}
		if( (lockID > MAX_LOCKS) || (lockID < 0) )
		{
			printf("\nERROR - Broadcast::Invalid Lock ID, out of range\n");
			return;
		}
//Further Lock Checks
		osLockTableLock->Acquire();
		KernelLock* requestedKernelLock=osLockTable[lockID];
		if(requestedKernelLock==NULL)
		{
			printf("\nERROR - Broadcast:: Invalid Lock ID..NULL value ..\n");
			osLockTableLock->Release();
			return;
		}
		
		if(requestedKernelLock->addrSpace != currentThread->space)
		{
			printf("\nERROR - Broadcast::Sorry...This lock does not belong to your process, so you cant broadcast on it\n");
			osLockTableLock->Release();
			return;
		}
		if(requestedKernelLock->lock->lockOwner != currentThread)
				{
					printf("\nERROR - Broadcast:: You Can't BroadCast without Acquiring lock of monitor !!!\n");
					osLockTableLock->Release();
					return;
				}
		osLockTableLock->Release();

//Further CV Checks
		osCVTableLock->Acquire();
		KernelCV* requestedKernelCV=osCVTable[CVid];
		if(requestedKernelCV==NULL)
		{
			printf("\nERROR - Broadcast::Invalid CV ID..NULL value ..\n");
			osCVTableLock->Release();
			return;
		}
		
		if(requestedKernelCV->addrSpace != currentThread->space)
		{
			printf("\nERROR - Broadcast:: Sorry...This CV does not belong to your process, so you cant acquire it\n");
			osCVTableLock->Release();
			return;
		}
//Everything is ALMOST fine, so you can go and Signal

		osCVTableLock->Release();
		(requestedKernelCV->CV)->Broadcast(requestedKernelLock->lock);
        //printf("Broadcast:: Just Broadcasted in the CV");
}
*/


#ifdef NETWORK

void Broadcast_Syscall(int cvName,int lockName)
{
	
	//printf("Inside Signal_Syscall\n");
	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize], data[MaxMailSize];
	strcpy(data,"07");
	//sprintf(charLockID,"%d",lockID);
	//sprintf(charCVID,"%d",CVid);
	
		int length=50;
	char* buf=new char[length+1];

	//if(buf==NULL) return -1;

	if(copyinWithNullEnding(cvName,buf)== -1)
	{
		printf("\n ERROR - Signal:: Bad pointer passed.\n");
		delete[] buf;
		//return -1;
	}
	buf[length]='\0';

	char* buf2=new char[length+1];

	//if(buf2==NULL) return -1;

	if(copyinWithNullEnding(lockName,buf2)== -1)
	{
		printf("\n ERROR - Signal:: Bad pointer passed.\n");
		delete[] buf2;
		//return -1;
	}
	buf2[length]='\0';
	
	
	strcat(data,buf);
	strcat(data,"+");
	strcat(data,buf2);
	//cout<<"In signal syscall string passd is "<<data<<endl;

    // construct packet, mail header for original message
    // To: destination machine, mailbox 0
    // From: our machine, reply to: mailbox 1
    
	//SERVER IS ALWAYS MACHINE 1
	int farAddr=1;
	outPktHdr.to = rand()%totalServers;
		//outPktHdr.to = servMachID;//farAddr;

   outPktHdr.from=myMachineID;
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(data) + 1;

    // Send the first message
    bool success = postOffice->Send(outPktHdr, outMailHdr, data); 
    if ( !success ) {
      printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
      interrupt->Halt();
    }

    postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);
    int bufferIntVal=atoi(buffer);

	if(bufferIntVal==-1)
		printf("\nERROR: Broadcast_Syscall- BROADCAST FAILURE..\n");

    fflush(stdout);
}

#endif


/*
void DeleteCV_Syscall(int CVid)
{
	
	if( (CVid > MAX_CVS) || (CVid < 0) )
	{
		printf("\nERROR - DeleteCV::Invalid CV ID, out of range\n");
		return;
	}
	osCVTableLock->Acquire();
	KernelCV* requestedKernelCV=osCVTable[CVid];
	if(requestedKernelCV==NULL)
	{
		printf("\nERROR - DeleteCV:Invalid CV ID,NULL Value\n");
		osCVTableLock->Release();
		return;
	}
	
	if(requestedKernelCV->addrSpace != currentThread->space)
	{
		printf("\nERROR - DeleteCV:Sorry...This CV does not belong to your process, so you cant delete it\n");
		osCVTableLock->Release();
		return;
	}

requestedKernelCV->isToBeDeleted=true;

if(requestedKernelCV->noOfUsers == 0)
{		
		 delete requestedKernelCV;
		 osCVTable[CVid]=NULL;
}

osCVTableLock->Release();
//return 1;
}
*/


#ifdef NETWORK
void DeleteCV_Syscall(int CVid)
{
	
	//printf("Inside DeleteCV_Syscall\n");
	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize], data[MaxMailSize], charCVid[MaxMailSize];
	strcpy(data,"09");
	sprintf(charCVid,"%d",CVid);
	strcat(data,charCVid);
	//cout<<"CVid in string is "<<data<<endl;

    // construct packet, mail header for original message
    // To: destination machine, mailbox 0
    // From: our machine, reply to: mailbox 1
    
	//SERVER IS ALWAYS MACHINE 1
	int farAddr=1;
	outPktHdr.to = farAddr;		
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(data) + 1;

    // Send the first message
    bool success = postOffice->Send(outPktHdr, outMailHdr, data); 

    if ( !success ) {
      printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
      interrupt->Halt();
    }

	//printf("After send from MailTest1 \n");
    // Wait for the first message from the other machine
    postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);
//    printf("Got \"%s\" from %d, box %d\n",buffer,inPktHdr.from,inMailHdr.from);
	int bufferIntVal=atoi(buffer);

	if(bufferIntVal==-1)
		printf("\nDeleteCV_Syscall- DELETE CV FAILURE..\n");	
	
	fflush(stdout);
	//return 1;

}
#endif




#ifdef NETWORK
void DeleteMV_Syscall(int MVid)
{
	
	//printf("Inside DeleteCV_Syscall\n");
	PacketHeader outPktHdr, inPktHdr;
    MailHeader outMailHdr, inMailHdr;
    char buffer[MaxMailSize], data[MaxMailSize], charMVid[MaxMailSize];
	strcpy(data,"13");
	sprintf(charMVid,"%d",MVid);
	strcat(data,charMVid);
    
	//SERVER IS ALWAYS MACHINE 1
	int farAddr=1;
	outPktHdr.to = farAddr;		
    outMailHdr.to = 0;
    outMailHdr.from = currentThread->myMailboxNum;
    outMailHdr.length = strlen(data) + 1;

    // Send the first message
    bool success = postOffice->Send(outPktHdr, outMailHdr, data); 

    if ( !success ) {
      printf("The postOffice Send failed. You must not have the other Nachos running. Terminating Nachos.\n");
      interrupt->Halt();
    }

    postOffice->Receive(currentThread->myMailboxNum, &inPktHdr, &inMailHdr, buffer);

	int bufferIntVal=atoi(buffer);

	if(bufferIntVal==-1)
		printf("\nDeleteMV_Syscall- DELETE MV FAILURE..\n");	
	
	fflush(stdout);
	//return 1;

}
#endif




//Lock & CVs related END
void kernel_thread(int virtAddr)
{
    // Calculate the position of starting address of the stack of forked thread in BYTES
	currentThread->space->StackToThread();
	
	machine->WriteRegister(PCReg,virtAddr);
	machine->WriteRegister(NextPCReg, virtAddr+4);
	
	//printf("\nIn Kernel_thread\n");
	currentThread->space->RestoreState();	
	
	//printf("\nPID %d, Starting Address of Stack %u\n",currentThread->space->myPID,currentThread->startingAddressofStack);
	machine->WriteRegister(StackReg, currentThread->startingAddressofStack);
	
		// Run the machine
	machine->Run();
}

void Fork_Syscall(unsigned int myFunction)
{
	int threadsMailBox;
    PCBTableLock->Acquire();
    	int myPID=currentThread->space->myPID;
    	//ASSERT((PCBTable[myPID]->noOfChildThreads) < MAX_THREADS);
    	(PCBTable[myPID]->noOfChildThreads)++;
    	 currentThread->space->noOfThreads=currentThread->space->noOfThreads+1;
    	 threadsMailBox=mailboxNumCounter;
    	 mailboxNumCounter++;
    PCBTableLock->Release();
	Thread *myThread = new Thread("New");
	myThread->space = currentThread->space;
	myThread->myMailboxNum=threadsMailBox;
	//myThread->myPID = currentThread->myPID;
	//printf("\nNo of Children Threads for Process with PID=%d is %d\n",myPID,PCBTable[myPID]->noOfChildThreads);   
	
	//printf("\nStarting address of process : %u", myThread->startingAddressofStack);
	
	myThread->Fork((VoidFunctionPtr) kernel_thread, myFunction);//myFunction);
	//printf("\nafter Calling Fork111\n");
	

}

void ExecThread(int i)
{
    //printf("\nPID %d, Starting Address of Stack %u,stackPageBottom %u-Main Thread\n", currentThread->space->myPID,(currentThread->stackPageOfBottom * PageSize)-16,currentThread->stackPageOfBottom);
    currentThread->space->InitRegisters();
	currentThread->space->RestoreState();
	
	machine->Run();		
}

void Exec_Syscall(unsigned int vaddr, int len)
{
		if(len <= 1)
		{		printf("\nERROR - Exec::Length of Name of a file can't be negative\n");
			    return;
		}

	char *filePath = new char[len+1];	// Kernel buffer to put the name in
    OpenFile *executable;			// The new open file
    int id;				// The openfile id

    if (!filePath) {
	printf("%s","ERROR - Exec::Can't allocate kernel buffer in Exec_Syscall\n");
	return;
    }

    if( copyin(vaddr,len,filePath) == -1 ) {
	printf("%s","ERROR - Exec::Bad pointer passed to Open\n");
	delete[] filePath;
	return;
    }

	//printf("\nhi I have done reading the file's path in a very nice way  %s\n", filePath);
    filePath[len]='\0';
	//ASSERT(FALSE);
	
    executable = fileSystem->Open(filePath);
        
    if (executable == NULL) {
	printf("\nERROR - Exec::Unable to open file %s\n", filePath);
	return;
    }   
 //
PCBTableLock->Acquire();
		//ASSERT(nextPCBLocation < MAX_PROCESSES);
		PCBTable[nextPCBLocation]=new PCB;
		AddrSpace* space = new AddrSpace(executable);   
		PCBTable[nextPCBLocation]->addrSpace=space;
		PCBTable[nextPCBLocation]->noOfChildThreads=1;
		PCBTable[nextPCBLocation]->withinProcessLock=new Lock("withinProcessLock");
		
	
	 
	Thread* myThread=new Thread("New Process");
    myThread->space = space;
    myThread->space->myPID=nextPCBLocation;
    myThread->stackPageOfBottom=space->GetNumPages();
    
		nextPCBLocation=nextPCBLocation+1;
		noOfTotalProcesses=noOfTotalProcesses+1;

//Assigning the mailbox number
myThread->myMailboxNum=mailboxNumCounter;
mailboxNumCounter++;

PCBTableLock->Release();

    
    delete executable;			// close file

    myThread->Fork((VoidFunctionPtr)ExecThread,1);
}


void Exit_Syscall(int status)
{
	  PCBTableLock->Acquire(); 
	  
	  PCB* myPCB = PCBTable[currentThread->space->myPID];
	  myPCB->noOfChildThreads=myPCB->noOfChildThreads-1;	
	  int runningthreadsCount=myPCB->noOfChildThreads;   //number of threads NOT yet exited for process with PID=myPID
	  int processRunningCount=0;
	
		/*
		
		//Here we try to detect for any thread which is exiting, that is it the last EXECUTING thread of that process
		//that is other (Non Exited)threads of that process are in wait, rather they are in dead wait
		//so this thread can safely clear all address pages of that Process
		// & if it last process itself, it should call interrupt->Halt() straight away
		osCVTableLock->Acquire();	
						int waitersForMyProcess=0;
				    	for(int i=0;i<MAX_CVS;i++)
				    	{
				    		if(osCVTable[i] != NULL)
				    		{
				    			if(osCVTable[i]->addrSpace==currentThread->space)
				    			{
									waitersForMyProcess = waitersForMyProcess + osCVTable[i]->noOfUsers;				    				
				    			}
				    		}
				    	
				    	}
					 if(runningthreadsCount == waitersForMyProcess)
							{
								printf("Yes threadCount == waitersForMyProcess took place with runningthreadsCount = %d",runningthreadsCount);
								runningthreadsCount=0;								
							}
		  osCVTableLock->Release();	
    */
      
	  //Last Thread in any process but not in the last process
	    if (runningthreadsCount==0)
	    {
			//	    printf("\nif 1, with PID as %d\n",currentThread->space->myPID);
		    currentThread->space->ClearAddressSpacePages();
			
		    	osLockTableLock->Acquire();
		    	
				for(int i=0;i<MAX_LOCKS;i++)
				{
					if(osLockTable[i] != NULL)
					{
						if(osLockTable[i]->addrSpace==currentThread->space)
						{
							//delete osLockTable[i]->lock;
							delete osLockTable[i];
							osLockTable[i]=NULL;	    
							//printf("\ndeleted one lock with id=%d\n",i);				
							
						}
					}			    	
				}
		    	
		    	osLockTableLock->Release();
		
				/*
		    	osCVTableLock->Acquire();	    	
				    	for(int i=0;i<MAX_CVS;i++)
				    	{
				    		if(osCVTable[i] != NULL)
				    		{
				    			if(osCVTable[i]->addrSpace==currentThread->space)
				    			{
				    				delete osCVTable[i]->CV;
				    				delete osCVTable[i];
				    				osCVTable[i]=NULL;	    				
				    				
				    			}
				    		}
				    	
				    	}	    	
		    	osCVTableLock->Release();	
		    	*/  
		    	delete myPCB;
		    	PCBTable[currentThread->space->myPID]=NULL;	    	    	
		    	delete currentThread->space;    	
		    	//printf("\n\nJust before  finish %d\n\n",currentThread->space->myPID);
		    	
		    	
		    	 for(int i=0; i<MAX_PROCESSES;i++)
				  {
				  	if (PCBTable[i] != NULL)
				  	{
				  		processRunningCount++;
				  	}
				  }
		    	
		    	//printf("\nTotal number of Threads for Process with PID %d ==> %d \n",currentThread->space->myPID,currentThread->space->noOfThreads);
		    	if (processRunningCount >0)
			     { 
			     	  //printf("\nPID as %d - Last Thread of a Process Only-IF\n",currentThread->space->myPID);
			    	  PCBTableLock->Release(); 
			    	  currentThread->Finish();
		    	 }
		    	else if(processRunningCount == 0)
		    	 { 
			    	 //printf("\nPID as %d - Global Last Thread-IF\n",currentThread->space->myPID);
			    	 PCBTableLock->Release(); 
			    	 interrupt->Halt(); 
		    	 }

	    }  	
	    else if (runningthreadsCount > 0)
	    {   
			//printf("\nPID as %d - Not a Last Thread of A Process-IF\n",currentThread->space->myPID);
	    	currentThread->space->ClearThreadStack();
	    	 
	    	PCBTableLock->Release();
	    	currentThread->Finish();
	    }	  		 
}


void ExceptionHandler(ExceptionType which) {
    int type = machine->ReadRegister(2); // Which syscall?
    int rv=0; 	// the return value from a syscall

    if ( which == SyscallException ) {
	switch (type) {
	    default:
		DEBUG('a', "Unknown syscall - shutting down.\n");
	    case SC_Halt:
		DEBUG('a', "Shutdown, initiated by user program.\n");
		interrupt->Halt();
		break;
	    case SC_Create:
		DEBUG('a', "Create syscall.\n");
		Create_Syscall(machine->ReadRegister(4), machine->ReadRegister(5));
		break;
	    case SC_Open:
		DEBUG('a', "Open syscall.\n");
		rv = Open_Syscall(machine->ReadRegister(4), machine->ReadRegister(5));
		break;
	    case SC_Write:
		DEBUG('a', "Write syscall.\n");
		Write_Syscall(machine->ReadRegister(4),
			      machine->ReadRegister(5),
			      machine->ReadRegister(6));
		break;
	    case SC_Read:
		DEBUG('a', "Read syscall.\n");
		rv = Read_Syscall(machine->ReadRegister(4),
			      machine->ReadRegister(5),
			      machine->ReadRegister(6));
		break;

		// Close system Call
	    case SC_Close:
		DEBUG('a', "Close syscall.\n");
		Close_Syscall(machine->ReadRegister(4));
		break;
		
		// CreateLock system Call
		case SC_CreateLock:
		#ifdef NETWORK
		rv=CreateLock_Syscall(machine->ReadRegister(4));
		#endif
		break;
		
		// Acquire system Call
		case SC_Acquire:
		#ifdef NETWORK
		rv=Acquire_Syscall(machine->ReadRegister(4));
		#endif
		break;

		// Release system Call
		case SC_Release:
		#ifdef NETWORK
		rv=Release_Syscall(machine->ReadRegister(4));
		#endif
		break;
		
		// DeleteLock system Call
		case SC_DeleteLock:
		#ifdef NETWORK
		DeleteLock_Syscall(machine->ReadRegister(4));
		#endif
		break;
		
		// CreateCV system Call
		case SC_CreateCV:
		#ifdef NETWORK
		rv=CreateCV_Syscall(machine->ReadRegister(4));
		#endif
		break;

		// CreateMV system Call
		case SC_CreateMV:
		#ifdef NETWORK
		rv=CreateMV_Syscall(machine->ReadRegister(4), machine->ReadRegister(5));
		#endif
		break;

		// SetMV system Call
		case SC_SetMV:
		#ifdef NETWORK
		rv=SetMV_Syscall(machine->ReadRegister(4), machine->ReadRegister(5), machine->ReadRegister(6));
		#endif
		break;

		// GetMV system Callg
		case SC_GetMV:
		#ifdef NETWORK
		rv=GetMV_Syscall(machine->ReadRegister(4), machine->ReadRegister(5));
		#endif
		break;



		// Wait system Call
		case SC_Wait:
		#ifdef NETWORK
		rv=Wait_Syscall(machine->ReadRegister(4), machine->ReadRegister(5));
		#endif
		break;
		
		// Signal system Call
		case SC_Signal:
		#ifdef NETWORK
		Signal_Syscall(machine->ReadRegister(4), machine->ReadRegister(5));
		#endif
		break;

		// Broadcast system Call
		case SC_Broadcast:
		#ifdef NETWORK
		Broadcast_Syscall(machine->ReadRegister(4), machine->ReadRegister(5));
		#endif
		break;

		// DeleteCV system Call
		case SC_DeleteCV:
		#ifdef NETWORK
		DeleteCV_Syscall(machine->ReadRegister(4));
		#endif
		break;

		// DeleteMV system Call
		case SC_DeleteMV:
		#ifdef NETWORK
		DeleteMV_Syscall(machine->ReadRegister(4));
		#endif
		break;
		
		// Rand system Call
		case SC_Rand:
		
		rv=Rand_Syscall(machine->ReadRegister(4));
		break;

		// Fork system Call
		case SC_Fork:
		
		Fork_Syscall(machine->ReadRegister(4));
		break;
		
		// Exit system Call
		case SC_Exit:
		
	    Exit_Syscall(machine->ReadRegister(4));
		//currentThread->Finish();  
		break;		

		// Exec system Call
		case SC_Exec:
		
		Exec_Syscall(machine->ReadRegister(4),machine->ReadRegister(5));
		
		break;	
		
		// Print system Call
		case SC_Print:
		
		Print_Syscall(machine->ReadRegister(4),
			      machine->ReadRegister(5),machine->ReadRegister(6),
			      machine->ReadRegister(7));
		break;	

		// Yield system Call
		case SC_Yield:
		
		Yield_Syscall();
		break;
		
		// Scan system Call
		case SC_Scan:
		
		rv=Scan_Syscall();
		break;

		case SC_Sprint:
			Sprint_Syscall(machine->ReadRegister(4),
			      machine->ReadRegister(5),machine->ReadRegister(6));
		break;
		
	}

	// Put in the return value and increment the PC
	machine->WriteRegister(2,rv);
	machine->WriteRegister(PrevPCReg,machine->ReadRegister(PCReg));
	machine->WriteRegister(PCReg,machine->ReadRegister(NextPCReg));
	machine->WriteRegister(NextPCReg,machine->ReadRegister(PCReg)+4);
	return;
    }	
		
	else {
      cout<<"Unexpected user mode exception - which:"<<which<<"  type:"<< type<<endl;
      interrupt->Halt();
    }
}

