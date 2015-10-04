/*
a) If 4 user programs create the same lock, and on exit everybody does a delete lock, but that lock is deleted only when after the last userprog deletes it.

b) If 4 user programs create the same cv, and on exit everybody does a delete cv, but that cv is not deleted until the last userprog deletes it.

c)
*/


#define MAX_TT 2			/* Maximum  Ticket Takers */
#define MAX_CC 3			/* Maximum Concession Clerks */
#define MAX_TC 3			/* Maximum Ticket Clerks */
#define MAX_GRP 2
#define PRINTMETOO *65536+

#include "syscall.h"

void main()
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

	char ticketClerkLineCVChar[MAX_TC][20];
	char ticketClerkCVChar[MAX_TC][20];
	char ticketClerkLockChar[MAX_TC][20];
	char concessionClerkLineCVChar[MAX_CC][20];
	char concessionClerkCVChar[MAX_TC][20];
	char concessionClerkLockChar[MAX_CC][20];
	char ticketTakerLockChar[MAX_TT][20];
	char ticketTakerLineCVChar[MAX_TT][20];
	char ticketTakerCVChar[MAX_TT][20];
	char ttWaitShowOverLockChar[MAX_TT][20];
	char ttWaitShowOverCVChar[MAX_TT][20];
	char groupLockChar[MAX_GRP][20];
	char groupCVChar[MAX_GRP][20];
	char bathroomLobbyCVChar[MAX_GRP][20];


	CreateLock("InitLock");

	Acquire("InitLock");	/*******************************************************************************************************/

/*	int totalCustomerNumber;						/* Total Number of Customers */
	CreateMV("totalCustomerNumber",1);

/*	int noOfGroups;								/* Stores the number of groups generated */
	CreateMV("noOfGroups",1);
	SetMV("noOfGroups",0,30);						/* %%%%%%%%%%%%%% For the time being. %%%%%%%%%%%%%%%% */

/*	int noOfTC;*/
	CreateMV("noOfTC",1);
	SetMV("noOfTC",0,5);

/*	int noOfCC;*/
	CreateMV("noOfCC",1);
	SetMV("noOfCC",0,5);

/*	int noOfTT;*/
	CreateMV("noOfTT",1);
	SetMV("noOfTT",0,3);

/*	int noOfCustomers;*/
	CreateMV("noOfCustomers",1);

/*	int groupSize;*/
	CreateMV("groupSize",1);

/*	int totalAmtTicket;*/							/* Total Amount Variable */
	CreateMV("totalAmtTicket",1);

/*	int noOfTickets[MAX_TC];						/* Keep track of no. of tickets sold by each clerk */
	CreateMV("noOfTickets",MAX_TC);

/*	int ticketClerkAmount[MAX_TC];				/* Amount given by customer at each TicketClerk */
	CreateMV("ticketClerkAmount",MAX_TC);

/*	int totalAmountTicketClerk[MAX_TC];			/* Amount deposited at each TicketClerk */
	CreateMV("totalAmountTicketClerk",MAX_TC);

/*	int ticketClerkOnBreak=0;						/* Count of the Ticket Clerks on break*/
	CreateMV("ticketClerkOnBreak",1);

/*	int managerTcWait[MAX_TC];					/* Manager signal for each Ticket Clerk*/
	CreateMV("managerTcWait",MAX_TC);

/*	int custFindLineTC[MAX_TC];					/* Variable to say that broadcast customers*/
	CreateMV("custFindLineTC",MAX_TC);

/*	int reFindLineTC[MAX_TC];						/*Flag to say that the customer has to find line again*/
	CreateMV("reFindLineTC",MAX_TC);

/*	int totalAmountConcessionClerk[MAX_CC];		/*Total Amount stored by all Concession Clerks*/
	CreateMV("totalAmountConcessionClerk",MAX_CC);

/*	int concessionClerkState[MAX_CC];				/*Stores the Concession Clerks State*/

	concessionClerkStateRV = CreateMV("concessionClerkState",MAX_CC);
	if(concessionClerkStateRV==1)
	{
		for(i=0;i<MAX_CC;i++)
		{
			SetMV("concessionClerkState",i,1);
		}
	}


