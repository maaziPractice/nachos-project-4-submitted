#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <time.h>
using namespace std;

struct PendingQElement
{
	int RqID;
	string name;
	string type;
	short int DecisiveCount;

};

struct DYHRq
{
	unsigned int RqID;
	char nameOfEntity[25];
	short int opcode;
	bool DIHEntity;
	bool ReqRep;
	short  int CMachID;
	short  int CmailBOX;
};

struct DYHRqforSig
{
	short int SignallerMachID;
	short int SignallerMailBxID;
	char nameOfEntity[27];
	short int opcode;
	bool DIHEntity; // destination server replies like do I have it??
	bool ReqRep;
	short int CMachID;
	short int CmailBOX;
};

enum OpCode
{
	 DYHC_LOCKs=0,
	 DYHC_CVs=1,
	 DYHC_MVs=2,
	 DYH_LOCKs=3,
	 DYH_CVs=4,
	 DYH_MVs=5
};

void ThreadTest ()
{

for(int i=0;i<10;i++)
{
	cout<<"\n"<<rand();

}

cout<<"\nSize of DYHRqforSig is"<<sizeof(DYHRqforSig)<<endl;
cout<<"\nSize of DYHRq is"<<sizeof(DYHRq)<<endl;


time_t seconds;
cout<<"\n\nSize of "<<sizeof(time_t);




  seconds = time (NULL);
  printf ("  ------- %lu hours since January 1, 1970", seconds );
 unsigned int sec;
 sec=(long unsigned int)seconds;

printf("\n\n hurayyyyyyyyyyyyyy %lu",sec);



 cout<<"MaxMailSize is" <<sizeof(DYHRq);
	cout<<"Size of DYHRq "<<sizeof(DYHRq)<<"\n";
	DYHRq rq;
	int opcodeOfPE=0;
	switch(opcodeOfPE)
						 {
						 	 	 case DYHC_LOCKs:


						 	 		 	 	 	 	 	 	 cout<<"\n\n\nThis works\n\n"<<endl;
						 	 		 	 	 	 	 	 	 break;





						 }
	//rq.opcode=DYH_LOCKs;

	//printf("\nrq.opcode  is %d\n",rq.opcode);


	map<string,int> map1;
	map<string,int>::iterator it1;


	map1.insert( pair<string,int>("ZZZ",100) );
	map1.insert( pair<string,int>("BBB",200) );


	it1 = map1.end();
	map1.insert(it1,pair<string,int>("AAA",200));

	for ( it1=map1.begin() ; it1 != map1.end(); it1++ )
		  		  	  {
		  		  	    cout << (*it1).first << " => " << ((*it1).second ) << endl;

		  		  	  }


while(true);

	map<string,PendingQElement*> mymap;
	  map<string,PendingQElement*>::iterator it;












	  string lockName,lockName1;
	  lockName="ticketTakerLock";
	  char str[3];
	  sprintf(str,"-Lock%u",DYH_LOCKs);
	  string m= lockName + str;
	  //if(strcmp("ticketTakerLock3",m.c_str())==0)
	  cout<<"\nhey  ---------------------------------------\n"<<m<<"\n\n";
	  lockName1="ticketTakerLock1";
	  PendingQElement* pe=new PendingQElement;
	  pe->RqID=-330;
	  pe->name=lockName;
	  pe->type="lock";
	  pe->DecisiveCount=9;

	  cout << "\n First - mymap.size() is " << (int) mymap.size() << endl;

	  mymap[lockName]=pe;

	  string key("ticketTakerLock");
	  PendingQElement* pe1 = mymap.find("ticketTakerLock")->second ;
	  cout<<"this is very se		xy  "<<pe1->type<<"\n\n";



	  PendingQElement* pe3=new PendingQElement;
	  	  pe3->RqID=-330;
	  	  pe3->name=lockName;
	  	  pe3->type="CVQQQQQQQQQQQvvvvvvvvvvvvvv";
	  	  pe3->DecisiveCount=9;

	  	PendingQElement* pe5=new PendingQElement;
	  		  	  pe5->RqID=-330;
	  		  	  pe5->name=lockName;
	  		  	  pe5->type="HEYYYYYYYYYYv";
	  		  	  pe5->DecisiveCount=9;

	  	mymap.insert( pair<string,PendingQElement*>("mayur",pe3) );
	  	mymap.insert( pair<string,PendingQElement*>("EXAm",pe5) );

	  	cout << "mymap.size() is " << (int) mymap.size() << endl;
	  	cout<< "\nmymap max size "<<mymap.max_size()<<endl;


	  	// show content:
	  	  //delete pe5;
	  	  for ( it=mymap.begin() ; it != mymap.end(); it++ )
	  	  {

	  	    cout << (*it).first << " => " << ((*it).second )->type << endl;
	  	    mymap.erase("EXAm");
	  	  }

	  	cout << "mymap.size() is " << (int) mymap.size() << endl;

	  	for ( it=mymap.begin() ; it != mymap.end(); it++ )
	  		  	  {
	  		  	    cout << (*it).first << " => " << ((*it).second )->type << endl;
	  		  	    mymap.erase("EXAm");
	  		  	  }




	  	PendingQElement* pe33 = mymap.find("mayur")->second ;
	  		  cout<<"this is very se		xy  "<<pe33->type<<"\n\n";


	  		string sd="mayur";
		  	mymap.erase (sd);
		  	cout << "\nmymap.size() is " << (int) mymap.size() << endl;




	  PendingQElement* pe2 = mymap.find(lockName)->second ;
	  cout<<"entity type is " << pe2->type<<"\n";
	  pe->DecisiveCount=1;
	  cout<<"PEntry dec Count is " <<pe2->DecisiveCount<<"\n";

	  lockName="mayur";
	  cout<<"pe name  "<<pe->name<<"\n";


	  if(mymap.find(lockName1) == mymap.end() )
		  	  	  cout << "element not in mymap:" << endl;
	  if(mymap.find(lockName) != mymap.end() )
	  		  	  	  cout << "element in mymap:" << endl;

	  lockName=pe->name;
	 cout << "a => " << (mymap.find(lockName)->second)->RqID << endl;












    char *line = "short line for testing";

    // with no arguments
    string s1;
    s1 = "Anatoliy";
    cout << "s1  is: " << s1 << endl;

    // copy constructor
    string s2 (s1);
    cout << "s2  is: " << s2 << endl;

    // one argumen
    string s3 (line);
    cout << "s3  is: " << s3 << endl;

    // first argumen C string
    // second number of characters
    string s4 (line,10);
    cout << "s4  is: " << s4 << endl;

    // 1 - C++ string
    // 2 - start position
    // 3 - number of characters
    string s5 (s3,6,4); // copy word 'line' from s3
    cout << "s5  is: " << s5 << endl;

    // 1 - number characters
    // 2 - character itself
    string s6 (15,'*');
    cout << "s6  is: " << s6 << endl;

    // 1 - start iterator
    // 2 - end iterator
    string s7 (s3.begin(),s3.end()-5);
    cout << "s7  is: " << s7 << endl;

    // you can instantiate string with assignment
    string s8 = "Anatoliy";
    cout << "s8  is: " << s8 << endl;

   // return 0;
}

