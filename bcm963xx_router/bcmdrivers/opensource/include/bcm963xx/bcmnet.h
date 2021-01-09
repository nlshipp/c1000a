/*
    Copyright 2000-2011 Broadcom Corporation

    <:label-BRCM:2011:DUAL/GPL:standard
    
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

/***********************************************************************/
/*                                                                     */
/*   MODULE:  bcmnet.h                                                 */
/*   DATE:    05/16/02                                                 */
/*   PURPOSE: network interface ioctl definition                       */
/*                                                                     */
/***********************************************************************/
#ifndef _IF_NET_H_
#define _IF_NET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <linux/sockios.h>
#include "skb_defines.h"
#include "bcmPktDma_defines.h"

#define LINKSTATE_DOWN      0
#define LINKSTATE_UP        1

#ifndef IFNAMSIZ
#define IFNAMSIZ  16
#endif

/*---------------------------------------------------------------------*/
/* Ethernet Switch Type                                                */
/*---------------------------------------------------------------------*/
#define ESW_TYPE_UNDEFINED                  0
#define ESW_TYPE_BCM5325M                   1
#define ESW_TYPE_BCM5325E                   2
#define ESW_TYPE_BCM5325F                   3
#define ESW_TYPE_BCM53101                   4

/*
 * Ioctl definitions.
 */
/* Note1: The maximum device private ioctls allowed are 16 */
/* Note2: SIOCDEVPRIVATE is reserved */
enum {
    SIOCGLINKSTATE = SIOCDEVPRIVATE + 1,
    SIOCSCLEARMIBCNTR,
    SIOCMIBINFO,
    SIOCGENABLEVLAN,
    SIOCGDISABLEVLAN,
    SIOCGQUERYNUMVLANPORTS,
    SIOCGQUERYNUMPORTS,
    SIOCPORTMIRROR,
    SIOCSWANPORT,
    SIOCGWANPORT,
    SIOCETHCTLOPS,
    SIOCGPONIF,
    SIOCETHSWCTLOPS,
    SIOCGSWITCHPORT,
    SIOCGGMACPORT,
#if defined(AEI_VDSL_HPNA)
    SIOCSHPNAVLANID,
    SIOCSHPNAADMSTATE, /* adminstate and mode (LAN only , LAN+WAN) */
    SIOCGHPNAADMSTATE,
    SIOCGHPNALINKSTATUS,
    SIOCSHPNALINKSTATUS,
#endif
#if defined(AEI_VDSL_SMARTLED)
    SIOCINETTRAFFICBLINK,
    SIOCINETAMBERSTATE,
#endif
#if defined(AEI_VDSL_POWERSAVE)
    SIOCPOWERSAVE,
#endif
#if defined(AEI_VDSL_STATS_DIAG)
    SIOCGETDEVSTATS,
#endif
    SIOCLAST,
};

/* Various operations through the SIOCETHCTLOPS */
enum {
    ETHGETNUMTXDMACHANNELS = 0,
    ETHSETNUMTXDMACHANNELS,
    ETHGETNUMRXDMACHANNELS,
    ETHSETNUMRXDMACHANNELS,   
    ETHGETSOFTWARESTATS,
    ETHSETSPOWERUP,
    ETHSETSPOWERDOWN,
    ETHGETMIIREG,
    ETHSETMIIREG,
};

struct ethctl_data {
    /* ethctl ioctl operation */
    int op;
    /* number of DMA channels */
    int num_channels;
    /* return value for get operations */
    int ret_val;
    /* value for set operations */
    int val;
    unsigned char phy_addr;
    unsigned char phy_reg;
    /* flags to indicate to ioctl functions */
    unsigned char flags;
};

/* Indicates the Access Requested is for External Phy */
enum {
    ETHCTL_FLAG_ACCESS_INT_PHY,
    ETHCTL_FLAG_ACCESS_EXT_PHY,
    ETHCTL_FLAG_ACCESS_EXTSW_PHY,
};

