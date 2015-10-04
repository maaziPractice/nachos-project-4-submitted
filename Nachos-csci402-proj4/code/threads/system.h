// system.h 
//	All global variables used in Nachos are defined here.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef SYSTEM_H
#define SYSTEM_H

#include "copyright.h"
#include "utility.h"
#include "thread.h"
#include "scheduler.h"
#include "interrupt.h"
#include "stats.h"
#include "timer.h"
#include "synch.h"
//#include "addrspace.h"

// Initialization and cleanup routines




extern void Initialize(int argc, char **argv); 	// Initialization,
						// called before anything else
extern void Cleanup();				// Cleanup, called when
						// Nachos is done.


 //const int MAX_TC=5;
 #define MAX_TicketTakers 5
 #define MAX_TicketClerks 5
 #define MAX_ConcClerks 5
 
 //FOR Within Group Assembly & Communication
extern Lock * withinGroupInteractionLock[50];
extern Condition* withinGroupInteractionCV[50]; //should be rather all group wait CV
extern Condition* headOfGroupInteractionCV[50];
extern Condition* headMTechCV[50];//
extern Condition* headLobbyCV[50];
 
 //Common For all Employees Start
enum ManagerOrders{GoOnBreak,NoBreak,JustReArrangeSinceYouAreLongest,PreviousOrderComplete,PreviousOrderNotComplete};
extern enum ManagerOrders orderFromManager[3][20][2];
 //Common For all Employees End
  
//Ticket Clerks related START HERE
extern Lock* ticketClerkLineLock;
extern Lock* ticketClerkLock[MAX_TicketClerks];
extern Condition* ticketClerkLineCV[MAX_TicketClerks];
extern Condition* ticketClerkCV[MAX_TicketClerks]; 
extern int ticketClerkState[MAX_TicketClerks];
extern int ticketClerkLineCount[MAX_TicketClerks];
extern int numberOfTicketsForTicketClerk[3][MAX_TicketClerks];
extern int ticketClerkCollection[MAX_TicketClerks];

extern Condition* allOnBreakTicketClerkCV;
extern Lock* myManagerTCLock[MAX_ConcClerks];
extern Condition* myManagerTCCV[MAX_ConcClerks];
extern Lock* ticketClerkFREELock[MAX_ConcClerks];
extern Condition* ticketClerkFREECV[MAX_ConcClerks];
extern Condition* ticketClerkReArrangeCV[MAX_ConcClerks];
//Ticket Clerks related END HERE

//Concession Clerk Related START HERE
extern Lock* concClerkLineLock;
extern Lock* concClerkLock[MAX_ConcClerks];
extern Condition* concClerkLineCV[MAX_ConcClerks];
extern Condition* concClerkCV[MAX_ConcClerks]; 
extern int concClerkState[MAX_ConcClerks];
extern int concClerkLineCount[MAX_ConcClerks];
extern int myCustomersFoodChoices[4][MAX_ConcClerks];
extern int concClerkCollection[MAX_ConcClerks];

extern Condition* allOnBreakConcClerkCV;
extern Lock* myManagerCCLock[MAX_ConcClerks];
extern Condition* myManagerCCCV[MAX_ConcClerks];
extern Condition* concClerkFREECV[MAX_ConcClerks];
extern Condition* concClerkReArrangeCV[MAX_ConcClerks];
//Concession Clerk Related END HERE

//Ticket Takers related START HERE
extern Condition* allOnBreakTicketTakerCV;
extern int allOnBreakTicketTakerCVCount;

extern Lock* ticketTakerLineLock;
extern Lock* ticketTakerLock[MAX_TicketTakers];
extern Condition* ticketTakerLineCV[MAX_TicketTakers];
extern Condition* ticketTakerCV[MAX_TicketTakers]; 
extern int ticketTakerState[MAX_TicketTakers];
extern int ticketTakerLineCount[MAX_TicketTakers];
extern int numberOfTicketsForTicketTaker[3][MAX_TicketTakers];

extern Lock* currentShowFullTillThenEnjoyLobbyLock;
extern Condition* currentShowFullTillThenEnjoyLobbyCV;

extern Condition* ticketTakerReArrangeCV[MAX_TicketTakers];
extern Lock* myManagerTTLock[MAX_TicketTakers];
extern Condition* myManagerTTCV[MAX_TicketTakers];
extern bool amIStuckTT[MAX_TicketTakers];
extern Condition* ticketTakerFREECV[MAX_TicketTakers];

