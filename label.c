/*----------------------------------------------------------------------------*/
/*  label.c                                                                   */
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
#include "label.h"
/*----------------------------------------------------------------------------*/
void VKDrawLabel(VKLabel *l)
{
	VKSetColor(display, l->gc, clBackground);
	XFillRectangle(display, l->win, l->gc, l->x, l->y, l->w, l->h);
	VKSetColor(display, l->gc, clGray);
	XDrawRectangle(display, l->win, l->gc, l->x, l->y, l->w, l->h);
	if( l->text ) {
#ifdef USE_XFT
		XftDraw *draw = l->draw ? l->draw :
						XftDrawCreate(display, l->win, visual, colormap);
		XftDrawStringUtf8(draw, &clGray, vk_font,
							l->tx+1, l->ty+1, (XftChar8*)l->text, l->l);
		XftDrawStringUtf8(draw, &clBlack, vk_font,
							l->tx, l->ty, (XftChar8*)l->text, l->l);
		if( !l->draw ) XftDrawDestroy(draw);
		l->draw = NULL;
#else
		XSetForeground(display, l->gc, clGray);
		XDrawString(display, l->win, l->gc, l->tx+1, l->ty+1, l->text, l->l);
		XSetForeground(display, l->gc, clBlack);
		XDrawString(display, l->win, l->gc, l->tx, l->ty, l->text, l->l);
#endif
	}
}
/*----------------------------------------------------------------------------*/
void VKSetLabel(VKLabel *l, char *v)
{
	l->text = v;
	if( !v ) return;

	l->l = strlen(v);
	{
	#ifdef USE_XFT
		XGlyphInfo fi;
		XftTextExtentsUtf8(display, vk_font, (uchar *)v, l->l, &fi);
	#else
		XRectangle fi;
		XmbTextExtents(vk_fontset, v, l->l, 0, &fi);
	#endif
		l->tx = l->x + (l->w - fi.width)/2;
	}
}
/*----------------------------------------------------------------------------*/
