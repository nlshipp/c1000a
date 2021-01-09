/*
 *----------------------------------------------------------------
 *
 * dns_probe_v4_and_v6.c
 *
 * <11, 15, 2012> <harrison>
 *
 * <new dns probe supporting to switch dns server between v4 and v6.
 *  1. in every probe time, probe all dns servers, both v4 and v6, if which one can get
 *  a probe reponse, just set its activeflag to enable.
 *  2. when proxy get a query from LAN, it can choose active dns server directly
 * >
 *
 * Copyright (c) 2012 Actiontec Electronics Inc.
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
#include "aei_dns_probe_v4_and_v6.h"

#define NUM_IPV4_DNS1   0
#define NUM_IPV4_DNS2   1
#define NUM_IPV6_DNS1   2
#define NUM_IPV6_DNS2   3

#ifdef DESKTOP_LINUX
#define REAL_DNS_FYI_FILENAME   "./dns.real"
#else
#define REAL_DNS_FYI_FILENAME   "/var/fyi/sys/dns.real"
#endif

static DNSServerEntry dnsServers;
static struct sockaddr_storage probe_addr[4];
static uint16_t probe_id[4];
static int probe_tried[4];
static time_t probe_next_time;
static time_t probe_timeout;

//use for dns activeflag not fresh in normal probe time
static time_t probe_short_interval_time;
static int probe_short_interval_count;
#define DNS_PROBE_SHORT_INTERVAL      (DNS_PROBE_TIMEOUT+1)

static char probe_pkt1_v4[35] =
{	0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x3, 'w','w','w', 0x9, 'm', 'i', 'c', 'r', 'o', 's','o','f','t', 0x3, 'c', 'o',
	'm', 0x0, 0x0, 0x1, 0x0, 0x1,
};

static char probe_pkt2_v4[35] =
{	0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x3, 'w','w','w', 0x9, 'm', 'i', 'c', 'r', 'o', 's','o','f','t', 0x3, 'c', 'o',
	'm', 0x0, 0x0, 0x1, 0x0, 0x1,
};

static char probe_pkt3_v6[33] =
{	0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x4, 'i','p','v', '6',0x6, 'g', 'o', 'o',  'g','l', 'e', 0x3, 'c', 'o', 'm',
	0x0, 0x0, 0x1c, 0x0, 0x1,
};

static char probe_pkt4_v6[33] =
{	0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x4, 'i','p','v', '6',0x6, 'g', 'o', 'o',  'g','l', 'e', 0x3, 'c', 'o', 'm',
	0x0, 0x0, 0x1c, 0x0, 0x1,
};

// from dns_subnet.c
#ifdef DMP_X_BROADCOM_COM_IPV6_1
extern UBOOL8 dns_subnet_map(struct in6_addr *lanIp, char *dns1);
#else
extern UBOOL8 dns_subnet_map(struct in_addr *lanIp, char *dns1);
#endif

/*
*  Function: load_dns_name_servers_v4_and_v6
*
*  Description: 1. load dns server name from file /etc/resolv.conf
*             2. init probe address
*
*
*   Return Values: 1 sucess, 0 failed
*/
static int load_dns_name_servers_v4_and_v6(void)
{
	FILE * fp;
	char line[256] = {0};
	char addr[INET6_ADDRSTRLEN] = {0};
	char domain[256] = {0};

	memset(&dnsServers,0,sizeof(DNSServerEntry));

	//name server of resolv.conf is 127.0.0.1, it redirects ont dns query
	//to dns proxy to record dns query failed of ipHost PM
	if((fp = fopen(REAL_DNS_FYI_FILENAME, "r")) == NULL)
	{
		debug("Opend %s failed", REAL_DNS_FYI_FILENAME);
		// if dns.real does not exist, open /etc/resolv.conf
		if((fp = fopen("/etc/resolv.conf", "r")) == NULL)
		{
			debug_perror("Opend /etc/resolv.conf failed");
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
					if(dnsServers.ipv4_dns1.activeflag == 0)
					{
						strncpy(dnsServers.ipv4_dns1.dns, addr, INET6_ADDRSTRLEN-1);
						dnsServers.ipv4_dns1.activeflag = 1;
						probe_addr[NUM_IPV4_DNS1].ss_family = AF_INET;
						((struct sockaddr_in *)&probe_addr[NUM_IPV4_DNS1])->sin_port = PORT;
						inet_pton( AF_INET, addr, &(((struct sockaddr_in *)&probe_addr[NUM_IPV4_DNS1])->sin_addr) );
					}
					else if(dnsServers.ipv4_dns2.activeflag == 0)
					{
						strncpy(dnsServers.ipv4_dns2.dns, addr, INET6_ADDRSTRLEN-1);
						dnsServers.ipv4_dns2.activeflag = 1;
						probe_addr[NUM_IPV4_DNS2].ss_family = AF_INET;
						((struct sockaddr_in *)&probe_addr[NUM_IPV4_DNS2])->sin_port = PORT;
						inet_pton( AF_INET, addr, &(((struct sockaddr_in *)&probe_addr[NUM_IPV4_DNS2])->sin_addr) );
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
					if(dnsServers.ipv6_dns1.activeflag == 0)
					{
						strncpy(dnsServers.ipv6_dns1.dns, addr, INET6_ADDRSTRLEN-1);
						dnsServers.ipv6_dns1.activeflag = 1;
						probe_addr[NUM_IPV6_DNS1].ss_family = AF_INET6;
						((struct sockaddr_in6 *)&probe_addr[NUM_IPV6_DNS1])->sin6_port = PORT;
						inet_pton( AF_INET6, addr, &(((struct sockaddr_in6 *)&probe_addr[NUM_IPV6_DNS1])->sin6_addr) );
					}
					else if(dnsServers.ipv6_dns2.activeflag == 0)
					{
						strncpy(dnsServers.ipv6_dns2.dns, addr, INET6_ADDRSTRLEN-1);
						dnsServers.ipv6_dns2.activeflag = 1;
						probe_addr[NUM_IPV6_DNS2].ss_family = AF_INET6;
						((struct sockaddr_in6 *)&probe_addr[NUM_IPV6_DNS2])->sin6_port = PORT;
						inet_pton( AF_INET6, addr, &(((struct sockaddr_in6 *)&probe_addr[NUM_IPV6_DNS2])->sin6_addr) );
					}
					else
					{
						debug("dnsproxy supports a max of two ipv6 name servers.  "
						      "Additional ipv6 name servers are ignored.\n");
					}
				}
			}
		}
		else if (sscanf(line, "domain %s", domain) == 1)
		{
			strncpy(config.domain_name, domain, sizeof(config.domain_name)-1);
		}
	}
	fclose(fp);

	debug("dproxy: load nameserver %s, %s, %s, %s\n", dnsServers.ipv4_dns1.dns, dnsServers.ipv4_dns2.dns,dnsServers.ipv6_dns1.dns,dnsServers.ipv6_dns2.dns);
	debug("dproxy: load domain %s\n", config.domain_name);

	if (strlen(dnsServers.ipv4_dns1.dns) == 0 && strlen(dnsServers.ipv6_dns1.dns) == 0)  /* not even a single valid nameserver found */
		return 0;
	return 1;
}

