#ifndef _BR_FDB_H
#define _BR_FDB_H

#if defined(CONFIG_MIPS_BRCM)

/* these are in addition to the defines in if_bridge.h, 
   br_mld.h and br_igmp.h */
#define BRCTL_ADD_FDB_ENTRIES 25
#define BRCTL_DEL_FDB_ENTRIES 26

extern int br_fdb_adddel_static(struct net_bridge *br, 
                                struct net_bridge_port *source,
                                const unsigned char *addr, int bInsert);
#endif /* CONFIG_MIPS_BRCM */

#endif /* _BR_FDB_H */

