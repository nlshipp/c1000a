/***********************************************************************
 *
 *  Copyright (c) 2007-2010  Broadcom Corporation
 *  All Rights Reserved
 *
<:label-BRCM:2012:DUAL/GPL:standard

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
 *
 ************************************************************************/


#include "cms.h"
#include "cms_util.h"

#if defined(SUPPPORT_GPL_UNDEFINED)
static void *msgHandle = NULL;
static UBOOL8 keepLooping = TRUE;
#endif

void usage(UINT32 exitCode)
{
   printf("usage: ledctl [WAN] [on|off|red]\n");
   printf("    WAN is the only led that is controllable by this app right now.\n");
   printf("    WAN must be specified.\n");
   printf("    one of on, off, or red must be specified.\n");

   exit(exitCode);
}


void processWanLed(const char *state)
{
   if (!cmsUtl_strcmp(state, "on"))
   {
      cmsLed_setWanConnected();
   }
   else if (!cmsUtl_strcmp(state, "off"))
   {
      cmsLed_setWanDisconnected();
   }
   else if (!cmsUtl_strcmp(state, "red"))
   {
      cmsLed_setWanFailed();
   }
   else if(!cmsUtl_strcmp(state, "flashgreen"))
   {
        while (keepLooping)
        {
            cmsLed_setWanConnected();
            usleep(250*1000);
            cmsLed_setWanDisconnected();
            usleep(750*1000);
        }
   }
   else
   {
      usage(1);
   }

}


int main(int argc, char *argv[])
{
#if defined(SUPPPORT_GPL_UNDEFINED)
    CmsRet ret;
    cmsLog_init(EID_LEDCTL);
    cmsLog_setLevel(DEFAULT_LOG_LEVEL);

    if ((ret = cmsMsg_init(EID_LEDCTL, &msgHandle)) != CMSRET_SUCCESS)
    {
        cmsLog_error("msg initialization failed, ret=%d", ret);
        cmsLog_cleanup();
        return 0;
    }
#endif

   if (argc != 3)
   {
      usage(1);
   }
cmsLog_error("++++++++%s %s",argv[1],argv[2]);
   if (!cmsUtl_strcmp(argv[1], "WAN"))
   {
      processWanLed(argv[2]);
   }
   else
   {
      usage(1);
   }
#if defined(SUPPPORT_GPL_UNDEFINED)
    cmsMsg_cleanup(&msgHandle);
    cmsLog_cleanup();
#endif
   return 0;
}