//Ticket Takers related END HERE


extern Lock* movieStatusLock;
extern bool isMovieRunning;

extern Lock* remainingNoOfSeatsLock;
extern int remainingNoOfSeats;



//new variables
extern int numberOfPeopleLeftTheatre;
extern int lastBatchEntertainedCount;




//Theatre Room Start
extern Lock* theatreRoomLock;
extern bool isTheatreRoomSeatAvlbl[5][5];
extern Lock* myManagerMTechLock;
extern Condition* myManagerMTechCV;
extern bool isMTReadyForManagerOrder;
extern int totalCustomerNumber;
extern int numberOfCustEntertained;
//Theatre Room End

//Movie Technician
extern Lock* letMovieTechnicianStartMovieLock;
extern Condition* letMovieTechnicianStartMovieCV;
extern bool areAllCustomersSatInTheatre;
extern int numberOfCustomersSatInTheatre;



/****************************************************************************************************************/
extern Thread *currentThread;			// the thread holding the CPU
extern Thread *threadToBeDestroyed;  		// the thread that just finished
extern Scheduler *scheduler;			// the ready list
extern Interrupt *interrupt;			// interrupt status
extern Statistics *stats;			// performance metrics
extern Timer *timer;				// the hardware alarm clock


/****************************************************************************************************************/






/*************************/

extern int pingTimer;

/*************************/



#ifdef USER_PROGRAM
#include "machine.h"
#include "addrspace.h"
extern Machine* machine;	// user program memory and registers

//Project 2 Start
#define MAX_LOCKS 500	
#define MAX_THREADS 500 
#define MAX_CVS 500
#define MAX_PROCESSES 100

extern Lock* osLockTableLock;
struct KernelLock {
    int myPID;
	Lock* lock;
	AddrSpace* addrSpace;
	int noOfUsers;
	bool isAlreadyDeleted;
	bool isToBeDeleted;
};
extern KernelLock* osLockTable[];
extern int nextLockLocation;


extern Lock* osCVTableLock;
struct KernelCV {
    int myPID;
	Condition* CV;
	AddrSpace* addrSpace;
	int noOfUsers;
	//bool isAlreadyDeleted;
	bool isToBeDeleted;
};

extern KernelCV* osCVTable[];
extern int nextCVLocation;


extern Lock* myBitmapLock;
extern BitMap* myBitmap;


struct PCB{
	int PID;
	AddrSpace* addrSpace;
	int noOfChildThreads;
	Lock* withinProcessLock;
};
 
 extern Lock* PCBTableLock;
 extern PCB* PCBTable[MAX_PROCESSES];
 extern int nextPCBLocation;
extern int noOfTotalProcesses;
//Project 2 End

#endif

#ifdef FILESYS_NEEDED 		// FILESYS or FILESYS_STUB 
#include "filesys.h"
extern FileSystem  *fileSystem;
#endif

#ifdef FILESYS
#include "synchdisk.h"
extern SynchDisk   *synchDisk;
#endif

#ifdef NETWORK
#include "post.h"

extern int totalServers;
extern int myMachineID;


extern PostOffice* postOffice;

#define MAX_MVS 500


struct ClientInfo
{
	int machineId;
	int mailboxNo;
};

class ServerLock
{
	public:
    ServerLock(string debugName);  		// initialize lock to be FREE
    ~ServerLock();				// deallocate lock
    
    //int Acquire();
    //int Release();
	
	//private:
	int lockState;
	int countOfCreateLock;
	string name;
	ClientInfo *ownerInfo;
	List *waitingQueue;
};
 extern ServerLock* lock[];
 extern int nextServerLockLocation;


class ServerCV
{
	public:
    ServerCV(string debugName);  		// initialize lock to be FREE
    ~ServerCV();				// deallocate lock
	
	//private:
	string name;
	int countOfCreateCV;
	string waitingLock;
	int waitingLock1;
	List *conditionQueue;
};
 extern ServerCV* cv[];
 extern int nextServerCVLocation;

class ServerMV
{
//	private:

	public:
	int mvSize;
	string name;
	int countOfCreateMV;
	int *mvValue;
    ServerMV(string debugName, int sizeMV);

};
 extern ServerMV* mv[];
 extern int nextServerMVLocation;
 


#endif
 extern int mailboxNumCounter;

#endif // SYSTEM_H
