#ifndef TR69_ST_H
#define TR69_ST_H


tsl_char_t st_version[128] = "2010.1.22.1";

typedef tsl_int_t (*tr69_func_get_obj_t)(tsl_char_t *p_oid_name, tsl_void_t *p_cur_data);
typedef tsl_int_t (*tr69_func_set_obj_t)(tsl_char_t *p_oid_name, tsl_void_t *p_cur_data, tsl_void_t *p_new_data);
struct tr69_register_func{
	 tsl_char_t oid_name[256];
	tr69_func_get_obj_t get_func;
	tr69_func_set_obj_t set_func;
};


struct tr69_register_func tr69_regfunc_tb[]={
	{
	"InternetGatewayDevice", 
	(tr69_func_get_obj_t )tr69_func_get_InternetGatewayDevice_value,
	(tr69_func_set_obj_t )tr69_func_set_InternetGatewayDevice_value
	},

	{
	"InternetGatewayDevice.DeviceInfo", 
	(tr69_func_get_obj_t )tr69_func_get_DeviceInfo_value,
	(tr69_func_set_obj_t )tr69_func_set_DeviceInfo_value
	},

	{
	"InternetGatewayDevice.DeviceInfo.VendorConfigFile", 
	(tr69_func_get_obj_t )tr69_func_get_VendorConfigFile_value,
	(tr69_func_set_obj_t )tr69_func_set_VendorConfigFile_value
	},

	{
	"InternetGatewayDevice.DeviceConfig", 
	(tr69_func_get_obj_t )tr69_func_get_DeviceConfig_value,
	(tr69_func_set_obj_t )tr69_func_set_DeviceConfig_value
	},

	{
	"InternetGatewayDevice.ManagementServer", 
	(tr69_func_get_obj_t )tr69_func_get_ManagementServer_value,
	(tr69_func_set_obj_t )tr69_func_set_ManagementServer_value
	},

	{
	"InternetGatewayDevice.Time", 
	(tr69_func_get_obj_t )tr69_func_get_Time_value,
	(tr69_func_set_obj_t )tr69_func_set_Time_value
	},

	{
	"InternetGatewayDevice.IPPingDiagnostics", 
	(tr69_func_get_obj_t )tr69_func_get_IPPingDiagnostics_value,
	(tr69_func_set_obj_t )tr69_func_set_IPPingDiagnostics_value
	},

	{
	"InternetGatewayDevice.LANDevice", 
	(tr69_func_get_obj_t )tr69_func_get_LANDevice_value,
	(tr69_func_set_obj_t )tr69_func_set_LANDevice_value
	},

	{
	"InternetGatewayDevice.LANDevice.i.LANHostConfigManagement", 
	(tr69_func_get_obj_t )tr69_func_get_LANHostConfigManagement_value,
	(tr69_func_set_obj_t )tr69_func_set_LANHostConfigManagement_value
	},

	{
	"InternetGatewayDevice.LANDevice.i.LANHostConfigManagement.IPInterface", 
	(tr69_func_get_obj_t )tr69_func_get_IPInterface_value,
	(tr69_func_set_obj_t )tr69_func_set_IPInterface_value
	},

	{
	"InternetGatewayDevice.LANDevice.i.X_BROADCOM_COM_IPv6LANHostConfigManagement", 
	(tr69_func_get_obj_t )tr69_func_get_X_BROADCOM_COM_IPv6LANHostConfigManagement_value,
	(tr69_func_set_obj_t )tr69_func_set_X_BROADCOM_COM_IPv6LANHostConfigManagement_value
	},

	{
	"InternetGatewayDevice.LANDevice.i.X_BROADCOM_COM_IPv6LANHostConfigManagement.X_BROADCOM_COM_MldSnoopingConfig", 
	(tr69_func_get_obj_t )tr69_func_get_X_BROADCOM_COM_MldSnoopingConfig_value,
	(tr69_func_set_obj_t )tr69_func_set_X_BROADCOM_COM_MldSnoopingConfig_value
	},

	{
	"InternetGatewayDevice.LANDevice.i.LANEthernetInterfaceConfig", 
	(tr69_func_get_obj_t )tr69_func_get_LANEthernetInterfaceConfig_value,
	(tr69_func_set_obj_t )tr69_func_set_LANEthernetInterfaceConfig_value
	},

	{
	"InternetGatewayDevice.LANDevice.i.LANEthernetInterfaceConfig.i.Stats", 
	(tr69_func_get_obj_t )tr69_func_get_Stats_value,
	(tr69_func_set_obj_t )tr69_func_set_Stats_value
	},

	{
	"InternetGatewayDevice.LANDevice.i.Hosts", 
	(tr69_func_get_obj_t )tr69_func_get_Hosts_value,
	(tr69_func_set_obj_t )tr69_func_set_Hosts_value
	},

