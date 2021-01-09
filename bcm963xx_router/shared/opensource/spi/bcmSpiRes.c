/*
    Copyright 2000-2010 Broadcom Corporation

    Unless you and Broadcom execute a separate written software license
    agreement governing use of this software, this software is licensed
    to you under the terms of the GNU General Public License version 2
    (the "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
    with the following added to such license:

        As a special exception, the copyright holders of this software give
        you permission to link this software with independent modules, and to
        copy and distribute the resulting executable under terms of your
        choice, provided that you also meet, for each linked independent
        module, the terms and conditions of the license of that module. 
        An independent module is a module which is not derived from this
        software.  The special exception does not apply to any modifications
        of the software.

    Notwithstanding the above, under no circumstances may you combine this
    software in any way with any other Broadcom software provided under a
    license other than the GPL, without Broadcom's express prior written
    consent.
*/                       

#ifdef _CFE_
#include "lib_types.h"
#include "lib_printf.h"
#include "lib_string.h"
#include "bcm_map.h"  
#define  printk  printf
#else
#include <linux/version.h>
#include <linux/autoconf.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29)
#include <linux/semaphore.h>
#endif
#include <linux/spi/spi.h>
#include <linux/autoconf.h>

#include <bcm_map_part.h>
#endif
#include "bcmSpiRes.h"

extern int BcmLegSpiRead(unsigned char * msg_buf, int prependcnt, int nbytes, int devId, int freqHz);
extern int BcmLegSpiWrite(unsigned char * msg_buf, int nbytes, int devId, int freqHz);
extern int BcmHsSpiRead(unsigned char * msg_buf, int prependcnt, int nbytes, int devId, int freqHz, int ctrlState);
extern int BcmHsSpiWrite(unsigned char * msg_buf, int nbytes, int devId, int freqHz, int ctrlState);
extern int BcmHsSpiSetup(int spiMode, int ctrlState);

#ifdef HS_SPI
unsigned int bcmSpiCtrlState[8] = {SPI_CONTROLLER_STATE_DEFAULT, SPI_CONTROLLER_STATE_DEFAULT,
                                   SPI_CONTROLLER_STATE_DEFAULT, SPI_CONTROLLER_STATE_DEFAULT, 
                                   SPI_CONTROLLER_STATE_DEFAULT, SPI_CONTROLLER_STATE_DEFAULT, 
                                   SPI_CONTROLLER_STATE_DEFAULT, SPI_CONTROLLER_STATE_DEFAULT};
#endif

#ifndef _CFE_
#ifdef SPI
/* the BCM legacy controller supports up to 8 devices */
static struct spi_board_info bcmLegSpiDevInfo[8] =
{
    {
        .modalias      = "bcm_LegSpiDev0",
        .chip_select   = 0,
        .max_speed_hz  = 781000,
        .bus_num       = LEG_SPI_BUS_NUM,
        .mode          = SPI_MODE_3,
    },
    {
        .modalias      = "bcm_LegSpiDev1",
        .chip_select   = 1,
        .max_speed_hz  = 781000,
        .bus_num       = LEG_SPI_BUS_NUM,
        .mode          = SPI_MODE_3,
    },
    {
        .modalias      = "bcm_LegSpiDev2",
        .chip_select   = 2,
        .max_speed_hz  = 781000,
        .bus_num       = LEG_SPI_BUS_NUM,
        .mode          = SPI_MODE_3,
    },
    {
        .modalias      = "bcm_LegSpiDev3",
        .chip_select   = 3,
        .max_speed_hz  = 781000,
        .bus_num       = LEG_SPI_BUS_NUM,
        .mode          = SPI_MODE_3,
    },
    {
        .modalias      = "bcm_LegSpiDev4",
        .chip_select   = 4,
        .max_speed_hz  = 781000,
        .bus_num       = LEG_SPI_BUS_NUM,
        .mode          = SPI_MODE_3,
    },
    {
        .modalias      = "bcm_LegSpiDev5",
        .chip_select   = 5,
        .max_speed_hz  = 781000,
        .bus_num       = LEG_SPI_BUS_NUM,
        .mode          = SPI_MODE_3,
    },
    {
        .modalias      = "bcm_LegSpiDev6",
        .chip_select   = 6,
        .max_speed_hz  = 781000,
        .bus_num       = LEG_SPI_BUS_NUM,
        .mode          = SPI_MODE_3,
    },
    {
        .modalias      = "bcm_LegSpiDev7",
        .chip_select   = 7,
        .max_speed_hz  = 781000,
        .bus_num       = LEG_SPI_BUS_NUM,
        .mode          = SPI_MODE_3,
    },
};

