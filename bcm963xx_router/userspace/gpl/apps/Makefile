#***********************************************************************
#
#  Copyright (c) 2006  Broadcom Corporation
#  All Rights Reserved
#
#  <:label-BRCM:2006:GPL/GPL:standard
#  
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License, version 2, as published by
#  the Free Software Foundation (the "GPL").
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  
#  A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
#  writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
#  Boston, MA 02111-1307, USA.
#  
#  :>
#
#***********************************************************************/


#
# You do not need to modify this Makefile to add an app.
# Simply create a .autodetect in the subdir and this Makefile will enter
# that directory during make and make clean.  (Auto detected directories
# are listed in the AUTODETECT_SUBDIRS variable.  Type make show_subdirs)
#
HARDCODED_SUBDIRS := atm2684 bridge-utils busybox sysstat ebtables ftpd \
           iproute2-2.6.37 iptables radvd udhcp urlfilterd zebra \
           dynahelper mtd-utils ntfs-3g samba iperf conntrack openl2tpd rng-tools-2 pptp \
           jamvm-1.5.4 felix_framework mtd-util

ifneq ($(strip $(AEI_VDSL_CUSTOMER_NTPV4)),)
HARDCODED_SUBDIRS += ntpclient
endif

ifneq ($(strip $(AEI_DPROXY_V4_AND_V6)),)
HARDCODED_SUBDIRS += dproxy-nexgen-aei
else
HARDCODED_SUBDIRS += dproxy-nexgen
endif

SUBDIRS = $(HARDCODED_SUBDIRS) $(AUTODETECT_SUBDIRS) $(MODSW_SUBDIRS)


# === this is the default target ===
# Need to add a level of indirection here so that AUTODETECT_SUBDIRS and
# MODSW_SUBDIRS can be populated in make.common/make.modsw before we build.
#
all : make_all_subdirs


#
# Set our CommEngine directory (by splitting the pwd into two words
# at /userspace and taking the first word only).
# Then include the common defines under CommEngine.
# You do not need to modify this part.
#
CURR_DIR := $(shell pwd)
BUILD_DIR:=$(subst /userspace, /userspace,$(CURR_DIR))
BUILD_DIR:=$(word 1, $(BUILD_DIR))

# automatically set BCM_BASE_BUILD_DIR so that the modsw dirs can compile
BCM_BASE_BUILD_DIR := $(BUILD_DIR)
export BCM_BASE_BUILD_DIR


include $(BUILD_DIR)/make.common

export BUILD_DIR


#
# We need to declare these directory names as phony targets,
# otherwise make will think the directories themselves are
# the targets and will never execute the cmds.
# See GNU Make, 4.6 
#
.PHONY : $(SUBDIRS)
make_all_subdirs : $(SUBDIRS)


clean: generic_subdir_clean


modsw_clean: generic_modsw_base_clean


##############################################################
# 
# Rules for inidividual apps
# apps can be compiled or not depending on the profile (which
# is modified via make menuconfig)
#
##############################################################


$(AUTODETECT_SUBDIRS) $(MODSW_SUBDIRS): 
	$(MAKE) -C $@


ifneq ($(strip $(BUILD_BRCTL)),)
bridge-utils: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfj bridge-utils.tar.bz2 2> /dev/null || true)
	$(MAKE) -C bridge-utils $(BUILD_BRCTL)
else
bridge-utils: sanity_check
endif


ifeq ($(strip $(BRCM_IKOS)),y)
BRCMCONFIG=ikos.config
else
BRCMCONFIG=brcm.config
endif
export BRCMCONFIG

PERL5LIB=$(HOSTTOOLS_PERL_LIB)
export PERL5LIB

ifneq ($(strip $(BUILD_BUSYBOX)),)
busybox: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfj busybox.tar.bz2 2> /dev/null || true)
	cd busybox; cp -f .config .config.old; cat $(BRCMCONFIG) > .config ; \
	for i in config.d/[0-9]*.conf ; do echo "config script $$i" ; $$i ; done
	$(MAKE) -C busybox include/autoconf.h
	$(MAKE) -C busybox install
else
busybox: sanity_check
	@echo "skipping busybox (not configured)"
endif

ifneq ($(strip $(BUILD_SYSSTAT)),)
sysstat: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfj sysstat.tar.bz2 2> /dev/null || true)
	cd sysstat
	$(MAKE) -C sysstat install
else
sysstat: sanity_check
	@echo "skipping sysstat (not configured)"
endif


ifneq ($(strip $(BUILD_DPROXY)),)

