/*
 *----------------------------------------------------------------
 *
 * aei_dns_switch_v4_and_v6.c
 *
 * <01, 30, 2013> <harrison>
 *
 * <supporting to switch dns server between v4 and v6 with no probe.
 * >
 *
 * Copyright (c) 2013 Actiontec Electronics Inc.
 * All rights reserved.
 *
 *----------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cms_params.h>

#include "dproxy.h"
#include "conf.h"
#include "dns_list.h"
#include "dns_io.h"
#include "aei_dns_switch_v4_and_v6.h"

#define NUM_IPV4_DNS1   0
#define NUM_IPV4_DNS2   1
#define NUM_IPV6_DNS1   2
#define NUM_IPV6_DNS2   3

#ifdef DESKTOP_LINUX
#define REAL_DNS_FYI_FILENAME   "./dns.real"
#else
#define REAL_DNS_FYI_FILENAME   "/var/fyi/sys/dns.real"
#endif

static DNSServerEntrySwitch dnsServersSwitch;
time_t dns_a_recover_time = 0;  // IPv4 primary DNS server switch back time
time_t dns_aaa_recover_time = 0; // IPv6 primary DNS server switch back time
int dproxy_active_a = 0;  // IPv4 dproxy enable 1, disable 0
int dproxy_active_aaa = 0; // IPv6 dproxy enable 1, disable 0
#ifdef AEI_PRIMARY_DNS_CHECK
#define CHECK_INIT      0  // primary DNS server active check init
#define CHECK_ENABLE    1  // primary DNS server active check enable
#define CHECK_STARTED   2  // primary DNS server active check already send checking packet 
int primary_check_a = CHECK_INIT;  //IPv4 primary DNS server active check
int primary_check_aaa = CHECK_INIT; //IPv6 primary DNS server active check
int primary_active_a = 0; //IPv4 primary DNS server active check result, active 1, unactive 0
int primary_active_aaa = 0; //IPv6 primary DNS server active check result, active 1, unactive 0
uint16_t probe_id_a = 0; //IPv4 primary DNS server active check id
uint16_t probe_id_aaa = 0; //IPv6 primary DNS server active check id
struct sockaddr_storage probe_addr_v4; //IPv4 DNS server need probe
struct sockaddr_storage probe_addr_v6; //IPv6 DNS server need probe
int dnsPrefer = 0;

char probe_pkt_a[35] =
{	0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x3, 'w','w','w', 0x9, 'm', 'i', 'c', 'r', 'o', 's','o','f','t', 0x3, 'c', 'o',
	'm', 0x0, 0x0, 0x1, 0x0, 0x1,
};


char probe_pkt_aaa[33] =
{	0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x4, 'i','p','v', '6',0x6, 'g', 'o', 'o',  'g','l', 'e', 0x3, 'c', 'o', 'm',
	0x0, 0x0, 0x1c, 0x0, 0x1,
};
#endif

/*
*  Function: load_switch_dns_servers_v4_and_v6
*
*  Description: 1. load dns server name from file /etc/resolv.conf
*             2. init probe address
*
*
*   Return Values: 1 sucess, 0 failed
*/
static int load_switch_dns_servers_v4_and_v6(void)
{
	FILE * fp;
	char line[256] = {0};
	char addr[INET6_ADDRSTRLEN] = {0};
    int isFirst = 0;

	//name server of resolv.conf is 127.0.0.1, it redirects ont dns query
	//to dns proxy to record dns query failed of ipHost PM
	if((fp = fopen(REAL_DNS_FYI_FILENAME, "r")) == NULL)
	{
		debug("Opend %s failed", REAL_DNS_FYI_FILENAME);
		// if dns.real does not exist, open /etc/resolv.conf
		if((fp = fopen("/etc/resolv.conf", "r")) == NULL)
		{
			debug_perror("Open /etc/resolv.conf failed");
			return 0;
		}
	}

	while(fgets(line, sizeof(line), fp))
	{
		if (sscanf(line, "nameserver %s", addr) == 1)
		{
			if ( strcmp( addr, "0.0.0.0") && strcmp( addr, "127.0.0.1")  && strcmp( addr, "::1"))
			{

				if(strstr(addr, ":") == NULL)
				{
					//IPv4
					if(!isFirst)
					{
                        dnsPrefer = 0;
                        isFirst = 1;
                    }
					if(strlen(dnsServersSwitch.dns[NUM_IPV4_DNS1]) == 0)
					{
						strncpy(dnsServersSwitch.dns[NUM_IPV4_DNS1], addr, INET6_ADDRSTRLEN-1);
#ifdef AEI_PRIMARY_DNS_CHECK
						probe_addr_v4.ss_family = AF_INET;
						((struct sockaddr_in *)&probe_addr_v4)->sin_port = PORT;
						inet_pton( AF_INET, addr, &(((struct sockaddr_in *)&probe_addr_v4)->sin_addr) );
#endif
					}
					else if(strlen(dnsServersSwitch.dns[NUM_IPV4_DNS2]) == 0)
					{
						strncpy(dnsServersSwitch.dns[NUM_IPV4_DNS2], addr, INET6_ADDRSTRLEN-1);
					}
					else
					{
						debug("dnsproxy supports a max of two ipv4 name servers.  "
						      "Additional ipv4 name servers are ignored.\n");
					}

				}
				else
				{
					//IPv6
					if(!isFirst)
					{
                        dnsPrefer = 1;
                        isFirst = 1;
                    }

					if(strlen(dnsServersSwitch.dns[NUM_IPV6_DNS1]) == 0)
					{
						strncpy(dnsServersSwitch.dns[NUM_IPV6_DNS1], addr, INET6_ADDRSTRLEN-1);
#ifdef AEI_PRIMARY_DNS_CHECK
						probe_addr_v6.ss_family = AF_INET6;
						((struct sockaddr_in6 *)&probe_addr_v6)->sin6_port = PORT;
						inet_pton( AF_INET6, addr, &(((struct sockaddr_in6 *)&probe_addr_v6)->sin6_addr) );
#endif
					}
					else if(strlen(dnsServersSwitch.dns[NUM_IPV6_DNS2]) == 0)
					{
						strncpy(dnsServersSwitch.dns[NUM_IPV6_DNS2], addr, INET6_ADDRSTRLEN-1);
					}
					else
					{
						debug("dnsproxy supports a max of two ipv6 name servers.  "
						      "Additional ipv6 name servers are ignored.\n");
					}
				}
			}
		}

	}
	fclose(fp);

	debug("dproxy: load nameserver %s, %s, %s, %s\n", dnsServersSwitch.dns[NUM_IPV4_DNS1], dnsServersSwitch.dns[NUM_IPV4_DNS2],
	      dnsServersSwitch.dns[NUM_IPV6_DNS1],dnsServersSwitch.dns[NUM_IPV6_DNS2]);

	if (strlen(dnsServersSwitch.dns[NUM_IPV4_DNS1]) == 0 && strlen(dnsServersSwitch.dns[NUM_IPV6_DNS1]) == 0)  /* not even a single valid nameserver found */
		return 0;
	return 1;
}

