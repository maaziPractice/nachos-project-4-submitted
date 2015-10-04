/* halt.c
 *	Simple program to test whether running a user program works.
 *	
 *	Just do a "syscall" that shuts down the OS.
 *
 * 	NOTE: for some reason, user programs with global data structures 
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as 
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "syscall.h"
int a[2];
int b, c;
void add111()
{
   int abc[50];
	Write("\nHALT 2: Add111 Function\n",22,ConsoleOutput);
	Exit(0);
}
void add()
{
   int abc[50];
	Write("\nHALT 2: Add Function\n",22,ConsoleOutput);
	Fork(add111);
	Exit(0);
}
void myFunction1()
{
	int a1=10; 
	int b1;
	int c1=125;
	int arr[40];
	a1=123;
	b1=2;
	
    Write("\nHALT 2: myFunction1\n",21,ConsoleOutput);
   
    Fork(add);    
   Exec("../test/sort",12);
    if(a1+b1 == c1)
    {
    	Write("\nHALT 2: myFunction1: SumIsCorrect\n",35,ConsoleOutput);
    }
    else
    {
    	Write("\nHALT 2: myFunction1: SumIs Not Correct\n",40,ConsoleOutput);
    }
    
    
    Exit(0);
} 
void myFunction2()
{
	int a1; 
	int b1;
	int c1=200;
	int arr[40];
	a1=123;
	b1=77;

	
   Write("\nHALT 2: myFunction2\n",21,ConsoleOutput);
   
   Fork(add);
    
    if(a1+b1 == c1)
    {
    	Write("\nHALT 2: myFunction2: SumIsCorrect\n",35,ConsoleOutput);
    }
    else
    {
    	Write("\nHALT 2: myFunction2: SumIs Not Correct\n",40,ConsoleOutput);
    }
    
    
     Exit(0);
} 

int
main()
{ 

int i1=-1,i2=-1;
int cv1=-1; 
int arr[6];

Write("\nHalt2: Your Exec is running\n",29,ConsoleOutput);
/*
Exec("../test/sort",12);
Exec("../test/sort",12);
Exec("../test/sort",12);
Exec("../test/sort",12);
Exec("../test/sort",12);
Exec("../test/sort",12);
Exec("../test/sort",12);
Exec("../test/sort",12);


*/

Fork(myFunction1);
Fork(myFunction2);  


/*Write("\nI am in Halt\n",14,ConsoleOutput);*/

/* 
   Halt();
char* lockName="FirstLock";
char* cvName="FirstCV";
    
    
    cv1=CreateCV(cvName,7);
    i1=CreateLock(lockName,7);
   i2=CreateLock(lockName,9); 
     capture the return value of acquire & release
    Acquire(i1);
    Wait(cv1,i1);
    Release(i1);
    DeleteLock(i1);
	Acquire(i1);
    Release(i1);
    
    Write("I2222\n",6,ConsoleOutput);
    
    Acquire(i2);
    
    Release(i2);
    DeleteLock(i2);
	Acquire(i2);
    Release(i2); 
    
    

     */
}
