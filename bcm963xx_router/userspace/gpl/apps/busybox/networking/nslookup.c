/* vi: set sw=4 ts=4: */
/*
 * Mini nslookup implementation for busybox
 *
 * Copyright (C) 1999,2000 by Lineo, inc. and John Beppu
 * Copyright (C) 1999,2000,2001 by John Beppu <beppu@codepoet.org>
 *
 * Correct default name server display and explicit name server option
 * added by Ben Zeckel <bzeckel@hmc.edu> June 2001
 *
 * Licensed under GPLv2 or later, see file LICENSE in this tarball for details.
 */

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>
#include <arpa/inet.h>
#include "busybox.h"
#include "libbb.h"

#if defined(AEI_VDSL_SMARTLED) || defined (SUPPPORT_GPL_UNDEFINED)
#include "cms_msg.h"
#include "cms_log.h"

extern struct hostent *AEI_gethostbyname_txt(const char *hostname);
extern void AEI_sendTxtRecordForNslookup(void *msgHandle);
extern void AEI_cleanup();

static void *msgHandle = NULL;
#endif

/*
 * I'm only implementing non-interactive mode;
 * I totally forgot nslookup even had an interactive mode.
 *
 * This applet is the only user of res_init(). Without it,
 * you may avoid pulling in _res global from libc.
 */

/* Examples of 'standard' nslookup output
 * $ nslookup yahoo.com
 * Server:         128.193.0.10
 * Address:        128.193.0.10#53
 *
 * Non-authoritative answer:
 * Name:   yahoo.com
 * Address: 216.109.112.135
 * Name:   yahoo.com
 * Address: 66.94.234.13
 *
 * $ nslookup 204.152.191.37
 * Server:         128.193.4.20
 * Address:        128.193.4.20#53
 *
 * Non-authoritative answer:
 * 37.191.152.204.in-addr.arpa     canonical name = 37.32-27.191.152.204.in-addr.arpa.
 * 37.32-27.191.152.204.in-addr.arpa       name = zeus-pub2.kernel.org.
 *
 * Authoritative answers can be found from:
 * 32-27.191.152.204.in-addr.arpa  nameserver = ns1.kernel.org.
 * 32-27.191.152.204.in-addr.arpa  nameserver = ns2.kernel.org.
 * 32-27.191.152.204.in-addr.arpa  nameserver = ns3.kernel.org.
 * ns1.kernel.org  internet address = 140.211.167.34
 * ns2.kernel.org  internet address = 204.152.191.4
 * ns3.kernel.org  internet address = 204.152.191.36
 */

static int print_host(const char *hostname, const char *header)
{
	/* We can't use xhost2sockaddr() - we want to get ALL addresses,
	 * not just one */
	struct addrinfo *result = NULL;
	int rc;
	struct addrinfo hint;

	memset(&hint, 0 , sizeof(hint));
	/* hint.ai_family = AF_UNSPEC; - zero anyway */
	/* Needed. Or else we will get each address thrice (or more)
	 * for each possible socket type (tcp,udp,raw...): */
	hint.ai_socktype = SOCK_STREAM;
	// hint.ai_flags = AI_CANONNAME;
	rc = getaddrinfo(hostname, NULL /*service*/, &hint, &result);

	if (!rc) {
		struct addrinfo *cur = result;
		unsigned cnt = 0;

		printf("%-10s %s\n", header, hostname);
		// puts(cur->ai_canonname); ?
		while (cur) {
			char *dotted, *revhost;
			dotted = xmalloc_sockaddr2dotted_noport(cur->ai_addr);
			revhost = xmalloc_sockaddr2hostonly_noport(cur->ai_addr);

			printf("Address %u: %s%c", ++cnt, dotted, revhost ? ' ' : '\n');
			if (revhost) {
				puts(revhost);
				if (ENABLE_FEATURE_CLEAN_UP)
					free(revhost);
			}
			if (ENABLE_FEATURE_CLEAN_UP)
				free(dotted);
			cur = cur->ai_next;
		}
	} else {
#if ENABLE_VERBOSE_RESOLUTION_ERRORS
		bb_error_msg("can't resolve '%s': %s", hostname, gai_strerror(rc));
#else
		bb_error_msg("can't resolve '%s'", hostname);
#endif
	}
	if (ENABLE_FEATURE_CLEAN_UP)
		freeaddrinfo(result);
	return (rc != 0);
}

