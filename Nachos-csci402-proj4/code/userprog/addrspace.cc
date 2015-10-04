// addrspace.cc 
//	Routines to manage address spaces (executing user programs).
//
//	In order to run a user program, you must:
//
//	1. link with the -N -T 0 option 
//	2. run coff2noff to convert the object file to Nachos format
//		(Nachos object code format is essentially just a simpler
//		version of the UNIX executable object code format)
//	3. load the NOFF file into the Nachos file system
//		(if you haven't implemented the file system yet, you
//		don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "noff.h"
#include "table.h"
#include "synch.h"

extern "C" { int bzero(char *, int); };

Table::Table(int s) : map(s), table(0), lock(0), size(s) {
    table = new void *[size];
    lock = new Lock("TableLock");
}

Table::~Table() {
    if (table) {
	delete table;
	table = 0;
    }
    if (lock) {
	delete lock;
	lock = 0;
    }
}

void *Table::Get(int i) {
    // Return the element associated with the given if, or 0 if
    // there is none.

    return (i >=0 && i < size && map.Test(i)) ? table[i] : 0;
}

int Table::Put(void *f) {
    // Put the element in the table and return the slot it used.  Use a
    // lock so 2 files don't get the same space.
    int i;	// to find the next slot

    lock->Acquire();
    i = map.Find();
    lock->Release();
    if ( i != -1)
	table[i] = f;
    return i;
}

void *Table::Remove(int i) {
    // Remove the element associated with identifier i from the table,
    // and return it.

    void *f =0;

    if ( i >= 0 && i < size ) {
	lock->Acquire();
	if ( map.Test(i) ) {
	    map.Clear(i);
	    f = table[i];
	    table[i] = 0;
	}
	lock->Release();
    }
    return f;
}

