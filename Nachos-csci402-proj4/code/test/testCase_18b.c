/*      testCase_18b.c

        The Third Process.

*/

#include "syscall.h"

int a1=0, b1=0, c1=0;

void subtract1()
{
        a1=5;
        b1=2;
        c1=3;

        Print("\n subtract1() Has Been Forked in testCase_18b. \n\0",1,1,1);

        Exit(0);
}

void subtract2()
{
        a1=5;
        b1=2;
        c1=0;

        Print("\n subtract2() Has Been Forked in testCase_18b. \n\0",1,1,1);

        Exit(0);
}

void myFunc1()
{
        Print("\n myFunc1() Has Been Forked in testCase_18b. \n\0",1,1,1);

        Fork(subtract1);    
   
    if(a1-b1 == c1)
        Print("\n myFunc1() in Process testCase_18b: Subtraction Is Correct. \n\0",1,1,1);
    else
        Print("\n myFunc1() in Process testCase_18b: Subtraction Is Not Correct. \n\0",1,1,1);
    
    Exit(0);
} 

void myFunc2()
{
        Print("\n myFunc2() Has Been Forked in testCase_18b. \n\0",1,1,1);

        Fork(subtract2);

    if(a1-b1 == c1)
        Print("\n myFunc2() in Process testCase_18b: Subtraction Is Correct. \n\0",1,1,1);
    else
        Print("\n myFunc2() in Process testCase_18a: Subtraction Is Not Correct. \n\0",1,1,1);
    
    Exit(0);
} 

int main()
{
        Print("\n Process (File) testCase_18b.c Has Been Executed. \n\0",1,1,1);
        
        Fork(myFunc1);
        Fork(myFunc2);
}