/*
*  Function: dns_switch_v4_and_v6_init
*
*  Description: 1. load dns server name from file /etc/resolv.conf
*             2. init all global parameter
*
*
*   Return Values: 1 sucess, 0 failed
*/
int dns_switch_v4_and_v6_init(void)
{

	debug("dns_switch_v4_and_v6_init");

	//set global parameters to default value
	memset(&dnsServersSwitch,0,sizeof(DNSServerEntrySwitch));
	dns_a_recover_time = 0;
	dns_aaa_recover_time = 0;
	dproxy_active_a = 0;
	dproxy_active_aaa = 0;
#ifdef AEI_PRIMARY_DNS_CHECK
	primary_check_a = CHECK_INIT;
	primary_check_aaa = CHECK_INIT;
	primary_active_a = 0;
	primary_active_aaa = 0;
#endif

	/* Try to read name servers from /var/fyi/sys/dns */
	if ( !load_switch_dns_servers_v4_and_v6())
	{
		debug_perror("No DNS server!");
		return 0;
	}

	//init DNS server for query type A
	if (strlen(dnsServersSwitch.dns[NUM_IPV4_DNS1]) != 0 )
	{
		dproxy_active_a = 1;
		dnsServersSwitch.primary_dns_a = NUM_IPV4_DNS1;      //only change when reload
		dnsServersSwitch.using_dns_a= NUM_IPV4_DNS1;         //change when switch dns server, can be 0-3
		dnsServersSwitch.last_active_dns_a = NUM_IPV4_DNS1;  //by default, set primary as active one, will change when switch
	}
#ifdef AEI_DNS_V4_AND_V6_SWITCH
	else if(strlen(dnsServersSwitch.dns[NUM_IPV6_DNS1]) != 0)
	{
		//just has IPv6 DNS server
		dproxy_active_a = 1;
		dnsServersSwitch.primary_dns_a = NUM_IPV6_DNS1;      //only change when reload
		dnsServersSwitch.using_dns_a = NUM_IPV6_DNS1;        //change when switch dns server, just between 2 and 3
		dnsServersSwitch.last_active_dns_a = NUM_IPV6_DNS1;  //by default, set primary as active one, will change when switch
	}
#endif

	//init DNS server for query type AAA
	if (strlen(dnsServersSwitch.dns[NUM_IPV6_DNS1]) != 0)
	{
		dproxy_active_aaa = 1;
		dnsServersSwitch.primary_dns_aaa= NUM_IPV6_DNS1;      //only change when reload
		dnsServersSwitch.using_dns_aaa= NUM_IPV6_DNS1;        //change when switch dns server, can be 0-3
		dnsServersSwitch.last_active_dns_aaa= NUM_IPV6_DNS1;  //by default, set primary as active one, will change when switch
	}
#ifdef AEI_DNS_V4_AND_V6_SWITCH
	else if(strlen(dnsServersSwitch.dns[NUM_IPV4_DNS1]) != 0)
	{
		//just has IPv4 DNS server
		dproxy_active_aaa = 1;
		dnsServersSwitch.primary_dns_aaa = NUM_IPV4_DNS1;     //only change when reload
		dnsServersSwitch.using_dns_aaa = NUM_IPV4_DNS1;       //change when switch dns server, just between 0 and 1
		dnsServersSwitch.last_active_dns_aaa= NUM_IPV4_DNS1;  //by default, set primary as active one, will change when switch
	}
#endif

	return 1;

}

