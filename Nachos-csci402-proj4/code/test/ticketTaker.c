#include "syscall.h"

#define PRINTMETOO *65536+

#define GlobalnoOfGroups 7
#define GlobalGroupNormalCustSize 3
#define GlobalnoOfTC 5
#define GlobalnoOfCC 5
#define GlobalnoOfTT 3
	


	char ticketClerkLineCVChar[GlobalnoOfTC][50];
	char ticketClerkCVChar[GlobalnoOfTC][50];
	char ticketClerkLockChar[GlobalnoOfTC][50];
	char concessionClerkLineCVChar[GlobalnoOfCC][50];
	char concessionClerkCVChar[GlobalnoOfTC][50];
	char concessionClerkLockChar[GlobalnoOfCC][50];
	char ticketTakerLockChar[GlobalnoOfTT][50];
	char ticketTakerLineCVChar[GlobalnoOfTT][50];
	char ticketTakerCVChar[GlobalnoOfTT][50];
	char ttWaitShowOverLockChar[GlobalnoOfTT][50];
	char ttWaitShowOverCVChar[GlobalnoOfTT][50];
	char groupLockChar[GlobalnoOfGroups][50];
	char groupCVChar[GlobalnoOfGroups][50];
	char bathroomLobbyCVChar[GlobalnoOfGroups][50];


