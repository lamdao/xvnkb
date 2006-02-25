/*----------------------------------------------------------------------------*/
/*  hotkey.c                                                                  */
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
#include "data.h"
#include "property.h"
#include "event.h"
#include "hotkey.h"
#include "button.h"
#include "label.h"
/*----------------------------------------------------------------------------*/
typedef struct {
	int x, y;
	int tx, ty;
	int width, height;
	int ly;
	int event_mask;
	VKLabel value;
	Window window;
	GC gc;

	int visible;
} hk_info;
/*----------------------------------------------------------------------------*/
hk_info hk = {
	0, 0,
	10, 8,
	300, 104,
	0,
	ExposureMask|ButtonReleaseMask|KeyPressMask|KeyReleaseMask,
	{10, 0, 280, 0, 0, 0, NULL, 0},
	0, 0
};
/*----------------------------------------------------------------------------*/
void VKHotkeyAccept();
void VKHotkeyReject();
void VKHotkeyWindowProcess(XEvent *event, void *data);
/*----------------------------------------------------------------------------*/
VKButtonControl B[2][2] = {
	{
		{0, 0, 0, 0, 0, 0, "OK",	 0, VKB_NORMAL, VKHotkeyAccept },
		{0, 0, 0, 0, 0, 0, "Cancel", 0, VKB_NORMAL, VKHotkeyReject }
	},
	{
		{0, 0, 0, 0, 0, 0, "Chọn",	 0, VKB_NORMAL, VKHotkeyAccept },
		{0, 0, 0, 0, 0, 0, "Bỏ",	 0, VKB_NORMAL, VKHotkeyReject }
	}
};
/*----------------------------------------------------------------------------*/
void VKDrawHotkeyWindow()
{
	static char *titles[2] = {"Select hotkey", "Chọn phím bật/tắt"};
	static char *mesages[] = {"Press a key group:", "Nhấn một nhóm phím:"};
	char *S = mesages[vk_interface];
	char *T = titles[vk_interface];
	int fa = vk_text_ascent;

#ifdef USE_XFT
	XftDraw *draw;
	draw = hk.value.draw = XftDrawCreate(display, hk.window, visual, colormap);
#else
	#define	draw
#endif

	XClearWindow(display, hk.window);
	VKSetColor(display, hk.gc, clBackground);
	XFillRectangle(display, hk.window, hk.gc, 0, 0, hk.width, hk.height);
	VKSetColor(display, hk.gc, clBorder);
	XDrawRectangle(display, hk.window, hk.gc, 1, 1, hk.width-3, hk.height-3);
	XFillRectangle(display, hk.window, hk.gc, 1, 1, hk.width-3, vk_text_height+6);
	XDrawLine(display, hk.window, hk.gc, 1, hk.ly, hk.width-3, hk.ly);
	VKDrawLabel(&hk.value);
#ifdef USE_XFT
	XftDrawStringUtf8(draw, &clBlack, vk_font,
						11, fa+5+1, (XftChar8*)T, strlen(T));
	XftDrawStringUtf8(draw, &clWhite, vk_font,
						10, fa+5, (XftChar8*)T, strlen(T));
	XftDrawStringUtf8(draw, &clGray, vk_font,
						hk.tx+1, hk.ty+1, (XftChar8*)S, strlen(S));
	XftDrawStringUtf8(draw, &clBlack, vk_font,
						hk.tx, hk.ty, (XftChar8*)S, strlen(S));
	XftDrawDestroy(draw);
#else
	#undef draw
	VKSetColor(display, hk.gc, clBlack);
	XmbDrawString(display, hk.window, vk_fontset, hk.gc,
						11, fa+5+1, T, strlen(T));
	VKSetColor(display, hk.gc, clWhite);
	XmbDrawString(display, hk.window, vk_fontset, hk.gc,
						10, fa+5, T, strlen(T));
	VKSetColor(display, hk.gc, clGray);
	XmbDrawString(display, hk.window, vk_fontset, hk.gc,
						hk.tx+1, hk.ty+1, S, strlen(S));
	VKSetColor(display, hk.gc, clBlack);
	XmbDrawString(display, hk.window, vk_fontset, hk.gc,
						hk.tx, hk.ty, S, strlen(S));
#endif
}
/*----------------------------------------------------------------------------*/
void VKShowHotkeyWindow()
{
	int x = (screen_width - hk.width) / 2;
	int y = (screen_height - hk.height) / 2;
	unsigned int event_mask = ButtonPressMask|ButtonReleaseMask|
							  PointerMotionMask|ButtonMotionMask;
	VKShowButtons(B[vk_interface], 2);
	XMoveWindow(display, hk.window, x, y);
	XMapRaised(display, hk.window);

	hk.x = x;
	hk.y = y;
	hk.visible = True;
	XGrabKeyboard(display, hk.window, True,
				 GrabModeAsync, GrabModeAsync, CurrentTime);
	XGrabPointer(display, hk.window, True, event_mask,
				 GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
}
/*----------------------------------------------------------------------------*/
void VKHideHotkeyWindow()
{
	VKHideButtons(B[vk_interface], 2);
	hk.visible = False;
	XUngrabPointer(display, CurrentTime);
	XUngrabKeyboard(display, CurrentTime);
	XUnmapWindow(display, hk.window);
}
/*----------------------------------------------------------------------------*/
void VKCreateHotkeyWindow()
{
	static char *max_hk_string = "Alt Control Shift ISO_Left_Tab";
	int i, j, fh, fa, fw;

#ifdef USE_XFT
	XGlyphInfo fi;
	fw = 2 * vk_font->max_advance_width;
	XftTextExtentsUtf8(display, vk_font,
						(uchar *)max_hk_string, strlen(max_hk_string), &fi);
#else
	XRectangle fi;
	fw = 2 * vk_font->per_char['W'].width;
	XmbTextExtents(vk_fontset,
						max_hk_string, strlen(max_hk_string), 0, &fi);
#endif
	hk.width = (fi.width<300 ? 300 : fi.width+fw);

	fa = vk_text_ascent;
	fh = vk_text_height;
	hk.ty = (fa + 5) + fh + 4;
	hk.value.y = 2 * (fh + 4) + 6;
	hk.value.w = hk.width - 20;
	hk.value.h = fh + 4;
	hk.value.ty = hk.value.y + fa + 4;
	hk.ly = hk.value.y + hk.value.h + fh/2;
	VKSetLabel(&hk.value, vk_hotkey);
	
	for( i=0; i<2; i++ ) {
		VKButtonControl *b = B[i];
	#ifdef USE_XFT
		XftTextExtentsUtf8(display, vk_font, (uchar *)"Cancel", 6, &fi);
	#else
		XmbTextExtents(vk_fontset, "Cancel", 6, 0, &fi);
	#endif
		fw = fi.width;
		b[0].w = b[1].w = fw + 24;
		b[0].x = (hk.width - 2 * b[0].w - 24) / 2;
		b[1].x = hk.width - b[0].x - b[0].w;

		for( j=0; j<2; j++ ) {
			b[j].y = hk.ly + fh/2;
			b[j].h = fh + 4;
		}
	}

	hk.height = B[0][0].y + fh + 4 + fh/2;
	hk.window = XCreateWindow(display, root,
						0, 0, hk.width, hk.height,
						0, DefaultDepth(display, screen),
						InputOutput, visual,
						vk_attribmask, &vk_attrib);
	XSelectInput(display, hk.window, MAIN_EVENT_MASKS);
	XDefineCursor(display, hk.window, vk_cursor);

	hk.gc = XCreateGC(display, hk.window, 0, 0);
	hk.value.win = hk.window;
	hk.value.gc = hk.gc;
#ifndef USE_XFT
	XSetFont(display, hk.gc, vk_font->fid);
#endif
	VKRegisterEvent(hk.window, VKHotkeyWindowProcess, &hk);

	VKCreateButtons(hk.window, B[0], 2);
	VKCreateButtons(hk.window, B[1], 2);
}
/*----------------------------------------------------------------------------*/
void VKDestroyHotkeyWindow()
{
	if( hk.visible )
		VKHideHotkeyWindow();

	VKDestroyButtons(B[0], 2);
	VKDestroyButtons(B[1], 2);
	VKUnregisterEvent(hk.window);

	XFreeGC(display, hk.gc);
	XDestroyWindow(display, hk.window);
}
/*----------------------------------------------------------------------------*/
void VKParseHotkey(char *s, int *state, KeySym *sym)
{
	static struct vk_statekey_map {
		char *name;
		int mask;
	} state_keys[] = {
		{"Alt",		VK_ALT},
		{"Control",	VK_CONTROL},
		{"Shift",	VK_SHIFT},
		{"Winkey",	VK_WINKEY},
		{NULL, 0}
	};

	char *p = strtok(s, " ");
	*state = *sym = 0;
	while( p ) {
		struct vk_statekey_map *sk;
		for( sk=state_keys; sk->name; sk++ )
			if( !strcasecmp(p, sk->name) ) break;
		if( sk->name )
			*state |= sk->mask;
		else
			*sym = XStringToKeysym(p);
		p = strtok(NULL, " ");
	}
}
/*----------------------------------------------------------------------------*/
void VKSetHotkeyProperty(int state, KeySym sym)
{
	long keyinfo[] = {
		state, (state & VK_SHIFT) && (sym < 128) ? toupper(sym) : sym
	};
	VKSetValues(display, vk_hotkey_atom, keyinfo, 2);
}
/*----------------------------------------------------------------------------*/
void VKUpdateHotkey()
{
	int state;
	KeySym sym;
	char *s;

	if( !strcmp(vk_hotkey, hk.value.text) ) return;

	s = strdup(hk.value.text);
	VKParseHotkey(s, &state, &sym);
	free(s);

	if( state!=0 && sym!=0 ) {
		VKSetHotkeyProperty(state, sym);
		if( vk_hotkey )
			free(vk_hotkey);
		vk_hotkey = strdup(hk.value.text);
	}
	else {
		hk.value.text = vk_hotkey;
	}
}
/*----------------------------------------------------------------------------*/
void VKParseKeyEvent(XKeyEvent *event)
{
	static char v[32];
	int state = event->state;
	KeySym k = XKeycodeToKeysym(display, event->keycode,
								state & VK_UPPERCASE_STATES ? 1 : 0);

	switch( k ) {
		case XK_Return:
			VKUpdateHotkey();
			VKHideHotkeyWindow();
			break;
		case XK_Escape:
			hk.value.text = vk_hotkey;
			VKHideHotkeyWindow();
			break;
		default:
			if( state & (VK_ALT|VK_CONTROL|VK_SHIFT|VK_WINKEY) ) {
				*v = 0;
				if( state & VK_ALT ) strcat(v, "Alt ");
				if( state & VK_CONTROL ) strcat(v, "Control ");
				if( state & VK_SHIFT ) strcat(v, "Shift ");
				if( state & VK_WINKEY ) strcat(v, "Winkey ");
				strcat(v, XKeysymToString(k));
				VKSetLabel(&hk.value, v);
			}
	}
}
/*----------------------------------------------------------------------------*/
void VKHotkeyAccept()
{
	VKUpdateHotkey();
	VKHideHotkeyWindow();
}
/*----------------------------------------------------------------------------*/
void VKHotkeyReject()
{
	hk.value.text = vk_hotkey;
	VKHideHotkeyWindow();
}
/*----------------------------------------------------------------------------*/
void VKHotkeyWindowProcess(XEvent *event, void *data)
{
	if( event->xany.window!=hk.window ) {
		VKHotkeyReject();
		return;
	}
	switch( event->type ) {
		case Expose:
		case GraphicsExpose:
			VKDrawHotkeyWindow();
			break;
		case KeyPress:
			VKParseKeyEvent((XKeyEvent *)event);
			VKDrawLabel(&hk.value);
			break;
		case ButtonPress:
			if( event->xbutton.x_root<hk.x ||
				event->xbutton.x_root>(hk.x+hk.width-1) ||
				event->xbutton.y_root<hk.y ||
				event->xbutton.y_root>(hk.y+hk.height-1) ) {
				hk.value.text = vk_hotkey;
				VKHideHotkeyWindow();
			}
			break;
		case ButtonRelease:
			break;
	}
}
/*----------------------------------------------------------------------------*/