/*
*  Function: dns_probe_v4_and_v6_init
*
*  Description: 1. load dns server name from file /etc/resolv.conf
*             2. init all probe parameter
*
*
*   Return Values: 1 sucess, 0 failed
*/
int dns_probe_v4_and_v6_init(void)
{
	int i =0;
	uint16_t num = 0;
	debug("dns_probe_v4_and_v6_init");

	/* Try to read name servers from /var/fyi/sys/dns */
	if ( !load_dns_name_servers_v4_and_v6())
		return 0;

	/* Initialize request id */
	srandom(time(NULL));
	num = ((uint16_t)random()) & 0xFFF;
	for(i=NUM_IPV4_DNS1; i<=NUM_IPV6_DNS2; i++)
	{
		probe_tried[i] = 0;
		switch(i)
		{
		case NUM_IPV4_DNS1:
			probe_id[NUM_IPV4_DNS1] = num;
			break;
		case NUM_IPV4_DNS2:
			probe_id[NUM_IPV4_DNS2] = num | 0x4000;
			break;
		case NUM_IPV6_DNS1:
			probe_id[NUM_IPV6_DNS1] = num | 0x8000;
			break;
		case NUM_IPV6_DNS2:
			probe_id[NUM_IPV6_DNS2] = num | 0xc000;
			break;
		default:
			break;
		}
	}

	probe_next_time = 0;
	probe_timeout = 0;
	probe_short_interval_time = 0;
	probe_short_interval_count = 0;

	return 1;
}

