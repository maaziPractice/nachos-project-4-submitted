// system.cc 
//	Nachos initialization and cleanup routines.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

// This defines *all* of the global data structures used by Nachos.
// These are all initialized and de-allocated by this file.


   
 //Common For all Employees Start
 enum ManagerOrders orderFromManager[3][20][2];
  //Common For all Employees End

Lock * withinGroupInteractionLock[50];
Condition* withinGroupInteractionCV[50]; //should be rather all group wait CV
Condition* headOfGroupInteractionCV[50];
Condition* headMTechCV[50];//
Condition* headLobbyCV[50];//come under currentShowFullTillThenEnjoyLobbyLock 

//Ticket Clerks related START HERE
 Lock* ticketClerkLineLock;
 Lock* ticketClerkLock[MAX_TicketClerks];
 Condition* ticketClerkLineCV[MAX_TicketClerks];
 Condition* ticketClerkCV[MAX_TicketClerks]; 
 int ticketClerkState[MAX_TicketClerks];
 int ticketClerkLineCount[MAX_TicketClerks];
 int numberOfTicketsForTicketClerk[3][MAX_TicketClerks];
 int ticketClerkCollection[MAX_TicketClerks];

 Condition* allOnBreakTicketClerkCV;
 Lock* myManagerTCLock[MAX_ConcClerks];
 Condition* myManagerTCCV[MAX_ConcClerks];
 Condition* ticketClerkFREECV[MAX_ConcClerks];
 Lock* ticketClerkFREELock[MAX_ConcClerks];
 Condition* ticketClerkReArrangeCV[MAX_ConcClerks];
//Ticket Clerks related END HERE

//Concession Clerk Related START HERE
 Lock* concClerkLineLock;
 Lock* concClerkLock[MAX_ConcClerks];
 Condition* concClerkLineCV[MAX_ConcClerks];
 Condition* concClerkCV[MAX_ConcClerks]; 
 int concClerkState[MAX_ConcClerks];
 int concClerkLineCount[MAX_ConcClerks];
 int myCustomersFoodChoices[4][MAX_ConcClerks];
 int concClerkCollection[MAX_ConcClerks];

 Condition* allOnBreakConcClerkCV;
 Lock* myManagerCCLock[MAX_ConcClerks];
 Condition* myManagerCCCV[MAX_ConcClerks];
 Condition* concClerkFREECV[MAX_ConcClerks];
 Condition* concClerkReArrangeCV[MAX_ConcClerks];
//Concession Clerk Related END HERE


//Ticket Taker Variables Start
 Lock* ticketTakerLineLock;
 Lock* ticketTakerLock[MAX_TicketTakers];
 Condition* ticketTakerLineCV[MAX_TicketTakers];
 Condition* ticketTakerCV[MAX_TicketTakers]; 
 int ticketTakerState[MAX_TicketTakers];
 int ticketTakerLineCount[MAX_TicketTakers];
 int numberOfTicketsForTicketTaker[3][MAX_TicketTakers];
 Lock* currentShowFullTillThenEnjoyLobbyLock;
 Condition* currentShowFullTillThenEnjoyLobbyCV;
 Lock* myManagerTTLock[MAX_TicketTakers];
 Condition* myManagerTTCV[MAX_TicketTakers];
 bool amIStuckTT[MAX_TicketTakers];

Condition* ticketTakerReArrangeCV[MAX_TicketTakers];
Condition* allOnBreakTicketTakerCV;
int allOnBreakTicketTakerCVCount;

Condition* ticketTakerFREECV[MAX_TicketTakers];

Lock* myManagerMTechLock;
Condition* myManagerMTechCV;
int totalCustomerNumber;
int numberOfCustEntertained;

//Ticket Taker Variables over

//new variables
int numberOfPeopleLeftTheatre;
int lastBatchEntertainedCount;

//Theatre Room Start
Lock* theatreRoomLock;
bool isTheatreRoomSeatAvlbl[5][5];
bool areAllCustomersSatInTheatre;
int numberOfCustomersSatInTheatre;
Lock* movieStatusLock;
bool isMovieRunning;
bool isMTReadyForManagerOrder;
Lock* remainingNoOfSeatsLock;
int remainingNoOfSeats;
//Theatre Room End

