/*----------------------------------------------------------------------------*/
/*  label.h                                                                   */
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
#ifndef __LABEL_H
#define __LABEL_H
/*----------------------------------------------------------------------------*/
typedef struct {
	int x, y;
	int w, h;
	int tx, ty;
	char *text;
	int l;

	Window win;
	GC gc;
#ifdef USE_XFT
	XftDraw *draw;
#endif
} VKLabel;
/*----------------------------------------------------------------------------*/
void VKSetLabel(VKLabel *l, char *v);
void VKDrawLabel(VKLabel *l);
/*----------------------------------------------------------------------------*/
#endif