/* lookup the default nameserver and display it */
static void server_print(void)
{
	char *server;
	struct sockaddr *sa;

#if ENABLE_FEATURE_IPV6
	sa = (struct sockaddr*)_res._u._ext.nsaddrs[0];
	if (!sa)
#endif
		sa = (struct sockaddr*)&_res.nsaddr_list[0];
	server = xmalloc_sockaddr2dotted_noport(sa);

	print_host(server, "Server:");
	if (ENABLE_FEATURE_CLEAN_UP)
		free(server);
	bb_putchar('\n');
}

/* alter the global _res nameserver structure to use
   an explicit dns server instead of what is in /etc/resolv.conf */
static void set_default_dns(const char *server)
{
	len_and_sockaddr *lsa;

	/* NB: this works even with, say, "[::1]:5353"! :) */
	lsa = xhost2sockaddr(server, 53);

	if (lsa->u.sa.sa_family == AF_INET) {
		_res.nscount = 1;
		/* struct copy */
		_res.nsaddr_list[0] = lsa->u.sin;
	}
#if ENABLE_FEATURE_IPV6
	/* Hoped libc can cope with IPv4 address there too.
	 * No such luck, glibc 2.4 segfaults even with IPv6,
	 * maybe I misunderstand how to make glibc use IPv6 addr?
	 * (uclibc 0.9.31+ should work) */
	if (lsa->u.sa.sa_family == AF_INET6) {
		// glibc neither SEGVs nor sends any dgrams with this
		// (strace shows no socket ops):
		//_res.nscount = 0;
		_res._u._ext.nscount = 1;
		/* store a pointer to part of malloc'ed lsa */
		_res._u._ext.nsaddrs[0] = &lsa->u.sin6;
		/* must not free(lsa)! */
	}
#endif
}

#if defined (SUPPPORT_GPL)
/* only works for IPv4 */
static int addr_fprint(char *addr)
{
	uint8_t split[4];
	uint32_t ip;
	uint32_t *x = (uint32_t *) addr;

	ip = ntohl(*x);
	split[0] = (ip & 0xff000000) >> 24;
	split[1] = (ip & 0x00ff0000) >> 16;
	split[2] = (ip & 0x0000ff00) >> 8;
	split[3] = (ip & 0x000000ff);
	printf("%d.%d.%d.%d", split[0], split[1], split[2], split[3]);
	return 0;
}

/* takes the NULL-terminated array h_addr_list, and
 * prints its contents appropriately
 */
static int addr_list_fprint(char **h_addr_list)
{
	int i, j;
	char *addr_string = (h_addr_list[1])
		? "Addresses:" : "Address:";

	printf("%s", addr_string);
	for (i = 0, j = 0; h_addr_list[i]; i++, j++) {
		addr_fprint(h_addr_list[i]);

		/* real nslookup does this */
		if (j == 4) {
			if (h_addr_list[i + 1]) {
				printf("\n          ");
			}
			j = 0;
		} else {
			if (h_addr_list[i + 1]) {
				printf(", ");
			}
		}

	}
	printf("\n");
	return 0;
}

/* print the results as nslookup would */
static struct hostent *hostent_fprint(struct hostent *host, const char *server_host)
{
	if (host) {
		printf("%s     %s\n", server_host, host->h_name);
		addr_list_fprint(host->h_addr_list);
	} else {
		printf("*** Unknown host\n");
	}
	return host;
}

/* changes a c-string matching the perl regex \d+\.\d+\.\d+\.\d+
 * into a uint32_t
 */
static uint32_t str_to_addr(const char *addr)
{
	uint32_t split[4];
	uint32_t ip;

	sscanf(addr, "%d.%d.%d.%d",
		   &split[0], &split[1], &split[2], &split[3]);

	/* assuming sscanf worked */
	ip = (split[0] << 24) |
		(split[1] << 16) | (split[2] << 8) | (split[3]);

	return htonl(ip);
}

/* gethostbyaddr wrapper */
static struct hostent *gethostbyaddr_wrapper(const char *address)
{
	struct in_addr addr;

	addr.s_addr = str_to_addr(address);
	return gethostbyaddr((char *) &addr, 4, AF_INET);	/* IPv4 only for now */
}

/* To see whether is IPv4 addr */
static int is_ipv4_address(const char *s)
{
	while (*s) {
		if ((isdigit(*s)) || (*s == '.')) {
			s++;
			continue;
		}
		return 0;
	}
	return 1;
}