/*	int concessionClerkLineCount[MAX_CC];			/*Stores the Concession Clerks Line Count*/
	CreateMV("concessionClerkLineCount",MAX_CC);



	/* $$$$$$$$ Ticket Clerk Variables $$$$$$$$ */

/*	int ticketClerkState[MAX_TC];					/* Stores the state of each Ticket Clerk */
	
	ticketClerkStateRV = CreateMV("ticketClerkState",MAX_TC);
	if(ticketClerkStateRV==1)
	{
		for(i=0;i<MAX_TC;i++)
		{
			SetMV("ticketClerkState",i,1);
		}
	}


/*	int ticketClerkLineCount[MAX_TC];				/* Stores the Line Count of each Ticket Clerk */
	CreateMV("ticketClerkLineCount",MAX_TC);

/*	int ticketClerkLineCVInt[MAX_TC]; */

/*	char ticketClerkLineCVChar[MAX_TC][200]; */
	for(i=0;i<MAX_TC;i++)
	{
		Sprint(ticketClerkLineCVChar[i],"ticketClerkLineCV",i);	
		CreateCV(ticketClerkLineCVChar[i]);
	}


/*	int ticketClerkLineLockInt; */
	CreateLock("ticketClerkLineLock");

/*	int totalAmtTicketLockInt; */
	CreateLock("totalAmtTicketLock");

/*	int ticketClerkCVInt[MAX_TC]; */

/*	char ticketClerkCVChar[MAX_TC][200]; */
	for(i=0;i<MAX_TC;i++)
	{
		Sprint(ticketClerkCVChar[i],"ticketClerkCV",i);	
		CreateCV(ticketClerkCVChar[i]);
	}

/*	int ticketClerkLockInt[MAX_TC]; */

/*	char ticketClerkLockChar[MAX_TC][200]; */
	for(i=0;i<MAX_TC;i++)
	{
		Sprint(ticketClerkLockChar[i],"ticketClerkLock",i);	
		CreateLock(ticketClerkLockChar[i]);
	}


/*	int concessionClerkLineCVInt[MAX_CC]; */

/*	char concessionClerkLineCVChar[MAX_CC][200]; */
	for(i=0;i<MAX_CC;i++)
	{
		Sprint(concessionClerkLineCVChar[i],"concessionClerkLineCV",i);	
		CreateCV(concessionClerkLineCVChar[i]);
	}

/*	int concessionClerkLineLockInt; */
	CreateLock("concessionClerkLineLock");

/*	int totalAmtPopSodaLockInt; */
	CreateLock("totalAmtPopSodaLock");

/*	int noOfSoda[MAX_CC];							/*customer Vaiable to store soda value on a Concession Clerk*/
	CreateMV("noOfSoda",MAX_CC);

/*	int noOfPopcorn[MAX_CC];						/*customer Vaiable to store popcorn value on a Concession Clerk*/
	CreateMV("noOfPopcorn",MAX_CC);

/*	int totalMoneySoda;								/*total money by Soda*/
	CreateMV("totalMoneySoda",1);

/*	int totalMoneyPopcorn;							/*total money by popcorn*/
	CreateMV("totalMoneyPopcorn",1);

/*	int amountSoda[MAX_CC];							/*Amount customer has to pay for Soda*/
	CreateMV("amountSoda",MAX_CC);

/*	int amountPopcorn[MAX_CC];						/*Amount customer has to pay for Popcorn*/
	CreateMV("amountPopcorn",MAX_CC);

/*	int concessionClerkCVInt[MAX_CC]; */

/*	char concessionClerkCVChar[MAX_TC][200]; */
	for(i=0;i<MAX_TC;i++)
	{
		Sprint(concessionClerkCVChar[i],"concessionClerkCV",i);	
		CreateCV(concessionClerkCVChar[i]);
	}

/*	int concessionClerkLockInt[MAX_CC]; */

/*	char concessionClerkLockChar[MAX_CC][200]; */
	for(i=0;i<MAX_CC;i++)
	{
		Sprint(concessionClerkLockChar[i],"concessionClerkLock",i);	
		CreateLock(concessionClerkLockChar[i]);
	}