//movie Technican
Lock* letMovieTechnicianStartMovieLock;
Condition* letMovieTechnicianStartMovieCV;


/****************************************************************************************************************/
Thread *currentThread;			// the thread we are running now
Thread *threadToBeDestroyed;  		// the thread that just finished
Scheduler *scheduler;			// the ready list
Interrupt *interrupt;			// interrupt status
Statistics *stats;			// performance metrics
Timer *timer;				// the hardware timer device,
					// for invoking context switches


/*************************/

int pingTimer=0;

/*************************/

#ifdef FILESYS_NEEDED
FileSystem  *fileSystem;
#endif

#ifdef FILESYS
SynchDisk   *synchDisk;
#endif

#ifdef USER_PROGRAM	// requires either FILESYS or FILESYS_STUB
Machine *machine;	// user program memory and registers

//Project 2 Start
 Lock* osLockTableLock;
 KernelLock* osLockTable[MAX_LOCKS];
 int nextLockLocation;
  
 Lock* osCVTableLock;
 KernelCV* osCVTable[MAX_CVS];
 int nextCVLocation;
 
 Lock* myBitmapLock;
 BitMap* myBitmap;
 
 Lock* PCBTableLock;
 PCB* PCBTable[MAX_PROCESSES];
 int nextPCBLocation;
 
 int noOfTotalProcesses;
//Project 2 End

#endif

#ifdef NETWORK
PostOffice *postOffice;

ServerLock *lock[MAX_LOCKS];
int nextServerLockLocation=0;

ServerLock::ServerLock(string debugName) 
{
     lockState = 0;		//0 is available state, 1 is busy
     name=debugName;
	 ownerInfo=new ClientInfo;
	 ownerInfo->machineId=-1;
	 ownerInfo->mailboxNo=-1;
	 countOfCreateLock=1;
     waitingQueue=new List;
}
int totalServers;
int myMachineID;
ServerLock::~ServerLock() 
{
    delete waitingQueue;
}


ServerCV::ServerCV(string debugName)
{
	name=debugName;    
    waitingLock="";
    waitingLock1=-1;
	countOfCreateCV=1;
    conditionQueue= new List;
}

ServerCV::~ServerCV() 
{
    delete conditionQueue;
}

ServerCV *cv[MAX_CVS];
int nextServerCVLocation=0;

ServerMV::ServerMV(string debugName, int sizeMV) 
{
	name=debugName;
	mvSize=sizeMV;
	countOfCreateMV=1;
	mvValue= new int[mvSize];

	for(int i=0; i<sizeMV; i++)
	{
		mvValue[i]=0;
	}

}

 ServerMV* mv[MAX_MVS];
 int nextServerMVLocation=0;



#endif
 int mailboxNumCounter=0;

// External definition, to allow us to take a pointer to this function
extern void Cleanup();


//----------------------------------------------------------------------
// TimerInterruptHandler
// 	Interrupt handler for the timer device.  The timer device is
//	set up to interrupt the CPU periodically (once every TimerTicks).
//	This routine is called each time there is a timer interrupt,
//	with interrupts disabled.
//
//	Note that instead of calling Yield() directly (which would
//	suspend the interrupt handler, not the interrupted thread
//	which is what we wanted to context switch), we set a flag
//	so that once the interrupt handler is done, it will appear as 
//	if the interrupted thread called Yield at the point it is 
//	was interrupted.
//
//	"dummy" is because every interrupt handler takes one argument,
//		whether it needs it or not.
//----------------------------------------------------------------------
static void
TimerInterruptHandler(int dummy)
{
    if (interrupt->getStatus() != IdleMode)
	interrupt->YieldOnReturn();
}