ifneq ($(strip $(AEI_DPROXY_V4_AND_V6)),)
dproxy-nexgen-aei: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	$(MAKE) -C dproxy-nexgen-aei $(BUILD_DPROXY)
else
dproxy-nexgen: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfj dproxy-nexgen.tar.bz2 2> /dev/null || true)
	$(MAKE) -C dproxy-nexgen $(BUILD_DPROXY)
endif

else

ifneq ($(strip $(AEI_DPROXY_V4_AND_V6)),)
dproxy-nexgen-aei: sanity_check
else
dproxy-nexgen: sanity_check
endif
	@echo "skipping dproxy (not configured)"

endif

# in userapps->Dynamic ALG loader
ifneq ($(strip $(BUILD_DYNAHELPER)),)
dynahelper: sanity_check
	$(MAKE) -C dynahelper $(BUILD_DYNAHELPER)
else
dynahelper: sanity_check
	@echo "skipping dynahelper (not configured)"
endif


ifneq ($(strip $(BUILD_EBTABLES)),)
ebtables: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfj ebtables.tar.bz2 2> /dev/null || true)
	$(MAKE) -C ebtables $(BUILD_EBTABLES)
else
ebtables: sanity_check
	@echo "skipping ebtables (not configured)"
endif


# ftpd does sanity check in its own Makefile
ifneq ($(strip $(BUILD_FTPD)),)
ftpd:
	(tar xkfj ftpd.tar.bz2 2> /dev/null || true)
	$(MAKE) -C ftpd $(BUILD_FTPD)
else
ftpd:
	@echo "skipping ftpd (not configured)"
endif


# Build the iproute2 package whenever IPROUTE2, IPV6, or BRCM_KERNEL_NETQOS
# is defined.  In make menuconfig, "traffic control" enables BRCM_KERNEL_NETQOS
ifneq ($(strip $(BUILD_IPROUTE2)),)
DO_BUILD_IPROUTE2=y
endif

ifneq ($(strip $(BUILD_IPV6)),)
DO_BUILD_IPROUTE2=y
endif

ifneq ($(strip $(BRCM_KERNEL_NETQOS)),)
DO_BUILD_IPROUTE2=y
endif

ifneq ($(strip $(BUILD_GPONRG_OMCI_FULL)),)
DO_BUILD_IPROUTE2=y
endif

ifneq ($(strip $(DO_BUILD_IPROUTE2)),)
#iproute2: sanity_check
#	(tar xkfj iproute2.tar.bz2 2> /dev/null || true)
#	$(MAKE) -C iproute2 install
iproute2-2.6.37: sanity_check
#	(tar xkfj iproute2.tar.bz2 2> /dev/null || true)
	$(warning =================begine to compile iproute2-2.6.37=======================)
	$(MAKE) -C iproute2-2.6.37 dynamic
else
iproute2: sanity_check
	@echo "skipping iproute2 (not configured)"
endif

ifneq ($(strip $(BRCM_KERNEL_AUXFS_JFFS2)),)
# Always make flash utilities and installed executables
mtd-util:
	(cd mtd-util; $(MAKE); $(MAKE) install)
else
mtd-util:
	@echo "BRCM_KERNEL_AUXFS_JFFS2 not configured, skipping"
endif


# iptables is dependent on kernel netfilter modules
ifneq ($(strip $(BRCM_KERNEL_NETFILTER)),)
ifneq ($(strip $(BUILD_IPTABLES)),)
iptables: sanity_check
	(tar xkfj iptables.tar.bz2 2> /dev/null || true)
	$(MAKE) -C iptables $(BUILD_IPTABLES)
else
iptables: sanity_check
	@echo "skipping iptables (not configured)"
endif
else
iptables: sanity_check
	@echo Warning: To use iptables, you need to enable netfilter in the kernel !!!!!
endif


ifneq ($(strip $(BUILD_IPTABLES)),)
ifneq ($(strip $(BUILD_URLFILTER)),)
urlfilterd: sanity_check
	$(MAKE) -C urlfilterd $(BUILD_URLFILTER)
else
urlfilterd: sanity_check
endif
else
urlfilterd: sanity_check
	@echo Warning: To use urlfilterd, you need to enable iptables!!!!!
endif



ifneq ($(strip $(BUILD_IPV6)),)
radvd: sanity_check
#	(tar xkjf radvd.tar.bz2 2> /dev/null || true)
#	$(MAKE) -C radvd
	(tar xkzf radvd-1.8.tar.gz 2> /dev/null || true)
	$(MAKE) -C radvd-1.8
else
radvd: sanity_check
	@echo "skipping radvd (not configured)"
endif

ifneq ($(strip $(AEI_VDSL_CUSTOMER_NTPV4)),)
ntpclient: sanity_check
	$(MAKE) -C ntpclient install