/* To see whether is IPv6 addr */
static int is_ipv6_address(const char *s)
{
    int i;
    for (i=0; i<=strlen(s); i++)
    {
        if (isdigit(s[i]) || (s[i] == ':') || (s[i] >= 65 && s[i] <= 70) || (s[i] >= 97 && s[i] <= 102))
        {
            continue;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}
#endif

/* ________________________________________________________________________ */

#if defined(SUPPPORT_GPL) || defined(SUPPPORT_GPL_UNDEFINED)
unsigned int get_curr_timestamp_ms()
{
        unsigned int timestamp = 0;

        struct timespec ts;
        int rc;

        rc = clock_gettime(CLOCK_MONOTONIC, &ts);
        if (rc == 0)
        {
                timestamp =ts.tv_sec*1000 + ts.tv_nsec/(1000*1000);
        }
        else
        {
                timestamp = time(0)*1000;
        }

	printf(" ts.tv_sec:%d  ts.tv_nsec:%d timestamp:%d\n",ts.tv_sec,  ts.tv_nsec,timestamp);
	return timestamp;
}

static struct hostent *hostent_fprint_with_responsetime(struct hostent *host, const char *server_host, unsigned int responsetime)
{
	if (host) {
		printf("%s:%d\n", "responsetime", responsetime);
		printf("%s:%s\n", server_host, host->h_name);
		addr_list_fprint(host->h_addr_list);
	} else {
		printf("resolve failed\n");
	}
	return host;
}
#endif

#if defined (SUPPPORT_GPL_UNDEFINED)
void AEI_sendEventMessageForNsloopup(int flag)
{
   char buf[sizeof(CmsMsgHeader) + sizeof(int)]={0};
   CmsMsgHeader *msg=(CmsMsgHeader *) buf;
   int *nslookupBody = (int*) (msg+1);
   CmsRet ret;

   *nslookupBody=flag;
   msg->type = CMS_MSG_NSLOOKUP_BACKOFF_RETURN;
   msg->src = EID_NSLOOKUP;
   msg->dst = EID_SSK;
   msg->flags_event = 1;
   msg->dataLength = sizeof(int);
   
   if ((ret = cmsMsg_send(msgHandle, msg)) != CMSRET_SUCCESS)
   {
      cmsLog_error("could not send out CMS_MSG_NSLOOKUP_BACKOFF_RETURN to SSK, ret=%d", ret);
   }
   else
   {
      cmsLog_error("sent out CMS_MSG_NSLOOKUP_BACKOFF_RETURN (state=%d) to SSK", flag);
   }
   cmsMsg_cleanup(&msgHandle);
   return;
}
#endif

int nslookup_main(int argc, char **argv) MAIN_EXTERNALLY_VISIBLE;
#ifdef AEI_FRONTIER_V2200H
int nslookup_main(int argc, char **argv)
{
	/* We allow 1 or 2 arguments.
	 * The first is the name to be looked up and the second is an
	 * optional DNS server with which to do the lookup.
	 * More than 3 arguments is an error to follow the pattern of the
	 * standard nslookup */
	if (!argv[1] || argv[1][0] == '-' || argc > 3)
		bb_show_usage();

	/* initialize DNS structure _res used in printing the default
	 * name server and in the explicit name server option feature. */
	res_init();
	/* rfc2133 says this enables IPv6 lookups */
	/* (but it also says "may be enabled in /etc/resolv.conf") */
	/*_res.options |= RES_USE_INET6;*/

	if (argv[2])
		set_default_dns(argv[2]);

	server_print();
	return print_host(argv[1], "Name:");
}

#else
int nslookup_main(int argc, char **argv)
{
	struct hostent *host = NULL;
#if defined(SUPPPORT_GPL) || defined(SUPPPORT_GPL_UNDEFINED)
	unsigned int timestamp = 0;
	unsigned int responsetime = 0;
#endif
#if ENABLE_FEATURE_IPV6
        struct sockaddr_in6 ip6;
        char name[128];
        int s = -1;
#endif

#if defined(AEI_VDSL_SMARTLED) || defined(SUPPPORT_GPL_UNDEFINED)
        cmsLog_init(EID_NSLOOKUP);
        cmsLog_setLevel(DEFAULT_LOG_LEVEL);
        cmsMsg_init(EID_NSLOOKUP, &msgHandle);
#endif

	/* We allow 1 or 2 arguments.
	 * The first is the name to be looked up and the second is an
	 * optional DNS server with which to do the lookup.
	 * More than 3 arguments is an error to follow the pattern of the
	 * standard nslookup */

	/* initialize DNS structure _res used in printing the default
	 * name server and in the explicit name server option feature. */
	res_init();
#if defined(SUPPPORT_GPL) || defined(SUPPPORT_GPL_UNDEFINED)
	if (argc < 2 || *argv[1]=='-' || argc > 4)
		bb_show_usage();
	else if(argc==3 || argc==4)
		set_default_dns(argv[2]);
#else
	if (!argv[1] || argv[1][0] == '-' || argc > 3)
		bb_show_usage();
	if (argv[2])
		set_default_dns(argv[2]);
#endif

	/* rfc2133 says this enables IPv6 lookups */
	/* (but it also says "may be enabled in /etc/resolv.conf") */
	/*_res.options |= RES_USE_INET6;*/

#if defined(AEI_VDSL_SMARTLED)
	if (is_ipv4_address(argv[1])) {
		host = gethostbyaddr_wrapper(argv[1]);
#if ENABLE_FEATURE_IPV6
        }else if (is_ipv6_address(argv[1])) {
            inet_pton(AF_INET6, argv[1], (struct sockaddr *) &ip6.sin6_addr);
            INET6_rresolve((struct sockaddr_in6 *) &ip6, 1);
            s = getnameinfo((struct sockaddr *) &ip6, sizeof(struct sockaddr_in6), name, sizeof(name), NULL, 0, 0);
#endif
        }else {
#if defined(SUPPPORT_GPL)
		if(argc==4 && !strcmp(argv[3], "nslookup_tmp")){
			timestamp = get_curr_timestamp_ms();
			host = gethostbyname(argv[1]);
			responsetime =  get_curr_timestamp_ms() - timestamp;
			hostent_fprint_with_responsetime(host, "hostname", responsetime);
		}else
                AEI_getaddrinfo_txt(argv[1]);
#else
		host = AEI_gethostbyname_txt(argv[1]);
#endif
	}
#if defined(SUPPPORT_GPL)
	if(argc==4 && !strcmp(argv[3], "nslookup_tmp")){
		AEI_sendNslookupResult(msgHandle);
	}else
#endif
	AEI_sendTxtRecordForNslookup(msgHandle);
	AEI_cleanup();

#if ENABLE_FEATURE_IPV6
	if (host || !s) {
#else
	if (host) {
#endif
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
#else
	if (is_ipv4_address(argv[1])) {
		host = gethostbyaddr_wrapper(argv[1]);
	} else {
#if defined(SUPPPORT_GPL) || defined(SUPPPORT_GPL_UNDEFINED)
		if(argc==4 && !strcmp(argv[3], "nslookup_tmp")){
			timestamp = get_curr_timestamp_ms();
			host = gethostbyname(argv[1]);
			responsetime =  get_curr_timestamp_ms() - timestamp;
			hostent_fprint_with_responsetime(host, "hostname", responsetime);
		}else
#endif
		host = xgethostbyname(argv[1]);
	}
#if defined(SUPPPORT_GPL) || defined(SUPPPORT_GPL_UNDEFINED)
	if(argc==4 && !strcmp(argv[3], "nslookup_tmp")){
		AEI_sendNslookupResult(msgHandle);
	}else
#endif
	hostent_fprint(host, "Name:  ");
	if (host) {
#if defined (SUPPPORT_GPL_UNDEFINED)	    
	    if(!strcmp(argv[1], "www.microsoft.com")||!strcmp(argv[1], "www.google.ca")||!strcmp(argv[1], "www.bellaliant.net"))
	        AEI_sendEventMessageForNsloopup(1);
#endif	
		return EXIT_SUCCESS;
	}
#if defined (SUPPPORT_GPL_UNDEFINED)	    
	if(!strcmp(argv[1], "www.microsoft.com")||!strcmp(argv[1], "www.google.ca")||!strcmp(argv[1], "www.bellaliant.net"))
	    AEI_sendEventMessageForNsloopup(0);
#endif
	return EXIT_FAILURE;
#endif

	server_print();
	return print_host(argv[1], "Name:");
}
#endif

/* $Id: nslookup.c,v 1.31 2004/01/30 22:40:05 andersen Exp $ */