static struct spi_driver bcmLegSpiDevDrv[8] = 
{
    {
        .driver = 
            {
            .name     = "bcm_LegSpiDev0",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_LegSpiDev1",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_LegSpiDev2",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_LegSpiDev3",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_LegSpiDev4",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    }, 
    {
        .driver = 
            {
            .name     = "bcm_LegSpiDev5",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_LegSpiDev6",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_LegSpiDev7",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
};

static struct spi_device * bcmLegSpiDevices[8];
#endif

#ifdef HS_SPI
/* the BCM HS controller supports up to 8 devices */
static struct spi_board_info bcmHSSpiDevInfo[8] =
{
    {
        .modalias        = "bcm_HSSpiDev0",
        .controller_data = (void *)SPI_CONTROLLER_STATE_DEFAULT,
        .chip_select     = 0,
        .max_speed_hz    = 781000,
        .bus_num         = HS_SPI_BUS_NUM,
        .mode            = SPI_MODE_DEFAULT,
    },
    {
        .modalias        = "bcm_HSSpiDev1",
        .controller_data = (void *)SPI_CONTROLLER_STATE_DEFAULT,
        .chip_select     = 1,
        .max_speed_hz    = 781000,
        .bus_num         = HS_SPI_BUS_NUM,
        .mode            = SPI_MODE_DEFAULT,
    },
    {
        .modalias        = "bcm_HSSpiDev2",
        .controller_data = (void *)SPI_CONTROLLER_STATE_DEFAULT,
        .chip_select     = 2,
        .max_speed_hz    = 781000,
        .bus_num         = HS_SPI_BUS_NUM,
        .mode            = SPI_MODE_DEFAULT,
    },
    {
        .modalias        = "bcm_HSSpiDev3",
        .controller_data = (void *)SPI_CONTROLLER_STATE_DEFAULT,
        .chip_select     = 3,
        .max_speed_hz    = 781000,
        .bus_num         = HS_SPI_BUS_NUM,
        .mode            = SPI_MODE_DEFAULT,
    },
    {
        .modalias        = "bcm_HSSpiDev4",
        .controller_data = (void *)SPI_CONTROLLER_STATE_DEFAULT,
        .chip_select     = 4,
        .max_speed_hz    = 781000,
        .bus_num         = HS_SPI_BUS_NUM,
        .mode            = SPI_MODE_DEFAULT,
    },
    {
        .modalias        = "bcm_HSSpiDev5",
        .controller_data = (void *)SPI_CONTROLLER_STATE_DEFAULT,
        .chip_select     = 5,
        .max_speed_hz    = 781000,
        .bus_num         = HS_SPI_BUS_NUM,
        .mode            = SPI_MODE_DEFAULT,
    },
    {
        .modalias        = "bcm_HSSpiDev6",
        .controller_data = (void *)SPI_CONTROLLER_STATE_DEFAULT,
        .chip_select     = 6,
        .max_speed_hz    = 781000,
        .bus_num         = HS_SPI_BUS_NUM,
        .mode            = SPI_MODE_DEFAULT,
    },
    {
        .modalias        = "bcm_HSSpiDev7",
        .controller_data = (void *)SPI_CONTROLLER_STATE_DEFAULT,
        .chip_select     = 7,
        .max_speed_hz    = 781000,
        .bus_num         = HS_SPI_BUS_NUM,
        .mode            = SPI_MODE_DEFAULT,
    },
};

static struct spi_driver bcmHSSpiDevDrv[8] = 
{
    {
        .driver = 
            {
            .name     = "bcm_HSSpiDev0",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_HSSpiDev1",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_HSSpiDev2",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_HSSpiDev3",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_HSSpiDev4",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    }, 
    {
        .driver = 
            {
            .name     = "bcm_HSSpiDev5",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_HSSpiDev6",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
    {
        .driver = 
            {
            .name     = "bcm_HSSpiDev7",
            .bus      = &spi_bus_type,
            .owner    = THIS_MODULE,
            },
    },
};

static struct spi_device * bcmHSSpiDevices[8];
#endif


int BcmSpiReserveSlave2(int busNum, int slaveId, int maxFreq, int spiMode, int ctrlState)
{
    struct spi_master * pSpiMaster;
    struct spi_driver * pSpiDriver;

    if ( slaveId > 7 )
    {
        return SPI_STATUS_ERR;
    }

    if ( LEG_SPI_BUS_NUM == busNum )
    {
#ifndef SPI
        return( SPI_STATUS_ERR );
#else
        if ( NULL != bcmLegSpiDevices[slaveId] )
        {
            printk(KERN_ERR "BcmSpiReserveSlave - slaveId %d, already registerd\n", slaveId);
            return( SPI_STATUS_ERR );
        }

        bcmLegSpiDevInfo[slaveId].max_speed_hz    = maxFreq;
        bcmLegSpiDevInfo[slaveId].controller_data = (void *)ctrlState;
        bcmLegSpiDevInfo[slaveId].mode            = spiMode;
        
        pSpiMaster                = spi_busnum_to_master( busNum );
        bcmLegSpiDevices[slaveId] = spi_new_device(pSpiMaster, &bcmLegSpiDevInfo[slaveId]);
        pSpiDriver                = &bcmLegSpiDevDrv[slaveId];
#endif
    }
    else if ( HS_SPI_BUS_NUM == busNum )
    {
#ifndef HS_SPI
        return( SPI_STATUS_ERR );
#else
        if ( NULL != bcmHSSpiDevices[slaveId] )
        {
            printk(KERN_ERR "BcmSpiReserveSlave - slaveId %d, already registerd\n", slaveId);
            return( SPI_STATUS_ERR );
        }

        bcmHSSpiDevInfo[slaveId].max_speed_hz    = maxFreq;
        bcmHSSpiDevInfo[slaveId].controller_data = (void *)ctrlState;
        bcmHSSpiDevInfo[slaveId].mode            = spiMode;
        
        pSpiMaster               = spi_busnum_to_master( busNum );
        bcmHSSpiDevices[slaveId] = spi_new_device(pSpiMaster, &bcmHSSpiDevInfo[slaveId]);
        pSpiDriver               = &bcmHSSpiDevDrv[slaveId];
#endif        
    }
    else
        return( SPI_STATUS_ERR );

    /* register the SPI driver */
    spi_register_driver(pSpiDriver);

    return 0;
    
}
EXPORT_SYMBOL(BcmSpiReserveSlave2);

int BcmSpiReserveSlave(int busNum, int slaveId, int maxFreq)
{
   return( BcmSpiReserveSlave2(busNum, slaveId, maxFreq, SPI_MODE_DEFAULT, SPI_CONTROLLER_STATE_DEFAULT) );
}
EXPORT_SYMBOL(BcmSpiReserveSlave);

int BcmSpiReleaseSlave(int busNum, int slaveId)
{
    if ( slaveId > 7 )
    {
        return SPI_STATUS_ERR;
    }

    if ( LEG_SPI_BUS_NUM == busNum )
    {
#ifndef SPI
        return( SPI_STATUS_ERR );
#else
        if ( NULL == bcmLegSpiDevices[slaveId] )
        {
            printk(KERN_ERR "BcmSpiReleaseSlave - slaveId %d, already released\n", slaveId);
            return( SPI_STATUS_ERR );
        }

        bcmLegSpiDevInfo[slaveId].max_speed_hz = 781000;
        spi_unregister_driver(&bcmLegSpiDevDrv[slaveId]);
        spi_unregister_device(bcmLegSpiDevices[slaveId]);
        bcmLegSpiDevices[slaveId] = 0;
#endif
    }
    else if ( HS_SPI_BUS_NUM == busNum )
    {
#ifndef HS_SPI
        return( SPI_STATUS_ERR );
#else
        if ( NULL == bcmHSSpiDevices[slaveId] )
        {
            printk(KERN_ERR "BcmSpiReleaseSlave - slaveId %d, already released\n", slaveId);
            return( SPI_STATUS_ERR );
        }

        bcmHSSpiDevInfo[slaveId].max_speed_hz = 781000;
        spi_unregister_driver(&bcmHSSpiDevDrv[slaveId]);
        spi_unregister_device(bcmHSSpiDevices[slaveId]);
        bcmHSSpiDevices[slaveId] = 0;
#endif        
    }
    else
        return( SPI_STATUS_ERR );

    return 0;
    
}
EXPORT_SYMBOL(BcmSpiReleaseSlave);


int BcmSpiSyncTrans(unsigned char *txBuf, unsigned char *rxBuf, int prependcnt, int nbytes, int busNum, int slaveId)
{
    struct spi_message  msg;
    struct spi_transfer xfer[2];
    int                 status;
    int                 maxLength;
    struct spi_device  *pSpiDevice;

    maxLength = BcmSpi_GetMaxRWSize(busNum);
    if ( (nbytes > maxLength) || (prependcnt > maxLength) )
    {
        printk(KERN_ERR "ERROR BcmSpiSyncTrans: invalid length len %d, pre %d, max %d\n", nbytes, prependcnt, maxLength);
        return SPI_STATUS_ERR;
    }
    
    if ( slaveId > 7 )
    {
        printk(KERN_ERR "ERROR BcmSpiSyncTrans: invalid slave id %d\n", slaveId);
        return SPI_STATUS_ERR;
    }

    if ( LEG_SPI_BUS_NUM == busNum )
    {
#ifndef SPI
        return( SPI_STATUS_ERR );
#else
        if ( NULL == bcmLegSpiDevices[slaveId] )
        {
            printk(KERN_ERR "ERROR BcmSpiSyncTrans: device not registered\n");
            return SPI_STATUS_ERR;
        } 
        pSpiDevice = bcmLegSpiDevices[slaveId];
#endif
    }
    else if ( HS_SPI_BUS_NUM == busNum )
    {
#ifndef HS_SPI
        return( SPI_STATUS_ERR );
#else
        if ( NULL == bcmHSSpiDevices[slaveId] )
        {
            printk(KERN_ERR "ERROR BcmSpiSyncTrans: device not registered\n");
            return SPI_STATUS_ERR;
        } 
        pSpiDevice = bcmHSSpiDevices[slaveId];
#endif
    }
    else
        return( SPI_STATUS_ERR );

    spi_message_init(&msg);
    memset(xfer, 0, (sizeof xfer));

    if ( prependcnt )
    {
        xfer[0].len      = prependcnt;
        xfer[0].speed_hz = pSpiDevice->max_speed_hz;
        if ( txBuf )
        {
            xfer[0].tx_buf = txBuf;
        }
        else
        {
            xfer[0].tx_buf = rxBuf;
        }
        spi_message_add_tail(&xfer[0], &msg);
    }

    xfer[1].len      = nbytes;
    xfer[1].speed_hz = pSpiDevice->max_speed_hz;
    xfer[1].rx_buf   = rxBuf;

    /* for the controller to use the prepend count correctly the first operation must be a read and the second a write 
       make sure tx is NULL for second transaction */
    if ( 0 == prependcnt )
    {
        xfer[1].tx_buf = txBuf;
    }
    spi_message_add_tail(&xfer[1], &msg);

    status = spi_sync(pSpiDevice, &msg);
    if (status >= 0)
    {
        status = SPI_STATUS_OK;
    } 
    else
    {
        status = SPI_STATUS_ERR;
    }

    return( status );

}
EXPORT_SYMBOL(BcmSpiSyncTrans);

int BcmSpiSyncMultTrans(struct spi_transfer *pSpiTransfer, int numTransfers, int busNum, int slaveId)
{
    struct spi_message  msg;
    int                 status;
    int                 maxLength;
    struct spi_device  *pSpiDevice;
    int                 i;

    if ( (slaveId > 7) || (busNum > 1) )
    {
        printk(KERN_ERR "ERROR BcmSpiSyncTrans: invalid slave id (%d) or busNum (%d)\n", slaveId, busNum);
        return SPI_STATUS_ERR;
    }

    /* verify the length of each transfer passed in and add each transfer to the message */
    spi_message_init(&msg);
    maxLength = BcmSpi_GetMaxRWSize(busNum);
    for ( i = 0; i < numTransfers; i++ )
    {
        if ( pSpiTransfer[i].len > maxLength )
        {
            printk(KERN_ERR "ERROR BcmSpiSyncTrans: invalid length len %d, max %d, for transfer %x\n", pSpiTransfer[i].len, maxLength, i);
            return SPI_STATUS_ERR;
        }
        spi_message_add_tail(&pSpiTransfer[i], &msg);
    }

    if ( LEG_SPI_BUS_NUM == busNum )
    {
#ifndef SPI
        return( SPI_STATUS_ERR );
#else
        if ( NULL == bcmLegSpiDevices[slaveId] )
        {
            printk(KERN_ERR "ERROR BcmSpiSyncTrans: device not registered\n");
            return SPI_STATUS_ERR;
        } 
        pSpiDevice = bcmLegSpiDevices[slaveId];
#endif
    }
    else if ( HS_SPI_BUS_NUM == busNum )
    {
#ifndef HS_SPI
        return( SPI_STATUS_ERR );
#else
        if ( NULL == bcmHSSpiDevices[slaveId] )
        {
            printk(KERN_ERR "ERROR BcmSpiSyncTrans: device not registered\n");
            return SPI_STATUS_ERR;
        } 
        pSpiDevice = bcmHSSpiDevices[slaveId];
#endif
    }
    else
        return( SPI_STATUS_ERR );

    status = spi_sync(pSpiDevice, &msg);
    if (status >= 0)
    {
        status = SPI_STATUS_OK;
    } 
    else
    {
        status = SPI_STATUS_ERR;
    }

    return( status );

}
EXPORT_SYMBOL(BcmSpiSyncMultTrans);

static void spidevcomplete(void *arg)
{
   int temp;
   temp = *(int *)arg;
   temp--;
   *(int *)arg = temp;
}

int BcmSpiSyncMultTransNoSched(struct spi_transfer *pSpiTransfer, int numTransfers, int busNum, int slaveId)
{
    struct spi_message  msg;
    int                 status;
    int                 maxLength;
    struct spi_device  *pSpiDevice;
    int                 i;
    volatile int        arg;

    if ( (slaveId > 7) || (busNum > 1) )
    {
        printk(KERN_ERR "ERROR BcmSpiSyncTrans: invalid slave id (%d) or busNum (%d)\n", slaveId, busNum);
        return SPI_STATUS_ERR;
    }

    /* verify the length of each transfer passed in and add each transfer to the message */
    spi_message_init(&msg);
    maxLength = BcmSpi_GetMaxRWSize(busNum);
    for ( i = 0; i < numTransfers; i++ )
    {
        if ( pSpiTransfer[i].len > maxLength )
        {
            printk(KERN_ERR "ERROR BcmSpiSyncTrans: invalid length len %d, max %d, for transfer %x\n", pSpiTransfer[i].len, maxLength, i);
            return SPI_STATUS_ERR;
        }
        spi_message_add_tail(&pSpiTransfer[i], &msg);
    }

    if ( LEG_SPI_BUS_NUM == busNum )
    {
#ifndef SPI
        return( SPI_STATUS_ERR );
#else
        if ( NULL == bcmLegSpiDevices[slaveId] )
        {
            printk(KERN_ERR "ERROR BcmSpiSyncTrans: device not registered\n");
            return SPI_STATUS_ERR;
        } 
        pSpiDevice = bcmLegSpiDevices[slaveId];
#endif
    }
    else if ( HS_SPI_BUS_NUM == busNum )
    {
#ifndef HS_SPI
        return( SPI_STATUS_ERR );
#else
        if ( NULL == bcmHSSpiDevices[slaveId] )
        {
            printk(KERN_ERR "ERROR BcmSpiSyncTrans: device not registered\n");
            return SPI_STATUS_ERR;
        } 
        pSpiDevice = bcmHSSpiDevices[slaveId];
#endif
    }
    else
        return( SPI_STATUS_ERR );

    arg = 1;
    msg.complete = spidevcomplete;
    msg.context  = (void *)&arg;

    status = spi_async(pSpiDevice, &msg);
    if (status >= 0)
    {
        status = SPI_STATUS_OK;
    } 
    else
    {
        status = SPI_STATUS_ERR;
    }

    while ( arg > 0)
    {
       udelay(1);
    }

    return( status );

}
EXPORT_SYMBOL(BcmSpiSyncMultTransNoSched);
#endif

int BcmSpi_SetCtrlState( int busNum, int slaveId, int spiMode, int ctrlState )
{
    if ( (slaveId > 7) || (busNum > 1) )
    {
        printk("ERROR BcmSpi_SetCtrlState: invalid slave id (%d) or busNum (%d)\n", slaveId, busNum);
        return SPI_STATUS_ERR;
    }

#ifdef HS_SPI
    bcmSpiCtrlState[slaveId] = BcmHsSpiSetup(spiMode, ctrlState);
#endif
    return SPI_STATUS_OK;
}


int BcmSpi_SetFlashCtrl( int opCode, int addrBytes, int dummyBytes, int busNum, int devId, int clockHz )
{
    if ( HS_SPI_BUS_NUM == busNum )
    {
#ifndef HS_SPI
        return SPI_STATUS_ERR;
#else
        int clock;

        clock = HS_SPI_PLL_FREQ/clockHz;
        if (HS_SPI_PLL_FREQ%clockHz)
            clock++;

        clock = 2048/clock;
        if (2048%(clock))
            clock++; 

        HS_SPI_PROFILES[0].clk_ctrl = 1<<HS_SPI_ACCUM_RST_ON_LOOP | 0<<HS_SPI_SPI_CLK_2X_SEL | clock<<HS_SPI_FREQ_CTRL_WORD;
        HS_SPI->hs_spiFlashCtrl = devId<<HS_SPI_FCTRL_SS_NUM | 0<<HS_SPI_FCTRL_PROFILE_NUM | dummyBytes<<HS_SPI_FCTRL_DUMMY_BYTES | 
                                  addrBytes<<HS_SPI_FCTRL_ADDR_BYTES | opCode<<HS_SPI_FCTRL_READ_OPCODE;
#endif
    }
    else if ( LEG_SPI_BUS_NUM == busNum )
    {
#ifndef SPI
        return SPI_STATUS_ERR;
#endif 
    }
    else
        return SPI_STATUS_ERR;
            
    return SPI_STATUS_OK;
    
}


int BcmSpi_GetMaxRWSize( int busNum )
{
    int maxRWSize = 0;

    if ( HS_SPI_BUS_NUM == busNum )
    {
#ifdef HS_SPI
        maxRWSize = HS_SPI_BUFFER_LEN;
#endif
    }
    else if ( LEG_SPI_BUS_NUM == busNum )
    {
#ifdef SPI
        maxRWSize = sizeof(SPI->spiMsgData);
#endif
    }

    maxRWSize &= ~0x3;

    return(maxRWSize);

}


/* The interface bcmSpi_Read and bcmSpi_Write provide direct access to the SPI controller.
   these interfaces should only be called by CFE and early spi flash code */
int BcmSpi_Read( unsigned char *msg_buf, int prependcnt, int nbytes, int busNum, int devId, int freqHz )
{
    if ( LEG_SPI_BUS_NUM == busNum )
    {
#ifndef SPI
        return SPI_STATUS_ERR;
#else
        return BcmLegSpiRead( msg_buf, prependcnt, nbytes, devId, freqHz );
#endif
    }
    else if ( HS_SPI_BUS_NUM == busNum )
    {
#ifndef HS_SPI
        return SPI_STATUS_ERR;
#else
        return BcmHsSpiRead( msg_buf, prependcnt, nbytes, devId, freqHz, 
                             bcmSpiCtrlState[devId] );
#endif
    }
    else
    {
        return SPI_STATUS_ERR;
    }

}

int BcmSpi_Write( unsigned char *msg_buf, int nbytes, int busNum, int devId, int freqHz )
{
    if ( LEG_SPI_BUS_NUM == busNum )
    {
#ifndef SPI
        return SPI_STATUS_ERR;
#else
        return BcmLegSpiWrite( msg_buf, nbytes, devId, freqHz );
#endif
    }
    else if ( HS_SPI_BUS_NUM == busNum )
    {
#ifndef HS_SPI
        return SPI_STATUS_ERR;
#else
        return BcmHsSpiWrite( msg_buf, nbytes, devId, freqHz, 
                              bcmSpiCtrlState[devId] );
#endif
    }
    else
    {
        return SPI_STATUS_ERR;
    }
}

#ifndef _CFE_
EXPORT_SYMBOL(BcmSpi_SetFlashCtrl);
EXPORT_SYMBOL(BcmSpi_GetMaxRWSize);
#endif

