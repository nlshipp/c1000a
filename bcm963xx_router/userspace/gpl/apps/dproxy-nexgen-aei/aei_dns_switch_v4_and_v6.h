#ifndef _AEI_DNS_SWITCH_V4_AND_V6_H_
#define _AEI_DNS_SWITCH_V4_AND_V6_H_

#define AEI_DNS_V4_AND_V6_SWITCH    1   //DNS query with type A can use IPv6 DNS servers, DNS query with type AAAA can use IPv4 DNS servers
#define AEI_PRIMARY_DNS_CHECK     1 //when switch back to primary DNS server need check if it is active
#define DNS_RECOVER_TIMEOUT       30

typedef struct _DNSServerEntry_Switch
{
	char  dns[4][INET6_ADDRSTRLEN]; // order is ipv4_dns1,  ipv4_dns2, ipv6_dns1, ipv6_dns1
	int primary_dns_a;  // just can be 0 or 2 (ipv4_dns1 or ipv6_dns1)
	int primary_dns_aaa;  // just can be 2 or 0 (ipv6_dns1 or ipv4_dns1)
	int using_dns_a;  // 0-3 when dns query with type A get using dns server by this id
	int using_dns_aaa;  // 0-3 when dns query with type AAA get using dns server by this id
	int last_active_dns_a; // keep last active one id for query with type A, next switch from primary directly to this one
	int last_active_dns_aaa; // keep last active one id for query with type AAAA, next switch from primary directly to this one
} DNSServerEntrySwitch;



int dns_switch_v4_and_v6_init(void);
int dns_switch_is_enable(int query_type);
void dns_switch_v4_and_v6(int query_type);
void dns_switchback_v4_and_v6(int query_type);
int dns_switch_v4_and_v6_find_using_dns(int queryType, char * dns, int * proto);

void dns_set_last_active_v4_and_v6(int query_type);


extern time_t dns_a_recover_time;
extern time_t dns_aaa_recover_time;
extern int dproxy_active_a;
extern int dproxy_active_aaa;
#ifdef AEI_PRIMARY_DNS_CHECK
void start_primary_dns_check_v4_and_v6(int queryType);
int primary_dns_check_v4_and_v6(dns_request_t *m);

int primary_active_a;
int primary_active_aaa;
#endif

#endif /*_AEI_DNS_SWITCH_V4_AND_V6_H_ */

