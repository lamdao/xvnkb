/*----------------------------------------------------------------------------*/
/*  flash.c                                                                   */
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
#include "flash.h"
#include "event.h"
/*----------------------------------------------------------------------------*/
#ifdef DEBUG
	#define VK_FLASH_TIMEOUT	1
#else
	#define VK_FLASH_TIMEOUT	5
#endif
/*----------------------------------------------------------------------------*/
char *soft_einfo[] =
{
	"Vietnamese keyboard for XWindow version "VERSION,
	"System Software Group of",
	"VISC Software & Security Consultant Company - VISC Ltd.",
	"http://www.visc-network.com",
	0
};
/*----------------------------------------------------------------------------*/
char *soft_vinfo[] =
{
	"Chương trình hỗ trợ gõ tiếng Việt trong XWindow bản "VERSION,
	"Nhóm Phần mềm Hệ thống",
	"Công ty Tư vấn và Phát triển Phần mềm VISC.",
	"http://www.visc-network.com",
	0
};
/*----------------------------------------------------------------------------*/
char **soft_info = soft_einfo;
/*----------------------------------------------------------------------------*/
int soft_infow[] = { 0, 0, 0, 0 };
/*----------------------------------------------------------------------------*/
int vk_flash_width = 0;
int vk_flash_height = 0;
/*----------------------------------------------------------------------------*/
void VKFlashLoadInterface()
{
	soft_info = vk_interface==VK_ENGLISH ? soft_einfo : soft_vinfo;
}
/*----------------------------------------------------------------------------*/
void VKCreateFlash()
{
	int i;
	vk_flash_height = vk_text_height;

	VKFlashLoadInterface();
	for( i=0; soft_info[i]; i++ ) {
		int w;
	#ifdef USE_XFT
		XGlyphInfo fi;
		XftTextExtentsUtf8( display, vk_font,
							(XftChar8*)soft_info[i], strlen(soft_info[i]), &fi );
	#else
		XRectangle fi;
		XmbTextExtents(vk_fontset, soft_info[i], strlen(soft_info[i]), 0, &fi);
	#endif
		w = soft_infow[i] = fi.width;
		if( w>vk_flash_width )
			vk_flash_width = w;
		vk_flash_height += vk_text_height;
	}
	vk_flash_height += 8;
	vk_flash_width += 24;
	flash_window = XCreateWindow(display, root,
					(screen_width-vk_flash_width)/2, (screen_height-vk_flash_height)/2,
					vk_flash_width, vk_flash_height, 0, DefaultDepth(display, screen),
					InputOutput, visual, vk_attribmask, &vk_attrib);
	XSelectInput(display, flash_window, ButtonPressMask|ExposureMask);
	XDefineCursor(display, flash_window, vk_cursor);
	flash_gc = XCreateGC(display, flash_window, 0, 0);
	XSetLineAttributes(display, flash_gc, 3, LineSolid, CapRound, JoinRound);
#ifndef USE_XFT
	XSetFont(display, flash_gc, vk_font->fid);
#endif
	VKRegisterEvent(flash_window, VKFlashWindowProcess, NULL);
}
/*----------------------------------------------------------------------------*/
void VKDestroyFlash()
{
	VKUnregisterEvent(flash_window);

	XFreeGC(display, flash_gc);
	XDestroyWindow(display, flash_window);
}
/*----------------------------------------------------------------------------*/
void VKShowFlash()
{
	vk_timeout = False;
	XMapRaised(display, flash_window);
	alarm(VK_FLASH_TIMEOUT);
	vk_flash_on = True;
}
/*----------------------------------------------------------------------------*/
void VKHideFlash()
{
	vk_flash_on = False;
	XUnmapWindow(display, flash_window);
}
/*----------------------------------------------------------------------------*/
void VKFlashWindowProcess(XEvent *event, void *data)
{
	int i, x, y;
#ifdef USE_XFT
	XftDraw *draw;
#endif
	switch( event->type ) {
		case Expose:
		case GraphicsExpose:
			XClearWindow(display, flash_window);
			VKSetColor(display, flash_gc, clWhite);
			XFillRectangle(display, flash_window, flash_gc,
							0, 0, vk_flash_width, vk_flash_height);
			VKSetColor(display, flash_gc, clBorder);
			XDrawRectangle(display, flash_window, flash_gc,
							2, 2, vk_flash_width-5, vk_flash_height-5);

		#ifdef USE_XFT
			draw = XftDrawCreate(display, flash_window, visual, colormap);
		#endif
			for( y=0, i=0; soft_info[i]; i++ ) {
				int l = strlen(soft_info[i]);

				y += vk_text_height + 4;
				x = (vk_flash_width - soft_infow[i])/2;
			#ifdef USE_XFT
				XftDrawStringUtf8(draw, &clGray, vk_font,
										x+1, y+1, (XftChar8*)soft_info[i], l);
				XftDrawStringUtf8(draw, &clText, vk_font,
										x, y, (XftChar8*)soft_info[i], l);
			#else
				XSetForeground(display, flash_gc, clGray);
				XmbDrawString(display, flash_window, vk_fontset, flash_gc,
										x+1, y+1, soft_info[i], l);
				XSetForeground(display, flash_gc, clText);
				XmbDrawString(display, flash_window, vk_fontset, flash_gc,
										x, y, soft_info[i], l);
			#endif
			}
		#ifdef USE_XFT
			XftDrawDestroy(draw);
		#endif
			break;
		case ButtonPress:
			alarm(0);
			VKHideFlash();
			break;
	}
}
/*----------------------------------------------------------------------------*/
