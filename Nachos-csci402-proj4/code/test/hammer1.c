#include "syscall.h"


#define MAX_TT 3			/* Maximum  Ticket Takers */
#define MAX_CC 5			/* Maximum Concession Clerks */
#define MAX_TC 5			/* Maximum Ticket Clerks */
#define MAX_GRP 30
#define PRINTMETOO *65536+

int totalCustomerNumber;		/* Total Number of Customers */

/* $$$$$$$ Global Menu Variables $$$$$$$ */

int noOfGroups;							/* Stores the number of groups generated */
int noOfTC;
int noOfCC;
int noOfTT;
int noOfCustomers;
/*int groupSizeArr[200];*/
int groupSize;

int totalAmtTicket;							/* Total Amount Variable */
int noOfTickets[MAX_TC];					/* keep track of no. of tickets sold by each clerk */
int ticketClerkAmount[MAX_TC];				/* Amount given by customer at each TicketClerk */

int totalAmountTicketClerk[MAX_TC];			/* Amount deposited at each TicketClerk */

int ticketClerkOnBreak=0;				/*Count of the Ticket Clerks on break*/
int managerTcWait[MAX_TC];				/*Manager signal for each Ticket Clerk*/
int custFindLineTC[MAX_TC];				/*variable to say that broadcast customers*/
int reFindLineTC[MAX_TC];				/*Flag to say that the customer has to find line again*/

int totalAmountConcessionClerk[MAX_CC];		/*Total Amount stored by all Concession Clerks*/
int concessionClerkState[MAX_CC];			/*Stores the Concession Clerks State*/
int concessionClerkLineCount[MAX_CC];		/*Stores the Concession Clerks Line Count*/

/* $$$$$$$$ Ticket Clerk Global Variables $$$$$$$$ */

int ticketClerkState[MAX_TC];			/* Stores the state of each Ticket Clerk */
int ticketClerkLineCount[MAX_TC];		/* Stores the Line Count of each Ticket Clerk */

int ticketClerkLineCVInt[MAX_TC];
/*Condition **ticketClerkLineCV;			Condition Variable for each TicketClerk Line */

int ticketClerkLineLockInt;
/*Lock* ticketClerkLineLock;				Lock for TicketClerk Line */

int totalAmtTicketLockInt;
/*Lock* totalAmtTicketLock;					Lock for fetching the total amount of TicketClerk */

int ticketClerkCVInt[MAX_TC];
/*Condition **ticketClerkCV;				Condition Variable for each TicketClerk */

int ticketClerkLockInt[MAX_TC];
/*Lock **ticketClerkLock;					Lock for each TicketClerk*/

int concessionClerkLineCVInt[MAX_CC];
/*Condition **concessionClerkLineCV;		//Condition Variable for each Concession Clerk Line*/

int concessionClerkLineLockInt;
/*Lock* concessionClerkLineLock;			//Lock for Line of Concession Clerks*/

int totalAmtPopSodaLockInt;
/*Lock* totalAmtPopSodaLock;				//Lock to access total amount*/

int noOfSoda[MAX_CC];					/*customer Vaiable to store soda value on a Concession Clerk*/
int noOfPopcorn[MAX_CC];				/*customer Vaiable to store popcorn value on a Concession Clerk*/
int totalMoneySoda;						/*total money by Soda*/
int totalMoneyPopcorn;					/*total money by popcorn*/
int amountSoda[MAX_CC];					/*Amount customer has to pay for Soda*/
int amountPopcorn[MAX_CC];				/*Amount customer has to pay for Popcorn*/

int concessionClerkCVInt[MAX_CC];
/*Condition **concessionClerkCV;			//Condition Variable for each CC*/

int concessionClerkLockInt[MAX_CC];
/*Lock **concessionClerkLock;				//Lock for each CC*/

int conClerkOnBreak=0;					/*Count of CCs on break*/
int managerCcWait[MAX_CC];				/*Flag for wait of CC*/
int custFindLineCC[MAX_CC];				/*Variable of CC to tell customer to find line*/
int reFindLineCC[MAX_CC];				/*Flag for customer to find line again*/

/*********Variables for Technician Manager and Customer Interaction*********/

int movieTheaterLockInt;
/*Lock* movieTheaterLock;					//Lock for Movie Theater*/

int movieTheaterCVInt;
/*Condition* movieTheaterCV;				//Condition Variable for Movie Theater*/


int custEnteredTheater;					/*Count of Cust entering the theater room*/
int custLeavingTheater;					/*Count of Cust leaving the theater room*/

int ttTakingTickets;
/* bool ttTakingTickets;					/*Stores if TT are taking tickets*/

int isMovieOver;
/* bool isMovieOver;						/*Stores the movie state*/

int movieTechLockInt;
/*Lock* movieTechLock;					//Lock for Movie Technician*/

int movieTechCVInt;
/*Condition* movieTechCV;					//Conditon Variable for Technician*/

int custFinalExitLockInt;
/*Lock* custFinalExitLock;				//Lock for count of finally exiting customers*/

int custFinalExitCount;					/*Variable for count of finally exiting customers*/

/*/////////////////////////////Ticket Taker//////////////////////////////////*/

int custTicketsApproved=0;				/*Stores the no of tickets approved to go inside theater room*/
int ticketTakerState[MAX_TT];			/*State of each TT(Ticket Taker)*/
int ticketTakerLineCount[MAX_TT];		/*Stores the Line count of each TT*/
int ticketTakerGroupIndicator[MAX_TT];	/*Indicates a group whether to go inside or wait in lobby*/
int custNoOfTicket[MAX_TT];				/*Number of tickets of each group*/
int ticketTakerTheatreCountStatus=1;	/*count for the ticket taker*/

int ticketTakerLineLockInt;
/*Lock* ticketTakerLineLock;				//Lock for the TT Line*/

int ticketTakerLockInt[MAX_TT];
/*Lock **ticketTakerLock;					//Lock for each TT*/

int ticketTakerManagerLockInt;
/*Lock* ticketTakerManagerLock;			//TicketTaker Manager Lock*/

int custTicketsApprovedLockInt;
/*Lock* custTicketsApprovedLock;			//Lock for total tickets approved to go inside*/

int ticketTakerLineCVInt[MAX_TT];
/*Condition **ticketTakerLineCV;			//CV for each TT Line*/

int ticketTakerCVInt[MAX_TT];
/*Condition **ticketTakerCV;				//CV for each TT interaction*/

int ticketTakerManagerCVInt;
/*Condition* ticketTakerManagerCV;		//CV for Technician */

int customerLobbyCVInt;
/*Condition* customerLobbyCV;				//CV for Lobby*/

int customerLobbyLockInt;
/*Lock* customerLobbyLock;				//Lock for Lobby*/

int isTakingTickets;
/*bool isTakingTickets;					/*Stores whether the TT is taking tickets or not*/

int ttWaitShowOverLockInt[MAX_TT];
/*Lock **ttWaitShowOverLock;				//Lock for TT till the next show starts*/

int ttWaitShowOverCVInt[MAX_TT];
/*Condition **ttWaitShowOverCV;			//CV for waiting of TT till next show start*/


/***************************Variables for Group Interaction*********************************/

int groupLockInt[MAX_GRP];
/*Lock **groupLock;						//Group Lock for each group*/

int groupCVInt[MAX_GRP];
/*Condition **groupCV;					//CV for each group*/

int canGoInsideTheater[MAX_GRP];
/*bool canGoInsideTheaterBool[MAX_GRP]; */
/*bool *canGoInsideTheater;				//Stores whether Cust can go inside*/

int canGoBathroom[MAX_GRP];
/*bool canGoBathroomBool[MAX_GRP]; */
/*bool *canGoBathroom;					//Stores whtehr cust can go to bathroom*/

int counterAfterMuvi[MAX_GRP];
/*int *counterAfterMuvi;					//stores the count of cust got up after movie*/

int counterAfterBathroom[MAX_GRP];
/*int *counterAfterBathroom;				//stores the count of cust going to bathroom*/

int bathroomLobbyCVInt[MAX_GRP];
/*Condition **bathroomLobbyCV;			//CV for use when other cust has to wait when 1 goes to bathroom*/

int bathroomLockInt;
/*Lock *bathroomLock;						//Lock for bathroom*/

int ticketTakerWaitingAfterTheaterFull[MAX_TT];
int managerWokeTT[MAX_TT];
/*bool managerWokeTT[MAX_TT];				/*manager waking up TT to start taking ticket*/

int countCustTT;						/*count of cust going to TT*/
int total;
int totalHeadCust;						/*Count of all head customer*/

int groupPopcorn[MAX_GRP];
/*int *groupPopcorn;						//popcorn by each group*/

int groupSoda[MAX_GRP];
/*int *groupSoda;							//Soda ordered by each group*/

int haveTickets[MAX_GRP];
/* bool haveTickets[MAX_GRP]; */
/*bool *haveTickets;						//Stores whtehr the head have tickets or not*/

int givenFoodChoice[MAX_GRP];
/*int *givenFoodChoice;					//sores whther give the food choice*/

/*Seat variabes*/
int rowNo,columnNo;						/*row number and column number of seat*/

int counterVal[MAX_GRP];
/*int *counterVal;						//counter for each customer accessing seat*/

int movieRoomSeatNoArray[5][5];
/*int **movieRoomSeatNoArray;				//array for storing seat avaible or not*/

int movieRoomGrpNoArray[5][5];
/*int **movieRoomGrpNoArray;				//array for storing seat assigned to which group*/

int sizeForGroupArr[50];				/*Storing the group size for each group*/
int availableCustSizeForGroupArr[50];	/*Array for each customer to determine its group*/
/*
struct CustomerData 
{
	int customerNumber;					//Unique,customer number
    int groupNumber;					//Unique Group number
	int groupSize;						//Size of each group
};*/


/*Global Part for TC myIndex value*/
int ticketClerkIndexLockInt;
int nextTCIndex=0;

/*Global Part for Customer value*/
int groupNumberLockInt, customerNumberLockInt, groupSizeLockInt;
int nextGroupNumber=0, nextCustomerNumber=0, nextGroupSize=0;


/*Global Part for CC myIndex value*/
int concessionClerkIndexLockInt;
int nextCCIndex=0;

int determineCustGroupNumberLockInt;

/*Global Part for TT myIndex value*/
int ticketTakerIndexLockInt;
int nextTTIndex=0;

int checkFinalExitLockInt;
int finalExitFlag=0;

/*
//---------------------------------------------------------------------------------------------------------------------------
// AssignSeat(int,int) function
//
// This simulates the seating of theater room. It can be called once at any given point of time.
// 2 argument is passed 
// noOfppl: Count of total cust to which seat is to be assigned
// groupNo: Group No that is asking to assign seats
// No value is returned 
//---------------------------------------------------------------------------------------------------------------------------
*/

void AssignSeat(int noOfppl, int groupNo)
{
	int seatsNotAvailable=-1, row, start_column,i,j,k, count=0, counter=0, seat_found=0;

	for (i=0;i<5;i++)
	{
		for (j=0;j<5;j++)
		{
			if (j+noOfppl<=5)
			{
				for(k=0;k<noOfppl-1;k++)
				{
					if (movieRoomSeatNoArray[i][j+k]==0)
					{
						seatsNotAvailable=0;						
					}
					else {seatsNotAvailable=1; break;}
				}
				if (seatsNotAvailable==0)
				{
					row=i;
					start_column=j;
					break;
				}
			}
			else break;
		}
		if (seatsNotAvailable==0)
		break;
	}

	if(seatsNotAvailable==0)		/* Means if seat is available in adjacent row*/
	{
		for(i=start_column;i<start_column+noOfppl;i++)
		{
			movieRoomSeatNoArray[row][i]=1;
			movieRoomGrpNoArray[row][i]=groupNo;
		}
	}
	else
	{		
		seat_found=0;
		for(i=0;i<5;i++)
		{
			count=0;
			if(i+1<5)
			{
				for(j=0;j<5;j++)
				{
					count=count+movieRoomSeatNoArray[i][j]+movieRoomSeatNoArray[i+1][j];					
				}
				if((10-count)>=noOfppl)
				{
					row=i;
					seat_found=1;
					
					break;
				}

			}
		}

		if(seat_found==1)
		{
		counter=0;
		for(i=row;i<row+2;i++)
		{
			for(j=0;j<5;j++)
			{
				if(movieRoomSeatNoArray[i][j]==0)
				{
					movieRoomSeatNoArray[i][j]=1;
					movieRoomGrpNoArray[i][j]=groupNo;
					counter++;
					if(counter==noOfppl)
					{
						seatsNotAvailable=0;
						break;
					}
				}				
			}
			if(counter==noOfppl)
				break;
		}
		}
		else
		{
			counter=0;
			for (i=0;i<5;i++)
			{
				for(j=0;j<5;j++)
				{
					if(movieRoomSeatNoArray[i][j]==0)
					{
					movieRoomSeatNoArray[i][j]=1;
					movieRoomGrpNoArray[i][j]=groupNo;
					counter++;
					if(counter==noOfppl)
					{
						seatsNotAvailable=0;
						break;
					}
					}


				}
				if(seatsNotAvailable==0)
					break;
			}
		}

		
	}

}

