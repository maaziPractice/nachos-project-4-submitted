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




void Manager()
{
	int i,j;
	int randBreakValue;

	int localNoOfTC;
	int localTicketClerkLineCount;
	int localTicketClerkOnBreak;

	int localNoOfCC;
	int localConcessionClerkLineCount;
	int localConClerkOnBreak;
	
	int localNoOfTT;	
	int localTicketTakerState;
	int localCountCustTT;
	int localTotalHeadCust;
	int localTtTakingTickets;
	int localCustEnteredTheater;
	int localCustTicketsApproved;
	int localCustLeavingTheater;
	int localIsMovieOver;

	int localTotalMoneySoda;
	int localTotalMoneyPopcorn;
	int localTotalAmtTicket;
	int localTicketClerkState;
	int localConcessionClerkState;
	int localTotalAmountTicketClerk;
	int localTotalAmountConcessionClerk;
	int localCustFinalExitCount;
	int localTotalCustomerNumber;
	int localManagerWokeTT;
	int localttWaitingAfterFull;

	while(1)
	{	
		/* for(i=0;i<noOfTC;i++) */			/*To send TC on break.*/
		
		localNoOfTC = GetMV("noOfTC",0);

		for(i=0;i<localNoOfTC;i++)
		{
/*			Acquire(ticketClerkLineLockInt); */
			Acquire("tcLineLock");

/*			if(ticketClerkLineCount[i]<3 && (ticketClerkOnBreak < (noOfTC-1))) */

			localTicketClerkLineCount = GetMV("tcLineCnt",i);
			localNoOfTC = GetMV("noOfTC",0);
			localTicketClerkOnBreak = GetMV("tcOnBreak",0);

			if(localTicketClerkLineCount<3 && (localTicketClerkOnBreak<(localNoOfTC-1)))
			{
/*				if(ticketClerkLineCount[i]==0 && ticketClerkState[i]==0)					/*Sending TC on Break with 0 customers in Line.*/

				localTicketClerkLineCount = GetMV("tcLineCnt",i);
				localTicketClerkState = GetMV("ticketClerkState",i);

				if(localTicketClerkLineCount==0 && localTicketClerkState==0)
				{     
					randBreakValue= Rand(100);												/*Random value for sending a clerk on break*/
					randBreakValue=randBreakValue+1;

					if(randBreakValue<=20)  
					{  
						Print("\nManager has told TicketClerk[%d] to go on break.\n",i,1,1);
						
/*						ticketClerkState[i]=-2; */
						SetMV("ticketClerkState",i,-2);

/*						ticketClerkOnBreak++; */

						localTicketClerkOnBreak = GetMV("tcOnBreak",0);
						SetMV("tcOnBreak",0,localTicketClerkOnBreak+1);
					}
				}

				else														/*Sending TC on Break with less than 3 customers in Line.*/
				{
					randBreakValue= Rand(100);			
					randBreakValue=randBreakValue+1;

					if(randBreakValue<=20) 
					{ 
/*						managerTcWait[i]=1; */
                        SetMV("managerTcWait",i,1);

/*						ticketClerkOnBreak++; */

						localTicketClerkOnBreak = GetMV("tcOnBreak",0);
						SetMV("tcOnBreak",0,localTicketClerkOnBreak+1);

						Print("\nManager has told TicketClerk[%d] to go on break.\n",i,1,1);
					}
				}
			}

/*			Release(ticketClerkLineLockInt); */
			Release("tcLineLock");
		}

/*		for(i=0;i<noOfTC;i++)												/*For bringing TCs off break.*/

		localNoOfTC = GetMV("noOfTC",0);

		for(i=0;i<localNoOfTC;i++)
		{
/*			Acquire(ticketClerkLineLockInt); */
			Acquire("tcLineLock");

/*			if(ticketClerkLineCount[i]>5 && (ticketClerkOnBreak >=1)) */

			localTicketClerkLineCount = GetMV("tcLineCnt",i);
			localTicketClerkOnBreak = GetMV("tcOnBreak",0);

			if(localTicketClerkLineCount>5 && (localTicketClerkOnBreak>=1))
			{
/*			    for(j=0;j<noOfTC;j++) */

				localNoOfTC = GetMV("noOfTC",0);

				for(j=0;j<localNoOfTC;j++)
				{
/*					if (ticketClerkState[j]==-2)							/*Bringing back a clerk from break*/

					localTicketClerkState = GetMV("ticketClerkState",j);

					if (localTicketClerkState==-2)
					{   
/*						ticketClerkState[j]=0; */
						SetMV("ticketClerkState",j,0);

/*						ticketClerkLineCount[j]=0; */
						SetMV("tcLineCnt",j,0);

/*						ticketClerkOnBreak--; */

						localTicketClerkOnBreak = GetMV("tcOnBreak",0);
						SetMV("tcOnBreak",0,localTicketClerkOnBreak-1);

/*						reFindLineTC[j]=0; */
						SetMV("reFindLineTC",j,0);

						Print("\nTicketClerk[%d] is coming off break.",j,1,1);

						break;
					}
				}

/*				reFindLineTC[i]=1;											/*Flag to tell that a new clerk has come so re-acquire shortest line*/
				SetMV("reFindLineTC",i,1);

/*				Broadcast(ticketClerkLineCVInt[i],ticketClerkLineLockInt); */
				Broadcast(ticketClerkLineCVChar[i],"tcLineLock");
			}

/*			Release(ticketClerkLineLockInt); */
			Release("tcLineLock");
		}

/*		for(i=0;i<noOfCC;i++)												/*To send CC on break*/

		localNoOfTC = GetMV("noOfTC",0);

		for(i=0;i<localNoOfTC;i++)
		{
/*			Acquire(concessionClerkLineLockInt); */
			Acquire("ccLineLock");

/*			if(concessionClerkLineCount[i]<3 && (conClerkOnBreak < (noOfCC-1))) */

			localConcessionClerkLineCount = GetMV("ccLineCnt",i);
			localConClerkOnBreak = GetMV("conClerkOnBreak",0);
			localNoOfCC = GetMV("noOfCC",0);
			
			if(localConcessionClerkLineCount<3 && (localConClerkOnBreak<(localNoOfCC-1)))
			{
/*				if(concessionClerkLineCount[i]==0 && concessionClerkState[i]==0)		/* If the CC has less than 3 customers in his line and this is not the last CC serving. */

				localConcessionClerkLineCount = GetMV("ccLineCnt",i);
				localConcessionClerkState = GetMV("ccState",i);
				
				if(localConcessionClerkLineCount==0 && localConcessionClerkState==0)
				{     
					randBreakValue= Rand(100);
			  
					if(randBreakValue<20)									/*Sending CC on Break with 0 customers in Line.*/
					{  
						Print("\nManager has told ConcessionClerk[%d] to go on break \n",i,1,1);
						
/*						concessionClerkState[i]=-2; */
						SetMV("ccState",i,-2);

/*						conClerkOnBreak++; */

						localConClerkOnBreak = GetMV("conClerkOnBreak",0);
						SetMV("conClerkOnBreak",0,localConClerkOnBreak+1);
					}
				}

				else
				{
					randBreakValue= Rand(100);

					if(randBreakValue<20)									/* Sending CC on Break with less than 3 customers in Line. */
					{
/*						managerCcWait[i]=1; */
						SetMV("managerCcWait",i,1);

/*						conClerkOnBreak++; */

						localConClerkOnBreak = GetMV("conClerkOnBreak",0);
						SetMV("conClerkOnBreak",0,localConClerkOnBreak+1);

						Print("\nManager has told ConcessionClerk[%d] to go on break \n",i,1,1);
					}
				}
			}

/*			Release(concessionClerkLineLockInt); */
			Release("ccLineLock");
		}

/*		for(i=0;i<noOfCC;i++)											/* To call CCs off the break. */

		localNoOfCC = GetMV("noOfCC",0);

		for(i=0;i<localNoOfCC;i++)
		{
/*			Acquire(concessionClerkLineLockInt); */
			Acquire("ccLineLock");

/*			if(concessionClerkLineCount[i]>5 && (conClerkOnBreak >=1)) */

			localConcessionClerkLineCount = GetMV("ccLineCnt",i);
			localConClerkOnBreak = GetMV("conClerkOnBreak",0);

			if(localConcessionClerkLineCount>5 && (localConClerkOnBreak>=1))
			{
/*				for(j=0;j<noOfCC;j++) */

				localNoOfCC = GetMV("noOfCC",0);

				for(j=0;j<localNoOfCC;j++)
		        {
/*					if (concessionClerkState[j]==-2) */

					localConcessionClerkState = GetMV("ccState",j);

					if (localConcessionClerkState==-2)
		            {   
/*						concessionClerkState[j]=0;						/* Assigning Default values again. */
						SetMV("ccState",j,0);

/*						concessionClerkLineCount[j]=0; */
						SetMV("ccLineCnt",j,0);

/*						conClerkOnBreak--; */

						localConClerkOnBreak = GetMV("conClerkOnBreak",0);
						SetMV("conClerkOnBreak",0,localConClerkOnBreak-1);

/*						reFindLineCC[j]=0; */
						SetMV("reFindLineCC",j,0);

						Print("\nConcessionClerk [%d] is coming off break.",j,1,1);

						break;
			        }
				}

/*				reFindLineCC[i]=1;										/* Setting the flag for customers. */
				SetMV("reFindLineCC",i,1);

/*	            Broadcast(concessionClerkLineCVInt[i],concessionClerkLineLockInt); */
	            Broadcast(concessionClerkLineCVChar[i],"ccLineLock");
			}

/*			Release(concessionClerkLineLockInt); */
			Release("ccLineLock");
		}


/*****************************		TicketTaker Manager Interaction		**********************************/

/*		Acquire(ticketTakerLineLockInt); */
		Acquire("ttLineLock");

/*		for (i=0;i<noOfTT;i++) */

		localNoOfTT = GetMV("noOfTT",0);
		
		for (i=0;i<localNoOfTT;i++)
		{
			/* If the ticket taker state is 0 and all customers have giventheir tickets so tell him to change his state. */

/*			if(ticketTakerState[i]==0 && (countCustTT==totalHeadCust ))	/*|| total==totalHeadCust */ /*countCustTT*/

			localTicketTakerState = GetMV("ticketTakerState",i);
			localCountCustTT = GetMV("countCustTT",0);
			localTotalHeadCust = GetMV("totalHeadCust",0);

/*Print("\nlocalTicketTakerState %d   localCountCustTT=%d   localTotalHeadCust %d\n",localTicketTakerState,localCountCustTT PRINTMETOO localTotalHeadCust,1);*/
			if(localTicketTakerState==0 && (localCountCustTT==localTotalHeadCust))
			{				
/*				managerWokeTT[i]=1; */
				SetMV("managerWokeTT",i,1);

/*				Acquire(ticketTakerLockInt[i]); */
				Acquire(ticketTakerLockChar[i]);

				/* Manager Asking#### TicketTaker[%d] to change their state to -1 */

/*				ticketTakerState[i]==-1; */
				/*SetMV("ticketTakerState",i,-1);*/

/*CHANGED JUST FOR CHECKING*/


/*				Signal(ticketTakerCVInt[i],ticketTakerLockInt[i]); */
				Signal(ticketTakerCVChar[i],ticketTakerLockChar[i]);

/*				Release(ticketTakerLockInt[i]); */
				Release(ticketTakerLockChar[i]);
			}
		}		
		
/*		for (i=0;i<noOfTT;i++) */

		localNoOfTT = GetMV("noOfTT",0);

		for (i=0;i<localNoOfTT;i++)
		{
/*			if(ticketTakerState[i]==-1)				/* To check that whether any TT is taking tickets or not. */

			localTicketTakerState = GetMV("ticketTakerState",i);

			if(localTicketTakerState==-1)
			{
/*				ttTakingTickets=0; */
				SetMV("ttTakingTickets",0,0);
			}

			else
			{ 
/*				ttTakingTickets=1; */
				SetMV("ttTakingTickets",0,1);

				break;   
			}

		}

/*		Release(ticketTakerLineLockInt); */
		Release("ttLineLock");

/*		Acquire(movieTheaterLockInt); */
		Acquire("movieTheaterLock");

/*		Acquire(custTicketsApprovedLockInt); */
		Acquire("TktsAppLock");

/*		if (ttTakingTickets==0 && custEnteredTheater==custTicketsApproved && custTicketsApproved > 0) */

		localTtTakingTickets = GetMV("ttTakingTickets",0);
		localCustEnteredTheater = GetMV("custEnteredTheater",0);
		localCustTicketsApproved = GetMV("custTicketsApproved",0);

/*Print("\nttTakingTickets=%d  custEnteredTheater=%d  custTicketsApproved=%d\n",localTtTakingTickets,localCustEnteredTheater PRINTMETOO localCustTicketsApproved,1);*/

		if (localTtTakingTickets==0 && localCustEnteredTheater==localCustTicketsApproved && localCustTicketsApproved> 0) 
		{
			/* TT have stopped taking tickets and all customers have seated inside the theater. */

/*			custTicketsApproved=0; */
			SetMV("custTicketsApproved",0,0);

/*			Release(movieTheaterLockInt); */
			Release("movieTheaterLock");

/*			Release(custTicketsApprovedLockInt); */
			Release("TktsAppLock");

			Print("\nManager is telling the MovieTechnnician to start the movie.\n",1,1,1);				/* Asking Technician to Start the movie. */

/*			Acquire(movieTechLockInt); */
			Acquire("movieTechLock");

/*			Signal(movieTechCVInt,movieTechLockInt); */
			Signal("movieTechCV","movieTechLock");

/*			Release(movieTechLockInt); */
			Release("movieTechLock");
		}

		else
		{
/*			Release(movieTheaterLockInt); */
			Release("movieTheaterLock");

/*			Release(custTicketsApprovedLockInt); */
			Release("TktsAppLock");
		}

/*		Acquire(movieTechLockInt); */
		Acquire("movieTechLock");

/*		Acquire(movieTheaterLockInt); */
		Acquire("movieTheaterLock");
		
		/* To check that the movie is over and all customers have left the theater room . */

/*		if ((custEnteredTheater==custLeavingTheater) && isMovieOver==1 && custEnteredTheater>0) */

		localCustEnteredTheater = GetMV("custEnteredTheater",0);
		localCustLeavingTheater = GetMV("custLeavingTheater",0);
		localIsMovieOver = GetMV("isMovieOver",0);

		if ((localCustEnteredTheater==localCustLeavingTheater) && localIsMovieOver==1 && localCustEnteredTheater>0)
		{
/*			custEnteredTheater=0; */
			SetMV("custEnteredTheater",0,0);

/*			custLeavingTheater=0; */
			SetMV("custLeavingTheater",0,0);
			
/*			isMovieOver = 0; */
			SetMV("isMovieOver",0,0);

/*			for(i=0;i<5;i++)									/* Vacant the seats again */

			for(i=0;i<5;i++)
			{
/*				for(j=0;j<5;j++) */

				for(j=0;j<5;j++)
				{
/*					movieRoomSeatNoArray[i][j]=0; */
				/*	movieRoomSeatNoArray[i][j]=0;	*/		/*$$$$$$$$$$$$$$$$$$$$$ REMOVED SEATING FUNCTIONALITY*/

/*					movieRoomGrpNoArray[i][j]=0; */
				/*	movieRoomGrpNoArray[i][j]=0; */		/*$$$$$$$$$$$$$$$$$$$$$ REMOVED SEATING FUNCTIONALITY*/
				}
			}

/*			Release(movieTheaterLockInt); */
			Release("movieTheaterLock");

/*			Release(movieTechLockInt); */
			Release("movieTechLock");
			
/*			Acquire(ticketTakerLineLockInt); */
			Acquire("ttLineLock");			

/*			for(i=0;i<noOfTT;i++) */

			localNoOfTT = GetMV("noOfTT",0);

			for(i=0;i<localNoOfTT;i++)
			{
/*				ticketTakerLineCount[i]=0; */
				SetMV("ttLineCnt",i,0);

/*				ticketTakerState[i]=1; */
				SetMV("ticketTakerState",i,1);

/*				ticketTakerGroupIndicator[i]=1; */
				SetMV("TTGroupInd",i,1); 
			}

/*			Release(ticketTakerLineLockInt); */
			Release("ttLineLock");
			
/*			Acquire(customerLobbyLockInt);						/* Broadcasting customers in Lobby as TT have started tacking tickets. */
			Acquire("customerLobbyLock");

/*			Broadcast(customerLobbyCVInt,customerLobbyLockInt); */
			Broadcast("customerLobbyCV","customerLobbyLock");

/*			Release(customerLobbyLockInt); */
			Release("customerLobbyLock");

/*			for (i=0;i<noOfTT;i++)								/*Bring back TTs to action. */

			localNoOfTT = GetMV("noOfTT",0);

			for (i=0;i<localNoOfTT;i++)
			{
/*				Acquire(ttWaitShowOverLockInt[i]); */
				Acquire(ttWaitShowOverLockChar[i]);

/*				Signal(ttWaitShowOverCVInt[i],ttWaitShowOverLockInt[i]); */
				Signal(ttWaitShowOverCVChar[i],ttWaitShowOverLockChar[i]);

/*				Release(ttWaitShowOverLockInt[i]); */
				Release(ttWaitShowOverLockChar[i]);
			}
		}

		else
		{
/*			Release(movieTheaterLockInt); */
			Release("movieTheaterLock");

/*			Release(movieTechLockInt); */
			Release("movieTechLock");
		}

/*		Acquire(totalAmtPopSodaLockInt);				/* Calculation of total money made by theater. */
		Acquire("toAmtPopLck");

/*		Acquire(totalAmtTicketLockInt); */
		Acquire("toAmtTktLck");

/*		Print("\n Total money made by office = $%d. \n",totalMoneySoda+totalMoneyPopcorn+totalAmtTicket,1,1); */

		localTotalMoneySoda = GetMV("totalMoneySoda",0);
		localTotalMoneyPopcorn = GetMV("totalMoneyPopcorn",0);
		localTotalAmtTicket = GetMV("totalAmtTicket",0);

		Print("\n Total money made by office = $%d. \n",localTotalMoneySoda+localTotalMoneyPopcorn+localTotalAmtTicket,1,1);
		
/*		Release(totalAmtTicketLockInt); */
		Release("toAmtTktLck");

/*		Release(totalAmtPopSodaLockInt); */
		Release("toAmtPopLck");

/*		for(i=0;i<noOfTC;i++)							/* Calculation of amount from each Ticket Clerk. */

		localNoOfTC = GetMV("noOfTC",0);

		for(i=0;i<localNoOfTC;i++)
		{
/*			Acquire(ticketClerkLockInt[i]); */
			Acquire(ticketClerkLockChar[i]);

/*			Print("\nManager collected $%d from TicketClerk[%d].\n",totalAmountTicketClerk[i],i PRINTMETOO 1,1); */

			localTotalAmountTicketClerk = GetMV("totAmtTC",i);

			Print("\nManager collected $%d from TicketClerk[%d].\n",localTotalAmountTicketClerk,i PRINTMETOO 1,1);

/*			Release(ticketClerkLockInt[i]); */
			Release(ticketClerkLockChar[i]);
		}

		for (i=0;i<2;i++)								/* Calculation of amount from each concession Clerk. */
		{
			Yield();
		}

/*		for(i=0;i<noOfCC;i++) */

		localNoOfCC = GetMV("noOfCC",0);

		for(i=0;i<localNoOfCC;i++)
		{
/*			Acquire(concessionClerkLockInt[i]); */
			Acquire(concessionClerkLockChar[i]);

/*			Print("\nManager collected $%d from ConcessionClerk[%d].\n",totalAmountConcessionClerk[i],i PRINTMETOO 1,1); */

			localTotalAmountConcessionClerk = GetMV("totAmtCC",i);

			Print("\nManager collected $%d from ConcessionClerk[%d].\n",localTotalAmountConcessionClerk,i PRINTMETOO 1,1);

/*			Release(concessionClerkLockInt[i]); */
			Release(concessionClerkLockChar[i]);
		}
											/* End of Money Calculation. */

/*		Acquire(custFinalExitLockInt);		/* Final Exit Condition. */
		Acquire("custFinalExitLock");

/*		if (custFinalExitCount==totalCustomerNumber) */

		localCustFinalExitCount = GetMV("custFinalExitCount",0);
		localTotalCustomerNumber = GetMV("totCustNum",0);

		/*Print("\nlocalCustFinalExitCount: %d   localTotalCustomerNumber=%d\n",localCustFinalExitCount,localTotalCustomerNumber PRINTMETOO 1,1); */

		if (localCustFinalExitCount==localTotalCustomerNumber)
		{
/*			Release(custFinalExitLockInt); */
			Release("custFinalExitLock");

			/* If all customers exited the theater then manager shuld also exit. */
			/* printf("\n\nBye Bye..Simulation Completed!!\n"); */
			
/*			Acquire(checkFinalExitLockInt); */
			Acquire("checkFinalExitLock");

/*			finalExitFlag=1; */
			SetMV("finalExitFlag",0,1);

/*			Release(checkFinalExitLockInt); */
			Release("checkFinalExitLock");
		
/*			for(i=0;i<noOfTC;i++)								/*For bringing TC to exit condition*/

			localNoOfTC = GetMV("noOfTC",0);

			for(i=0;i<localNoOfTC;i++)
			{
/*				Acquire(ticketClerkLockInt[i]); */
				Acquire(ticketClerkLockChar[i]);		

/*				Signal(ticketClerkCVInt[i],ticketClerkLockInt[i]); */
				Signal(ticketClerkCVChar[i],ticketClerkLockChar[i]);

/*				Release(ticketClerkLockInt[i]); */
				Release(ticketClerkLockChar[i]);
			}

/*			for(i=0;i<noOfCC;i++)								/*For bringing CC to exit condition*/

			localNoOfCC = GetMV("noOfCC",0);

			for(i=0;i<localNoOfCC;i++)
			{
/*				Acquire(concessionClerkLockInt[i]); */
				Acquire(concessionClerkLockChar[i]);		

/*				Signal(concessionClerkCVInt[i],concessionClerkLockInt[i]); */
				Signal(concessionClerkCVChar[i],concessionClerkLockChar[i]);

/*				Release(concessionClerkLockInt[i]); */
				Release(concessionClerkLockChar[i]);
			}
			
/*			for(i=0;i<noOfTT;i++)							/*For bringing TT to exit condition*/

			localNoOfTT = GetMV("noOfTT",0);

			for(i=0;i<localNoOfTT;i++)
			{
/*				Acquire(ticketTakerLockInt[i]); */
				Acquire(ticketTakerLockChar[i]);

/*				if (managerWokeTT[i]==1 || ttWaitingAfterFull[i]==1) */

				localManagerWokeTT = GetMV("managerWokeTT",i);
				localttWaitingAfterFull = GetMV("ttWaitingAfterFull",i);

				if (localManagerWokeTT==1 || localttWaitingAfterFull==1)
				{
/*					Release(ticketTakerLockInt[i]); */
					Release(ticketTakerLockChar[i]);

/*					Acquire(ttWaitShowOverLockInt[i]); */
					Acquire(ttWaitShowOverLockChar[i]);

/*					Signal(ttWaitShowOverCVInt[i],ttWaitShowOverLockInt[i]); */
					Signal(ttWaitShowOverCVChar[i],ttWaitShowOverLockChar[i]);

/*					Release(ttWaitShowOverLockInt[i]); */
					Release(ttWaitShowOverLockChar[i]);
				}

				else
				{
/*					Release(ticketTakerLockInt[i]); */
					Release(ticketTakerLockChar[i]);

/*					Acquire(ticketTakerLockInt[i]); */
					Acquire(ticketTakerLockChar[i]);		

/*					Signal(ticketTakerCVInt[i],ticketTakerLockInt[i]); */
					Signal(ticketTakerCVChar[i],ticketTakerLockChar[i]);

/*					Release(ticketTakerLockInt[i]); */
					Release(ticketTakerLockChar[i]);
				}
			}

/*			Acquire(movieTechLockInt);							/*For bringing MovieTechnician to exit condition*/
			Acquire("movieTechLock");

/*			Signal(movieTechCVInt,movieTechLockInt); */
			Signal("movieTechCV","movieTechLock");

/*			Release(movieTechLockInt); */
			Release("movieTechLock");

			break;
		}

/*		Release(custFinalExitLockInt); */
		Release("custFinalExitLock");

		for (i=0;i<200;i++)
		{
			Yield();
		}

	}
			
}

void main()
{

	Initialize();
	Manager();
	Exit(0);
}
