#!/bin/bash
#----------------------------------------------------------------------------#
#  new_install.sh -- new style installation for xvnkb                        #
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
	echo "You must be root to install xvnkb."
	echo "Please use \"su -c 'make install'\" or \"su -c $0\""
	exit 1
fi

if [ -f VERSION ]; then
	VERSION=`cat VERSION`;
else
	echo "Missing version information (file VERSION)!!!"
	exit 1
fi

OL="`echo $LD_PRELOAD | grep xvnkb.so`"
unset LD_PRELOAD
unset N

echo -n "Copy xvnkb  =>  $PREFIX/bin ... "
cp ./xvnkb $PREFIX/bin && echo ok
echo -n "Copy xvnkb.so.$VERSION  =>  $PREFIX/lib ... "
cp ./xvnkb.so.$VERSION $PREFIX/lib && echo ok
echo -n "Copy xvnkb_localeconf.sh  =>  $PREFIX/bin ... "
cp ./scripts/xvnkb.lconf.sh $PREFIX/bin/xvnkb_localeconf.sh && echo ok
echo -n "Initialize xvnkb core ... "
XVNKB_CORE="$SO.$VERSION"
while [ -f $XVNKB_CORE ]; do
	if [ "$N" = "" ]; then
		N=1;
	else
		N=$((N + 1))
	fi
	XVNKB_CORE="$SO.$VERSION-$N"
done
cp ./xvnkb.so.$VERSION $XVNKB_CORE
chattr +i $XVNKB_CORE
if [ -f "$LD" ]; then
	grep -v xvnkb.so $LD > $LD.xvnkb
	/bin/mv -f $LD.xvnkb $LD
fi
echo "$XVNKB_CORE" >> $LD
echo done

if [ "$LANG" = "C" ]; then
	LANG="en_US"
fi

if [ "`echo $LANG | grep UTF-8`" = "" ]; then
	echo "If you want to input Vietnamese Unicode, please run"
	echo
	echo "  # $PREFIX/bin/xvnkb_localeconf.sh $LANG.UTF-8"
	echo
	echo "and set your LANG to $LANG.UTF-8."
	echo "See xvnkb documents for more information."
fi

if [ "$OL" != "" ]; then
	echo "You are using LD_PRELOAD to load xvnkb core."
	echo "Try to remove this old setting style..."
	if [ -f /etc/X11/xinit/xinitrc.d/xvnkb.sh ]; then
		/bin/rm -f /etc/X11/xinit/xinitrc.d/xvnkb.sh
	fi
	echo -e "\\033[1;31m"
	echo "* NOTICE: If you set it somewhere else (e.g. /etc/profile, /etc/bashrc,"
	echo "~/.bash_profile, ~/.bashrc, ~/.xinitrc) by yourself, please remove it also!"
	echo -e "\\033[0;39m"
fi

echo
echo "You can use xvnkb now!  If you are using X, please restart your Window Manager."
echo "It will load xvnkb core control automatically for you and affect to all"
echo "applications.  Right now, xvnkb core control can affect to new starting"
echo "applications only.  Run \"xvnkb\" to control status."
echo

