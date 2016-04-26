#include "applicfg.h"
#include "data.h"
#include "can_driver.h"

#define MAX_NB_CAN_PORTS 16

/** CAN port structure */
typedef struct {
  char used;  /**< flag indicating CAN port usage, will be used to abort Receiver task*/
  CO_Data* d; /**< CAN object data*/
} CANPort;

CANPort canports[MAX_NB_CAN_PORTS] = {{0,},{0,},{0,},{0,},{0,},{0,},{0,},{0,},{0,},{0,},{0,},{0,},{0,},{0,},{0,},{0,}};

/* board参数暂时废弃不使用 */
CAN_PORT canOpen(s_BOARD *board, CO_Data * d)
{
    int i;
	for(i=0; i < MAX_NB_CAN_PORTS; i++)
	{
		if(!canports[i].used)
		break;
	}
	
    canports[i].used = 1;
    canports[i].d = d;
    d->canHandle = (CAN_PORT)&canports[i];

    return (CAN_PORT)&canports[i];
}

int canClose(CO_Data * d)
{
	UNS8 res;

	((CANPort*)d->canHandle)->used = 0;
	CANPort* tmp = (CANPort*)d->canHandle;

	d->canHandle = NULL;

	return res;
}

UNS8 canSend(CAN_PORT port, Message *m)
{
	if (port)
	{
		UNS8 res;
		res = can_tx(m);
		return res; // OK
	}
	return 1; // NOT OK
}