void Initialize()
{
	int i,j;
	int localGroupSize;
	int localNumberOfGroups;
	int concessionClerkStateRV;
	int ticketClerkStateRV;
	int ttTakingTicketsRV;
	int ticketTakerStateRV;
	int ticketTakerGroupIndicatorRV;
	int ticketTakerTheatreCountStatusRV;
	int localTotalCustomerNumber;
	int availableCustSizeForGroupArrRV;


	CreateLock("InitLock");

	Acquire("InitLock");

/*	int concessionClerkState[GlobalnoOfCC];				/*Stores the Concession Clerks State*/

	concessionClerkStateRV = CreateMV("ccState",GlobalnoOfCC);
	if(concessionClerkStateRV==1)
	{
		for(i=0;i<GlobalnoOfCC;i++)
		{
			SetMV("ccState",i,1);
		}
	}

/*	int ticketClerkState[GlobalnoOfTC];					/* Stores the state of each Ticket Clerk */
	
	ticketClerkStateRV = CreateMV("ticketClerkState",GlobalnoOfTC);
	if(ticketClerkStateRV==1)
	{
		for(i=0;i<GlobalnoOfTC;i++)
		{
			SetMV("ticketClerkState",i,1);
		}
	}

/*	int ttTakingTickets;							/*Stores if TT are taking tickets*/

	ttTakingTicketsRV = CreateMV("ttTakingTickets",1);
	if(ttTakingTicketsRV==1)
	{
		SetMV("ttTakingTickets",0,1);
	}



/*	int ticketTakerState[GlobalnoOfTT];					/*State of each TT(Ticket Taker)*/

	ticketTakerStateRV = CreateMV("ticketTakerState",GlobalnoOfTT);
	if(ticketTakerStateRV==1)
	{
		for(i=0;i<GlobalnoOfTT;i++)
		{
			SetMV("ticketTakerState",i,1);
		}
	}


/*	int ticketTakerGroupIndicator[GlobalnoOfTT];			/*Indicates a group whether to go inside or wait in lobby*/

	ticketTakerGroupIndicatorRV = CreateMV("TTGroupInd",GlobalnoOfTT);
	if(ticketTakerGroupIndicatorRV==1)
	{
		for(i=0;i<GlobalnoOfTT;i++)
		{
			SetMV("TTGroupInd",i,1);
		}
	}


/*	int ticketTakerTheatreCountStatus=1;			/*count for the ticket taker*/

	ticketTakerTheatreCountStatusRV = CreateMV("ttTheCount",1);
	if(ticketTakerTheatreCountStatusRV==1)
	{
		SetMV("ttTheCount",0,1);
	}

	/*	int availableCustSizeForGroupArr[50];		/*Array for each customer to determine its group*/
	availableCustSizeForGroupArrRV=CreateMV("avCustGrpArr",50);
	for(i=0;i<GlobalnoOfGroups;i++)
	{
		if(availableCustSizeForGroupArrRV==1)
		{
			SetMV("avCustGrpArr",i,GlobalGroupNormalCustSize);
		}
	}

	Release("InitLock");

	/*******************************************************************************************************/

/*	int totalCustomerNumber;						/* Total Number of Customers */
	CreateMV("totCustNum",1);

/*	int noOfGroups;								/* Stores the number of groups generated */
	CreateMV("noOfGroups",1);
	SetMV("noOfGroups",0,GlobalnoOfGroups);						/* %%%%%%%%%%%%%% For the time being. %%%%%%%%%%%%%%%% */

/*	int noOfTC;*/
	CreateMV("noOfTC",1);
	SetMV("noOfTC",0,GlobalnoOfTC);

/*	int noOfCC;*/
	CreateMV("noOfCC",1);
	SetMV("noOfCC",0,GlobalnoOfCC);

/*	int noOfTT;*/
	CreateMV("noOfTT",1);
	SetMV("noOfTT",0,GlobalnoOfTT);

/*	int noOfCustomers;*/
	CreateMV("noOfCustomers",1);

/*	int groupSize;*/
	CreateMV("groupSize",1);

/*	int totalAmtTicket;*/							/* Total Amount Variable */
	CreateMV("totalAmtTicket",1);

/*	int noOfTickets[GlobalnoOfTC];						/* Keep track of no. of tickets sold by each clerk */
	CreateMV("noOfTickets",GlobalnoOfTC);

/*	int ticketClerkAmount[GlobalnoOfTC];				/* Amount given by customer at each TicketClerk */
	CreateMV("ticketClerkAmount",GlobalnoOfTC);

/*	int totalAmountTicketClerk[GlobalnoOfTC];			/* Amount deposited at each TicketClerk */
	CreateMV("totAmtTC",GlobalnoOfTC);

/*	int ticketClerkOnBreak=0;						/* Count of the Ticket Clerks on break*/
	CreateMV("tcOnBreak",1);

/*	int managerTcWait[GlobalnoOfTC];					/* Manager signal for each Ticket Clerk*/
	CreateMV("managerTcWait",GlobalnoOfTC);

/*	int custFindLineTC[GlobalnoOfTC];					/* Variable to say that broadcast customers*/
	CreateMV("custFindLineTC",GlobalnoOfTC);

/*	int reFindLineTC[GlobalnoOfTC];						/*Flag to say that the customer has to find line again*/
	CreateMV("reFindLineTC",GlobalnoOfTC);

/*	int totalAmountConcessionClerk[GlobalnoOfCC];		/*Total Amount stored by all Concession Clerks*/
	CreateMV("totAmtCC",GlobalnoOfCC);


/*	int concessionClerkLineCount[GlobalnoOfCC];			/*Stores the Concession Clerks Line Count*/
	CreateMV("ccLineCnt",GlobalnoOfCC);



	/* $$$$$$$$ Ticket Clerk Variables $$$$$$$$ */



/*	int ticketClerkLineCount[GlobalnoOfTC];				/* Stores the Line Count of each Ticket Clerk */
	CreateMV("tcLineCnt",GlobalnoOfTC);

/*	int ticketClerkLineCVInt[GlobalnoOfTC]; */

/*	char ticketClerkLineCVChar[GlobalnoOfTC][200]; */
	for(i=0;i<GlobalnoOfTC;i++)
	{
		Sprint(ticketClerkLineCVChar[i],"TCLineCV",i);			/*changed this $$$$$$$$$$$$$$$$$$$$*/
		CreateCV(ticketClerkLineCVChar[i]);
	}


/*	int ticketClerkLineLockInt; */
	CreateLock("tcLineLock");

/*	int totalAmtTicketLockInt; */
	CreateLock("toAmtTktLck");

/*	int ticketClerkCVInt[GlobalnoOfTC]; */

/*	char ticketClerkCVChar[GlobalnoOfTC][200]; */
	for(i=0;i<GlobalnoOfTC;i++)
	{
		Sprint(ticketClerkCVChar[i],"TCCV",i);	
		CreateCV(ticketClerkCVChar[i]);
	}

/*	int ticketClerkLockInt[GlobalnoOfTC]; */

/*	char ticketClerkLockChar[GlobalnoOfTC][200]; */
	for(i=0;i<GlobalnoOfTC;i++)
	{
		Sprint(ticketClerkLockChar[i],"TCLock",i);	
		CreateLock(ticketClerkLockChar[i]);
	}


/*	int concessionClerkLineCVInt[GlobalnoOfCC]; */

/*	char concessionClerkLineCVChar[GlobalnoOfCC][200]; */
	for(i=0;i<GlobalnoOfCC;i++)
	{
		Sprint(concessionClerkLineCVChar[i],"CCLineCV",i);	
		CreateCV(concessionClerkLineCVChar[i]);
	}

/*	int concessionClerkLineLockInt; */
	CreateLock("ccLineLock");

/*	int totalAmtPopSodaLockInt; */
	CreateLock("toAmtPopLck");

/*	int noOfSoda[GlobalnoOfCC];							/*customer Vaiable to store soda value on a Concession Clerk*/
	CreateMV("noOfSoda",GlobalnoOfCC);

/*	int noOfPopcorn[GlobalnoOfCC];						/*customer Vaiable to store popcorn value on a Concession Clerk*/
	CreateMV("noOfPopcorn",GlobalnoOfCC);

/*	int totalMoneySoda;								/*total money by Soda*/
	CreateMV("totalMoneySoda",1);

/*	int totalMoneyPopcorn;							/*total money by popcorn*/
	CreateMV("totalMoneyPopcorn",1);

/*	int amountSoda[GlobalnoOfCC];							/*Amount customer has to pay for Soda*/
	CreateMV("amountSoda",GlobalnoOfCC);

/*	int amountPopcorn[GlobalnoOfCC];						/*Amount customer has to pay for Popcorn*/
	CreateMV("amountPopcorn",GlobalnoOfCC);

/*	int concessionClerkCVInt[GlobalnoOfCC]; */

/*	char concessionClerkCVChar[GlobalnoOfTC][200]; */
	for(i=0;i<GlobalnoOfTC;i++)
	{
		Sprint(concessionClerkCVChar[i],"CCCV",i);	
		CreateCV(concessionClerkCVChar[i]);
	}

/*	int concessionClerkLockInt[GlobalnoOfCC]; */

/*	char concessionClerkLockChar[GlobalnoOfCC][200]; */
	for(i=0;i<GlobalnoOfCC;i++)
	{
		Sprint(concessionClerkLockChar[i],"CCLock",i);	
		CreateLock(concessionClerkLockChar[i]);
	}

/*	int conClerkOnBreak=0;							/*Count of CCs on break*/
	CreateMV("conClerkOnBreak",1);

/*	int managerCcWait[GlobalnoOfCC];						/*Flag for wait of CC*/
	CreateMV("managerCcWait",GlobalnoOfCC);

/*	int custFindLineCC[GlobalnoOfCC];						/*Variable of CC to tell customer to find line*/
	CreateMV("custFindLineCC",GlobalnoOfCC);

/*	int reFindLineCC[GlobalnoOfCC];						/*Flag for customer to find line again*/
	CreateMV("reFindLineCC",GlobalnoOfCC);



	/*********Variables for Technician Manager and Customer Interaction*********/

/*	int movieTheaterLockInt; */
	CreateLock("movieTheaterLock");

/*	int movieTheaterCVInt; */
	CreateCV("movieTheaterCV");

/*	int custEnteredTheater;							/*Count of Cust entering the theater room*/
	CreateMV("custEnteredTheater",1);

/*	int custLeavingTheater;							/*Count of Cust leaving the theater room*/
	CreateMV("custLeavingTheater",1);



/*	int isMovieOver;								/* Stores the movie state*/
	CreateMV("isMovieOver",1);

/*	int movieTechLockInt;							/* Lock for Movie Technician */
	CreateLock("movieTechLock");

/*	int movieTechCVInt;								/* Conditon Variable for Technician*/
	CreateCV("movieTechCV");

/*	int custFinalExitLockInt;						/* Lock for count of finally exiting customers*/
	CreateLock("custFinalExitLock");

/*	int custFinalExitCount;							/*Variable for count of finally exiting customers*/
	CreateMV("custFinalExitCount",1);


	
	/*/////////////////////////////Ticket Taker//////////////////////////////////*/

/*	int custTicketsApproved=0;						/*Stores the no of tickets approved to go inside theater room*/
	CreateMV("custTicketsApproved",1);



/*	int ticketTakerLineCount[GlobalnoOfTT];				/*Stores the Line count of each TT*/
	CreateMV("ttLineCnt",GlobalnoOfTT);



/*	int custNoOfTicket[GlobalnoOfTT];						/*Number of tickets of each group*/
	CreateMV("custNoOfTicket",GlobalnoOfTT);



/*	int ticketTakerLineLockInt;						/* Lock for the TT Line*/
	CreateLock("ttLineLock");

/*	int ticketTakerLockInt[GlobalnoOfTT];					/* Lock for each TT*/

/*	char ticketTakerLockChar[GlobalnoOfTT][200]; */
	for(i=0;i<GlobalnoOfTT;i++)
	{
		Sprint(ticketTakerLockChar[i],"TTLock",i);	
		CreateLock(ticketTakerLockChar[i]);
	}

/*	int ticketTakerManagerLockInt;					/* TicketTaker Manager Lock*/
	CreateLock("ttMgrLock");

/*	int custTicketsApprovedLockInt;					/* Lock for total tickets approved to go inside*/
	CreateLock("TktsAppLock");

/*	int ticketTakerLineCVInt[GlobalnoOfTT];				/* CV for each TT Line*/

/*	char ticketTakerLineCVChar[GlobalnoOfTT][200]; */
	for(i=0;i<GlobalnoOfTT;i++)
	{
		Sprint(ticketTakerLineCVChar[i],"TTLineCV",i);	
		CreateCV(ticketTakerLineCVChar[i]);
	}

/*	int ticketTakerCVInt[GlobalnoOfTT];					/* CV for each TT interaction*/

/*	char ticketTakerCVChar[GlobalnoOfTT][200]; */
	for(i=0;i<GlobalnoOfTT;i++)
	{
		Sprint(ticketTakerCVChar[i],"TTCV",i);	
		CreateCV(ticketTakerCVChar[i]);
	}

/*	int ticketTakerManagerCVInt;					/* CV for Technician */
	CreateCV("ttMgrCV");

/*	int customerLobbyCVInt;							/*CV for Lobby*/
	CreateCV("customerLobbyCV");

/*	int customerLobbyLockInt;						/*Lock for Lobby*/
	CreateLock("customerLobbyLock");

/*	int isTakingTickets;							/*Stores whether the TT is taking tickets or not*/
	CreateMV("isTakingTickets",1);

/*	int ttWaitShowOverLockInt[GlobalnoOfTT];				/*Lock for TT till the next show starts*/

/*	char ttWaitShowOverLockChar[GlobalnoOfTT][200]; */
	for(i=0;i<GlobalnoOfTT;i++)
	{
		Sprint(ttWaitShowOverLockChar[i],"ttWSOLock",i);	
		CreateLock(ttWaitShowOverLockChar[i]);
	}

/*	int ttWaitShowOverCVInt[GlobalnoOfTT];				/*CV for waiting of TT till next show start*/

/*	char ttWaitShowOverCVChar[GlobalnoOfTT][200]; */
	for(i=0;i<GlobalnoOfTT;i++)
	{
		Sprint(ttWaitShowOverCVChar[i],"ttWSOCV",i);	
		CreateCV(ttWaitShowOverCVChar[i]);
	}




	/***************************Variables for Group Interaction*********************************/

/*	int groupLockInt[GlobalnoOfGroups];						/*Group Lock for each group*/

/*	char groupLockChar[GlobalnoOfGroups][200]; */
	for(i=0;i<GlobalnoOfGroups;i++)
	{
		Sprint(groupLockChar[i],"groupLock",i);	
		CreateLock(groupLockChar[i]);
	}

/*	int groupCVInt[GlobalnoOfGroups];						/* CV for each group*/

/*	char groupCVChar[GlobalnoOfGroups][200]; */
	for(i=0;i<GlobalnoOfGroups;i++)
	{
		Sprint(groupCVChar[i],"groupCV",i);	
		CreateCV(groupCVChar[i]);
	}

/*	int canGoInsideTheater[GlobalnoOfGroups];				/*Stores whether Cust can go inside*/
	CreateMV("canGoInsideTheater",GlobalnoOfGroups);

/*	int canGoBathroom[GlobalnoOfGroups];						/*Stores whtehr cust can go to bathroom*/
	CreateMV("canGoBathroom",GlobalnoOfGroups);

/*	int counterAfterMuvi[GlobalnoOfGroups];					/* stores the count of cust got up after movie*/
	CreateMV("counterAfterMuvi",GlobalnoOfGroups);

/*	int counterAfterBathroom[GlobalnoOfGroups];				/* stores the count of cust going to bathroom*/
	CreateMV("ctrAfterBath",GlobalnoOfGroups);

/*	int bathroomLobbyCVInt[GlobalnoOfGroups];				/* CV for use when other cust has to wait when 1 goes to bathroom*/

/*	char bathroomLobbyCVChar[GlobalnoOfGroups][200]; */
	for(i=0;i<GlobalnoOfGroups;i++)
	{
		Sprint(bathroomLobbyCVChar[i],"bLobbyCV",i);	
		CreateCV(bathroomLobbyCVChar[i]);
	}

/*	int bathroomLockInt;							/* Lock for bathroom*/
	CreateLock("bathroomLock");

/*	int ttWaitingAfterFull[GlobalnoOfTT]; */
	CreateMV("ttWaitingAfterFull",GlobalnoOfTT);

/*	int managerWokeTT[GlobalnoOfTT];					/*manager waking up TT to start taking ticket*/
	CreateMV("managerWokeTT",GlobalnoOfTT);

/*	int countCustTT;							/*count of cust going to TT*/
	CreateMV("countCustTT",1);
	
/*	int total; */
	CreateMV("total",1);

/*	int totalHeadCust;							/*Count of all head customer*/
	CreateMV("totalHeadCust",1);

/*	int groupPopcorn[GlobalnoOfGroups];					/*popcorn by each group*/
	CreateMV("groupPopcorn",GlobalnoOfGroups);

/*	int groupSoda[GlobalnoOfGroups];						/* Soda ordered by each group*/
	CreateMV("groupSoda",GlobalnoOfGroups);

/*	int haveTickets[GlobalnoOfGroups];					/*Stores whtehr the head have tickets or not*/
	CreateMV("haveTickets",GlobalnoOfGroups);

/*	int givenFoodChoice[GlobalnoOfGroups];				/*sores whther give the food choice*/
	CreateMV("givenFoodChoice",GlobalnoOfGroups);

	/*Seat variabes*/
/*	int rowNo,columnNo;							/*row number and column number of seat*/
	CreateMV("rowNo",1);
	CreateMV("columnNo",1);

/*	int counterVal[GlobalnoOfGroups];					/*counter for each customer accessing seat*/
	CreateMV("counterVal",GlobalnoOfGroups);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/*	int movieRoomSeatNoArray[5][5];				/*array for storing seat avaible or not

	int movieRoomGrpNoArray[5][5];				/*array for storing seat assigned to which group
*/

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/*	int sizeForGroupArr[50];					/*Storing the group size for each group*/
	CreateMV("sizeForGroupArr",50);


	/*Global Part for TC myIndex value*/

/*	int ticketClerkIndexLockInt; */
	CreateLock("ticketClerkIndexLock");

/*	int nextTCIndex=0; */
	CreateMV("nextTCIndex",1);


	/*Global Part for Customer value*/

/*	int groupNumberLockInt, customerNumberLockInt, groupSizeLockInt; */
	CreateLock("groupNumberLock");
	CreateLock("customerNumberLock");
	CreateLock("groupSizeLock");

/*	int nextGroupNumber=0, nextCustomerNumber=0, nextGroupSize=0; */
	CreateMV("nextGroupNumber",1);
	CreateMV("nextCustomerNumber",1);
	CreateMV("nextGroupSize",1);


	/*Global Part for CC myIndex value*/

/*	int concessionClerkIndexLockInt; */
	CreateLock("ccIndexLock");

/*	int nextCCIndex=0; */
	CreateMV("nextCCIndex",1);

/*	int determineCustGroupNumberLockInt; */
	CreateLock("custGrpNumLock");



	/*Global Part for TT myIndex value*/

/*	int ticketTakerIndexLockInt; */
	CreateLock("ticketTakerIndexLock");

/*	int nextTTIndex=0; */
	CreateMV("nextTTIndex",1);

/*	int checkFinalExitLockInt; */
	CreateLock("checkFinalExitLock");

/*	int finalExitFlag=0; */
	CreateMV("finalExitFlag",1);


/*	numberOfGroups=noOfGroups;*/								/*$$$$$$$$$$$$$$$$$ From Main Function $$$$$$$$$$$$$$$$$*/
	localNumberOfGroups=GetMV("noOfGroups",0);


/*	Acquire("InitLock");				/* ############################################################### */

/*	totalHeadCust=numberOfGroups;*/

	SetMV("totalHeadCust",0,localNumberOfGroups);


		SetMV("totCustNum",0,GlobalnoOfGroups*(GlobalGroupNormalCustSize+1));

	for(i=0;i<localNumberOfGroups;i++)
	{
/*		groupSize=Rand(5);*/
		/*localGroupSize = Rand(5);*/			/*$$$$$$$$$$$$$$$$$ Hardcoded to 0 $$$$$$$$$$$$$$$$$*/		
		localGroupSize=0;

		SetMV("groupSize",0,GlobalGroupNormalCustSize);


/*		sizeForGroupArr[i]=groupSize;								/*Assigning group size*/ 
		localGroupSize = GetMV("groupSize",0);
		SetMV("sizeForGroupArr",i,localGroupSize);

/*		availableCustSizeForGroupArr[i]=groupSize; */

/*		if(availableCustSizeForGroupArrRV==1)
		{
		SetMV("avCustGrpArr",i,localGroupSize);			//Removed from here to top, inside the lock.
		}
*/


/*		totalCustomerNumber++;*/
		localTotalCustomerNumber=GetMV("totCustNum",0);
	/*	SetMV("totCustNum",0,localTotalCustomerNumber+1);*/

		for (j=0;j<localGroupSize;j++ )
		{
/*			totalCustomerNumber++; */
		localTotalCustomerNumber=GetMV("totCustNum",0);
		/*	SetMV("totCustNum",0,localTotalCustomerNumber+1);*/

/*			Fork(Customer); */
		}
	
	}

/*	Release("InitLock");				/* ############################################################### */


/*	Release("InitLock"); */
}