/*

#include "copyright.h"

#include "system.h"
#include "network.h"
#include "post.h"
#include "interrupt.h"
#include <cstring>

using namespace std;

enum HeadCustomerStatus {NotBoughtTickets,BoughtTickets};
struct HeadCustomer
{
	int myGroupSize;
	int myGroupID;
	int  myGroupFoodChoices[4][10];// so number of people in a group is restricted to 10
	bool movieOrLobby;
    HeadCustomerStatus myStatus; //initilised to NotBoughtTickets
    char Name[20];
    
};
void WaitForGroupToAssembleOfHeadCust(HeadCustomer*);
struct RegularCustomer
{
		short int myCustID;   //have significcance for within group interaction only
		short int myGroupID;
		HeadCustomer* myHeadCustomer;
		
};


void ThreadTest() {

   // Thread *t;
    char *name;
    int i;
    totalCustomerNumber = 0;
    //Lock * withinGroupInteractionLock[10];  //10 assumed to be max number of groups

     HeadCustomer *headCustomer = new HeadCustomer;
     char *imp=(char *)headCustomer;
     headCustomer->myGroupID = 10;
     headCustomer->myGroupSize = -55;
     headCustomer->myStatus = NotBoughtTickets;
     strcpy(headCustomer->Name,"mayur sheth");
     char *stringStruct=new char[sizeof(HeadCustomer)];

     printf("\nSize of Head Customer %d\n",sizeof(RegularCustomer));
     for(i=0;i<sizeof(HeadCustomer);i++)
     {
    	stringStruct[i]=imp[i];
     }

     printf("\nAfter Serilsation1 %d\n",((HeadCustomer *)stringStruct)->myGroupID);
     printf("\nAfter Serilsation2 %d\n",((HeadCustomer *)stringStruct)->myGroupSize);
     printf("\nAfter Serilsation2 %s\n",((HeadCustomer *)stringStruct)->Name);

     HeadCustomer *headCustomer1 = new HeadCustomer;
     char *imp1=(char *)headCustomer1;
     for(i=0;i<sizeof(HeadCustomer);i++)
          {
         	imp1[i]=stringStruct[i];
          }
     printf("\nAfter Desearilsation in Struct  %d \n", headCustomer1->myGroupSize);
     printf("\nAfter Desearilsation in Struct  %s \n", headCustomer1->Name);
     printf("\nAfter Desearilsation in Struct   groupID %d \n", headCustomer1->myGroupID);


     std::string passedValue,typeIdentifier,ackString,lockPassedValue,cvPassedValue ;

     passedValue="" ;

    cout<<"\nHi    \n"<<passedValue+"mayur"<<"\n";
    while(true);





}

*/
