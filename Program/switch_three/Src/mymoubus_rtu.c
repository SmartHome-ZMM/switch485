#include "mymoubus_rtu.h"
#ifdef CONFIG_ZIGBEE 

#include "../BSP/port.h"
#include "../BSP/dco.h"
#include "../DRV/drv_board.h"
#include "../METER/meter_register.h"
/* ----------------------- Platform includes --------------------------------*/
#include "../BSP/port.h"
#include "../BSP/dco.h"
#include "../BSP/bsp_gpio.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "../MODBUS/include/mb.h"
#include "../MODBUS/include/mbport.h"
#include "../MODBUS/rtu/mbrtu.h"
/* ----------------------- Defines ------------------------------------------*/
#define REG_INPUT_START   0
#define REG_INPUT_NREGS   4
#define REG_HOLDING_START 0
#define REG_HOLDING_NREGS 10000

/* ----------------------- Static variables ---------------------------------*/
//static USHORT   usRegInputStart = REG_INPUT_START;
//static USHORT   usRegInputBuf[REG_INPUT_NREGS];
//static USHORT   usRegHoldingStart = REG_HOLDING_START;
//static USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];

/* ----------------------- Start implementation -----------------------------*/
void mymodbus_process(u8 dat)
{
  static u8 config_flag;
  volatile USHORT usACLKCnt;
  if(1==dat)
  {
    config_flag=0;
  }
  
  if(!config_flag)
  {
    
    /* Initialize Protocol Stack. */
    if( (eMBInit( MB_RTU, comm_info_var.maddr, 0, comm_info_var.baud_485, MB_PAR_NONE ) ) != MB_ENOERR )
    {
      return;
    }
    /* Enable the Modbus Protocol Stack. */
    else if( ( eMBEnable( ) ) != MB_ENOERR )
    {
      return;
    }
    config_flag=1;
  }
  
  ( void )eMBPoll(  );
}

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
  eMBErrorCode    eStatus = MB_ENOERR;
  
  
  if( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS )
  {
    
    switch ( eMode )
    {
      /* Pass current register values to the protocol stack. */
    case MB_REG_READ:
      {
        read_modbus_register(usAddress,usNRegs,(u16 *)pucRegBuffer);
      }
      break;
      
      /* Update current register values with new values from the
      * protocol stack. */
    case MB_REG_WRITE:
      {
        u16 temp_16dat[125];
        memcpy(temp_16dat,pucRegBuffer,usNRegs*2);
        //swap_u16_buff(temp_16dat,usNRegs);
        write_modbus_register(usAddress,usNRegs,temp_16dat);
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



eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
  eMBErrorCode    eStatus = MB_ENOERR;
  
  
  return eStatus;
}


eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
  return MB_ENOREG;
}

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
  return MB_ENOREG;
}

#endif