#!/bin/sh
#----------------------------------------------------------------------------#
#  install.sh for xvnkb                                                      #
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
PREFIX=/usr/local
SCRIPT_DIR=$PREFIX/share/xvnkb
#----------------------------------------------------------------------------#
# Sub routines                                                               #
#----------------------------------------------------------------------------#
copy() {
	if [ "$1" = "-f" ]; then
		echo "Copy $2 => $3..."
		d=`dirname $3`
		mkdir -p $d
		/bin/cp -rf $2 $3
	else
		echo "Copy $1 => $2..."
		mkdir -p $2
		/bin/cp -rf $1 $2
	fi
}
#----------------------------------------------------------------------------#
backup() {
	echo "Backup $1 => $2..."
	/bin/mv -f $1 $2
}
#----------------------------------------------------------------------------#
addv() {
	d=`dirname $2`
	mkdir -p $d
	echo "Copy $1 => $2..."
	cat "$1" | sed -e "s/__VERSION__\$/$VERSION/" > "$2"
}
#----------------------------------------------------------------------------#
check_locale() {
	echo
	echo -n "Checking for locale [$LANG]... "

	locale=0
	missing=""
	if [ ! -f /usr/lib/locale/$LANG/LC_IDENTIFICATION ]; then
		locale=1
		missing="[/usr/lib/locale]"
	fi
	if [ ! -f /usr/share/locale/$LANG/LC_IDENTIFICATION ]; then
		locale=$(($locale + 1))
		if [ "$missing" = "" ]; then
			missing="[/usr/share/locale]"
		else
			missing="$missing and [/usr/share/locale]"
		fi
	fi

	lstatus=(yes missing no)
	echo ${lstatus[$locale]}

	if [ "$locale" != "0" ]; then
		echo "* Locale $LANG is missing in $missing"
		echo
		echo -n "Do you want to create [Y/n]? "
		read r

		if [ "$r" != "" -a "$r" != "Y" -a "$r" != "y" ]; then
			echo
			echo "* Warning:"
			echo "Most applications require locale $LANG to work properly with LANG=$LANG"
			echo "in Unicode input mode. You can use \"$SCRIPT_DIR/xvnkb.lconf.sh $LANG\""
			echo "to create it later."
			echo
		else
			if [ "$ID" != "0" ]; then
				echo "*** Please input root password for locale creating!"
				su -c "./xvnkb_localeconf $LANG"
			else
				./xvnkb_localeconf $LANG
			fi
		fi
	fi
}
#----------------------------------------------------------------------------#
check_i18n() {
	echo
	echo -n "Checking locale setting for [$LANG] in i18n resource... "
	if [ -f $I18NRCS ]; then
		r=`grep $LANG $I18NRCS`
		if [ "`echo $r|grep ^LANG=`" != "" ]; then
			echo ok
			r=0
		else
			grep -v ^LANG= $I18NRCS > $I18NRCS.xvnkb
			r=1
		fi
	else
		echo no
		r=2
	fi

	if [ "$r" != "0" ]; then
		echo -n "Add \"LANG='$LANG'\" to $I18NRCS... "
		echo "LANG='$LANG'" >> $I18NRCS.xvnkb
		/bin/mv -f $I18NRCS.xvnkb $I18NRCS
		echo ok
	fi
}
#----------------------------------------------------------------------------#
# Main                                                                       #
#----------------------------------------------------------------------------#
if [ -f VERSION ]; then
	VERSION=`cat VERSION`;
else
	echo "Missing version information (file VERSION)!!!"
	exit
fi

if [ ! -f ./xvnkb.so.$VERSION ]; then
	echo "Run \"./configure\" and then"
	echo "Type \"make\" to build xvnkb (core & gui)!"
	exit
fi

if [ "$*" = "" ]; then
	echo
	echo "Installer for xvnkb $VERSION"
	echo "Press \"ENTER\" to copy xvnkb to your system, \"^C\" to cancel."
	read
fi

ID=`id -u`

if [ "$ID" = "0" ]; then
	XVN_SYS=/usr/local
	XVN_BIN=$XVN_SYS/bin
	XVN_LIB=$XVN_SYS/lib
	XVN_RCS=/etc/X11/xinit/xinitrc.d
	I18NRCS=/etc/sysconfig/i18n
	PRELOAD_SCRIPT="$XVN_RCS/xvnkb.sh"
	PRELOAD_SOURCE="./scripts/xvnkb.sys.sh"
	FOLDERS="system folders:"