/*
*  Function: dns_switch_is_enable
*
*  Description: check if need enable DNS switch
*
*  Input Parameters:
*    int query_type: A or AAA
*
*   Return Values: 1 sucess, 0 failed
*/
int dns_switch_is_enable(int query_type)
{
	if(query_type == A)
	{
#ifdef AEI_DNS_V4_AND_V6_SWITCH
		if ((dns_a_recover_time == 0)
		        || ( dnsServersSwitch.using_dns_a == NUM_IPV4_DNS2 && strlen(dnsServersSwitch.dns[NUM_IPV6_DNS1]) != 0)
		        || ( dnsServersSwitch.using_dns_a == NUM_IPV6_DNS1 && strlen(dnsServersSwitch.dns[NUM_IPV6_DNS2]) != 0))
#else
		if (dns_a_recover_time == 0)
#endif
			return 1;
		else
			return 0;
	}
	else if(query_type == AAA)
	{
#ifdef AEI_DNS_V4_AND_V6_SWITCH
		if ((dns_aaa_recover_time == 0)
		        || ( dnsServersSwitch.using_dns_aaa == NUM_IPV6_DNS2 && strlen(dnsServersSwitch.dns[NUM_IPV4_DNS1]) != 0)
		        || ( dnsServersSwitch.using_dns_aaa == NUM_IPV4_DNS1 && strlen(dnsServersSwitch.dns[NUM_IPV4_DNS2]) != 0))
#else
		if (dns_aaa_recover_time == 0)
#endif
			return 1;
		else
			return 0;
	}
	else
	{
		debug_perror("Not support type!");
	}

	return 0;
}