/*	int conClerkOnBreak=0;							/*Count of CCs on break*/
	CreateMV("conClerkOnBreak",1);

/*	int managerCcWait[MAX_CC];						/*Flag for wait of CC*/
	CreateMV("managerCcWait",MAX_CC);

/*	int custFindLineCC[MAX_CC];						/*Variable of CC to tell customer to find line*/
	CreateMV("custFindLineCC",MAX_CC);

/*	int reFindLineCC[MAX_CC];						/*Flag for customer to find line again*/
	CreateMV("reFindLineCC",MAX_CC);



	/*********Variables for Technician Manager and Customer Interaction*********/

/*	int movieTheaterLockInt; */
	CreateLock("movieTheaterLock");

/*	int movieTheaterCVInt; */
	CreateCV("movieTheaterCV");

/*	int custEnteredTheater;							/*Count of Cust entering the theater room*/
	CreateMV("custEnteredTheater",1);

/*	int custLeavingTheater;							/*Count of Cust leaving the theater room*/
	CreateMV("custLeavingTheater",1);

/*	int ttTakingTickets;							/*Stores if TT are taking tickets*/

	ttTakingTicketsRV = CreateMV("ttTakingTickets",1);
	if(ttTakingTicketsRV==1)
	{
		SetMV("ttTakingTickets",0,1);
	}

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

/*	int ticketTakerState[MAX_TT];					/*State of each TT(Ticket Taker)*/

	ticketTakerStateRV = CreateMV("ticketTakerState",MAX_TT);
	if(ticketTakerStateRV==1)
	{
		for(i=0;i<MAX_TT;i++)
		{
			SetMV("ticketTakerState",i,1);
		}
	}

/*	int ticketTakerLineCount[MAX_TT];				/*Stores the Line count of each TT*/
	CreateMV("ticketTakerLineCount",MAX_TT);

/*	int ticketTakerGroupIndicator[MAX_TT];			/*Indicates a group whether to go inside or wait in lobby*/

	ticketTakerGroupIndicatorRV = CreateMV("ticketTakerGroupIndicator",MAX_TT);
	if(ticketTakerGroupIndicatorRV==1)
	{
		for(i=0;i<MAX_TT;i++)
		{
			SetMV("ticketTakerGroupIndicator",i,1);
		}
	}

/*	int custNoOfTicket[MAX_TT];						/*Number of tickets of each group*/
	CreateMV("custNoOfTicket",MAX_TT);

/*	int ticketTakerTheatreCountStatus=1;			/*count for the ticket taker*/

	ticketTakerTheatreCountStatusRV = CreateMV("ticketTakerTheatreCountStatus",1);
	if(ticketTakerTheatreCountStatusRV==1)
	{
		SetMV("ticketTakerTheatreCountStatus",0,1);
	}

/*	int ticketTakerLineLockInt;						/* Lock for the TT Line*/
	CreateLock("ticketTakerLineLock");

/*	int ticketTakerLockInt[MAX_TT];					/* Lock for each TT*/

/*	char ticketTakerLockChar[MAX_TT][200]; */
	for(i=0;i<MAX_TT;i++)
	{
		Sprint(ticketTakerLockChar[i],"ticketTakerLock",i);	
		CreateLock(ticketTakerLockChar[i]);
	}

/*	int ticketTakerManagerLockInt;					/* TicketTaker Manager Lock*/
	CreateLock("ticketTakerManagerLock");

/*	int custTicketsApprovedLockInt;					/* Lock for total tickets approved to go inside*/
	CreateLock("custTicketsApprovedLock");

/*	int ticketTakerLineCVInt[MAX_TT];				/* CV for each TT Line*/

/*	char ticketTakerLineCVChar[MAX_TT][200]; */
	for(i=0;i<MAX_TT;i++)
	{
		Sprint(ticketTakerLineCVChar[i],"ticketTakerLineCV",i);	
		CreateCV(ticketTakerLineCVChar[i]);
	}

/*	int ticketTakerCVInt[MAX_TT];					/* CV for each TT interaction*/