/*
//---------------------------------------------------------------------------------------------------------------------------
// MySeat(int) function
//
// This simulates the functionality where each customer of the group sees which seat is assigned to him.
// 1 argument is passed 
// grpNo : It is the group Number of cust who is viewing seat
//
// No value is returned 
//---------------------------------------------------------------------------------------------------------------------------
*/

void MySeat(int grpNo)
{
	int localCounter=0,i,j;

	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			if (movieRoomGrpNoArray[i][j]==grpNo)
			{
				localCounter++;
			}
			if (localCounter==counterVal[grpNo])
			{
				rowNo=i;
				columnNo=j;				
				return;
			}
		}
	}
}


/***************************** TicketClerk *****************************/

void TicketClerk()
{ 

/*Local Part*/

int myIndex;

Acquire(ticketClerkIndexLockInt);
myIndex=nextTCIndex;
nextTCIndex++;
Release(ticketClerkIndexLockInt);
	
	while(1)
	{ 
		/*ticketClerkLineLock->Acquire();*/
		Acquire(ticketClerkLineLockInt);
		
		if(managerTcWait[myIndex]==1)
		{
			/*If the Manager has been asked to go to break*/
			ticketClerkState[myIndex]=-2;
			managerTcWait[myIndex]=0;
			Print("\nTicketClerk[%d] is going on break.\n",myIndex,1,1);

			/*Broadcasting all customers in the group to find a new line*/
			reFindLineTC[myIndex]=1;       

			/*ticketClerkLineCV[myIndex]->Broadcast(ticketClerkLineLock);*/
			Broadcast(ticketClerkLineCVInt[myIndex],ticketClerkLineLockInt);
		}
		else
		{

			if(ticketClerkLineCount[myIndex]>0)
			{
				/*If a customer is waiting for TC*/
				Print("\nTicketClerk[%d] has a line length=%d and is signaling a customer.\n\0",myIndex,ticketClerkLineCount[myIndex] PRINTMETOO 1,1);
				ticketClerkState[myIndex]=1;
				ticketClerkLineCount[myIndex]--;

				/* ticketClerkLineCV[myIndex]->Signal(ticketClerkLineLock); */
				Signal(ticketClerkLineCVInt[myIndex],ticketClerkLineLockInt);
			} 
			else
			{
				/*If no one is waiting for him*/
				ticketClerkState[myIndex]=0;
				Print("\nTicketClerk[%d] has no one in line. I am available for a customer.\n\0",myIndex,1,1);
			}
	}
		/*Releasing TCLine Lock after acquiring TC Lock to ensure customer cannot grab it before him*/

		/*ticketClerkLockInt[myIndex]->Acquire();*/
		Acquire(ticketClerkLockInt[myIndex]);

		/*ticketClerkLineLock->Release();*/
		Release(ticketClerkLineLockInt);
		
		/*ticketClerkCV[myIndex]->Wait(ticketClerkLock[myIndex]);*/
		Wait(ticketClerkCVInt[myIndex],ticketClerkLockInt[myIndex]);


		/*check final exit condition after being signalled*/
		Acquire(checkFinalExitLockInt);
		if (finalExitFlag==1)
		{
			Release(checkFinalExitLockInt);
			/*Manager woke me up and asking me to exit*/
			break;
		}		
		Release(checkFinalExitLockInt);

		/*Calculating the amount of tickets per group*/
		ticketClerkAmount[myIndex]=noOfTickets[myIndex]*12;
		Print("\nTicketClerk[%d] has an order for %d tickets and the cost is $%d.\n\0",myIndex,noOfTickets[myIndex] PRINTMETOO ticketClerkAmount[myIndex],1);

		/*ticketClerkCV[myIndex]->Signal(ticketClerkLock[myIndex]);*/
		Signal(ticketClerkCVInt[myIndex],ticketClerkLockInt[myIndex]);

		/*ticketClerkCV[myIndex]->Wait(ticketClerkLock[myIndex]);*/
		Wait(ticketClerkCVInt[myIndex],ticketClerkLockInt[myIndex]);

		/*totalAmtTicketLock->Acquire();*/
		Acquire(totalAmtTicketLockInt);
		
		totalAmtTicket+=ticketClerkAmount[myIndex];
		
		/*totalAmtTicketLock->Release();*/
		Release(totalAmtTicketLockInt);
		
		totalAmountTicketClerk[myIndex]+=ticketClerkAmount[myIndex];

		/*Asking the customer to leave*/
		/*ticketClerkCV[myIndex]->Signal(ticketClerkLock[myIndex]);*/
		Signal(ticketClerkCVInt[myIndex],ticketClerkLockInt[myIndex]);

		/*ticketClerkLock[myIndex]->Release();*/
		Release(ticketClerkLockInt[myIndex]);
	}

		Exit(0);
}


/*---------------------------------------------------------------------------------------------------------------------------
// ConcessionClerk(int) function
//
// This simulates a Concession Clerk in the Movie Theater. Each thread of this function represents a concession clerk
// 1 argument is passed 
// myIndex : it is the id of the CC which remains constant for the entire life of this function
//
// No value is returned 
//---------------------------------------------------------------------------------------------------------------------------*/

void ConcessionClerk()
{ 

int myIndex;
int myConcessionClerk;
int customerTotal;

/*Local Part*/

Acquire(concessionClerkIndexLockInt);
myIndex=nextCCIndex;
nextCCIndex++;
Release(concessionClerkIndexLockInt);


	myConcessionClerk=-1;
	while(1)
	{ 
		Acquire(concessionClerkLineLockInt);
		/*concessionClerkLineLock->Acquire();*/

		/*If Manager has asked the Clerk to go on wait*/
		if(managerCcWait[myIndex]==1)
		{
			
			/*Changing the state of CC as -2(Break State)*/
			concessionClerkState[myIndex]=-2;
			managerCcWait[myIndex]=0;
			Print("\nConcessionClerk[%d] is going on break.\n",myIndex,1,1);
			/*Broadcasting all customers in the group*/
			reFindLineCC[myIndex]=1;  
			
			Broadcast(concessionClerkLineCVInt[myIndex],concessionClerkLineLockInt);
			/*concessionClerkLineCV[myIndex]->Broadcast(concessionClerkLineLock);*/
		}
		else
		{
		/*If the Clerk is not asked to go on wait by Manager*/
		if(concessionClerkLineCount[myIndex]>0)
		{
			Print("\nConcessionClerk[%d] has a line length=%d and is signaling a customer.\n",myIndex,concessionClerkLineCount[myIndex] PRINTMETOO 1,1);
			/* Change state to 1 as busy */
			concessionClerkState[myIndex]=1;
			concessionClerkLineCount[myIndex]--;

			Signal(concessionClerkLineCVInt[myIndex],concessionClerkLineLockInt);
			/*concessionClerkLineCV[myIndex]->Signal(concessionClerkLineLock);*/
		} 
		else
		{
			/* If the CC is available */
			concessionClerkState[myIndex]=0;
			Print("\nConcessionClerk[%d] has no one in line. I am available for a customer.\n",myIndex,1,1);
		}
		
		}
		
		/*Acquiring f the CC Lock before eleasing Line Lock to ensure that customer cannot grab before him*/
		
		Acquire(concessionClerkLockInt[myIndex]);
		/*concessionClerkLock[myIndex]->Acquire();*/

		Release(concessionClerkLineLockInt);
		/*concessionClerkLineLock->Release();*/

		Wait(concessionClerkCVInt[myIndex],concessionClerkLockInt[myIndex]);
		/*concessionClerkCV[myIndex]->Wait(concessionClerkLock[myIndex]);*/


		/*check final exit condition after being signalled*/
		Acquire(checkFinalExitLockInt);
		if (finalExitFlag==1)
		{
			Release(checkFinalExitLockInt);
			/*Manager woke me up and asking me to exit*/
			break;
		}		
		Release(checkFinalExitLockInt);

		/*Calculating the amount of Soda and popcorn*/
		amountSoda[myIndex]=noOfSoda[myIndex]*4;
		amountPopcorn[myIndex]=noOfPopcorn[myIndex]*5;
		
		customerTotal=amountSoda[myIndex]+ amountPopcorn[myIndex];
		
		Print("\nConcessionClerk[%d] has an order for %d popcorn and %d soda. The cost is $%d.\n",myIndex,noOfPopcorn[myIndex] PRINTMETOO noOfSoda[myIndex],customerTotal PRINTMETOO 1);
		/*printf("\nConcessionClerk[%d] has an order for %d popcorn and %d soda. The cost is $%d.\n",myIndex,noOfPopcorn[myIndex],noOfSoda[myIndex],customerTotal);*/
		
		/*Told customer about the total money and waiting him to pay.*/

		Signal(concessionClerkCVInt[myIndex],concessionClerkLockInt[myIndex]);
		/*concessionClerkCV[myIndex]->Signal(concessionClerkLock[myIndex]);*/

		Wait(concessionClerkCVInt[myIndex],concessionClerkLockInt[myIndex]);
		/*concessionClerkCV[myIndex]->Wait(concessionClerkLock[myIndex]);*/

		Print("\nConcessionClerk[%d] has been paid for the order.\n",myIndex,1,1);
		/*printf("\nConcessionClerk[%d] has been paid for the order.\n",myIndex);*/
		
		
		/*Updating total earning*/
		
		Acquire(totalAmtPopSodaLockInt);
		/*totalAmtPopSodaLock->Acquire();*/

		totalMoneySoda+=amountSoda[myIndex];
		totalMoneyPopcorn+=amountPopcorn[myIndex];
		
		Release(totalAmtPopSodaLockInt);
		/*totalAmtPopSodaLock->Release();*/
		
		totalAmountConcessionClerk[myIndex]+=amountSoda[myIndex]+amountPopcorn[myIndex];		
		
		Signal(concessionClerkCVInt[myIndex],concessionClerkLockInt[myIndex]);
		/*concessionClerkCV[myIndex]->Signal(concessionClerkLock[myIndex]);*/
		
		/*Asking customer to leave*/
		Release(concessionClerkLockInt[myIndex]);
		/*concessionClerkLock[myIndex]->Release();*/
	
		
	}

			Exit(0);    
}

/* /////////////////////////////////////////////////END of CC/////////////////////////////////////////////////////////////// */


/*
//---------------------------------------------------------------------------------------------------------------------------
// TicketTaker(int) function
//
// This simulates a TicketTaker in the Movie Theater. Each thread of this function represents a TicketTaker
// 1 argument is passed 
// myIndex : it is the id of the TicketTaker which remains constant for the entire life of this function
//
// No value is returned 
//---------------------------------------------------------------------------------------------------------------------------
*/

