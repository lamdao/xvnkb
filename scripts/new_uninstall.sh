#!/bin/bash
#----------------------------------------------------------------------------#
#  new_uninstall.sh -- new style uninstallation for xvnkb                    #
#----------------------------------------------------------------------------#
#  copyright         : (C) 2002 by Dao Hai Lam                               #
#                      VISC Software & Security Consultant Company           #
#                      Hall 3, Quang Trung Software City                     #
#                      Tan Chanh Hiep Ward, District 12,                     #
#                      Ho Chi Minh city, VIETNAM                             #
#  website           : http://www.visc-network.com                           #
#  email             : lam@visc-network.com                                  #
#  last modify       : Tue, 13 Aug 2002 03:14:07 +0700                       #
#----------------------------------------------------------------------------#
#                                                                            #
#   This program is free software; you can redistribute it and/or modify     #
#   it under the terms of the GNU General Public License as published by     #
#   the Free Software Foundation; either version 2 of the License, or        #
#   (at your option) any later version.                                      #
#                                                                            #
#----------------------------------------------------------------------------#

PREFIX="/usr/local"

ID=`id -u`
LD="/etc/ld.so.preload"
SO="/lib/xvnkb.so"

if [ "$ID" != "0" ]; then
	echo "You must be root to uninstall xvnkb."
	echo "Please use \"su -c 'make uninstall'\" or \"su -c $0\""
	exit 1
fi

if [ -f $LD -a "`grep xvnkb.so $LD`" != "" ]; then
	grep -v xvnkb.so $LD > $LD.xvnkb
	/bin/mv -f $LD.xvnkb $LD
fi

if [ -f $SO ]; then
	XVNKB_CORE=`ls -l $SO | sed -e "s/.*-> //"`
	if [ -n "$XVNKB_CORE" ]; then
		chattr -i $XVNKB_CORE
		echo "You can remove $SO & $XVNKB_CORE safely in the *NEXT* boot time"
	fi
fi