/*
*  Function: dns_probe_v4_and_v6
*
*  Description: send out probe packet for all dns servers in interval
*
*
*   Return Values: next probe time
*/
int dns_probe_v4_and_v6(void)
{
	int ret = 0;
	int i = 0;
	int retval;
	int probing = 0;
	time_t now = time(NULL);

	debug("dns_probe_v4_and_v6: entered, dns_wanup=%d\n",dns_wanup);

	if (!dns_wanup) { /* No need to probe if no WAN interface */
		return 1;  //select timeout in 1 second
	}

	// check probe result
	for(i=NUM_IPV4_DNS1; i<=NUM_IPV6_DNS2; i++)
	{
		if (probe_tried[i]) // Probing
		{
			if (now >= probe_timeout) // Timed out
			{
				// Probe failed
				switch(i)
				{
				case NUM_IPV4_DNS1:
					dnsServers.ipv4_dns1.activeflag = 0;
					break;
				case NUM_IPV4_DNS2:
					dnsServers.ipv4_dns2.activeflag = 0;
					break;
				case NUM_IPV6_DNS1:
					dnsServers.ipv6_dns1.activeflag = 0;
					break;
				case NUM_IPV6_DNS2:
					dnsServers.ipv6_dns2.activeflag = 0;
					break;
				default:
					break;
				}

				probe_tried[i] = 0;

			}
			else  //in probing and not reach timeout
			{
				probing = 1;
			}
		}
	}

	if(probing)
	{
		//when in probing, can't start a new probe, just return
		ret = probe_timeout - now;
	}
	else
	{

		// start new probe
		if ( (now >= probe_next_time) || (dnsServers.probe_flag && now >= probe_short_interval_time))
		{
			debug("%d,%d,%d\n",now >= probe_next_time,dnsServers.probe_flag,now >= probe_short_interval_time);
			// Time to probe
			for(i=NUM_IPV4_DNS1; i<=NUM_IPV6_DNS2; i++)
			{
				switch(i)
				{
				case NUM_IPV4_DNS1:
					if(strlen(dnsServers.ipv4_dns1.dns) > 0)
					{
						if(++probe_id[NUM_IPV4_DNS1] == 0x3FFF)
							probe_id[NUM_IPV4_DNS1] = 0;
						*((uint16_t*)probe_pkt1_v4) = htons(probe_id[NUM_IPV4_DNS1]);

						retval = sendto(dns_querysock[0], probe_pkt1_v4, sizeof(probe_pkt1_v4),
						                0, (struct sockaddr*)&probe_addr[NUM_IPV4_DNS1],
						                sizeof(struct sockaddr_in));
						if( retval < 0 )
							debug_perror("sendto ipv4_dns1 failed\n");
						else
							probe_tried[i] = 1;
					}
					break;
				case NUM_IPV4_DNS2:
					if(strlen(dnsServers.ipv4_dns2.dns) > 0 && dnsServers.ipv4_dns1.activeflag == 0)
					{
						if(++probe_id[NUM_IPV4_DNS2] == 0x7FFF)
							probe_id[NUM_IPV4_DNS2] = 0x4000;
						*((uint16_t*)probe_pkt2_v4) = htons(probe_id[NUM_IPV4_DNS2]);

						retval = sendto(dns_querysock[0], probe_pkt2_v4, sizeof(probe_pkt2_v4),
						                0, (struct sockaddr*)&probe_addr[NUM_IPV4_DNS2],
						                sizeof(struct sockaddr_in));
						if( retval < 0 )
							debug_perror("sendto ipv4_dns2 failed\n");
						else
							probe_tried[i] = 1;
					}
					break;
				case NUM_IPV6_DNS1:
					if(strlen(dnsServers.ipv6_dns1.dns) > 0)
					{
						if(++probe_id[NUM_IPV6_DNS1] == 0xBFFF)
							probe_id[NUM_IPV6_DNS1] = 0x8000;
						*((uint16_t*)probe_pkt3_v6) = htons(probe_id[NUM_IPV6_DNS1]);

						retval = sendto(dns_querysock[1], probe_pkt3_v6, sizeof(probe_pkt3_v6),
						                0, (struct sockaddr*)&probe_addr[NUM_IPV6_DNS1],
						                sizeof(struct sockaddr_in6));
						if( retval < 0 )
							debug_perror("sendto ipv6_dns1 failed\n");
						else
							probe_tried[i] = 1;
					}
					break;
				case NUM_IPV6_DNS2:
					if(strlen(dnsServers.ipv6_dns2.dns) > 0 && dnsServers.ipv6_dns1.activeflag == 0)
					{
						if(++probe_id[NUM_IPV6_DNS2] == 0xFFFF)
							probe_id[NUM_IPV6_DNS2] = 0xC000;
						*((uint16_t*)probe_pkt4_v6) = htons(probe_id[NUM_IPV6_DNS2]);

						retval = sendto(dns_querysock[1], probe_pkt4_v6, sizeof(probe_pkt4_v6),
						                0, (struct sockaddr*)&probe_addr[NUM_IPV6_DNS2],
						                sizeof(struct sockaddr_in6));
						if( retval < 0 )
							debug_perror("sendto ipv6_dns2 failed\n");
						else
							probe_tried[i] = 1;
					}
					break;
				default:
					break;
				}
			}

			probe_timeout = now + DNS_PROBE_TIMEOUT;
			probe_next_time = now + DNS_PROBE_INTERVAL;

			if(dnsServers.probe_flag)
			{
				probe_short_interval_count++;
				if(probe_short_interval_count <= 3 )
					probe_short_interval_time =  now + DNS_PROBE_SHORT_INTERVAL;
				else
					probe_short_interval_time =  now + DNS_PROBE_SHORT_INTERVAL*(probe_short_interval_count-2);

				if(probe_short_interval_time > probe_next_time)
					probe_short_interval_time = probe_next_time;
			}
			else
			{
				probe_short_interval_time = now + DNS_PROBE_SHORT_INTERVAL;
			}
			ret = DNS_PROBE_TIMEOUT;
		}
		else
		{
			if(dnsServers.probe_flag)
				ret = probe_short_interval_time - now;
			else
				ret = probe_next_time - now;
		}
	}


	debug("dns_probe_v4_and_v6: done, ret=%d\n", ret);

	return ret;
}

