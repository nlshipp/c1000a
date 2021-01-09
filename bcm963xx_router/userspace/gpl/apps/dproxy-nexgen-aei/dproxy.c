/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <linux/sockios.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdarg.h>
#include <signal.h>
#include <bits/signum.h>
#include <syslog.h>
#include <linux/if.h>
#include "dproxy.h"
#include "dns_decode.h"
#include "conf.h"
#include "dns_list.h"
#include "dns_construct.h"
#include "dns_io.h"
#include "dns_dyn_cache.h"
#include "cache.h"
extern int dnsPrefer;
#ifdef AEI_DNS_PROBE
#include "aei_dns_probe_v4_and_v6.h"
#else
#include "aei_dns_switch_v4_and_v6.h"
#endif
#if defined(AEI_VDSL_DNS_CACHE)
#include <sys/stat.h>
 #endif
/*****************************************************************************/
/*****************************************************************************/
int dns_main_quit;
int dns_sock[2]= {-1, -1};
fd_set rfds;

//BRCM
int dns_querysock[2]= {-1, -1};
#ifdef DMP_X_ITU_ORG_GPON_1
static unsigned int dns_query_error = 0;
#endif

int dns_wanup = 0;

/* CMS message handle */
void *msgHandle=NULL;
int msg_fd;

//AEI
static char *pid_file = DPROXY_PIDFILE;

/*****************************************************************************/
static void dnsproxy_reload_handler(int sig)
{
#ifdef AEI_DNS_PROBE
	dns_wanup = dns_probe_v4_and_v6_init();
#else
	dns_wanup = dns_switch_v4_and_v6_init();
#endif
}

static void host_reload_handler(int sig)
{
	cache_purge( config.purge_time );
}

#if defined(AEI_VDSL_DNS_CACHE)
time_t syn_time=0;
int enable_dns_cache=0;
/*Whether dns cache enabled. */
int dns_cache_enabled()
{
   time_t t=time(NULL);
   if (t-syn_time>3)
   {
	syn_time=t;
	struct stat stats;
	if(stat("/var/dns_cache", &stats) == 0)
	  enable_dns_cache=1;
	else
	  enable_dns_cache=0;
   }
   return enable_dns_cache;

}
#endif