void TicketTaker()
{
	int check =1;	/* Check that its not coming from wait state. */

int myIndex;
/*Local Part*/

Acquire(ticketTakerIndexLockInt);
myIndex=nextTTIndex;
nextTTIndex++;
Release(ticketTakerIndexLockInt);

	while(1)
	{ 
		/* ticketTakerLineLock->Acquire(); */
		Acquire(ticketTakerLineLockInt);
		
		if(ticketTakerLineCount[myIndex]>0)
		{
			/* If any customer is waiting in his line. */

			check=0;
			ticketTakerState[myIndex]=1;
			ticketTakerLineCount[myIndex]--;

			/* printf("\nTicketTaker[%d] has a line length [%d] and is signaling a customer.\n",myIndex,ticketTakerLineCount[myIndex]); */
			Print("\nTicketTaker[%d] has a line length [%d] and is signaling a customer.\n",myIndex,ticketTakerLineCount[myIndex] PRINTMETOO 1, 1);

			/* ticketTakerLineCV[myIndex]->Signal(ticketTakerLineLock); */
			Signal(ticketTakerLineCVInt[myIndex],ticketTakerLineLockInt);
		}

		else
		{
			/* If nobody was present infront of him and then too manager asked him to take tickets, so will wait until the last customer. */

			check=0;
			ticketTakerState[myIndex]=0;

			/* printf("\nTicketTaker[%d] has no one in line. I am available for a customer.\n",myIndex); */
			Print("\nTicketTaker[%d] has no one in line. I am available for a customer.\n",myIndex,1,1);
		}

		/* ticketTakerLock[myIndex]->Acquire(); */
		Acquire(ticketTakerLockInt[myIndex]);
		
		/* ticketTakerLineLock->Release(); */
		Release(ticketTakerLineLockInt);

		/* ticketTakerCV[myIndex]->Wait(ticketTakerLock[myIndex]); */
		Wait(ticketTakerCVInt[myIndex],ticketTakerLockInt[myIndex]);


		/* $$$$$$$$$$$$   check final exit condition after being signalled  from their queue  $$$$$$$$$$$$ */
		Acquire(checkFinalExitLockInt);
		if (finalExitFlag==1)
		{
			Release(checkFinalExitLockInt);
			/*Manager woke me up and asking me to exit*/
			break;
		}		
		Release(checkFinalExitLockInt);

		
		/* If I am woken up by manager, this will happen when all the cust have taken tickets and nobody left. */

		if (managerWokeTT[myIndex]==1)
		{
			check=0;
			/* $$$$$managerWokeTT[myIndex]=0;*/
			
			/* ticketTakerLock[myIndex]->Release(); */
			Release(ticketTakerLockInt[myIndex]);

			/* Manager Told ~~~~ TicketTaker to stop taking tickets. */

			/* ticketTakerLineLock->Acquire(); */
			Acquire(ticketTakerLineLockInt);

			ticketTakerState[myIndex]=-1;

			/* ttWaitShowOverLock[myIndex]->Acquire(); */
			Acquire(ttWaitShowOverLockInt[myIndex]);
			
			/* ticketTakerLineLock->Release(); */
			Release(ticketTakerLineLockInt);

			/* waiting on the CV, will come out when Manager will ask him to do so. */

			/* ttWaitShowOverCV[myIndex]->Wait(ttWaitShowOverLock[myIndex]); */
			Wait(ttWaitShowOverCVInt[myIndex],ttWaitShowOverLockInt[myIndex]);

			/* ttWaitShowOverLock[myIndex]->Release(); */
			Release(ttWaitShowOverLockInt[myIndex]);


			/* $$$$$$$$$$$$   check final exit condition after being signalled  from their manager queue  $$$$$$$$$$$$ */
			Acquire(checkFinalExitLockInt);
			if (finalExitFlag==1)
			{
				Release(checkFinalExitLockInt);
				/*Manager woke me up and asking me to exit*/
				break;
			}		
			Release(checkFinalExitLockInt);

			Acquire(ticketTakerLockInt[myIndex]);
			managerWokeTT[myIndex]=0;
			Release(ticketTakerLockInt[myIndex]);

			continue;
		}
	
		/* custTicketsApprovedLock->Acquire(); */
		Acquire(custTicketsApprovedLockInt); 
		
		/* Checking that the number of tickets customer has do not exceed the theater room capacity. */

		if (custTicketsApproved+custNoOfTicket[myIndex] <=25)
		{
			/* Number of tickets customer has are approved. */

			/*printf("\nTicketTaker[%d] is allowing the group into the theater. The number of tickets taken is %d.\n",myIndex,custNoOfTicket[myIndex]); */
			Print("\nTicketTaker[%d] is allowing the group into the theater. The number of tickets taken is %d.\n",myIndex,custNoOfTicket[myIndex] PRINTMETOO 1,1);

			custTicketsApproved+=custNoOfTicket[myIndex];

			/* custTicketsApprovedLock->Release(); */
			Release(custTicketsApprovedLockInt);

			ticketTakerGroupIndicator[myIndex]=1;

			/* ticketTakerCV[myIndex]->Signal(ticketTakerLock[myIndex]); */
			Signal(ticketTakerCVInt[myIndex],ticketTakerLockInt[myIndex]);

			/* ticketTakerLock[myIndex]->Release(); */
			Release(ticketTakerLockInt[myIndex]);
		}

		else
		{
			/* No of tickets that cust has are exceeding the teater capacity. */

			/* printf("\nTicketTaker[%d] is not allowing the group into the theater. The number of taken tickets is %d and the group size is %d including HeadCustomer.\n",myIndex,custTicketsApproved,custNoOfTicket[myIndex]); */
			Print("\nTicketTaker[%d] is not allowing the group into the theater. The number of taken tickets is %d and the group size is %d including HeadCustomer.\n",myIndex,custTicketsApproved PRINTMETOO custNoOfTicket[myIndex],1);

			/* printf("\nTicketTaker[%d] has stopped taking tickets\n",myIndex); */
			Print("\nTicketTaker[%d] has stopped taking tickets\n",myIndex,1,1);

			/* custTicketsApprovedLock->Release(); */
			Release(custTicketsApprovedLockInt);

			ticketTakerGroupIndicator[myIndex]=0; 

			/* Signal to go in lobby. */

			/* ticketTakerCV[myIndex]->Signal(ticketTakerLock[myIndex]); */
			Signal(ticketTakerCVInt[myIndex],ticketTakerLockInt[myIndex]);

		ticketTakerWaitingAfterTheaterFull[myIndex]=1; 

			/* ticketTakerLock[myIndex]->Release(); */
			Release(ticketTakerLockInt[myIndex]);

			/* ticketTakerLineLock->Acquire(); */
			Acquire(ticketTakerLineLockInt);

			ticketTakerState[myIndex]=-1;

			/* Ask other cust in Line to go back to lobby as I have rejected 1 cust. */

			/* ticketTakerLineCV[myIndex]->Broadcast(ticketTakerLineLock); */
			Broadcast(ticketTakerLineCVInt[myIndex],ticketTakerLineLockInt);

			/* ticketTakerLineLock->Release(); */
			Release(ticketTakerLineLockInt);					

			/* Going to wait state. Now when manager will change my state, customer will come and wake me up. */

			/* ttWaitShowOverLock[myIndex]->Acquire(); */
			Acquire(ttWaitShowOverLockInt[myIndex]);

			/* ttWaitShowOverCV[myIndex]->Wait(ttWaitShowOverLock[myIndex]); */
			Wait(ttWaitShowOverCVInt[myIndex],ttWaitShowOverLockInt[myIndex]);

			/* ttWaitShowOverLock[myIndex]->Release(); */
			Release(ttWaitShowOverLockInt[myIndex]);

			check = 1;

		/* $$$$$$$$$$$$   check final exit condition after being signalled  from their manager queue  $$$$$$$$$$$$ */
		Acquire(checkFinalExitLockInt);
		if (finalExitFlag==1)
		{
			Release(checkFinalExitLockInt);
			/*Manager woke me up and asking me to exit*/
			break;
		}		
		Release(checkFinalExitLockInt);


		Acquire(ticketTakerLockInt[myIndex]);
		ticketTakerWaitingAfterTheaterFull[myIndex]=0; 
		Release(ticketTakerLockInt[myIndex]);
		}

	}  /* End of while statement. */

	Exit(0);
}






/*/---------------------------------------------------------------------------------------------------------------------------
// CustomerHead(int) function
//
// This simulates a Customer Head in the Movie Theater. Each thread of this function represents a Head Customer
// 1 argument is passed 
// data : It is typecasted backed to the structure type which is storing the informaton about the group 
//
// No value is returned 
//---------------------------------------------------------------------------------------------------------------------------*/

