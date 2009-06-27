/*----------------------------------------------------------------------------*/
/*  mainwin.c                                                                 */
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
#include "menu.h"
#include "event.h"
#include "systray.h"
/*----------------------------------------------------------------------------*/
char *Ss[] = { "Off", "Vni", "Telex", "Viqr" };
/*----------------------------------------------------------------------------*/
void VKIconLoadInterface()
{
	Ss[0] = vk_interface==VK_VIETNAMESE ? "Tắt" : "Off";
}
/*----------------------------------------------------------------------------*/
void VKMainWindowProcess(XEvent *event, void *data);
/*----------------------------------------------------------------------------*/
void VKDrawIcon()
{
	long x, y, h, l;
	char *S = (vk_docking == VKD_ON) ? (vk_method == VKM_OFF ? "N" : "V") : Ss[vk_method];

#ifdef USE_XFT
	XftDraw *draw;
	XGlyphInfo fi;
	XftTextExtentsUtf8(display, vk_font, (uchar *)S, l=strlen(S), &fi);
#else
	XRectangle fi;
	XmbTextExtents(vk_fontset, S, l=strlen(S), 0, &fi);
#endif
	h = vk_text_height;
	x = (vk_icon_width - fi.width)/2;
	y = vk_text_ascent + (vk_icon_height - h)/2 + 1;

	XClearWindow(display, main_window);
	VKSetColor(display, main_gc, clBackground);
	XFillRectangle(display, main_window, main_gc,
							0, 0, vk_icon_width, vk_icon_height);
	VKSetColor(display, main_gc, clBorder);
	XDrawRectangle(display, main_window, main_gc,
							1, 1, vk_icon_width-3, vk_icon_height-3);
#ifdef USE_XFT
	draw = XftDrawCreate(display, main_window, visual, colormap);
	XftDrawStringUtf8(draw, &clGray, vk_font, x+1, y+1, (XftChar8*)S, l);
	XftDrawStringUtf8(draw, &clText, vk_font, x, y, (XftChar8*)S, l);
	XftDrawDestroy(draw);
#else
	XSetForeground(display, main_gc, clGray);
	XmbDrawString(display, main_window, vk_fontset, main_gc, x+1, y+1, S, l);
	XSetForeground(display, main_gc, clText);
	XmbDrawString(display, main_window, vk_fontset, main_gc, x, y, S, l);
#endif
}
/*----------------------------------------------------------------------------*/
void VKSetDefaultColor()
{
	clBackground = clWhite;
	clBorder = clMenuBar;
	clText = clRed;
}
/*----------------------------------------------------------------------------*/
void VKSetMainWindowHints(int w, int h)
{
	XSizeHints sh;
	sh.flags = PMinSize | PMaxSize;
	sh.min_width = sh.max_width = w;
	sh.min_height = sh.max_height = h;
	XSetWMNormalHints(display, main_window, &sh);
}
/*----------------------------------------------------------------------------*/
void VKCalcMainWindowSize()
{
	if( vk_docking == VKD_ON ) {
		VKSystrayCalcIconSize();
		return;
	}
#ifdef USE_XFT
	XGlyphInfo fi;
	XftTextExtentsUtf8(display, vk_font, (uchar *)"Telex", 5, &fi);
	vk_icon_width = fi.width + 16;
	vk_icon_height = 16 + vk_text_height;
#else
	vk_icon_width = XTextWidth(vk_font, "Telex", 5) + 16;
	vk_icon_height = 16 + vk_text_height;
#endif
	if( vk_x==-1 && vk_y==-1 ) {
		vk_x = screen_width - vk_icon_width - 12;
		vk_y = screen_height - vk_icon_height - 2;
	}
	else {
		if( vk_x<0 )
			vk_x = 0;
		else
		if( vk_x+vk_icon_width>=screen_width )
			vk_x = screen_width - vk_icon_width - 1;

		if( vk_y<0 )
			vk_y = 0;
		else
		if( vk_y+vk_icon_height>=screen_height )
			vk_y = screen_height - vk_icon_height - 1;
	}
}
/*----------------------------------------------------------------------------*/
void VKCreateMainWindow()
{
	VKIconLoadInterface();
	VKCalcMainWindowSize();
	main_window = XCreateWindow(display, root,
					vk_x, vk_y, vk_icon_width, vk_icon_height, 0,
					DefaultDepth(display, screen), InputOutput, visual,
					vk_attribmask, &vk_attrib);
	XSetSelectionOwner(display, visckey_atom, main_window, CurrentTime);
	XSelectInput(display, main_window,
		MAIN_EVENT_MASKS|VisibilityChangeMask|StructureNotifyMask);

	main_gc = XCreateGC(display, main_window, 0, 0);
	XDefineCursor(display, main_window, vk_cursor);
#ifndef USE_XFT
	XSetFont(display, main_gc, vk_font->fid);
#endif
	XStoreName(display, main_window, PROGRAM_NAME);
	XChangeProperty(display, main_window, XInternAtom(display, "WM_CLASS", False),
		XA_STRING, 8, PropModeReplace, (uchar *)PROGRAM_NAME, strlen(PROGRAM_NAME));
	XChangeProperty(display, main_window, XInternAtom(display, "_NET_WM_NAME", False),
		XA_STRING, 8, PropModeReplace, (uchar *)PROGRAM_NAME, strlen(PROGRAM_NAME));
	VKRegisterEvent(main_window, VKMainWindowProcess, NULL);

	if( vk_docking != VKD_OFF ) { // ON or AUTO
		if( VKIsDockable() ) {
			vk_docking = VKD_ON;
			VKSetMainWindowHints(vk_icon_height, vk_icon_height);
			VKRequestDocking();
		}
		else {
			vk_docking = VKD_OFF;
			XMapWindow(display, main_window);
			VKSetAutoDocking(VKD_ON);
		}
	}
	else {
		vk_docking = VKD_OFF;
		XMapWindow(display, main_window);
	}

	VKSetDefaultColor();
}
/*----------------------------------------------------------------------------*/
void VKDestroyMainWindow()
{
	VKUnregisterEvent(main_window);

	XFreeGC(display, main_gc);
	XDestroyWindow(display, main_window);
}
/*----------------------------------------------------------------------------*/
void VKDockMainWindow()
{
	if( VKIsDockable() ) {
		vk_docking = VKD_ON;
		VKDestroyMainWindow();
		VKCreateMainWindow();
		VKUpdateDockingMessage();
	}
}
/*----------------------------------------------------------------------------*/
void VKUndockMainWindow()
{
	vk_docking = VKD_OFF;
	VKDestroyMainWindow();
	VKCreateMainWindow();
	VKUpdateDockingMessage();
}
/*----------------------------------------------------------------------------*/
void VKMainWindowProcess(XEvent *event, void *data)
{
	static int x, y;
	static int dragging = False, has_moved = False;

	switch( event->type ) {
		case Expose:
		case GraphicsExpose:
			VKDrawIcon();
			break;
		case ButtonPress:
			VKHideMenu();
			x = event->xbutton.x_root;
			y = event->xbutton.y_root;
			dragging = event->xbutton.button==Button1;
			break;
		case MotionNotify:
			if( vk_docking != VKD_ON && dragging ) {
				has_moved = True;
				vk_x += event->xbutton.x_root - x;
				vk_y += event->xbutton.y_root - y;
				x = event->xbutton.x_root;
				y = event->xbutton.y_root;
				if( vk_x<0 ) vk_x = 0;
				if( vk_y<0 ) vk_y = 0;
				if( vk_x+vk_icon_width>=screen_width )
					vk_x = screen_width-vk_icon_width-1;
				if( vk_y+vk_icon_height>=screen_height )
					vk_y = screen_height-vk_icon_height-1;
				XMoveWindow(display, main_window, vk_x, vk_y);
			}
			break;
		case ButtonRelease:
			dragging = False;
			if( has_moved )
				has_moved = False;
			else
			switch( event->xbutton.button ) {
				case Button1:
					VKSwitchMethod();
					VKDrawIcon();
					break;
				case Button2:
					vk_done = True;
					break;
				case Button3:
					// * Workaround for Fluxbox systray
					// Fluxbox systray doesn't report absolute position
					// of client in ConfigureNotify message event
					vk_x = event->xbutton.x_root - event->xbutton.x;
					vk_y = event->xbutton.y_root - event->xbutton.y;
					VKShowMenu();
					break;
			}
			break;
		case VisibilityNotify:
			if( ((XVisibilityEvent *)event)->state != VisibilityUnobscured )
				XRaiseWindow(display, main_window);
			break;
		case ReparentNotify:
			if( vk_docking == VKD_ON && event->xreparent.parent == root ) {
				VKUndockMainWindow();
				VKSetAutoDocking(VKD_ON);
			}
			break;
		case ConfigureNotify:
			if( vk_docking == VKD_ON ) {
				vk_x = event->xconfigure.x;
				vk_y = event->xconfigure.y;
				vk_icon_width = event->xconfigure.width;
				vk_icon_height = event->xconfigure.height;
				if( vk_icon_height > vk_icon_width )
					vk_icon_width = vk_icon_height;
				else
					vk_icon_height = vk_icon_width;

				VKSetMainWindowHints(vk_icon_width, vk_icon_height);
			}
			break;
		case ClientMessage:
			TRACE("MessageID = %ld\n", event->xclient.data.l[1]);
	}
}
/*----------------------------------------------------------------------------*/
