/*----------------------------------------------------------------------------*/
/*  button.c                                                                  */
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
#include "button.h"
/*----------------------------------------------------------------------------*/
void VKDrawButton(VKButtonControl *b)
{
	if( b->style==VKB_NORMAL ) {
		#define s b->text
		#define l b->l
	#ifdef USE_XFT
		XftDraw *draw = XftDrawCreate(display, b->win, visual, colormap);
		XftDrawStringUtf8(draw, &clGray, vk_font, b->tx+1, b->ty+1, (XftChar8*)s, l);
		XftDrawStringUtf8(draw, &clBlack, vk_font, b->tx, b->ty, (XftChar8*)s, l);
		XftDrawDestroy(draw);
	#else
		VKSetColor(display, b->gc, clGray);
		XmbDrawString(display, b->win, vk_fontset, b->gc, b->tx+1, b->ty+1, s, l);
		VKSetColor(display, b->gc, clBlack);
		XmbDrawString(display, b->win, vk_fontset, b->gc, b->tx, b->ty, s, l);
	#endif
		#undef s
		#undef l
	}
	else {
		int yc = b->h/2;
		int xc = b->w/2;

		XPoint p[] = {
			{2, yc-3},
			{b->w-2, yc-3},
			{xc, 2},

			{2, yc+4},
			{b->w-2, yc+4},
			{xc, b->h-2},
		};
		VKSetColor(display, b->gc, clBorder);
		XDrawLine(display, b->win, b->gc, 0, b->h/2, b->w, b->h/2);
		XFillPolygon(display, b->win, b->gc, p, 3, 0, 0);
		XFillPolygon(display, b->win, b->gc, &p[3], 3, 0, 0);
	}
}
/*----------------------------------------------------------------------------*/
void VKButtonControlProcess(XEvent *event, void *data)
{
	VKButtonControl *bc = (VKButtonControl *)data;
	switch( event->type ) {
		case Expose:
		case GraphicsExpose:
			VKDrawButton(bc);
			break;
		case ButtonRelease:
			if( bc->style==VKB_NORMAL )
				bc->action();
			else
				bc->action(((XButtonEvent *)event)->y < bc->h/2);
			break;
	}
}
/*----------------------------------------------------------------------------*/
void VKCreateButton(Window p, VKButtonControl *b)
{
#ifdef USE_XFT
	XGlyphInfo fi;
	XftTextExtentsUtf8(display, vk_font, (uchar *)b->text, b->l=strlen(b->text), &fi);
#else
	XRectangle fi;
	XmbTextExtents(vk_fontset, b->text, b->l=strlen(b->text), 0, &fi);
#endif
	b->ty = vk_text_ascent + 4;
	b->tx = (b->w - fi.width)/2;

#ifdef USE_XFT
	b->win = XCreateSimpleWindow(display, p,
				b->x, b->y, b->w, b->h, 1, clBorder.pixel, clWhite.pixel);
#else
	b->win = XCreateSimpleWindow(display, p,
				b->x, b->y, b->w, b->h, 1, clBorder, clWhite);
#endif	
	XSelectInput(display, b->win, MAIN_EVENT_MASKS);
	XDefineCursor(display, b->win, vk_cursor);
	b->gc = XCreateGC(display, b->win, 0, 0);
	VKRegisterEvent(b->win, VKButtonControlProcess, b);
}
/*----------------------------------------------------------------------------*/
void VKDestroyButton(VKButtonControl *b)
{
	VKUnregisterEvent(b->win);
	XFreeGC(display, b->gc);
	XDestroyWindow(display, b->win);
}
/*----------------------------------------------------------------------------*/
void VKCreateButtons(Window p, VKButtonControl *b, int n)
{
	int i;
	for( i=0; i<n; i++ )
		VKCreateButton(p, &b[i]);
}
/*----------------------------------------------------------------------------*/
void VKDestroyButtons(VKButtonControl *b, int n)
{
	int i;
	for( i=0; i<n; i++ )
		VKDestroyButton(&b[i]);
}
/*----------------------------------------------------------------------------*/
void VKShowButtons(VKButtonControl *b, int n)
{
	int i;
	for( i=0; i<n; i++ )
		VKShowButton(b[i]);
}
/*----------------------------------------------------------------------------*/
void VKHideButtons(VKButtonControl *b, int n)
{
	int i;
	for( i=0; i<n; i++ )
		VKHideButton(b[i]);
}
/*----------------------------------------------------------------------------*/
