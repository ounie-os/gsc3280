#ifndef SCRIPT_H
#define SCRIPT_H

#define OS_UNIX

#ifdef OS_UNIX
#include <sys/mman.h>
#include <stdlib.h>  
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <asm/ioctls.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#endif

#define SHM_MODE (SHM_R | SHM_W | IPC_CREAT) 

#ifdef OS_UNIX
#define MAX_NUM             4000
#endif

#define MAX_SYSITEM         200
#define MAX_STRUCT          5
#define MAX_STRUCT_DOWN     5
#define MAX_STRUCT_UP       5

#ifdef OS_UNIX
#define SHMDBKEYRTRAM_RT    1829503351  //811047
#define STATION_SIZE        70000
#endif

typedef struct _StructData
{
    double dValue ;
    char chState ;              //ʵʱ��״ֵ̬
    char    bAlarm ;            
    char bChangeState ;
    char bVisible;
}StructData;

typedef struct _StructKcData
{
    int kcNo;
    char dataKC[200];
}StructKcData;

//��̨�����ʵʱ���ݿ�
typedef struct _StructStation    
{
    int iVersion;
    StructData  DataValue[ MAX_NUM ];           
    int DataKCFlag;                             //���������ʶ
    StructKcData DataKC;                        //�����ṹ
    int StructNum;                              //�澯�ṹ��ʶ
    char chStruct[MAX_STRUCT][200];             //�澯�ṹ��
    int StructUpNum ;                           //�ϴ��ṹ��ʶ
    char chStructUp[MAX_STRUCT_UP][200] ;       //�ϴ��ṹ��
    int StructDownNum;                          //�´��ṹ��ʶ
    int StructDownProg;                         //����id
    char chStructDown[MAX_STRUCT_DOWN][200];    //�´��ṹ��
}StructStation;

    
double * pSysItem;
StructStation * pStation ;
char bEmbed;
int OpenRamRt();//�򿪹���
double GetItemValue( int iStationid,  int id ) ;
char GetItemChangeState( int iStationid,  int id ) ;
void  SetItemValue( int iStationid ,  int id , double dValue ) ;
StructKcData * GetKcData(int iStationid);
int GetKcFlag(int iStationid);
StructData* GetItem(int iStationid,int id);
    
double GetSysItem( int id );
char * GetStruct(int iNum);
int GetStructNum();
char * GetStructDown(int iNum);
int GetStructDownNum();
int GetStructDownProgId();
int GetStructUpNum();
char * GetStructUp(int iNum);

void  SetDataState(int iStationid, int id , char bAlarm ,  char bChangeState);
void  SetSysItem( int id , double dValue);

void  SetStruct(int iNum, char *chMsg);
void  SetStructNum(int iStructNum);
void  SetStructDown(int iNum, char *chMsg);
void  SetStructDownNum(int iProg ,int iNum);
void  SetStructUpNum(int iStructNum);
void  SetStructUp(int iNum,char *chMsg);
void  SetKcFlag(int iStationid,int flag);
void  SetKcData(int iStationid, int no,char *data);
void  SetKcClear(int iStationid,int flag);
void  waitForMillisec(int millisec);

#endif
