#!/bin/sh
#----------------------------------------------------------------------------#
#  localesetup.sh for xvnkb                                                  #
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

this=$0

usage() {
	echo
	echo "Usage:"
	echo "    $this [language.]UTF-8"
	echo "Ex:"
	echo "    $this en_US.UTF-8"
	echo "  or"
	echo "    $this vi_VN.UTF-8"
	echo
}

check_localedef() {
	local p
	local paths="/bin /sbin /usr/bin /usr/sbin /usr/local/bin /usr/local/sbin"

	for p in $paths; do
		if [ -f $p/localedef ]; then
			LOCALEDEF="$p/localedef"
			return 0
		fi
	done
	return 1
}

ID=`id -u`

if [ "$ID" != "0" ]; then
	echo "You must be root to run $this."
	exit 1
fi

if [ "$*" = "" ]; then
	usage
	exit
else
	if [ "`echo $1 | grep UTF-8`" = "" ]; then
		usage
		exit
	fi

	locale=$1
	check_localedef
	if [ "$?" != "0" ]; then
		echo
		echo "* Error: \"localedef\" not found!"
		echo "You have to install \"localedef\" utility to create locale information."
		echo "Please install \"localedef\" and try following command to create again:"
		echo
		echo "  # /usr/local/share/xvnkb/xvnkb.lconf.sh $locale"
		echo
		sleep 3
		exit
	fi

	ref=`echo $locale | sed -e "s/.UTF-8//"`
	if [ "$ref" = "$locale" ]; then
		ref="en_US"
	fi

	echo
	if [ ! -f /usr/share/locale/$locale/LC_IDENTIFICATION ]; then
		echo -n "Creating /usr/share/locale/$locale, please wait... "
		if [ ! -f /usr/lib/locale/$locale/LC_IDENTIFICATION ]; then
			mkdir -p /usr/share/locale/$locale
			$LOCALEDEF -ci $ref -f UTF-8 /usr/share/locale/$locale
		else
			ln -sf /usr/lib/locale/$locale /usr/share/locale
		fi
		echo done
	else
		echo "Locale $locale already exists in /usr/share/locale."
	fi

	if [ -f /usr/share/locale/$locale/LC_IDENTIFICATION -a \
		! -f /usr/lib/locale/$locale/LC_IDENTIFICATION ]; then
		echo -n "Creating /usr/lib/locale/$locale, please wait... "
		ln -sf /usr/share/locale/$locale /usr/lib/locale
		echo done
	else
		echo "Locale $locale already exists in /usr/lib/locale."
	fi
	echo
fi

