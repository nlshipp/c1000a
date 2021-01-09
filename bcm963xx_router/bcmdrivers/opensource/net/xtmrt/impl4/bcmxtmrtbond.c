/*
<:copyright-gpl 
 Copyright 2007 Broadcom Corp. All Rights Reserved. 
 
 This program is free software; you can distribute it and/or modify it 
 under the terms of the GNU General Public License (Version 2) as 
 published by the Free Software Foundation. 
 
 This program is distributed in the hope it will be useful, but WITHOUT 
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License 
 for more details. 
 
 You should have received a copy of the GNU General Public License along 
 with this program; if not, write to the Free Software Foundation, Inc., 
 59 Temple Place - Suite 330, Boston MA 02111-1307, USA. 
:>
*/
/**************************************************************************
 * File Name  : bcmxtmrtbond.c
 *
 * Description: This file implements BCM6368 ATM/PTM bonding network device driver
 *              runtime processing - sending and receiving data.
 *              Current implementation pertains to PTM bonding. Broadcom ITU G.998.2 
 *              solution.
 ***************************************************************************/


/* Includes. */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/version.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/rtnetlink.h>
#include <linux/ethtool.h>
#include <linux/if_arp.h>
#include <linux/ppp_channel.h>
#include <linux/ppp_defs.h>
#include <linux/if_ppp.h>
#include <linux/atm.h>
#include <linux/atmdev.h>
#include <linux/atmppp.h>
#include <linux/blog.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <bcmtypes.h>
#include <bcm_map_part.h>
#include <bcm_intr.h>
#include <board.h>
#include "bcmnet.h"
#include "bcmxtmcfg.h"
#include "bcmxtmrt.h"
#include <asm/io.h>
#include <asm/r4kcache.h>
#include <asm/uaccess.h>
#include <linux/nbuff.h>
#include "bcmxtmrtimpl.h"

#ifdef PERF_MON_BONDING_US
#include <asm/pmonapi.h>
#endif

#ifdef PERF_MON_BONDING_US
#define PMON_US_LOG(x)        pmon_log(x)
#define PMON_US_CLR(x)        pmon_clr(x)
#define PMON_US_BGN           pmon_bgn()
#define PMON_US_END(x)        pmon_end(x)
#define PMON_US_REG(x,y)      pmon_reg(x,y)
#else
#define PMON_US_LOG(x)        
#define PMON_US_CLR(x)        
#define PMON_US_BGN
#define PMON_US_END(x)        
#define PMON_US_REG(x,y)
#endif

static inline int getPtmFragmentLen (int len) ;
static int constructPtmBondHdr (PBCMXTMRT_DEV_CONTEXT pDevCtx, UINT32 ulPtmPrioIdx, int len) ;

/***************************************************************************
 * Function Name: getPtmFragmentLen
 * Description  : Compute next fragment length
 * Returns      : fragment length.
 ***************************************************************************/
static inline int getPtmFragmentLen (int len)
{
	int fragmentLen ;
	int leftOver ;

	if (len <= XTMRT_PTM_BOND_TX_MAX_FRAGMENT_SIZE) {
		fragmentLen = len ;
	}
	else {
		/* send as much as possible unless we don't have
		   enough data left anymore for a full fragment */
		fragmentLen = XTMRT_PTM_BOND_TX_MAX_FRAGMENT_SIZE ;
		leftOver = len-fragmentLen ;
		if (leftOver < XTMRT_PTM_BOND_TX_MIN_FRAGMENT_SIZE) {
			fragmentLen -= (XTMRT_PTM_BOND_TX_MIN_FRAGMENT_SIZE + leftOver) ;
			fragmentLen &= ~0x3 ; /* make it a multiple of 4 bytes */
		}
	}
	return fragmentLen ;
}

/***************************************************************************
 * Function Name: constructPtmBondHdr
 * Description  : Calculates the PTM bonding hdr information and fills it up
 *                in the global buffer to be used for the packet.
 * Returns      : NoofFragments.
 ***************************************************************************/
