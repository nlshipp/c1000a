#ifndef __AEI_UTILES_H__
#define __AEI_UTILES_H__
#include "mdm_object.h"
#ifdef AEI_LOCKOUT_AGAINST_BRUTE_FORCE_ATTACKS
UBOOL8 isCliLocked(UINT32 timeout);
CmsRet saveCliLockInfo(UINT32 max_retry, UINT32 curr_retry, UINT32 timeout);
CmsRet getCliLockInfo(UINT32* max_retry, UINT32* curr_retry, UINT32* timeout);
void saveCliLockUptime(char *appname);
#endif
int AEI_get_value_by_file(char *file, int size, char *value);
UINT16 AEI_get_interface_mtu(char *ifname);
void AEI_createFile(char *filename, char *content);
int AEI_removeFile(char *filename);
int AEI_isFileExist(char *filename);
int AEI_get_mac_addr(char *ifname, char *mac);
int AEI_convert_space(char *src,char *dst);
int AEI_convert_spec_chars(char *src,char *dst);
char* AEI_SpeciCharEncode(char *s, int len);
pid_t* find_pid_by_name( char* pidName);
int AEI_GetPid(char * command);
#if defined(AEI_CONFIG_JFFS) && defined(SUPPORT_GPL)
CmsRet AEI_writeDualPartition(char *imagePtr, UINT32 imageLen, void *msgHandle, int partition);
#endif

typedef enum
{
    AEI_WAN_ETH,
    AEI_WAN_ADSL,
    AEI_WAN_VDSL,
}AEIWanDevType;

#if defined(SUPPORT_GPL)
int AEI_save_syslog();

#endif
#endif