void CustomerHead()
{


int myTicketClerk;
int myConcessionClerk;
int i,j;
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


	/*Local Part*/
Acquire(groupNumberLockInt);
myGroupNumber=nextGroupNumber;
nextGroupNumber++;
Release(groupNumberLockInt);

Acquire(customerNumberLockInt);
myCustomerNumber=nextCustomerNumber;
nextCustomerNumber++;
Release(customerNumberLockInt);

/*Acquire(groupSizeLockInt);*/
myGroupSize=sizeForGroupArr[myGroupNumber];
/*Release(groupSizeLockInt);*/

/*	CustomerData* myData = (CustomerData*)data;
	
	//Now store the values in simple int variables to make the code easier to read
	int myGroupNumber = myData->groupNumber;
	int myCustomerNumber = myData->customerNumber;
	int myGroupSize=myData->groupSize;
*/
 
	while(1)
	{ 
		myTicketClerk=-1;
		/*ticketClerkLineLock->Acquire();*/
		Acquire(ticketClerkLineLockInt);
	
		/* If any TC is available, not busy */
		for (i=0;i<noOfTC ;i++ )
		{
			if (ticketClerkState[i]==0)
			{
				myTicketClerk=i;
				ticketClerkState[i]=1;
				Print("\nCustomer[%d] in Group[%d] is getting in TicketClerk line[%d]\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,1);
				break;
			}		
		}	
		
		/*Acquiring the shortest Line*/
		if (myTicketClerk == -1)
		{
			shortestTCLine;
			shortestTCLineLen=ticketClerkLineCount[0];

			for(i=0;i<noOfTC;i++)
			{
				/*check that the TC is not on break*/
				if(ticketClerkState[i]!=-2)
				{
					shortestTCLine=i;
					shortestTCLineLen=ticketClerkLineCount[i];
					break;
				}
				else
				{
					/*checking which all TCs are on break*/
					Print("\nCustomer[%d] in Group [%d] sees TicketClerk[%d] is on break.\n\0",myCustomerNumber,myGroupNumber PRINTMETOO i,1);
				}
			}		
			
			/*Assigning the TC with shortest Line*/
			for (i=1;i<noOfTC;i++ )
			{
				if (ticketClerkState[i]==1 && (shortestTCLineLen > ticketClerkLineCount[i]))
				{
					shortestTCLine=i;
					shortestTCLineLen=ticketClerkLineCount[i];

				}
			}

			myTicketClerk=shortestTCLine;
			ticketClerkLineCount[myTicketClerk]++;
			Print("\nCustomer[%d] in Group[%d] is getting in TicketClerk line[%d]\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,1);
		
			/*ticketClerkLineCV[myTicketClerk]->Wait(ticketClerkLineLock);*/
			Wait(ticketClerkLineCVInt[myTicketClerk],ticketClerkLineLockInt);
		}
	
	/*If I have been asked to re-acquire the line*/
	if(reFindLineTC[myTicketClerk]==1)
	{
		/*customers in the line of  ticketclerk[%d] are starting the process of finding shortest line again as they are asked to re-arrange*/
		custFindLineTC[myTicketClerk]++;

		if(ticketClerkLineCount[myTicketClerk]==custFindLineTC[myTicketClerk])
		{
			reFindLineTC[myTicketClerk]=0;
			ticketClerkLineCount[myTicketClerk]=0;
			custFindLineTC[myTicketClerk]=0;
		}

		/*ticketClerkLineLock->Release();*/
		Release(ticketClerkLineLockInt);

		continue;
	}
	else
	{
		/*continue with the same clerk*/

		/*ticketClerkLineLock->Release();*/
		Release(ticketClerkLineLockInt);

		break;
	}
		
	}	/*while loop*/

	/*Time to interact with clerk*/
	/*ticketClerkLock[myTicketClerk]->Acquire();*/
	Acquire(ticketClerkLockInt[myTicketClerk]);

	/*Telling the number of tickets I wish to purchase i.e Groupsize+HeadCust*/
	noOfTickets[myTicketClerk]=myGroupSize+1;

	Print("\nCustomer[%d] in Group[%d] is walking up to TicketClerk[%d] to buy %d tickets\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,noOfTickets[myTicketClerk] PRINTMETOO 1);
/*Print("\nSubstitute- Customer[%d] in Groupis walking up to TicketClerk[%d] to buy %d tickets\n\0",myCustomerNumber,myTicketClerk,noOfTickets[myTicketClerk]);*/
	/*ticketClerkCV[myTicketClerk]->Signal(ticketClerkLock[myTicketClerk]);*/
	Signal(ticketClerkCVInt[myTicketClerk],ticketClerkLockInt[myTicketClerk]);

	/*ticketClerkCV[myTicketClerk]->Wait(ticketClerkLock[myTicketClerk]);*/
	Wait(ticketClerkCVInt[myTicketClerk],ticketClerkLockInt[myTicketClerk]);
	
	/*Waiting for TC o tell me the amount*/
	Print("\nCustomer[%d] in Group[%d] in TicketClerk line[%d] is paying %d for tickets\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,ticketClerkAmount[myTicketClerk] PRINTMETOO 1);
	/*Print("\nSubstitute- Customer[%d] in Group in TicketClerk line[%d] is paying %d for tickets\n\0",myCustomerNumber,myTicketClerk,ticketClerkAmount[myTicketClerk]);*/

	/*ticketClerkCV[myTicketClerk]->Signal(ticketClerkLock[myTicketClerk]);*/
	Signal(ticketClerkCVInt[myTicketClerk],ticketClerkLockInt[myTicketClerk]);

	/*ticketClerkCV[myTicketClerk]->Wait(ticketClerkLock[myTicketClerk]);*/
	Wait(ticketClerkCVInt[myTicketClerk],ticketClerkLockInt[myTicketClerk]);

	Print("\nCustomer[%d] in Group[%d] is leaving TicketClerk[%d]\n\0",myCustomerNumber,myGroupNumber PRINTMETOO myTicketClerk,1);
	
	/*Going out from TC*/
	/*ticketClerkLock[myTicketClerk]->Release();*/
	Release(ticketClerkLockInt[myTicketClerk]);

	
	
	/******************************End of Tc Interaction**********************************/
	
	
	
	/* ///////////////////// customer  interaction for food///////////// */


	Acquire(groupLockInt[myGroupNumber]);
	/*groupLock[myGroupNumber]-> Acquire();*/

	haveTickets[myGroupNumber]=1;
	/*haveTickets[myGroupNumber]=true;*/

	if(myGroupSize != 0)
	{
	Broadcast(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
	/*groupCV[myGroupNumber]-> Broadcast(groupLock[myGroupNumber]);*/

	/* waiting for group to give choices of popcorn n soda*/
	Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
	/*groupCV[myGroupNumber]-> Wait(groupLock[myGroupNumber]);*/

	/*Code for individual customer food choice*/
	}
	
	/*Random value for popcorn and soda*/
	
	/* popRandVal=rand()%100+1;
	sodaRandVal=rand()%100+1; */
	popRandVal=Rand(100);
	popRandVal=popRandVal+1;
	sodaRandVal=Rand(100);
	sodaRandVal=sodaRandVal+1;


	printPop=0;
	printSoda=0;

	/* Ensuring 75% probability */
	if(popRandVal<=75)
	{		
			groupPopcorn[myGroupNumber]++;
			printPop=1;
	}
	/*Ensuring 75% probability*/
	if(sodaRandVal<=75)
	{		
		groupSoda[myGroupNumber]++;
		printSoda=1;
	}
	
	/* Got the number of popcorns and soda for my group */
	Print("\nCustomer[%d] in group[%d] wants %d popcorn and %d soda.\n",myCustomerNumber,myGroupNumber PRINTMETOO printPop,printSoda PRINTMETOO 1);
	
/*	groupLock[myGroupNumber]->Release();*/
	Release(groupLockInt[myGroupNumber]);


	/* /////////////    CC   Interaction      //////////////// */
	
	while(1)
	{ 
		myConcessionClerk=-1;

/*	concessionClerkLineLock->Acquire();*/
	Acquire(concessionClerkLineLockInt);
	
	/* Checing for a available clerk */
	for (i=0;i<noOfCC ;i++ )
	{
		if (concessionClerkState[i]==0)
		{
			myConcessionClerk=i;
			concessionClerkState[i]=1;
			Print("\nCustomer[%d] in Group[%d] is getting in ConcessionClerk Line[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,1);
			break;
		}

	}

	/* If no clerk is available */
	if (myConcessionClerk == -1)
	{
		/*int shortestCCLine;
		int shortestCCLineLen;*/

		for(i=0;i<noOfCC;i++)
		{
			if(concessionClerkState[i]!=-2)
			{
				/* checking that the particular clerk is not on break */
				shortestCCLine=i;
				shortestCCLineLen=concessionClerkLineCount[i];
				break;
			}
			else
			{
				/* checking all the clerks on break */
				Print("\nCustomer[%d] in Group [%d] sees ConcessionClerk[%d] is on break.\n",myCustomerNumber,myGroupNumber PRINTMETOO i,1);
			}
		}		
		
		for (j=1;j<noOfCC;j++)
		{
			/* If the clerk is busy and he has the shortest line */
			if (concessionClerkState[j]==1 && (shortestCCLineLen > concessionClerkLineCount[j]))
			{
				shortestCCLine=j;
				shortestCCLineLen=concessionClerkLineCount[j];
			}
		}
		
		/* Got my clerk */
		myConcessionClerk=shortestCCLine;
		concessionClerkLineCount[myConcessionClerk]++;

		/*printf("\nCustomer[%d] in Group[%d] is getting in ConcessionClerk Line[%d]\n",myCustomerNumber,myGroupNumber,myConcessionClerk);*/
		Print("\nCustomer[%d] in Group[%d] is getting in ConcessionClerk Line[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,1);

		/*concessionClerkLineCV[myConcessionClerk]->Wait(concessionClerkLineLock);*/
		Wait(concessionClerkLineCVInt[myConcessionClerk],concessionClerkLineLockInt);
	}
	
	/* If manager has aked me to acquire the shortest line again */
	if(reFindLineCC[myConcessionClerk]==1)
		{
			/*customers in the line of  concessionclerk[%d] are starting the process of finding shortest line again as they are asked to re-arrange*/
			custFindLineCC[myConcessionClerk]++;

			if(concessionClerkLineCount[myConcessionClerk]==custFindLineCC[myConcessionClerk])
			{
				reFindLineCC[myConcessionClerk]=0;
				concessionClerkLineCount[myConcessionClerk]=0;
				custFindLineCC[myConcessionClerk]=0;
			}

			/*concessionClerkLineLock->Release();*/
			Release(concessionClerkLineLockInt);

			continue;
		}
	else
		{	
			/*concessionClerkLineLock->Release();*/
			Release(concessionClerkLineLockInt);
			
			break;
	    }
		
	}	/*while loop*/

	/*Time to interact with clerk*/
	/*concessionClerkLock[myConcessionClerk]->Acquire();*/
	Acquire(concessionClerkLockInt[myConcessionClerk]);

	/*groupLock[myGroupNumber]->Acquire();*/
	Acquire(groupLockInt[myGroupNumber]);

	noOfSoda[myConcessionClerk]=groupSoda[myGroupNumber];
	noOfPopcorn[myConcessionClerk]=groupPopcorn[myGroupNumber];

	/*groupLock[myGroupNumber]->Release();*/
	Release(groupLockInt[myGroupNumber]);

	/*concessionClerkCV[myConcessionClerk]->Signal(concessionClerkLock[myConcessionClerk]);*/
	Signal(concessionClerkCVInt[myConcessionClerk],concessionClerkLockInt[myConcessionClerk]);

	/*printf("\nCustomer[%d] in Group[%d] is walking up to ConcessionClerk[%d] to buy [%d] popcorn and [%d] soda.\n",myCustomerNumber,myGroupNumber,myConcessionClerk,noOfPopcorn[myConcessionClerk],noOfSoda[myConcessionClerk]);*/
	Print("\nCustomer[%d] in Group[%d] is walking up to ConcessionClerk[%d] to buy [%d] popcorn and [%d] soda.\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,noOfPopcorn[myConcessionClerk] PRINTMETOO noOfSoda[myConcessionClerk]); 
	
	/*Waiting for clerk to tell him the amount*/
	/*concessionClerkCV[myConcessionClerk]->Wait(concessionClerkLock[myConcessionClerk]);*/
	Wait(concessionClerkCVInt[myConcessionClerk],concessionClerkLockInt[myConcessionClerk]);

	foodAmount=amountSoda[myConcessionClerk]+amountPopcorn[myConcessionClerk];

	/*printf("\nCustomer[%d] in Group[%d] in ConcessionClerk line[%d] is paying[%d] for food.\n",myCustomerNumber,myGroupNumber,myConcessionClerk,foodAmount);*/
	Print("\nCustomer[%d] in Group[%d] in ConcessionClerk line[%d] is paying[%d] for food.\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,foodAmount PRINTMETOO 1);

	/*concessionClerkCV[myConcessionClerk]->Signal(concessionClerkLock[myConcessionClerk]);*/
	Signal(concessionClerkCVInt[myConcessionClerk],concessionClerkLockInt[myConcessionClerk]);
	
	/*Giving the amount, now waiting his confirmation to leave*/

	/*concessionClerkCV[myConcessionClerk]->Wait(concessionClerkLock[myConcessionClerk]);*/
	Wait(concessionClerkCVInt[myConcessionClerk],concessionClerkLockInt[myConcessionClerk]);

	/*printf("\nCustomer[%d] in Group [%d] is leaving ConcessionClerk[%d]\n",myCustomerNumber,myGroupNumber,myConcessionClerk);*/
	Print("\nCustomer[%d] in Group [%d] is leaving ConcessionClerk[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO myConcessionClerk,1);

	/*concessionClerkLock[myConcessionClerk]->Release();*/
	Release(concessionClerkLockInt[myConcessionClerk]);

/* ///////////////////		Done With CC	////////////////// */


/************************ Ticket Taker Interaction **************************/


/*Ticket Taker and Head Customer Interaction*/

/*ticketTakerLineLock->Acquire();*/
Acquire(ticketTakerLineLockInt);

while(1)	/*It will run until break happens when it is allowed to go in the theater.*/
{

/* Monitor variable to check the state of TT. If he is taking tickets then go to TTLineCV else go to LobbyCV. */

/*isTakingTickets=false;*/
isTakingTickets=0;

for (i=0;i<noOfTT;i++)
{
	if (ticketTakerState[i]!=-1)
	{
		/*I got a TT who is taking tickets.*/
		isTakingTickets=1;
		break;			
	}
}


if (isTakingTickets != 1)
{

	/*I should add myself to the Lobby queue.*/

	/*ticketTakerLineLock->Release();*/
	Release(ticketTakerLineLockInt);

	/*customerLobbyLock->Acquire();*/
	Acquire(customerLobbyLockInt);

	Print("\nCustomer[%d] in Group[%d] is in the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	
	/*customerLobbyCV->Wait(customerLobbyLock);*/
	Wait(customerLobbyCVInt,customerLobbyLockInt);

	Print("\nCustomer[%d] in Group[%d] is leaving the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	
	/*customerLobbyLock->Release();*/
	Release(customerLobbyLockInt);

	/*ticketTakerLineLock->Acquire();*/
	Acquire(ticketTakerLineLockInt);

continue;
}

	/* Theatre is not full. Fighting for the shortest TT line. */

	myTicketTaker=-1;

	/*see if any ticket taker is not busy*/
	for (i=0; i <noOfTT; i++)
	{
		if (ticketTakerState[i]==0)
		{
			/*a TT is not busy, I dont have to wait*/
			myTicketTaker=i;
			ticketTakerState[i]=1;
			Print("\nCustomer[%d] in Group[%d] is getting in TicketTaker Line[%d] \n",myCustomerNumber,myGroupNumber PRINTMETOO myTicketTaker,1);
			break;
		}

	} 
	
	/*finding the TT with shortest Line*/
	if (myTicketTaker==-1)
	{
		/*int shortestTTLine;
		int shortestTTLineLen=ticketTakerLineCount[0];
		*/

		shortestTTLineLen = ticketTakerLineCount[0];
		
		for(i=0;i<noOfTT;i++)
		{
			if(ticketTakerState[i]!=-1)
			{
				shortestTTLine=i;
				shortestTTLineLen=ticketTakerLineCount[i];

				break;
			}
		}

		for (i=1; i<noOfTT; i++)
		{
			/*checking if the TT is busy and his line is shorter*/

			 if (ticketTakerState[i]==1 && (shortestTTLineLen > ticketTakerLineCount[i]))
			 {
				 shortestTTLine=i;
				 shortestTTLineLen > ticketTakerLineCount[i];
			 }
	    }
		
		/* I have the shortest Line */
		myTicketTaker=shortestTTLine;

		total++;

		/* Get in that Line */
		ticketTakerLineCount[myTicketTaker]++;
		Print("\nCustomer[%d] in Group[%d] is getting in TicketTaker Line[%d] \n",myCustomerNumber,myGroupNumber PRINTMETOO myTicketTaker,1);
		
		/*ticketTakerLineCV[myTicketTaker]->Wait(ticketTakerLineLock);*/
		Wait(ticketTakerLineCVInt[myTicketTaker],ticketTakerLineLockInt);


		/*Signalled by TT, now check, whether to go back to lobby?*/

		if (ticketTakerGroupIndicator[myTicketTaker]==0) 
		{
			/*If that TT has stopped taking tickets and asking to go in Lobby*/
			Print("\nCustomer[%d] in Group[%d] sees TicketTaker[%d] is no longer taking tickets. Going to the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO myTicketTaker,1);
				
			countCustTT++;

			/*ticketTakerLineLock->Release();*/
			Release(ticketTakerLineLockInt);

			/*customerLobbyLock->Acquire();*/
			Acquire(customerLobbyLockInt);

			Print("\nCustomer[%d] in Group[%d] is in the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

			/*customerLobbyCV->Wait(customerLobbyLock);*/
			Wait(customerLobbyCVInt,customerLobbyLockInt);

			/*printf("\nCustomer[%d] in Group[%d] is leaving the lobby.\n",myCustomerNumber,myGroupNumber);*/
			Print("\nCustomer[%d] in Group[%d] is leaving the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
			
			/*customerLobbyLock->Release();*/
			Release(customerLobbyLockInt);
			
			/* When manager wakes me up from the lobby */

			/*ticketTakerLineLock->Acquire();*/
			Acquire(ticketTakerLineLockInt);			

			countCustTT--;
			total--;
			continue;
		}
		else
		{
			/*ticketTakerLineLock->Release();*/			
			Release(ticketTakerLineLockInt);			
		}

	} /* end of if */
		

		else
		{
			total++;

			/*ticketTakerLineLock->Release();*/
			Release(ticketTakerLineLockInt);			
		}

	/*Time to interact with the Ticket Taker*/

	/*ticketTakerLock[myTicketTaker]->Acquire();*/
	Acquire(ticketTakerLockInt[myTicketTaker]);

	custNoOfTicket[myTicketTaker]=myGroupSize+1;	/* 3 should be changed to the actual dynamic statement */

	/*Giving my tickets to TT
	//If theatre is full then ticketTakerTheatreCountStatus is 1. he wont entertain more customers. */

	/*ticketTakerCV[myTicketTaker]->Signal(ticketTakerLock[myTicketTaker]);*/
	Signal(ticketTakerCVInt[myTicketTaker],ticketTakerLockInt[myTicketTaker]);

	/*ticketTakerLineLock->Acquire();	*/
	Acquire(ticketTakerLineLockInt);	

	countCustTT++;

	/*ticketTakerLineLock->Release();	*/
	Release(ticketTakerLineLockInt);	

	/*ticketTakerCV[myTicketTaker]->Wait (ticketTakerLock[myTicketTaker]);*/
	Wait(ticketTakerCVInt[myTicketTaker],ticketTakerLockInt[myTicketTaker]);

	/*I have been given an indicator value. Check that. It its 1, I can go inside else I have to wait in the lobby.*/
	if (ticketTakerGroupIndicator[myTicketTaker]==1)
	{
		/* Yippeee...Go inside the theater */

		/*ticketTakerLock[myTicketTaker]->Release();*/
		Release(ticketTakerLockInt[myTicketTaker]);
		
		Print("\nCustomer[%d] in Group[%d] is leaving TicketTaker[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO myTicketTaker,1);

		/* Adding myself to theatre CV by the theatre lock. */
		break; 	/*exit from the while loop. You already are inside the theater.*/
	}

	/*ticketTakerLock[myTicketTaker]->Release();*/
	Release(ticketTakerLockInt[myTicketTaker]);

	/*printf("\nCustomer[%d] in Group[%d] is leaving TicketTaker[%d]\n",myCustomerNumber,myGroupNumber,myTicketTaker);*/
	Print("\nCustomer[%d] in Group[%d] is rejected by TicketTaker[%d]. Going to the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO myTicketTaker,1);
	
	/*ticketTakerLineLock->Acquire();*/
	Acquire(ticketTakerLineLockInt);
	
	/*ticketTakerLineLock->Release();*/
	Release(ticketTakerLineLockInt);

	/*customerLobbyLock->Acquire();*/
	Acquire(customerLobbyLockInt);

	/*printf("\nCustomer[%d] in Group[%d] is in the lobby.\n",myCustomerNumber,myGroupNumber);*/
	Print("\nCustomer[%d] in Group[%d] is in the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	
	/*customerLobbyCV->Wait(customerLobbyLock);*/
	Wait(customerLobbyCVInt,customerLobbyLockInt);
	
	/*printf("\nCustomer[%d] in Group[%d] is leaving the lobby.\n",myCustomerNumber,myGroupNumber);*/
	Print("\nCustomer[%d] in Group[%d] is leaving the lobby.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
 
	/*customerLobbyLock->Release();*/
	Release(customerLobbyLockInt);

	/*ticketTakerLineLock->Acquire();*/
	Acquire(ticketTakerLineLockInt);

	countCustTT--;
	total--;
 
  } /*End of while statement*/
 
	/* Forming the Group to go inside theater room. */
	if(myGroupSize != 0)
	{
		/*groupLock[myGroupNumber]-> Acquire();*/
		Acquire(groupLockInt[myGroupNumber]);

		canGoInsideTheater[myGroupNumber]=1;
		
		/*printf("\nHeadCustomer[%d] of group[%d] has told the group to proceed.\n",myCustomerNumber,myGroupNumber);*/
		Print("\nHeadCustomer[%d] of group[%d] has told the group to proceed.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
		
		/*groupCV[myGroupNumber]->Broadcast(groupLock[myGroupNumber]);*/
		Broadcast(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);

		/*movieTheaterLock->Acquire();*/
		Acquire(movieTheaterLockInt);

		/*groupLock[myGroupNumber]->Release();*/
		Release(groupLockInt[myGroupNumber]);

	}

	else
	{
		/*movieTheaterLock->Acquire();*/
		Acquire(movieTheaterLockInt);
	}
 
  /*Customer group can go inside the theater room.*/

	custEnteredTheater++;

	/*Calling function for assigning the seats to the group*/
	AssignSeat(myGroupSize+1, myGroupNumber);

	/*Calling function to view the assigned seat*/
	MySeat(myGroupNumber);

	counterVal[myGroupNumber]++;

	/*printf("\nCustomer[%d] in Group[%d] has found the following seat: row[%d] and seat[%d]\n",myCustomerNumber,myGroupNumber,rowNo,columnNo);*/
	Print("\nCustomer[%d] in Group[%d] has found the following seat: row[%d] and seat[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO rowNo,columnNo PRINTMETOO 1);

	/*printf("\nCustomer[%d] of group[%d] is sitting in a theater room seat.\n",myCustomerNumber,myGroupNumber);*/
	Print("\nCustomer[%d] of group[%d] is sitting in a theater room seat.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

	/*movieTheaterCV->Wait(movieTheaterLock);*/
	Wait(movieTheaterCVInt,movieTheaterLockInt);

	/*Movie Over*/

	/*groupLock[myGroupNumber]->Acquire();*/
	Acquire(groupLockInt[myGroupNumber]);

	/*movieTheaterLock->Release();*/
	Release(movieTheaterLockInt);

	if(myGroupSize != 0)
	{
		/*printf("\nHeadCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber);*/
		Print("\nHeadCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
		
		/*groupCV[myGroupNumber]->Wait(groupLock[myGroupNumber]);*/
		Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);

		/*printf("\nHeadCustomer[%d] of group[%d] has told the group to proceed.\n",myCustomerNumber,myGroupNumber);*/
		Print("\nHeadCustomer[%d] of group[%d] has told the group to proceed.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

		/*Asking group to proceed*/

		/*groupCV[myGroupNumber]->Broadcast(groupLock[myGroupNumber]);*/
		Broadcast(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
	}

	/*movieTheaterLock->Acquire();*/
	Acquire(movieTheaterLockInt);

	/*groupLock[myGroupNumber]->Release();*/
	Release(groupLockInt[myGroupNumber]);
		
	/*Leaving Theater*/
	custLeavingTheater++;

	/*groupLock[myGroupNumber]->Acquire();*/
	Acquire(groupLockInt[myGroupNumber]);

	/*movieTheaterLock->Release();*/
	Release(movieTheaterLockInt);

	/*Went out of theater after re-grouping, now broadcasting for bathroom*/

	/*int bathRoomValue=rand()%100+1;*/
	bathRoomValue = Rand(100);
	bathRoomValue=bathRoomValue+1;

	if(bathRoomValue<=25)
	{
		/*printf("\nCustomer[%d] in Group[%d] is going to the bathroom.\n",myCustomerNumber,myGroupNumber);*/
		Print("\nCustomer[%d] in Group[%d] is going to the bathroom.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

		/*bathroomLock->Acquire();*/
		Acquire(bathroomLockInt);

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
		/*currentThread->Yield();*/
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
Yield();

		/*bathroomLock->Release();*/
		Release(bathroomLockInt);

		/*printf("\nCustomer[%d] in Group[%d] is leaving the bathroom.\n",myCustomerNumber,myGroupNumber);*/
		Print("\nCustomer[%d] in Group[%d] is leaving the bathroom.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	}

	/*broadcast in groupCV for bathroom*/
	
	/*canGoBathroom[myGroupNumber]=true;*/
	canGoBathroom[myGroupNumber]=1;

	if(myGroupSize != 0)
	{
		/*groupCV[myGroupNumber]->Broadcast(groupLock[myGroupNumber]);*/
		Broadcast(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);

		/*Waiting in bathroom Lobby*/
		/*printf("\nHeadCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber);*/
		Print("\nHeadCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

		/*bathroomLobbyCV[myGroupNumber]->Wait(groupLock[myGroupNumber]);*/
		Wait(bathroomLobbyCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
		
		/*All group members have returned from bathroom, so signal them to go.*/

		/*printf("\nHeadCustomer[%d] of group[%d] has told the group to proceed.\n",myCustomerNumber,myGroupNumber);*/
		Print("\nHeadCustomer[%d] of group[%d] has told the group to proceed.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

		/*bathroomLobbyCV[myGroupNumber]->Broadcast(groupLock[myGroupNumber]);*/
		Broadcast(bathroomLobbyCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
	}

	/*groupLock[myGroupNumber]->Release(); */
	Release(groupLockInt[myGroupNumber]);

	/*custFinalExitLock->Acquire();*/
	Acquire(custFinalExitLockInt);

	custFinalExitCount++;

	/*custFinalExitLock->Release();*/
	Release(custFinalExitLockInt);

	Exit(0);
}



/*
/---------------------------------------------------------------------------------------------------------------------------
// Customer(int) function
//
// This simulates a Customer in the Movie Theater. Each thread of this function represents a Customer
// 1 argument is passed 
// data : It is typecasted backed to the structure type which is storing the informaton about the group 
//
// No value is returned 
//---------------------------------------------------------------------------------------------------------------------------
*/

void Customer()
{ 

int printPop=0;		/*It will be 1 when cust takes popcorn*/
int printSoda=0;	/*It will be 1 when cust takes soda*/
int	popRandVal;
int	sodaRandVal;
int i;

int bathRoomValue;
	
int myGroupNumber,myCustomerNumber,myGroupSize;

		/*Local Part*/

	Acquire(determineCustGroupNumberLockInt);
	for(i=0;i<MAX_GRP;i++)		/* Determine the group number for customer */
	{
		if(availableCustSizeForGroupArr[i]==0)
			continue;

		availableCustSizeForGroupArr[i]--;
		myGroupNumber=i;
		break;
	}
	Release(determineCustGroupNumberLockInt);

	Acquire(customerNumberLockInt);
	myCustomerNumber=nextCustomerNumber;
	nextCustomerNumber++;
	Release(customerNumberLockInt);

	/*Acquire(groupSizeLockInt);*/
	myGroupSize=sizeForGroupArr[myGroupNumber];
	/*Release(groupSizeLockInt);*/


/*	//structure variable taht stores information about the group
	CustomerData* myData = (CustomerData*)data;

	int myGroupNumber = myData->groupNumber;
	int myCustomerNumber = myData->customerNumber;
	int myGroupSize= myData->groupSize;
*/	


	Print("\nCustomer [%d] in Group [%d] has entered the movie theater.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	
	Acquire(groupLockInt[myGroupNumber]);
	/*groupLock[myGroupNumber]->Acquire();*/

	/*If the headcustomer hasnt purchased the tickets yet then go on wait else proceed straight away*/
	if(!haveTickets[myGroupNumber])
	{

		Print("\nCustomer[%d] of group[%d] is waiting for the HeadCustomer.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

		/*groupCV[myGroupNumber]->Wait(groupLock[myGroupNumber]);*/
		Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
	}
	/*set the value of popcorn and soda now*/
	
	/* int popRandVal=rand()%100+1;
	int sodaRandVal=rand()%100+1;*/
	popRandVal=Rand(100);
	popRandVal=popRandVal+1;
	sodaRandVal=Rand(100);
	sodaRandVal=sodaRandVal+1;

	
	/*Determining 75% probability for customer*/
	if(popRandVal<=75)
	{
		groupPopcorn[myGroupNumber]++;
		printPop=1;
	}

	/*Determining 75% probability for customer*/
	if(sodaRandVal<=75)
	{
		groupSoda[myGroupNumber]++;
		printSoda=1;
	}

	givenFoodChoice[myGroupNumber]++;

	Print("\nCustomer[%d] in group[%d] wants %d popcorn and %d soda.\n",myCustomerNumber,myGroupNumber PRINTMETOO printPop,printSoda PRINTMETOO 1);

	Print("\nCustomer[%d] in Group[%d] has %d popcorn and %d soda request from a group member\n",myCustomerNumber,myGroupNumber PRINTMETOO printPop,printSoda PRINTMETOO 1);
	
	/*If all customer have given their foodchoice, then notify head*/

	if(givenFoodChoice[myGroupNumber]==myGroupSize)
	{ 
		/*groupCV[myGroupNumber]->Signal(groupLock[myGroupNumber]);*/
		Signal(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
	}

	/*groupLock[myGroupNumber]->Release();*/
	Release(groupLockInt[myGroupNumber]);

	/*After Taking Food, Going to Theater Room*/
	
	
	/*groupLock[myGroupNumber]->Acquire();*/
	Acquire(groupLockInt[myGroupNumber]);

	if(!canGoInsideTheater[myGroupNumber])
	{
		/*printf("\nCustomer[%d] of group[%d] is waiting for the HeadCustomer.\n",myCustomerNumber,myGroupNumber);*/
		Print("\nCustomer[%d] of group[%d] is waiting for the HeadCustomer.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

		/*groupCV[myGroupNumber]->Wait(groupLock[myGroupNumber]);*/
		Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
	}

	/*groupLock[myGroupNumber]->Release();  */
	Release(groupLockInt[myGroupNumber]);  
	
	/*My group Head asked me to go inside the theater.*/

	/*movieTheaterLock->Acquire();*/
	Acquire(movieTheaterLockInt);

	custEnteredTheater++;
	
	MySeat(myGroupNumber);

	counterVal[myGroupNumber]++;

	/*printf("\nCustomer[%d] in Group[%d] has found the following seat: row[%d] and seat[%d]\n",myCustomerNumber,myGroupNumber,rowNo,columnNo);*/
	Print("\nCustomer[%d] in Group[%d] has found the following seat: row[%d] and seat[%d]\n",myCustomerNumber,myGroupNumber PRINTMETOO rowNo,columnNo PRINTMETOO 1);
	
	/*printf("\nCustomer[%d] of group[%d] is sitting in a theater room seat.\n",myCustomerNumber,myGroupNumber);*/
	Print("\nCustomer[%d] of group[%d] is sitting in a theater room seat.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

	/*movieTheaterCV->Wait(movieTheaterLock);*/
	Wait(movieTheaterCVInt,movieTheaterLockInt);

	/*printf("\nCustomer[%d] of group[%d] is getting out of a theater room seat.\n",myCustomerNumber,myGroupNumber);*/
	Print("\nCustomer[%d] of group[%d] is getting out of a theater room seat.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

	/*movieTheaterLock->Release();*/
	Release(movieTheaterLockInt);

	/*Re-grouping inside the theater*/

	/*groupLock[myGroupNumber]->Acquire();*/
	Acquire(groupLockInt[myGroupNumber]);

	counterAfterMuvi[myGroupNumber]++;

	if (counterAfterMuvi[myGroupNumber]==myGroupSize)
	{		
		/*groupCV[myGroupNumber]->Signal(groupLock[myGroupNumber]);*/
		Signal(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
	}
	
	/*Waiting for confirmation from Headcustomer to proceed. */

	/*printf("\nCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber);*/
	Print("\nCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

	/*groupCV[myGroupNumber]->Wait(groupLock[myGroupNumber]); */
	Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);	

	/*printf("\nCustomer[%d] of group[%d] has been told by the HeadCustomer to proceed.\n",myCustomerNumber,myGroupNumber);*/
	Print("\nCustomer[%d] of group[%d] has been told by the HeadCustomer to proceed.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	
	/*groupLock[myGroupNumber]->Release();*/
	Release(groupLockInt[myGroupNumber]);

	/*movieTheaterLock->Acquire();*/
	Acquire(movieTheaterLockInt);

	custLeavingTheater++;

	/*movieTheaterLock->Release(); */
	Release(movieTheaterLockInt);	

	/*Went out of theater after re-grouping*/

	/*groupLock[myGroupNumber]->Acquire();*/
	Acquire(groupLockInt[myGroupNumber]);

	if(!canGoBathroom[myGroupNumber])
	{
		/*groupCV[myGroupNumber]->Wait(groupLock[myGroupNumber]);*/
		Wait(groupCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
	}

	/*Determining the random value to go to bathroom*/

	/*int bathRoomValue=rand()%100+1;*/
	bathRoomValue=Rand(100);
	bathRoomValue=bathRoomValue+1;

	if(bathRoomValue<=25)
	{
		/*printf("\nCustomer[%d] in Group[%d] is going to the bathroom.\n",myCustomerNumber,myGroupNumber);*/
		Print("\nCustomer[%d] in Group[%d] is going to the bathroom.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

		/*bathroomLock->Acquire();*/
		Acquire(bathroomLockInt);

		/*Inside the bathroom*/

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
		/*currentThread->Yield();*/
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
Yield();
		/*bathroomLock->Release();*/
		Release(bathroomLockInt);

		/*printf("\nCustomer[%d] in Group[%d] is leaving the bathroom.\n",myCustomerNumber,myGroupNumber);*/
		Print("\nCustomer[%d] in Group[%d] is leaving the bathroom.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);
	}

	counterAfterBathroom[myGroupNumber]++;

	/*Telling grup head that all members have come back from bathroom*/

	if(counterAfterBathroom[myGroupNumber]==myGroupSize)
	{
		/*bathroomLobbyCV[myGroupNumber]->Signal(groupLock[myGroupNumber]);*/
		Signal(bathroomLobbyCVInt[myGroupNumber],groupLockInt[myGroupNumber]);
	}

	/*Waiting for grouphead to signal to proceed*/

	/*printf("\nCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber);*/
	Print("\nCustomer[%d] of group[%d] is waiting for the group to form.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

	/*bathroomLobbyCV[myGroupNumber]->Wait(groupLock[myGroupNumber]);*/
	Wait(bathroomLobbyCVInt[myGroupNumber],groupLockInt[myGroupNumber]);

	/*printf("\nCustomer[%d] of group[%d] has been told by the HeadCustomer to proceed.\n",myCustomerNumber,myGroupNumber);	*/
	Print("\nCustomer[%d] of group[%d] has been told by the HeadCustomer to proceed.\n",myCustomerNumber,myGroupNumber PRINTMETOO 1,1);

	/*groupLock[myGroupNumber]->Release(); */
	Release(groupLockInt[myGroupNumber]);	

	/*I am exiting, update the custFinalExitCount*/

	/*custFinalExitLock->Acquire();*/
	Acquire(custFinalExitLockInt);

	custFinalExitCount++;

	/*custFinalExitLock->Release(); */
	Release(custFinalExitLockInt);	


	Exit(0);
}


/*
//---------------------------------------------------------------------------------------------------------------------------
// Movie Technician() function
//
// This simulates a Movie Technician in the Movie Theater. One thread of this function only as 1 Tech is reqd.
// 0 argument is passed 
//
// No value is returned 
//---------------------------------------------------------------------------------------------------------------------------
*/

void MovieTechnician()
{
	int i;

	while(1)
	{
		/* movieTechLock->Acquire(); */
		Acquire(movieTechLockInt);

		/* Waiting for the Manager signal. */

		/* movieTechCV->Wait(movieTechLock); */
		Wait(movieTechCVInt,movieTechLockInt);


		/*check final exit condition after being signalled*/
		Acquire(checkFinalExitLockInt);
		if (finalExitFlag==1)
		{
			Release(checkFinalExitLockInt);
			/*Manager woke me up and asking me to exit*/
			break;
		}		
		Release(checkFinalExitLockInt);


		/* printf("\nThe MovieTechnician has started the movie.\n"); */
		Print("\nThe MovieTechnician has started the movie.\n",1,1,1);

		for(i=0;i<250; i++)
		{
			/* Movie running. */

			/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
			/*currentThread->Yield();*/
			/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
			Yield();
		}

		/* printf("\nThe MovieTechnician has ended the movie.\n"); */
		Print("\nThe MovieTechnician has ended the movie.\n",1,1,1);

		/* movieTheaterLock->Acquire(); */
		Acquire(movieTheaterLockInt);

		/* printf("\nThe MovieTechnician has told all customers to leave the theater room.\n"); */
		Print("\nThe MovieTechnician has told all customers to leave the theater room.\n",1,1,1);

		/* movieTheaterCV->Broadcast(movieTheaterLock); */
		Broadcast(movieTheaterCVInt,movieTheaterLockInt);

		/*movieTheaterLock->Release();*/
		Release(movieTheaterLockInt);

		/* Setting the movie over flag. */

		isMovieOver=1;

		/* movieTechLock->Release(); */
		Release(movieTechLockInt);
	}

	Exit(0);
}





/*
//---------------------------------------------------------------------------------------------------------------------------
// Manager() function
//
// This simulates a Manager in the Movie Theater. One thread is accessing this function as only 1 Manager is required.
// 1 argument is passed 
// myIndex : it is the id of the TicketTaker which remains constant for the entire life of this function
//
// No value is returned 
//---------------------------------------------------------------------------------------------------------------------------
*/

void Manager()
{
	int i,j;
	int randBreakValue;

	while(1)
	{	
		/*To send TC on break.*/

		for(i=0;i<noOfTC;i++)
		{
			/*ticketClerkLineLock->Acquire();*/
			Acquire(ticketClerkLineLockInt);

			if(ticketClerkLineCount[i]<3 && (ticketClerkOnBreak < (noOfTC-1)))
			{    
				/*Sending TC on Break with 0 customers in Line.*/

				if(ticketClerkLineCount[i]==0 && ticketClerkState[i]==0)
				{     
					/*Random value for sending a clerk on break*/

					/* int randBreakValue= rand()%100+1; */
					randBreakValue= Rand(100);
					randBreakValue=randBreakValue+1;

					if(randBreakValue<=20)  
					{  
						/*printf("\nManager has told TicketClerk[%d] to go on break.\n",i);*/
						Print("\nManager has told TicketClerk[%d] to go on break.\n",i,1,1);
						
						ticketClerkState[i]=-2;
						ticketClerkOnBreak++;
					}
				}

				else
				{
					/*Sending TC on Break with less than 3 customers in Line.*/

					/*int randBreakValue= rand()%100+1;*/
					randBreakValue= Rand(100);
					randBreakValue=randBreakValue+1;

					if(randBreakValue<=20) 
					{ 
                        managerTcWait[i]=1;
					   	ticketClerkOnBreak++;

						/*printf("\nManager has told TicketClerk[%d] to go on break.\n",i);*/
						Print("\nManager has told TicketClerk[%d] to go on break.\n",i,1,1);
					}
				}
			}

			/*ticketClerkLineLock->Release();*/
			Release(ticketClerkLineLockInt);
		}
			
		/*For bringing TCs off break.*/
		for(i=0;i<noOfTC;i++)
		{
			/*ticketClerkLineLock->Acquire();*/
			Acquire(ticketClerkLineLockInt);

			if(ticketClerkLineCount[i]>5 && (ticketClerkOnBreak >=1))
			{
			    for(j=0;j<noOfTC;j++)
				{ 		
					if (ticketClerkState[j]==-2)
					{   
						/*Bringing back a clerk from break*/

						ticketClerkState[j]=0;
						ticketClerkLineCount[j]=0;
						ticketClerkOnBreak--;
						reFindLineTC[j]=0;

						/*printf("\nTicketClerk[%d] is coming off break.",j);*/
						Print("\nTicketClerk[%d] is coming off break.",j,1,1);

						break;
				        }
				}

				/*Flag to tell that a new clerk has come so re-acquire shortest line*/

				reFindLineTC[i]=1;

				/*ticketClerkLineCV[i]-> Broadcast(ticketClerkLineLock);*/
				Broadcast(ticketClerkLineCVInt[i],ticketClerkLineLockInt);
			}

			/*ticketClerkLineLock->Release();*/
			Release(ticketClerkLineLockInt);
		}

		/*To send CC on break*/

		for(i=0;i<noOfCC;i++)
		{
			/*concessionClerkLineLock->Acquire();*/
			Acquire(concessionClerkLineLockInt);

			if(concessionClerkLineCount[i]<3 && (conClerkOnBreak < (noOfCC-1)))
			{    
				/* If the CC has less than 3 customers in his line and this is not the last CC serving. */

				if(concessionClerkLineCount[i]==0 && concessionClerkState[i]==0)
				{     
					/*int randBreakValue= rand()%100;*/
					randBreakValue= Rand(100);
			  
					if(randBreakValue<20)  
					{  
						/*Sending CC on Break with 0 customers in Line.*/

						/*printf("\n Manager has told ConcessionClerk[%d] to go on break \n",i);*/
						Print("\nManager has told ConcessionClerk[%d] to go on break \n",i,1,1);
						
						concessionClerkState[i]=-2;
						conClerkOnBreak++;
					}
				}

				else
				{
					/*int randBreakValue= rand()%100;*/
					randBreakValue= Rand(100);

					if(randBreakValue<20) 
					{ 	  
						/* Sending CC on Break with less than 3 customers in Line. */

						managerCcWait[i]=1;
						conClerkOnBreak++;

						/*printf("\n Manager has told ConcessionClerk[%d] to go on break \n",i);*/
						Print("\nManager has told ConcessionClerk[%d] to go on break \n",i,1,1);
					}
				}
			}

			/*concessionClerkLineLock->Release();*/
			Release(concessionClerkLineLockInt);
		}
			
		/* To call CCs off the break. */

		for(i=0;i<noOfCC;i++)
		{
			/*concessionClerkLineLock->Acquire();*/
			Acquire(concessionClerkLineLockInt);


			if(concessionClerkLineCount[i]>5 && (conClerkOnBreak >=1))
			{
                for(j=0;j<noOfCC;j++)
		        { 		
					if (concessionClerkState[j]==-2)
		            {   
						/* Assigning Default values again. */

						concessionClerkState[j]=0;
						concessionClerkLineCount[j]=0;
						conClerkOnBreak--;						
						reFindLineCC[j]=0;

						/*printf("\nConcessionClerk [%d] is coming off break.",j);*/
						Print("\nConcessionClerk [%d] is coming off break.",j,1,1);

						break;
			        }
				}

				/* Setting the flag for customers. */

				reFindLineCC[i]=1;

				/*concessionClerkLineCV[i]-> Broadcast(concessionClerkLineLock);*/
	            Broadcast(concessionClerkLineCVInt[i],concessionClerkLineLockInt);
			}

			/*concessionClerkLineLock->Release();*/
			Release(concessionClerkLineLockInt);
		}


		/*****************************		TicketTaker Manager Interaction		**********************************/

		/*ticketTakerLineLock->Acquire();*/
		Acquire(ticketTakerLineLockInt);

		for (i=0;i<noOfTT;i++)
		{
			/* If the ticket taker state is 0 and all customers have giventheir tickets so tell him to change his state. */

			if(ticketTakerState[i]==0 && (countCustTT==totalHeadCust ))	/*|| total==totalHeadCust */ /*countCustTT*/
			{				
				managerWokeTT[i]=1;

				/*ticketTakerLock[i]->Acquire();*/
				Acquire(ticketTakerLockInt[i]);

				/* Manager Asking#### TicketTaker[%d] to change their state to -1 */

				ticketTakerState[i]==-1;

				/*ticketTakerCV[i]->Signal(ticketTakerLock[i]);*/
				Signal(ticketTakerCVInt[i],ticketTakerLockInt[i]);

				/*ticketTakerLock[i]->Release();*/
				Release(ticketTakerLockInt[i]);
			}
		}		
		
		for (i=0;i<noOfTT;i++)
		{
			/* To check that whether any TT is taking tickets or not. */

			if(ticketTakerState[i]==-1)
				ttTakingTickets=0;
			else
			{ 
				ttTakingTickets=1;
				break;   
			}

		}

		/* ticketTakerLineLock->Release(); */
		Release(ticketTakerLineLockInt);

		/*movieTheaterLock->Acquire();*/
		Acquire(movieTheaterLockInt);

		/*custTicketsApprovedLock->Acquire();*/
		Acquire(custTicketsApprovedLockInt);

		if (ttTakingTickets==0 && custEnteredTheater==custTicketsApproved && custTicketsApproved > 0) 
		{
			/* TT have stopped taking tickets and all customers have seated inside the theater. */

			custTicketsApproved=0;

			/* movieTheaterLock->Release(); */
			Release(movieTheaterLockInt);

			/* custTicketsApprovedLock->Release(); */
			Release(custTicketsApprovedLockInt);

			/* Asking Technician to Start the movie. */

			/* printf("\nManager is telling the MovieTechnnician to start the movie.\n"); */
			Print("\nManager is telling the MovieTechnnician to start the movie.\n",1,1,1);

			/* movieTechLock->Acquire(); */
			Acquire(movieTechLockInt);

			/* movieTechCV->Signal(movieTechLock); */
			Signal(movieTechCVInt,movieTechLockInt);

			/* movieTechLock->Release(); */
			Release(movieTechLockInt);
		}

		else
		{
			/* movieTheaterLock->Release(); */
			Release(movieTheaterLockInt);

			/* custTicketsApprovedLock->Release(); */
			Release(custTicketsApprovedLockInt);
		}

		/* movieTechLock->Acquire(); */
		Acquire(movieTechLockInt);

		/* movieTheaterLock->Acquire(); */
		Acquire(movieTheaterLockInt);
		
		/* To check that the movie is over and all customers have left the theater room . */

		if ((custEnteredTheater==custLeavingTheater) && isMovieOver==1 && custEnteredTheater>0)
		{
			custEnteredTheater=0;
			custLeavingTheater=0;
			
			isMovieOver = 0;

			/* Vacant the seats again */

			for(i=0;i<5;i++)
			{
				for(j=0;j<5;j++)
				{
					movieRoomSeatNoArray[i][j]=0;
					movieRoomGrpNoArray[i][j]=0;
				}
			}

			/* movieTheaterLock->Release(); */
			Release(movieTheaterLockInt);

			/* movieTechLock->Release(); */
			Release(movieTechLockInt);
			
			/* ticketTakerLineLock->Acquire(); */
			Acquire(ticketTakerLineLockInt);			

			for(i=0;i<noOfTT;i++)
			{
				ticketTakerLineCount[i]=0;
				ticketTakerState[i]=1;
				ticketTakerGroupIndicator[i]=1; 
			}

			/* ticketTakerLineLock->Release(); */
			Release(ticketTakerLineLockInt);
			
			/* Broadcasting customers in Lobby as TT have started tacking tickets. */

			/*customerLobbyLock->Acquire();*/
			Acquire(customerLobbyLockInt);

			/* customerLobbyCV->Broadcast(customerLobbyLock); */
			Broadcast(customerLobbyCVInt,customerLobbyLockInt);

			/* customerLobbyLock->Release(); */
			Release(customerLobbyLockInt);

			/*Bring back TTs to action. */

			for (i=0;i<noOfTT;i++)
			{
				/* ttWaitShowOverLock[i]->Acquire(); */
				Acquire(ttWaitShowOverLockInt[i]);

				/* ttWaitShowOverCV[i]->Signal(ttWaitShowOverLock[i]); */
				Signal(ttWaitShowOverCVInt[i],ttWaitShowOverLockInt[i]);

				/* ttWaitShowOverLock[i]->Release(); */
				Release(ttWaitShowOverLockInt[i]);
			}
		}

		else
		{
			/* movieTheaterLock->Release(); */
			Release(movieTheaterLockInt);

			/* movieTechLock->Release(); */
			Release(movieTechLockInt);
		}

		/* Calculation of total money made by theater. */

		/* totalAmtPopSodaLock->Acquire(); */
		Acquire(totalAmtPopSodaLockInt);

		/* totalAmtTicketLock->Acquire(); */
		Acquire(totalAmtTicketLockInt);

		/* printf("\nTotal money made by office = $%d\n",totalMoneySoda+totalMoneyPopcorn+totalAmtTicket); */
		Print("\n Total money made by office = $%d. \n",totalMoneySoda+totalMoneyPopcorn+totalAmtTicket,1,1);
		
		/* totalAmtTicketLock->Release(); */
		Release(totalAmtTicketLockInt);

		/* totalAmtPopSodaLock->Release(); */
		Release(totalAmtPopSodaLockInt);

		/* Calculation of amount from each Ticket Clerk. */

		for(i=0;i<noOfTC;i++)
		{
			/*ticketClerkLock[i]->Acquire(); */
			Acquire(ticketClerkLockInt[i]);

			/* printf("\nManager collected $%d from TicketClerk[%d].\n",totalAmountTicketClerk[i],i); */
			Print("\nManager collected $%d from TicketClerk[%d].\n",totalAmountTicketClerk[i],i PRINTMETOO 1,1);

			/* ticketClerkLock[i]->Release(); */
			Release(ticketClerkLockInt[i]);
		}

		/* Calculation of amount from each concession Clerk. */

		for (i=0;i<2;i++)
		{
			/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
			/*currentThread->Yield();*/
			/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
			Yield();
		}

		for(i=0;i<noOfCC;i++)
		{
			/* concessionClerkLock[i]->Acquire(); */
			Acquire(concessionClerkLockInt[i]);

			/* printf("\nManager collected $%d from ConcessionClerk[%d].\n",totalAmountConcessionClerk[i],i); */
			Print("\nManager collected $%d from ConcessionClerk[%d].\n",totalAmountConcessionClerk[i],i PRINTMETOO 1,1);

			/* concessionClerkLock[i]->Release(); */
			Release(concessionClerkLockInt[i]);
		}

		/* End of Money Calculation. */

		/* Final Exit Condition. */

		/* custFinalExitLock->Acquire(); */
		Acquire(custFinalExitLockInt);

		if (custFinalExitCount==totalCustomerNumber)
		{
					Release(custFinalExitLockInt);
			/* If all customers exited the theater then manager shuld also exit. */
			/* printf("\n\nBye Bye..Simulation Completed!!\n"); */
			
		Acquire(checkFinalExitLockInt);
		finalExitFlag=1;
		Release(checkFinalExitLockInt);
		
		/*For bringing TC to exit condition*/
		for(i=0;i<noOfTC;i++)
		{
			Acquire(ticketClerkLockInt[i]);		
			Signal(ticketClerkCVInt[i],ticketClerkLockInt[i]);
			Release(ticketClerkLockInt[i]);
		}

		/*For bringing CC to exit condition*/
		for(i=0;i<noOfCC;i++)
		{
			Acquire(concessionClerkLockInt[i]);		
			Signal(concessionClerkCVInt[i],concessionClerkLockInt[i]);
			Release(concessionClerkLockInt[i]);
		}

		/*For bringing TT to exit condition*/
		
		for(i=0;i<noOfTT;i++)
		{
			Acquire(ticketTakerLockInt[i]);

			if (managerWokeTT[i]==1 || ticketTakerWaitingAfterTheaterFull[i]==1)
			{
				Release(ticketTakerLockInt[i]);

				Acquire(ttWaitShowOverLockInt[i]);
				Signal(ttWaitShowOverCVInt[i],ttWaitShowOverLockInt[i]);
				Release(ttWaitShowOverLockInt[i]);

			}
			else
			{
				Release(ticketTakerLockInt[i]);

				Acquire(ticketTakerLockInt[i]);		
				Signal(ticketTakerCVInt[i],ticketTakerLockInt[i]);
				Release(ticketTakerLockInt[i]);
			}
		}


		/*For bringing MovieTechnician to exit condition*/
		Acquire(movieTechLockInt);
		Signal(movieTechCVInt,movieTechLockInt);
		Release(movieTechLockInt);

		break;


			/*return;*/
		}

		/* custFinalExitLock->Release(); */
		Release(custFinalExitLockInt);

		for (i=0;i<200;i++)
		{
			/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
			/*currentThread->Yield();*/
			/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
			Yield();
		}

	}
			
			Exit(0);
}








/**************** void MovieSimulator() ****************/

void main()
{

int i,j;
int numberOfGroups;
int val;

Print("\nEnter the number of Ticket Clerks [1-5]\n",1,1,1);

	while(1)
	{	
	val=Scan();
	if(val >=1 && val <=5)
		{
		noOfTC=val;
		break;
		}
	else
		{
		Print("\nInvalid Valueof TC. Please enter within range..\n",1,1,1);
		continue;
		}
	}


Print("\nEnter the number of Concession Clerks [1-5]\n",1,1,1);

	while(1)
	{	
	val=Scan();
	if(val >=1 && val <=5)
		{
		noOfCC=val;
		break;
		}
	else
		{
		Print("\nInvalid Value of CC. Please enter within range..\n",1,1,1);
		continue;
		}
	}

Print("\nEnter the number of Ticket Takers [1-3] \n",1,1,1);

	while(1)
	{	
	val=Scan();
	if(val >=1 && val <=3)
		{
		noOfTT=val;
		break;
		}
	else
		{
		Print("\nInvalid Value of TT. Please enter within range..\n",1,1,1);
		continue;
		}
	}



Print("\nEnter the number of Customer Groups. No. of Group Members in each group is determined randomly in 1-5 range. Group Range: [1-30]\n",1,1,1);

	while(1)
	{	
	val=Scan();
	if(val >=1 && val <=30)
		{
		noOfGroups=val;
		break;
		}
	else
		{
		Print("\nInvalid Value of number of CustomersGroups. Please enter within range..\n",1,1,1);
		continue;
		}
	}

/*noOfTC=5;*/

/*noOfCC=5;*/

/*noOfTT=3;*/

/*noOfGroups=30;*/

/*****************************  TC Index , Customer Index , CC Index *****************************/

ticketClerkIndexLockInt=CreateLock("ticketClerkIndexLock",20);

groupNumberLockInt=CreateLock("groupNumberLockInt",18);
customerNumberLockInt=CreateLock("customerNumberLockInt",21);
groupSizeLockInt=CreateLock("groupSizeLockInt",16);


concessionClerkIndexLockInt=CreateLock("concessionClerkIndexLock",24);


/*Global Part for TT myIndex value*/
ticketTakerIndexLockInt=CreateLock("ticketTakerIndexLock",20);

checkFinalExitLockInt=CreateLock("checkFinalExitLock",18);

/*****************************  End of TC Index   *****************************/

/* #########	Initialization of the TicketTaker Variables		########## */

ticketTakerLineLockInt=CreateLock("ticketTakerLineLock",19);
/*ticketTakerLineLock=new Lock("ticketTakerLineLock");*/

ticketTakerManagerLockInt=CreateLock("ticketTakerManagerLock",22);
custTicketsApprovedLockInt=CreateLock("custTicketsApprovedLock",23);
customerLobbyLockInt=CreateLock("customerLobbyLock",17);

ticketTakerManagerCVInt=CreateCV("ticketTakerManagerCV",20);
customerLobbyCVInt=CreateCV("customerLobbyCV",15);

/*
ticketTakerManagerLock=new Lock("ticketTakerManagerLock");
custTicketsApprovedLock=new Lock("custTicketsApprovedLock");
ticketTakerManagerCV=new Condition("ticketTakerManagerCV");
customerLobbyCV= new Condition("customerLobbyCV");
customerLobbyLock= new Lock("customerLobbyLock");
*/

/*
ticketTakerLineCV=new Condition*[noOfTT];
ticketTakerCV=new Condition*[noOfTT];
ticketTakerLock=new Lock*[noOfTT];
ttWaitShowOverCV=new Condition*[noOfTT];
ttWaitShowOverLock=new Lock*[noOfTT];
*/

for (i=0;i<noOfTT;i++)
{   custNoOfTicket[i]=0;
	ticketTakerLineCount[i]=0;
	ticketTakerState[i]=1;
	ticketTakerGroupIndicator[i]=1; 

	ticketTakerLineCVInt[i]=CreateCV("ticketTakerLineCV",17);
	/*ticketTakerLineCV[i]=new Condition("ticketTakerLineCV");*/
	
	ticketTakerCVInt[i]=CreateCV("ticketTakerCV",13);
	/*ticketTakerCV[i]=new Condition("ticketTakerCV");*/

	ticketTakerLockInt[i]=CreateLock("ticketTakerLineLock",19);
	/*ticketTakerLock[i]=new Lock("ticketTakerLock");*/

	ttWaitShowOverCVInt[i]=CreateCV("ttWaitShowOverCV",16);
	/*ttWaitShowOverCV[i]=new Condition("ttWaitShowOverCV");*/

	ttWaitShowOverLockInt[i]=CreateLock("ttWaitShowOverLock",18);
	/*ttWaitShowOverLock[i]=new Lock("ttWaitShowOverLock");*/

	managerWokeTT[i]=0;
	ticketTakerWaitingAfterTheaterFull[i]=0;
	/*managerWokeTT[i]=false;*/
}


/* ##############		Initialization of Theater variables			############## */

movieTheaterLockInt=CreateLock("movieTheaterLock",16);
movieTechLockInt=CreateLock("movieTechLock",13);
custFinalExitLockInt=CreateLock("custFinalExitLock",17);
movieTheaterCVInt=CreateCV("movieTheaterCV",14);
movieTechCVInt=CreateCV("movieTechCV",11);

/*
movieTheaterLock=new Lock("movieTheaterLock");
movieTechLock=new Lock("movieTechLock");
custFinalExitLock=new Lock("custFinalExitLock");
movieTheaterCV=new Condition("movieTheaterCV");
movieTechCV=new Condition("movieTechCV");
*/

custEnteredTheater=0;
custLeavingTheater=0;
ttTakingTickets=1;
/*ttTakingTickets=true;*/

isMovieOver=0;
/* isMovieOver=false; */

custFinalExitCount=0;
totalCustomerNumber=0;
countCustTT=0;
total=0;

/* ^^^^^^^^^^^^^^		Seat variabes		^^^^^^^^^^^^ */
rowNo=0;
columnNo=0;

/*		//////////		Initialization of TicketClerk Variables		/////////		*/

totalAmtTicketLockInt=CreateLock("totalAmtTicketLock",18);
ticketClerkLineLockInt=CreateLock("ticketClerkLineLock",19);

/*
totalAmtTicketLock=new Lock("totalAmtTicketLock");
ticketClerkLineLock=new Lock("ticketClerkLineLock");
*/

/*
ticketClerkLineCV=new Condition*[noOfTC];
ticketClerkCV=new Condition*[noOfTC];
ticketClerkLock=new Lock*[noOfTC];
*/

totalAmtTicket=0;

for (i=0;i<noOfTC;i++)
{
	ticketClerkLineCount[i]=0;
	ticketClerkState[i]=1;
	noOfTickets[i]=0;

	ticketClerkLineCVInt[i]=CreateCV("ticketClerkLineCV",17);
	/*ticketClerkLineCV[i]=new Condition("ticketClerkLineCV");*/

	ticketClerkCVInt[i]=CreateCV("ticketClerkCV",13);
	/*ticketClerkCV[i]=new Condition("ticketClerkCV");*/

	ticketClerkLockInt[i]=CreateLock("ticketClerkLock",15);
	/*ticketClerkLock[i]=new Lock("ticketClerkLock");*/

	managerCcWait[i]=0;
	custFindLineTC[i]=0;
	reFindLineTC[i]=0;
	totalAmountTicketClerk[i]=0;
}


/*	/////////////		Initialization of Concession Clerk Variables	//////////	*/

totalAmtPopSodaLockInt=CreateLock("totalAmtPopSodaLock",19);
concessionClerkLineLockInt=CreateLock("concessionClerkLineLock",23);

/*
totalAmtPopSodaLock=new Lock("totalAmtPopSodaLock");
concessionClerkLineLock=new Lock("concessionClerkLineLock");
*/

/*
concessionClerkLineCV=new Condition*[noOfCC];
concessionClerkCV=new Condition*[noOfCC];
concessionClerkLock=new Lock*[noOfCC];
*/

totalMoneySoda=0;
totalMoneyPopcorn=0;

for (i=0;i<noOfCC;i++)
{
	concessionClerkLineCount[i]=0;
	concessionClerkState[i]=1;
	reFindLineCC[i]=0;
	custFindLineCC[i]=0;
	managerCcWait[i]=0;

	concessionClerkLineCVInt[i]=CreateCV("concessionClerkLineCV",21);
	/*concessionClerkLineCV[i]=new Condition("concessionClerkLineCV");*/

	concessionClerkCVInt[i]=CreateCV("concessionClerkCV",17);
	/*concessionClerkCV[i]=new Condition("concessionClerkCV");*/

	concessionClerkLockInt[i]=CreateLock("concessionClerkLock",19);
	/*concessionClerkLock[i]=new Lock("concessionClerkLock");*/

	noOfSoda[i]=0;
	noOfPopcorn[i]=0;
	amountSoda[i]=0;
	amountPopcorn[i]=0;
	totalAmountConcessionClerk[i]=0;
}



/*Initialize the seats as vacant*/

for(i=0;i<5;i++)
{
	for(j=0;j<5;j++)
	{
		movieRoomSeatNoArray[i][j]=0;
		movieRoomGrpNoArray[i][j]=0;
	}
}



numberOfGroups =noOfGroups;
totalHeadCust=numberOfGroups;

/*
groupPopcorn= new int[numberOfGroups];
givenFoodChoice= new int[numberOfGroups];
groupSoda=new int[numberOfGroups];
counterAfterMuvi=new int[numberOfGroups];
counterAfterBathroom=new int [numberOfGroups];
counterVal=new int [numberOfGroups];

haveTickets=new bool[numberOfGroups];
canGoInsideTheater=new bool[numberOfGroups];
canGoBathroom=new bool[numberOfGroups];
*/

bathroomLockInt=CreateLock("bathroomLock",12);
/*bathroomLock=new Lock("bathroomLock");*/

/*
groupLock=new Lock*[numberOfGroups];
groupCV=new Condition*[numberOfGroups];
bathroomLobbyCV=new Condition*[numberOfGroups];
*/

determineCustGroupNumberLockInt=CreateLock("determineCustGroupNumberLock",28);

for ( i=0; i<numberOfGroups; i++ ) 
{
	counterAfterMuvi[i]=0;
	counterAfterBathroom[i]=0;

	canGoInsideTheater[i]=0;
	canGoBathroom[i]=0;

/*	canGoInsideTheater[i]=false;
	canGoBathroom[i]=false;	*/

	groupLockInt[i]=CreateLock("groupLock",9);
	groupCVInt[i]=CreateCV("groupCV",7);
	bathroomLobbyCVInt[i]=CreateCV("bathroomLobbyCV",15);

	/*groupLock[i]=new Lock("groupLock");
	groupCV[i]=new Condition("groupCV");
	bathroomLobbyCV[i]=new Condition("bathroomLobbyCV");*/

	groupPopcorn[i]=0;
	groupSoda[i]=0;
	givenFoodChoice[i]=0;
	
	haveTickets[i]=0;
	/* haveTickets[i]=false; */
	
	counterVal[i]=1;

/*###################################### Change this  ###############################*/
	/*groupSize=rand()%5;*/
	groupSize=Rand(5);
/*groupSize=0;*/
/*###################################### End of Change this  ###############################*/

	sizeForGroupArr[i]=groupSize;	/*Assigning group size*/
	availableCustSizeForGroupArr[i]=groupSize;

	totalCustomerNumber++;

	/*CustomerData *current = new CustomerData;	
	current->customerNumber = nextCustomerNumber;	
	totalCustomerNumber++; 	//don't need a lock as only this main thread does this*/
		
	/*current->groupNumber = i;	
	current->groupSize = groupSize;*/
	
	Fork(CustomerHead);
	/*Thread *t = new Thread("Head Customer");
	t->Fork( CustomerHead, (int)current );*/



	for (j=0; j<groupSize; j++ )
	{
		/*CustomerData *current1 = new CustomerData;
		current1->customerNumber = nextCustomerNumber;
		current1->groupSize=groupSize;
		totalCustomerNumber++;
		current1->groupNumber = i;*/
		
		
		/*//Creating customers for different groups*/
		totalCustomerNumber++;
		Fork(Customer);
		
		/*Thread *s = new Thread("Customer");
		s->Fork( Customer,(int)current1 );*/
	}

}

/*TC threads*/
    for (i=0; i<noOfTC; i++)
    {
		
		Fork(TicketClerk);

		/*Thread *c = new Thread("TC");
		c->Fork((VoidFunctionPtr)TicketClerk,i);*/
    }
/* CC threads */
    for (i=0; i<noOfCC; i++)
    {
		Fork(ConcessionClerk);
		/*Thread *c = new Thread("CC");
		c->Fork((VoidFunctionPtr)ConcessionClerk,i);*/
    }

/*TT threads*/
    for (i=0; i<noOfTT; i++)
    {
		Fork(TicketTaker);
	/*Thread *c = new Thread("TT");
	c->Fork((VoidFunctionPtr)TicketTaker,i);*/
    }
	
/*Movie Technician Thread*/

		Fork(MovieTechnician);
	/*Thread *d=new Thread("MovieTechnician");
	d->Fork((VoidFunctionPtr)MovieTechnician,0);*/

/*Manager Thread*/

		Fork(Manager);
	/*
	Thread *e=new Thread("Manager");
	e->Fork((VoidFunctionPtr)Manager,0);*/

	Exit(0);

}
