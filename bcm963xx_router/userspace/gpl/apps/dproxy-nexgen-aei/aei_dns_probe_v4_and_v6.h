#ifndef _AEI_DNS_PROBE_V4_AND_V6_H_
#define _AEI_DNS_PROBE_V4_AND_V6_H_
#include <netinet/in.h>

typedef struct _DNSServer
{
	int activeflag;
	char dns[INET6_ADDRSTRLEN];
} DNSServer;

typedef struct _DNSServerEntry
{
	DNSServer ipv4_dns1;  //Activeflag Default 1
	DNSServer ipv4_dns2;  //Activeflag Default 1
	DNSServer ipv6_dns1;  //Activeflag Default 1
	DNSServer ipv6_dns2;  //Activeflag Default 1
	int probe_flag;  // 1 need probe in short interval
} DNSServerEntry;


int dns_probe_v4_and_v6(void);
int dns_probe_v4_and_v6_init(void);
int dns_probe_v4_and_v6_response(dns_request_t *m);
int dns_probe_v4_and_v6_activate(struct sockaddr_storage *name_server);
int Dns_probe_v4_and_v6_find_activate_dns( int queryType, char *dns, int *proto, int rex);


#endif /*_AEI_DNS_PROBE_V4_AND_V6_H_ */