else
	echo -n "Install to system folders [y/N]? "
	read r

	echo
	if [ "$r" = "y" -o "$r" = "Y" ]; then
		echo "* Please input root password for installation!!!"
		su -c './xvnkb_install ok'
		exit
	fi
	XVN_SYS=$HOME
	XVN_BIN=$XVN_SYS/bin
	XVN_LIB=$XVN_SYS/lib
	XVN_RCS=$HOME
	I18NRCS=$HOME/.i18n
	PRELOAD_SCRIPT="$XVN_RCS/.xvnkb.preload"
	PRELOAD_SOURCE="./scripts/xvnkb.user.sh"
	FOLDERS="folders:"
fi

if [ -f $XVN_LIB/xvnkb.so.$VERSION ]; then
	echo "Version \"$VERSION\" of xvnkb is already installed!"
	echo "If you are currently using X with preloaded xvnkb core,"
	echo "override installation may \"crash\" your X Window"
	echo
	echo -n "Do you want to continue [N/y] ? "
	read r
	if [ "$r" != "y" -a "$r" != "Y" ]; then
		echo "Please logout X Window and login to console"
		echo "then try to install again"
		echo
		exit
	fi
	echo
fi

echo "Install xvnkb to your "$FOLDERS

unset LD_PRELOAD
copy ./xvnkb $XVN_BIN
copy ./xvnkb.so.$VERSION $XVN_LIB
addv $PRELOAD_SOURCE $PRELOAD_SCRIPT
chmod +x $PRELOAD_SCRIPT
addv ./scripts/xvnkb.sh $XVN_BIN/xvnkb.sh
chmod +x $XVN_BIN/xvnkb.sh
if [ -f ./tools/xvnkb_ctrl ]; then
copy ./tools/xvnkb_ctrl $XVN_BIN
fi

# Check and backup user $HOME/.xinitrc then replace it with xvnkb's one
# The old one will be called by xvnkb's one later to restore all user
# configurations when X start up
if [ "$ID" != "0" ]; then
	XINITRC=$HOME/.xinitrc
	if [ ! -f $HOME/.xvnkb.xrcdefaults -a -f $XINITRC ]; then
		if [ "`grep XVNKB_VERSION $XINITRC`" = "" ]; then
			backup $XINITRC $HOME/.xvnkb.xrcdefaults
		fi
	fi
	addv ./scripts/xvnkb.xinitrc.sh $XINITRC
else
	addv ./scripts/xvnkb_setup.sh /usr/local/bin/xvnkb_setup.sh
	chmod +x /usr/local/bin/xvnkb_setup.sh
	copy -f ./scripts /usr/local/share/xvnkb
fi

LANG=`echo $LANG|cut -f1 -d.`
ENCODING=`echo $LANG|cut -f2 -d.`

if [ "$ENCODING" = "UTF-8" ]; then
fi

if [ "$LANG" = "" -o "$LANG" = "UTF-8" -o "$LANG" = "vi_VN" ]; then
	LANG="en_US"
fi

echo
echo "For using Unicode input, you have to set LANG=*.UTF-8 (see README)"
echo
echo "Set LANG"
echo "(1) $LANG.UTF-8"
echo "(2) vi_VN.UTF-8"
echo "(3) Do not modify <*>"
echo
echo -n "Please select a number: "
read r

case "$r" in
	1) LANG="$LANG.UTF-8";;
	2) LANG="vi_VN.UTF-8";;
	*) LANG="";;
esac

if [ "$LANG" = "" ]; then
	echo
	echo "You can set LANG=*.UTF-8 manually to use Unicode input later."
	echo "Also remember to create *.UTF-8 locale"
	echo "See README for more information."
else
	check_locale
	check_i18n
	echo "Add \"export LANG=$LANG\" to $PRELOAD_SCRIPT"
	echo "export LANG=$LANG" >> $PRELOAD_SCRIPT
	cat "$XVN_BIN/xvnkb.sh" | sed -e "s/__LANG__\$/$LANG/" > "$XVN_BIN/xvnkb.sh.lang"
	/bin/mv -f "$XVN_BIN/xvnkb.sh.lang" "$XVN_BIN/xvnkb.sh"
	chmod +x "$XVN_BIN/xvnkb.sh"
fi

echo
echo "Please restart X (if currently running) to \"activate\" preloading xvnkb.so.$VERSION"
echo "(core control). And run xvnkb (gui) to change status."
echo 
echo "Thank you for using xvnkb!!! Have fun!!! ;-)"
echo

