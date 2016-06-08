#include "mb.h"
#include "mbutils.h"
	
#define REG_INPUT_START 1
#define REG_INPUT_NREGS 8

#define REG_HOLDING_START 1
#define REG_HOLDING_NREGS 8

#define REG_COILS_START 1
#define REG_COILS_SIZE 8

#define REG_DISCRETE_START 1
#define REG_DISCRETE_SIZE 8

USHORT usRegInputBuf[REG_HOLDING_NREGS]={0x147b,0x400e,0x1eb8,0x4055,0x147b,0x408e,0x0270,0x0180};
USHORT usRegHoldingBuf[REG_HOLDING_NREGS]={0x147b,0x3f8e,0x147b,0x400e,0x1eb8,0x4055,0x147b,0x408e}; 
UCHAR ucRegCoilsBuf[REG_COILS_SIZE]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
UCHAR ucRegDiscreteBuf[REG_DISCRETE_SIZE]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};


//读数字寄存器 功能码0x04
eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
  eMBErrorCode    eStatus = MB_ENOERR;
	int             iRegIndex;
	
    if( ( usAddress >= REG_INPUT_START )&& ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress - REG_INPUT_START );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;

}

// 寄存器的读写函数 支持的命令为读 0x03 和写0x06
eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;	

    if ((usAddress >= REG_HOLDING_START ) && ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ))
    {
        iRegIndex = ( int )( usAddress - REG_HOLDING_START );
        switch ( eMode )
        {
        case MB_REG_READ:
            while( usNRegs > 0 )
            {
    //                *PRT++ = __REV16(usRegHoldingBuf[iRegIndex++]); //数据序转 REV16.W
                *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] >> 8 );
                *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] & 0xFF );
                iRegIndex++;
                usNRegs--;
            }
            break;

        case MB_REG_WRITE:
            while( usNRegs > 0 )
            {
    //                usRegHoldingBuf[iRegIndex++] = __REV16(*PRT++); //数据序转 REV16.W
                usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
                usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
                iRegIndex++;
                usNRegs--;
            }
            break;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

//读/写开关寄存器  0x01  x05
eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
    eMBErrorCode eStatus = MB_ENOERR;
	  //寄存器个数
    USHORT iNCoils = usNCoils;
	  //寄存器偏移量
    USHORT usBitOffset;
	
	
    //检查寄存器是否在指定范围内
    if( (usAddress >= REG_COILS_START ) &&
    ( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
    {
    //计算寄存器偏移量
    usBitOffset = ( usAddress - REG_COILS_START );
    switch ( eMode )
    {
    //读操作
    case MB_REG_READ:
        while( iNCoils > 0 )
        {
            *pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,
            ( UCHAR )( iNCoils > 8 ? 8 : iNCoils ) );
            iNCoils -= 8;
            usBitOffset += 8;
        }
    break;
    
    //写操作
    case MB_REG_WRITE:
        while( iNCoils > 0 )
        {
            xMBUtilSetBits( ucRegCoilsBuf, usBitOffset,
            ( iNCoils > 8 ? 8 : iNCoils ),
            *pucRegBuffer++ );
            iNCoils -= 8;
        }
    break;
    }
    
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
    
}

//读开关寄存器 0x02
eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
	eMBErrorCode eStatus = MB_ENOERR;
    //操作寄存器个数
    USHORT iNDiscrete = usNDiscrete;
    //偏移量
    USHORT usBitOffset;
	
    //判断寄存器时候再制定范围内
    if( (usAddress >= REG_DISCRETE_START ) &&
    ( usAddress + usNDiscrete <= REG_DISCRETE_START + REG_DISCRETE_SIZE ) )
    {
        //获得偏移量
        usBitOffset = ( usAddress - REG_DISCRETE_START );
        
        while( iNDiscrete > 0 )
        {
            *pucRegBuffer++ = xMBUtilGetBits( ucRegDiscreteBuf, usBitOffset,
            ( iNDiscrete > 8 ? 8 : iNDiscrete ) );
            iNDiscrete -= 8;
            usBitOffset += 8;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;  
  
}

/**
  * @}
  */


/*******************文件结尾**************************************************/
