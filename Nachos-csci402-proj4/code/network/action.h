#include "system.h"
#include <map>
#define MAX_RQID 1999999999
#define SSMailBox 1
#define SCMailBox 0


extern Lock* PendingQLock;
extern Lock* lockTableLock;
extern Lock* CVTableLock;
extern Lock* MVTableLock;
//extern List * PendingQ;
extern Lock* RqIDBitMapLock;
extern BitMap* RqIDBitMap;

 /*
 RqIDBitMapLock=new Lock("RqIDBitMapLock");
 RqIDBitMap=new BitMap(MAX_RQID);
*/

 //enum EntityType{LOCKs,CVs,MVs};
 enum OpCode
 {
	 DYHC_LOCKs=0,
	 DYHC_CVs=1,
	 DYHC_MVs=2,

	 DYHA_LOCKs=3,
	 DYHR_LOCKs=4,

	 DYHW_CVs=5,
	 DYHS_CVs=6,
	 DYHR_LOCKs_WAIT=7,
	 DYHA_LOCKs_SIG=8,

	 //DYH_MVs=9,
	 DYHG_MVs=10,
	 DYHS_MVs=11,

	 DYH_LOCKs_OwnerShip=12,
	 DYHB_CVs=13,
	 DYHA_LOCKs_BROAD=14
 };

struct DYHRq
{
	unsigned int timestamp;
	char nameOfEntity[25];
	short int opcode;
	bool DIHEntity; // destination server replies like do I have it??
	bool ReqRep;
	short int CMachID;
	short int CmailBOX;
};

class PendingQElement
{
public:
	List* clientInfoQ;
	DYHRq* myDYHRq;
    string origCliMsg; // can be use for fwding request to apt server
    bool exactOneYes;
    int ownerServer;
    int totalCorreResponses;
    int cvIndex;
    List* pendingDYHCreateMsgs;
	int fMachID;
	int fMailBoxNum;

    PendingQElement();

};


struct DYHRp
{
	int RqIDofDYHRq;
	char nameOfEntity[25];
	bool DIHEntity;
	short int opcode;
};

extern map< string,PendingQElement* > PendingQ;   //PERROR you may declre it void* to avoid getting called destructors in erase
extern map<string,PendingQElement*>::iterator PendingQiterator;

extern void StructToString(char* DYHRqStructPtr,char* destbuf);
extern void StringToStruct(char* DYHRqStructPtr,char* destbuf);
extern string GenerateKey(string nameOfEntityPtr,OpCode opcode);
extern void SendAsIfFromClient(PendingQElement* pendQE);
extern void SendErrorToClients(PendingQElement* pendQE);
extern void SendGetMVErrorToClients(PendingQElement* pendQE);

extern int lookUpforLock(string lockName);
extern int lookUpforCV(string cvName);
extern int lookUpforMVCreate(string mvName);
extern int lookUpforMV(string passedValue);
extern void  funcSetMV(int mvIndex, int mvIndexArray, int mvValueAssign, ClientInfo *addressInformation);

extern void SendDYH(DYHRq* myDYHRq);
extern void ReplyToDYH(int farSerMachiID,DYHRq* myDYHRq);

extern void funcSend(int inPktHdrFromVal, int inMailHdrFromVal, string ackString);
extern int funcCreateCV(string passedValue, ClientInfo *addressInformation);
extern int funcCreateLock(string passedValue, ClientInfo *addressInformation);
extern int funcAcquire(string lockToBeAcquiredName, ClientInfo *addressInformation);
extern int funcRelease(string lockToBeReleasedName, ClientInfo *addressInformation);
extern int funcWait(int lockIndex, int cvIndex, ClientInfo *addressInformation);
extern void initialiseDSS();
extern void SendAsIfFromSpecClient(ClientInfo* clientInfo,int farServID,char* opcode, char* entityName);
extern int funcSignal(int lockIndex, int cvIndex, ClientInfo *addressInformation);
extern int funcBroadcast(int lockIndex, int cvIndex, ClientInfo *addressInformation);
/***************************************************************/
extern void AddToPendingQ(string passedValue,char* buffer,short int opcode,ClientInfo* addressInformation);
extern void CurrentRequestServent();

extern void ServeReqeusts(int farSerMachiID,DYHRq* msgObj);
extern void UpdatePendQ(int farSerMachiID,DYHRq* msgObj);
extern void ReadSSMailBOX();
extern void ServePendingQ();
extern void ServerToServer();
extern void HandleCreateLock(PendingQElement* pendQE);
extern void HandleCreateCV(PendingQElement* pendQE);
extern void HandleCreateMV(PendingQElement* pendQE);
extern void SendCreateMessageToClients(PendingQElement* pendQE, string ackString);
extern int funcCreateMV(string passedValue, int mvArraySizeInt, ClientInfo *addressInformation);
/***************************************************************************************************/
extern void myServerFunc1();