/*
*  Function: dns_probe_v4_and_v6_activate
*
*  Description: activate dns server, set its activeflag to 1
*
*   Input Parameters:
*         struct sockaddr_storage *name_server: DNS response source
*
*
*   Return Values: 1 sucess , 0 failed
*/
int dns_probe_v4_and_v6_activate(struct sockaddr_storage *name_server)
{
	int activate = 0;

	if (name_server->ss_family == AF_INET)
	{
		if(((struct sockaddr_in *)name_server)->sin_addr.s_addr == ((struct sockaddr_in *)(&probe_addr[NUM_IPV4_DNS1]))->sin_addr.s_addr)
		{
			dnsServers.ipv4_dns1.activeflag = 1;
			probe_tried[NUM_IPV4_DNS1] = 0;
			activate = 1;
		}
		else if(((struct sockaddr_in *)name_server)->sin_addr.s_addr == ((struct sockaddr_in *)(&probe_addr[NUM_IPV4_DNS2]))->sin_addr.s_addr)
		{
			dnsServers.ipv4_dns2.activeflag = 1;
			probe_tried[NUM_IPV4_DNS2] = 0;
			activate = 1;
		}
	}
	else if (name_server->ss_family == AF_INET6)
	{
		if(memcmp(&(((struct sockaddr_in6 *)name_server)->sin6_addr), &(((struct sockaddr_in6 *)(&probe_addr[NUM_IPV6_DNS1]))->sin6_addr),sizeof(struct in6_addr) )== 0)
		{
			dnsServers.ipv6_dns1.activeflag = 1;
			probe_tried[NUM_IPV6_DNS1] = 0;
			activate = 1;
		}
		else if(memcmp(&(((struct sockaddr_in6 *)name_server)->sin6_addr), &(((struct sockaddr_in6 *)(&probe_addr[NUM_IPV6_DNS2]))->sin6_addr),sizeof(struct in6_addr)) == 0)
		{
			dnsServers.ipv6_dns2.activeflag = 1;
			probe_tried[NUM_IPV6_DNS2] = 0;
			activate = 1;
		}
	}


	return activate;
}


/*
*  Function: dns_probe_v4_and_v6_response
*
*  Description: Activate name server if it's the response for probing request
*
*   Input Parameters:
*         dns_request_t *m: packet from dns_querysock
*
*
*   Return Values: dns server id sucess, 0 failed
*/
int dns_probe_v4_and_v6_response(dns_request_t *m)
{

	if (m->message.header.flags.flags & 0x8000 &&
	        (m->message.header.id == probe_id[NUM_IPV4_DNS1] ||
	         m->message.header.id == probe_id[NUM_IPV4_DNS2] ||
	         m->message.header.id == probe_id[NUM_IPV6_DNS1] ||
	         m->message.header.id == probe_id[NUM_IPV6_DNS2] ))
	{
		dnsServers.probe_flag = 0;
		probe_short_interval_count = 0;
		return dns_probe_v4_and_v6_activate(&(m->src_info));
	}

	return 0;
}

