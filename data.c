/*----------------------------------------------------------------------------*/
/*  data.c                                                                    */
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
/*----------------------------------------------------------------------------*/
int screen;
int screen_width;
int screen_height;
Visual *visual;
Display *display;
Colormap colormap;
Window root = None;
/*----------------------------------------------------------------------------*/
GC main_gc = None;
GC menu_gc = None;
GC flash_gc = None;
Atom visckey_atom = None;
Window main_window = None;
Window menu_window = None;
Window flash_window = None;
/*----------------------------------------------------------------------------*/
int vk_method;
int vk_charset;
int vk_using;
int vk_spelling = 1;
int vk_interface = 0;
int vk_docking = VKD_OFF;
char *vk_hotkey = NULL;
/*----------------------------------------------------------------------------*/
int vk_done = False;
int vk_x = -1, vk_y = -1;
int vk_timeout = False;
int vk_menu_on = False;
int vk_flash_on = False;
int vk_mouse_clicked = False;
int vk_error_detected = False;
int vk_text_height = 0;
int vk_text_ascent = 0;
char *vk_font_name = NULL;
char *vk_config_file = NULL;
/*----------------------------------------------------------------------------*/
Cursor vk_hand;
Cursor vk_cursor;
#ifdef USE_XFT
XftFont *vk_font;
#else
XFontStruct *vk_font;
XFontSet vk_fontset;
#endif
XSetWindowAttributes vk_attrib;
ulong vk_attribmask = CWOverrideRedirect;
/*----------------------------------------------------------------------------*/
#ifdef USE_XFT
XftColor clBackground, clBorder, clText, clMenuBar;
XftColor clYellow, clRed, clWhite, clBlack, clBlue, clGray;
#else
ulong clBackground, clBorder, clText, clMenuBar;
ulong clYellow, clRed, clWhite, clBlack, clBlue, clGray;
#endif
/*----------------------------------------------------------------------------*/
int vk_icon_width = 0;
int vk_icon_height = 0;
/*----------------------------------------------------------------------------*/
