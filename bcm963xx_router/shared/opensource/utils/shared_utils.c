
/*
 * <:copyright-BRCM:2012:DUAL/GPL:standard
 * 
 *    Copyright (c) 2012 Broadcom Corporation
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
 */

#include "shared_utils.h"

#ifdef _CFE_                                                
#include "lib_types.h"
#include "lib_printf.h"
#include "lib_string.h"
#include "bcm_map.h"
#define printk  printf
#else // Linux
#include <linux/kernel.h>
#include <bcm_map_part.h>
#include <linux/string.h>
#endif


char *UtilGetChipName(char *buf, int len) {

    unsigned int chipId = (PERF->RevID & CHIP_ID_MASK) >> CHIP_ID_SHIFT;
    unsigned int revId;
    char *mktname = NULL;
    revId = (int) (PERF->RevID & REV_ID_MASK);

#if  defined (_BCM96818_) || defined(CONFIG_BCM96818)
   unsigned int var = (BRCM_VARIANT_REG & BRCM_VARIANT_REG_MASK) >> BRCM_VARIANT_REG_SHIFT;

    switch ((chipId << 8) | var) {
	case(0x681100):
		mktname = "6812B";
		break;
	case(0x681101):
		mktname = "6812R";
		break;
	case(0x681503):
		mktname = "6812GU";
		break;
	case(0x681500):
		mktname = "6818SR";
		break;
	case(0x681700):
		mktname = "6818G";
		break;
	case(0x681701):
		mktname = "6818GS";
		break;
	case(0x681501):
		mktname = "6818GR";
		break;
	case(0x681502):
		mktname = "6820IAD";
		break;
	default:
		mktname = NULL;
    }

#elif  defined (_BCM96828_) || defined(CONFIG_BCM96828)
#if defined(CHIP_VAR_MASK)
        unsigned int var = (PERF->RevID & CHIP_VAR_MASK) >> CHIP_VAR_SHIFT;
#endif
    switch ((chipId << 8) | var) {
	case(0x682100):
		mktname = "6821F";
		break;
	case(0x682101):
		mktname = "6821G";
		break;
	case(0x682200):
		mktname = "6822F";
		break;
	case(0x682201):
		mktname = "6822G";
		break;
	case(0x682800):
		mktname = "6828F";
		break;
	case(0x682801):
		mktname = "6828G";
		break;
	default:
		mktname = NULL;
		break;
    }
#endif

    if (mktname == NULL) {
	sprintf(buf,"%X%X",chipId,revId);
    } else {
        sprintf(buf,"%s_%X",mktname,revId);
    }
    return(buf);
}

int UtilGetChipIsPinCompatible(void) 
{

    int ret = 0;
#if  defined (_BCM96818_) || defined(CONFIG_BCM96818)
    unsigned int chipId = (PERF->RevID & CHIP_ID_MASK) >> CHIP_ID_SHIFT;
    unsigned int var = (BRCM_VARIANT_REG & BRCM_VARIANT_REG_MASK) >> BRCM_VARIANT_REG_SHIFT;
    unsigned int sw;
    sw =  ((chipId << 8) | var);
    switch (sw) {
	case(0x681503): //  "6812GU";
	case(0x681500): //  "6818SR";
	case(0x681501): //  "6818GR";
		ret = 1;
		break;
	default:
		ret = 0;
    }
#endif

    return(ret);
}