//----------------------------------------------------------------------
// SwapHeader
// 	Do little endian to big endian conversion on the bytes in the 
//	object file header, in case the file was generated on a little
//	endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void 
SwapHeader (NoffHeader *noffH)
{
	noffH->noffMagic = WordToHost(noffH->noffMagic);
	noffH->code.size = WordToHost(noffH->code.size);
	noffH->code.virtualAddr = WordToHost(noffH->code.virtualAddr);
	noffH->code.inFileAddr = WordToHost(noffH->code.inFileAddr);
	noffH->initData.size = WordToHost(noffH->initData.size);
	noffH->initData.virtualAddr = WordToHost(noffH->initData.virtualAddr);
	noffH->initData.inFileAddr = WordToHost(noffH->initData.inFileAddr);
	noffH->uninitData.size = WordToHost(noffH->uninitData.size);
	noffH->uninitData.virtualAddr = WordToHost(noffH->uninitData.virtualAddr);
	noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

//----------------------------------------------------------------------
// AddrSpace::AddrSpace
// 	Create an address space to run a user program.
//	Load the program from a file "executable", and set everything
//	up so that we can start executing user instructions.
//
//	Assumes that the object code file is in NOFF format.
//
//	"executable" is the file containing the object code to load into memory
//
//      It's possible to fail to fully construct the address space for
//      several reasons, including being unable to allocate memory,
//      and being unable to read key parts of the executable.
//      Incompletely consretucted address spaces have the member
//      constructed set to false.
//----------------------------------------------------------------------

AddrSpace::AddrSpace(OpenFile *executable) : fileTable(MaxOpenFiles) {
	//printf("\nI am in AddrSpace\n");
	noOfThreads=1;	
	
    NoffHeader noffH;
    unsigned int i, size;

    // Don't allocate the input or output to disk files
    fileTable.Put(0);
    fileTable.Put(0);

    executable->ReadAt((char *)&noffH, sizeof(noffH), 0);

	//printf("\nafter read at        I am in AddrSpace\n");
    if ((noffH.noffMagic != NOFFMAGIC) && 
		(WordToHost(noffH.noffMagic) == NOFFMAGIC))
    	SwapHeader(&noffH);
    ASSERT(noffH.noffMagic == NOFFMAGIC);
   
   
					    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size ;
					    
						numPages = divRoundUp(size, PageSize) + divRoundUp(UserStackSize,PageSize);
	/*					printf("\nFor Main Thread:Initial Size Code+Int+Uninit = %d\n",size);
						printf("\nFor Main Thread:Initial Value of numPage = %d\n",numPages);
					    printf("\nFor Main Thread:Initial Size Code+Int+Uninit+MainStack = %d\n",numPages*PageSize);   */
						
						stackPage=divRoundUp(size, PageSize);
																	// we need to increase the size
											// to leave room for the stack
					    size = numPages * PageSize;
					    //printf("NumPhysPages %d ",NumPhysPages);
					    ASSERT(numPages <= NumPhysPages);		// check we're not trying
											// to run anything too big --
											// at least until we have
											// virtual memory
					
					    DEBUG('a', "Initializing address space, num pages %d, size %d\n", 
										numPages, size);
					// first, set up the translation 
			   		pageTable = new TranslationEntry[numPages+(MAX_THREADS-1)*8];
			//	pageTable = new TranslationEntry[numPages];
					    
					//    bzero(machine->mainMemory, size);
					
			myBitmapLock->Acquire();			
								//currentThread->stackPageOfBottom=numPages;
								
								//printf("\nAfter Acquiring Bitmap\n");
						
							    for (i = 0; i < numPages; i++) {
							
									int unusedPageNum = myBitmap->Find();				// Finding an unused page
									//printf("\nAfter Acquiring Bitmap, Unused page num=%d\n",unusedPageNum);
									pageTable[i].virtualPage = i;
									pageTable[i].physicalPage = unusedPageNum;
								//	printf("\nPhysical Page Allocated is %d \n",unusedPageNum);
									pageTable[i].valid = TRUE;
									pageTable[i].use = FALSE;
									pageTable[i].dirty = FALSE;
									pageTable[i].readOnly = FALSE;  // if the code segment was entirely on 
													// a separate page, we could set its 
													// pages to be read-only
								}
						//printf("\nAfter for loop\n");
	myBitmapLock->Release();

  /*
int totalSizeInBytes=noffH.code.size+noffH.initData.size;
int totalNumFullPages=totalSizeInBytes / PageSize;

  for (i = 0; i < totalNumFullPages; i++) {

	        executable->ReadAt(&(machine->mainMemory[pageTable[i].physicalPage*PageSize]), PageSize, noffH.code.inFileAddr+(i*PageSize));
	    }
  if((totalSizeInBytes % PageSize) > 0)
	{
			executable->ReadAt(&(machine->mainMemory[pageTable[i].physicalPage*PageSize]), (totalSizeInBytes % PageSize), noffH.code.inFileAddr+((totalNumFullPages)*PageSize));
	}
	   */
	   
  int totalSizeInBytes=noffH.code.size+noffH.initData.size;
  int totalNumFullPages=divRoundUp(totalSizeInBytes,PageSize);

  for (i = 0; i < totalNumFullPages; i++) 
	  {

	        executable->ReadAt(&(machine->mainMemory[pageTable[i].physicalPage*PageSize]), PageSize, noffH.code.inFileAddr+(i*PageSize));
	  }
	   
	   
	//printf("\nI am done with reading programme in RAM n");

}

//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
//
// 	Dealloate an address space.  release pages, page tables, files
// 	and file tables
//----------------------------------------------------------------------

AddrSpace::~AddrSpace()
{
    delete pageTable;
}

//----------------------------------------------------------------------
// AddrSpace::InitRegisters
// 	Set the initial values for the user-level register set.
//
// 	We write these directly into the "machine" registers, so
//	that we can immediately jump to user code.  Note that these
//	will be saved/restored into the currentThread->userRegisters
//	when this thread is context switched out.
//----------------------------------------------------------------------

void
AddrSpace::InitRegisters()
{
    int i;

    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, 0);	

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, 4);

   // Set the stack register to the end of the address space, where we
   // allocated the stack; but subtract off a bit, to make sure we don't
   // accidentally reference off the end!
  // printf("\nI am in InitRegisters StackReg For %d\n", numPages * PageSize - 16);
    machine->WriteRegister(StackReg, numPages * PageSize - 16);
    DEBUG('a', "Initializing stack register to %x\n", numPages * PageSize - 16);
}

//----------------------------------------------------------------------
// AddrSpace::SaveState
// 	On a context switch, save any machine state, specific
//	to this address space, that needs saving.
//
//	For now, nothing!
//----------------------------------------------------------------------

void AddrSpace::SaveState() 
{

}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
// 	On a context switch, restore the machine state so that
//	this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void AddrSpace::RestoreState() 
{
    machine->pageTable = pageTable;
    machine->pageTableSize = numPages;
}