void TicketTaker()
{
	int check = 1;														/* Check that its not coming from wait state. */

	int myIndex;
	int localTicketTakerLineCount;
	int localFinalExitFlag;
	int localManagerWokeTT;
	int localCustNoOfTicket;
	int localCustTicketsApproved;


/*	Acquire(ticketTakerIndexLockInt); */
	Acquire("ticketTakerIndexLock");

/*	myIndex=nextTTIndex; */ 
	myIndex=GetMV("nextTTIndex",0);

/*	nextTTIndex++; */
	SetMV("nextTTIndex",0,myIndex+1);

/*	Release(ticketTakerIndexLockInt); */
	Release("ticketTakerIndexLock");

	while(1)
	{ 
/*		Acquire(ticketTakerLineLockInt); */
		Acquire("ttLineLock");
		
/*		if(ticketTakerLineCount[myIndex]>0) */

		localTicketTakerLineCount = GetMV("ttLineCnt",myIndex);

		if(localTicketTakerLineCount>0)
		{
			check=0;													/* If any customer is waiting in his line. */

/*			ticketTakerState[myIndex]=1; */
			SetMV("ticketTakerState",myIndex,1);

/*			ticketTakerLineCount[myIndex]--; */

			localTicketTakerLineCount = GetMV("ttLineCnt",myIndex);
			SetMV("ttLineCnt",myIndex,localTicketTakerLineCount-1);

/*			Print("\nTicketTaker[%d] has a line length [%d] and is signaling a customer.\n",myIndex,ticketTakerLineCount[myIndex] PRINTMETOO 1, 1); */

			localTicketTakerLineCount = GetMV("ttLineCnt",myIndex);
			Print("\nTicketTaker[%d] has a line length [%d] and is signaling a customer.\n",myIndex,localTicketTakerLineCount PRINTMETOO 1, 1);

/*			Signal(ticketTakerLineCVInt[myIndex],ticketTakerLineLockInt); */
			Signal(ticketTakerLineCVChar[myIndex],"ttLineLock");
		}

		else
		{
			/* If nobody was present infront of him and then too manager asked him to take tickets, so will wait until the last customer. */

			check=0;

/*			ticketTakerState[myIndex]=0; */
			SetMV("ticketTakerState",myIndex,0);

			Print("\nTicketTaker[%d] has no one in line. I am available for a customer.\n",myIndex,1,1);
		/*Print("\nState of TT[%d] is now %d\n",myIndex,GetMV("ticketTakerState",myIndex) PRINTMETOO 1,1);*/
		}

/*		Acquire(ticketTakerLockInt[myIndex]); */
		Acquire(ticketTakerLockChar[myIndex]);
		
/*		Release(ticketTakerLineLockInt); */
		Release("ttLineLock");

/*		Wait(ticketTakerCVInt[myIndex],ticketTakerLockInt[myIndex]); */
		Wait(ticketTakerCVChar[myIndex],ticketTakerLockChar[myIndex]);

		/* $$$$$$$$$$$$   check final exit condition after being signalled  from their queue  $$$$$$$$$$$$ */

/*		Acquire(checkFinalExitLockInt); */
		Acquire("checkFinalExitLock");

/*		if (finalExitFlag==1) */

		localFinalExitFlag = GetMV("finalExitFlag",0);

		if (localFinalExitFlag==1)
		{
/*			Release(checkFinalExitLockInt);								/*Manager woke me up and asking me to exit*/
			Release("checkFinalExitLock");

			break;
		}		

/*		Release(checkFinalExitLockInt); */
		Release("checkFinalExitLock");
		
		/* If I am woken up by manager, this will happen when all the cust have taken tickets and nobody left. */

/*		if (managerWokeTT[myIndex]==1) */

		localManagerWokeTT = GetMV("managerWokeTT",myIndex);

		if (localManagerWokeTT==1)
		{
							/*Print("\nInside..Manager woke TT\n",1,1,1);*/
			check=0;
			
/*			Release(ticketTakerLockInt[myIndex]);						/* Manager Told ~~~~ TicketTaker to stop taking tickets. */
			Release(ticketTakerLockChar[myIndex]);

/*			Acquire(ticketTakerLineLockInt); */
			Acquire("ttLineLock");

/*			ticketTakerState[myIndex]=-1; */
			SetMV("ticketTakerState",myIndex,-1);

/*Print("\nInside..ticketTakerState is now set to %d\n",GetMV("ticketTakerState",myIndex),1,1);*/


/*			Acquire(ttWaitShowOverLockInt[myIndex]); */
			Acquire(ttWaitShowOverLockChar[myIndex]);
			
/*			Release(ticketTakerLineLockInt); */
			Release("ttLineLock");

/*			Wait(ttWaitShowOverCVInt[myIndex],ttWaitShowOverLockInt[myIndex]);				/* waiting on the CV, will come out when Manager will ask him to do so. */
			Wait(ttWaitShowOverCVChar[myIndex],ttWaitShowOverLockChar[myIndex]);

/*			Release(ttWaitShowOverLockInt[myIndex]); */
			Release(ttWaitShowOverLockChar[myIndex]);

			/* $$$$$$$$$$$$   check final exit condition after being signalled  from their manager queue  $$$$$$$$$$$$ */

/*			Acquire(checkFinalExitLockInt); */
			Acquire("checkFinalExitLock");

/*			if (finalExitFlag==1) */

			localFinalExitFlag = GetMV("finalExitFlag",0);

			if (localFinalExitFlag==1)
			{
/*				Release(checkFinalExitLockInt);							/*Manager woke me up and asking me to exit*/
				Release("checkFinalExitLock");

				break;
			}		

/*			Release(checkFinalExitLockInt); */
			Release("checkFinalExitLock");

/*			Acquire(ticketTakerLockInt[myIndex]); */
			Acquire(ticketTakerLockChar[myIndex]);

/*			managerWokeTT[myIndex]=0; */
			SetMV("managerWokeTT",myIndex,0);

/*			Release(ticketTakerLockInt[myIndex]); */
			Release(ticketTakerLockChar[myIndex]);

			continue;
		}
	
/*		Acquire(custTicketsApprovedLockInt); */
		Acquire("TktsAppLock"); 
		
		/* Checking that the number of tickets customer has do not exceed the theater room capacity. */

/*		if (custTicketsApproved+custNoOfTicket[myIndex] <=25)							/* Number of tickets customer has are approved. */

		localCustTicketsApproved = GetMV("custTicketsApproved",0);
		localCustNoOfTicket = GetMV("custNoOfTicket",myIndex);

		if (localCustTicketsApproved+localCustNoOfTicket <=25)
		{
/*			Print("\nTicketTaker[%d] is allowing the group into the theater. The number of tickets taken is %d.\n",myIndex,custNoOfTicket[myIndex] PRINTMETOO 1,1); */
		
			/*localcustNoOfTicket = GetMV("custNoOfTicket",myIndex);*/
			Print("\nTicketTaker[%d] is allowing the group into the theater. The number of tickets taken is %d.\n",myIndex,localCustNoOfTicket PRINTMETOO 1,1);

/*			custTicketsApproved+=custNoOfTicket[myIndex]; */

			localCustTicketsApproved = GetMV("custTicketsApproved",0);
			localCustNoOfTicket = GetMV("custNoOfTicket",myIndex);
			SetMV("custTicketsApproved",0,localCustTicketsApproved+localCustNoOfTicket);

/*			Release(custTicketsApprovedLockInt); */
			Release("TktsAppLock");

/*			ticketTakerGroupIndicator[myIndex]=1; */
			SetMV("TTGroupInd",myIndex,1);

/*			Signal(ticketTakerCVInt[myIndex],ticketTakerLockInt[myIndex]); */
			Signal(ticketTakerCVChar[myIndex],ticketTakerLockChar[myIndex]);

/*			Release(ticketTakerLockInt[myIndex]); */
			Release(ticketTakerLockChar[myIndex]);
		}

		else																	/* No of tickets that cust has are exceeding the teater capacity. */
		{
/*			Print("\nTicketTaker[%d] is not allowing the group into the theater. The number of taken tickets is %d and the group size is %d including HeadCustomer.\n",myIndex,custTicketsApproved PRINTMETOO custNoOfTicket[myIndex],1); */

			localCustTicketsApproved = GetMV("custTicketsApproved",0);
			localCustNoOfTicket = GetMV("custNoOfTicket",myIndex);

			Print("\nTicketTaker[%d] is not allowing the group into the theater. The number of taken tickets is %d and the group size is %d including HeadCustomer.\n",myIndex,localCustTicketsApproved PRINTMETOO localCustNoOfTicket,1);

			Print("\nTicketTaker[%d] has stopped taking tickets\n",myIndex,1,1);

/*			Release(custTicketsApprovedLockInt); */
			Release("TktsAppLock");

/*			ticketTakerGroupIndicator[myIndex]=0; */
			SetMV("TTGroupInd",myIndex,0); 

/*			Signal(ticketTakerCVInt[myIndex],ticketTakerLockInt[myIndex]);				/* Signal to go in lobby. */
			Signal(ticketTakerCVChar[myIndex],ticketTakerLockChar[myIndex]);

/*			ttWaitingAfterFull[myIndex]=1; */
			SetMV("ttWaitingAfterFull",myIndex,1); 

/*			Release(ticketTakerLockInt[myIndex]); */
			Release(ticketTakerLockChar[myIndex]);

/*			Acquire(ticketTakerLineLockInt); */
			Acquire("ttLineLock");

/*			ticketTakerState[myIndex]=-1; */
			SetMV("ticketTakerState",myIndex,-1);

			/* Ask other cust in Line to go back to lobby as I have rejected 1 cust. */

/*			Broadcast(ticketTakerLineCVInt[myIndex],ticketTakerLineLockInt); */
			Broadcast(ticketTakerLineCVChar[myIndex],"ttLineLock");

/*			Release(ticketTakerLineLockInt); */
			Release("ttLineLock");					

			/* Going to wait state. Now when manager will change my state, customer will come and wake me up. */

/*			Acquire(ttWaitShowOverLockInt[myIndex]); */
			Acquire(ttWaitShowOverLockChar[myIndex]);

/*			Wait(ttWaitShowOverCVInt[myIndex],ttWaitShowOverLockInt[myIndex]); */
			Wait(ttWaitShowOverCVChar[myIndex],ttWaitShowOverLockChar[myIndex]);

/*			Release(ttWaitShowOverLockInt[myIndex]); */
			Release(ttWaitShowOverLockChar[myIndex]);

			check = 1;

		/* $$$$$$$$$$$$   check final exit condition after being signalled  from their manager queue  $$$$$$$$$$$$ */

/*			Acquire(checkFinalExitLockInt); */
			Acquire("checkFinalExitLock");

/*			if (finalExitFlag==1) */

			localFinalExitFlag = GetMV("finalExitFlag",0);

			if (localFinalExitFlag==1)
			{
/*				Release(checkFinalExitLockInt);									/*Manager woke me up and asking me to exit*/
				Release("checkFinalExitLock");

				break;
			}		

/*			Release(checkFinalExitLockInt); */
			Release("checkFinalExitLock");

/*			Acquire(ticketTakerLockInt[myIndex]); */
			Acquire(ticketTakerLockChar[myIndex]);

/*			ttWaitingAfterFull[myIndex]=0; */
			SetMV("ttWaitingAfterFull",myIndex,0); 

/*			Release(ticketTakerLockInt[myIndex]); */
			Release(ticketTakerLockChar[myIndex]);
		}

	}  																			/* End of while statement. */

}





void main()
{
	Initialize();
	TicketTaker();
	Exit(0);
}