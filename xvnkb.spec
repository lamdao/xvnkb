%define name xvnkb
%define version 0.2.8
%define rel 1
%define myprefix /usr/local

Summary: xvnkb  - Vietnamese keyboard input for X-Window
Name: %{name}
Version: %{version}
Release: %{rel}
License: GPL
Group: System/Internationalization
URL: http://xvnkb.sourceforge.net/
Source: http://xvnkb.sourceforge.net/%{name}-%{version}.tar.bz2
Prefix: %{myprefix}
BuildRoot: %{_tmppath}/%{name}-buildroot
#Packager: Dao Hai Lam <lam at visc-network dot com>

%description
xvnkb is a Vietnamese keyboard input for X-Window. It provides an 
useful way for editing Vietnamese on X-Window environment with 
popular input methods and charsets. 

xvnkb 0.2.x support UTF-8 Encoding ;). Good news, eh?

%prep
%setup

%build
export CFLAGS="$RPM_OPT_FLAGS"
./configure --use-extstrocke

make

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{myprefix}/{bin,lib,share}
mkdir -p $RPM_BUILD_ROOT%{myprefix}/share/%{name}

install -m 755 %{name} $RPM_BUILD_ROOT%{myprefix}/bin
install -m 755 %{name}.so.%{version} $RPM_BUILD_ROOT%{myprefix}/lib
install -m 755 tools/xvnkb_ctrl $RPM_BUILD_ROOT%{myprefix}/bin
install -m 755 scripts/* $RPM_BUILD_ROOT%{myprefix}/share/%{name}

%clean
rm -rf $RPM_BUILD_ROOT

%post
VERSION="%{version}"
OL=`echo $LD_PRELOAD | grep xvnkb.so`
LD="/etc/ld.so.preload"
SO="/lib/xvnkb.so"
XVNKB_CORE="$SO.$VERSION"
unset LD_PRELOAD N
while [ -f $XVNKB_CORE ]; do
	if [ "$N" = "" ]; then
		N=1
	else
		N=$((N + 1))
	fi
	XVNKB_CORE="$SO.$VERSION-$N"
done
cp %{myprefix}/lib/xvnkb.so.$VERSION $XVNKB_CORE
chattr +i $XVNKB_CORE
if [ -f "$LD" ]; then
	grep -v xvnkb.so $LD > $LD.xvnkb
	/bin/mv -f $LD.xvnkb $LD
fi
echo "$XVNKB_CORE" >> $LD

if [ "$LANG" = "C" ]; then
	LANG="en_US"
fi

if [ "`echo $LANG | grep UTF-8`" = "" ]; then
	echo "If you want to input Vietnamese Unicode, please run"
	echo
	echo "  # $PREFIX/bin/xvnkb_localeconf.sh $LANG.UTF-8"
	echo
	echo "and set your LANG to $LANG.UTF-8."
	echo "See xvnkb documents at %{myprefix}/share/doc/xvnkb for more information."
fi

if [ "$OL" != "" ]; then
	echo -e "\\033[1;31m"
	echo "* NOTICE:"
	echo "You are using LD_PRELOAD to load xvnkb core. If you set it somewhere else"
	echo "(e.g. /etc/profile, /etc/bashrc, ~/.bash_profile, ~/.bashrc, ~/.xinitrc)"
	echo "by yourself, please remove it also!"
	echo -e "\\033[0;39m"
fi

echo "You can use xvnkb now!  If you are using X, please restart your Window Manager."
echo "It will load xvnkb core control automatically for you and affect to all"
echo "applications.  Right now, xvnkb core control can affect to new starting"
echo "applications only.  Run \"xvnkb\" to control status."

%files
%defattr(-,root,root)
%doc AUTHORS ChangeLog README* INSTALL* TODO THANKS COPYING 
%doc contrib/profile scripts/*.sh doc/* 
%{myprefix}/*/*

%changelog
* Fri Jan 16 2004 Dao Hai Lam <daohailam at yahoo dot com>
- use new installation style

* Sun Nov 16 2003 Dao Hai Lam <daohailam at yahoo dot com>
- use new configure's options
- anti email spam :)

* Wed Oct 15 2003 Nguyen Dai Quy <quy at nguyendai dot org>
- correction for multi-target RPM building.

* Sun Apr 20 2003 Dao Hai Lam <lam at visc-network dot com>
- updated to version 0.2.8

* Sun Mar  2 2003 Dao Hai Lam <lam at visc-network dot com>
- updated to version 0.2.7

* Sun Feb  9 2003 Dao Hai Lam <lam at visc-network dot com>
- updated to version 0.2.6

* Tue Aug 13 2002 Dao Hai Lam <lam at visc-network dot com>
- updated to version 0.2.5

* Thu May  9 2002 Nguyen-Dai Quy <Quy at NguyenDai dot org>
- updated to version 0.2.4

* Mon May  6 2002 Nguyen-Dai Quy <Quy at NguyenDai dot org>
- build RPM for version 0.2.2

