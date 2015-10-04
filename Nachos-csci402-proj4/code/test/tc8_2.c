/*
Broadcast signals all the waiting members on that cv. (can be 4 clients on wait, 1 signaller)
*/

#include "syscall.h"
#define MAX_TT 3			/* Maximum  Ticket Takers */
#define MAX_CC 5			/* Maximum Concession Clerks */
#define MAX_TC 5			/* Maximum Ticket Clerks */
#define MAX_GRP 30
#define PRINTMETOO *65536+

void main()
{


	int getMvValue=-5;

/*	CreateCV("cv1");
	CreateLock("InitLock");
	CreateLock("InitLock1");

	Acquire("InitLock");
	
	Wait("cv1","InitLock");
	
	Release("InitLock");
*/

CreateMV("MyMV",3);
	Print("\n TC11_1:: Setting value for MV name 'MyMV' at its Array Index '0'\n\0",1,1,1);
	SetMV("MyMV", 0, -1);
	SetMV("MyMV", 2, 55);

	getMvValue = GetMV("MyMV", 0);
	Print("\n TC11_1:: GetMV gets: '%d' for 'MyMV', Array Index '0'. \n\0",getMvValue,1,1);

	getMvValue = GetMV("MyMV", 1);
	Print("\n TC11_1:: GetMV gets: '%d' for 'MyMV', Array Index '1'. \n\0",getMvValue,1,1);

	getMvValue = GetMV("MyMV", 2);
	Print("\n TC11_1:: GetMV gets: '%d' for 'MyMV', Array Index '2'. \n\0",getMvValue,1,1);


	Exit(0);
}
