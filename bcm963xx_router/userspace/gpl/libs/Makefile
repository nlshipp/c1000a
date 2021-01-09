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
HARDCODED_SUBDIRS := sqlite classpath-0.98

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
# Rules for inidividual libs
# libs can be compiled or not depending on the profile (which
# is modified via make menuconfig)
#
##############################################################


$(AUTODETECT_SUBDIRS) $(MODSW_SUBDIRS): 
	$(MAKE) -C $@


ifneq ($(strip $(BUILD_DLNA)),)
sqlite: sanity_check
	$(MAKE) -C sqlite dynamic
else
sqlite: sanity_check
	@echo "skipping SQLite (not configured)"
endif

ifneq ($(strip $(BUILD_OSGI_JVM)),)
classpath-0.98:
	(tar xkfz classpath-0.98.tar.gz 2> /dev/null || true)
	cd classpath-0.98; ./configure --host=mips-linux-uclibc --target=mips-linux-uclibc --enable-local-sockets --disable-gconf-peer --disable-gtk-peer --disable-plugin --enable-jni --disable-alsa --disable-dssi --disable-gjdoc --disable-libtool-lock --disable-default_toolkit --disable-gmp --disable-examples --without-x --prefix=$(INSTALL_DIR)/usr/local/classpath
	cd classpath-0.98; cp native/jni/java-nio/Makefile.modified native/jni/java-nio/Makefile
	cd classpath-0.98; cp native/jni/native-lib/Makefile.modified native/jni/native-lib/Makefile
	cd classpath-0.98; $(MAKE) install
	cd $(INSTALL_DIR)/usr/local/classpath/share/classpath; unzip -o glibj.zip
	cd $(INSTALL_DIR)/usr/local/classpath/share/classpath; rm -rf glibj.zip
	cp -f $(INSTALL_DIR)/usr/local/classpath/lib/classpath/libjavanet.so $(INSTALL_DIR)/lib/libjavanet.so
else
classpath-0.98:
	@echo "skipping classpath-0.98 (not configured)"
endif