	{
	"InternetGatewayDevice.LANDevice.i.Hosts.Host", 
	(tr69_func_get_obj_t )tr69_func_get_Host_value,
	(tr69_func_set_obj_t )tr69_func_set_Host_value
	},

	{
	"InternetGatewayDevice.LANDevice.i.LANPDConfigManagement", 
	(tr69_func_get_obj_t )tr69_func_get_LANPDConfigManagement_value,
	(tr69_func_set_obj_t )tr69_func_set_LANPDConfigManagement_value
	},

	{
	"InternetGatewayDevice.LANDevice.i.LANPDConfigManagement.LanPDInstance", 
	(tr69_func_get_obj_t )tr69_func_get_LanPDInstance_value,
	(tr69_func_set_obj_t )tr69_func_set_LanPDInstance_value
	},

	{
	"InternetGatewayDevice.WANDevice", 
	(tr69_func_get_obj_t )tr69_func_get_WANDevice_value,
	(tr69_func_set_obj_t )tr69_func_set_WANDevice_value
	},

	{
	"InternetGatewayDevice.WANDevice.i.WANCommonInterfaceConfig", 
	(tr69_func_get_obj_t )tr69_func_get_WANCommonInterfaceConfig_value,
	(tr69_func_set_obj_t )tr69_func_set_WANCommonInterfaceConfig_value
	},

	{
	"InternetGatewayDevice.WANDevice.i.WANConnectionDevice", 
	(tr69_func_get_obj_t )tr69_func_get_WANConnectionDevice_value,
	(tr69_func_set_obj_t )tr69_func_set_WANConnectionDevice_value
	},

	{
	"InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection", 
	(tr69_func_get_obj_t )tr69_func_get_WANIPConnection_value,
	(tr69_func_set_obj_t )tr69_func_set_WANIPConnection_value
	},

	{
	"InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.PortMapping", 
	(tr69_func_get_obj_t )tr69_func_get_PortMapping_value,
	(tr69_func_set_obj_t )tr69_func_set_PortMapping_value
	},

	{
	"InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection", 
	(tr69_func_get_obj_t )tr69_func_get_WANPPPConnection_value,
	(tr69_func_set_obj_t )tr69_func_set_WANPPPConnection_value
	},

	{
	"InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.PortMapping", 
	(tr69_func_get_obj_t )tr69_func_get_WANPPPConnection_PortMapping_value,
	(tr69_func_set_obj_t )tr69_func_set_WANPPPConnection_PortMapping_value
	},

	{
	"InternetGatewayDevice.X_BROADCOM_COM_IPv6Layer3Forwarding", 
	(tr69_func_get_obj_t )tr69_func_get_X_BROADCOM_COM_IPv6Layer3Forwarding_value,
	(tr69_func_set_obj_t )tr69_func_set_X_BROADCOM_COM_IPv6Layer3Forwarding_value
	},

	{
	"InternetGatewayDevice.X_BROADCOM_COM_IPv6Layer3Forwarding.IPv6Forwarding", 
	(tr69_func_get_obj_t )tr69_func_get_IPv6Forwarding_value,
	(tr69_func_set_obj_t )tr69_func_set_IPv6Forwarding_value
	},

	{
	"InternetGatewayDevice.X_AEI_COM_Firewall", 
	(tr69_func_get_obj_t )tr69_func_get_X_AEI_COM_Firewall_value,
	(tr69_func_set_obj_t )tr69_func_set_X_AEI_COM_Firewall_value
	},

	{
	"InternetGatewayDevice.X_AEI_COM_Firewall.X_AEI_COM_Firewall_Rules", 
	(tr69_func_get_obj_t )tr69_func_get_X_AEI_COM_Firewall_Rules_value,
	(tr69_func_set_obj_t )tr69_func_set_X_AEI_COM_Firewall_Rules_value
	},

	{
	"InternetGatewayDevice.QueueManagement", 
	(tr69_func_get_obj_t )tr69_func_get_QueueManagement_value,
	(tr69_func_set_obj_t )tr69_func_set_QueueManagement_value
	},

	{
	"InternetGatewayDevice.QueueManagement.Classification", 
	(tr69_func_get_obj_t )tr69_func_get_Classification_value,
	(tr69_func_set_obj_t )tr69_func_set_Classification_value
	},

	{
	"InternetGatewayDevice.LogLevel", 
	(tr69_func_get_obj_t )tr69_func_get_LogLevel_value,
	(tr69_func_set_obj_t )tr69_func_set_LogLevel_value
	},

	{
	"InternetGatewayDevice.X_AEI_COM_IPv6NUD", 
	(tr69_func_get_obj_t )tr69_func_get_X_AEI_COM_IPv6NUD_value,
	(tr69_func_set_obj_t )tr69_func_set_X_AEI_COM_IPv6NUD_value
	},

};



#endif