/*
*  Function: dns_switch_v4_and_v6
*
*  Description: switch during all DNS server, IPv4 and IPv6
*
*  Input Parameters:
*    int query_type: A or AAA
*
*/
void dns_switch_v4_and_v6(int query_type)
{
	debug("Before switch query_type=%d, IPv4 DNS server=%s, IPv6 DNS server=%s \n",
	      query_type,dnsServersSwitch.dns[dnsServersSwitch.using_dns_a],dnsServersSwitch.dns[dnsServersSwitch.using_dns_aaa]);


	if (!dns_wanup)
	{	/* No need to switch if no WAN interface */
		return;
	}

	if(query_type == A)
	{
		if(dns_a_recover_time == 0)
		{
			//switch from primary DNS server
			if(dnsServersSwitch.last_active_dns_a == dnsServersSwitch.primary_dns_a)
			{
				//switch from primary DNS server to next one
				if(strlen(dnsServersSwitch.dns[dnsServersSwitch.primary_dns_a+1]) != 0)
				{
					dnsServersSwitch.using_dns_a = dnsServersSwitch.primary_dns_a + 1;
					dns_a_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
					dns_list_unarm_all_requests(query_type);
				}
			}
			else
			{
				// switch from primary DNS server to last active one directly
				if(strlen(dnsServersSwitch.dns[dnsServersSwitch.last_active_dns_a]) != 0)
				{
					dnsServersSwitch.using_dns_a= dnsServersSwitch.last_active_dns_a;
					dnsServersSwitch.last_active_dns_a = dnsServersSwitch.primary_dns_a; //reset default again, will set if get response next time
					dns_a_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
					dns_list_unarm_all_requests(query_type);
				}
			}

		}
#ifdef AEI_DNS_V4_AND_V6_SWITCH
		else if(dns_a_recover_time && dnsServersSwitch.using_dns_a < NUM_IPV6_DNS2)
		{
			//switch during other DNS servers
			if(strlen(dnsServersSwitch.dns[dnsServersSwitch.using_dns_a+1]) != 0)
			{
				dnsServersSwitch.using_dns_a += 1;
				dns_list_unarm_all_requests(query_type);
			}
#ifdef AEI_PRIMARY_DNS_CHECK
			//last one unactive, switch back to primary
			else
			{
				dns_a_recover_time = 0;
				primary_active_a = 0;
				primary_check_a = CHECK_INIT;
				dnsServersSwitch.using_dns_a = dnsServersSwitch.primary_dns_a;
				dns_list_unarm_all_requests(query_type);
			}
#endif
		}
#endif
#ifdef AEI_PRIMARY_DNS_CHECK
		//last one unactive, switch back to primary
		else if(dns_a_recover_time && dnsServersSwitch.using_dns_a == NUM_IPV6_DNS2)
		{
			dns_a_recover_time = 0;
			primary_active_a = 0;
			primary_check_a = CHECK_INIT;
			dnsServersSwitch.using_dns_a = dnsServersSwitch.primary_dns_a;
			dns_list_unarm_all_requests(query_type);
		}
#endif
	}
	else if(query_type == AAA)
	{
		if(dns_aaa_recover_time == 0)
		{
			//switch from primary DNS server
			if(dnsServersSwitch.last_active_dns_aaa == dnsServersSwitch.primary_dns_aaa)
			{
				//switch from primary DNS server to next one
				if(strlen(dnsServersSwitch.dns[dnsServersSwitch.primary_dns_aaa+1]) != 0)
				{
					dnsServersSwitch.using_dns_aaa = dnsServersSwitch.primary_dns_aaa+1;
					dns_aaa_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
					dns_list_unarm_all_requests(query_type);
				}
			}
			else
			{
				// switch from primary DNS server to last active one directly
				if(strlen(dnsServersSwitch.dns[dnsServersSwitch.last_active_dns_aaa]) != 0)
				{
					dnsServersSwitch.using_dns_aaa = dnsServersSwitch.last_active_dns_aaa;
					dnsServersSwitch.last_active_dns_aaa = dnsServersSwitch.primary_dns_aaa; //reset default again, will set if get response next time
					dns_aaa_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
					dns_list_unarm_all_requests(query_type);
				}
			}

		}
#ifdef AEI_PRIMARY_DNS_CHECK
		//last one unactive, switch back to primary
		else if(dns_aaa_recover_time && dnsServersSwitch.using_dns_aaa == NUM_IPV4_DNS2)
		{
			dns_aaa_recover_time = 0;
			primary_active_aaa = 0;
			primary_check_aaa = CHECK_INIT;
			dnsServersSwitch.using_dns_aaa = dnsServersSwitch.primary_dns_aaa;
			dns_list_unarm_all_requests(query_type);
		}
#endif
#ifdef AEI_DNS_V4_AND_V6_SWITCH
		else if(dns_aaa_recover_time && dnsServersSwitch.primary_dns_aaa == NUM_IPV6_DNS1)
		{
			//switch during other DNS servers
			if(dnsServersSwitch.using_dns_aaa == NUM_IPV6_DNS2)
			{
				if(strlen(dnsServersSwitch.dns[NUM_IPV4_DNS1]) != 0)
				{
					dnsServersSwitch.using_dns_aaa = NUM_IPV4_DNS1;
					dns_list_unarm_all_requests(query_type);
				}
#ifdef AEI_PRIMARY_DNS_CHECK
				//last one unactive, switch back to primary
				else
				{
					dns_aaa_recover_time = 0;
					primary_active_aaa = 0;
					primary_check_aaa = CHECK_INIT;
					dnsServersSwitch.using_dns_aaa = dnsServersSwitch.primary_dns_aaa;
					dns_list_unarm_all_requests(query_type);
				}
#endif
			}
			else if(dnsServersSwitch.using_dns_aaa == NUM_IPV4_DNS1)
			{
				if(strlen(dnsServersSwitch.dns[NUM_IPV4_DNS2]) != 0)
				{
					dnsServersSwitch.using_dns_aaa = NUM_IPV4_DNS2;
					dns_list_unarm_all_requests(query_type);
				}
#ifdef AEI_PRIMARY_DNS_CHECK
				//last one unactive, switch back to primary
				else
				{
					dns_aaa_recover_time = 0;
					primary_active_aaa = 0;
					primary_check_aaa = CHECK_INIT;
					dnsServersSwitch.using_dns_aaa = dnsServersSwitch.primary_dns_aaa;
					dns_list_unarm_all_requests(query_type);
				}
#endif
			}

		}
#endif

	}
	else
	{
		debug_perror("Not support type!");
	}

	debug("After switch query_type=%d, IPv4 DNS server=%s, IPv6 DNS server=%s \n",
	      query_type,dnsServersSwitch.dns[dnsServersSwitch.using_dns_a],dnsServersSwitch.dns[dnsServersSwitch.using_dns_aaa]);

}


