/*----------------------------------------------------------------------------*/
/*  menu.c                                                                    */
/*----------------------------------------------------------------------------*/
/*  copyright         : (C) 2002 by Dao Hai Lam                               */
/*                      VISC Software & Security Consultant Company           */
/*                      Hall 3, Quang Trung Software City                     */
/*                      Tan Chanh Hiep Ward, District 12,                     */
/*                      Ho Chi Minh city, VIETNAM                             */
/*  website           : http://www.visc-network.com                           */
/*  email             : lam@visc-network.com                                  */
/*  last modify       : Tue, 13 Aug 2002 03:14:07 +0700                       */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*   This program is free software; you can redistribute it and/or modify     */
/*   it under the terms of the GNU General Public License as published by     */
/*   the Free Software Foundation; either version 2 of the License, or        */
/*   (at your option) any later version.                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "data.h"
#include "flash.h"
#include "event.h"
/*----------------------------------------------------------------------------*/
typedef struct {
	int x, y;
	char *name;
	int type;
	int *vptr;
	int value;
	int length;
	int width;
} vk_menu_item;
/*----------------------------------------------------------------------------*/
vk_menu_item vk_menu_items_info[][20] =
{
	{
	{ 0, 0, "o Input method",		0 },
	{ 0, 0, "Off",					1, &vk_method, VKM_OFF },
	{ 0, 0, "Vni",					1, &vk_method, VKM_VNI },
	{ 0, 0, "Telex",				1, &vk_method, VKM_TELEX },
	{ 0, 0, "Viqr",					1, &vk_method, VKM_VIQR },
	{ 0, 0, "o Charset",			0 },
	{ 0, 0, "Unicode",				3, &vk_charset, VKC_UTF8 },
	{ 0, 0, "Tcvn3",				3, &vk_charset, VKC_TCVN },
	{ 0, 0, "Vni",					3, &vk_charset, VKC_VNI },
	{ 0, 0, "Viqr",					3, &vk_charset, VKC_VIQR },
	{ 0, 0, "Viscii",				3, &vk_charset, VKC_VISCII },
	{ 0, 0, "Vps",					3, &vk_charset, VKC_VPS },
//#ifdef USE_XFT
//	{ 0, 0, "o Interface",			0 },
	{ 0, 0, "o Miscellaneous",		0 },
	{ 0, 0, "English",				4, &vk_interface, VK_ENGLISH },
	{ 0, 0, "Vietnamese",			4, &vk_interface, VK_VIETNAMESE },
	{ 0, 0, "Set hotkey",			5, &vk_interface, VK_VIETNAMESE },
//#endif
	{ 0, 0, "o Exit     |   About",	0 },
	{ 0, 0, NULL,					0 }
	},
//};
/*----------------------------------------------------------------------------*/
//vk_menu_item vk_menu_vitems[] =
{
	{ 0, 0, "o Kiểu gõ",			0 },
	{ 0, 0, "Tắt",					1, &vk_method, VKM_OFF },
	{ 0, 0, "Vni",					1, &vk_method, VKM_VNI },
	{ 0, 0, "Telex",				1, &vk_method, VKM_TELEX },
	{ 0, 0, "Viqr",					1, &vk_method, VKM_VIQR },
	{ 0, 0, "o Bảng mã",			0 },
	{ 0, 0, "Unicode",				3, &vk_charset, VKC_UTF8 },
	{ 0, 0, "Tcvn3",				3, &vk_charset, VKC_TCVN },
	{ 0, 0, "Vni",					3, &vk_charset, VKC_VNI },
	{ 0, 0, "Viqr",					3, &vk_charset, VKC_VIQR },
	{ 0, 0, "Viscii",				3, &vk_charset, VKC_VISCII },
	{ 0, 0, "Vps",					3, &vk_charset, VKC_VPS },
//#ifdef USE_XFT
//	{ 0, 0, "o Giao diện",			0 },
	{ 0, 0, "o Linh tinh",			0 },
	{ 0, 0, "Tiếng Anh",			4, &vk_interface, VK_ENGLISH },
	{ 0, 0, "Tiếng Việt",			4, &vk_interface, VK_VIETNAMESE },
	{ 0, 0, "Chọn phím gõ tắt",		5, &vk_interface, VK_VIETNAMESE },
//#endif
	{ 0, 0, "o Thoát  | Thông tin",	0 },
	{ 0, 0, NULL,					0 }
}};
/*----------------------------------------------------------------------------*/
vk_menu_item *vk_menu_items = vk_menu_items_info[0];//vk_menu_eitems;
/*----------------------------------------------------------------------------*/
int vk_menu_space = 0;
int vk_menu_width = 0;
int vk_menu_height = 0;
/*----------------------------------------------------------------------------*/
int vk_item_space = 0;
int vk_menu_x = 0;
int vk_menu_y = 0;
/*----------------------------------------------------------------------------*/
extern void VKDrawIcon();
extern void VKIconLoadInterface();
extern void VKCreateFlash();
extern void VKDestroyFlash();
extern void VKShowHotkeyWindow();
/*----------------------------------------------------------------------------*/
void VKMenuWindowProcess(XEvent *event);
/*----------------------------------------------------------------------------*/
void VKDrawMenu()
{
	vk_menu_item *item;

#ifdef USE_XFT
	XftColor clItem;
	XftDraw *draw;
	draw = XftDrawCreate(display, menu_window, visual, colormap);
#endif
	XClearWindow(display, menu_window);
	VKSetColor(display, menu_gc, clBackground);
	XFillRectangle(display, menu_window, menu_gc, 0, 0, vk_menu_width, vk_menu_height);
	VKSetColor(display, menu_gc, clMenuBar);
	XDrawRectangle(display, menu_window, menu_gc, 1, 1, vk_menu_width-3, vk_menu_height-3);

	XSetForeground(display, menu_gc, 0);
	for( item=vk_menu_items; item->name; item++ ) {
		switch( item->type ) {
			case 0:
				VKSetColor(display, menu_gc, clMenuBar);
				XFillRectangle(display, menu_window, menu_gc,
										2, item->y-2*vk_menu_space-6,//2*vk_menu_space+2,
										vk_menu_width-4, vk_text_height+8/*+vk_menu_space+4*/);
		#ifdef USE_XFT
				clItem = clWhite;
				break;
			case 1 ... 4:
				clItem = *item->vptr==item->value ? clText : clGray;
				break;
			default:
				clItem = clGray;
				break;
		}
		if( !item->type )
			XftDrawStringUtf8(draw, &clBlack, vk_font, item->x+1, item->y-4,
								(XftChar8*)item->name, strlen(item->name));
		XftDrawStringUtf8(draw, &clItem, vk_font, item->x, item->y-5,
								(XftChar8*)item->name, strlen(item->name));

		#else
				XSetForeground(display, menu_gc, clWhite);
				break;
			case 1 ... 4:
				XSetForeground(display, menu_gc, *item->vptr==item->value ? clText : clGray);
				break;
			default:
				XSetForeground(display, menu_gc, clGray);
		}
		XDrawString(display, menu_window, menu_gc,
					item->x, item->y-5, item->name, strlen(item->name));
		#endif
	}
