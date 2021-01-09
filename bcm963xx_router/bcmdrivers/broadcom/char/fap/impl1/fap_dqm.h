/************************************************************
 * <:copyright-BRCM:2009:DUAL/GPL:standard
 * 
 *    Copyright (c) 2009 Broadcom Corporation
 *    All Rights Reserved
 * 
 * Unless you and Broadcom execute a separate written software license 
 * agreement governing use of this software, this software is licensed 
 * to you under the terms of the GNU General Public License version 2 
 * (the "GPL"), available at http://www.broadcom.com/licenses/GPLv2.php, 
 * with the following added to such license:
 * 
 *    As a special exception, the copyright holders of this software give 
 *    you permission to link this software with independent modules, and 
 *    to copy and distribute the resulting executable under terms of your 
 *    choice, provided that you also meet, for each linked independent 
 *    module, the terms and conditions of the license of that module. 
 *    An independent module is a module which is not derived from this
 *    software.  The special exception does not apply to any modifications 
 *    of the software.  
 * 
 * Not withstanding the above, under no circumstances may you combine 
 * this software in any way with any other Broadcom software provided 
 * under a license other than the GPL, without Broadcom's express prior 
 * written consent. 
 * 
 * :>
 ************************************************************/

#ifndef __FAPDQM_H_INCLUDED__ 
#define __FAPDQM_H_INCLUDED__


/******************************************************************************
* File Name  : fap_dqm.h                                                      *
*                                                                             *
* Description: This is the main header file of the DQM implementation for     * 
*              the FAP MIPS core.                                             *
******************************************************************************/

#include    "bcmtypes.h"
#include    "fap_hw.h"

/* Queue Definitions */
#define DQM_MAX_QUEUE                   32
#define DQM_MAX_HANDLER                 8

#if defined(CONFIG_BCM_XTMCFG) || defined(CONFIG_BCM_XTMCFG_MODULE)
typedef struct {
    uint32 pBuf;
    uint32 dmaWord0;
    uint32 na1;
    uint32 na2;
} fapDqm_XtmRx_t;


#define DQM_FAP2HOST_XTM_RX_Q_SIZE		    2
#define DQM_IUDMA_XTM_RX_BUDGET		        100

#define DQM_FAP2HOST_XTM_RX_Q_LOW         	0
    #define DQM_FAP2HOST_XTM_RX_DEPTH_LOW   104
       

#define DQM_FAP2HOST_XTM_RX_Q_RSVD1	        1

#define DQM_FAP2HOST_XTM_RX_Q_HI   	        2
    #define DQM_FAP2HOST_XTM_RX_DEPTH_HI    40

#define DQM_FAP2HOST_XTM_RX_Q_RSVD2          3

typedef struct {
    uint8   *pBuf;           // 32  word0
    uint8    source;         // 8   word1
    uint8    channel;        // 8   word1
    uint16   len;            // 16  word1
    uint32   key;            // 32  word2
    uint16   dmaStatus;      // 16  word3
    uint16   param1;         // 16  word3
} fapDqm_XtmTx_t;

#define DQM_HOST2FAP_XTM_XMIT_Q_SIZE           4
#define DQM_HOST2FAP_XTM_XMIT_BUDGET           80

#define DQM_HOST2FAP_XTM_XMIT_Q_LOW        	   4
    #define DQM_HOST2FAP_XTM_XMIT_DEPTH_LOW    50


#define DQM_HOST2FAP_XTM_XMIT_Q_RSVD1          5

#define DQM_HOST2FAP_XTM_XMIT_Q_HI             6
    #define DQM_HOST2FAP_XTM_XMIT_DEPTH_HI     16
       

#define DQM_HOST2FAP_XTM_FREE_RXBUF_Q           7
    #define DQM_HOST2FAP_XTM_FREE_RXBUF_Q_SIZE  2
    #define DQM_HOST2FAP_XTM_FREE_RXBUF_DEPTH  \
                (DQM_HOST2FAP_XTM_XMIT_DEPTH_LOW + DQM_HOST2FAP_XTM_XMIT_DEPTH_HI)
    #define DQM_HOST2FAP_XTM_FREE_RXBUF_BUDGET  32
       