else
ntpclient: sanity_check
	@echo "skipping ntpclient (not configured)"
endif

ifneq ($(strip $(BUILD_UDHCP)),)
udhcp: sanity_check
	$(MAKE) -C udhcp $(BUILD_UDHCP)
else
udhcp: sanity_check
	@echo "skipping udhcp (not configured)"
endif


ifneq ($(strip $(BUILD_ZEBRA)),)
zebra: sanity_check
	(tar xkfj zebra.tar.bz2 2> /dev/null || true)
	$(MAKE) -C zebra $(BUILD_ZEBRA)
else
zebra: sanity_check
	@echo "skipping zebra (not configured)"
endif

ifneq ($(strip $(BUILD_MTDUTILS)),)
mtd-utils: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfz mtd-utils.tar.gz 2> /dev/null || true)
	(cd mtd-utils; $(MAKE) install)
else
mtd-utils: sanity_check
	@echo "skipping mtd-utils (not configured)"
endif

ifneq ($(strip $(BUILD_NTFS_3G)),)
ntfs-3g: sanity_check
	(tar xkfz ntfs-3g.tar.gz 2> /dev/null || true)
	$(MAKE) -C ./ntfs-3g 
	install -m 755 ./ntfs-3g/libntfs-3g/.libs/libntfs-3g.so $(INSTALL_DIR)/lib/libntfs-3g.so.83
	install -m 755 ./ntfs-3g/src/.libs/ntfs-3g  $(INSTALL_DIR)/bin/ntfs-3g	
else
ntfs-3g: sanity_check
	@echo "skipping $@ (not configured)"
endif

ifneq ($(strip $(BUILD_SAMBA)),)
samba: sanity_check
	(tar xkfz samba.tar.gz 2> /dev/null || true)
	$(MAKE) -C ./samba -j 1
else
samba: sanity_check 
	@echo "skipping $@ (not configured)"
endif

ifneq ($(strip $(BUILD_IPERF)),)
iperf: sanity_check
	$(MAKE) -C ./iperf -j 1
else
iperf: sanity_check
	@echo "skipping $@ (not configured)"
endif

ifneq ($(strip $(BUILD_L2TPAC)),)
openl2tpd: sanity_check
	(tar xkjf openl2tpd.tar.bz2 2> /dev/null || true)
	$(MAKE) -C openl2tpd
else
openl2tpd: sanity_check
	@echo "skipping openl2tpd (not configured)"
endif

ifneq ($(strip $(BUILD_RNGD)),)
rng-tools-2: sanity_check
	mkdir -p $(INSTALL_DIR)/bin
	(tar xkfz rng-tools-2.tar.gz 2> /dev/null || true)
	($(MAKE) -C rng-tools-2 $(BUILD_RNGD))
else
rngd: sanity_check
	@echo "skipping rng-tools-2 (not configured)"
endif

ifneq ($(strip $(BUILD_PPTPAC)),)
pptp: sanity_check
	(tar xkjf pptp.tar.bz2 2> /dev/null || true)
	$(MAKE) -C pptp
else
pptp: sanity_check
	@echo "skipping pptp (not configured)"
endif

ifneq ($(strip $(BUILD_CONNTRACK_TOOLS)),)
conntrack: sanity_check
	(tar xkfz conntrack.tar.gz 2> /dev/null || true)
	$(MAKE) -C ./conntrack
else
conntrack: sanity_check
	@echo "skipping $@ (not configured)"
endif

ifneq ($(strip $(BUILD_OSGI_JVM)),)
jamvm-1.5.4: sanity_check
#	cd jamvm-1.5.4; ./configure --prefix=$(INSTALL_DIR)/usr/local/jamvm --host=mips-linux --target=mips-linux-uclibc --disable-dependency-tracking --disable-zip --with-classpath-install-dir=/usr/local/classpath
	(tar xkfz jamvm-1.5.4.tar.gz 2> /dev/null || true)
	cd jamvm-1.5.4/src; (ln -s arch/mips.h arch.h 2>/dev/null || true)
	$(MAKE) -C ./jamvm-1.5.4 install

felix_framework: sanity_check
	cd felix_framework; (tar xkfz ../felix.tar.gz 2> /dev/null || true)
	$(MAKE) -C ./felix_framework
#this bundle is used for debugging only.  Felix will run in the background, so this needs to be removed.
#	rm -f $(INSTALL_DIR)/usr/local/felix/bundle/org.apache.felix.gogo.shell-0.7.0-SNAPSHOT.jar

else
jamvm-1.5.4: sanity_check
	@echo "skipping $@ (not configured)"

felix_framework: sanity_check
	@echo "skipping $@ (not configured)"
endif

