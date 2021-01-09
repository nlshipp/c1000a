/*
<:copyright-BRCM:2007:DUAL/GPL:standard

   Copyright (c) 2007 Broadcom Corporation
   All Rights Reserved

Unless you and Broadcom execute a separate written software license
agreement governing use of this software, this software is licensed
to you under the terms of the GNU General Public License version 2
(the "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php,
with the following added to such license:

   As a special exception, the copyright holders of this software give
   you permission to link this software with independent modules, and
   to copy and distribute the resulting executable under terms of your
   choice, provided that you also meet, for each linked independent
   module, the terms and conditions of the license of that module.
   An independent module is a module which is not derived from this
   software.  The special exception does not apply to any modifications
   of the software.

Not withstanding the above, under no circumstances may you combine
this software in any way with any other Broadcom software provided
under a license other than the GPL, without Broadcom's express prior
written consent.

:>
*/
/******************************************************************************
 * File Name  : spudrv.h
 *
 * Description: This file contains Linux character device driver data
 *              structures for the IPSec SPU.
 *
 * Updates    : 11/16/2007  Pavan Kumar.  Created.
 ***************************************************************************/
#ifndef __SPUDRV_H__
#define __SPUDRV_H__

#if 0
#define SPU_DEBUG 1
#define SPU_DEBUG_PKT 1
#endif

#ifdef SPU_DEBUG
#define SPU_TRACE(x)        printk x
#else
#define SPU_TRACE(x)
#endif

#ifdef SPU_DEBUG_PKT
#define SPU_DATA_DUMP(x, y, z) spu_dump_array(x, y, z)
#else
#define SPU_DATA_DUMP(x, y, z)
#endif

#define DMA_MAX_BURST_LENGTH         8
#define DESC_ALIGN                   16
#define BUF_ALIGN                    4
#define IPSEC_SPU_MSEC_PER_TICK      (1000/HZ)
#define IPSEC_SPU_ALIGN(addr, bound) (((UINT32) addr + bound - 1) & ~(bound - 1))

#define IPSECSPUDRV_MAJOR       233
#define DEV_ALIGN               32
#define DEV_ALIGN_CONST         (DEV_ALIGN - 1)
#define NR_XMIT_BDS             512
#define NR_RX_BDS               128
#define RX_BUF_SIZE             8192
#define CACHE_TO_NONCACHE(x)    KSEG1ADDR(x)
#define NONCACHE_TO_CACHE(x)    KSEG0ADDR(x)

// Cache related definitions and inline functions.
#define CACHE_LINE_SIZE                  16	// should read from CP0 config, 1
#define Hit_Invalidate_D                 0x11
#define Hit_Writeback_Inv_D              0x15	/* 5       1 */

#define XTRA_DMA_HDR_SIZE            1024
#define UBSEC_CIPHER_LIST            0
#define IPSEC_SPU_ALIGN(addr, bound) (((UINT32) addr + bound - 1) & ~(bound - 1))
#define ALIGN_SIZE                   4

#define CACHED_TO_UNCACHED(x)   KSEG1ADDR(x)
#define UNCACHED_TO_CACHED(x)   KSEG0ADDR(x)
#define VIRT_TO_PHYS(x)         CPHYSADDR(x)
#define PHYS_TO_CACHED(x)       ((x) | KSEG0)
#define PHYS_TO_UNCACHED(x)     ((x) | KSEG1)

typedef struct spu_dev_ctrl_s
{
    spinlock_t spin_lock;
    int        tx_free_bds;
    int        tx_head;
    int        tx_tail;
    int        rx_free_bds;
    int        rx_head;
    int        rx_tail;
    int        rx_irq;

    unsigned int     *txBdsBase;
    unsigned int     *rxBdsBase;
    volatile DmaDesc *tx_bds;
    volatile DmaDesc *rx_bds;
   
    volatile DmaRegs       *dma_ctrl;
    volatile DmaChannelCfg *tx_dma;
    volatile DmaChannelCfg *rx_dma;
    void                   *spu_linux;
    struct tasklet_struct   task;
#ifdef CONFIG_BCM_SPU_TEST
    int                     test_mode;
#endif
    SPU_STAT_PARMS stats;
} spu_dev_ctrl_t, *pspu_dev_ctrl_t;

#endif /* __SPUDRV_H__ */
