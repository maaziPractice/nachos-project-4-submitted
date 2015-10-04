/*      testCase_18a.c

        The Second Process.

*/

#include "syscall.h"

int a1=0, b1=0, c1=0;

void add1()
{
        a1=1;
        b1=2;
        c1=3;

        Print("\n add1() Has Been Forked in testCase_18a. \n\0",1,1,1);

        Exit(0);
}

void add2()
{
        a1=1;
        b1=2;
        c1=0;

        Print("\n add2() Has Been Forked in testCase_18a. \n\0",1,1,1);

        Exit(0);
}

void myFunction1()
{
        Print("\n myFunction1() Has Been Forked in testCase_18a. \n\0",1,1,1);

        Fork(add1);    
   
    if(a1+b1 == c1)
        Print("\n myFunction1() in Process testCase_18a: Sum Is Correct. \n\0",1,1,1);
    else
        Print("\n myFunction1() in Process testCase_18a: Sum Is Not Correct. \n\0",1,1,1);
    
    Exit(0);
} 

void myFunction2()
{
        Print("\n myFunction2() Has Been Forked in testCase_18a. \n\0",1,1,1);

        Fork(add2);

    if(a1+b1 == c1)
        Print("\n myFunction2() in Process testCase_18a: Sum Is Correct. \n\0",1,1,1);
    else
        Print("\n myFunction2() in Process testCase_18a: Sum Is Not Correct. \n\0",1,1,1);
    
    Exit(0);
} 

int main()
{
        Print("\n Process (File) testCase_18a.c Has Been Executed. \n\0",1,1,1);
        
        Fork(myFunction1);
        Fork(myFunction2);
}