#define DQM_FAP2HOST_XTM_FREE_TXBUF_Q           8
    #define DQM_FAP2HOST_XTM_FREE_TXBUF_Q_SIZE  1
    /* Keep ahead of XTM_NR_TX_BDS to be able to bring iuDMA channels down */
#if defined(CONFIG_BCM_DSL_GINP_RTX) || defined(SUPPORT_DSL_GINP_RTX)
    #define DQM_FAP2HOST_XTM_FREE_TXBUF_DEPTH  405
#else
    #define DQM_FAP2HOST_XTM_FREE_TXBUF_DEPTH  (FAP_XTM_NR_TXBDS + 5)
#endif
    #define DQM_FAP2HOST_XTM_FREE_TXBUF_BUDGET  32
#else
#define DQM_FAP2HOST_XTM_RX_Q_SIZE		0
#define DQM_FAP2HOST_XTM_RX_Q_LOW         	0
#define DQM_FAP2HOST_XTM_RX_DEPTH_LOW           0
#define DQM_FAP2HOST_XTM_RX_Q_HI   	        0
#define DQM_FAP2HOST_XTM_RX_DEPTH_HI            0
#define DQM_HOST2FAP_XTM_XMIT_Q_SIZE            0
#define DQM_HOST2FAP_XTM_XMIT_Q_LOW        	0
#define DQM_HOST2FAP_XTM_XMIT_DEPTH_LOW         0
#define DQM_HOST2FAP_XTM_XMIT_Q_HI              0
#define DQM_HOST2FAP_XTM_XMIT_DEPTH_HI          0
#define DQM_HOST2FAP_XTM_FREE_RXBUF_Q_SIZE      0
#define DQM_HOST2FAP_XTM_FREE_RXBUF_DEPTH       0
#define DQM_FAP2HOST_XTM_FREE_TXBUF_Q_SIZE      0
#define DQM_FAP2HOST_XTM_FREE_TXBUF_DEPTH       0
#endif
       
typedef struct {
    uint32 pBuf;
    uint32 dmaWord0;
    uint32 na1;
    uint32 na2;
} fapDqm_EthRx_t;

#define DQM_FAP2HOST_ETH_RX_Q_SIZE              2
#define DQM_IUDMA_ETH_RX_BUDGET                 100


#define DQM_FAP2HOST_ETH_RX_Q_HI                11
    #define DQM_FAP2HOST_ETH_RX_DEPTH_HI        140 

#define DQM_FAP2HOST_ETH_RX_Q_RSVD1             10

#define DQM_FAP2HOST_ETH_RX_Q_LOW               9
    #define DQM_FAP2HOST_ETH_RX_DEPTH_LOW    \
	   (((FAP_ENET_NR_RXBDS - DQM_FAP2HOST_ETH_RX_DEPTH_HI) + 3) & (~3)) /*round to multiple of 4 */


#define DQM_FAP2HOST_ETH_RX_Q_RSVD2             12

typedef struct {
    uint8   *pBuf;           // 32  word0
    uint8    source;         // 8   word1
    union {
        struct {
            uint8 virtDestPort : 4;
            uint8 destQueue    : 4;
        };
        uint8 tm;            // 8   word1
    };
    uint16   len;            // 16  word1
    uint32   key;            // 32  word2
    uint16   dmaStatus;      // 16  word3
    uint16   param1;         // 16  word3
} fapDqm_EthTx_t;
       
#define DQM_HOST2FAP_ETH_XMIT_Q_SIZE       4
#define DQM_HOST2FAP_ETH_XMIT_BUDGET       80

#define DQM_HOST2FAP_ETH_XMIT_Q_LOW                 13
    #define DQM_HOST2FAP_ETH_XMIT_DEPTH_LOW         100
       

#define DQM_HOST2FAP_ETH_XMIT_Q_RSVD                 14

#define DQM_HOST2FAP_ETH_XMIT_Q_HI                  15
    #define DQM_HOST2FAP_ETH_XMIT_DEPTH_HI          20 

