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



void ConcessionClerk()
{
	int myIndex;
	int myConcessionClerk;
	int customerTotal;

	int localFinalExitFlag;
	int localmanagerCcWait;
	int localConcessionClerkLineCount;
	int localNoOfSoda;
	int localNoOfPopcorn;
	int localAmountSoda;
	int localAmountPopcorn;
	int localTotalMoneySoda;
	int localTotalMoneyPopcorn;
	int localTotalAmountConcessionClerk;

/*	Acquire(concessionClerkIndexLockInt); */
	Acquire("ccIndexLock");

/*	myIndex=nextCCIndex; */
	myIndex=GetMV("nextCCIndex",0);

/*	nextCCIndex++; */
	SetMV("nextCCIndex",0,myIndex+1);

/*	Release(concessionClerkIndexLockInt); */
	Release("ccIndexLock");

	myConcessionClerk=-1;

	while(1)
	{ 
/*		Acquire(concessionClerkLineLockInt); */
		Acquire("ccLineLock");

/*		if(managerCcWait[myIndex]==1)  */

		localmanagerCcWait = GetMV("managerCcWait",myIndex);

		if(localmanagerCcWait==1)											/*If Manager has asked the Clerk to go on wait*/
		{
/*			concessionClerkState[myIndex]=-2;								/*Changing the state of CC as -2(Break State)*/
			SetMV("ccState",myIndex,-2);

/*			managerCcWait[myIndex]=0; */
			SetMV("managerCcWait",myIndex,0);

			Print("\n ConcessionClerk[%d] is going on break.\n",myIndex,1,1);

/*			reFindLineCC[myIndex]=1;										/*Broadcasting all customers in the group*/
			SetMV("reFindLineCC",myIndex,1);
			
/*			Broadcast(concessionClerkLineCVInt[myIndex],concessionClerkLineLockInt); */
			Broadcast(concessionClerkLineCVChar[myIndex],"ccLineLock");
		}

		else
		{

/*			if(concessionClerkLineCount[myIndex]>0) */

			localConcessionClerkLineCount = GetMV("ccLineCnt",myIndex);

			if(localConcessionClerkLineCount>0)					/*If the Clerk is not asked to go on wait by Manager*/
			{
				Print("\n ConcessionClerk[%d] has a line length=%d and is signaling a customer.\n",myIndex,localConcessionClerkLineCount PRINTMETOO 1,1);

/*				concessionClerkState[myIndex]=1;							/* Change state to 1 as busy */
				SetMV("ccState",myIndex,1);

/*				concessionClerkLineCount[myIndex]--; */

				localConcessionClerkLineCount = GetMV("ccLineCnt",myIndex);
				SetMV("ccLineCnt",myIndex,localConcessionClerkLineCount-1);

/*				Signal(concessionClerkLineCVInt[myIndex],concessionClerkLineLockInt); */
				Signal(concessionClerkLineCVChar[myIndex],"ccLineLock");
			}

			else
			{
/*				concessionClerkState[myIndex]=0;							/* If the CC is available */
				SetMV("ccState",myIndex,0);

				Print("\n ConcessionClerk[%d] has no one in line. I am available for a customer.\n",myIndex,1,1);
			}		
		}
		
		/*Acquiring of the CC Lock before eleasing Line Lock to ensure that customer cannot grab before him*/
		
/*		Acquire(concessionClerkLockInt[myIndex]); */
		Acquire(concessionClerkLockChar[myIndex]);

/*		Release(concessionClerkLineLockInt); */
		Release("ccLineLock");

/*		Wait(concessionClerkCVInt[myIndex],concessionClerkLockInt[myIndex]); */
		Wait(concessionClerkCVChar[myIndex],concessionClerkLockChar[myIndex]);

/*		Acquire(checkFinalExitLockInt);										/*check final exit condition after being signalled*/
		Acquire("checkFinalExitLock");

/*		if (finalExitFlag==1) */

		localFinalExitFlag = GetMV("finalExitFlag",0);

		if (localFinalExitFlag==1)
		{
/*			Release(checkFinalExitLockInt);									/*Manager woke me up and asking me to exit*/
			Release("checkFinalExitLock");

			break;
		}		

/*		Release(checkFinalExitLockInt); */
		Release("checkFinalExitLock");

/*		amountSoda[myIndex]=noOfSoda[myIndex]*4;							/*Calculating the amount of Soda and popcorn*/

		localNoOfSoda = GetMV("noOfSoda",myIndex);
		SetMV("amountSoda",myIndex,localNoOfSoda*4);

/*		amountPopcorn[myIndex]=noOfPopcorn[myIndex]*5; */

		localNoOfPopcorn = GetMV("noOfPopcorn",myIndex);
		SetMV("amountPopcorn",myIndex,localNoOfPopcorn*4);
		
/*		customerTotal=amountSoda[myIndex]+amountPopcorn[myIndex]; */

		localAmountSoda = GetMV("amountSoda",myIndex);
		localAmountPopcorn = GetMV("amountPopcorn",myIndex);

		customerTotal = localAmountSoda+localAmountPopcorn;
		
		Print("\n ConcessionClerk[%d] has an order for %d popcorn and %d soda. The cost is $%d.\n",myIndex,localNoOfPopcorn PRINTMETOO localNoOfSoda,customerTotal PRINTMETOO 1);

																			/*Told customer about the total money and waiting him to pay.*/

/*		Signal(concessionClerkCVInt[myIndex],concessionClerkLockInt[myIndex]); */
		Signal(concessionClerkCVChar[myIndex],concessionClerkLockChar[myIndex]);

/*		Wait(concessionClerkCVInt[myIndex],concessionClerkLockInt[myIndex]); */
		Wait(concessionClerkCVChar[myIndex],concessionClerkLockChar[myIndex]);

		Print("\n ConcessionClerk[%d] has been paid for the order.\n",myIndex,1,1);		
				
/*		Acquire(totalAmtPopSodaLockInt);									/*Updating total earning*/
		Acquire("toAmtPopLck");

/*		totalMoneySoda+=amountSoda[myIndex]; */

		localTotalMoneySoda = GetMV("totalMoneySoda",0);
		localAmountSoda = GetMV("amountSoda",myIndex);
		SetMV("totalMoneySoda",0,localAmountSoda+localTotalMoneySoda);

/*		totalMoneyPopcorn+=amountPopcorn[myIndex]; */

		localTotalMoneyPopcorn = GetMV("totalMoneyPopcorn",0);
		localAmountPopcorn = GetMV("amountPopcorn",myIndex);
		SetMV("totalMoneyPopcorn",0,localAmountPopcorn+localTotalMoneyPopcorn);
		
/*		Release(totalAmtPopSodaLockInt); */
		Release("toAmtPopLck");
		
/*		totalAmountConcessionClerk[myIndex]+=amountSoda[myIndex]+amountPopcorn[myIndex]; */

		localTotalAmountConcessionClerk = GetMV("totAmtCC",myIndex);
		localAmountSoda = GetMV("amountSoda",myIndex);
		localAmountPopcorn = GetMV("amountPopcorn",myIndex);

		SetMV("totAmtCC",myIndex,localTotalAmountConcessionClerk+localAmountSoda+localAmountPopcorn);

/*		Signal(concessionClerkCVInt[myIndex],concessionClerkLockInt[myIndex]); */
		Signal(concessionClerkCVChar[myIndex],concessionClerkLockChar[myIndex]);
		
/*		Release(concessionClerkLockInt[myIndex]);									/*Asking customer to leave*/
		Release(concessionClerkLockChar[myIndex]);
	}

}

void main()
{
	Initialize();
	ConcessionClerk();
	Exit(0);
}