/* Various operations through the SIOCGPONIF */
enum {
    GETFREEGEMIDMAP = 0,
    SETGEMIDMAP,
    GETGEMIDMAP,
    CREATEGPONVPORT,
    DELETEGPONVPORT,
    DELETEALLGPONVPORTS,
    SETMCASTGEMID,
};

#if (defined(CONFIG_BCM96816) || defined(CONFIG_BCM96818))
struct gponif_data{
    /* gponif ioctl operation */
    int op;
    /* GEM ID map for addgem and remgem operations */
    unsigned char gem_map_arr[CONFIG_BCM_MAX_GEM_PORTS];
    /* ifnumber for show all operation */
    int ifnumber;
    /* interface name for create, delete, addgem, remgem, and show ops */
    char ifname[IFNAMSIZ];
};
#endif
struct interface_data{
    char ifname[IFNAMSIZ];
    int switch_port_id;
};



/* The enet driver subdivides queue field (mark[4:0]) in the skb->mark into
   priority and channel */
/* priority = queue[2:0] (=>mark[2:0]) */
#define SKBMARK_Q_PRIO_S        (SKBMARK_Q_S)
#define SKBMARK_Q_PRIO_M        (0x07 << SKBMARK_Q_PRIO_S)
#define SKBMARK_GET_Q_PRIO(MARK) \
    ((MARK & SKBMARK_Q_PRIO_M) >> SKBMARK_Q_PRIO_S)
#define SKBMARK_SET_Q_PRIO(MARK, Q) \
    ((MARK & ~SKBMARK_Q_PRIO_M) | (Q << SKBMARK_Q_PRIO_S))
/* channel = queue[4:3] (=>mark[4:3]) */
#define SKBMARK_Q_CH_S          (SKBMARK_Q_S + 3)
#define SKBMARK_Q_CH_M          (0x03 << SKBMARK_Q_CH_S)
#define SKBMARK_GET_Q_CHANNEL(MARK) ((MARK & SKBMARK_Q_CH_M) >> SKBMARK_Q_CH_S)
#define SKBMARK_SET_Q_CHANNEL(MARK, CH) \
    ((MARK & ~SKBMARK_Q_CH_M) | (CH << SKBMARK_Q_CH_S))

#define SPEED_10MBIT        10000000
#define SPEED_100MBIT       100000000
#define SPEED_1000MBIT      1000000000

typedef struct IoctlMibInfo
{
    unsigned long ulIfLastChange;
    unsigned long ulIfSpeed;
    unsigned long ulIfDuplex;
} IOCTL_MIB_INFO, *PIOCTL_MIB_INFO;


#define MIRROR_INTF_SIZE    32
#define MIRROR_DIR_IN       0
#define MIRROR_DIR_OUT      1
#define MIRROR_DISABLED     0
#define MIRROR_ENABLED      1

typedef struct _MirrorCfg
{
    char szMonitorInterface[MIRROR_INTF_SIZE];
    char szMirrorInterface[MIRROR_INTF_SIZE];
    int nDirection;
    int nStatus;
#if defined(SUPPPORT_GPL)
    int vlanId;
#endif
#if (defined(CONFIG_BCM96816) || defined(CONFIG_BCM96818)) || defined(DMP_X_ITU_ORG_GPON_1)
    /* +1 is when CONFIG_BCM_MAX_GEM_PORTS is not a multiple of 8 */
    unsigned char nGemPortMaskArray[(CONFIG_BCM_MAX_GEM_PORTS/8)+1]; 
#endif
} MirrorCfg ;

#if defined(AEI_VDSL_POWERSAVE)
enum PowerSaveMode
{
    PWS_INVALID_MODE = -1,
    PWS_AUTO_POWER_DOWN = 0,
    PWS_ENERGY_EFFICIENT_ETHERNET,
    PWS_SHORT_CABLE,
    PWS_DEEP_GREEN
};

typedef struct
{
    int enable;
    enum PowerSaveMode mode;
} PowerSaveCfg;
#endif

#ifdef __cplusplus
}
#endif

#endif /* _IF_NET_H_ */
