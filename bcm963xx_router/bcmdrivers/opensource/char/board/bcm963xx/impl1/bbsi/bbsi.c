/*
<:label-BRCM::DUAL/GPL:standard 
:>
*/

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <bcm_map_part.h>
#include <linux/device.h>
#include <bcmSpiRes.h>
#include <board.h>
#include <boardparms.h>
#include <linux/mii.h>
#include "bbsi.h"


/***************************************************************************
* File Name  : bbsi.c
*
* Description: This file contains the functions for communicating between a brcm
*              cpe chip(eg 6818) to another brcm chip(6802) which is connected 
*              as a spi slave device. This protocol used to communicate is BBSI.
*
***************************************************************************/

/*********************************************************************************************************
 * Eg. configuration required for spi slave devices
 * 
 * 6368: BcmSpiReserveSlave2(HS_SPI_BUS_NUM, 7, 781000, SPI_MODE_3, SPI_CONTROLLER_STATE_GATE_CLK_SSOFF);
 *
 *
 **********************************************************************************************************/

extern spinlock_t bcm_gpio_spinlock;

#define BCM_SPI_SLAVE_ID     1
#define BCM_SPI_SLAVE_FREQ   20000000
#define MAX_STATUS_RETRY 5

static unsigned int bcmSpiSlaveResetGpio = 0xFF;
static unsigned int bcmSpiSlaveBus       = LEG_SPI_BUS_NUM;
static unsigned int bcmSpiSlaveId        = BCM_SPI_SLAVE_ID;
static unsigned int bcmSpiSlaveMaxFreq   = BCM_SPI_SLAVE_FREQ;
static unsigned int bcmSpiSlaveMode      = SPI_MODE_3;
static unsigned int bcmSpiSlaveCtrState  = SPI_CONTROLLER_STATE_CPHA_EXT;




static void getSpiSlaveDeviceInfo(void);
static void resetSpiSlaveDevice(void);
static int isBBSIDone(void);


static struct mutex bcmSpiSlaveMutex;

static int isBBSIDone(void)
{
    uint8_t read_status[2] = { BBSI_COMMAND_BYTE | 0x1, // Do a Read
                               STATUS_REGISTER_ADDR
                            };
    int status;
    int i;
    int ret = 0;
     
    for (i=0; i<MAX_STATUS_RETRY; i++)
    {   
        status = BcmSpiSyncTrans(read_status, &read_status[0], 2, 1, bcmSpiSlaveBus, bcmSpiSlaveId);
        if ( SPI_STATUS_OK != status )
        {
           printk(KERN_ERR "isBBSIDone: BcmSpiSyncTrans returned error\n");          
           ret = 0;
           break;
        }
        status = read_status[0];
        
        if (status & 0xF)
        {
           printk(KERN_ERR "isBBSIDone: BBSI transaction error, status=0x%x", status);          
           ret = 0; 
           break;
        }
        else if ( (status & (1<<BUSY_SHIFT)) == 0 )
        {
            ret = 1;
            break;
        }
    }   

    return ret;
}


int kerSysBcmSpiSlaveInit( void )
{
    unsigned long data;
    int32_t       retVal = 0;
    int           status;

    mutex_init(&bcmSpiSlaveMutex);
    
    getSpiSlaveDeviceInfo();             
    resetSpiSlaveDevice();  

    status = BcmSpiReserveSlave2(bcmSpiSlaveBus, bcmSpiSlaveId, bcmSpiSlaveMaxFreq, bcmSpiSlaveMode, bcmSpiSlaveCtrState);
    if ( SPI_STATUS_OK != status )
    {
      printk(KERN_ERR "%s: BcmSpiReserveSlave2 returned error %d\n", __FUNCTION__, status);
      return(SPI_STATUS_ERR);
    }
  
     
    if ((kerSysBcmSpiSlaveRead(0x107ffc80, &data, 4) == -1) ||
       (data == 0) || (data == 0xffffffff))
    {   
      printk(KERN_ERR "%s: Failed to read the MOCA_GR_BRIDGE_REVISION: 0x%08x\n", __FUNCTION__, (unsigned int)data);
      return -1;
    }
    else
    {
      printk(KERN_INFO "%s: MOCA_GR_BRIDGE_REVISION: 0x%08x\n", __FUNCTION__, (unsigned int)data);
    }

    
    return( retVal );

}

