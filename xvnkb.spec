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
#Group: User Interface/X
URL: http://xvnkb.sourceforge.net/
Source: http://xvnkb.sourceforge.net/%{name}-%{version}.tar.bz2
Prefix: %{myprefix}
BuildRoot: %{_tmppath}/%{name}-buildroot
#Packager: Dao Hai Lam <lam@visc-network.com>

%description
xvnkb is a Vietnamese keyboard input for X-Window. It provides an 
useful way for editing Vietnamese on X-Window environment with 
popular input methods and charsets. 

xvnkb 0.2.x support UTF-8 Encoding ;). Good news, eh?

%prep
%setup

%build
export CFLAGS="$RPM_OPT_FLAGS"
./configure --spell-check --use-xft

make && ./scripts/adjver.sh

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{myprefix}/{bin,lib,share}
mkdir -p $RPM_BUILD_ROOT%{myprefix}/share/%{name}

install -m 755 %{name} $RPM_BUILD_ROOT%{myprefix}/bin
install -m 755 %{name}.so.%{version} $RPM_BUILD_ROOT%{myprefix}/lib
install -m 755 tools/xvnkb_ctrl $RPM_BUILD_ROOT%{myprefix}/bin
install -m 755 tools/xvnkb_setup $RPM_BUILD_ROOT%{myprefix}/bin
install -m 755 scripts/xvnkb_setup.sh $RPM_BUILD_ROOT%{myprefix}/bin
install -m 755 scripts/* $RPM_BUILD_ROOT%{myprefix}/share/%{name}

%clean
rm -rf $RPM_BUILD_ROOT

%post
/usr/local/bin/xvnkb_setup

%files
%defattr(-,root,root)
%doc AUTHORS ChangeLog README* INSTALL* TODO THANKS COPYING 
%doc contrib/profile scripts/*.sh doc/* 
%{myprefix}/*/*

%changelog
* Wed Oct 15 2003 Nguyen Dai Quy <quy@nguyendai.org>
- correction for multi-target RPM building.

* Sun Apr 20 2003 Dao Hai Lam <lam@visc-network.com>
- updated to version 0.2.8

* Sun Mar  2 2003 Dao Hai Lam <lam@visc-network.com>
- updated to version 0.2.7

* Sun Feb  9 2003 Dao Hai Lam <lam@visc-network.com>
- updated to version 0.2.6

* Tue Aug 13 2002 Dao Hai Lam <lam@visc-network.com>
- updated to version 0.2.5

* Thu May  9 2002 Nguyen-Dai Quy <Quy@NguyenDai.org>
- updated to version 0.2.4

* Mon May  6 2002 Nguyen-Dai Quy <Quy@NguyenDai.org>
- build RPM for version 0.2.2