/*
*  Function: dns_switchback_v4_and_v6
*
*  Description: Switch back to primary server
*
*  Input Parameters:
*    int query_type: A or AAA
*
*/
void dns_switchback_v4_and_v6(int query_type)
{
	debug("Before switchback query_type=%d, IPv4 DNS server=%s, IPv6 DNS server=%s \n",
	      query_type,dnsServersSwitch.dns[dnsServersSwitch.using_dns_a],dnsServersSwitch.dns[dnsServersSwitch.using_dns_aaa]);

	if (!dns_wanup)
	{	/* No need to switch if no WAN interface */
		return;
	}

	if(query_type == A)
	{
#ifdef AEI_PRIMARY_DNS_CHECK
		if(primary_check_a == CHECK_INIT && dnsServersSwitch.last_active_dns_a != dnsServersSwitch.primary_dns_a)
		{
			//other DNS server active, enable check
			primary_check_a = CHECK_ENABLE;
			dns_a_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
		}
		else if(primary_active_a)
		{
			//primary DNS server actice switch back
			dns_a_recover_time = 0;
			primary_active_a = 0;
			primary_check_a = CHECK_INIT;
			dnsServersSwitch.using_dns_a = dnsServersSwitch.primary_dns_a;
			dns_list_unarm_all_requests(query_type);
		}
		else if(primary_check_a == CHECK_STARTED)
		{
			//check timeout, enable again
			primary_check_a = CHECK_ENABLE;
			dns_a_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
		}
		else
		{
			//set a recover time
			dns_a_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
		}
#else
		dns_a_recover_time = 0;
		dnsServersSwitch.using_dns_a = dnsServersSwitch.primary_dns_a;
		dns_list_unarm_all_requests(query_type);
#endif

	}
	else if(query_type == AAA)
	{
#ifdef AEI_PRIMARY_DNS_CHECK
		if(primary_check_aaa == CHECK_INIT && dnsServersSwitch.last_active_dns_aaa != dnsServersSwitch.primary_dns_aaa)
		{
			//other DNS server active, enable check
			primary_check_aaa = CHECK_ENABLE;
			dns_aaa_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
		}
		else if(primary_active_aaa)
		{
			//primary DNS server actice switch back
			dns_aaa_recover_time = 0;
			primary_active_aaa = 0;
			primary_check_aaa = CHECK_INIT;
			dnsServersSwitch.using_dns_aaa = dnsServersSwitch.primary_dns_aaa;
			dns_list_unarm_all_requests(query_type);
		}
		else if(primary_check_aaa == CHECK_STARTED)
		{
			//check timeout, enable again
			primary_check_aaa = CHECK_ENABLE;
			dns_aaa_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
		}
		else
		{
			//set aaa recover time
			dns_aaa_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
		}
#else
		dns_aaa_recover_time = 0;
		dnsServersSwitch.using_dns_aaa = dnsServersSwitch.primary_dns_aaa;
		dns_list_unarm_all_requests(query_type);
#endif

	}
	else
	{
		debug_perror("Not support type!");
	}

	debug("After switchback query_type=%d, IPv4 DNS server=%s, IPv6 DNS server=%s \n",
	      query_type,dnsServersSwitch.dns[dnsServersSwitch.using_dns_a],dnsServersSwitch.dns[dnsServersSwitch.using_dns_aaa]);

}

