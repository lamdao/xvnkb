/*----------------------------------------------------------------------------*/
/*  font.c                                                                    */
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
#include "font.h"
#include "label.h"
#include "button.h"
/*----------------------------------------------------------------------------*/
typedef struct {
	int x, y;
	int w, h;
	int tx, ty;
	char *text;
} VKControl;
/*----------------------------------------------------------------------------*/
typedef struct {
	int x, y;
	int tx, ty;
	int width, height;
	int ly;
	int event_mask;
	Window window;
	GC gc;
	int visible;

	/*
	VKLabel name;
	VKLabel style;
	VKLabel size;
	*/
} fnt_info;
/*----------------------------------------------------------------------------*/
fnt_info fnt = {
	0, 0,
	10, 8,
	300, 104,
	0,
	ExposureMask|ButtonReleaseMask|KeyPressMask|KeyReleaseMask,
	0, 0,
	0,
	
};
/*----------------------------------------------------------------------------*/
void VKFontNameChange(int a) {}
void VKFontStyleChange(int a) {}
void VKFontSizeChange(int a) {}
void VKFontAccept() {}
void VKFontReject() {}
/*----------------------------------------------------------------------------*/
VKLabel fl[] = {
	{0, 0, 0, 0, 0, 0, "+", 0},
	{0, 0, 0, 0, 0, 0, "+", 0},
	{0, 0, 0, 0, 0, 0, "+", 0},
};
/*----------------------------------------------------------------------------*/
VKButtonControl fb[] = {
	{0, 0, 0, 0, 0, 0, "+", 0, VKB_UPDOWN, VKFontNameChange},
	{0, 0, 0, 0, 0, 0, "+", 0, VKB_UPDOWN, VKFontStyleChange},
	{0, 0, 0, 0, 0, 0, "+", 0, VKB_UPDOWN, VKFontSizeChange},
};
/*----------------------------------------------------------------------------*/
VKControl *fc[] = {
	(VKControl *)&fl[0]/*&fnt.name*/, (VKControl *)&fl[1]/*fnt.style*/, (VKControl *)&fl[2]/*fnt.size*/,
	(VKControl *)&fb[0], (VKControl *)&fb[1], (VKControl *)&fb[3],
	0
};
/*----------------------------------------------------------------------------*/
VKButtonControl fb_actions[2][2] = {
	{
		{0, 0, 0, 0, 0, 0, "OK",	 0, VKB_NORMAL, VKFontAccept },
		{0, 0, 0, 0, 0, 0, "Cancel", 0, VKB_NORMAL, VKFontReject }
	},
	{
		{0, 0, 0, 0, 0, 0, "Chọn",	 0, VKB_NORMAL, VKFontAccept },
		{0, 0, 0, 0, 0, 0, "Bỏ",	 0, VKB_NORMAL, VKFontReject }
	}
};
/*----------------------------------------------------------------------------*/
void VKFontProcess(XEvent *event);
/*----------------------------------------------------------------------------*/
void VKDrawFontDialog()
{
	static char *titles[2] = {"Select interface font", "Chọn font giao dien"};
	static char *mesages[] = {"Press a key group:", "Nhấn một nhóm phím:"};
	char *S = mesages[vk_interface];
	char *T = titles[vk_interface];
	int i, fa = vk_text_ascent;

#ifdef USE_XFT
	XftDraw *draw;
	draw = XftDrawCreate(display, fnt.window, visual, colormap);
#else
	#define	draw
#endif

	XClearWindow(display, fnt.window);
	VKSetColor(display, fnt.gc, clBackground);
	XFillRectangle(display, fnt.window, fnt.gc, 0, 0, fnt.width, fnt.height);
	VKSetColor(display, fnt.gc, clBorder);
	XDrawRectangle(display, fnt.window, fnt.gc, 1, 1, fnt.width-3, fnt.height-3);
	XFillRectangle(display, fnt.window, fnt.gc, 1, 1, fnt.width-3, vk_text_height+6);
	XDrawLine(display, fnt.window, fnt.gc, 1, fnt.ly, fnt.width-3, fnt.ly);
	for( i=0; i<3; i++ ) {
		VKDrawLabel((VKLabel *)fc[i]);
	}
#ifdef USE_XFT
	XftDrawStringUtf8(draw, &clBlack, vk_font,
						11, fa+5+1, (XftChar8*)T, strlen(T));
	XftDrawStringUtf8(draw, &clWhite, vk_font,
						10, fa+5, (XftChar8*)T, strlen(T));
	XftDrawStringUtf8(draw, &clGray, vk_font,
						fnt.tx+1, fnt.ty+1, (XftChar8*)S, strlen(S));
	XftDrawStringUtf8(draw, &clBlack, vk_font,
						fnt.tx, fnt.ty, (XftChar8*)S, strlen(S));
	XftDrawDestroy(draw);
#else
	#undef draw
	VKSetColor(display, fnt.gc, clBlack);
	XmbDrawString(display, fnt.window, vk_fontset, fnt.gc,
						11, fa+5+1, T, strlen(T));
	VKSetColor(display, fnt.gc, clWhite);
	XmbDrawString(display, fnt.window, vk_fontset, fnt.gc,
						10, fa+5, T, strlen(T));
	VKSetColor(display, fnt.gc, clGray);
	XmbDrawString(display, fnt.window, vk_fontset, fnt.gc,
						fnt.tx+1, fnt.ty+1, S, strlen(S));
	VKSetColor(display, fnt.gc, clBlack);
	XmbDrawString(display, fnt.window, vk_fontset, fnt.gc,
						fnt.tx, fnt.ty, S, strlen(S));
#endif
}
/*----------------------------------------------------------------------------*/
void VKShowFontDialog()
{
	int x = (screen_width - fnt.width) / 2;
	int y = (screen_height - fnt.height) / 2;
	unsigned int event_mask = ButtonPressMask|ButtonReleaseMask|
							  PointerMotionMask|ButtonMotionMask;
	XMoveWindow(display, fnt.window, x, y);
	XMapRaised(display, fnt.window);

	fnt.x = x;
	fnt.y = y;
	fnt.visible = True;
	XGrabKeyboard(display, fnt.window, True,
				 GrabModeAsync, GrabModeAsync, CurrentTime);
	XGrabPointer(display, fnt.window, True, event_mask,
				 GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
}
/*----------------------------------------------------------------------------*/
void VKHideFontDialog()
{
	fnt.visible = False;
	XUngrabPointer(display, CurrentTime);
	XUngrabKeyboard(display, CurrentTime);
	XUnmapWindow(display, fnt.window);
}
/*----------------------------------------------------------------------------*/
void VKFontControlInit(int x, int y, int w, int h)
{
	int i, ww[] = { 3*w/6, 2*w/6, 1*w/6, h/2, h/2, h/2 };

	DUMP("start\n");
	for( i=0; i<6; i++ ) {
		(*fc[i]).y = y;
		(*fc[i]).h = h;
		/*(*fc[i]).w = ww[i];*/
		if( i>0 )
		DUMP("fc[%d] = %p\n", i-1, fc[i-1]);
	}
	for( i=0; fc[i]; i++ )
		DUMP("fc[%d] = %p\n", i, fc[i]);
	/*
	fc[0]->x = x;
	for( i=1; fc[i]; i++ ) {
		DUMP("x=%d,w=%d\n",fc[i-1]->x,fc[i-1]->w);
		//fc[i]->x = fc[i-1]->x + fc[i-1]->w + 4;
		DUMP("huh? i=%d, %p\n", i, fc[i]);
	}
	*/
	DUMP("done\n");
}
/*----------------------------------------------------------------------------*/
void VKCreateFontDialog()
{
	static char *max_fnt_string = "Alt Control Shift ISO_Left_Tab";
	int i, j, fh, fa, fw;

#ifdef USE_XFT
	XGlyphInfo fi;
	fw = 2 * vk_font->max_advance_width;
	XftTextExtentsUtf8(display, vk_font,
						max_fnt_string, strlen(max_fnt_string), &fi);
#else
	XRectangle fi;
	fw = 2 * vk_font->perchar['W'].width;
	XmbTextExtents(vk_fontset,
						max_fnt_string, strlen(max_fnt_string), 0, &fi);
#endif
	fnt.width = (fi.width<300 ? 300 : fi.width+fw);

	fa = vk_text_ascent;
	fh = vk_text_height;
	fnt.ty = (fa + 5) + fh + 4;
	VKFontControlInit(20, 2 * (fh + 4) + 6, fnt.width - 20, fh+4);
	fnt.ly = 0;//fnt.name.y + fnt.name.h + fh/2;
	
	
	for( i=0; i<2; i++ ) {
		VKButtonControl *b = fb_actions[i];
	#ifdef USE_XFT
		XftTextExtentsUtf8(display, vk_font, "Cancel", 6, &fi);
	#else
		XmbTextExtents(vk_fontset, "Cancel", 6, 0, &fi);
	#endif
		fw = fi.width;
		b[0].w = b[1].w = fw + 24;
		b[0].x = (fnt.width - 2 * b[0].w - 24) / 2;
		b[1].x = fnt.width - b[0].x - b[0].w;

		for( j=0; j<2; j++ ) {
			b[j].y = fnt.ly + fh/2;
			b[j].h = fh + 4;
		}
	}

	fnt.height = fb_actions[0][0].y + fh + 4 + fh/2;
	fnt.window = XCreateWindow(display, root,
						0, 0, fnt.width, fnt.height,
						0, DefaultDepth(display, screen),
						InputOutput, visual,
						vk_attribmask, &vk_attrib);
	XSelectInput(display, fnt.window, MAIN_EVENT_MASKS);
	XDefineCursor(display, fnt.window, vk_cursor);

	fnt.gc = XCreateGC(display, fnt.window, 0, 0);
#ifndef USE_XFT
	XSetFont(display, fnt.gc, vk_font->fid);
#endif
	VKRegisterEvent(fnt.window, VKFontProcess);
	DUMP("create done\n");
}
/*----------------------------------------------------------------------------*/
void VKDestroyFontDialog()
{
	if( fnt.visible )
		VKHideFontDialog();

	VKUnregisterEvent(fnt.window);

	XFreeGC(display, fnt.gc);
	XDestroyWindow(display, fnt.window);
}
/*----------------------------------------------------------------------------*/
void VKFontProcess(XEvent *event)
{
	switch( event->type ) {
		case Expose:
		case GraphicsExpose:
			VKDrawFontDialog();
			break;
		case ButtonPress:
			if( event->xbutton.x_root<fnt.x ||
				event->xbutton.x_root>(fnt.x+fnt.width-1) ||
				event->xbutton.y_root<fnt.y ||
				event->xbutton.y_root>(fnt.y+fnt.height-1) ) {
				//fnt.value.text = vk_hotkey;
				VKHideFontDialog();
			}
			break;
		case ButtonRelease:
			break;
	}
}
/*----------------------------------------------------------------------------*/