//----------------------------------------------------------------------
// Initialize
// 	Initialize Nachos global data structures.  Interpret command
//	line arguments in order to determine flags for the initialization.  
// 
//	"argc" is the number of command line arguments (including the name
//		of the command) -- ex: "nachos -d +" -> argc = 3 
//	"argv" is an array of strings, one for each command line argument
//		ex: "nachos -d +" -> argv = {"nachos", "-d", "+"}
//----------------------------------------------------------------------
void
Initialize(int argc, char **argv)
{
    int argCount;
    char* debugArgs = "";
    bool randomYield = FALSE;

#ifdef USER_PROGRAM
    bool debugUserProg = FALSE;	// single step user program
#endif
#ifdef FILESYS_NEEDED
    bool format = FALSE;	// format disk
#endif
#ifdef NETWORK
    double rely = 1;		// network reliability
    int netname = 0;		// UNIX socket name
#endif
    
    for (argc--, argv++; argc > 0; argc -= argCount, argv += argCount) {
	argCount = 1;
	if (!strcmp(*argv, "-d")) {
	    if (argc == 1)
		debugArgs = "+";	// turn on all debug flags
	    else {
	    	debugArgs = *(argv + 1);
	    	argCount = 2;
	    }
	} else if (!strcmp(*argv, "-rs")) {
	    ASSERT(argc > 1);
	    RandomInit(atoi(*(argv + 1)));	// initialize pseudo-random
						// number generator
	    randomYield = TRUE;
	    argCount = 2;
	}



#ifdef USER_PROGRAM
	if (!strcmp(*argv, "-s"))
	    debugUserProg = TRUE;
#endif
#ifdef FILESYS_NEEDED
	if (!strcmp(*argv, "-f"))
	    format = TRUE;
#endif
#ifdef NETWORK
	if (!strcmp(*argv, "-l")) {
	    ASSERT(argc > 1);
	    rely = atof(*(argv + 1));
	    argCount = 2;
	} else if (!strcmp(*argv, "-m")) {
	    ASSERT(argc > 1);
	   netname = atoi(*(argv + 1));
	   myMachineID = netname;
	    argCount = 2;
	}


	 if (!strcmp(*argv, "-sc")) {
		 ASSERT(argc > 1);
		 	    totalServers = atoi(*(argv + 1));
		 	    //printf("\nTotalServers is %d\n",totalServers);
		 	    argCount = 2;
		}


#endif
    }

    DebugInit(debugArgs);			// initialize DEBUG messages
    stats = new Statistics();			// collect statistics
    interrupt = new Interrupt;			// start up interrupt handling
    scheduler = new Scheduler();		// initialize the ready queue
    if (randomYield)				// start the timer (if needed)
	timer = new Timer(TimerInterruptHandler, 0, randomYield);

    threadToBeDestroyed = NULL;

    // We didn't explicitly allocate the current thread we are running in.
    // But if it ever tries to give up the CPU, we better have a Thread
    // object to save its state. 
    currentThread = new Thread("main");		
    currentThread->setStatus(RUNNING);

    interrupt->Enable();
    CallOnUserAbort(Cleanup);			// if user hits ctl-C
    
#ifdef USER_PROGRAM
    machine = new Machine(debugUserProg);	// this must come first
    
    
    //Project 2 Start

	osLockTableLock=new Lock("osLockTableLock");	 
	 for(int i=0;i<MAX_LOCKS;i++)
	{
	osLockTable[i]=NULL;
	}
	nextLockLocation=0;

	 osCVTableLock=new Lock("osCVTableLock");
	 //KernelCV* osCVTable[MAX_CVS];
	 for(int i=0;i<MAX_CVS;i++)
		{
			osCVTable[i]=NULL;
		}
	  nextCVLocation=0;


 myBitmapLock=new Lock("myBitMapLock");
 myBitmap=new BitMap(NumPhysPages);

  PCBTableLock=new Lock("PCBTableLock");
  for(int i=0;i<MAX_PROCESSES;i++)
 			{
 			PCBTable[i]=NULL;
 			}
 
 nextPCBLocation=0;
 noOfTotalProcesses=0;


	//Project 2 End
    
    
    
    
#endif






#ifdef FILESYS
    synchDisk = new SynchDisk("DISK");
#endif

#ifdef FILESYS_NEEDED
    fileSystem = new FileSystem(format);
#endif

#ifdef NETWORK
    postOffice = new PostOffice(netname, rely, 100);

	


#endif



/**********************************************************************/

  //Common For all Employees End
		for(int i=0;i<30;i++)
				for(int j=0;j<3;j++)
					{orderFromManager[j][i][0]=NoBreak;orderFromManager[j][i][1]=PreviousOrderComplete;}

  //Common For all Employees End

					
				for(int i=0;i<50;i++)
					{
					  withinGroupInteractionLock[i]=new Lock("GroupLock");
					} 
				for(int i=0;i<50;i++)
					{
					  withinGroupInteractionCV[i]=new Condition("WGCV");
					} 
				for(int i=0;i<50;i++)
					{
					  headOfGroupInteractionCV[i]=new Condition("HGCV");
					} 
					
		//for ticket takers initilisation code
				for(int i=0;i<MAX_TicketTakers;i++)
					{
					  ticketTakerState[i]=0;
					}
				
				for(int i=0;i<MAX_TicketTakers;i++)
					{
					  ticketTakerLineCount[i]=0;
					}
				
				for(int i=0;i<MAX_TicketTakers;i++)
					{
					 ticketTakerLineCV[i]=new Condition("TTLCV");
					}
				
				for(int i=0;i<MAX_TicketTakers;i++)
					{
					  ticketTakerCV[i]=new Condition("TTCV");
					} 
				
				for(int i=0;i<MAX_TicketTakers;i++)
					{
					  ticketTakerLock[i]=new Lock("TTL");
					}
				for(int i=0;i<MAX_TicketTakers;i++)
					{
					  ticketTakerFREECV[i]=new Condition("TTFFCV");
					} 
				
			   for(int i=0;i<MAX_TicketTakers;i++)
					{
					  numberOfTicketsForTicketTaker[0][i]=0;
					  numberOfTicketsForTicketTaker[1][i]=-1;
					  numberOfTicketsForTicketTaker[2][i]=0;
					}
					
					/*
				for(int i=0;i<MAX_TicketTakers;i++)
					{
					  ticketTakerFreeLock[i]=new Lock("TTL1");
					}					
				*/
						
				 ticketTakerLineLock=new Lock("TTLL");
		
               allOnBreakTicketTakerCV=new Condition("ABTTCV");
               allOnBreakTicketTakerCVCount=0;

				    remainingNoOfSeatsLock=new Lock("RNTL");
					remainingNoOfSeats=25;
				for(int i=0;i<MAX_TicketTakers;i++)
					{
					  myManagerTTLock[i]=new Lock("MMTTL");
					}
				for(int i=0;i<MAX_TicketTakers;i++)
					{				
						myManagerTTCV[i]=new Condition("MMTTCV");
					}
				for(int i=0;i<MAX_TicketTakers;i++)
					{
					    amIStuckTT[i]=false;
					}	
				for(int i=0;i<MAX_TicketTakers;i++)
					{
					 ticketTakerReArrangeCV[i]=new Condition("TTRACV");;
					}
		    currentShowFullTillThenEnjoyLobbyLock = new Lock("CSFTEL");
		    currentShowFullTillThenEnjoyLobbyCV = new Condition("Condition");
	   // ticket takers initilisation code ends HERE
	    
	 
	    
	      //for ticket clerk initilisation code
				for(int i=0;i<MAX_TicketClerks;i++)
					{
					  ticketClerkState[i]=0;
					}
				
				for(int i=0;i<MAX_TicketClerks;i++)
					{
					  ticketClerkLineCount[i]=0;
					}
				
				for(int i=0;i<MAX_TicketClerks;i++)
					{
					 ticketClerkLineCV[i]=new Condition("TCLCV");
					}
				
				for(int i=0;i<MAX_TicketClerks;i++)
					{
					  ticketClerkCV[i]=new Condition("TCCV");
					} 
				
				for(int i=0;i<MAX_TicketClerks;i++)
					{
					  ticketClerkLock[i]=new Lock("TCL");
					}
				
			   for(int i=0;i<MAX_TicketClerks;i++)
					{
					  numberOfTicketsForTicketClerk[0][i]=0;
					  numberOfTicketsForTicketClerk[1][i]=-1;
					  numberOfTicketsForTicketClerk[2][i]=0;
					}
				for(int i=0;i<MAX_TicketClerks;i++)
					{
					  ticketClerkCollection[i]=0;
					}
					
				for(int i=0;i<MAX_TicketClerks;i++)
					{
					  ticketClerkFREELock[i]=new Lock("TCL1");
					}
				for(int i=0;i<MAX_TicketClerks;i++)
					{
					  ticketClerkFREECV[i]=new Condition("TCCV1");
					} 
				
				 ticketClerkLineLock=new Lock("TCLL");
       // ticket takers initilisation code ends HERE
	   //for concession clerk initilisation code
				for(int i=0;i<MAX_ConcClerks;i++)
					{
					  concClerkState[i]=0;
					}
				
				for(int i=0;i<MAX_ConcClerks;i++)
					{
					  concClerkLineCount[i]=0;
					}
				 
				for(int i=0;i<MAX_ConcClerks;i++)
					{
					 concClerkLineCV[i]=new Condition("CCLCV");
					}
				
				for(int i=0;i<MAX_ConcClerks;i++)
					{
					  concClerkCV[i]=new Condition("CCCV");
					} 
				
				for(int i=0;i<MAX_ConcClerks;i++)
					{
					  concClerkLock[i]=new Lock("CCL");
					}
				
			   for(int i=0;i<MAX_ConcClerks;i++)
					{
					  myCustomersFoodChoices[0][i]=0;
					  myCustomersFoodChoices[1][i]=0;
					  myCustomersFoodChoices[2][i]=0;
					  myCustomersFoodChoices[3][i]=0;
					}
				for(int i=0;i<MAX_ConcClerks;i++)
					{
					  concClerkCollection[i]=0;
					}

				for(int i=0;i<MAX_ConcClerks;i++)
					{
					 myManagerCCCV[i]=new Condition("MMCCCV");

					}
				for(int i=0;i<MAX_ConcClerks;i++)
					{
					 concClerkFREECV[i]=new Condition("CCFCV");

					}
 
				for(int i=0;i<MAX_ConcClerks;i++)
					{
					 concClerkReArrangeCV[i]=new Condition("CCRACV");
					}
					
				allOnBreakConcClerkCV= new Condition("AOBCCCV");
	
				concClerkLineLock=new Lock("CCLL");
				
				for(int i=0;i<MAX_ConcClerks;i++)
					{
					 myManagerCCLock[i]=new Lock("CCRACV");
					}	


//ticketClerkNew
	for(int i=0;i<MAX_TicketClerks;i++)
					{
					  ticketClerkCollection[i]=0;
					}


				for(int i=0;i<MAX_TicketClerks;i++)
					{
					 myManagerTCCV[i]=new Condition("MMCCCV");

					}
				for(int i=0;i<MAX_TicketClerks;i++)
					{
					 ticketClerkReArrangeCV[i]=new Condition("TCRACV");

					}
					
					
				allOnBreakTicketClerkCV= new Condition("AOBTCCV");
	
				
				for(int i=0;i<MAX_TicketClerks;i++)
					{
					 myManagerTCLock[i]=new Lock("MMTCL");

					}
					
				for(int i=0;i<50;i++)
				{
					headMTechCV[i]=new Condition("headMTechCV");
				
				}	
				for(int i=0;i<50;i++)
				{
					headLobbyCV[i]=new Condition("headMTechCV");
				
				}	
	    	    
	    
	    
	    //Theatre Room Start
 			theatreRoomLock= new Lock("TRL");

	 			for(int i=0;i<5;i++)
						{	for(int j=0;j<5;j++)
								{	
									isTheatreRoomSeatAvlbl[i][j]=true;
								}
						}

		//Theatre Room End
			movieStatusLock=new Lock("MSL");
		    isMovieRunning=false;
		   areAllCustomersSatInTheatre=false;
		   numberOfCustomersSatInTheatre=0;
			    		letMovieTechnicianStartMovieLock=new Lock("MTLOCK");
						letMovieTechnicianStartMovieCV=new Condition("MTTCV");	
			numberOfCustEntertained=0;
			myManagerMTechLock=new Lock("MTECH");
			myManagerMTechCV=new Condition("MTechCV");
       		isMTReadyForManagerOrder=false;
       		numberOfPeopleLeftTheatre=0;
       		lastBatchEntertainedCount=0;
}

//----------------------------------------------------------------------
// Cleanup
// 	Nachos is halting.  De-allocate global data structures.
//----------------------------------------------------------------------
void
Cleanup()
{
    printf("\nCleaning up...\n");
#ifdef NETWORK
    delete postOffice;
#endif
    
#ifdef USER_PROGRAM
    delete machine;
#endif

#ifdef FILESYS_NEEDED
    delete fileSystem;
#endif

#ifdef FILESYS
    delete synchDisk;
#endif
    
    delete timer;
    delete scheduler;
    delete interrupt;
    
    Exit(0);
}