int dns_init()
{
	struct addrinfo hints, *res, *p;
	int errcode;
	int ret, i, on=1;

	memset(&hints, 0, sizeof (hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	/*
	 * BRCM:
	 * Open sockets to receive DNS queries from LAN.
	 * dns_sock[0] is used for DNS queries over IPv4
	 * dns_sock[1] is used for DNS queries over IPv6
	 */
	errcode = getaddrinfo(NULL, PORT_STR, &hints, &res);
	if (errcode != 0)
	{
		debug("gai err %d %s", errcode, gai_strerror(errcode));
		exit(1) ;
	}

	p = res;
	while (p)
	{
		if ( p->ai_family == AF_INET )   i = 0;
		else if ( p->ai_family == AF_INET6 )   i = 1;
		else {
			debug_perror("Unknown protocol!!\n");
			goto next_lan;
		}

		dns_sock[i] = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

		if (dns_sock[i] < 0)
		{
			debug("Could not create dns_sock[%d]", i);
			goto next_lan;
		}

#ifdef IPV6_V6ONLY
		if ( (p->ai_family == AF_INET6) &&
		        (setsockopt(dns_sock[i], IPPROTO_IPV6, IPV6_V6ONLY,
		                    &on, sizeof(on)) < 0) )
		{
			debug_perror("Could not set IPv6 only option for LAN");
			close(dns_sock[i]);
			goto next_lan;
		}
#endif

		/* bind() the socket to the interface */
		if (bind(dns_sock[i], p->ai_addr, p->ai_addrlen) < 0) {
			debug("dns_init: bind: dns_sock[%d] can't bind to port", i);
			close(dns_sock[i]);
		}


next_lan:
		p = p->ai_next;
	}

	freeaddrinfo(res);

	if ( (dns_sock[0] < 0) && (dns_sock[1] < 0) )
	{
		debug_perror("Cannot create sockets for LAN");
		exit(1) ;
	}

	/*
	 * BRCM:
	 * use different sockets to send queries to WAN so we can use ephemeral port
	 * dns_querysock[0] is used for DNS queries sent over IPv4
	 * dns_querysock[1] is used for DNS queries sent over IPv6
	 */
	errcode = getaddrinfo(NULL, "0", &hints, &res);
	if (errcode != 0)
	{
		debug("gai err %d %s", errcode, gai_strerror(errcode));
		exit(1) ;
	}

	p = res;
	while (p)
	{
		if ( p->ai_family == AF_INET )   i = 0;
		else if ( p->ai_family == AF_INET6 )   i = 1;
		else
		{
			debug_perror("Unknown protocol!!\n");
			goto next_wan;
		}

		dns_querysock[i] = socket(p->ai_family, p->ai_socktype,
		                          p->ai_protocol);

		if (dns_querysock[i] < 0)
		{
			debug("Could not create dns_querysock[%d]", i);
			goto next_wan;
		}

#ifdef IPV6_V6ONLY
		if ( (p->ai_family == AF_INET6) &&
		        (setsockopt(dns_querysock[i], IPPROTO_IPV6, IPV6_V6ONLY,
		                    &on, sizeof(on)) < 0) )
		{
			debug_perror("Could not set IPv6 only option for WAN");
			close(dns_querysock[i]);
			goto next_wan;
		}
#endif

		/* bind() the socket to the interface */
		if (bind(dns_querysock[i], p->ai_addr, p->ai_addrlen) < 0) {
			debug("dns_init: bind: dns_querysock[%d] can't bind to port", i);
			close(dns_querysock[i]);
		}


next_wan:
		p = p->ai_next;
	}

	freeaddrinfo(res);

	if ( (dns_querysock[0] < 0) && (dns_querysock[1] < 0) )
	{
		debug_perror("Cannot create sockets for WAN");
		exit(1) ;
	}

	// BRCM: Connect to ssk
	if ((ret = cmsMsg_init(EID_DNSPROXY, &msgHandle)) != CMSRET_SUCCESS) {
		debug_perror("dns_init: cmsMsg_init() failed");
		exit(1);
	}
	cmsMsg_getEventHandle(msgHandle, &msg_fd);

	dns_main_quit = 0;

	FD_ZERO( &rfds );
	if (dns_sock[0] > 0)
		FD_SET( dns_sock[0], &rfds );
	if (dns_sock[1] > 0)
		FD_SET( dns_sock[1], &rfds );
	if (dns_querysock[0] > 0)
		FD_SET( dns_querysock[0], &rfds );
	if (dns_querysock[1] > 0)
		FD_SET( dns_querysock[1], &rfds );

	FD_SET( msg_fd, &rfds );

	//AEI for IPv6 dns servers update
	if (signal(SIGUSR2, dnsproxy_reload_handler) == SIG_ERR)
	{
		debug_perror( "SIGUSR2 reg fail\n" );
		exit(1);
	}

#ifdef DNS_DYN_CACHE
	dns_dyn_hosts_add();
#endif

#ifdef AEI_VDSL_DNS_CACHE

#ifdef AEI_HOSTNAME_V6
	//AEI for IPv6 hostname update
	if (signal(SIGUSR1, host_reload_handler) == SIG_ERR)
	{
		debug_perror( "SIGUSR1 reg fail\n" );
		exit(1);
	}
#endif

	cache_purge( config.purge_time );
#endif

	//AEI
#ifdef AEI_DNS_PROBE
	dns_wanup = dns_probe_v4_and_v6_init();
#else
	dns_wanup = dns_switch_v4_and_v6_init();
#endif

	return 1;
}


/*****************************************************************************/
void dns_handle_new_query(dns_request_t *m)
{
	int retval = -1;
	dns_dyn_list_t *dns_entry;
	char srcIP[INET6_ADDRSTRLEN];
	int query_type = m->message.question[0].type;

	if( query_type == A )
	{	/* IPv4 */
		retval = 0;
#ifdef AEI_VDSL_DNS_CACHE
		retval = cache_lookup_name( m->cname, m->ip );
#ifdef AEI_HOSTNAME_V6
		if (retval == 0)
		{
			char name[128] = {0};
			snprintf( name, sizeof(name)-1, "[%s]", m->cname );
			retval = cache_lookup_name( name, m->ip );
			if (retval==1)
				retval= 2; // Its should be a IPv6 request
		}
#endif
#endif

#ifdef DNS_DYN_CACHE
		if(retval == 0)
		{
#if defined(AEI_VDSL_DNS_CACHE) 
		  if(dns_cache_enabled())
#endif
			if ((dns_entry = dns_dyn_find(m)))
			{
				strcpy(m->ip, inet_ntoa(dns_entry->addr));
				m->ttl = abs(dns_entry->expiry - time(NULL));
				retval = 1;
				debug(".... %s, srcPort=%d, retval=%d\n", m->cname, ((struct sockaddr_in *)&m->src_info)->sin_port, retval);
			}
		}
#endif
	}
	else if( query_type == AAA)
	{	/* IPv6 */
		retval = 0;
#ifdef AEI_VDSL_DNS_CACHE
#ifdef AEI_HOSTNAME_V6

		char name[128] = {0};
		snprintf( name, sizeof(name)-1, "[%s]", m->cname );
		retval = cache_lookup_name( name, m->ip );
#endif
#endif
	}
	else if( query_type == PTR )
	{
		retval = 0;
		/* reverse lookup */
#ifdef DNS_DYN_CACHE
#ifdef AEI_VDSL_DNS_CACHE
          if(dns_cache_enabled())
#endif
		if ((dns_entry = dns_dyn_find(m)))
		{
			strncpy(m->cname, dns_entry->cname,NAME_SIZE-1);
			m->ttl = abs(dns_entry->expiry - time(NULL));
			retval = 1;
			debug("TYPE==PTR.... %s, srcPort=%d, retval=%d\n", m->cname,  ((struct sockaddr_in *)&m->src_info)->sin_port, retval);

		}
#endif
	}
	else /* BRCM:  For all other query_type including TXT, SPF... */
	{
		retval = 0;
	}

	inet_ntop( m->src_info.ss_family,
	           get_in_addr(&m->src_info),
	           srcIP, INET6_ADDRSTRLEN );
	cmsLog_notice("dns_handle_new_query: %s %s, srcPort=%d, retval=%d\n",
	              m->cname, srcIP,
	              ((struct sockaddr_in *)&m->src_info)->sin_port,
	              retval);

	switch( retval )
	{
	case 0:
	{
		char dns[INET6_ADDRSTRLEN];
		int proto = 0;

#ifdef AEI_PRIMARY_DNS_CHECK
		start_primary_dns_check_v4_and_v6(m->message.question[0].type);
#endif

#ifdef AEI_DNS_PROBE
		if(Dns_probe_v4_and_v6_find_activate_dns(
		            m->message.question[0].type,
		            dns, &proto,0) >= 0)
#else
		if(dns_switch_v4_and_v6_find_using_dns(
		            m->message.question[0].type,
		            dns, &proto) >= 0)

#endif
		{
			struct sockaddr_storage sa;
			int sock;

			cmsLog_notice("Found dns %s for subnet %s", dns, srcIP);
#ifdef AEI_DNS_PROBE
			dns_list_add(m,0);
#else
			int switch_timeout = 0;
#ifdef AEI_PRIMARY_DNS_CHECK
			switch_timeout = 1;
#else
			switch_timeout = dns_switch_is_enable(m->message.question[0].type);
#endif

			dns_list_add(m,switch_timeout);
#endif

			if (proto == AF_INET)
			{
				sock = dns_querysock[0];
				((struct sockaddr_in *)&sa)->sin_port = PORT;
				inet_pton(proto, dns, &(((struct sockaddr_in *)&sa)->sin_addr));
			}
			else
			{
				sock = dns_querysock[1];
				((struct sockaddr_in6 *)&sa)->sin6_port = PORT;
				inet_pton( proto, dns,
				           &(((struct sockaddr_in6 *)&sa)->sin6_addr) );
			}
			sa.ss_family = proto;
			dns_write_packet( sock, &sa, m );
		}
		else
		{
			cmsLog_debug("No dns service.");
		}
		break;
	}



#ifdef AEI_HOSTNAME_V6
	case 1:
		// IPv4 and IPv6 caching, IPv6 just for hostname
		dns_construct_reply( m );

		if (m->src_info.ss_family == AF_INET)
			dns_write_packet(dns_sock[0], &m->src_info, m);
		else
			dns_write_packet(dns_sock[1], &m->src_info, m);
		break;

	case 2:
		dns_construct_reject_reply( m );

		if (m->src_info.ss_family == AF_INET)
			dns_write_packet(dns_sock[0], &m->src_info, m);
		else
			dns_write_packet(dns_sock[1], &m->src_info, m);
		debug("reject hit\n");
		break;
#else
	case 1:
		// Only IPv4 caching
		dns_construct_reply( m );
		dns_write_packet(dns_sock[0], &m->src_info, m);
		break;
#endif

	default:
		debug("Unknown query type: %d\n", query_type);
	}
}
/*****************************************************************************/
void dns_handle_request(dns_request_t *m)
{
	dns_request_t *ptr = NULL;

	/* request may be a new query or a answer from the upstream server */
	ptr = dns_list_find_by_id(m);

	if( ptr != NULL ) {
		debug("Found query in list; id 0x%04x flags 0x%04x\n ip %s - cname %s\n",
		      m->message.header.id, m->message.header.flags.flags,
		      m->ip, m->cname);

		/* message may be a response */
		if( m->message.header.flags.flags & 0x8000)
		{
			int sock;
			char srcIP[INET6_ADDRSTRLEN];

			if (ptr->src_info.ss_family == AF_INET)
				sock = dns_sock[0];
			else
				sock = dns_sock[1];

			inet_ntop( m->src_info.ss_family,
			           get_in_addr(&m->src_info),
			           srcIP, INET6_ADDRSTRLEN );

			debug("Replying with answer from %s, id 0x%04x\n",
			      srcIP, m->message.header.id);
			dns_write_packet( sock, &ptr->src_info, m );
#ifndef AEI_DNS_PROBE
			dns_list_unarm_requests_after_this( ptr, ptr->message.question[0].type);
			dns_set_last_active_v4_and_v6(ptr->message.question[0].type);
#endif
			dns_list_remove( ptr );

#ifdef DMP_X_ITU_ORG_GPON_1
			if( m->message.header.flags.f.rcode != 0 ) { // lookup failed
				dns_query_error++;
				debug("dns_query_error = %u\n", dns_query_error);
			}
#endif

#ifdef DNS_DYN_CACHE
#ifdef AEI_VDSL_DNS_CACHE
          if(dns_cache_enabled())
#endif
			if( m->message.question[0].type != AAA) /* No cache for IPv6 */
			{
				dns_dyn_cache_add(m);
			}

#endif
#ifdef AEI_DNS_PROBE
			dns_probe_v4_and_v6_activate(&(m->src_info));
#endif
		}
		else
		{
			debug( "Duplicate query to %s (retx_count=%d)",
			       m->cname, ptr->retx_count );

			if (ptr->retx_count < MAX_RETX_COUNT)
			{
				char dns[INET6_ADDRSTRLEN];
				int proto = 0;


				ptr->retx_count++;
				cmsLog_debug("retx_count=%d", ptr->retx_count);
#ifdef AEI_DNS_PROBE
				int rex = 1;
				if(ptr->retx_count <= 2 && m->message.question[0].type == AAA)
				{
					/*in case DNS server valid, test in win7, ping one domain name, find that it first query with type A to get IPv4 address,
					if it get IPv4 address reponse, it will query with type AAA to get IPv6 address, if not get reponse will retry 3 times*/
					rex = 0;
				}

				if(Dns_probe_v4_and_v6_find_activate_dns(
				            m->message.question[0].type,
				            dns, &proto,rex) >= 0)
#else
				if(dns_switch_v4_and_v6_find_using_dns(
				            m->message.question[0].type,
				            dns, &proto) >= 0)
#endif
				{
					struct sockaddr_storage sa;
					int sock = 0;


					if (proto == AF_INET)
					{
						sock = dns_querysock[0];
						((struct sockaddr_in *)&sa)->sin_port = PORT;
						inet_pton( proto, dns,
						           &(((struct sockaddr_in *)&sa)->sin_addr) );
					}
					else
					{
						sock = dns_querysock[1];
						((struct sockaddr_in6 *)&sa)->sin6_port = PORT;
						inet_pton( proto, dns,
						           &(((struct sockaddr_in6 *)&sa)->sin6_addr) );
					}
					sa.ss_family = proto;
					dns_write_packet( sock, &sa, m );
				}
				else
				{
					cmsLog_debug("No dns service for duplicate query??");
				}
			}
			else
			{
				debug("=>drop! retx limit reached.\n");
			}
		}
	}
	else
	{
		dns_handle_new_query( m );
	}

	debug("dns_handle_request: done\n\n");
}

/*****************************************************************************/
static void processCmsMsg(void)
{
	CmsMsgHeader *msg;
	CmsRet ret;

	while( (ret = cmsMsg_receiveWithTimeout(msgHandle, &msg, 0)) == CMSRET_SUCCESS) {
		switch(msg->type) {
		case CMS_MSG_SET_LOG_LEVEL:
			cmsLog_debug("got set log level to %d", msg->wordData);
			cmsLog_setLevel(msg->wordData);
			if ((ret = cmsMsg_sendReply(msgHandle, msg, CMSRET_SUCCESS)) != CMSRET_SUCCESS) {
				cmsLog_error("send response for msg 0x%x failed, ret=%d", msg->type, ret);
			}
			break;
		case CMS_MSG_SET_LOG_DESTINATION:
			cmsLog_debug("got set log destination to %d", msg->wordData);
			cmsLog_setDestination(msg->wordData);
			if ((ret = cmsMsg_sendReply(msgHandle, msg, CMSRET_SUCCESS)) != CMSRET_SUCCESS) {
				cmsLog_error("send response for msg 0x%x failed, ret=%d", msg->type, ret);
			}
			break;

		case CMS_MSG_DNSPROXY_RELOAD:
			cmsLog_debug("received CMS_MSG_DNSPROXY_RELOAD\n");
			/* Reload config file */
#ifdef DNS_DYN_CACHE
			dns_dyn_hosts_add();
#endif

			/* load the /var/wandns into the linked list for dns/subnet pair */
			//dns_subnet_init();

			/*reload hostname*/
			cmsLog_debug("IPv4 reload hostname\n");
			cache_purge( config.purge_time );

			//AEI
#ifdef AEI_DNS_PROBE
			dns_wanup = dns_probe_v4_and_v6_init();
#else
			dns_wanup = dns_switch_v4_and_v6_init();
#endif
			/*
			 * During CDRouter dhcp scaling tests, this message is sent a lot to dnsproxy.
			 * To make things more efficient/light weight, the sender of the message does
			 * not expect a reply.
			 */
			break;

#ifdef SUPPORT_DEBUG_TOOLS

		case CMS_MSG_DNSPROXY_DUMP_STATUS:
			printf("\n============= Dump dnsproxy status=====\n");
			printf("config.name_server=%s config.domain=%s\n",
			       config.name_server, config.domain_name);
			dns_list_print();
			dns_dyn_print();
			break;

		case CMS_MSG_DNSPROXY_DUMP_STATS:
			printf("stats dump not implemented yet\n");
			break;

#endif /* SUPPORT_DEBUG_TOOLS */

#ifdef DMP_X_ITU_ORG_GPON_1
		case CMS_MSG_DNSPROXY_GET_STATS:
		{
			char buf[sizeof(CmsMsgHeader) + sizeof(DnsGetStatsMsgBody)]= {0};
			CmsMsgHeader *replyMsgPtr = (CmsMsgHeader *) buf;
			DnsGetStatsMsgBody *dnsStats = (DnsGetStatsMsgBody *) (replyMsgPtr+1);


			// Setup response message.
			replyMsgPtr->type = msg->type;
			replyMsgPtr->dst = msg->src;
			replyMsgPtr->src = EID_DNSPROXY;
			replyMsgPtr->flags.all = 0;
			replyMsgPtr->flags_response = 1;
			//set dns query error counter
			replyMsgPtr->dataLength = sizeof(DnsGetStatsMsgBody);
			dnsStats->dnsErrors = dns_query_error;

			cmsLog_notice("dns query error is %d", dns_query_error);
			// Attempt to send CMS response message & test result.
			ret = cmsMsg_send(msgHandle, replyMsgPtr);
			if (ret != CMSRET_SUCCESS)
			{
				// Log error.
				cmsLog_error("Send message failure, cmsReturn: %d", ret);
			}
		}
		break;
#endif

		default:
			cmsLog_error("unrecognized msg 0x%x", msg->type);
			break;
		}
#ifdef AEI_COVERITY_FIX
		/*CID 12493 Use of untrusted scalar value */
		if(msg != NULL)
#endif
			CMSMEM_FREE_BUF_AND_NULL_PTR(msg);

	}

	if (ret == CMSRET_DISCONNECTED) {
		cmsLog_error("lost connection to smd, exiting now.");
		dns_main_quit = 1;
	}
}

/*****************************************************************************/
int dns_main_loop()
{
	struct timeval tv, *ptv;
	fd_set active_rfds;
	int retval;
	dns_request_t m;
	dns_request_t *ptr, *next;
	int next_request_time;
	int next_probe_time = 1;

	while( !dns_main_quit )
	{

		next_request_time = dns_list_next_time();
		if (next_request_time)
		{
			if (next_request_time < next_probe_time || !next_probe_time)
			{
				debug("use next_request_time = %d", next_request_time);
				tv.tv_sec = next_request_time;
			}
			else
			{
				tv.tv_sec = next_probe_time;
			}
		}
		else
		{
			tv.tv_sec = next_probe_time;
		}

		tv.tv_usec = 0;
		if (tv.tv_sec == 0)
		{	/* To wait indefinitely */
			ptv = NULL;
			debug("\n\n=============select will wait indefinitely============");
		}
		else
		{
			tv.tv_usec = 0;
			ptv = &tv;
			debug("select timeout = %lu seconds", tv.tv_sec);
		}


		/* copy the main rfds in the active one as it gets modified by select*/
		active_rfds = rfds;
		retval = select( FD_SETSIZE, &active_rfds, NULL, NULL, ptv );

		if (retval) {
			debug("received something");

			if (FD_ISSET(msg_fd, &active_rfds)) { /* message from ssk */
				debug("received cms message");
				processCmsMsg();
			} else if ((dns_sock[0] > 0) && FD_ISSET(dns_sock[0], &active_rfds)) {
				debug("received DNS message (LAN side IPv4)");
				/* data is now available */
				bzero(&m, sizeof(dns_request_t));
				//BRCM
				if (dns_read_packet(dns_sock[0], &m) == 0) {
                    if(!dnsPrefer)
                        m.message.question[0].type = A;
                    else
                        m.message.question[0].type = AAA;
					dns_handle_request( &m );
				}
			} else if ((dns_sock[1] > 0) && FD_ISSET(dns_sock[1], &active_rfds)) {
				debug("received DNS message (LAN side IPv6)");
				/* data is now available */
				bzero(&m, sizeof(dns_request_t));
				//BRCM
				if (dns_read_packet(dns_sock[1], &m) == 0) {
                    if(!dnsPrefer)
                        m.message.question[0].type = A;
                    else
                        m.message.question[0].type = AAA;
					dns_handle_request( &m );
				}
			} else if ((dns_querysock[0] > 0) &&
			           FD_ISSET(dns_querysock[0], &active_rfds)) {
				debug("received DNS response (WAN side IPv4)");
				bzero(&m, sizeof(dns_request_t));
#ifdef AEI_DNS_PROBE
				if (dns_read_packet(dns_querysock[0], &m ) == 0 && !dns_probe_v4_and_v6_response(&m))
#else
				if (dns_read_packet(dns_querysock[0], &m ) == 0 && !primary_dns_check_v4_and_v6(&m))
#endif
					dns_handle_request( &m );
			} else if ((dns_querysock[1] > 0) &&
			           FD_ISSET(dns_querysock[1], &active_rfds)) {
				debug("received DNS response (WAN side IPv6)");
				bzero(&m, sizeof(dns_request_t));
#ifdef AEI_DNS_PROBE
				if (dns_read_packet(dns_querysock[1], &m) == 0 && !dns_probe_v4_and_v6_response(&m))
#else
				if (dns_read_packet(dns_querysock[1], &m) == 0 && !primary_dns_check_v4_and_v6(&m))
#endif
					dns_handle_request( &m );
			}
		} else { /* select time out */
			time_t now = time(NULL);

#ifndef AEI_DNS_PROBE
			int doSwitch_a = 0;
			int doSwitch_aaa = 0;
#ifdef AEI_PRIMARY_DNS_CHECK
			if (dproxy_active_a && (primary_active_a || (dns_a_recover_time && now >= dns_a_recover_time)))
#else
			if (dproxy_active_a && (dns_a_recover_time && now >= dns_a_recover_time))
#endif
			{
				dns_switchback_v4_and_v6(A);
			}
#ifdef AEI_PRIMARY_DNS_CHECK
			if (dproxy_active_aaa && (primary_active_aaa || (dns_aaa_recover_time && now >= dns_aaa_recover_time)))
#else
			if (dproxy_active_aaa && (dns_aaa_recover_time && now >= dns_aaa_recover_time))
#endif
			{
				dns_switchback_v4_and_v6(AAA);
			}
#endif
			ptr = dns_request_list;
			while (ptr) {
				next = ptr->next;

				if (ptr->expiry <= now) {
					char date_time_buf[DATE_TIME_BUFLEN];
					get_date_time_str(date_time_buf, sizeof(date_time_buf));

					debug("removing expired request %p\n", ptr);
					debug("%s dnsproxy: query for %s timed out after %d secs "
					      "(type=%d switch_on_timeout=%d retx_count=%d)\n",
					      date_time_buf, ptr->cname, DNS_TIMEOUT,
					      (unsigned int) ptr->message.question[0].type,
					      ptr->switch_on_timeout, ptr->retx_count);
#ifndef AEI_DNS_PROBE
					if (ptr->switch_on_timeout)
					{
						if(ptr->message.question[0].type == A)
						{
							doSwitch_a = 1;
						}
						else if(ptr->message.question[0].type == AAA)
						{
							doSwitch_aaa = 1;
						}

					}
#endif

					dns_list_remove(ptr);
				}

				ptr = next;
			}

#ifndef AEI_DNS_PROBE
			if (dproxy_active_a && doSwitch_a)
			{
				dns_switch_v4_and_v6(A);
			}

			if (dproxy_active_aaa && doSwitch_aaa)
			{
				dns_switch_v4_and_v6(AAA);
			}
#endif

		} /* if (retval) */

#ifdef AEI_DNS_PROBE
		next_probe_time = dns_probe_v4_and_v6();
#endif


	}  /* while (!dns_main_quit) */
	return 0;
}


/*
 * Return a buffer which contains the current date/time.
 */
void get_date_time_str(char *buf, unsigned int buflen)
{
	time_t t;
	struct tm *tmp;

	memset(buf, 0, buflen);

	t = time(NULL);
	tmp = localtime(&t);
	if (tmp == NULL) {
		debug_perror("could not get localtime");
		return;
	}

	strftime(buf, buflen, "[%F %k:%M:%S]", tmp);

}


/*****************************************************************************/
void debug_perror( char * msg ) {
	debug( "%s : %s\n" , msg , strerror(errno) );
}

#if 0 //BRCM: Mask the debug() function. It's redefined by cmsLog_debug()
#ifdef DPROXY_DEBUG
/*****************************************************************************/
void debug(char *fmt, ...)
{
#define MAX_MESG_LEN 1024

	va_list args;
	char text[ MAX_MESG_LEN ];

	sprintf( text, "[ %d ]: ", getpid());
	va_start (args, fmt);
	vsnprintf( &text[strlen(text)], MAX_MESG_LEN - strlen(text), fmt, args);
	va_end (args);

	printf(text);
#if 0 //BRCM 
	if( config.debug_file[0] ) {
		FILE *fp;
		fp = fopen( config.debug_file, "a");
		if(!fp) {
			syslog( LOG_ERR, "could not open log file %m" );
			return;
		}
		fprintf( fp, "%s", text);
		fclose(fp);
	}


	/** if not in daemon-mode stderr was not closed, use it. */
	if( ! config.daemon_mode ) {
		fprintf( stderr, "%s", text);
	}
#endif
}

#endif
#endif
/*****************************************************************************
 * print usage informations to stderr.
 *
 *****************************************************************************/
void usage(char * program , char * message ) {
	fprintf(stderr,"%s\n" , message );
	fprintf(stderr,"usage : %s [-c <config-file>] [-d] [-h] [-P]\n", program );
	fprintf(stderr,"\t-c <config-file>\tread configuration from <config-file>\n");
	fprintf(stderr,"\t-d \t\trun in debug (=non-daemon) mode.\n");
	fprintf(stderr,"\t-D \t\tDomain Name\n");
	fprintf(stderr,"\t-P \t\tprint configuration on stdout and exit.\n");
	fprintf(stderr,"\t-v \t\tset verbosity, where num==0 is LOG_ERROR, 1 is LOG_NOTICE, all others is LOG_DEBUG\n");
	fprintf(stderr,"\t-h \t\tthis message.\n");
}
/*****************************************************************************
 * get commandline options.
 *
 * @return 0 on success, < 0 on error.
 *****************************************************************************/
int get_options( int argc, char ** argv )
{
	char c = 0;
	int not_daemon = 0;
	int want_printout = 0;
	char * progname = argv[0];
	SINT32 logLevelNum;
	CmsLogLevel logLevel=DEFAULT_LOG_LEVEL;
	//UBOOL8 useConfiguredLogLevel=TRUE;

	cmsLog_init(EID_DNSPROXY);

	conf_defaults();
#if 1
	while( (c = getopt( argc, argv, "cD:dhPv:")) != EOF ) {
		switch(c) {
		case 'c':
			conf_load(optarg);
			break;
		case 'd':
			not_daemon = 1;
			break;
		case 'D':
			strncpy(config.domain_name, optarg,255);
			break;
		case 'h':
			usage(progname,"");
			return -1;
		case 'P':
			want_printout = 1;
			break;
		case 'v':
			logLevelNum = atoi(optarg);
			if (logLevelNum == 0)
			{
				logLevel = LOG_LEVEL_ERR;
			}
			else if (logLevelNum == 1)
			{
				logLevel = LOG_LEVEL_NOTICE;
			}
			else
			{
				logLevel = LOG_LEVEL_DEBUG;
			}
			cmsLog_setLevel(logLevel);
			//useConfiguredLogLevel = FALSE;
			break;
		default:
			usage(progname,"");
			return -1;
		}
	}
#endif

#if 0
	/** unset daemon-mode if -d was given. */
	if( not_daemon ) {
		config.daemon_mode = 0;
	}

	if( want_printout ) {
		conf_print();
		exit(0);
	}
#endif

	return 0;
}
/*****************************************************************************/
void sig_hup (int signo)
{
	signal(SIGHUP, sig_hup); /* set this for the next sighup */
	conf_load (config.config_file);
}
/*****************************************************************************/
int main(int argc, char **argv)
{
	int pid;
	FILE *pidfp;

	/* get commandline options, load config if needed. */
	if(get_options( argc, argv ) < 0 ) {
		exit(1);
	}

	/* detach from terminal and detach from smd session group. */
	if (setsid() < 0)
	{
		cmsLog_error("could not detach from terminal");
		exit(-1);
	}

	/* ignore some common, problematic signals */
	signal(SIGINT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);

	signal(SIGHUP, sig_hup);
	dns_init();

//BRCM: Don't fork a task again!
#if 0
	if (config.daemon_mode) {
		/* Standard fork and background code */
		switch (fork()) {
		case -1:	/* Oh shit, something went wrong */
			debug_perror("fork");
			exit(-1);
		case 0:	/* Child: close off stdout, stdin and stderr */
			close(0);
			close(1);
			close(2);
			break;
		default:	/* Parent: Just exit */
			exit(0);
		}
	}
#endif

	/* AEI dump current PID */
	pid = getpid();
	if ((pidfp = fopen(pid_file, "w")) != NULL) {
		fprintf(pidfp, "%d\n", pid);
		fclose(pidfp);
	}

	dns_main_loop();

	return 0;
}

