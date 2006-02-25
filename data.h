/*----------------------------------------------------------------------------*/
/*  data.h                                                                    */
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
#ifndef __DATA_H
#define __DATA_H
/*----------------------------------------------------------------------------*/
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/Xproto.h>
#include <X11/keysym.h>
#include <X11/cursorfont.h>
#ifdef USE_XFT
#include <X11/Xft/Xft.h>
#endif
/*----------------------------------------------------------------------------*/
#include "debug.h"
#include "typedefs.h"
#include "mode.h"
/*----------------------------------------------------------------------------*/
#ifdef USE_XFT
#define VK_FONT_SMALL			"helvetica:size=9:style=bold"
#define VK_FONT_LARGE			"helvetica:size=10:style=bold"
#else
#define VK_FONT_SMALL			"*helvetica-bold-r*-80-*"
#define VK_FONT_LARGE			"*helvetica-bold-r*-100-*"
#endif
#define VK_VN_FONT			"-*-clearlyu-medium-r-normal--*-*-*-*-*-*-iso10646-1"
/*----------------------------------------------------------------------------*/
#define PROGRAM_NAME		"VISCKEY"
/*----------------------------------------------------------------------------*/
#define	MAIN_EVENT_MASKS	ExposureMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask
/*----------------------------------------------------------------------------*/
extern int screen;
extern int screen_width;
extern int screen_height;
extern Visual *visual;
extern Display *display;
extern Colormap colormap;
extern Window root;
/*----------------------------------------------------------------------------*/
extern GC main_gc;
extern GC menu_gc;
extern GC flash_gc;
extern Atom visckey_atom;
extern Window main_window;
extern Window menu_window;
extern Window flash_window;
/*----------------------------------------------------------------------------*/
extern int vk_done;
extern int vk_x, vk_y;
extern int vk_timeout;
extern int vk_menu_on;
extern int vk_flash_on;
extern int vk_mouse_clicked;
extern int vk_text_height;
extern int vk_text_ascent;
extern char *vk_font_name;
extern char *vk_config_file;
/*----------------------------------------------------------------------------*/
extern int vk_method;
extern int vk_charset;
extern int vk_using;
extern int vk_spelling;
extern int vk_interface;
extern int vk_docking;
extern char *vk_hotkey;
/*----------------------------------------------------------------------------*/
extern int vk_icon_width;
extern int vk_icon_height;
/*----------------------------------------------------------------------------*/
extern Cursor vk_hand;
extern Cursor vk_cursor;
#ifdef USE_XFT
extern XftFont *vk_font;
#else
extern XFontStruct *vk_font;
extern XFontSet vk_fontset;
#endif
extern XSetWindowAttributes vk_attrib;
extern ulong vk_attribmask;
/*----------------------------------------------------------------------------*/
#ifdef USE_XFT
extern XftColor clBackground, clBorder, clText, clMenuBar;
extern XftColor clYellow, clRed, clWhite, clBlack, clBlue, clGray;
#else
extern ulong clBackground, clBorder, clText, clMenuBar;
extern ulong clYellow, clRed, clWhite, clBlack, clBlue, clGray;
#endif
/*----------------------------------------------------------------------------*/
#ifdef USE_XFT
	#define VKSetColor(D, G, C)		XSetForeground(D, G, C.pixel)
#else
	#define VKSetColor(D, G, C)		XSetForeground(D, G, C)
#endif
/*----------------------------------------------------------------------------*/
#define VK_ENGLISH		0
#define VK_VIETNAMESE	1
/*----------------------------------------------------------------------------*/
#endif
