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
 *
 *  Broadcom IPsec SPU Driver Common API
 *  Description: Header file for IPSec SPU Device Driver
 *  File: spuext.h
 *  Author: Pavan Kumar
 *  Date: 11/16/2007
 *
 *****************************************************************************/
#ifndef _SPUEXT_H_
#define _SPUEXT_H_

#define UBSEC_EXPLICIT_IV                131072
#define UBSEC_USING_EXPLICIT_IV(f)       ( (f) & (UBSEC_EXPLICIT_IV) )
#define UBSEC_EXTCHIPINFO_EXPLICIT_IV    0x00001000
#define OPERATION_IPSEC_3DES_EXPLICIT_IV 0x4100
#define OPERATION_IPSEC_AES_EXPLICIT_IV  0x4200
#define BCM_OEM_4_FEATURES()             pExtChipInfo->Features\
                                         &= ~(UBSEC_EXTCHIPINFO_EXPLICIT_IV);
#define BCM_OEM_4_PDEVICE_FEATURES()     pDevice->Features\
                                         &= ~(UBSEC_EXTCHIPINFO_EXPLICIT_IV);
#define BCM_OEM_4_CHECK() if(UBSEC_USING_EXPLICIT_IV(at->flags)){ \
        if (!(features & UBSEC_EXTCHIPINFO_EXPLICIT_IV))        \
                return UBSEC_STATUS_NO_DEVICE;                  \
  }

#endif /* _SPUEXT_H_ */
