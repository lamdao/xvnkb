#!/bin/sh
#----------------------------------------------------------------------------#
#  uninstall.sh for xvnkb                                                    #
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

remove() {
	echo "Remove $1..."
	/bin/rm -rf $1
}

restore() {
	if [ -f $2 ]; then
		remove $2
	fi
	echo "Restore $1 $2..."
	/bin/mv $1 $2
}

getver() {
	eval `grep XVNKB_VERSION $1`
}

if [ -f VERSION ]; then
	VERSION=`cat VERSION`;
else
	echo "Missing version information (file VERSION)!!!"
	exit
fi

if [ "$*" = "" ]; then
	echo
	echo "Uninstaller for xvnkb $VERSION"
	echo "Press \"ENTER\" to remove xvnkb from your system, \"^C\" to cancel."
	read
fi

ID=`id -u`

if [ "$ID" = "0" ]; then
	XID_SYS=/usr/local
	XID_BIN=$XID_SYS/bin
	XID_LIB=$XID_SYS/lib
	PRELOAD_SCRIPT=/etc/X11/xinit/xinitrc.d/xvnkb.sh
	FOLDERS="system folders:"
else
	echo -n "Uninstall from system folder [y/N]? "
	read r
	if [ "$r" = "y" -o "$r" = "Y" ]; then
		echo "* Please input root password for uninstallation!"
		su -c './xvnkb_uninstall ok'
		exit
	fi
	XID_SYS=$HOME
	XID_BIN=$XID_SYS/bin
	XID_LIB=$XID_SYS/lib
	PRELOAD_SCRIPT=$HOME/.xvnkb.preload
	FOLDERS="folders:"
fi

echo
echo "Uninstalling xvnkb from your "$FOLDERS

unset LD_PRELOAD
getver $PRELOAD_SCRIPT
remove $XID_LIB/xvnkb.so.$VERSION
if [ "$XVNKB_VERSION" = "$VERSION" ]; then
	remove $XID_BIN/xvnkb
	remove $XID_BIN/xvnkb.sh
	remove $XID_BIN/xvnkb_ctrl
	remove $PRELOAD_SCRIPT
	if [ "$ID" != 0 ]; then
		remove $HOME/.xinitrc
		if [ -f $HOME/.xvnkb.xrcdefaults ]; then
			restore $HOME/.xvnkb.xrcdefaults $HOME/.xinitrc
		fi
	else
		remove /usr/local/bin/xvnkb_setup.sh
		remove $XID_SYS/share/xvnkb
	fi
	echo
	echo "Please restart X (if currently running) to \"deactivate\" preloading xvnkb core."
	echo
	echo "Thank you for using xvnkb!!!"
	echo
fi