/*
*  Function: dns_switch_v4_and_v6_find_using_dns
*
*  Description: find a using dns  server
*
*   Input Parameters:
*         struct sockaddr_storage *lanInfo: DNS query information
*         int queryType: AAA(v6), A(v4)
*
*   Output Parameters:
*         char *dns: the using dns server
*         int *proto: the using dns server protocol
*   Return Values: dns server id sucess, -1 failed
*/
int dns_switch_v4_and_v6_find_using_dns(int queryType, char *dns, int *proto)
{
	int found = -1;

	if (dns == NULL)
	{
		return 0;
	}

	if (queryType == A && dproxy_active_a)
	{
		/*
		 * A query: If IPv4 DNS server active, return the IPv4 DNS
		 * server address. Otherwise, return the IPv6 DNS server
		 * address if available.
		 */

		if(strlen(dnsServersSwitch.dns[dnsServersSwitch.using_dns_a]) != 0)
		{
			strncpy(dns,dnsServersSwitch.dns[dnsServersSwitch.using_dns_a],INET6_ADDRSTRLEN-1);
		}
		else
		{
			debug_perror("find using dns fail!");
			return -1;
		}

		if(dns_a_recover_time == 0)
		{
			if(dnsServersSwitch.primary_dns_a == NUM_IPV4_DNS1)
			{
				*proto = AF_INET;
				found = NUM_IPV4_DNS1;
			}
			else if(dnsServersSwitch.primary_dns_a == NUM_IPV6_DNS1)
			{
				*proto = AF_INET6;
				found = NUM_IPV6_DNS1;
			}
		}
		else
		{
			if(dnsServersSwitch.using_dns_a <= NUM_IPV4_DNS2)
			{
				*proto = AF_INET;
				found = dnsServersSwitch.using_dns_a;
			}
			else if(dnsServersSwitch.using_dns_a >= NUM_IPV6_DNS1)
			{
				*proto = AF_INET6;
				found = dnsServersSwitch.using_dns_a;
			}
		}


	}
	else if(queryType == AAA && dproxy_active_aaa)
	{
		/*
		 * AAAA query: If IPv6 DNS server active, return the IPv6 DNS
		 * server address. Otherwise, return the IPv4 DNS server
		 * address if available.
		 */
		if(strlen(dnsServersSwitch.dns[dnsServersSwitch.using_dns_aaa]) != 0)
		{
			strncpy(dns,dnsServersSwitch.dns[dnsServersSwitch.using_dns_aaa],INET6_ADDRSTRLEN-1);
		}
		else
		{
			debug_perror("find using dns fail!");
			return -1;
		}

		if(dns_aaa_recover_time == 0)
		{
			if(dnsServersSwitch.primary_dns_aaa == NUM_IPV4_DNS1)
			{
				*proto = AF_INET;
				found = NUM_IPV4_DNS1;
			}
			else if(dnsServersSwitch.primary_dns_aaa == NUM_IPV6_DNS1)
			{
				*proto = AF_INET6;
				found = NUM_IPV6_DNS1;
			}
		}
		else
		{
			if(dnsServersSwitch.using_dns_aaa <= NUM_IPV4_DNS2)
			{
				*proto = AF_INET;
				found = dnsServersSwitch.using_dns_aaa;
			}
			else if(dnsServersSwitch.using_dns_aaa >= NUM_IPV6_DNS1)
			{
				*proto = AF_INET6;
				found = dnsServersSwitch.using_dns_aaa;
			}
		}
	}



	debug("Dns_switch_v4_and_v6_find_activate_dns dns %d,%d,%s,%d\n",queryType,found,dns,*proto);

	return found;
}

