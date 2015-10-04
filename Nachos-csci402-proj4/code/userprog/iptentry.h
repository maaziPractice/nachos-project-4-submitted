#include "translate.h"


class IPTEntry : public TranslationEntry  {

	public:

	AddrSpace* addrSpace;
	int processID;
	IPTEntry()
	{
		valid=false;
		physicalPage=-1;
		use=false;
		addrSpace=NULL;
		dirty=false;
		processID=-1000;
	}

} ;
