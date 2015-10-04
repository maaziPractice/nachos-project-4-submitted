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






void Customer()
{ 

	int i;
	int printPop=0;										/* It will be 1 when cust takes popcorn*/
	int printSoda=0;									/* It will be 1 when cust takes soda*/
	int	popRandVal;
	int	sodaRandVal;
	int bathRoomValue;
	int myGroupNumber,myCustomerNumber,myGroupSize;


	int localCustFinalExitCount;
	int localCounterAfterBathroom;
	int localCanGoBathroom;
	int localCustLeavingTheater;
	int localCounterAfterMuvi;
	int localCounterVal;
	int localRowNo;
	int localColumnNo;
	int localCustEnteredTheater;
	int localCanGoInsideTheater;
	int localGivenFoodChoice;
	int localHaveTickets;
	int localGroupPopcorn;
	int localGroupSoda;
	int localNextCustomerNumber;
	int localAvailableCustSizeForGroupArr;
	int localSizeForGroupArr;


/*	Acquire(determineCustGroupNumberLockInt); */
	Acquire("custGrpNumLock");

/*	for(i=0;i<GlobalnoOfGroups;i++)								/* Determine the group number for customer */

	for(i=0;i<GlobalnoOfGroups;i++)
	{
/*		if(availableCustSizeForGroupArr[i]==0) */

		localAvailableCustSizeForGroupArr = GetMV("avCustGrpArr",i);
		/*Print("\nAvailable Size for Grp %d is %d\n",i,localAvailableCustSizeForGroupArr PRINTMETOO 1,1);*/

		if(localAvailableCustSizeForGroupArr==0)
		{
			continue;
		}

/*		availableCustSizeForGroupArr[i]--; */

		localAvailableCustSizeForGroupArr = localAvailableCustSizeForGroupArr-1;
		SetMV("avCustGrpArr",i,localAvailableCustSizeForGroupArr);

		myGroupNumber=i;
		/*Print("\nMy grp number is %d \n",i,1,1);*/

		break;
	}

/*	Release(determineCustGroupNumberLockInt); */
	Release("custGrpNumLock");

/*	Acquire(customerNumberLockInt); */
	Acquire("customerNumberLock");

/*	myCustomerNumber=nextCustomerNumber; */

	localNextCustomerNumber = GetMV("nextCustomerNumber",0);
	myCustomerNumber = localNextCustomerNumber;

/*	nextCustomerNumber++; */

	localNextCustomerNumber = GetMV("nextCustomerNumber",0);
	SetMV("nextCustomerNumber",0,localNextCustomerNumber+1);

/*	Release(customerNumberLockInt); */
	Release("customerNumberLock");

/*	myGroupSize=sizeForGroupArr[myGroupNumber]; */

	localSizeForGroupArr = GetMV("sizeForGroupArr",myGroupNumber);
	myGroupSize = localSizeForGroupArr;

	Print("\nCustomer [%d] in Group [%d] has entered the movie theater.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	
/*	Acquire(groupLockInt[myGroupNumber]); */
	Acquire(groupLockChar[myGroupNumber]);

	/*If the headcustomer hasnt purchased the tickets yet then go on wait else proceed straight away*/

/*	if(!haveTickets[myGroupNumber]) */

	localHaveTickets = GetMV("haveTickets",myGroupNumber);

	if(!localHaveTickets)
	{

		Print("\nCustomer[%d] of group[%d] is waiting for the HeadCustomer.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*		Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Wait(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);
	}

	popRandVal=Rand(100);						/*set the value of popcorn and soda now*/
	popRandVal=popRandVal+1;
	sodaRandVal=Rand(100);
	sodaRandVal=sodaRandVal+1;

	if(popRandVal<=75)							/*Determining 75% probability for customer*/
	{
/*		groupPopcorn[myGroupNumber]++; */

		localGroupPopcorn = GetMV("groupPopcorn",myGroupNumber);
		SetMV("groupPopcorn",myGroupNumber,localGroupPopcorn+1);

		printPop=1;
	}

	if(sodaRandVal<=75)							/*Determining 75% probability for customer*/
	{
/*		groupSoda[myGroupNumber]++; */

		localGroupSoda = GetMV("groupSoda",myGroupNumber);
		SetMV("groupSoda",myGroupNumber,localGroupSoda+1);

		printSoda=1;
	}

/*	givenFoodChoice[myGroupNumber]++; */

	localGivenFoodChoice = GetMV("givenFoodChoice",myGroupNumber);
	SetMV("givenFoodChoice",myGroupNumber,localGivenFoodChoice+1);

	Print("\nCustomer[%d] in group[%d] wants %d popcorn and %d soda.\n",myCustomerNumber,myGroupNumber PRINTMETOO printPop,printSoda PRINTMETOO 1);

	Print("\nCustomer[%d] in Group[%d] has %d popcorn and %d soda request from a group member\n",myCustomerNumber,myGroupNumber PRINTMETOO printPop,printSoda PRINTMETOO 1);
	
/*	if(givenFoodChoice[myGroupNumber]==myGroupSize)			/*If all customer have given their foodchoice, then notify head*/

	localGivenFoodChoice = GetMV("givenFoodChoice",myGroupNumber);
/*Print("\n$$$$cust %d - localGivenFoodChoice=%d  myGroupSize=%d\n",myCustomerNumber,localGivenFoodChoice PRINTMETOO myGroupSize, 1);*/
	if(localGivenFoodChoice==myGroupSize)
	{ 
		/*Print("\n$$$$cust %d - Signalling my headcust of group %d\n",myCustomerNumber,myGroupNumber PRINTMETOO 1, 1);*/
/*		Signal(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Signal(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);
	}

/*	Release(groupLockInt[myGroupNumber]); */
	Release(groupLockChar[myGroupNumber]);


/*	Acquire(groupLockInt[myGroupNumber]);					/*After Taking Food, Going to Theater Room*/
	Acquire(groupLockChar[myGroupNumber]);

/*	if(!canGoInsideTheater[myGroupNumber]) */

	localCanGoInsideTheater = GetMV("canGoInsideTheater",myGroupNumber);

	if(!localCanGoInsideTheater)
	{
		Print("\nCustomer[%d] of group[%d] is waiting for the HeadCustomer.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*		Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Wait(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);
	}

/*	Release(groupLockInt[myGroupNumber]); */
	Release(groupLockChar[myGroupNumber]);  
	
/*	Acquire(movieTheaterLockInt);							/*My group Head asked me to go inside the theater.*/
	Acquire("movieTheaterLock");

/*	custEnteredTheater++; */

	localCustEnteredTheater = GetMV("custEnteredTheater",0);
	SetMV("custEnteredTheater",0,localCustEnteredTheater+1);
	

	
	/*MySeat(myGroupNumber);*/		/*$$$$$$$$$$$$$$$$$$$ SEAT FUNCTIONALITY REMOVED*/




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

	Print("\nCustomer[%d] of group[%d] is getting out of a theater room seat.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*	Release(movieTheaterLockInt); */
	Release("movieTheaterLock");

/*	Acquire(groupLockInt[myGroupNumber]);					/*Re-grouping inside the theater*/
	Acquire(groupLockChar[myGroupNumber]);

/*	counterAfterMuvi[myGroupNumber]++; */

	localCounterAfterMuvi = GetMV("counterAfterMuvi",myGroupNumber);
	SetMV("counterAfterMuvi",myGroupNumber,localCounterAfterMuvi+1);


/*	if (counterAfterMuvi[myGroupNumber]==myGroupSize) */

	localCounterAfterMuvi = GetMV("counterAfterMuvi",myGroupNumber);

	if (localCounterAfterMuvi==myGroupSize)
	{		
/*		Signal(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Signal(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);
	}
	
	/*Waiting for confirmation from Headcustomer to proceed. */

	Print("\nCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*	Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
	Wait(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);	

	Print("\nCustomer[%d] of group[%d] has been told by the HeadCustomer to proceed.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	
/*	Release(groupLockInt[myGroupNumber]); */
	Release(groupLockChar[myGroupNumber]);

/*	Acquire(movieTheaterLockInt); */
	Acquire("movieTheaterLock");

/*	custLeavingTheater++; */

	localCustLeavingTheater = GetMV("custLeavingTheater",0);
	SetMV("custLeavingTheater",0,localCustLeavingTheater+1);

/*	Release(movieTheaterLockInt); */
	Release("movieTheaterLock");	

/*	Acquire(groupLockInt[myGroupNumber]);					/*Went out of theater after re-grouping*/
	Acquire(groupLockChar[myGroupNumber]);

/*	if(!canGoBathroom[myGroupNumber]) */

	localCanGoBathroom = GetMV("canGoBathroom",myGroupNumber);

	if(!localCanGoBathroom)
	{
/*		Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Wait(groupCVChar[myGroupNumber],groupLockChar[myGroupNumber]);
	}

	bathRoomValue=Rand(100);								/*Determining the random value to go to bathroom*/
	bathRoomValue=bathRoomValue+1;

	if(bathRoomValue<=25)
	{
		Print("\nCustomer[%d] in Group[%d] is going to the bathroom.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*		Acquire(bathroomLockInt); */
		Acquire("bathroomLock");

		Yield();											/*Inside the bathroom*/

/*		Release(bathroomLockInt); */
		Release("bathroomLock");

		Print("\nCustomer[%d] in Group[%d] is leaving the bathroom.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	}

/*	counterAfterBathroom[myGroupNumber]++; */

	localCounterAfterBathroom = GetMV("ctrAfterBath",myGroupNumber);
	SetMV("ctrAfterBath",myGroupNumber,localCounterAfterBathroom+1);

/*	if(counterAfterBathroom[myGroupNumber]==myGroupSize)				/*Telling grup head that all members have come back from bathroom*/

	localCounterAfterBathroom = GetMV("ctrAfterBath",myGroupNumber);

	if(localCounterAfterBathroom==myGroupSize)
	{
/*		Signal(bathroomLobbyCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
		Signal(bathroomLobbyCVChar[myGroupNumber],groupLockChar[myGroupNumber]);
	}

	/*Waiting for grouphead to signal to proceed*/

	Print("\nCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*	Wait(bathroomLobbyCVInt[myGroupNumber],groupLockInt[myGroupNumber]); */
	Wait(bathroomLobbyCVChar[myGroupNumber],groupLockChar[myGroupNumber]);

	Print("\nCustomer[%d] of group[%d] has been told by the HeadCustomer to proceed.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

/*	Release(groupLockInt[myGroupNumber]); */
	Release(groupLockChar[myGroupNumber]);	

/*	Acquire(custFinalExitLockInt);										/*I am exiting, update the custFinalExitCount*/
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
	Customer();
	Exit(0);
}