static int constructPtmBondHdr (PBCMXTMRT_DEV_CONTEXT pDevCtx, UINT32 ulPtmPrioIdx, int len)
{
   int i, serviced = 0 ;
   PBCMXTMRT_GLOBAL_INFO pGi = &g_GlobalInfo ;
   XtmRtPtmTxBondHeader  *pPtmHeader  = NULL ;
   int                   fragNo, fragLen ;
   XtmRtPtmBondInfo      *pBondInfo = &pGi->ptmBondInfo ;
   volatile UINT32       *pPortDataMask = &pDevCtx->ulPortDataMask ;
   volatile UINT32       *pulLinkWts    = &pBondInfo->ulLinkUsWt[0] ;
   volatile UINT8        *pu8ConfWtPortDist = &pBondInfo->u8ConfWtPortDist[0] ;
   volatile UINT32       *pulCurrWtPortDistStartIndex = &pBondInfo->ulCurrWtPortDistStartIndex ;
   volatile UINT32       *pulCurrWtPortDistRunIndex   = &pBondInfo->ulCurrWtPortDistRunIndex ;
   volatile UINT32       *pulCurrWtTotalIterationsBeforeReset   = &pBondInfo->ulCurrWtTotalIterationsBeforeReset ;
   UINT8                 portCount ;
   int                   reloadCount;

   fragNo = 0 ;
   len += ETH_FCS_LEN ;    /* Original Packet Len + 4 bytes of Eth FCS Len */
   
   while (len != 0) {
      fragLen = getPtmFragmentLen (len) ;
      len -= fragLen ;
      pPtmHeader = &pGi->ptmBondHdr [fragNo] ;

      fragLen += XTMRT_PTM_BOND_FRAG_HDR_SIZE + XTMRT_PTM_CRC_SIZE ;  /* With actual hdrs/trailers */
      pPtmHeader->sVal.FragSize = fragLen ;

#ifndef PTMBOND_US_PRIO_TRAFFIC_SPLIT
      reloadCount = 0;
      do {
         for (i = 0; i< MAX_BOND_PORTS; i++) {

            portCount = pu8ConfWtPortDist [*pulCurrWtPortDistRunIndex] ;

            if ((((*pPortDataMask >> portCount) & 0x1) != 0)
                  &&
                  (pulLinkWts[portCount] >= fragLen)) {  /* port is enabled with valid weights */

               pPtmHeader->sVal.portSel = portCount ;
               pulLinkWts[portCount] -= fragLen ;
               serviced = 1 ;
            }

            *pulCurrWtTotalIterationsBeforeReset += 1 ;
            if (*pulCurrWtTotalIterationsBeforeReset == pBondInfo->totalWtPortDist) {

               *pulCurrWtPortDistStartIndex = ((*pulCurrWtPortDistStartIndex+1) >= pBondInfo->totalWtPortDist) ? 0 :
                  *pulCurrWtPortDistStartIndex+1 ;
               *pulCurrWtPortDistRunIndex = *pulCurrWtPortDistStartIndex ;
               *pulCurrWtTotalIterationsBeforeReset = 0 ;
            }
            else {
               *pulCurrWtPortDistRunIndex = ((*pulCurrWtPortDistRunIndex+1) >= pBondInfo->totalWtPortDist) ? 0 :
                  *pulCurrWtPortDistRunIndex+1 ;
            }

            if (serviced == 1) {
               break ;
            }
         } /* for (i) */

         if (serviced == 1) {
            serviced  = 0 ;
            break ;
         }
         else {/* No port selection happened  for this fragment, reload the weights with unused credits */
            reloadCount ++;
            /* reload the weights more than one time, CPE does not have enought bandwidth. */
            if (reloadCount > 1) { 
               //printk (CARDNAME " constructPtmBondHdr: does not have enough uplink bandwidth. \n") ;             
               return 0 ;
            }

            pulLinkWts[0] += pBondInfo->ulConfLinkUsWt[0] ;
            pulLinkWts[1] += pBondInfo->ulConfLinkUsWt[1] ;
         }
      } while (1) ;
#else
      pPtmHeader->sVal.portSel = (ulPtmPrioIdx == PTM_FLOW_PRI_LOW) ? PHY_PORTID_0 : PHY_PORTID_1 ;
#endif

      pPtmHeader->sVal.PktEop = XTMRT_PTM_BOND_HDR_NON_EOP ;
      fragNo++ ;
   } /* while (len != 0) */

   pPtmHeader->sVal.PktEop = XTMRT_PTM_BOND_FRAG_HDR_EOP ;
   return (fragNo) ;
}