void AddrSpace::StackToThread()
{
	/*
	TranslationEntry *newPageTable=new TranlationEntry[numPages+8];
	for(unsigned int i=0;i<numPages;i++)
		{
		newPageTable[i].virtualPage=pageTable[i].virtualPage;
		newPageTable[i].physicalPage=pageTable[i].physicalPage;
		newPageTable[i].valid=pageTable[i+numPages].valid;
		newPageTable[i].use=pageTable[i+numPages].use;
		newPageTable[i+numPages].dirty=pageTable[i+numPages].dirty;
		newPageTable[i+numPages].readOnly=pageTable[i+numPages].readOnly;
		}	
	
	myBitmapLock->Acquire();
				for (int i = 0; i < 8; i++) {		
					int unusedPageNum = myBitmap->Find();				// Finding an unused page
					//printf("\nAfter Acquiring Bitmap, Unused page num=%d\n",unusedPageNum);
					newPageTable[i+numPages].virtualPage = i;
					newPageTable[i+numPages].physicalPage = unusedPageNum;
				//	printf("\nPhysical Page Allocated is %d \n",unusedPageNum);
					newPageTable[i+numPages].valid = TRUE;
					newPageTable[i+numPages].use = FALSE;
					newPageTable[i+numPages].dirty = FALSE;
					newPageTable[i+numPages].readOnly = FALSE;  // if the code segment was entirely on 
									// a separate page, we could set its 
									// pages to be read-only
				}
				
				TranslationEntry * oldPageTable=pageTable;
				pageTable=newPageTable;
				delete oldPageTable;				 
				numPages=numPages+8;	
					
	currentThread->stackPageOfBottom=numPages;
	currentThread->startingAddressofStack = ((currentThread->space->numPages) * PageSize) - 16;
	
	myBitmapLock->Release();
	*/
	
	
	myBitmapLock->Acquire();
				for (int i = 0; i < 8; i++) {
			
					int unusedPageNum = myBitmap->Find();				// Finding an unused page
					//printf("\nAfter Acquiring Bitmap, Unused page num=%d\n",unusedPageNum);
					pageTable[i+numPages].virtualPage = i;
					pageTable[i+numPages].physicalPage = unusedPageNum;
				//	printf("\nPhysical Page Allocated is %d \n",unusedPageNum);
					pageTable[i+numPages].valid = TRUE;
					pageTable[i+numPages].use = FALSE;
					pageTable[i+numPages].dirty = FALSE;
					pageTable[i+numPages].readOnly = FALSE;  // if the code segment was entirely on 
									// a separate page, we could set its 
									// pages to be read-only
				}
				
				numPages=numPages+8;
	//printf("\nmy Starting Stack Page Number: Virtual One is %d\n",numPages);	
	
	currentThread->stackPageOfBottom=numPages;
	currentThread->startingAddressofStack = ((currentThread->space->numPages) * PageSize) - 16;
	myBitmapLock->Release();
  
}

void AddrSpace::ClearAddressSpacePages()
{
	myBitmapLock->Acquire();	    	
		    //	printf("\nClearAddressSpacePages: NumPages value is %d\n",currentThread->space->numPages);
				    	for(unsigned int i=0;i<currentThread->space->numPages ; i++)
				    	{
				    		if(currentThread->space->pageTable[i].valid==true)
				    			{
				    			currentThread->space->pageTable[i].valid=false;
				    			myBitmap->Clear(currentThread->space->pageTable[i].physicalPage);
				//    			printf("\nPhysical Page Freed is %d \n",currentThread->space->pageTable[i].physicalPage);
				    			}	    		
				    	}
		    	
	myBitmapLock->Release();
	//printf("\nClearAddressSpacePages: After releasing Bitmap lock\n");

}


void AddrSpace::ClearThreadStack()
{	
	int stackPageOfBottom=currentThread->stackPageOfBottom;
	//printf("\nIn ClearThreadStack, with PID as %d\n",currentThread->space->myPID);
	myBitmapLock->Acquire();	    	
		    	
				    	for(unsigned int i=0;i<8; i++)
				    	{
				    		stackPageOfBottom--;
				    		if(currentThread->space->pageTable[stackPageOfBottom].valid==true)
				    			{
				    			currentThread->space->pageTable[stackPageOfBottom].valid=false;
				    			myBitmap->Clear(currentThread->space->pageTable[stackPageOfBottom].physicalPage);
				   // 			printf("\nPhysical Page Freed is %d \n",currentThread->space->pageTable[stackPageOfBottom].physicalPage);
				    			}	    		
				    	}
		    	
    myBitmapLock->Release();
   // printf("\nAt the end of ClearThreadStack, with PID as %d\n",currentThread->space->myPID);
}

unsigned int AddrSpace::GetNumPages()
{
return numPages;

}