int kerSysBcmSpiSlaveRead(unsigned long addr, unsigned long *data, unsigned long len)
{
    uint8_t buf[12];
    int status;   
  
    mutex_lock(&bcmSpiSlaveMutex); 
   
    buf[0]  = BBSI_COMMAND_BYTE | 0x1;          /* Assumes read signal is 1 */
    buf[1]  = CONFIG_REGISTER_ADDR;       /* Start the writes from this addr */
    buf[2]  = ( (4-len) << XFER_MODE_SHIFT ) |  0x1; /* Indicates the transaction is 32bit, 24bit, 16bit or 8bit. Len is 1..4 */  
    buf[3]  = (addr >> 24) & 0xFF;  /* Assuming MSB bytes are always sent first */
    buf[4]  = (addr >> 16) & 0xFF;
    buf[5]  = (addr >> 8)  & 0xFF;
    buf[6]  = (addr >> 0)  & 0xFF;
    
    status = BcmSpiSyncTrans(buf, buf, 7, 4, bcmSpiSlaveBus, bcmSpiSlaveId);
    if ( SPI_STATUS_OK != status )
    {
       printk(KERN_ERR "kerSysBcmSpiSlaveRead: BcmSpiSyncTrans returned error\n");
       mutex_unlock(&bcmSpiSlaveMutex);
       return(-1);
    }

    *data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    
    mutex_unlock(&bcmSpiSlaveMutex);  
    return(0);
}

int kerSysBcmSpiSlaveWrite(unsigned long addr, unsigned long data, unsigned long len)
{
   uint8_t buf[12]; 
   int status;

   mutex_lock(&bcmSpiSlaveMutex);

   data <<= 8 * (4 - len); // Do we have to do this? It will matter only for len = 1 or 2.

   buf[0]  = BBSI_COMMAND_BYTE;          /* Assumes write signal is 0 */
   buf[1]  = CONFIG_REGISTER_ADDR;       /* Start the writes from this addr */
   buf[2]  = (4-len) << XFER_MODE_SHIFT ; /* Indicates the transaction is 32bit, 24bit, 16bit or 8bit. Len is 1..4 */  
   buf[3]  = (addr >> 24) & 0xFF;  /* Assuming MSB bytes are always sent first */
   buf[4]  = (addr >> 16) & 0xFF;
   buf[5]  = (addr >> 8)  & 0xFF;
   buf[6]  = (addr >> 0)  & 0xFF;
   buf[7]  = (data >> 24) & 0xFF;
   buf[8]  = (data >> 16) & 0xFF;
   buf[9]  = (data >> 8)  & 0xFF;
   buf[10] = (data >> 0)  & 0xFF;

   
   status = BcmSpiSyncTrans(buf, NULL, 0,11, bcmSpiSlaveBus, bcmSpiSlaveId);
   if ( SPI_STATUS_OK != status )
   {
      printk(KERN_ERR "kerSysBcmSpiSlaveWrite: BcmSpiSyncTrans returned error\n");
      mutex_unlock(&bcmSpiSlaveMutex);
      return(-1);
   }

   if (!isBBSIDone())
   {
      printk(KERN_ERR "kerSysBcmSpiSlaveWrite: write to addr:0x%lx failed\n", addr);
      mutex_unlock(&bcmSpiSlaveMutex);
      return(-1);
   }

   mutex_unlock(&bcmSpiSlaveMutex);

   return(0);
}


int kerSysBcmSpiSlaveWriteBuf(unsigned long addr, unsigned long *data, unsigned long len, unsigned int unitSize)
{
    int            ret = SPI_STATUS_ERR;  
 
    mutex_lock(&bcmSpiSlaveMutex);

    /* To Do: Optimize using autoincrement. */
    while(len >= unitSize)
    {
        if (kerSysBcmSpiSlaveWrite(addr, *data, unitSize))
        {
           printk(KERN_ERR "kerSysBcmSpiSlaveWriteBuf: write to addr:0x%lx failed\n", addr);
           ret = SPI_STATUS_ERR;
           break;
        }

        len  -= unitSize;
        addr += unitSize;
        data = (unsigned long *)( (unsigned long)data + unitSize ) ;
    }
    
    mutex_unlock(&bcmSpiSlaveMutex);
    return ret;
}

  