/***************************************************************************
 * Function Name: bcmxtmrt_ptmbond_add_hdr
 * Description  : Adds the PTM Bonding Tx header to a WAN packet before transmitting
 *                it.
 * Returns      : 0: fail, others: success.
 ***************************************************************************/
int bcmxtmrt_ptmbond_add_hdr (PBCMXTMRT_DEV_CONTEXT pDevCtx, UINT32 ulPtmPrioIdx,
                               pNBuff_t *ppNBuff, struct sk_buff **ppNBuffSkb, 
                               UINT8 **ppData, int *pLen)
{
   int                   frags = 0;
   XtmRtPtmTxBondHeader  *pPtmBondHdr ;
   int                   headroom ;
   int                   len ;
   int                   minheadroom ;
   PBCMXTMRT_GLOBAL_INFO pGi ;
   XtmRtPtmBondInfo      *pBondInfo ;
   XtmRtPtmTxBondHeader  *pPtmSrcBondHdr ;

   PMON_US_BGN ;

   minheadroom  = sizeof (XtmRtPtmTxBondHeader) * XTMRT_PTM_BOND_MAX_FRAG_PER_PKT ;
   pGi = &g_GlobalInfo ;
   pBondInfo = &pGi->ptmBondInfo ;
   pPtmSrcBondHdr = &pGi->ptmBondHdr[0] ;

   //printk ("bcmxtmrt: ptm tx priority %d \n", ulPtmPrioIdx) ;

   PMON_US_LOG(1) ;

   len = *pLen ;

   if ( *ppNBuffSkb == NULL) {

      struct fkbuff *fkb = PNBUFF_2_FKBUFF(*ppNBuff);
      headroom = fkb_headroom (fkb) ;

      if (headroom >= minheadroom) {
         frags = constructPtmBondHdr (pDevCtx, ulPtmPrioIdx, len) ;

         if (frags != 0) {
             PMON_US_LOG(2) ;
             *ppData = fkb_push (fkb, minheadroom) ;
             *pLen   = len + minheadroom ;
             pPtmBondHdr = (XtmRtPtmTxBondHeader *) *ppData ;
             PMON_US_LOG(3) ;
             u16cpy (pPtmBondHdr, pPtmSrcBondHdr, sizeof (XtmRtPtmTxBondHeader) * frags) ;
             PMON_US_LOG(4) ;
         }
      }
      else
         printk(CARDNAME "bcmxtmrt_xmit: FKB not enough headroom.\n") ;
   }
   else {
      struct sk_buff *skb = *ppNBuffSkb ;
      headroom = skb_headroom (skb) ;

      if (headroom < minheadroom) {
         struct sk_buff *skb2 = skb_realloc_headroom(skb, minheadroom) ;
#if 0
         printk ("bcmxtmrt: Warning!!, headroom (%d) is less than min headroom (%d) \n",
               headroom, minheadroom) ;
#endif
         dev_kfree_skb_any(skb);
         if (skb2 == NULL) {
            printk (CARDNAME ": Fatal!!, NULL Skb \n") ;
            skb = NULL ;
         }
         else
            skb = skb2 ;
      }

      if( skb ) {
         frags = constructPtmBondHdr (pDevCtx, ulPtmPrioIdx, len) ;

         if (frags != 0) {
             PMON_US_LOG(2) ;
             *ppData = skb_push (skb, minheadroom) ;
             *pLen   = len + minheadroom ;
             pPtmBondHdr = (XtmRtPtmTxBondHeader *) *ppData ;
             PMON_US_LOG(3) ;
             u16cpy (pPtmBondHdr, pPtmSrcBondHdr, sizeof (XtmRtPtmTxBondHeader) * frags) ;
             PMON_US_LOG(4) ;
         }
      }

      *ppNBuffSkb = skb ;
      *ppNBuff = SKBUFF_2_PNBUFF(skb) ;
   }

   PMON_US_LOG(5) ;
   PMON_US_END(5) ;

   return frags ;
} /* bcmxtmrt_ptmbond_add_hdr */