/*
*  Function: findDnsServerAddress
*
*  Description: find a active dns server
*
*   Input Parameters:
*         DNSServerEntry *servers: global DNSServerEntry
*         int queryType: AAA(v6), A(v4)
*
*   Output Parameters:
*         char *dns: the active dns server
*         int *proto: the active dns server protocol
*
*   Return Values: dns server id sucess, -1 failed
*/
static int findDnsServerAddress(DNSServerEntry *servers, int queryType,
                                char *dns, int *proto)
{
	int found = -1;

	if (queryType == AAA)
	{
		/*
		 * AAAA query: If IPv6 DNS server exists, return the IPv6 DNS
		 * server address. Otherwise, return the IPv4 DNS server
		 * address if available.
		 */
		if (servers->ipv6_dns1.activeflag)
		{
			strncpy(dns, servers->ipv6_dns1.dns, INET6_ADDRSTRLEN-1);
			*proto = AF_INET6;
			found = NUM_IPV6_DNS1;
		}
		else if (servers->ipv6_dns2.activeflag)
		{
			strncpy(dns, servers->ipv6_dns2.dns, INET6_ADDRSTRLEN-1);
			*proto = AF_INET6;
			found = NUM_IPV6_DNS2;
		}
		else if (servers->ipv4_dns1.activeflag)
		{
			strncpy(dns, servers->ipv4_dns1.dns, INET6_ADDRSTRLEN-1);
			*proto = AF_INET;
			found = NUM_IPV4_DNS1;
		}
		else if (servers->ipv4_dns2.activeflag)
		{
			strncpy(dns, servers->ipv4_dns2.dns, INET6_ADDRSTRLEN-1);
			*proto = AF_INET;
			found = NUM_IPV4_DNS2;
		}
		else
		{
			//no active found, use first one
			if(strlen(servers->ipv6_dns1.dns) > 0)
			{
				strncpy(dns, servers->ipv6_dns1.dns, INET6_ADDRSTRLEN-1);
				*proto = AF_INET6;
				found = NUM_IPV6_DNS1;
			}
		}
	}
	else
	{
		/*
		 * A query: If IPv4 DNS server exists, return the IPv4 DNS
		 * server address. Otherwise, return the IPv6 DNS server
		 * address if available.
		 */
		if (servers->ipv4_dns1.activeflag)
		{
			strncpy(dns, servers->ipv4_dns1.dns, INET6_ADDRSTRLEN-1);
			*proto = AF_INET;
			found = NUM_IPV4_DNS1;
		}
		else if (servers->ipv4_dns2.activeflag)
		{
			strncpy(dns, servers->ipv4_dns2.dns, INET6_ADDRSTRLEN-1);
			*proto = AF_INET;
			found = NUM_IPV4_DNS2;
		}
		else if (servers->ipv6_dns1.activeflag)
		{
			strncpy(dns, servers->ipv6_dns1.dns, INET6_ADDRSTRLEN-1);
			*proto = AF_INET6;
			found = NUM_IPV6_DNS1;
		}
		else if (servers->ipv6_dns2.activeflag)
		{
			strncpy(dns, servers->ipv6_dns2.dns, INET6_ADDRSTRLEN-1);
			*proto = AF_INET6;
			found = NUM_IPV6_DNS2;
		}
		else
		{
			//no active found, use first one
			if(strlen(servers->ipv4_dns1.dns) > 0)
			{
				strncpy(dns, servers->ipv4_dns1.dns, INET6_ADDRSTRLEN-1);
				*proto = AF_INET;
				found = NUM_IPV4_DNS1;
			}
		}

	}

	debug("findDnsServerAddress %d\n",found);

	return found;
}

/*
*  Function: Dns_probe_v4_and_v6_find_activate_dns
*
*  Description: find a active dns  server
*
*   Input Parameters:
*         int queryType: AAA(v6), A(v4)
*
*   Output Parameters:
*         char *dns: the active dns server
*         int *proto: the active dns server protocol
*         int rex: Duplicate query flag
*
*   Return Values: dns server id sucess, -1 failed
*/
int Dns_probe_v4_and_v6_find_activate_dns(int queryType, char *dns, int *proto, int rex)
{
	int found = -1;

	if (dns == NULL)
	{
		return 0;
	}


	/*If LAN duplicate query, means pre-query with an unactive dns server,
	  set probe_flag to let proxy probe in short interval,
	  so can renew the dns server activeflag*/
	if(rex)
		dnsServers.probe_flag = 1;


	found = findDnsServerAddress(&dnsServers, queryType, dns, proto);


	return found;
}