/*
*  Function: dns_set_last_active_v4_and_v6
*
*  Description: set dns last active one
*
*  Input Parameters:
*    int query_type: A or AAA
*
*/
void dns_set_last_active_v4_and_v6(int query_type)
{
	if (query_type == A)
	{
		if(dnsServersSwitch.using_dns_a != dnsServersSwitch.primary_dns_a)
		{
			dnsServersSwitch.last_active_dns_a = dnsServersSwitch.using_dns_a;
		}
	}
	else if(query_type == AAA)
	{
		if(dnsServersSwitch.using_dns_aaa != dnsServersSwitch.primary_dns_aaa)
		{
			dnsServersSwitch.last_active_dns_aaa = dnsServersSwitch.using_dns_aaa;
		}
	}
}

#ifdef AEI_PRIMARY_DNS_CHECK
/*
*  Function: start_primary_dns_check_v4_and_v6
*
*  Description: start to send check for primary DNS server
*
*  int queryType: A or AAA
*/
void start_primary_dns_check_v4_and_v6(int queryType)
{
	int retval = 0;

	if (queryType == A && primary_check_a == CHECK_ENABLE)
	{
		srandom(time(NULL));
		probe_id_a = (uint16_t)random();
		*((uint16_t*)probe_pkt_a) = htons(probe_id_a);

		if(dnsServersSwitch.primary_dns_a == NUM_IPV4_DNS1)
		{

			retval = sendto(dns_querysock[0], probe_pkt_a, sizeof(probe_pkt_a),
			                0, (struct sockaddr*)&probe_addr_v4,
			                sizeof(struct sockaddr_in));
			if( retval < 0 )
			{
				debug_perror("sendto ipv4 primary dns server failed\n");
			}
			else
			{
				primary_check_a = CHECK_STARTED;
				dns_a_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
			}
		}
		else if(dnsServersSwitch.primary_dns_a == NUM_IPV6_DNS1)
		{

			retval = sendto(dns_querysock[1], probe_pkt_a, sizeof(probe_pkt_a),
			                0, (struct sockaddr*)&probe_addr_v6,
			                sizeof(struct sockaddr_in6));
			if( retval < 0 )
			{
				debug_perror("sendto ipv4 primary dns server failed\n");
			}
			else
			{
				primary_check_a = CHECK_STARTED;
				dns_a_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
			}
		}
	}
	else if(queryType == AAA && primary_check_aaa == CHECK_ENABLE)
	{
		srandom(time(NULL));
		probe_id_aaa = (uint16_t)random();
		*((uint16_t*)probe_pkt_aaa) = htons(probe_id_aaa);

		if(dnsServersSwitch.primary_dns_aaa == NUM_IPV4_DNS1)
		{
			retval = sendto(dns_querysock[0], probe_pkt_aaa, sizeof(probe_pkt_aaa),
			                0, (struct sockaddr*)&probe_addr_v4,
			                sizeof(struct sockaddr_in));
			if( retval < 0 )
			{
				debug_perror("sendto ipv6 primary dns server failed\n");
			}
			else
			{
				primary_check_aaa = CHECK_STARTED;
				dns_aaa_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
			}
		}
		else if(dnsServersSwitch.primary_dns_aaa == NUM_IPV6_DNS1)
		{

			retval = sendto(dns_querysock[1], probe_pkt_aaa, sizeof(probe_pkt_aaa),
			                0, (struct sockaddr*)&probe_addr_v6,
			                sizeof(struct sockaddr_in6));
			if( retval < 0 )
			{
				debug_perror("sendto ipv6 primary dns server failed\n");
			}
			else
			{
				primary_check_aaa = CHECK_STARTED;
				dns_aaa_recover_time = time(NULL) + DNS_RECOVER_TIMEOUT;
			}
		}
	}

}

/*
*  Function: primary_dns_check_v4_and_v6
*
*  Description: check if primary DNS is active
*
*  Input Parameters:
*    dns_request_t *m: packet from dns_querysock
*
*   return 1 success, 0 fail
*/
int primary_dns_check_v4_and_v6(dns_request_t *m)
{

	if (m->message.header.flags.flags & 0x8000 )
	{

		if(primary_check_a == CHECK_STARTED && m->message.header.id == probe_id_a)
		{
			primary_active_a = 1;
		}
		else if(primary_check_aaa == CHECK_STARTED && m->message.header.id == probe_id_aaa)
		{
			primary_active_aaa = 1;
		}

	}

	return (primary_active_a || primary_active_aaa);


}
#endif

