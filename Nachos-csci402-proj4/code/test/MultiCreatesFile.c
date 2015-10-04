/*
Broadcast signals all the waiting members on that cv. (can be 4 clients on wait, 1 signaller)
*/


void main()
{

        
		CreateLock("lock1");
        Print("\nLock by name 'lock1' Created.\n",1,1,1);
		CreateLock("lock2");
        Print("\nLock by name 'lock2' Created.\n",1,1,1);
        CreateCV("cv1");	
        Print("\nCV by name 'cv1' Created.\n",1,1,1);
        CreateCV("cv2");	
        Print("\nCV by name 'cv2' Created.\n",1,1,1);
        CreateMV("mv1",5);
        Print("\nMV by name 'mv1' Created.\n",1,1,1);        
		CreateMV("mv2",4);
        Print("\nMV by name 'mv1' Created.\n",1,1,1);

		Exit(0);
}