#ifdef USE_XFT
	XftDrawDestroy(draw);
#endif
}
/*----------------------------------------------------------------------------*/
void VKCreateMenuWindow()
{
	int y;
	char *s;
	vk_menu_item *item;
#ifdef USE_XFT
	XGlyphInfo fi;
//	vk_menu_items = vk_interface==VK_ENGLISH ? vk_menu_eitems : vk_menu_vitems;
	vk_menu_items = vk_menu_items_info[vk_interface];
#endif

	y = vk_menu_width = 0;
	vk_menu_space = vk_text_height/2;
	for( item=vk_menu_items; (s=item->name); item++ ) {
	#ifdef USE_XFT
		int w;
		XftTextExtentsUtf8(display, vk_font, s, item->length = strlen(s), &fi);
		w = item->width = fi.width;
	#else
		int w = item->width = XTextWidth(vk_font, s, item->length = strlen(s));
	#endif
		if( w>vk_menu_width ) vk_menu_width = w;
	}
	vk_menu_width += 2 * vk_menu_space;
	for( item=vk_menu_items; (s=item->name); item++ ) {
		if( !item->type ) {
			if( y>0 ) y += 2;
			item->x = vk_menu_space;
			y += (vk_text_height+8);//vk_menu_space);
		}
		else {
			item->x = vk_menu_width - vk_menu_space - item->width;
			y += (vk_text_height+8);
			//y += (vk_text_height+vk_menu_space+4);
		}
		item->y = y;
	}
	vk_menu_height = y+4;

	menu_window = XCreateWindow(display, root,
					vk_menu_x, vk_menu_y, vk_menu_width, vk_menu_height, 0,
					DefaultDepth(display, screen), InputOutput, visual,
					vk_attribmask, &vk_attrib);
	XSelectInput(display, menu_window, MAIN_EVENT_MASKS);

	menu_gc = XCreateGC(display, menu_window, 0, 0);
	XDefineCursor(display, menu_window, vk_hand);
#ifndef USE_XFT
	XSetFont(display, menu_gc, vk_font->fid);
#endif
	VKRegisterEvent(menu_window, VKMenuWindowProcess);
}
/*----------------------------------------------------------------------------*/
void VKDestroyMenuWindow()
{
	VKUnregisterEvent(menu_window);

	XFreeGC(display, menu_gc);
	XDestroyWindow(display, menu_window);
}
/*----------------------------------------------------------------------------*/
void VKShowMenu()
{
	if( vk_x+vk_menu_width>screen_width )
		vk_menu_x = screen_width - vk_menu_width;
	else
		vk_menu_x = vk_x;
	if( vk_y+vk_menu_height>screen_height )
		vk_menu_y = vk_y - vk_menu_height;
	else
		vk_menu_y = vk_y + vk_icon_height;
	XMoveWindow(display, menu_window, vk_menu_x, vk_menu_y);
	XMapRaised(display, menu_window);
	vk_mouse_clicked = False;
	vk_menu_on = True;
}
/*----------------------------------------------------------------------------*/
void VKHideMenu()
{
	XUnmapWindow(display, menu_window);
	vk_menu_on = False;
}
/*----------------------------------------------------------------------------*/
void VKMenuMousePress(XEvent *event)
{
	int item_space;
	int x = event->xbutton.x;
	int y = event->xbutton.y;
	vk_menu_item *item = vk_menu_items;

	item_space = (vk_text_height+vk_menu_space+2);
	for( ; item->name; item++ )
		if( y >= item->y-item_space && y <= item->y+2 ) break;

	if( item->name )
	switch( item->type ) {
		case 0:
			if( !strncmp(item->name, "o T", 3) ||
				!strncmp(item->name, "o Exit", 6) ) {
				if( x < vk_menu_width/2 )
					vk_done = True;
				else
					VKShowFlash();
			}
			break;
		case 1:
			if( vk_method != item->value ) {
				vk_method = item->value;
				if( vk_method != VKM_OFF ) {
					vk_using = vk_method;
					VKChangeUsing();
				}
				VKChangeMethod();
			}
			break;
		case 3:
			if( vk_charset != item->value )
				VKChangeCharset(vk_charset = item->value);
			break;
		case 4:
			if( vk_interface!=item->value ) {
				vk_interface = item->value;
				VKDestroyMenuWindow();
				VKCreateMenuWindow();
				VKIconLoadInterface();
				VKDestroyFlash();
				VKCreateFlash();
			}
			break;
		case 5:
			VKShowHotkeyWindow();
			break;
	}
	VKDrawIcon();
	VKHideMenu();
}
/*----------------------------------------------------------------------------*/
void VKMenuMouseMove(XEvent *event)
{
	static vk_menu_item *current_item = 0;
	vk_menu_item *item = vk_menu_items;

	int item_space;
	int y = event->xbutton.y;

//	item_space = (vk_text_height+vk_menu_space);
	item_space = vk_text_height + 8;
	for( ; item->name; item++ )
		if( y>=item->y-item_space && y<=item->y+2 ) break;

	if( item->name && item!=current_item ) {
		if( current_item && current_item->type ) {
			VKSetColor(display, menu_gc, clWhite);
			XDrawRectangle(display, menu_window, menu_gc,
									4, current_item->y-item_space+3,
									vk_menu_width-9, item_space-1);
		}
		current_item = item;
		if( item->type ) {
			VKSetColor(display, menu_gc, clBlack);
			XDrawRectangle(display, menu_window, menu_gc,
									4, item->y-item_space+3,
									vk_menu_width-9, item_space-1);
		}
	}
}
/*----------------------------------------------------------------------------*/
void VKMenuWindowProcess(XEvent *event)
{
	switch( event->type ) {
		case Expose:
		case GraphicsExpose:
			VKDrawMenu();
			break;
		case ButtonPress:
			VKMenuMousePress(event);
			break;
		case MotionNotify:
			VKMenuMouseMove(event);
			break;
	}
}
/*----------------------------------------------------------------------------*/
