#!/bin/sh
#----------------------------------------------------------------------------#
#  xvnkb shell                                                               #
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
XVNKB_VERSION=__VERSION__
XVNKB_CORE=xvnkb.so.__VERSION__

if ! expr "$LD_PRELOAD" : ".*xvnkb.so.*" >/dev/null
then
	if [ -f $HOME/lib/$XVNKB_CORE ] ; then
		export LD_PRELOAD="$LD_PRELOAD $HOME/lib/$XVNKB_CORE"
	else
		if [ -f $PREFIX/lib/$XVNKB_CORE ]; then
			export LD_PRELOAD="$LD_PRELOAD $PREFIX/lib/$XVNKB_CORE"
		else
			echo
			echo "Missing xvnkb core: $XVNKB_CORE!"
			echo
			exit
		fi
	fi
fi
VN_UTF8_FONT="-misc-fixed-medium-r-normal--0-0-75-75-c-0-iso10646-1"
alias vnvi="xterm -title XVNKB-VI -u8 -fn $VN_UTF8_FONT -e vim &"

export LANG=__LANG__
if [ "`pidof xvnkb`" = "" ]; then
	xvnkb
fi

if [ "$SHELL" = "" ]; then
	/bin/sh
else
	$SHELL
fi
