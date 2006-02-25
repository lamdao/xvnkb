/*----------------------------------------------------------------------------*/
/*  property.c                                                                */
/*----------------------------------------------------------------------------*/
/*  copyright         : (C) 2002 by Dao Hai Lam                               */
/*                      VISC Software & Security Consultant Company           */
/*                      Hall 3, Quang Trung Software City                     */
/*                      Tan Chanh Hiep Ward, District 12,                     */
/*                      Ho Chi Minh city, VIETNAM                             */
/*  website           : http://www.visc-network.com                           */
/*  email             : lam@visc-network.com                                  */
/*  last modify       : Thu, 18 Apr 2002 22:00:33 +0700                       */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*   This program is free software; you can redistribute it and/or modify     */
/*   it under the terms of the GNU General Public License as published by     */
/*   the Free Software Foundation; either version 2 of the License, or        */
/*   (at your option) any later version.                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*----------------------------------------------------------------------------*/
#include "debug.h"
#include "typedefs.h"
#include "property.h"
/*----------------------------------------------------------------------------*/
Atom vk_using_atom;
Atom vk_method_atom;
Atom vk_charset_atom;
Atom vk_spelling_atom;
Atom vk_hotkey_atom;
/*----------------------------------------------------------------------------*/
extern Window root;
/*----------------------------------------------------------------------------*/
Atom VKInternAtom(Display *display, char *name)
{
	Atom a = XInternAtom(display, name, True);
	if( a==None ) {
		TRACE("Atom %s not found. Create new!\n", name);
		a = XInternAtom(display, name, False);
	}
	return a;
}
/*----------------------------------------------------------------------------*/
void VKAtomInit(Display *display)
{
	vk_charset_atom = VKInternAtom(display, VKP_CHARSET);
	vk_method_atom = VKInternAtom(display, VKP_METHOD);
	vk_using_atom = VKInternAtom(display, VKP_USING);
	vk_spelling_atom = VKInternAtom(display, VKP_SPELLING);
	vk_hotkey_atom = VKInternAtom(display, VKP_HOTKEY);
}
/*----------------------------------------------------------------------------*/
long VKGetValue(Display *display, Atom key)
{
	Atom at;
	int af;
	long *s;
	ulong ni, br;

	if( XGetWindowProperty(display, root, key, 0, 1, False, XA_CARDINAL,
							&at, &af, &ni, &br, (uchar **)&s)==Success ) {
		if( s!=NULL ) {
			long v = *s;
			XFree(s);
			return v;
		}
	}
	return -1;
}
/*----------------------------------------------------------------------------*/
void VKSetValue(Display *display, Atom key, long value)
{
	XChangeProperty(display, root, key, XA_CARDINAL, 32, PropModeReplace,
					(uchar*)&value, 1);
}
/*----------------------------------------------------------------------------*/
void VKGetValues(Display *display, Atom key, long *values, int n)
{
	Atom at;
	int af;
	long *s;
	ulong ni, br;

	if( XGetWindowProperty(display, root, key, 0, n, False, XA_CARDINAL,
							&at, &af, &ni, &br, (uchar **)&s)==Success ) {
		if( s!=NULL ) {
			memcpy(values, s, n * sizeof(long));
			XFree(s);
		}
	}
}
/*----------------------------------------------------------------------------*/
void VKSetValues(Display *display, Atom key, long *values, int n)
{
	XChangeProperty(display, root, key, XA_CARDINAL, 32, PropModeReplace,
					(uchar*)values, n);
}
/*----------------------------------------------------------------------------*/
char *VKGetString(Display *display, Atom key)
{
	int af;
	uchar *s;
	ulong ni, br;
	Atom at;

	if( XGetWindowProperty(display, root, key, 0, VKP_MAX_LENGTH, False,
							XA_STRING, &at, &af, &ni, &br, &s)==Success ) {
		return (char *)s;
	}

	return NULL;
}
/*----------------------------------------------------------------------------*/
void VKSetString(Display *display, Atom key, uchar *value)
{
	XChangeProperty(display, root, key, XA_STRING, 8, PropModeReplace,
					value, strlen((char *)value)+1);
}
/*----------------------------------------------------------------------------*/
