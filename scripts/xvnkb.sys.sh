#!/bin/sh
#----------------------------------------------------------------------------#
#  xvnkb system preloading script                                            #
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
XVNKB_CORE=$PREFIX/lib/xvnkb.so.__VERSION__

# Set preload
if ! [ -r "$XVNKB_CORE" ]; then
	echo "$XVNKB_CORE is not readable!"
elif expr "$LD_PRELOAD" : ".*xvnkb.so.*" >/dev/null
then
	echo
#	echo "xvnkb.so is already preloaded."
else
#	echo "Preloading $XVNKB_CORE"
	LD_PRELOAD="$LD_PRELOAD $XVNKB_CORE"
	export LD_PRELOAD
fi
unset LC_CTYPE LC_COLLATE LC_MESSAGES
unset LC_NUMERIC LC_MONETARY LC_TIME LC_ALL
unset LANGUAGE LINGUAS