unsigned long kerSysBcmSpiSlaveReadReg32(unsigned long addr)
{
   unsigned long data = 0;

   BUG_ON(addr & 3);
   addr &= 0x1fffffff;
   
   if(kerSysBcmSpiSlaveRead(addr, &data, 4) < 0)
   {
      printk(KERN_ERR "kerSysBcmSpiSlaveReadReg32: can't read %08x\n", (unsigned int)addr);
   }

   return(data);
}

void kerSysBcmSpiSlaveWriteReg32(unsigned long addr, unsigned long data)
{
   BUG_ON(addr & 3);
   addr &= 0x1fffffff;

   if(kerSysBcmSpiSlaveWrite(addr, data, 4) < 0)
   {
      printk(KERN_ERR "kerSysBcmSpiSlaveWriteReg32: can't write %08x (data %08x)\n", (unsigned int)addr, (unsigned int)data);
   }

}



 // Move these functions to a moca board file.
static void resetSpiSlaveDevice(void)
{
   // unsigned long flags;
    
    printk(KERN_ERR "Entering %s: bcmSpiSlaveResetGpio = %d\n", __FUNCTION__, bcmSpiSlaveResetGpio);  

    if ( bcmSpiSlaveResetGpio != 0xFF )
    {
        kerSysSetGpioState(bcmSpiSlaveResetGpio,  kGpioInactive);
        mdelay(1);
        kerSysSetGpioState(bcmSpiSlaveResetGpio,  kGpioActive); 
        mdelay(350);
    }
  
}

 
static void getSpiSlaveDeviceInfo(void)
{ 
    unsigned short gpio;
    unsigned short slaveId;
    unsigned short slaveBus;
    unsigned short slaveMode;  
    unsigned long  ctrlState;  
    unsigned long  slaveMaxFreq;     
     
    if ( BpGetSpiSlaveResetGpio(&gpio) == BP_SUCCESS ) 
    {
        bcmSpiSlaveResetGpio = gpio;
        printk(KERN_INFO "%s: bcmSpiSlaveResetGpio = %d\n", __FUNCTION__, bcmSpiSlaveResetGpio);        
    }

    if ( BpGetSpiSlaveSelectNum(&slaveId) == BP_SUCCESS ) 
    {
        bcmSpiSlaveId = slaveId;
        printk(KERN_INFO"%s: bcmSpiSlaveId = %d\n", __FUNCTION__, bcmSpiSlaveId);          
    }
    
    if ( BpGetSpiSlaveBusNum(&slaveBus) == BP_SUCCESS ) 
    {
        bcmSpiSlaveBus = slaveBus;
        printk(KERN_INFO "%s: bcmSpiSlaveBus = %d\n", __FUNCTION__, bcmSpiSlaveBus);           
    }
    
    if ( BpGetSpiSlaveMode(&slaveMode) == BP_SUCCESS ) 
    {
        bcmSpiSlaveMode = slaveMode;
        printk(KERN_INFO "%s: bcmSpiSlaveMode = %d\n", __FUNCTION__, bcmSpiSlaveMode);            
    }

    if ( BpGetSpiSlaveCtrlState(&ctrlState) == BP_SUCCESS ) 
    {
        bcmSpiSlaveCtrState = ctrlState;
        printk(KERN_INFO "%s: bcmSpiSlaveCtrState = 0x%x\n", __FUNCTION__, bcmSpiSlaveCtrState);           
    }
    
    if ( BpGetSpiSlaveMaxFreq(&slaveMaxFreq) == BP_SUCCESS ) 
    {
        bcmSpiSlaveMaxFreq = slaveMaxFreq;
        printk(KERN_INFO "%s: bcmSpiSlaveMaxFreq = %d\n", __FUNCTION__, bcmSpiSlaveMaxFreq);          
    }         
 
}


