#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "canfestival.h"
#include "OD_0_0.h"
#include "iec_types.h"
/*
 * Prototypes of functions provided by generated C softPLC
 **/
void config_run__(unsigned long tick);
void config_init__(void);
/*
 * Prototypes of functions provided by generated target C code
 * */

void __init_debug(void);
void __cleanup_debug(void);
/*void __retrieve_debug(void);*/
void __publish_debug(void);
//#endif
/*
 *  Variables used by generated C softPLC and plugins
 **/
IEC_TIME __CURRENT_TIME;
IEC_BOOL __DEBUG = 0;
//#endif
unsigned long __tick = 0;
/* Help to quit cleanly when init fail at a certain level */
static int init_level = 0;

/*
 * Prototypes of functions exported by plugins
 **/
int __init_0();
void __cleanup_0(void);
void __retrieve_0(void);
void __publish_0(void);

static char busname[8];
static char baudrate[32];
static s_BOARD Knm_Board = {busname, baudrate};

static RT_TASK init_task;

static void init_process(void *arg)
{
    __init();    /** 初始化。里面含有can报文发送动作，需要在实时环境中进行，故建立一个任务 */

#if 0
    while (1)
    {
        rt_task_wait_period(NULL);
        EnterMutex();
        __retrieve_0();
    config_run__(__tick);        
    __publish_debug();
        __publish_0();
        LeaveMutex();
    }
#endif /* if 0 end*/
}


/*
 * Initialize variables according to PLC's default values,
 * and then init plugins with that values
 **/
int __init()
{
    int res = 0;
    init_level = 0;
    config_init__();
    __init_debug();
    init_level=1; if((res = __init_0())){return res;}
    return res;
}

int main(int argc, char** argv)
{
    char* LibraryPath="./lib/libcanfestival_can_socket.so";

    if (argc < 2)
    {
        printf("you should do like this : ./knm rtcan0 500K\n");
		exit(1);
    }

    TimerInit();

    LoadCanDriver(LibraryPath);

    snprintf(busname, sizeof(busname), "%s", argv[1]);
    snprintf(baudrate, sizeof(baudrate), "%s", argv[2]);

    if(0 == canOpen(&Knm_Board, &OD_0_0_Data))
    {
        goto init_failture;
    }

    /* This value must range from [0 .. 99] (inclusive) where 0 is the lowest effective priority */
    rt_task_create(&init_task, "init-task", 0, 99, 0);

    rt_task_start(&init_task, init_process, NULL);

    while (1);

init_failture:
    printf("init failture\n");
    TimerCleanup();
    return 0;

}

void plc_run(void)
{
    /* processed here when we meet 0x80 */
    
}



