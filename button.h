/*----------------------------------------------------------------------------*/
/*  button.h                                                                  */
/*----------------------------------------------------------------------------*/
/*  copyright         : (C) 2002 by Dao Hai Lam                               */
/*                      VISC Software & Security Consultant Company           */
/*                      Hall 3, Quang Trung Software City                     */
/*                      Tan Chanh Hiep Ward, District 12,                     */
/*                      Ho Chi Minh city, VIETNAM                             */
/*  website           : http://www.visc-network.com                           */
/*  email             : lam@visc-network.com                                  */
/*  last modify       : Sun,  4 Aug 2002 15:34:55 +0700                       */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*   This program is free software; you can redistribute it and/or modify     */
/*   it under the terms of the GNU General Public License as published by     */
/*   the Free Software Foundation; either version 2 of the License, or        */
/*   (at your option) any later version.                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef __BUTTON_H
#define __BUTTON_H
/*----------------------------------------------------------------------------*/
#include "event.h"
/*----------------------------------------------------------------------------*/
#define VKB_NORMAL	0
#define VKB_UPDOWN	1
/*----------------------------------------------------------------------------*/
typedef struct {
	int x, y;
	int w, h;
	int tx, ty;
	char *text;
	int l;
	int style;

	void (*action)();
	Window win;
	GC gc;
} VKButtonControl;
/*----------------------------------------------------------------------------*/
void VKCreateButton(Window p, VKButtonControl *b);
void VKDestroyButton(VKButtonControl *b);
/*----------------------------------------------------------------------------*/
#define VKShowButton(b)	XMapWindow(display, b.win)
#define VKHideButton(b)	XUnmapWindow(display, b.win)
/*----------------------------------------------------------------------------*/
void VKCreateButtons(Window p, VKButtonControl *b, int n);
void VKDestroyButtons(VKButtonControl *b, int n);
void VKShowButtons(VKButtonControl *b, int n);
void VKHideButtons(VKButtonControl *b, int n);
/*----------------------------------------------------------------------------*/
#endif