#define DQM_HOST2FAP_ETH_FREE_RXBUF_Q               16
    #define DQM_HOST2FAP_ETH_FREE_RXBUF_Q_SIZE      2
    #define DQM_HOST2FAP_ETH_FREE_RXBUF_DEPTH      \
                (DQM_HOST2FAP_ETH_XMIT_Q_HI + DQM_HOST2FAP_ETH_XMIT_DEPTH_LOW)
    #define DQM_HOST2FAP_ETH_FREE_RXBUF_BUDGET      32
       
#define DQM_FAP2HOST_ETH_FREE_TXBUF_Q               17
    #define DQM_FAP2HOST_ETH_FREE_TXBUF_Q_SIZE      1
    #define DQM_FAP2HOST_ETH_FREE_TXBUF_DEPTH       HOST_ENET_NR_TXBDS
    #define DQM_FAP2HOST_ETH_FREE_TXBUF_BUDGET      32
       

#define DQM_FAP2HOST_HOSTIF_Q                       30
    #define DQM_FAP2HOST_HOSTIF_Q_SIZE              4
    #define DQM_FAP2HOST_HOSTIF_Q_DEPTH             16
    #define DQM_FAP2HOST_HOSTIF_Q_BUDGET            16

#define DQM_HOST2FAP_HOSTIF_Q                       31
    #define DQM_HOST2FAP_HOSTIF_Q_SIZE              4
    #define DQM_HOST2FAP_HOSTIF_Q_DEPTH             100
    #define DQM_HOST2FAP_HOSTIF_Q_BUDGET            100



#define FAP_TOTAL_DQM_SIZE (( \
      ( DQM_FAP2HOST_ETH_RX_Q_SIZE * DQM_FAP2HOST_ETH_RX_DEPTH_LOW ) \
    + ( DQM_FAP2HOST_ETH_RX_Q_SIZE * DQM_FAP2HOST_ETH_RX_DEPTH_HI ) \
    + ( DQM_HOST2FAP_ETH_FREE_RXBUF_Q_SIZE * DQM_HOST2FAP_ETH_FREE_RXBUF_DEPTH ) \
    + ( DQM_HOST2FAP_ETH_XMIT_Q_SIZE * DQM_HOST2FAP_ETH_XMIT_DEPTH_LOW ) \
    + ( DQM_HOST2FAP_ETH_XMIT_Q_SIZE * DQM_HOST2FAP_ETH_XMIT_DEPTH_HI ) \
    + ( DQM_FAP2HOST_ETH_FREE_TXBUF_Q_SIZE * DQM_FAP2HOST_ETH_FREE_TXBUF_DEPTH ) \
    + ( DQM_HOST2FAP_HOSTIF_Q_SIZE * DQM_HOST2FAP_HOSTIF_Q_DEPTH ) \
    + ( DQM_FAP2HOST_HOSTIF_Q_SIZE * DQM_FAP2HOST_HOSTIF_Q_DEPTH ) \
    + ( DQM_FAP2HOST_XTM_RX_Q_SIZE * DQM_FAP2HOST_XTM_RX_DEPTH_LOW ) \
    + ( DQM_FAP2HOST_XTM_RX_Q_SIZE * DQM_FAP2HOST_XTM_RX_DEPTH_HI ) \
    + ( DQM_HOST2FAP_XTM_FREE_RXBUF_Q_SIZE * DQM_HOST2FAP_XTM_FREE_RXBUF_DEPTH ) \
    + ( DQM_HOST2FAP_XTM_XMIT_Q_SIZE * DQM_HOST2FAP_XTM_XMIT_DEPTH_LOW ) \
    + ( DQM_HOST2FAP_XTM_XMIT_Q_SIZE * DQM_HOST2FAP_XTM_XMIT_DEPTH_HI ) \
    + ( DQM_FAP2HOST_XTM_FREE_TXBUF_Q_SIZE * DQM_FAP2HOST_XTM_FREE_TXBUF_DEPTH ) \
    )*4)


#endif /* __FAPDQM_H_INCLUDED__ */
