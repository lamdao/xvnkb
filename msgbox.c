/*----------------------------------------------------------------------------*/
/*  msgbox.c                                                                  */
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
#include "msgbox.h"
#include "button.h"
/*----------------------------------------------------------------------------*/
typedef struct {
	int x, y;
	int length;
	int width;
	char *value;
} msgbox_text;
/*----------------------------------------------------------------------------*/
typedef struct {
	int count;
	msgbox_text text[8];
} msgbox_data;
/*----------------------------------------------------------------------------*/
typedef struct {
	int width, height;
	int event_mask;
	Window window;
	GC gc;

	char *text;
	msgbox_data data;
} msgbox_info;
/*----------------------------------------------------------------------------*/
void VKMsgBoxDestroy();
void VKMsgBoxProcess(XEvent *event, void *data);
/*----------------------------------------------------------------------------*/
msgbox_info msgbox = {
	300, 104,
	ExposureMask|ButtonPressMask,
	0, 0, 0
};
/*----------------------------------------------------------------------------*/
static VKButtonControl B[2] = {
	{0, 0, 0, 0, 0, 0, "OK",	 0, VKB_NORMAL, VKMsgBoxDestroy },
	{0, 0, 0, 0, 0, 0, "Đóng",	 0, VKB_NORMAL, VKMsgBoxDestroy }
};
/*----------------------------------------------------------------------------*/
void VKMsgBoxDraw()
{
	static char *titles[2] = {"Warning", "Chú ý"};
	char *T = titles[vk_interface];
	int fa = vk_text_ascent, i;

#ifdef USE_XFT
	XftDraw *draw;
	draw = XftDrawCreate(display, msgbox.window, visual, colormap);
#else
	#define	draw
#endif

	XClearWindow(display, msgbox.window);
	VKSetColor(display, msgbox.gc, clBackground);
	XFillRectangle(display, msgbox.window, msgbox.gc, 0, 0, msgbox.width, msgbox.height);
	VKSetColor(display, msgbox.gc, clBorder);
	XDrawRectangle(display, msgbox.window, msgbox.gc, 1, 1, msgbox.width-3, msgbox.height-3);
	XFillRectangle(display, msgbox.window, msgbox.gc, 1, 1, msgbox.width-3, vk_text_height+6);
#ifdef USE_XFT
	XftDrawStringUtf8(draw, &clBlack, vk_font,
						11, fa+5+1, (XftChar8*)T, strlen(T));
	XftDrawStringUtf8(draw, &clWhite, vk_font,
						10, fa+5, (XftChar8*)T, strlen(T));
	for( i = 0; i < msgbox.data.count; i++ ) {
		XftDrawStringUtf8(draw, &clGray, vk_font,
			msgbox.data.text[i].x+1, msgbox.data.text[i].y+1,
			(XftChar8*)msgbox.data.text[i].value, msgbox.data.text[i].length);
		XftDrawStringUtf8(draw, &clText, vk_font,
			msgbox.data.text[i].x, msgbox.data.text[i].y,
			(XftChar8*)msgbox.data.text[i].value, msgbox.data.text[i].length);
	}
	XftDrawDestroy(draw);
#else
	#undef draw
	VKSetColor(display, msgbox.gc, clBlack);
	XmbDrawString(display, msgbox.window, vk_fontset, msgbox.gc,
						11, fa+5+1, T, strlen(T));
	VKSetColor(display, msgbox.gc, clWhite);
	XmbDrawString(display, msgbox.window, vk_fontset, msgbox.gc,
						10, fa+5, T, strlen(T));
	for( i = 0; i < msgbox.data.count; i++ ) {
		VKSetColor(display, msgbox.gc, clGray);
		XmbDrawString(display, msgbox.window, vk_fontset, msgbox.gc,
			msgbox.data.text[i].x+1, msgbox.data.text[i].y+1,
			msgbox.data.text[i].value, msgbox.data.text[i].length);
		VKSetColor(display, msgbox.gc, clText);
		XmbDrawString(display, msgbox.window, vk_fontset, msgbox.gc,
			msgbox.data.text[i].x, msgbox.data.text[i].y,
			msgbox.data.text[i].value, msgbox.data.text[i].length);
	}
#endif
	i = msgbox.data.text[i - 1].y + 12;
	VKSetColor(display, msgbox.gc, clGray);
	XDrawLine(display, msgbox.window, msgbox.gc, 1, i, msgbox.width - 3, i);
}
/*----------------------------------------------------------------------------*/
void VKCreateMsgBoxWindow(char *message)
{
	char *p = strdup(message);
	int i, j, fw, w = 0;

#ifdef USE_XFT
	XGlyphInfo fi;
	fw = 2 * vk_font->max_advance_width;
#else
	XRectangle fi;
	fw = 2 * vk_font->per_char['W'].width;
#endif
	msgbox.text = p;
	p = strtok(p, "\n");
#ifdef USE_XFT
	XftTextExtentsUtf8(display, vk_font, (uchar *)p, j = strlen(p), &fi);
#else
	XmbTextExtents(vk_fontset, p, j = strlen(p), 0, &fi);
#endif
	msgbox.data.text[0].value = p;
	msgbox.data.text[0].length = j;
	msgbox.data.text[0].width = w = fi.width;
	msgbox.data.count = i = 1;
	while( p ) {
		p = strtok(0, "\n");
		if( !p ) break;
#ifdef USE_XFT
		XftTextExtentsUtf8(display, vk_font, (uchar *)p, j = strlen(p), &fi);
#else
		XmbTextExtents(vk_fontset, p, j = strlen(p), 0, &fi);
#endif
		if( w < fi.width ) w = fi.width;
		msgbox.data.text[i].value = p;
		msgbox.data.text[i].length = j;
		msgbox.data.text[i].width = fi.width;
		i = i + 1;
	}
	msgbox.data.count = i;
	msgbox.width = w = (w < 250 ? 250 : w) + fw;
	msgbox.height = j = (i + 1) * vk_text_height;
	for( i--; i >= 0; i--, j -= vk_text_height ) {
		msgbox.data.text[i].x = (w - msgbox.data.text[i].width) / 2;
		msgbox.data.text[i].y = j + 4;
	}

	for( i = 0; i < 2; i++ ) {
		VKButtonControl *b = &B[i];
	#ifdef USE_XFT
		XftTextExtentsUtf8(display, vk_font, (uchar *)b->text, strlen(b->text), &fi);
	#else
		XmbTextExtents(vk_fontset, b->text, strlen(b->text), 0, &fi);
	#endif
		b->x = (w - fi.width) / 2;
		b->y = msgbox.data.text[msgbox.data.count - 1].y + vk_text_height + 2;
		b->h = vk_text_height + 8;
		b->w = fi.width + 24;
	}

	msgbox.height = B[0].y + B[0].h + vk_text_height / 2 + 4;
	msgbox.window = XCreateWindow(display, root,
						0, 0, msgbox.width, msgbox.height,
						0, DefaultDepth(display, screen),
						InputOutput, visual,
						vk_attribmask, &vk_attrib);
	XSelectInput(display, msgbox.window, msgbox.event_mask);
	XDefineCursor(display, msgbox.window, vk_cursor);

	msgbox.gc = XCreateGC(display, msgbox.window, 0, 0);
#ifndef USE_XFT
	XSetFont(display, msgbox.gc, vk_font->fid);
#endif
	VKRegisterEvent(msgbox.window, VKMsgBoxProcess, &msgbox);
	VKCreateButtons(msgbox.window, B, 2);
}
/*----------------------------------------------------------------------------*/
void VKShowMessage(char *message)
{
	int x, y;
	unsigned int event_mask = ButtonPressMask|ButtonReleaseMask|
							  PointerMotionMask|ButtonMotionMask;

	VKCreateMsgBoxWindow(message);
	x = (screen_width - msgbox.width) / 2;
	y = (screen_height - msgbox.height) / 2;
	VKShowButtons(&B[vk_interface], 1);
	XMoveWindow(display, msgbox.window, x, y);
	XMapRaised(display, msgbox.window);
	XGrabPointer(display, msgbox.window, True, event_mask,
				 GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
}
/*----------------------------------------------------------------------------*/
void VKMsgBoxDestroy()
{
	XUngrabPointer(display, CurrentTime);
	XUngrabKeyboard(display, CurrentTime);
	XUnmapWindow(display, msgbox.window);

	VKDestroyButtons(B, 2);
	VKUnregisterEvent(msgbox.window);

	XFreeGC(display, msgbox.gc);
	XDestroyWindow(display, msgbox.window);
	free(msgbox.text);
}
/*----------------------------------------------------------------------------*/
void VKMsgBoxProcess(XEvent *event, void *data)
{
	switch( event->type ) {
		case Expose:
		case GraphicsExpose:
			VKMsgBoxDraw();
			break;
		case ButtonPress:
			VKMsgBoxDestroy();
			break;
	}
}
/*----------------------------------------------------------------------------*/
