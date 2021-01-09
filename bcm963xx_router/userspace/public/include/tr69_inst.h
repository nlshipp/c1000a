#ifndef TR69_INST_H
#define TR69_INST_H

struct tr69_inst_numb_of_entries_s{
	char numb_of_entries_oid[256];
	char entries_oid[256];
};

struct tr69_inst_numb_of_entries_s tr69_inst_numb_tb[]={
	{
		"LANDeviceNumberOfEntries",
		"InternetGatewayDevice.LANDevice.i"
	},

	{
		"WANDeviceNumberOfEntries",
		"InternetGatewayDevice.WANDevice.i"
	},

	{
		"LogLevelNumberOfEntries",
		"InternetGatewayDevice.LogLevel.i"
	},

	{
		"LANEthernetInterfaceNumberOfEntries",
		"InternetGatewayDevice.LANDevice.i.LANEthernetInterfaceConfig.i"
	},

	{
		"IPInterfaceNumberOfEntries",
		"InternetGatewayDevice.LANDevice.i.LANHostConfigManagement.IPInterface.i"
	},

	{
		"IPv6InterfaceNumberOfEntries",
		""
	},

	{
		"HostNumberOfEntries",
		"InternetGatewayDevice.LANDevice.i.Hosts.Host.i"
	},

	{
		"LanPDInstanceNumberOfEntries",
		"InternetGatewayDevice.LANDevice.i.LANPDConfigManagement.LanPDInstance.i"
	},

	{
		"WANConnectionNumberOfEntries",
		"InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i"
	},

	{
		"WANIPConnectionNumberOfEntries",
		"InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i"
	},

	{
		"WANPPPConnectionNumberOfEntries",
		"InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i"
	},

	{
		"PortMappingNumberOfEntries",
		"InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANIPConnection.i.PortMapping.i"
	},

	{
		"PortMappingNumberOfEntries",
		"InternetGatewayDevice.WANDevice.i.WANConnectionDevice.i.WANPPPConnection.i.PortMapping.i"
	},

	{
		"ForwardNumberOfEntries",
		""
	},

	{
		"X_AEI_COM_Firewall_RulesNumberOfEntries",
		"InternetGatewayDevice.X_AEI_COM_Firewall.X_AEI_COM_Firewall_Rules.i"
	},

	{
		"ClassificationNumberOfEntries",
		"InternetGatewayDevice.QueueManagement.Classification.i"
	},

};

#endif