/*	char ticketTakerCVChar[MAX_TT][200]; */
	for(i=0;i<MAX_TT;i++)
	{
		Sprint(ticketTakerCVChar[i],"ticketTakerCVChar",i);	
		CreateCV(ticketTakerCVChar[i]);
	}

/*	int ticketTakerManagerCVInt;					/* CV for Technician */
	CreateCV("ticketTakerManagerCV");

/*	int customerLobbyCVInt;							/*CV for Lobby*/
	CreateCV("customerLobbyCV");

/*	int customerLobbyLockInt;						/*Lock for Lobby*/
	CreateLock("customerLobbyLock");

/*	int isTakingTickets;							/*Stores whether the TT is taking tickets or not*/
	CreateMV("isTakingTickets",1);

/*	int ttWaitShowOverLockInt[MAX_TT];				/*Lock for TT till the next show starts*/

/*	char ttWaitShowOverLockChar[MAX_TT][200]; */
	for(i=0;i<MAX_TT;i++)
	{
		Sprint(ttWaitShowOverLockChar[i],"ttWaitShowOverLock",i);	
		CreateLock(ttWaitShowOverLockChar[i]);
	}

/*	int ttWaitShowOverCVInt[MAX_TT];				/*CV for waiting of TT till next show start*/

/*	char ttWaitShowOverCVChar[MAX_TT][200]; */
	for(i=0;i<MAX_TT;i++)
	{
		Sprint(ttWaitShowOverCVChar[i],"ttWaitShowOverCV",i);	
		CreateCV(ttWaitShowOverCVChar[i]);
	}




	/***************************Variables for Group Interaction*********************************/

/*	int groupLockInt[MAX_GRP];						/*Group Lock for each group*/

/*	char groupLockChar[MAX_GRP][200]; */
	for(i=0;i<MAX_GRP;i++)
	{
		Sprint(groupLockChar[i],"groupLock",i);	
		CreateLock(groupLockChar[i]);
	}

/*	int groupCVInt[MAX_GRP];						/* CV for each group*/

/*	char groupCVChar[MAX_GRP][200]; */
	for(i=0;i<MAX_GRP;i++)
	{
		Sprint(groupCVChar[i],"groupCV",i);	
		CreateCV(groupCVChar[i]);
	}

/*	int canGoInsideTheater[MAX_GRP];				/*Stores whether Cust can go inside*/
	CreateMV("canGoInsideTheater",MAX_GRP);

/*	int canGoBathroom[MAX_GRP];						/*Stores whtehr cust can go to bathroom*/
	CreateMV("canGoBathroom",MAX_GRP);

/*	int counterAfterMuvi[MAX_GRP];					/* stores the count of cust got up after movie*/
	CreateMV("counterAfterMuvi",MAX_GRP);

/*	int counterAfterBathroom[MAX_GRP];				/* stores the count of cust going to bathroom*/
	CreateMV("counterAfterBathroom",MAX_GRP);

/*	int bathroomLobbyCVInt[MAX_GRP];				/* CV for use when other cust has to wait when 1 goes to bathroom*/

/*	char bathroomLobbyCVChar[MAX_GRP][200]; */
	for(i=0;i<MAX_GRP;i++)
	{
		Sprint(bathroomLobbyCVChar[i],"bathroomLobbyCV",i);	
		CreateCV(bathroomLobbyCVChar[i]);
	}

/*	int bathroomLockInt;							/* Lock for bathroom*/
	CreateLock("bathroomLock");

/*	int ticketTakerWaitingAfterTheaterFull[MAX_TT]; */
	CreateMV("ticketTakerWaitingAfterTheaterFull",MAX_TT);

/*	int managerWokeTT[MAX_TT];					/*manager waking up TT to start taking ticket*/
	CreateMV("managerWokeTT",MAX_TT);

/*	int countCustTT;							/*count of cust going to TT*/
	CreateMV("countCustTT",1);
	
/*	int total; */
	CreateMV("total",1);

/*	int totalHeadCust;							/*Count of all head customer*/
	CreateMV("totalHeadCust",1);

/*	int groupPopcorn[MAX_GRP];					/*popcorn by each group*/
	CreateMV("groupPopcorn",MAX_GRP);

