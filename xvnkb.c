/*----------------------------------------------------------------------------*/
/*  xvnkb.c                                                                   */
/*----------------------------------------------------------------------------*/
/*  copyright         : (C) 2002 by Dao Hai Lam                               */
/*                      VISC Software & Security Consultant Company           */
/*                      Hall 3, Quang Trung Software City                     */
/*                      Tan Chanh Hiep Ward, District 12,                     */
/*                      Ho Chi Minh city, VIETNAM                             */
/*  website           : http://www.visc-network.com                           */
/*  email             : lam@visc-network.com                                  */
/*  last modify       : Tue, 13 Aug 2002 03:14:07 +0700                       */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*   This program is free software; you can redistribute it and/or modify     */
/*   it under the terms of the GNU General Public License as published by     */
/*   the Free Software Foundation; either version 2 of the License, or        */
/*   (at your option) any later version.                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
/*----------------------------------------------------------------------------*/
#include "debug.h"
#include "typedefs.h"
#include "visckey.h"
#include "property.h"
#include "xvnkb_dll.h"
#include "vkeydefs.h"
/*----------------------------------------------------------------------------*/
#define	VK_MAGIC_CHAR			0x01
/*----------------------------------------------------------------------------*/
typedef int (*xfunc)();
/*----------------------------------------------------------------------------*/
typedef struct {
	char *name;
	int mask;
} vk_statekey_map;
/*----------------------------------------------------------------------------*/
typedef struct {
	long state;
	long sym;
} vk_hotkey_info;
/*----------------------------------------------------------------------------*/
Window root = -1;
Window focus = -1;
/*----------------------------------------------------------------------------*/
static KeyCode rk = 0;
static KeyCode bs = 0;
static XKeyEvent xk;
/*----------------------------------------------------------------------------*/
vk_hotkey_info hotkey = {
	VK_HOTKEY_STATE,
	VK_HOTKEY_CODE
};
/*----------------------------------------------------------------------------*/
static int bk = 0;
/*----------------------------------------------------------------------------*/
static char *separators[] = {
	" ",										// VKM_OFF
	" !@#$%&)_|\\-{}[]:\";<>,/'`~?.^*(+=",		// VKM_VNI
	" !@#$%&)_|\\-:\";<>,/'`~?.^*(+="			// VKM_TELEX
#ifndef VK_USE_EXTSTROKE
	"{}[]"
#endif
	,
	" !@#$%&)_|\\-{}[]:\";<>,/",				// VKM_VIQR
};
/*----------------------------------------------------------------------------*/
static inline void key_handler(Display *display, XKeyEvent *event)
{
	char *sp;
	int i, len;
	int state = event->state;
	KeySym key = XKeycodeToKeysym(display, event->keycode,
					state & VK_SHIFT ? 1 : 0);

	if( (state & VK_CAPS_LOCK) ) {
		if( key >= 'A' && key <= 'Z' )
			key = tolower(key);
		else
		if( key >= 'a' && key <= 'z' )
			key = toupper(key);
	}

	if( key==hotkey.sym && (state & hotkey.state)==hotkey.state ) {
		bk = 0;
		VKSwitchMethod();
	#ifndef VK_CORE_ONLY
		VKSetValue(display, vk_method_atom, vk_method);
	#endif
		TRACE("m=%d, u=%d, c=%d\n", vk_method, vk_using, vk_charset);
		return;
	}

	if( vk_method == VKM_VNI && (state & VK_SHIFT) ) {
		static char *vni_shift = ")!@#$%^&*(";

		if( (sp = strchr(vni_shift, key)) )
			key = '0' + sp - vni_shift;
	}

	switch( key ) {
		case XK_Linefeed:
		case XK_Clear:
		case XK_Return:
		case XK_Home:
		case XK_Left:
		case XK_Up:
		case XK_Right:
		case XK_Down:
		case XK_Page_Up:
		case XK_Page_Down:
		case XK_End:
		case XK_Begin:
		case XK_Tab:
			VKClearBuffer();
			break;
		case XK_BackSpace:
			len = VKBackspaceDelete();
			if( len>0 ) {
				xk.display = display;
				xk.window = focus;
				xk.keycode = bs;
				xk.serial = event->serial+len;
				xk.time = event->time+len;
				for( i=0; i<len; i++ ) {
					XPutBackEvent(display, (XEvent *)&xk);
					xk.serial--;
					xk.time--;
				}
				bk = len;
			}
			break;
		default:
			if( vk_method==VKM_OFF || key>0xFF || key<0x01 ) break;

			sp = strchr(separators[vk_method], key);
			if( sp || (state & VK_NOTACCEPT_STATES) ) {
				VKClearBuffer();
				break;
			}

			switch( VKAddKey(key) ) {
				case -1:
					break;
			#ifdef VK_USE_EXTSTROKE
				case -2:
					xk.display = display;
					xk.window = focus;
					xk.keycode = VK_MAGIC_CHAR;
					xk.time = event->time;
					xk.serial = event->serial;
					XPutBackEvent(display, (XEvent *)&xk);
					xk.keycode = bs;
					for( bk=1, i=0; i<vk_plength-1; i++, bk++ ) {
						xk.time -= 2;
						xk.serial--;
						XPutBackEvent(display, (XEvent *)&xk);
					}
					rk = event->keycode;
					event->time = xk.time - 2;
					event->serial = xk.serial - 1;
					event->keycode = bs;
					event->state = 0;
					break;
				case -3:
					event->keycode = VK_MAGIC_CHAR;
					event->state = 0;
					break;
			#endif
				default:
					xk.display = display;
					xk.window = focus;
					xk.keycode = VK_MAGIC_CHAR;
					xk.time = event->time;
					xk.serial = event->serial;
					XPutBackEvent(display, (XEvent *)&xk);

					xk.keycode = bs;
					for( bk=1, i=0; i<vk_plength-1; i++, bk++ ) {
						xk.time -= 2;
						xk.serial--;
						XPutBackEvent(display, (XEvent *)&xk);
					}
					rk = event->keycode;
					event->time = xk.time - 2;
					event->serial = xk.serial - 1;
					event->keycode = bs;
					event->state = 0;
					break;
			}
	}
}
/*----------------------------------------------------------------------------*/
static inline int isoutf(char *utf, int usize, char *iso, int isize)
{
	int n = usize < isize ? usize : isize;
	register uchar *p = (uchar *)utf;
	register int i;

	for( i=0; i<n; i++ ) {
		register uchar c = *iso++;
		if( c >= 128 ) {
			if( c < 192 )
				*p++ = 0xC2;
			else {
				*p++ = 0xC3;
				c -= 64;
			}
		}
		*p++ = c;
	}

	return (char *)p-utf;
}
/*----------------------------------------------------------------------------*/
extern int XLookupString(XKeyEvent *event, char *buffer, int size,
									KeySym *keysym, XComposeStatus *cstatus)
{
	static int utf_lang = 0;
	static xfunc fptr = 0;
	register int r = 0;

	if( !fptr ) {
		char *p;
		fptr = get_func_entry("libX11.so", "libX11.so.6", "XLookupString");
		if( !fptr ) {
			TRACE("xvnkb: error loading XLookupString!\n");
			return 0;
		}
		p = getenv("LANG");
		utf_lang = p && strstr(p, "UTF-8");
	}

	if( event->keycode!=VK_MAGIC_CHAR )
		r = (*fptr)(event, buffer, size, keysym, cstatus);
	else
	if( buffer ) {
	#ifdef VK_USE_KEYSYM
		extern ushort *pw;
	#endif

		if( utf_lang && vk_charset!=VKC_UTF8 )
			r = isoutf(buffer, size, vk_buffer, vk_blength);
		else
		for( ; r<vk_blength; r++ )
			buffer[r] = vk_buffer[r];
	#ifdef VK_USE_KEYSYM
		/*
		 * Changes:
		 * - vi_VN.tcvn report & fixed by Egor Yu. Shkerin <egor@papillon.ru>
		 *   MUST be (*(char *)buffer & 0xFF) instead of *buffer. Because some
		 *   compilers will force RHS operand of = to type of LHS, and buffer
		 *   will be treated as a pointer to 2-byte buffer
		 */
		*keysym = vk_charset==VKC_UTF8 ? *pw|0x01000000 : (*(char *)buffer & 0xFF);
	#else
		*keysym = 0;
	#endif
	}
	return r;
}
/*----------------------------------------------------------------------------*/
#ifndef VK_CORE_ONLY
static void VKInitResource(Display *display, Atom atom, int *resource,
														int default_value)
{
	int value = VKGetValue(display, atom);
	if( value!=-1 )
		*resource = value;
	else
		VKSetValue(display, atom, default_value);
}
/*----------------------------------------------------------------------------*/
static void VKInitHotkeyResource(Display *display, vk_hotkey_info *hotkey)
{
	vk_hotkey_info hk = { 0, 0 };

	VKGetValues(display, vk_hotkey_atom, (long *)&hk, 2);
	if( !hk.state )
		VKSetValues(display, vk_hotkey_atom, (long *)hotkey, 2);
	else
		*hotkey = hk;
}
#endif
/*----------------------------------------------------------------------------*/
static inline void VKSetRootReport(Display *display)
{
	XWindowAttributes wa;
	if( XGetWindowAttributes(display, root, &wa) &&
		(wa.your_event_mask & PropertyChangeMask)==0 )
		XSelectInput(display, root, wa.your_event_mask|PropertyChangeMask);
}
/*----------------------------------------------------------------------------*/
extern int XNextEvent(Display* display, XEvent *event)
{
	static xfunc fptr = 0;

	if( !fptr ) {
		fptr = get_func_entry("libX11.so", "libX11.so.6", "XNextEvent");
		if( fptr ) {
			bs = XKeysymToKeycode(display, XK_BackSpace);
			xk.root = root = DefaultRootWindow(display);
			xk.subwindow = None;
			xk.same_screen = True;
			xk.type = KeyPress;
			xk.state = 0;

		#ifdef VK_CORE_ONLY
			#ifdef VK_CORE_METHOD
				vk_using = VK_CORE_METHOD;
			#else
				vk_using = VKM_VIQR;
			#endif
			vk_method = VKM_OFF;
			vk_charset = VKC_UTF8;
			{
				char *vkm = getenv("VK_CORE_METHOD");
				if( vkm ) {
					int m = atoi(vkm);
					if( m>VKM_OFF && m<=VKM_VIQR )
						vk_using = m;
				}
			}
		#else
			VKAtomInit(display);
			VKInitResource(display, vk_using_atom, &vk_using, VKM_OFF);
			VKInitResource(display, vk_method_atom, &vk_method, VKM_OFF);
			VKInitResource(display, vk_charset_atom, &vk_charset, VKC_UTF8);
			VKInitResource(display, vk_spelling_atom, &vk_spelling, 1);
			VKInitHotkeyResource(display, &hotkey);
			VKChangeCharset(vk_charset);

			VKSetRootReport(display);
		#endif
			TRACE("m=%d, u=%d, c=%d\n", vk_method, vk_using, vk_charset);
		}
		else {
			TRACE("xvnkb: error loading XNextEvent!\n");
			return 0;
		}
	}

	(*fptr)(display, event);
	switch( event->type ) {
		case KeyRelease:
			if( rk==((XKeyEvent *)event)->keycode ) {
				((XKeyEvent *)event)->keycode = bs;
				((XKeyEvent *)event)->state = 0;
				rk = 0;
			}
			break;
		case KeyPress:
			if( bk )
				bk--;
			else {
				focus = ((XKeyEvent *)event)->window;
				key_handler(display, (XKeyEvent *)event);
			}
			break;
		case FocusIn:
			rk = bk = 0;
			focus = ((XFocusChangeEvent *)event)->window;
			VKClearBuffer();
			break;
		case ButtonPress:
			rk = bk = 0;
			VKClearBuffer();
			break;
	#ifndef VK_CORE_ONLY
		case PropertyNotify:
			if( ((XPropertyEvent *)event)->window == root ) {
				char *name = XGetAtomName(display, ((XPropertyEvent *)event)->atom);
				if( name!=NULL ) {
					long id;

					if( !strcmp(name, VKP_HOTKEY) ) {
						VKGetValues(display, ((XPropertyEvent *)event)->atom,
									(long *)&hotkey, 2);
						break;
					}
					id = VKGetValue(display, ((XPropertyEvent *)event)->atom);
					if( !strcmp(name, VKP_CHARSET) )
						VKChangeCharset(id);
					else
					if( !strcmp(name, VKP_METHOD) )
						vk_method = id;
					else
					if( !strcmp(name, VKP_USING) )
						vk_using = id;
					else
					if( !strcmp(name, VKP_SPELLING) )
						VKSetSpelling(id);
					TRACE("%s[%ld]\n", name, id);
					XFree(name);
				}
			}
			break;
	#endif
	}

	return 0;
}
/*----------------------------------------------------------------------------*/
