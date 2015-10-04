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





void CustomerHead()
{
	int i,j;
	int myTicketClerk;
	int myConcessionClerk;
	int shortestTCLine;
	int shortestTCLineLen;
	int popRandVal;
	int sodaRandVal;
	int printPop;
	int printSoda;
	int shortestCCLine;
	int shortestCCLineLen;
	int foodAmount;
	int myTicketTaker;
	int shortestTTLine;
	int shortestTTLineLen;

	int bathRoomValue;
	int myGroupNumber,myCustomerNumber,myGroupSize;


	int localNoOfTC;
	int localTicketClerkState;
	int localReFindLineTC;
	int localCustFindLineTC;
	int localTicketClerkAmount;
	
	int localNoOfCC;
	int localConcessionClerkState;	
	int localConcessionClerkLineCount;
	int localCustFindLineCC;

	int localIsTakingTickets;
	int localTicketTakerState;
	int localTicketTakerLineCount;
	int localTotal;
	int localTicketClerkLineCount;

	int localRowNo;
	int localColumnNo;

	int localGroupPopcorn;
	int localGroupSoda;
	int localReFindLineCC;
	int localNoOfPopcorn;
	int localNoOfSoda;
	int localAmountSoda;
	int localAmountPopcorn;

	int localNoOfTT;
	int localTicketTakerGroupIndicator;
	int localCountCustTT;
	int localCustEnteredTheater;
	int localCustLeavingTheater;
	int localCustFinalExitCount;
	int localCounterVal;


/*	Acquire(groupNumberLockInt); */
	Acquire("groupNumberLock");

/*	myGroupNumber=nextGroupNumber; */
	myGroupNumber=GetMV("nextGroupNumber",0);
/*Print("\n The value of GET myGroupNumber is %d\n",myGroupNumber,1,1);*/

/*	nextGroupNumber++; */
	SetMV("nextGroupNumber",0,myGroupNumber+1);
/*Print("\n The value being SET of myGroupNumber is %d\n",myGroupNumber+1,1,1);
Print("\n The value after SET of myGroupNumber is %d\n",GetMV("nextGroupNumber",0),1,1);*/


/*	Release(groupNumberLockInt); */
	Release("groupNumberLock");

/*	Acquire(customerNumberLockInt); */
	Acquire("customerNumberLock");

/*	myCustomerNumber=nextCustomerNumber; */
	myCustomerNumber=GetMV("nextCustomerNumber",0);

/*	nextCustomerNumber++; */
	SetMV("nextCustomerNumber",0,myCustomerNumber+1);

/*	Release(customerNumberLockInt); */
	Release("customerNumberLock");

/*	myGroupSize=sizeForGroupArr[myGroupNumber]; */
	myGroupSize=GetMV("sizeForGroupArr",myGroupNumber);
/*Print("\n The value after GET of myGroupSize is %d\n",GetMV("sizeForGroupArr",myGroupNumber),1,1);
Print("\n The value of GroupSize is %d\n",myGroupSize+1,1,1);*/

	while(1)
	{ 
		myTicketClerk=-1;

/*		Acquire(ticketClerkLineLockInt); */
		Acquire("tcLineLock");
	
/*		for (i=0;i<noOfTC;i++)								/* If any TC is available, not busy */
		
		localNoOfTC = GetMV("noOfTC",0);

		for (i=0;i<localNoOfTC;i++)							/* If any TC is available, not busy */
		{
/*			if (ticketClerkState[i]==0) */

			localTicketClerkState = GetMV("ticketClerkState",i);

			if (localTicketClerkState==0)
			{
				myTicketClerk=i;

/*				ticketClerkState[i]=1; */
				SetMV("ticketClerkState",i,1);

				Print("\nCustomer[%d] in Group[%d] is getting in TicketClerk line[%d]\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,1);

				break;
			}		
		}	
		
		if (myTicketClerk == -1)							/*Acquiring the shortest Line*/
		{
/*			shortestTCLine; */

/*			shortestTCLineLen=ticketClerkLineCount[0]; */
			shortestTCLineLen = GetMV("tcLineCnt",0);

/*			for(i=0;i<noOfTC;i++) */

			localNoOfTC = GetMV("noOfTC",0);
			
			for(i=0;i<localNoOfTC;i++)
			{
/*				if(ticketClerkState[i]!=-2)								/*check that the TC is not on break*/

				localTicketClerkState = GetMV("ticketClerkState",i);

				if(localTicketClerkState!=-2)							/*check that the TC is not on break*/
				{
					shortestTCLine=i;

/*					shortestTCLineLen=ticketClerkLineCount[i]; */
					shortestTCLineLen=GetMV("tcLineCnt",i);

					break;
				}

				else
				{
																		/*checking which all TCs are on break*/
					Print("\nCustomer[%d] in Group [%d] sees TicketClerk[%d] is on break.\n\0",myCustomerNumber,myGroupNumber PRINTMETOO i,1);
				}
			}		
			
/*			for (i=1;i<noOfTC;i++ )										/*Assigning the TC with shortest Line*/

			localNoOfTC = GetMV("noOfTC",0);

			for (i=1;i<localNoOfTC;i++)
			{
/*				if (ticketClerkState[i]==1 && (shortestTCLineLen > ticketClerkLineCount[i])) */

				localTicketClerkState = GetMV("ticketClerkState",i);
				localTicketClerkLineCount = GetMV("tcLineCnt",i);

				if (localTicketClerkState==1 && (shortestTCLineLen > localTicketClerkLineCount))
				{
					shortestTCLine=i;

/*					shortestTCLineLen=ticketClerkLineCount[i]; */
					shortestTCLineLen = GetMV("tcLineCnt",i);
				}
			}

			myTicketClerk=shortestTCLine;

/*			ticketClerkLineCount[myTicketClerk]++; */

			localTicketClerkLineCount = GetMV("tcLineCnt",myTicketClerk);
			SetMV("tcLineCnt",myTicketClerk,localTicketClerkLineCount+1);

			Print("\nCustomer[%d] in Group[%d] is getting in TicketClerk line[%d]\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,1);
		
/*			Wait(ticketClerkLineCVInt[myTicketClerk],ticketClerkLineLockInt); */
			Wait(ticketClerkLineCVChar[myTicketClerk],"tcLineLock");
		}
	
/*		if(reFindLineTC[myTicketClerk]==1)				/*If I have been asked to re-acquire the line*/
		
		localReFindLineTC = GetMV("reFindLineTC",myTicketClerk);

		if(localReFindLineTC==1)						/*If I have been asked to re-acquire the line*/
		{
			/*customers in the line of  ticketclerk[%d] are starting the process of finding shortest line again as they are asked to re-arrange*/

/*			custFindLineTC[myTicketClerk]++; */

			localCustFindLineTC = GetMV("custFindLineTC",myTicketClerk);
			SetMV("custFindLineTC",myTicketClerk,localCustFindLineTC+1);

/*			if(ticketClerkLineCount[myTicketClerk]==custFindLineTC[myTicketClerk]) */

			localTicketClerkLineCount = GetMV("tcLineCnt",myTicketClerk);
			localCustFindLineTC = GetMV("custFindLineTC",myTicketClerk);

			if(localTicketClerkLineCount==localCustFindLineTC)
			{
/*				reFindLineTC[myTicketClerk]=0; */
				SetMV("reFindLineTC",myTicketClerk,0);

/*				ticketClerkLineCount[myTicketClerk]=0; */
				SetMV("tcLineCnt",myTicketClerk,0);

/*				custFindLineTC[myTicketClerk]=0; */
				SetMV("custFindLineTC",myTicketClerk,0);
			}

/*			Release(ticketClerkLineLockInt); */
			Release("tcLineLock");

			continue;
		}

		else
		{
/*			Release(ticketClerkLineLockInt);						/*continue with the same clerk*/
			Release("tcLineLock");

			break;
		}		
	}																/*while loop*/

/*	Acquire(ticketClerkLockInt[myTicketClerk]);						/*Time to interact with clerk*/
	Acquire(ticketClerkLockChar[myTicketClerk]);

/*	noOfTickets[myTicketClerk]=myGroupSize+1;						/*Telling the number of tickets I wish to purchase i.e Groupsize+HeadCust*/
	SetMV("noOfTickets",myTicketClerk,myGroupSize+1);

/*	Print("\nCustomer[%d] in Group[%d] is walking up to TicketClerk[%d] to buy %d tickets\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,noOfTickets[myTicketClerk] PRINTMETOO 1); */
/*	Print("\nCustomer[%d] in Group[%d] is walking up to TicketClerk[%d] to buy %d tickets\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,GetMV("noOfTickets",myTicketClerk) PRINTMETOO 1);*/
/*Print("GroupSize val: %d",myGroupSize+1,1,1);*/
	Print("\nCustomer[%d] in Group[%d] is walking up to TicketClerk[%d] to buy %d tickets\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,myGroupSize+1 PRINTMETOO 1);

/*	Signal(ticketClerkCVInt[myTicketClerk],ticketClerkLockInt[myTicketClerk]); */
	Signal(ticketClerkCVChar[myTicketClerk],ticketClerkLockChar[myTicketClerk]);

/*	Wait(ticketClerkCVInt[myTicketClerk],ticketClerkLockInt[myTicketClerk]);		/*Waiting for TC o tell me the amount*/
	Wait(ticketClerkCVChar[myTicketClerk],ticketClerkLockChar[myTicketClerk]);
	
/*	Print("\nCustomer[%d] in Group[%d] in TicketClerk line[%d] is paying %d for tickets\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,ticketClerkAmount[myTicketClerk] PRINTMETOO 1); */

	localTicketClerkAmount = GetMV("ticketClerkAmount",myTicketClerk);
	Print("\nCustomer[%d] in Group[%d] in TicketClerk line[%d] is paying %d for tickets\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,localTicketClerkAmount PRINTMETOO 1);

/*	Signal(ticketClerkCVInt[myTicketClerk],ticketClerkLockInt[myTicketClerk]); */
	Signal(ticketClerkCVChar[myTicketClerk],ticketClerkLockChar[myTicketClerk]);

/*	Wait(ticketClerkCVInt[myTicketClerk],ticketClerkLockInt[myTicketClerk]); */
	Wait(ticketClerkCVChar[myTicketClerk],ticketClerkLockChar[myTicketClerk]);

	Print("\nCustomer[%d] in Group[%d] is leaving TicketClerk[%d]\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,1);
	
/*	Release(ticketClerkLockInt[myTicketClerk]);						/*Going out from TC*/
	Release(ticketClerkLockChar[myTicketClerk]);

		
	/******************************End of Tc Interaction**********************************/


	
/* ///////////////////// customer  interaction for food///////////// */


/*	Acquire(groupLockInt[myGroupNumber]); */
	Acquire(groupLockChar[myGroupNumber]);

/*	haveTickets[myGroupNumber]=1; */
	SetMV("haveTickets",myGroupNumber,1);

	if(myGroupSize != 0)
	{
/*		Broadcast(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Broadcast(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);

/*		Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);			/* waiting for group to give choices of popcorn & soda*/
		Wait(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);

		/*Code for individual customer food choice*/
	}

	popRandVal=Rand(100);							/*Random value for popcorn and soda*/
	popRandVal=popRandVal+1;
	sodaRandVal=Rand(100);
	sodaRandVal=sodaRandVal+1;

	printPop=0;
	printSoda=0;

	if(popRandVal<=75)								/* Ensuring 75% probability */
	{
/*		groupPopcorn[myGroupNumber]++; */
		
		localGroupPopcorn = GetMV("groupPopcorn",myGroupNumber);
		SetMV("groupPopcorn",myGroupNumber,localGroupPopcorn+1);

		printPop=1;
	}

	if(sodaRandVal<=75)								/*Ensuring 75% probability*/
	{
/*		groupSoda[myGroupNumber]++; */

		localGroupSoda = GetMV("groupSoda",myGroupNumber);
		SetMV("groupSoda",myGroupNumber,localGroupSoda+1);

		printSoda=1;
	}
	
	/* Got the number of popcorns and soda for my group */

	Print("\nCustomer[%d] in group[%d] wants %d popcorn and %d soda.\n",myCustomerNumber,myGroupNumber PRINTMETOO printPop,printSoda PRINTMETOO 1);
	
/*	Release(groupLockInt[myGroupNumber]); */
	Release(groupLockChar[myGroupNumber]);


	/* /////////////    CC   Interaction      //////////////// */
	
	while(1)
	{ 
		myConcessionClerk=-1;

/*		Acquire(concessionClerkLineLockInt); */
		Acquire("ccLineLock");
		
/*		for (i=0;i<noOfCC;i++)					/* Checking for an available clerk */
		
		localNoOfCC = GetMV("noOfCC",0);

		for (i=0;i<localNoOfCC;i++)
		{
/*			if (concessionClerkState[i]==0) */
			
			localConcessionClerkState = GetMV("ccState",i);

			if (localConcessionClerkState==0)
			{
				myConcessionClerk=i;

/*				concessionClerkState[i]=1; */
				SetMV("ccState",i,1);

				Print("\nCustomer[%d] in Group[%d] is getting in ConcessionClerk Line[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,1);

				break;
			}

		}

		if (myConcessionClerk == -1)				/* If no clerk is available */
		{
/*			for(i=0;i<noOfCC;i++) */

			localNoOfCC = GetMV("noOfCC",0);

			for (i=0;i<localNoOfCC;i++)
			{
/*				if(concessionClerkState[i]!=-2) */

				localConcessionClerkState = GetMV("ccState",i);

				if(localConcessionClerkState!=-2)
				{
					shortestCCLine=i;										/* checking that the particular clerk is not on break */

/*					shortestCCLineLen=concessionClerkLineCount[i]; */
					
					shortestCCLineLen = GetMV("ccLineCnt",i);

					break;
				}

				else
				{
					/* checking all the clerks on break */
					Print("\nCustomer[%d] in Group [%d] sees ConcessionClerk[%d] is on break.\n",myCustomerNumber,myGroupNumber PRINTMETOO i,1);
				}
			}		
			
/*			for (j=1;j<noOfCC;j++) */

			localNoOfCC = GetMV("noOfCC",0);

			for (j=1;j<localNoOfCC;j++)
			{
				/* If the clerk is busy and he has the shortest line */

/*				if (concessionClerkState[j]==1 && (shortestCCLineLen > concessionClerkLineCount[j])) */

				localConcessionClerkState = GetMV("ccState",j);
				localConcessionClerkLineCount = GetMV("ccLineCnt",j);

				if (localConcessionClerkState==1 && (shortestCCLineLen > localConcessionClerkLineCount))
				{
					shortestCCLine=j;

/*					shortestCCLineLen=concessionClerkLineCount[j]; */
					shortestCCLineLen=GetMV("ccLineCnt",j);;
				}
			}
			
			myConcessionClerk=shortestCCLine;								/* Got my clerk */

/*			concessionClerkLineCount[myConcessionClerk]++; */

			localConcessionClerkLineCount = GetMV("ccLineCnt",myConcessionClerk);
			SetMV("ccLineCnt",myConcessionClerk,localConcessionClerkLineCount+1);

			Print("\nCustomer[%d] in Group[%d] is getting in ConcessionClerk Line[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,1);

/*			Wait(concessionClerkLineCVInt[myConcessionClerk],concessionClerkLineLockInt); */
			Wait(concessionClerkLineCVChar[myConcessionClerk],"ccLineLock");
		}
	
/*		if(reFindLineCC[myConcessionClerk]==1)						/* If manager has aked me to acquire the shortest line again */
		
		localReFindLineCC = GetMV("reFindLineCC",myConcessionClerk);

		if(localReFindLineCC==1)
		{
			/*customers in the line of  concessionclerk[%d] are starting the process of finding shortest line again as they are asked to re-arrange*/

/*			custFindLineCC[myConcessionClerk]++; */

			localCustFindLineCC = GetMV("custFindLineCC",myConcessionClerk);
			SetMV("custFindLineCC",myConcessionClerk,localCustFindLineCC+1);

/*			if(concessionClerkLineCount[myConcessionClerk]==custFindLineCC[myConcessionClerk]) */

			localConcessionClerkLineCount = GetMV("ccLineCnt",myConcessionClerk);
			localCustFindLineCC = GetMV("custFindLineCC",myConcessionClerk);

			if(localConcessionClerkLineCount==localCustFindLineCC)
			{
/*				reFindLineCC[myConcessionClerk]=0; */
				SetMV("reFindLineCC",myConcessionClerk,0);

/*				concessionClerkLineCount[myConcessionClerk]=0; */
				SetMV("ccLineCnt",myConcessionClerk,0);

/*				custFindLineCC[myConcessionClerk]=0; */
				SetMV("custFindLineCC",myConcessionClerk,0);
			}

/*			Release(concessionClerkLineLockInt); */
			Release("ccLineLock");

			continue;
		}

		else
		{	
/*			Release(concessionClerkLineLockInt); */
			Release("ccLineLock");
			
			break;
		}
		
	}	/*while loop*/




/*	Acquire(concessionClerkLockInt[myConcessionClerk]);					/*Time to interact with clerk*/
	Acquire(concessionClerkLockChar[myConcessionClerk]);

/*	Acquire(groupLockInt[myGroupNumber]); */
	Acquire(groupLockChar[myGroupNumber]);

/*	noOfSoda[myConcessionClerk]=groupSoda[myGroupNumber]; */

	localGroupSoda = GetMV("groupSoda",myGroupNumber);
	SetMV("noOfSoda",myConcessionClerk,localGroupSoda);

/*	noOfPopcorn[myConcessionClerk]=groupPopcorn[myGroupNumber]; */

	localGroupPopcorn = GetMV("groupPopcorn",myGroupNumber);
	SetMV("noOfPopcorn",myConcessionClerk,localGroupPopcorn);

/*	Release(groupLockInt[myGroupNumber]); */
	Release(groupLockChar[myGroupNumber]);

/*	Signal(concessionClerkCVInt[myConcessionClerk],concessionClerkLockInt[myConcessionClerk]); */
	Signal(concessionClerkCVChar[myConcessionClerk],concessionClerkLockChar[myConcessionClerk]);

/*	Print("\nCustomer[%d] in Group[%d] is walking up to ConcessionClerk[%d] to buy [%d] popcorn and [%d] soda.\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,noOfPopcorn[myConcessionClerk] PRINTMETOO noOfSoda[myConcessionClerk]); */

	localNoOfPopcorn = GetMV("noOfPopcorn",myConcessionClerk);
	localNoOfSoda = GetMV("noOfSoda",myConcessionClerk);

	Print("\nCustomer[%d] in Group[%d] is walking up to ConcessionClerk[%d] to buy [%d] popcorn and [%d] soda.\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,localNoOfPopcorn PRINTMETOO localNoOfSoda);
	
/*	Wait(concessionClerkCVInt[myConcessionClerk],concessionClerkLockInt[myConcessionClerk]);			/*Waiting for clerk to tell him the amount*/
	Wait(concessionClerkCVChar[myConcessionClerk],concessionClerkLockChar[myConcessionClerk]);

/*	foodAmount=amountSoda[myConcessionClerk]+amountPopcorn[myConcessionClerk]; */

	localAmountSoda = GetMV("amountSoda",myConcessionClerk);
	localAmountPopcorn = GetMV("amountPopcorn",myConcessionClerk);
	foodAmount = localAmountSoda + localAmountPopcorn;

	Print("\nCustomer[%d] in Group[%d] in ConcessionClerk line[%d] is paying[%d] for food.\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,foodAmount PRINTMETOO 1);

/*	Signal(concessionClerkCVInt[myConcessionClerk],concessionClerkLockInt[myConcessionClerk]); */
	Signal(concessionClerkCVChar[myConcessionClerk],concessionClerkLockChar[myConcessionClerk]);
	
	/*Giving the amount, now waiting his confirmation to leave*/

/*	Wait(concessionClerkCVInt[myConcessionClerk],concessionClerkLockInt[myConcessionClerk]); */
	Wait(concessionClerkCVChar[myConcessionClerk],concessionClerkLockChar[myConcessionClerk]);

	Print("\nCustomer[%d] in Group [%d] is leaving ConcessionClerk[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,1);

/*	Release(concessionClerkLockInt[myConcessionClerk]); */
	Release(concessionClerkLockChar[myConcessionClerk]);



	/* ///////////////////		Done With CC	////////////////// */	



/************************ Ticket Taker Interaction **************************/


	/*Ticket Taker and Head Customer Interaction*/

/*	Acquire(ticketTakerLineLockInt); */
	Acquire("ttLineLock");

	while(1)										/*It will run until break happens when it is allowed to go in the theater.*/
	{
		/* Monitor variable to check the state of TT. If he is taking tickets then go to TTLineCV else go to LobbyCV. */

/*		isTakingTickets=0; */
		SetMV("isTakingTickets",0,0);

/*		for (i=0;i<noOfTT;i++) */

		localNoOfTT = GetMV("noOfTT",0);

		for (i=0;i<localNoOfTT;i++)
		{
/*			if (ticketTakerState[i]!=-1) */

			localTicketTakerState = GetMV("ticketTakerState",i);

			if (localTicketTakerState!=-1)
			{
/*				isTakingTickets=1;					/*I got a TT who is taking tickets.*/
				SetMV("isTakingTickets",0,1);

				break;			
			}
		}


/*		if (isTakingTickets != 1) */

		localIsTakingTickets = GetMV("isTakingTickets",0);

		if (localIsTakingTickets!=1)
		{
/*			Release(ticketTakerLineLockInt);		/*I should add myself to the Lobby queue.*/
			Release("ttLineLock");

/*			Acquire(customerLobbyLockInt); */
			Acquire("customerLobbyLock");

			Print("\nCustomer[%d] in Group[%d] is in the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
			
/*			Wait(customerLobbyCVInt,customerLobbyLockInt); */
			Wait("customerLobbyCV","customerLobbyLock");

			Print("\nCustomer[%d] in Group[%d] is leaving the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
			
/*			Release(customerLobbyLockInt); */
			Release("customerLobbyLock");

/*			Acquire(ticketTakerLineLockInt); */
			Acquire("ttLineLock");

			continue;
		}

		/* Theatre is not full. Fighting for the shortest TT line. */

		myTicketTaker=-1;

/*		for (i=0;i<noOfTT;i++)			/*see if any ticket taker is not busy*/

		localNoOfTT = GetMV("noOfTT",0);

		for (i=0;i<localNoOfTT;i++)
		{
/*			if (ticketTakerState[i]==0) */

			localTicketTakerState = GetMV("ticketTakerState",i);

			if (localTicketTakerState==0)
			{
				myTicketTaker=i;			/*a TT is not busy, I dont have to wait*/

/*				ticketTakerState[i]=1; */
				SetMV("ticketTakerState",i,1);

				Print("\nCustomer[%d] in Group[%d] is getting in TicketTaker Line[%d] \n",myCustomerNumber,myGroupNumber PRINTMETOO myTicketTaker,1);

				break;
			}
		} 
		
		if (myTicketTaker==-1)							/*finding the TT with shortest Line*/
		{
/*			shortestTTLineLen = ticketTakerLineCount[0]; */
			shortestTTLineLen = GetMV("ttLineCnt",0);
			
/*			for(i=0;i<noOfTT;i++) */

			localNoOfTT = GetMV("noOfTT",0);
			
			for(i=0;i<localNoOfTT;i++)
			{
/*				if(ticketTakerState[i]!=-1) */

				localTicketTakerState = GetMV("ticketTakerState",i);

				if(localTicketTakerState!=-1)
				{
					shortestTTLine=i;

/*					shortestTTLineLen=ticketTakerLineCount[i];*/
					shortestTTLineLen = GetMV("ttLineCnt",i);

					break;
				}
			}

/*			for (i=1; i<noOfTT; i++) */

			localNoOfTT = GetMV("noOfTT",0);

			for (i=1; i<localNoOfTT; i++)
			{
				/*checking if the TT is busy and his line is shorter*/

/*				if (ticketTakerState[i]==1 && (shortestTTLineLen > ticketTakerLineCount[i])) */

				localTicketTakerState = GetMV("ticketTakerState",i);
				localTicketTakerLineCount = GetMV("ttLineCnt",i);

				if (localTicketTakerState==1 && (shortestTTLineLen > localTicketTakerLineCount))
				{
					shortestTTLine=i;

/*					shortestTTLineLen > ticketTakerLineCount[i]; */

/*					shortestTTLineLen = localTicketTakerLineCount; */

					shortestTTLineLen > localTicketTakerLineCount;
				}
			}
			
			myTicketTaker=shortestTTLine;					/* I have the shortest Line */

/*			total++; */

			localTotal = GetMV("total",0);
			SetMV("total",0,localTotal+1);

/*			ticketTakerLineCount[myTicketTaker]++;			/* Get in that Line */

			localTicketTakerLineCount = GetMV("ttLineCnt",myTicketTaker);
			SetMV("ttLineCnt",myTicketTaker,localTicketTakerLineCount+1);

			Print("\nCustomer[%d] in Group[%d] is getting in TicketTaker Line[%d] \n",myCustomerNumber,myGroupNumber PRINTMETOO myTicketTaker,1);
			
/*			Wait(ticketTakerLineCVInt[myTicketTaker],ticketTakerLineLockInt); */
			Wait(ticketTakerLineCVChar[myTicketTaker],"ttLineLock");

			/*Signalled by TT, now check, whether to go back to lobby?*/

/*			if (ticketTakerGroupIndicator[myTicketTaker]==0) */

			localTicketTakerGroupIndicator = GetMV("TTGroupInd",myTicketTaker);

			if (localTicketTakerGroupIndicator==0) 
			{
				/*If that TT has stopped taking tickets and asking to go in Lobby*/

				Print("\nCustomer[%d] in Group[%d] sees TicketTaker[%d] is no longer taking tickets. Going to the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO myTicketTaker,1);

/*				countCustTT++; */
				localCountCustTT = GetMV("countCustTT",0);
				SetMV("countCustTT",0,localCountCustTT+1);

/*				Release(ticketTakerLineLockInt); */
				Release("ttLineLock");

/*				Acquire(customerLobbyLockInt); */
				Acquire("customerLobbyLock");

				Print("\nCustomer[%d] in Group[%d] is in the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*				Wait(customerLobbyCVInt,customerLobbyLockInt); */
				Wait("customerLobbyCV","customerLobbyLockChar");

				Print("\nCustomer[%d] in Group[%d] is leaving the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
				
/*				Release(customerLobbyLockInt); */
				Release("customerLobbyLock");

/*				Acquire(ticketTakerLineLockInt);						/* When manager wakes me up from the lobby */
				Acquire("ttLineLock");

/*				countCustTT--; */

				localCountCustTT = GetMV("countCustTT",0);
				SetMV("countCustTT",0,localCountCustTT-1);

/*				total--; */

				localTotal = GetMV("total",0);
				SetMV("total",0,localTotal-1);

				continue;
			}

			else
			{
/*				Release(ticketTakerLineLockInt); */
				Release("ttLineLock");
			}
		}												/* end of if */

		else
		{
/*			total++; */

			localTotal = GetMV("total",0);
			SetMV("total",0,localTotal+1);

/*			Release(ticketTakerLineLockInt); */
			Release("ttLineLock");
		}

		/*Time to interact with the Ticket Taker*/

/*		Acquire(ticketTakerLockInt[myTicketTaker]); */
		Acquire(ticketTakerLockChar[myTicketTaker]);

/*		custNoOfTicket[myTicketTaker]=myGroupSize+1;				/* 3 should be changed to the actual dynamic statement */
		SetMV("custNoOfTicket",myTicketTaker,myGroupSize+1);

		/* Giving my tickets to TT */
		/* If theatre is full then ticketTakerTheatreCountStatus is 1. he wont entertain more customers. */

/*		Signal(ticketTakerCVInt[myTicketTaker],ticketTakerLockInt[myTicketTaker]); */
		Signal(ticketTakerCVChar[myTicketTaker],ticketTakerLockChar[myTicketTaker]);

/*		Acquire(ticketTakerLineLockInt); */
		Acquire("ttLineLock");	

/*		countCustTT++; */

		localCountCustTT = GetMV("countCustTT",0);
		SetMV("countCustTT",0,localCountCustTT+1);

/*		Release(ticketTakerLineLockInt); */
		Release("ttLineLock");	

/*		Wait(ticketTakerCVInt[myTicketTaker],ticketTakerLockInt[myTicketTaker]); */
		Wait(ticketTakerCVChar[myTicketTaker],ticketTakerLockChar[myTicketTaker]);

		/*I have been given an indicator value. Check that. It its 1, I can go inside else I have to wait in the lobby.*/

/*		if (ticketTakerGroupIndicator[myTicketTaker]==1) */

		localTicketTakerGroupIndicator = GetMV("TTGroupInd",myTicketTaker);

		if (localTicketTakerGroupIndicator==1)
		{
/*			Release(ticketTakerLockInt[myTicketTaker]);				/* Go inside the theater */
			Release(ticketTakerLockChar[myTicketTaker]);
			
			Print("\nCustomer[%d] in Group[%d] is leaving TicketTaker[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO myTicketTaker,1);

																	/* Adding myself to theatre CV by the theatre lock. */
			break; 													/*exit from the while loop. You already are inside the theater.*/
		}

/*		Release(ticketTakerLockInt[myTicketTaker]); */
		Release(ticketTakerLockChar[myTicketTaker]);

		Print("\nCustomer[%d] in Group[%d] is rejected by TicketTaker[%d]. Going to the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO myTicketTaker,1);
		
/*		Acquire(ticketTakerLineLockInt); */
		Acquire("ttLineLock");
		
/*		Release(ticketTakerLineLockInt); */
		Release("ttLineLock");

/*		Acquire(customerLobbyLockInt); */
		Acquire("customerLobbyLock");

		Print("\nCustomer[%d] in Group[%d] is in the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
		
/*		Wait(customerLobbyCVInt,customerLobbyLockInt); */
		Wait("customerLobbyCV","customerLobbyLock");
		
		Print("\nCustomer[%d] in Group[%d] is leaving the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	 
/*		Release(customerLobbyLockInt); */
		Release("customerLobbyLock");

/*		Acquire(ticketTakerLineLockInt); */
		Acquire("ttLineLock");

/*		countCustTT--; */

		localCountCustTT = GetMV("countCustTT",0);
		SetMV("countCustTT",0,localCountCustTT-1);

/*		total--;  */

		localTotal = GetMV("total",0);
		SetMV("total",0,localTotal-1);
	}															/*End of while statement*/
	 
	if(myGroupSize != 0)									/* Forming the Group to go inside theater room. */
	{
/*		Acquire(groupLockInt[myGroupNumber]); */
		Acquire(groupLockChar[myGroupNumber]);

/*		canGoInsideTheater[myGroupNumber]=1; */
		SetMV("canGoInsideTheater",myGroupNumber,1);
		
		Print("\nHeadCustomer[%d] of group[%d] has told the group to proceed.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
		
/*		Broadcast(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */ 
		Broadcast(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);

/*		Acquire(movieTheaterLockInt); */
		Acquire("movieTheaterLock");

/*		Release(groupLockInt[myGroupNumber]); */
		Release(groupLockChar[myGroupNumber]);
	}

	else
	{
/*		Acquire(movieTheaterLockInt); */
		Acquire("movieTheaterLock");
	}
 
	/* Customer group can go inside the theater room.*/

/*	custEnteredTheater++; */

	localCustEnteredTheater = GetMV("custEnteredTheater",0);
	SetMV("custEnteredTheater",0,localCustEnteredTheater+1);


					/*$$$$$$$$$$$$$$$$$$$ SEAT FUNCTIONALITY REMOVED*/
	
	/*AssignSeat(myGroupSize+1, myGroupNumber);				/*Calling function for assigning the seats to the group*/

	/*MySeat(myGroupNumber);									/*Calling function to view the assigned seat*/





/*	counterVal[myGroupNumber]++; */

	localCounterVal = GetMV("counterVal",myGroupNumber);
	SetMV("counterVal",myGroupNumber,localCounterVal+1);

/*	Print("\nCustomer[%d] in Group[%d] has found the following seat: row[%d] and seat[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO rowNo,columnNo PRINTMETOO 1); */

	localRowNo = GetMV("rowNo",0);
	localColumnNo = GetMV("columnNo",0);

	Print("\nCustomer[%d] in Group[%d] has found the following seat: row[%d] and seat[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO localRowNo,localColumnNo PRINTMETOO 1);
	
	Print("\nCustomer[%d] of group[%d] is sitting in a theater room seat.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*	Wait(movieTheaterCVInt,movieTheaterLockInt); */
	Wait("movieTheaterCV","movieTheaterLock");

	/*Movie Over*/

/*	Acquire(groupLockInt[myGroupNumber]); */
	Acquire(groupLockChar[myGroupNumber]);

/*	Release(movieTheaterLockInt); */
	Release("movieTheaterLock");

	if(myGroupSize != 0)
	{
		Print("\nHeadCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
		
/*		Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Wait(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);

		Print("\nHeadCustomer[%d] of group[%d] has told the group to proceed.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

		/*Asking group to proceed*/

/*		Broadcast(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Broadcast(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);
	}

/*	Acquire(movieTheaterLockInt); */
	Acquire("movieTheaterLock");

/*	Release(groupLockInt[myGroupNumber]); */
	Release(groupLockChar[myGroupNumber]);
		
/*	custLeavingTheater++;							/*Leaving Theater*/
	
	localCustLeavingTheater = GetMV("custLeavingTheater",0);
	SetMV("custLeavingTheater",0,localCustLeavingTheater+1);

/*	Acquire(groupLockInt[myGroupNumber]); */
	Acquire(groupLockChar[myGroupNumber]);

/*	Release(movieTheaterLockInt); */
	Release("movieTheaterLock");

	bathRoomValue = Rand(100);						/*Went out of theater after re-grouping, now broadcasting for bathroom*/
	bathRoomValue = bathRoomValue+1;

	if(bathRoomValue<=25)
	{
		Print("\nCustomer[%d] in Group[%d] is going to the bathroom.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*		Acquire(bathroomLockInt); */
		Acquire("bathroomLock");

		Yield();

/*		Release(bathroomLockInt); */
		Release("bathroomLock");

		Print("\nCustomer[%d] in Group[%d] is leaving the bathroom.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	}
	
/*	canGoBathroom[myGroupNumber]=1;										/*broadcast in groupCV for bathroom*/
	SetMV("canGoBathroom",myGroupNumber,1);

	if(myGroupSize != 0)
	{
/*		Broadcast(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Broadcast(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);

		/*Waiting in bathroom Lobby*/
		Print("\nHeadCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*		Wait(bathroomLobbyCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Wait(bathroomLobbyCVChar[myGroupNumber],groupLockChar[myGroupNumber]);
		
		/*All group members have returned from bathroom, so signal them to go.*/

		Print("\nHeadCustomer[%d] of group[%d] has told the group to proceed.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*		Broadcast(bathroomLobbyCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Broadcast(bathroomLobbyCVChar[myGroupNumber],groupLockChar[myGroupNumber]);
	}

/*	Release(groupLockInt[myGroupNumber]); */
	Release(groupLockChar[myGroupNumber]);

/*	Acquire(custFinalExitLockInt); */
	Acquire("custFinalExitLock");

/*	custFinalExitCount++; */

	localCustFinalExitCount = GetMV("custFinalExitCount",0);
	SetMV("custFinalExitCount",0,localCustFinalExitCount+1);

/*	Release(custFinalExitLockInt); */
	Release("custFinalExitLock");



}


void main()
{
	Initialize();
	CustomerHead();
		Exit(0);
}