/***************************************************************************
 * Function Name: bcmxtmrt_ptmbond_calculate_link_weights
 * Description  : Calculates the ptm bonding link weights, based on the
 *                link availability.
 * Returns      : None.
 ***************************************************************************/
int bcmxtmrt_ptmbond_calculate_link_weights (PBCMXTMRT_DEV_CONTEXT pDevCtx) 
{
   int i, max, min, nRet = 0 ;
   int quot, mod, quotFromMod, ratioMin, ratioMax ;
   XtmRtPtmBondInfo      *pBondInfo ;
   PBCMXTMRT_GLOBAL_INFO pGi = &g_GlobalInfo ;

   pBondInfo = &pGi->ptmBondInfo ;

   for (i=0; i< MAX_BOND_PORTS; i++) {
      if (pDevCtx->ulLinkUsRate[i] != 0)
         pBondInfo->ulConfLinkUsWt [i] = pDevCtx->ulLinkUsRate[i]/8 ;  /* bytes/sec */
      else
         pBondInfo->ulConfLinkUsWt [i] = 0 ;
   }

   memcpy (&pBondInfo->ulLinkUsWt[0], &pBondInfo->ulConfLinkUsWt[0], (MAX_BOND_PORTS*sizeof (UINT32))) ;

   /* Calculate the wt port distribution */

   if (pDevCtx->ulLinkUsRate[0] >= pDevCtx->ulLinkUsRate[1]) {
      max = 0; min = 1 ;
   }
   else {
      max = 1; min = 0 ;
   }

   if (pDevCtx->ulLinkUsRate[max] != 0) {

      if (pDevCtx->ulLinkUsRate[min] != 0) {
         quot = pDevCtx->ulLinkUsRate[max]/pDevCtx->ulLinkUsRate[min] ;
         mod  = pDevCtx->ulLinkUsRate[max]%pDevCtx->ulLinkUsRate[min] ;
         quotFromMod = (mod*10)/pDevCtx->ulLinkUsRate[min];
         if ((mod==0) || (quotFromMod==0)) {
            ratioMax = quot ;
            ratioMin = 0x1 ;
         }
         else {
            ratioMax = (quot*10)+quotFromMod ;
            ratioMin = 0x1*10 ;
         }

         pBondInfo->totalWtPortDist = ratioMax+ratioMin ;
         if (pBondInfo->totalWtPortDist > MAX_WT_PORT_DIST) {
            nRet = -ENOBUFS ;
            goto _End ;
         }

         quot = (pBondInfo->totalWtPortDist/ratioMin) ;

         for (i=0;i<pBondInfo->totalWtPortDist;i++) {
            if (((i%quot)==0) && ratioMin != 0) {
               pBondInfo->u8ConfWtPortDist[i] = min ;
               ratioMin--;
            }
            else
               pBondInfo->u8ConfWtPortDist[i] = max ;
         }
      }
      else {
         pBondInfo->totalWtPortDist = 0x1 ;
         pBondInfo->u8ConfWtPortDist[0]    = max ;
      }
   }
   else {
      if (pDevCtx->ulLinkUsRate[min] != 0) {
         pBondInfo->totalWtPortDist = 0x1 ;
         pBondInfo->u8ConfWtPortDist[0]    = min ;
      }
      else {
         pBondInfo->totalWtPortDist = 0x0 ;
         pBondInfo->u8ConfWtPortDist[0]    = 0xFF ;
      }
   }

   pBondInfo->ulCurrWtPortDistStartIndex = 0 ;
   pBondInfo->ulCurrWtPortDistRunIndex   = pBondInfo->ulCurrWtPortDistStartIndex ;
   pBondInfo->ulCurrWtTotalIterationsBeforeReset   = 0 ;

_End :
   return (nRet) ;
}

