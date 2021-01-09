/*TR69_FUNC.h*/

#ifndef TR69_FUNC_H
#define TR69_FUNC_H

#include "tsl_common.h"

#define TR69_RT_SUCCESS_VALUE_UNCHANGED 0x101
#define TR69_RT_SUCCESS_VALUE_CHANGED 0x102



/*InternetGatewayDevice*/
typedef struct st_InternetGatewayDevice_obj {
	 tsl_uint_t LANDeviceNumberOfEntries;
	 tsl_uint_t WANDeviceNumberOfEntries;
	 tsl_uint_t LogLevelNumberOfEntries;
	 tsl_char_t *X_AEI_COM_Physical_WAN;
}st_InternetGatewayDevice_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_InternetGatewayDevice_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_InternetGatewayDevice_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_InternetGatewayDevice_value(tsl_char_t *p_oid_name, st_InternetGatewayDevice_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_InternetGatewayDevice_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_InternetGatewayDevice_t *p_cur_data
 *	        st_InternetGatewayDevice_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_InternetGatewayDevice_value(tsl_char_t *p_oid_name, st_InternetGatewayDevice_t *p_cur_data, st_InternetGatewayDevice_t *p_new_data);


/*InternetGatewayDevice.DeviceInfo*/
typedef struct st_DeviceInfo_obj {
	 tsl_char_t *Manufacturer;
	 tsl_char_t *ManufactureOUI;
	 tsl_char_t *ModelName;
	 tsl_char_t *Description;
	 tsl_char_t *ProductClass;
	 tsl_char_t *SerialNumber;
	 tsl_char_t *HardwareVersion;
	 tsl_char_t *SoftwareVersion;
	 tsl_char_t *SpecVersion;
	 tsl_char_t *ProvisioningCode;
	 tsl_uint_t UpTime;
	 tsl_char_t *FirstUseTime;
}st_DeviceInfo_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_DeviceInfo_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.DeviceInfo
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_DeviceInfo_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_DeviceInfo_value(tsl_char_t *p_oid_name, st_DeviceInfo_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_DeviceInfo_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.DeviceInfo
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_DeviceInfo_t *p_cur_data
 *	        st_DeviceInfo_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_DeviceInfo_value(tsl_char_t *p_oid_name, st_DeviceInfo_t *p_cur_data, st_DeviceInfo_t *p_new_data);


/*InternetGatewayDevice.DeviceInfo.VendorConfigFile*/
typedef struct st_VendorConfigFile_obj {
	 tsl_char_t *Name;
	 tsl_char_t *Version;
	 tsl_char_t *Date;
	 tsl_char_t *Description;
}st_VendorConfigFile_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_VendorConfigFile_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.DeviceInfo.VendorConfigFile
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_VendorConfigFile_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_VendorConfigFile_value(tsl_char_t *p_oid_name, st_VendorConfigFile_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_VendorConfigFile_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.DeviceInfo.VendorConfigFile
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_VendorConfigFile_t *p_cur_data
 *	        st_VendorConfigFile_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_VendorConfigFile_value(tsl_char_t *p_oid_name, st_VendorConfigFile_t *p_cur_data, st_VendorConfigFile_t *p_new_data);


/*InternetGatewayDevice.DeviceConfig*/
typedef struct st_DeviceConfig_obj {
	 tsl_int_t EnableCWMP;
	 tsl_uint_t PeriodInformTime;
	 tsl_char_t *ConnectionRequestURL;
	 tsl_int_t X_AEI_COM_IPv6Enable;
	 tsl_char_t *X_AEI_COM_TransType;
}st_DeviceConfig_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_DeviceConfig_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.DeviceConfig
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_DeviceConfig_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_DeviceConfig_value(tsl_char_t *p_oid_name, st_DeviceConfig_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_DeviceConfig_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.DeviceConfig
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_DeviceConfig_t *p_cur_data
 *	        st_DeviceConfig_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_DeviceConfig_value(tsl_char_t *p_oid_name, st_DeviceConfig_t *p_cur_data, st_DeviceConfig_t *p_new_data);


/*InternetGatewayDevice.ManagementServer*/
typedef struct st_ManagementServer_obj {
	 tsl_char_t *URL;
	 tsl_char_t *Username;
	 tsl_char_t *Password;
	 tsl_int_t PeriodicInformEnable;
	 tsl_uint_t PeriodicInformInterval;
	 tsl_char_t *PeriodicInformTime;
	 tsl_char_t *ParameterKey;
	 tsl_char_t *ConnectionRequestURL;
	 tsl_char_t *ConnectionRequestUsername;
	 tsl_char_t *ConnectionRequestPassword;
	 tsl_int_t UpgradesManaged;
	 tsl_char_t *UDPConnectionRequestAddress;
	 tsl_int_t STUNEnable;
	 tsl_char_t *STUNServerAddress;
	 tsl_uint_t STUNServerPort;
	 tsl_char_t *STUNUsername;
	 tsl_char_t *STUNPassword;
	 tsl_int_t NATDetected;
}st_ManagementServer_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_ManagementServer_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.ManagementServer
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_ManagementServer_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_ManagementServer_value(tsl_char_t *p_oid_name, st_ManagementServer_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_ManagementServer_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.ManagementServer
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_ManagementServer_t *p_cur_data
 *	        st_ManagementServer_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_ManagementServer_value(tsl_char_t *p_oid_name, st_ManagementServer_t *p_cur_data, st_ManagementServer_t *p_new_data);


/*InternetGatewayDevice.Time*/
typedef struct st_Time_obj {
	 tsl_char_t *NTPServer1;
	 tsl_char_t *NTPServer2;
	 tsl_char_t *NTPServer3;
	 tsl_char_t *NTPServer4;
	 tsl_char_t *NTPServer5;
	 tsl_char_t *CurrentLocalTime;
	 tsl_char_t *LocalTimeZone;
	 tsl_char_t *LocalTimeZoneName;
	 tsl_int_t DaylightSavingsUsed;
	 tsl_char_t *DaylightSavingsStart;
	 tsl_char_t *DaylightSavingsEnd;
}st_Time_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_Time_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.Time
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_Time_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_Time_value(tsl_char_t *p_oid_name, st_Time_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_Time_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.Time
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_Time_t *p_cur_data
 *	        st_Time_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_Time_value(tsl_char_t *p_oid_name, st_Time_t *p_cur_data, st_Time_t *p_new_data);


/*InternetGatewayDevice.IPPingDiagnostics*/
typedef struct st_IPPingDiagnostics_obj {
	 tsl_char_t *DiagnosticsState;
	 tsl_char_t *Interface;
	 tsl_char_t *Host;
	 tsl_uint_t SuccessCount;
	 tsl_uint_t FailureCount;
}st_IPPingDiagnostics_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_IPPingDiagnostics_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.IPPingDiagnostics
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_IPPingDiagnostics_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_IPPingDiagnostics_value(tsl_char_t *p_oid_name, st_IPPingDiagnostics_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_IPPingDiagnostics_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.IPPingDiagnostics
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_IPPingDiagnostics_t *p_cur_data
 *	        st_IPPingDiagnostics_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_IPPingDiagnostics_value(tsl_char_t *p_oid_name, st_IPPingDiagnostics_t *p_cur_data, st_IPPingDiagnostics_t *p_new_data);


/*InternetGatewayDevice.LANDevice*/
typedef struct st_LANDevice_obj {
	 tsl_uint_t LANEthernetInterfaceNumberOfEntries;
}st_LANDevice_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_LANDevice_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LANDevice_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_LANDevice_value(tsl_char_t *p_oid_name, st_LANDevice_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_LANDevice_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LANDevice_t *p_cur_data
 *	        st_LANDevice_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_LANDevice_value(tsl_char_t *p_oid_name, st_LANDevice_t *p_cur_data, st_LANDevice_t *p_new_data);


/*InternetGatewayDevice.LANDevice.1.LANHostConfigManagement*/
typedef struct st_LANHostConfigManagement_obj {
	 tsl_uint_t IPInterfaceNumberOfEntries;
	 tsl_int_t DHCPServerEnable;
	 tsl_char_t *MinAddress;
	 tsl_char_t *MaxAddress;
	 tsl_int_t DHCPLeaseTime;
	 tsl_char_t *DNSServers;
}st_LANHostConfigManagement_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_LANHostConfigManagement_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANHostConfigManagement
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LANHostConfigManagement_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_LANHostConfigManagement_value(tsl_char_t *p_oid_name, st_LANHostConfigManagement_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_LANHostConfigManagement_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANHostConfigManagement
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LANHostConfigManagement_t *p_cur_data
 *	        st_LANHostConfigManagement_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_LANHostConfigManagement_value(tsl_char_t *p_oid_name, st_LANHostConfigManagement_t *p_cur_data, st_LANHostConfigManagement_t *p_new_data);


/*InternetGatewayDevice.LANDevice.1.LANHostConfigManagement.IPInterface*/
typedef struct st_IPInterface_obj {
	 tsl_int_t Enable;
	 tsl_char_t *IPInterfaceIPAddress;
	 tsl_char_t *IPInterfaceSubnetMask;
	 tsl_char_t *IPInterfaceAddressingType;
	 tsl_char_t *X_BROADCOM_COM_IfName;
	 tsl_int_t X_BROADCOM_COM_FirewallEnabled;
	 tsl_char_t *X_BROADCOM_COM_IPv6InterfaceAddress;
	 tsl_char_t *X_BROADCOM_COM_IPv6InterfaceAddressingType;
	 tsl_char_t *X_AEI_COM_IPv6ULAAddress;
	 tsl_char_t *X_AEI_COM_IPv6ULAAddressingType;
	 tsl_char_t *X_AEI_COM_IPv6LinkLocalAddress;
}st_IPInterface_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_IPInterface_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANHostConfigManagement.IPInterface
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_IPInterface_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_IPInterface_value(tsl_char_t *p_oid_name, st_IPInterface_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_IPInterface_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANHostConfigManagement.IPInterface
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_IPInterface_t *p_cur_data
 *	        st_IPInterface_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_IPInterface_value(tsl_char_t *p_oid_name, st_IPInterface_t *p_cur_data, st_IPInterface_t *p_new_data);


/*InternetGatewayDevice.LANDevice.1.X_BROADCOM_COM_IPv6LANHostConfigManagement*/
typedef struct st_X_BROADCOM_COM_IPv6LANHostConfigManagement_obj {
	 tsl_int_t Enable;
	 tsl_char_t *X_AEI_COM_IPv6LinkLocalAddress;
	 tsl_int_t DHCPv6ServerEnable;
	 tsl_int_t StatefulDHCPv6Server;
	 tsl_char_t *MinInterfaceID;
	 tsl_char_t *MaxInterfaceID;
	 tsl_int_t DHCPv6LeaseTime;
	 tsl_char_t *IPv6DomainName;
	 tsl_char_t *IPv6DNSConfigType;
	 tsl_char_t *IPv6DNSServers;
	 tsl_char_t *IPv6DNSWANConnection;
	 tsl_int_t RADVDEnabled;
	 tsl_char_t *X_AEI_COM_IPv6DHCPReqManner;
	 tsl_char_t *X_AEI_COM_IPv6RAConfigType;
	 tsl_uint_t X_AEI_COM_IPv6RALifetime;
	 tsl_char_t *IPv6PDWANConnection;
	 tsl_int_t IPv6ULAPrefixEnabled;
	 tsl_char_t *IPv6ULAPrefix;
	 tsl_uint_t X_AEI_COM_IPv6SubnetNum;
	 tsl_uint_t X_AEI_COM_IPv6SubnetNumRsv6rdWan;
	 tsl_char_t *X_AEI_COM_IPv6CurrPrefixID;
	 tsl_char_t *X_AEI_COM_IPv6LastPrefixID;
	 tsl_char_t *X_AEI_COM_IPv6CurrULAPrefixID;
	 tsl_char_t *X_AEI_COM_IPv6LastULAPrefixID;
	 tsl_uint_t IPv6InterfaceNumberOfEntries;
}st_X_BROADCOM_COM_IPv6LANHostConfigManagement_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_X_BROADCOM_COM_IPv6LANHostConfigManagement_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.X_BROADCOM_COM_IPv6LANHostConfigManagement
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_BROADCOM_COM_IPv6LANHostConfigManagement_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_X_BROADCOM_COM_IPv6LANHostConfigManagement_value(tsl_char_t *p_oid_name, st_X_BROADCOM_COM_IPv6LANHostConfigManagement_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_X_BROADCOM_COM_IPv6LANHostConfigManagement_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.X_BROADCOM_COM_IPv6LANHostConfigManagement
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_BROADCOM_COM_IPv6LANHostConfigManagement_t *p_cur_data
 *	        st_X_BROADCOM_COM_IPv6LANHostConfigManagement_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_X_BROADCOM_COM_IPv6LANHostConfigManagement_value(tsl_char_t *p_oid_name, st_X_BROADCOM_COM_IPv6LANHostConfigManagement_t *p_cur_data, st_X_BROADCOM_COM_IPv6LANHostConfigManagement_t *p_new_data);


/*InternetGatewayDevice.LANDevice.1.X_BROADCOM_COM_IPv6LANHostConfigManagement.X_BROADCOM_COM_MldSnoopingConfig*/
typedef struct st_X_BROADCOM_COM_MldSnoopingConfig_obj {
	 tsl_int_t Enable;
	 tsl_char_t *Mode;
}st_X_BROADCOM_COM_MldSnoopingConfig_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_X_BROADCOM_COM_MldSnoopingConfig_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.X_BROADCOM_COM_IPv6LANHostConfigManagement.X_BROADCOM_COM_MldSnoopingConfig
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_BROADCOM_COM_MldSnoopingConfig_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_X_BROADCOM_COM_MldSnoopingConfig_value(tsl_char_t *p_oid_name, st_X_BROADCOM_COM_MldSnoopingConfig_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_X_BROADCOM_COM_MldSnoopingConfig_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.X_BROADCOM_COM_IPv6LANHostConfigManagement.X_BROADCOM_COM_MldSnoopingConfig
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_BROADCOM_COM_MldSnoopingConfig_t *p_cur_data
 *	        st_X_BROADCOM_COM_MldSnoopingConfig_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_X_BROADCOM_COM_MldSnoopingConfig_value(tsl_char_t *p_oid_name, st_X_BROADCOM_COM_MldSnoopingConfig_t *p_cur_data, st_X_BROADCOM_COM_MldSnoopingConfig_t *p_new_data);


/*InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig*/
typedef struct st_LANEthernetInterfaceConfig_obj {
	 tsl_int_t Enable;
	 tsl_char_t *Status;
	 tsl_char_t *MACAddress;
}st_LANEthernetInterfaceConfig_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_LANEthernetInterfaceConfig_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANEthernetInterfaceConfig
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LANEthernetInterfaceConfig_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_LANEthernetInterfaceConfig_value(tsl_char_t *p_oid_name, st_LANEthernetInterfaceConfig_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_LANEthernetInterfaceConfig_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANEthernetInterfaceConfig
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LANEthernetInterfaceConfig_t *p_cur_data
 *	        st_LANEthernetInterfaceConfig_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_LANEthernetInterfaceConfig_value(tsl_char_t *p_oid_name, st_LANEthernetInterfaceConfig_t *p_cur_data, st_LANEthernetInterfaceConfig_t *p_new_data);


/*InternetGatewayDevice.LANDevice.1.LANEthernetInterfaceConfig.1.Stats*/
typedef struct st_Stats_obj {
	 tsl_uint_t BytesSent;
	 tsl_uint_t BytesReceived;
	 tsl_uint_t PacketsSent;
	 tsl_uint_t PacketsReceived;
}st_Stats_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_Stats_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANEthernetInterfaceConfig.i.Stats
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_Stats_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_Stats_value(tsl_char_t *p_oid_name, st_Stats_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_Stats_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANEthernetInterfaceConfig.i.Stats
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_Stats_t *p_cur_data
 *	        st_Stats_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_Stats_value(tsl_char_t *p_oid_name, st_Stats_t *p_cur_data, st_Stats_t *p_new_data);


/*InternetGatewayDevice.LANDevice.1.Hosts*/
typedef struct st_Hosts_obj {
	 tsl_uint_t HostNumberOfEntries;
}st_Hosts_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_Hosts_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.Hosts
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_Hosts_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_Hosts_value(tsl_char_t *p_oid_name, st_Hosts_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_Hosts_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.Hosts
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_Hosts_t *p_cur_data
 *	        st_Hosts_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_Hosts_value(tsl_char_t *p_oid_name, st_Hosts_t *p_cur_data, st_Hosts_t *p_new_data);


/*InternetGatewayDevice.LANDevice.1.Hosts.Host*/
typedef struct st_Host_obj {
	 tsl_char_t *MACAddress;
}st_Host_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_Host_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.Hosts.Host
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_Host_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_Host_value(tsl_char_t *p_oid_name, st_Host_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_Host_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.Hosts.Host
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_Host_t *p_cur_data
 *	        st_Host_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_Host_value(tsl_char_t *p_oid_name, st_Host_t *p_cur_data, st_Host_t *p_new_data);


/*InternetGatewayDevice.LANDevice.1.LANPDConfigManagement*/
typedef struct st_LANPDConfigManagement_obj {
	 tsl_int_t Enable;
	 tsl_int_t IPv6PDDelegateEnable;
	 tsl_uint_t IPv6MaxSubPDNumber;
	 tsl_uint_t IPv6SubPDlength;
	 tsl_uint_t IPv6SubPDlengthbackup;
	 tsl_char_t *IPv6PDbackup;
	 tsl_uint_t LanPDInstanceNumberOfEntries;
}st_LANPDConfigManagement_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_LANPDConfigManagement_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANPDConfigManagement
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LANPDConfigManagement_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_LANPDConfigManagement_value(tsl_char_t *p_oid_name, st_LANPDConfigManagement_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_LANPDConfigManagement_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANPDConfigManagement
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LANPDConfigManagement_t *p_cur_data
 *	        st_LANPDConfigManagement_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_LANPDConfigManagement_value(tsl_char_t *p_oid_name, st_LANPDConfigManagement_t *p_cur_data, st_LANPDConfigManagement_t *p_new_data);


/*InternetGatewayDevice.LANDevice.1.LANPDConfigManagement.LanPDInstance*/
typedef struct st_LanPDInstance_obj {
	 tsl_int_t Enable;
	 tsl_char_t *IPv6PD;
	 tsl_int_t IPv6PDPltime;
	 tsl_int_t IPv6PDVltime;
	 tsl_uint_t IPv6PDLeasetime;
	 tsl_char_t *IPv6DUID;
	 tsl_char_t *IPv6linkaddress;
	 tsl_char_t *IPv6HostName;
}st_LanPDInstance_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_LanPDInstance_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANPDConfigManagement.LanPDInstance
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LanPDInstance_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_LanPDInstance_value(tsl_char_t *p_oid_name, st_LanPDInstance_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_LanPDInstance_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LANDevice.i.LANPDConfigManagement.LanPDInstance
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LanPDInstance_t *p_cur_data
 *	        st_LanPDInstance_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_LanPDInstance_value(tsl_char_t *p_oid_name, st_LanPDInstance_t *p_cur_data, st_LanPDInstance_t *p_new_data);


/*InternetGatewayDevice.WANDevice*/
typedef struct st_WANDevice_obj {
	 tsl_uint_t WANConnectionNumberOfEntries;
}st_WANDevice_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_WANDevice_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANDevice_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_WANDevice_value(tsl_char_t *p_oid_name, st_WANDevice_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_WANDevice_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANDevice_t *p_cur_data
 *	        st_WANDevice_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_WANDevice_value(tsl_char_t *p_oid_name, st_WANDevice_t *p_cur_data, st_WANDevice_t *p_new_data);


/*InternetGatewayDevice.WANDevice.1.WANCommonInterfaceConfig*/
typedef struct st_WANCommonInterfaceConfig_obj {
	 tsl_int_t EnabledForInternet;
	 tsl_char_t *WANAccessType;
	 tsl_uint_t TotalBytesSent;
	 tsl_uint_t TotalBytesReceived;
	 tsl_uint_t TotalPacketsSent;
	 tsl_uint_t TotalPacketsReceived;
}st_WANCommonInterfaceConfig_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_WANCommonInterfaceConfig_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANCommonInterfaceConfig
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANCommonInterfaceConfig_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_WANCommonInterfaceConfig_value(tsl_char_t *p_oid_name, st_WANCommonInterfaceConfig_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_WANCommonInterfaceConfig_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANCommonInterfaceConfig
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANCommonInterfaceConfig_t *p_cur_data
 *	        st_WANCommonInterfaceConfig_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_WANCommonInterfaceConfig_value(tsl_char_t *p_oid_name, st_WANCommonInterfaceConfig_t *p_cur_data, st_WANCommonInterfaceConfig_t *p_new_data);


/*InternetGatewayDevice.WANDevice.1.WANConnectionDevice*/
typedef struct st_WANConnectionDevice_obj {
	 tsl_uint_t WANIPConnectionNumberOfEntries;
	 tsl_uint_t WANPPPConnectionNumberOfEntries;
}st_WANConnectionDevice_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_WANConnectionDevice_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANConnectionDevice
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANConnectionDevice_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_WANConnectionDevice_value(tsl_char_t *p_oid_name, st_WANConnectionDevice_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_WANConnectionDevice_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANConnectionDevice
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANConnectionDevice_t *p_cur_data
 *	        st_WANConnectionDevice_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_WANConnectionDevice_value(tsl_char_t *p_oid_name, st_WANConnectionDevice_t *p_cur_data, st_WANConnectionDevice_t *p_new_data);


/*InternetGatewayDevice.WANDevice.1.WANConnectionDevice.1.WANIPConnection*/
typedef struct st_WANIPConnection_obj {
	 tsl_int_t Enable;
	 tsl_int_t Reset;
	 tsl_uint_t Uptime;
	 tsl_char_t *X_AEI_COM_LLA_DAD;
	 tsl_char_t *ConnectionStatus;
	 tsl_char_t *connectionType;
	 tsl_int_t NATEnabled;
	 tsl_char_t *AddressingType;
	 tsl_char_t *ExternalIPAddress;
	 tsl_char_t *SubnetMask;
	 tsl_char_t *DefaultGateway;
	 tsl_char_t *DNSServers;
	 tsl_uint_t MaxMTUSize;
	 tsl_char_t *X_BROADCOM_COM_IfName;
	 tsl_int_t X_BROADCOM_COM_IPv6Enabled;
	 tsl_int_t X_BROADCOM_COM_FirewallEnabled;
	 tsl_int_t X_BROADCOM_COM_IPv4Enabled;
	 tsl_int_t X_BROADCOM_COM_UnnumberedModel;
	 tsl_char_t *X_BROADCOM_COM_IPv6ConnStatus;
	 tsl_char_t *X_BROADCOM_COM_IPv6AddressingType;
	 tsl_char_t *X_BROADCOM_COM_ExternalIPv6Address;
	 tsl_char_t *X_BROADCOM_COM_DefaultIPv6RouteSource;
	 tsl_char_t *X_BROADCOM_COM_DefaultIPv6Gateway;
	 tsl_char_t *X_BROADCOM_COM_IPv6DNSServers;
	 tsl_int_t X_BROADCOM_COM_IPv6PrefixDelegationEnabled;
	 tsl_char_t *X_BROADCOM_COM_IPv6SitePrefix;
	 tsl_char_t *X_AEI_COM_IPv6SitePrefix_BackUp;
	 tsl_int_t X_BROADCOM_COM_IPv6SitePrefixPltime;
	 tsl_int_t X_BROADCOM_COM_IPv6SitePrefixVltime;
	 tsl_uint_t X_BROADCOM_COM_Dhcp6cPid;
	 tsl_int_t X_BROADCOM_COM_MLDEnabled;
	 tsl_char_t *X_BROADCOM_COM_IPv6SitePrefixT1;
	 tsl_char_t *X_BROADCOM_COM_IPv6SitePrefixT2;
	 tsl_char_t *X_BROADCOM_COM_IPv6DNSSearchList;
	 tsl_int_t X_BROADCOM_COM_MBIT;
	 tsl_int_t X_BROADCOM_COM_OBIT;
	 tsl_uint_t X_BROADCOM_COM_TMP_RALIFETIME;
	 tsl_int_t X_AEI_COM_IPv6DataEnabled;
	 tsl_char_t *X_AEI_COM_TransType;
	 tsl_char_t *X_AEI_COM_IPv6rdStatus;
	 tsl_char_t *X_AEI_COM_IPv6rdPrefixType;
	 tsl_char_t *X_AEI_COM_IPv6rdBRIPv4Addresses;
	 tsl_char_t *X_AEI_COM_IPv6rdPrefix;
	 tsl_uint_t X_AEI_COM_IPv6rdPrefixLength;
	 tsl_uint_t X_AEI_COM_IPv6rdIPv4MaskLength;
	 tsl_uint_t X_AEI_COM_IPv6rdTunnelMTU;
	 tsl_char_t *X_AEI_COM_IPv6TunnelIfName;
	 tsl_char_t *X_AEI_COM_IPv6in4Status;
	 tsl_char_t *X_AEI_COM_IPv6in4LocalIPv4Address;
	 tsl_char_t *X_AEI_COM_IPv6in4LocalIPv6Address;
	 tsl_char_t *X_AEI_COM_IPv6in4RemoteIPv4Address;
	 tsl_char_t *X_AEI_COM_IPv6in4RemoteIPv6Address;
	 tsl_char_t *X_AEI_COM_IPv6in4Prefix;
	 tsl_int_t X_AEI_COM_IPv6in4PrefixLength;
	 tsl_char_t *X_AEI_COM_IPv6to4Status;
	 tsl_char_t *X_AEI_COM_IPv6to4ServerIPv6Address;
	 tsl_char_t *X_AEI_COM_IPv6LinkLocalAddress;
	 tsl_uint_t PortMappingNumberOfEntries;
}st_WANIPConnection_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_WANIPConnection_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANIPConnection_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_WANIPConnection_value(tsl_char_t *p_oid_name, st_WANIPConnection_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_WANIPConnection_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANIPConnection_t *p_cur_data
 *	        st_WANIPConnection_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_WANIPConnection_value(tsl_char_t *p_oid_name, st_WANIPConnection_t *p_cur_data, st_WANIPConnection_t *p_new_data);


/*InternetGatewayDevice.WANDevice.1.WANConnectionDevice.1.WANIPConnection.1.PortMapping*/
typedef struct st_PortMapping_obj {
	 tsl_int_t PortMappingEnabled;
	 tsl_uint_t PortMappingLeaseDuration;
	 tsl_uint_t ExternalPort;
	 tsl_uint_t InternalPort;
	 tsl_char_t *PortMappingProtocol;
}st_PortMapping_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_PortMapping_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.PortMapping
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_PortMapping_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_PortMapping_value(tsl_char_t *p_oid_name, st_PortMapping_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_PortMapping_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.PortMapping
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_PortMapping_t *p_cur_data
 *	        st_PortMapping_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_PortMapping_value(tsl_char_t *p_oid_name, st_PortMapping_t *p_cur_data, st_PortMapping_t *p_new_data);


/*InternetGatewayDevice.WANDevice.1.WANConnectionDevice.1.WANPPPConnection*/
typedef struct st_WANPPPConnection_obj {
	 tsl_int_t Enable;
	 tsl_int_t Reset;
	 tsl_uint_t Uptime;
	 tsl_char_t *X_AEI_COM_LLA_DAD;
	 tsl_char_t *ConnectionStatus;
	 tsl_char_t *connectionType;
	 tsl_int_t NATEnabled;
	 tsl_char_t *AddressingType;
	 tsl_char_t *ExternalIPAddress;
	 tsl_char_t *SubnetMask;
	 tsl_char_t *DefaultGateway;
	 tsl_char_t *DNSServers;
	 tsl_uint_t MaxMTUSize;
	 tsl_char_t *X_BROADCOM_COM_IfName;
	 tsl_int_t X_BROADCOM_COM_IPv6Enabled;
	 tsl_int_t X_BROADCOM_COM_FirewallEnabled;
	 tsl_int_t X_BROADCOM_COM_IPv4Enabled;
	 tsl_int_t X_BROADCOM_COM_UnnumberedModel;
	 tsl_char_t *X_BROADCOM_COM_IPv6ConnStatus;
	 tsl_int_t X_BROADCOM_COM_IPv6PppUp;
	 tsl_char_t *X_BROADCOM_COM_IPv6AddressingType;
	 tsl_char_t *X_BROADCOM_COM_ExternalIPv6Address;
	 tsl_char_t *X_BROADCOM_COM_DefaultIPv6RouteSource;
	 tsl_char_t *X_BROADCOM_COM_DefaultIPv6Gateway;
	 tsl_char_t *X_BROADCOM_COM_IPv6DNSServers;
	 tsl_int_t X_BROADCOM_COM_IPv6PrefixDelegationEnabled;
	 tsl_char_t *X_BROADCOM_COM_IPv6SitePrefix;
	 tsl_char_t *X_AEI_COM_IPv6SitePrefix_BackUp;
	 tsl_int_t X_BROADCOM_COM_IPv6SitePrefixPltime;
	 tsl_int_t X_BROADCOM_COM_IPv6SitePrefixVltime;
	 tsl_uint_t X_BROADCOM_COM_Dhcp6cPid;
	 tsl_int_t X_BROADCOM_COM_MLDEnabled;
	 tsl_char_t *X_BROADCOM_COM_IPv6SitePrefixT1;
	 tsl_char_t *X_BROADCOM_COM_IPv6SitePrefixT2;
	 tsl_char_t *X_BROADCOM_COM_IPv6DNSSearchList;
	 tsl_int_t X_BROADCOM_COM_MBIT;
	 tsl_int_t X_BROADCOM_COM_OBIT;
	 tsl_uint_t X_BROADCOM_COM_TMP_RALIFETIME;
	 tsl_int_t X_AEI_COM_IPv6DataEnabled;
	 tsl_char_t *X_AEI_COM_TransType;
	 tsl_char_t *X_AEI_COM_IPv6rdStatus;
	 tsl_char_t *X_AEI_COM_IPv6rdPrefixType;
	 tsl_char_t *X_AEI_COM_IPv6rdBRIPv4Addresses;
	 tsl_char_t *X_AEI_COM_IPv6rdPrefix;
	 tsl_uint_t X_AEI_COM_IPv6rdPrefixLength;
	 tsl_uint_t X_AEI_COM_IPv6rdIPv4MaskLength;
	 tsl_uint_t X_AEI_COM_IPv6rdTunnelMTU;
	 tsl_char_t *X_AEI_COM_IPv6TunnelIfName;
	 tsl_char_t *X_AEI_COM_IPv6LinkLocalAddress;
	 tsl_uint_t PortMappingNumberOfEntries;
}st_WANPPPConnection_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_WANPPPConnection_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANPPPConnection_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_WANPPPConnection_value(tsl_char_t *p_oid_name, st_WANPPPConnection_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_WANPPPConnection_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANPPPConnection_t *p_cur_data
 *	        st_WANPPPConnection_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_WANPPPConnection_value(tsl_char_t *p_oid_name, st_WANPPPConnection_t *p_cur_data, st_WANPPPConnection_t *p_new_data);


/*InternetGatewayDevice.WANDevice.1.WANConnectionDevice.1.WANPPPConnection.1.PortMapping*/
typedef struct st_WANPPPConnection_PortMapping_obj {
	 tsl_int_t PortMappingEnabled;
	 tsl_uint_t PortMappingLeaseDuration;
	 tsl_uint_t ExternalPort;
	 tsl_uint_t InternalPort;
	 tsl_char_t *PortMappingProtocol;
}st_WANPPPConnection_PortMapping_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_WANPPPConnection_PortMapping_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.PortMapping
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANPPPConnection_PortMapping_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_WANPPPConnection_PortMapping_value(tsl_char_t *p_oid_name, st_WANPPPConnection_PortMapping_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_WANPPPConnection_PortMapping_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.PortMapping
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_WANPPPConnection_PortMapping_t *p_cur_data
 *	        st_WANPPPConnection_PortMapping_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_WANPPPConnection_PortMapping_value(tsl_char_t *p_oid_name, st_WANPPPConnection_PortMapping_t *p_cur_data, st_WANPPPConnection_PortMapping_t *p_new_data);


/*InternetGatewayDevice.X_BROADCOM_COM_IPv6Layer3Forwarding*/
typedef struct st_X_BROADCOM_COM_IPv6Layer3Forwarding_obj {
	 tsl_char_t *DefaultConnectionService;
	 tsl_uint_t ForwardNumberOfEntries;
}st_X_BROADCOM_COM_IPv6Layer3Forwarding_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_X_BROADCOM_COM_IPv6Layer3Forwarding_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.X_BROADCOM_COM_IPv6Layer3Forwarding
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_BROADCOM_COM_IPv6Layer3Forwarding_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_X_BROADCOM_COM_IPv6Layer3Forwarding_value(tsl_char_t *p_oid_name, st_X_BROADCOM_COM_IPv6Layer3Forwarding_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_X_BROADCOM_COM_IPv6Layer3Forwarding_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.X_BROADCOM_COM_IPv6Layer3Forwarding
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_BROADCOM_COM_IPv6Layer3Forwarding_t *p_cur_data
 *	        st_X_BROADCOM_COM_IPv6Layer3Forwarding_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_X_BROADCOM_COM_IPv6Layer3Forwarding_value(tsl_char_t *p_oid_name, st_X_BROADCOM_COM_IPv6Layer3Forwarding_t *p_cur_data, st_X_BROADCOM_COM_IPv6Layer3Forwarding_t *p_new_data);


/*InternetGatewayDevice.X_BROADCOM_COM_IPv6Layer3Forwarding.IPv6Forwarding*/
typedef struct st_IPv6Forwarding_obj {
	 tsl_int_t Enable;
	 tsl_char_t *Status;
	 tsl_char_t *Type;
	 tsl_char_t *PolicyRoutingName;
	 tsl_char_t *DestIPv6Address;
	 tsl_char_t *SourceIPv6Address;
	 tsl_char_t *SourceIfName;
	 tsl_int_t ForwardingPolicy;
	 tsl_char_t *GatewayIPv6Address;
	 tsl_char_t *Interface;
	 tsl_int_t ForwardingMetric;
	 tsl_uint_t MTU;
}st_IPv6Forwarding_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_IPv6Forwarding_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.X_BROADCOM_COM_IPv6Layer3Forwarding.IPv6Forwarding
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_IPv6Forwarding_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_IPv6Forwarding_value(tsl_char_t *p_oid_name, st_IPv6Forwarding_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_IPv6Forwarding_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.X_BROADCOM_COM_IPv6Layer3Forwarding.IPv6Forwarding
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_IPv6Forwarding_t *p_cur_data
 *	        st_IPv6Forwarding_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_IPv6Forwarding_value(tsl_char_t *p_oid_name, st_IPv6Forwarding_t *p_cur_data, st_IPv6Forwarding_t *p_new_data);


/*InternetGatewayDevice.X_AEI_COM_Firewall*/
typedef struct st_X_AEI_COM_Firewall_obj {
	 tsl_int_t Enable;
	 tsl_int_t X_AEI_COM_FIREWALL_TR69Enabled;
	 tsl_int_t X_AEI_COM_FIREWALL_STEALTHMODE;
	 tsl_int_t X_AEI_COM_FIREWALL_STATEFULEnabled;
	 tsl_char_t *X_AEI_COM_FIREWALL_LEVEL;
	 tsl_char_t *X_AEI_COM_FIREWALL_INVALUE;
	 tsl_char_t *X_AEI_COM_FIREWALL_OUTVALUE;
	 tsl_char_t *X_AEI_COM_FIREWALL_IP;
	 tsl_char_t *X_AEI_COM_FIREWALL_SET;
	 tsl_char_t *X_AEI_COM_FIREWALL_UNNUMIP_STR;
	 tsl_uint_t X_AEI_COM_MaxFirewallEntries;
	 tsl_uint_t X_AEI_COM_Firewall_RulesNumberOfEntries;
}st_X_AEI_COM_Firewall_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_X_AEI_COM_Firewall_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.X_AEI_COM_Firewall
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_AEI_COM_Firewall_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_X_AEI_COM_Firewall_value(tsl_char_t *p_oid_name, st_X_AEI_COM_Firewall_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_X_AEI_COM_Firewall_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.X_AEI_COM_Firewall
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_AEI_COM_Firewall_t *p_cur_data
 *	        st_X_AEI_COM_Firewall_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_X_AEI_COM_Firewall_value(tsl_char_t *p_oid_name, st_X_AEI_COM_Firewall_t *p_cur_data, st_X_AEI_COM_Firewall_t *p_new_data);


/*InternetGatewayDevice.X_AEI_COM_Firewall.X_AEI_COM_Firewall_Rules*/
typedef struct st_X_AEI_COM_Firewall_Rules_obj {
	 tsl_int_t Enable;
	 tsl_char_t *X_AEI_COM_FirewallServiceName;
	 tsl_char_t *X_AEI_COM_FirewallServiceType;
	 tsl_char_t *X_AEI_COM_FirewallServicePort;
	 tsl_uint_t X_AEI_COM_Protocol;
	 tsl_char_t *X_AEI_COM_SourceIP;
	 tsl_char_t *X_AEI_COM_SourcePort;
	 tsl_char_t *X_AEI_COM_DestIP;
	 tsl_char_t *X_AEI_COM_DestPort;
	 tsl_uint_t X_AEI_COM_TrafficType;
	 tsl_char_t *X_AEI_COM_TrafficInPolicy;
	 tsl_char_t *X_AEI_COM_TrafficOutPolicy;
	 tsl_uint_t X_AEI_COM_RuleId;
}st_X_AEI_COM_Firewall_Rules_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_X_AEI_COM_Firewall_Rules_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.X_AEI_COM_Firewall.X_AEI_COM_Firewall_Rules
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_AEI_COM_Firewall_Rules_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_X_AEI_COM_Firewall_Rules_value(tsl_char_t *p_oid_name, st_X_AEI_COM_Firewall_Rules_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_X_AEI_COM_Firewall_Rules_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.X_AEI_COM_Firewall.X_AEI_COM_Firewall_Rules
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_AEI_COM_Firewall_Rules_t *p_cur_data
 *	        st_X_AEI_COM_Firewall_Rules_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_X_AEI_COM_Firewall_Rules_value(tsl_char_t *p_oid_name, st_X_AEI_COM_Firewall_Rules_t *p_cur_data, st_X_AEI_COM_Firewall_Rules_t *p_new_data);


/*InternetGatewayDevice.QueueManagement*/
typedef struct st_QueueManagement_obj {
	 tsl_int_t Enable;
	 tsl_uint_t X_AEI_COM_CURRENT_MAXClassKey;
	 tsl_uint_t MaxClassificationEntries;
	 tsl_uint_t ClassificationNumberOfEntries;
}st_QueueManagement_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_QueueManagement_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.QueueManagement
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_QueueManagement_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_QueueManagement_value(tsl_char_t *p_oid_name, st_QueueManagement_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_QueueManagement_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.QueueManagement
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_QueueManagement_t *p_cur_data
 *	        st_QueueManagement_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_QueueManagement_value(tsl_char_t *p_oid_name, st_QueueManagement_t *p_cur_data, st_QueueManagement_t *p_new_data);


/*InternetGatewayDevice.QueueManagement.Classification*/
typedef struct st_Classification_obj {
	 tsl_int_t Enable;
	 tsl_char_t *X_AEI_COM_ClassName;
	 tsl_uint_t X_AEI_COM_ClassKey;
	 tsl_char_t *ClassInterface;
	 tsl_char_t *DestIP;
	 tsl_char_t *DestMask;
	 tsl_int_t DestIPExclude;
	 tsl_char_t *SourceIP;
	 tsl_char_t *SourceMask;
	 tsl_int_t SourceIPExclude;
	 tsl_int_t Protocol;
	 tsl_int_t ProtocolExclude;
	 tsl_int_t DestPort;
	 tsl_int_t DestPortRangeMax;
	 tsl_int_t DestPortExclude;
	 tsl_int_t SourcePort;
	 tsl_int_t SourcePortRangeMax;
	 tsl_int_t SourcePortExclude;
	 tsl_char_t *SourceMACAddress;
	 tsl_char_t *SourceMACMask;
	 tsl_int_t SourceMACExclude;
	 tsl_char_t *DestMACAddress;
	 tsl_char_t *DestMACMask;
	 tsl_int_t DestMACExclude;
	 tsl_int_t Ethertype;
	 tsl_int_t EthertypeExclude;
	 tsl_int_t DSCPCheck;
	 tsl_int_t DSCPExclude;
	 tsl_int_t DSCPMark;
	 tsl_int_t EthernetPriorityMark;
	 tsl_uint_t X_AEI_COM_Priority;
}st_Classification_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_Classification_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.QueueManagement.Classification
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_Classification_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_Classification_value(tsl_char_t *p_oid_name, st_Classification_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_Classification_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.QueueManagement.Classification
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_Classification_t *p_cur_data
 *	        st_Classification_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_Classification_value(tsl_char_t *p_oid_name, st_Classification_t *p_cur_data, st_Classification_t *p_new_data);


/*InternetGatewayDevice.LogLevel*/
typedef struct st_LogLevel_obj {
	 tsl_char_t *X_AEI_COM_ModuleName;
	 tsl_int_t Enable;
	 tsl_uint_t X_AEI_COM_LogLevel;
}st_LogLevel_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_LogLevel_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LogLevel
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LogLevel_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_LogLevel_value(tsl_char_t *p_oid_name, st_LogLevel_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_LogLevel_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.LogLevel
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_LogLevel_t *p_cur_data
 *	        st_LogLevel_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_LogLevel_value(tsl_char_t *p_oid_name, st_LogLevel_t *p_cur_data, st_LogLevel_t *p_new_data);


/*InternetGatewayDevice.X_AEI_COM_IPv6NUD*/
typedef struct st_X_AEI_COM_IPv6NUD_obj {
	 tsl_int_t Enable;
	 tsl_uint_t PayloadLength;
	 tsl_char_t *Result;
	 tsl_char_t *RTT;
}st_X_AEI_COM_IPv6NUD_t;


/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_get_X_AEI_COM_IPv6NUD_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.X_AEI_COM_IPv6NUD
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_AEI_COM_IPv6NUD_t *p_cur_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_get_X_AEI_COM_IPv6NUD_value(tsl_char_t *p_oid_name, st_X_AEI_COM_IPv6NUD_t *p_cur_data);

/**************************************************************************
 *	[FUNCTION NAME]:
 *	        tf69_func_set_X_AEI_COM_IPv6NUD_value
 *
 *	[DESCRIPTION]:
 *	        InternetGatewayDevice.X_AEI_COM_IPv6NUD
 *
 *	[PARAMETER]:
 *	        tsl_char_t *p_oid_name
 *	        st_X_AEI_COM_IPv6NUD_t *p_cur_data
 *	        st_X_AEI_COM_IPv6NUD_t *p_new_data
 *
 *	[RETURN]
 *              >= 0          SUCCESS
 *              <  0          ERROR
 **************************************************************************/

tsl_int_t tr69_func_set_X_AEI_COM_IPv6NUD_value(tsl_char_t *p_oid_name, st_X_AEI_COM_IPv6NUD_t *p_cur_data, st_X_AEI_COM_IPv6NUD_t *p_new_data);

#endif

