#include "canfestival.h"

/* CanFestival nodes generated OD headers*/
#include "OD_0_0.h"

#define BOARD_DECL(nodename, busname, baudrate)\
    s_BOARD nodename##Board = {busname, baudrate};

static TimerCallback_t init_callback;

/* Keep track of init level to cleanup correctly */
static int init_level=0;
/* Retrieve PLC cycle time */
extern unsigned long common_ticktime__;

unsigned int masterBooted = 0;
/* Called once all NetworkEdit declares slaves have booted*/
static void Master_post_SlaveBootup(CO_Data* d, UNS8 nodeId)
{
    /* Put the master in operational mode */
    setState(d, Operational);

    /* Ask slave node to go in operational mode */
    masterSendNMTstateChange (d, 0, NMT_Start_Node);
		masterBooted=1;
}

/* Per master node slavebootup callbacks. Checks that
 * every node have booted before calling Master_post_SlaveBootup */
int TestSlave_slave_2_booted = 0;
static void TestSlave_post_SlaveBootup(CO_Data* d, UNS8 nodeId){
    switch(nodeId){
        case 8:
            TestSlave_slave_2_booted = 1;
            break;
        default:
            break;
    }
    if( TestSlave_slave_2_booted )
        Master_post_SlaveBootup(d,nodeId);
}


/* One slave node post_sync callback.
 * Used to align PLC tick-time on CANopen SYNC
 */


#define NODE_FORCE_SYNC(nodename) \
    /* Artificially force sync state to 1 so that it is not started */\
    nodename##_Data.CurrentCommunicationState.csSYNC = -1;\
    /* Force sync period to common_ticktime__ so that other node can read it*/\
    *nodename##_Data.COB_ID_Sync = 0x40000080;
    /**nodename##_Data.Sync_Cycle_Period = 100 * 1000;//100ms*/
    

#define NODE_INIT(nodename, nodeid) \
    /* Defining the node Id */\
    setNodeId(&nodename##_Data, nodeid);\
    /* init */\
    setState(&nodename##_Data, Initialisation);

#if 0
#define NODE_MASTER_INIT(nodename, nodeid) \
    NODE_FORCE_SYNC(nodename) \
    NODE_INIT(nodename, nodeid)
#endif /* if 0 end*/

#define NODE_MASTER_INIT(nodename, nodeid) \
    NODE_INIT(nodename, nodeid)


#define NODE_SLAVE_INIT(nodename, nodeid) \
    NODE_INIT(nodename, nodeid)

void InitNodes(CO_Data* d, UNS32 id)
{
	OD_0_0_Data.post_SlaveBootup = TestSlave_post_SlaveBootup;	
    NODE_MASTER_INIT(OD_0_0, 1)
}

#define NODE_STOP(nodename) \
    if(init_level-- > 0)\
    {\
        masterSendNMTstateChange(&nodename##_Data, 0, NMT_Reset_Node);\
        setState(&nodename##_Data, Stopped);\
    }

void Exit(CO_Data* d, UNS32 id)
{
    NODE_STOP(OD_0_0)
    
}


void __cleanup_0(void)
{

    /** jiangounie */
    //StopTimerLoop(&Exit);
    canClose(&OD_0_0_Data);
    //TimerCleanup();
}


void on__IB0_0_8_25088_1(CO_Data * d)
{
	int a=1;
}


#define NODE_SEND_SYNC(nodename)\
    sendSYNCMessage(&nodename##_Data);
#define NODE_PROCEED_SYNC(nodename)\
    proceedSYNC(&nodename##_Data);

/***************************  INIT  *****************************************/
int __init_0(void)
{
    // Start timer thread
    //StartTimerLoop(&InitNodes);
    InitNodes(&OD_0_0_Data, 0);    /** jiangounie */
    RegisterSetODentryCallBack(&OD_0_0_Data, 0x2208, 0x1, on__IB0_0_8_25088_1);
	
    return 0;
}

void __retrieve_0(void)
{
    //NODE_SEND_SYNC(OD_0_0);
}


void __publish_0(void)
{
    NODE_PROCEED_SYNC(OD_0_0)
}


