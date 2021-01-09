#ifndef _CTL_NID_H
#define _CTL_NID_H

//
// Ctrl Layer Node ID definitions
//

#define __CTL_NID_PREFIX 	"ctl."


#define NID_CORE 	__CTL_NID_PREFIX"core"


#define NID_TR69C	__CTL_NID_PREFIX"tr69c"
#define NID_PMD		__CTL_NID_PREFIX"pmd"
#define NID_RTD		__CTL_NID_PREFIX"rtd"	// Router Daemon
#define NID_PPP		__CTL_NID_PREFIX"ppp"
#define NID_DHCPC	__CTL_NID_PREFIX"dhcpc"
#define NID_DHCPD	__CTL_NID_PREFIX"dhcpd"
//   EID_FTPD=25,
//   EID_TFTPD=26,
//   EID_TFTP=27,
//   EID_DNSPROBE=28,
//   EID_SYSLOGD=30,
//   EID_KLOGD=31,
//   EID_DDNSD=33,
//   EID_ZEBRA=34,
//   EID_RIPD=35,
//   EID_SNTP=36,
//   EID_URLFILTERD=37,
//   EID_IGMP=38,
//   EID_PING=40,
#define NID_DHCP6C	__CTL_NID_PREFIX"dhcp6c"
#define NID_DHCP6S	__CTL_NID_PREFIX"dhcp6s"
#define NID_RADVD	__CTL_NID_PREFIX"radvd"
#define NID_DNSPROXY	__CTL_NID_PREFIX"dnsproxy"
//   EID_IPPD=45,
//   EID_FTP=46,
#define NID_MLD		__CTL_NID_PREFIX"mld"
//   EID_DSLDIAGD=48,
//   EID_SOAPSERVER=49,
//   EID_PWRCTL=50,
//   EID_HOTPLUG=51,
//   EID_L2TPD=52,
//   EID_SAMBA=53,
//   EID_PPTPD=54,
//   EID_UNITTEST=90,
//   EID_MISC=91,
//   EID_WLWPS=93,
//   EID_CMFD=94,
#define NID_MCPD	__CTL_NID_PREFIX"mcpd"
//   EID_MOCAD=96,
//   EID_RNGD=97,
//   EID_DMSD=98,
//   EID_DECTDBGD=99,
//   EID_SWMDK=100,

//   EID_TRACEROUTE=101,
//   EID_TR143_DLD=110,
//   EID_TR143_UPLD=111,
//   EID_TR143_ECHO=112,
//   EID_MYNETWORK=113,

#endif //_CTL_NID_H
