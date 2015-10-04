
enum LocationOfPage{NotOnDISK,EXECUTABLE,SWAP_FILE};

class EPTEntry : public TranslationEntry  {

public:
LocationOfPage locationOfPage;
int byteOffSet;
		EPTEntry()
		{
		valid=FALSE;
		physicalPage=-1;
		dirty=FALSE;
		use=FALSE;
		readOnly = FALSE;
		locationOfPage = NotOnDISK;
		byteOffSet = -1;
		//cout<<"\nin ept entry constructor\n";
		}

} ;