/*	int groupSoda[MAX_GRP];						/* Soda ordered by each group*/
	CreateMV("groupSoda",MAX_GRP);

/*	int haveTickets[MAX_GRP];					/*Stores whtehr the head have tickets or not*/
	CreateMV("haveTickets",MAX_GRP);

/*	int givenFoodChoice[MAX_GRP];				/*sores whther give the food choice*/
	CreateMV("givenFoodChoice",MAX_GRP);

	/*Seat variabes*/
/*	int rowNo,columnNo;							/*row number and column number of seat*/
	CreateMV("rowNo",1);
	CreateMV("columnNo",1);

/*	int counterVal[MAX_GRP];					/*counter for each customer accessing seat*/
	CreateMV("counterVal",MAX_GRP);


/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/*	int movieRoomSeatNoArray[5][5];				/*array for storing seat avaible or not

	int movieRoomGrpNoArray[5][5];				/*array for storing seat assigned to which group
*/

/* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */

/*	int sizeForGroupArr[50];					/*Storing the group size for each group*/
	CreateMV("sizeForGroupArr",50);

/*	int availableCustSizeForGroupArr[50];		/*Array for each customer to determine its group*/
	CreateMV("availableCustSizeForGroupArr",50);


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
	CreateLock("concessionClerkIndexLock");

/*	int nextCCIndex=0; */
	CreateMV("nextCCIndex",1);

/*	int determineCustGroupNumberLockInt; */
	CreateLock("determineCustGroupNumberLock");



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

/*	totalHeadCust=numberOfGroups;*/

	SetMV("totalHeadCust",0,localNumberOfGroups);

	for(i=0;i<localNumberOfGroups;i++)
	{
/*		groupSize=Rand(5);*/
		localGroupSize = Rand(5);
		SetMV("groupSize",0,localGroupSize);

/*		sizeForGroupArr[i]=groupSize;								/*Assigning group size*/ 
		localGroupSize = GetMV("groupSize",0);
		SetMV("sizeForGroupArr",i,localGroupSize);

/*		availableCustSizeForGroupArr[i]=groupSize; */
		SetMV("availableCustSizeForGroupArr",i,localGroupSize);

/*		totalCustomerNumber++;*/
		localTotalCustomerNumber=GetMV("totalCustomerNumber",0);
		SetMV("totalCustomerNumber",0,localTotalCustomerNumber+1);

		for (j=0;j<localGroupSize;j++ )
		{
/*			totalCustomerNumber++; */
			localTotalCustomerNumber=GetMV("totalCustomerNumber",0);
			SetMV("totalCustomerNumber",0,localTotalCustomerNumber+1);;

/*			Fork(Customer); */
		}
	}





	Release("InitLock");











/*	CreateCV("cv1");
	CreateLock("InitLock");

	Acquire("InitLock");
	
	Broadcast("cv1","InitLock");
	
	Release("InitLock");
	

	int lck1,cv1,lck2,mv1,lck3;
	char myFinalString1[200];
	char myFinalString2[200];
	char myCV1[200],myMV[200];
int i;
char ticketClerkLineCVChar[5][200];

	for(i=0;i<5;i++)
	{
		Sprint(ticketClerkLineCVChar[i],"ticketClerkLineCV",i);	
		CreateCV(ticketClerkLineCVChar[i]);
	}

	CreateCV(ticketClerkLineCVChar[3]);

	Sprint((int)myFinalString1,(int)"MySexyLock",23450);
		Sprint(myFinalString2,"MySexyLock",22222);
	
	lck1=CreateLock(myFinalString1);
	lck3=CreateLock("MySexyLock23450");
	
		
		lck2=CreateLock(myFinalString2);
	Sprint(myCV1,"MyTestCV",1);
		cv1=CreateCV(myCV1);

	Sprint(myMV,"MyTestMV",1);
			mv1 = CreateMV(myMV, 1);


	Print("\nLock1 id is: %d \n",lck1,1,1);	
		Print("\nLock2 id is: %d \n",lck2,1,1);	
		Print("\nCV id is: %d \n",cv1,1,1);	
				Print("\nMV id is: %d \n",mv1,1,1);	*/
}