/***************************************************************************
 * Function Name: ProcTxBondInfo
 * Description  : Displays information about Bonding Tx side counters.
 *                Currently for PTM bonding.
 * Returns      : 0 if successful or error status
 ***************************************************************************/
 int ProcTxBondInfo (char *page, char **start, off_t off, int cnt,
    int *eof, void *data)
{
    PBCMXTMRT_GLOBAL_INFO pGi = &g_GlobalInfo;
    PBCMXTMRT_DEV_CONTEXT pDevCtx;
    XtmRtPtmBondInfo *pBondInfo = &pGi->ptmBondInfo ;
    volatile XtmRtPtmTxBondHeader *pPtmHeader;
    UINT32 i ;
    int sz = 0, port, eopStatus, fragSize ;

    if (pGi->bondConfig.sConfig.ptmBond == BC_PTM_BONDING_ENABLE) {

       pPtmHeader = &pGi->ptmBondHdr [0] ;

       sz += sprintf(page + sz, "\nPTM Tx Bonding Information \n") ;
       sz += sprintf(page + sz, "\n========================== \n") ;

       sz += sprintf(page + sz, "\nPTM Header Information") ; 
       
       for (i=0; i<XTMRT_PTM_BOND_MAX_FRAG_PER_PKT; i++) {
          
          port       = pPtmHeader[i].sVal.portSel ;
          eopStatus  = pPtmHeader[i].sVal.PktEop ;
          fragSize   = pPtmHeader[i].sVal.FragSize ;
          fragSize   -= (XTMRT_PTM_BOND_FRAG_HDR_SIZE+
                        XTMRT_PTM_CRC_SIZE) ;
          if (eopStatus == 1) {
             sz += sprintf(page + sz, "\nFragment[%u]: port-%d, eopStatus-%d, size-%d \n",
                           (unsigned int)i, port, eopStatus, fragSize-ETH_FCS_LEN) ;
             break ;
          }
          else {
             sz += sprintf(page + sz, "\nFragment[%u]: port-%u, eopStatus-%u, size-%u \n",
                           (unsigned int)i, port, eopStatus, fragSize) ;
          }
       } /* for (i) */

       for( i = 0; i < MAX_DEV_CTXS; i++ )
       {
          pDevCtx = pGi->pDevCtxs[i];
          if ( pDevCtx != (PBCMXTMRT_DEV_CONTEXT) NULL )
          {
             sz += sprintf(page + sz, "dev: %s, ActivePortMask: %u \n",
                   pDevCtx->pDev->name, (unsigned int) pDevCtx->ulPortDataMask) ;

          }
       }

       for( i = 0; i < MAX_BOND_PORTS; i++ )
       {
          sz += sprintf(page + sz, "Port %u ConfWt : %u CurrWt : %u\n",
                (unsigned int) i, (unsigned int) pBondInfo->ulConfLinkUsWt[i], (unsigned int) pBondInfo->ulLinkUsWt[i]) ;

       }

       sz += sprintf(page + sz, "totalWtPortDist : %u CurrWtPortDistStartIndex : %u "
             "CurrWtPortDistRunIndex : %u CurrBeforeReset : %u \n", (unsigned int) pBondInfo->totalWtPortDist, 
             (unsigned int) pBondInfo->ulCurrWtPortDistStartIndex, (unsigned int) pBondInfo->ulCurrWtPortDistRunIndex,
             (unsigned int) pBondInfo->ulCurrWtTotalIterationsBeforeReset) ;

       sz += sprintf(page + sz, "All Wt Port Distributions ==>") ;

       for( i = 0; i < pBondInfo->totalWtPortDist; i++ ) {
          sz += sprintf(page + sz, " %u,", pBondInfo->u8ConfWtPortDist[i]) ;
       }

       sz += sprintf(page + sz, "\n") ;
    }
    else {
       sz += sprintf(page + sz, "No Bonding Information \n") ;
    }

    *eof = 1;
    return( sz );
} /* ProcTxBondInfo */
