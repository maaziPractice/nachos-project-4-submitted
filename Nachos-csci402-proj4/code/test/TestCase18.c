/*      testCase_18.c

        Program Which is The First Process Executing Two More Processes Within Itself.

*/

#include "syscall.h"

int main()
{
        Print("\n Exec-ing both testCase_18a & testCase_18a \n",1,1,1);
        Exec("../test/testCase_18a",20);
        Exec("../test/testCase_18b",20);
        Exit(0);    
}