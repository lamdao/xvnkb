#!/bin/sh
#----------------------------------------------------------------------------#
#  xvnkb_setup.sh                                                            #
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

VERSION=__VERSION__
PREFIX=/usr/local
XVNKB_CORE=xvnkb.so.$VERSION
SCRIPT_DIR=$PREFIX/share/xvnkb

#----------------------------------------------------------------------------#
# Subroutines                                                                #
#----------------------------------------------------------------------------#
copy() {
	if [ "$1" = "-f" ]; then
		echo "Copy $2 => $3..."
		d=`dirname $3`
		mkdir -p $d
		/bin/cp -f $2 $3
	else
		echo "Copy $1 => $2..."
		mkdir -p $2
		/bin/cp -f $1 $2
	fi
}
#----------------------------------------------------------------------------#
getver() {
	if [ -f "$1" ]; then
		eval `grep XVNKB_VERSION $1`
	fi
}
#----------------------------------------------------------------------------#
backup() {
	echo "Backup $1 => $2..."
	/bin/mv -f $1 $2
}
#----------------------------------------------------------------------------#
addv() {
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
				echo "* Please input root password for locale creating!"
				su -c "$SCRIPT_DIR/xvnkb.lconf.sh $LANG"
			else
				$SCRIPT_DIR/xvnkb.lconf.sh $LANG
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
echo
echo "Configurator for xvnkb $VERSION"
echo "Press \"ENTER\" to start, \"^C\" to cancel."
read

if [ ! -f $PREFIX/lib/$XVNKB_CORE ]; then
	echo
	echo "Missing xvnkb core \"$XVNKB_CORE\" in $PREFIX/lib!"
	echo
	exit -1
fi

getver /etc/X11/xinit/xinitrc.d/xvnkb.sh
if [ "$XVNKB_VERSION" = "$VERSION" ]; then
	echo "Global settings for xvnkb $VERSION already exists in [/etc/X11/xinit/xinitrc.d]!"
	echo "Do you want to continue [N/y]? "
	read r
	if [ "$r" = "" -o "$r" = "N" -o "$r" = "n" ]; then
		exit
	fi
fi

ID=`id -u`
if [ "$ID" = "0" ]; then
	echo -n "Do you want to configure xvnkb for all users in your system [Y/n]? "
	read r

	if [ "$r" != "" -a "$r" != "Y" -a "$r" != "y" ]; then
		XVN_RCS=$HOME
		I18NRCS=$HOME/.i18n
		PRELOAD_SCRIPT="$XVN_RCS/.xvnkb.preload"
		PRELOAD_SOURCE="$SCRIPT_DIR/xvnkb.user.sh"
		r=0
	else
		XVN_RCS=/etc/X11/xinit/xinitrc.d
		I18NRCS=/etc/sysconfig/i18n
		PRELOAD_SCRIPT="$XVN_RCS/xvnkb.sh"
		PRELOAD_SOURCE="$SCRIPT_DIR/xvnkb.sys.sh"
		r=1
	fi
else
	XVN_RCS=$HOME
	I18NRCS=$HOME/.i18n
	PRELOAD_SCRIPT="$XVN_RCS/.xvnkb.preload"
	PRELOAD_SOURCE="$SCRIPT_DIR/xvnkb.sys.sh"
	r=0
fi

addv $PRELOAD_SOURCE $PRELOAD_SCRIPT
chmod +x $PRELOAD_SCRIPT

# Check and backup user $HOME/.xinitrc then replace it with xvnkb's one
# The old one will be called by xvnkb's one later to restore all user
# configurations when X start up
if [ "$r" = "0" ]; then
	XINITRC=$HOME/.xinitrc
	if [ ! -f $HOME/.xvnkb.xrcdefaults -a -f $XINITRC ]; then
		if [ "`grep XVNKB_VERSION $XINITRC`" = "" ]; then
			backup $XINITRC $HOME/.xvnkb.xrcdefaults
		fi
	fi
	addv $SCRIPT_DIR/xvnkb.xinitrc.sh $XINITRC
fi

LANG=`echo $LANG|cut -f1 -d.`
if [ "$LANG" = "" -o "$LANG" = "UTF-8" -o "$LANG" = "vi_VN" ]; then
	LANG="en_US"
fi

echo
echo "For using Unicode input, you have to set LANG=*UTF-8 (see README)"
echo
echo "Set LANG"
echo "(1) UTF-8"
echo "(2) $LANG.UTF-8"
echo "(3) vi_VN.UTF-8"
echo "(4) Do not modify <*>"
echo
echo -n "Please choose a number: "
read r
echo

case "$r" in
	1) LANG="UTF-8";;
	2) LANG="$LANG.UTF-8";;
	3) LANG="vi_VN.UTF-8";;
	*) LANG="";;
esac

if [ "$LANG" = "" ]; then
	echo "You can set LANG=*UTF-8 manually to use Unicode input later (see README)."
else
	check_locale
	check_i18n
	echo "Add \"export LANG=$LANG\" to $PRELOAD_SCRIPT"
	echo "export LANG=$LANG" >> $PRELOAD_SCRIPT
fi

echo
echo "Please restart X (if currently running) to \"activate\" preloading xvnkb.so.$VERSION"
echo "(core control). And run xvnkb (gui) to change status."
echo 
echo "Thank you for using xvnkb!!! Have fun!!! ;-)"
echo

