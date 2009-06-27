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
#include "mainwin.h"
#include "systray.h"
#include "menu.h"
/*----------------------------------------------------------------------------*/
#ifdef VK_CHECK_SPELLING
#define DOCK_MSG_IDX	3
#else
#define DOCK_MSG_IDX	2
#endif
/*----------------------------------------------------------------------------*/
typedef struct vk_menu_item {
	int x, y;
	char *name;
	int type;
	int *vptr;
	int value;
	int length;
	int width;
	struct vk_menu_item *next;
	struct vk_menu *menu;
} vk_menu_item;
/*----------------------------------------------------------------------------*/
typedef struct vk_menu {
	int x, y;
	int w, h;
	int tx, ty;
	char *name;
	int sidex;
	vk_menu_item *sitem;
	vk_menu_item *items;

	Window win;
	GC gc;
} vk_menu;
/*----------------------------------------------------------------------------*/
#define MENU_PADDING	4
/*----------------------------------------------------------------------------*/
static char *vk_dock_message[][2] = {
	{"Docking to systray", "Undocking"},
	{"Đặt vào khay", "Gỡ khỏi khay"}
};
/*----------------------------------------------------------------------------*/
vk_menu_item vk_menu_data[][25] =
{
	{
	{ 0, 0, "About",				-2 },
	{ 0, 0, "Miscellaneous",		 0 },
#ifdef VK_CHECK_SPELLING
	{ 0, 0, "Check spelling",		 7, &vk_spelling, 1 },
#endif
	{ 0, 0, NULL,					 8, NULL },
	{ 0, 0, "Set hotkey",			 5, NULL },
	{ 0, 0, "Set interface font",	 6, NULL },
	{ 0, 0, "Input method",			 0 },
	{ 0, 0, "Off",					 1, &vk_method, VKM_OFF },
	{ 0, 0, "Vni",					 1, &vk_method, VKM_VNI },
	{ 0, 0, "Telex",				 1, &vk_method, VKM_TELEX },
	{ 0, 0, "Viqr",					 1, &vk_method, VKM_VIQR },
	{ 0, 0, "Charset",				 0 },
	{ 0, 0, "Unicode",				 3, &vk_charset, VKC_UTF8 },
	{ 0, 0, "Tcvn3",				 3, &vk_charset, VKC_TCVN },
	{ 0, 0, "Vni",					 3, &vk_charset, VKC_VNI },
	{ 0, 0, "Viqr",					 3, &vk_charset, VKC_VIQR },
	{ 0, 0, "Viscii",				 3, &vk_charset, VKC_VISCII },
	{ 0, 0, "Vps",					 3, &vk_charset, VKC_VPS },
	{ 0, 0, "Interface",			 0 },
	{ 0, 0, "English",				 4, &vk_interface, VK_ENGLISH },
	{ 0, 0, "Vietnamese",			 4, &vk_interface, VK_VIETNAMESE },
	{ 0, 0, "Exit",					-1 },
	{ 0, 0, NULL,					 0 }
	},
	{
	{ 0, 0, "Thông tin",			-2 },
	{ 0, 0, "Linh tinh",			 0 },
#ifdef VK_CHECK_SPELLING
	{ 0, 0, "Kiểm tra từ",			 7, &vk_spelling, 1 },
#endif
	{ 0, 0, NULL,					 8, NULL },
	{ 0, 0, "Chọn phím bật/tắt",	 5, NULL },
	{ 0, 0, "Chọn font giao diện",	 6, NULL },
	{ 0, 0, "Kiểu gõ",				 0 },
	{ 0, 0, "Tắt",					 1, &vk_method, VKM_OFF },
	{ 0, 0, "Vni",					 1, &vk_method, VKM_VNI },
	{ 0, 0, "Telex",				 1, &vk_method, VKM_TELEX },
	{ 0, 0, "Viqr",					 1, &vk_method, VKM_VIQR },
	{ 0, 0, "Bảng mã",				 0 },
	{ 0, 0, "Unicode",				 3, &vk_charset, VKC_UTF8 },
	{ 0, 0, "Tcvn3",				 3, &vk_charset, VKC_TCVN },
	{ 0, 0, "Vni",					 3, &vk_charset, VKC_VNI },
	{ 0, 0, "Viqr",					 3, &vk_charset, VKC_VIQR },
	{ 0, 0, "Viscii",				 3, &vk_charset, VKC_VISCII },
	{ 0, 0, "Vps",					 3, &vk_charset, VKC_VPS },
	{ 0, 0, "Giao diện",			 0 },
	{ 0, 0, "Tiếng Anh",			 4, &vk_interface, VK_ENGLISH },
	{ 0, 0, "Tiếng Việt",			 4, &vk_interface, VK_VIETNAMESE },
	{ 0, 0, "Thoát",				-1 },
	{ 0, 0, NULL,					 0 }
	}
};
/*----------------------------------------------------------------------------*/
vk_menu menu = {
	0, 0, 0, 0, 0, 0,
	"xvnkb  "VERSION,
	0, NULL, NULL,
	0, 0
};
/*----------------------------------------------------------------------------*/
extern void VKDrawIcon();
extern void VKIconLoadInterface();
extern void VKCreateFlash();
extern void VKDestroyFlash();
extern void VKShowHotkeyWindow();
extern void VKDrawHotkeyWindow();
/*----------------------------------------------------------------------------*/
void MenuProcess(XEvent *event, void *data);
/*----------------------------------------------------------------------------*/
void CreateMenuWindow(vk_menu *m, int w, int h)
{
	m->w = w + 36;
	m->h = h * (vk_text_height + 4) + MENU_PADDING;
	m->tx = 12;
	m->ty = vk_text_ascent + 4;
	m->win = XCreateWindow(display, root,
					m->x, m->y, m->w, m->h, 0,
					DefaultDepth(display, screen), InputOutput, visual,
					vk_attribmask, &vk_attrib);
	XSelectInput(display, m->win, MAIN_EVENT_MASKS);

	m->gc = XCreateGC(display, m->win, 0, 0);
	XDefineCursor(display, m->win, vk_hand);
#ifndef USE_XFT
	XSetFont(display, m->gc, vk_font->fid);
#endif
	VKRegisterEvent(m->win, MenuProcess, m);
}
/*----------------------------------------------------------------------------*/
void CalculateItemWidth(vk_menu_item *current, vk_menu_item *item)
{
	char *s = item->name;
#ifdef USE_XFT
	XGlyphInfo fi;
	XftTextExtentsUtf8(display, vk_font, (uchar *)s, item->length = strlen(s), &fi);
#else
	XRectangle fi;
	XmbTextExtents(vk_fontset, s, item->length = strlen(s), 0, &fi);
#endif
	item->width = fi.width;
	if( current ) current->next = (struct vk_menu_item *)item;
}
/*----------------------------------------------------------------------------*/
void CalculateItemPosition(vk_menu *m)
{
	int h = m->ty + vk_text_height + 4;
	vk_menu_item *item = m->items;
	while( item && item->name ) {
		item->x = m->tx;
		item->y = h;
		item = (vk_menu_item *)item->next;
		h += (vk_text_height + 4);
	}
}
/*----------------------------------------------------------------------------*/
vk_menu_item *CreateSubMenu(vk_menu_item *item, vk_menu_item *child)
{
	int w, h;
	vk_menu_item *citem = NULL;
	vk_menu *m = item->menu = (vk_menu *)calloc(1, sizeof(vk_menu));

	CalculateItemWidth(citem, item);
	h = 1; w = item->width;
	m->name = item->name;
	m->items = child;
	while( child && child->type>0 ) {
		CalculateItemWidth(citem, child);
		if( w<child->width )
			w = child->width;
		citem = child;
		child++;
		h++;
	}
	citem->next = NULL;
	CreateMenuWindow(m, w, h);
	CalculateItemPosition(m);

	return child;
}
/*----------------------------------------------------------------------------*/
void VKCreateMenuWindow()
{
	int h = 1, w;
	char *s = menu.name;
	vk_menu_item *citem = NULL;
	vk_menu_item *item = vk_menu_data[vk_interface];
#ifdef USE_XFT
	XGlyphInfo fi;
	XftTextExtentsUtf8(display, vk_font, (uchar *)s, strlen(s), &fi);
#else
	XRectangle fi;
	XmbTextExtents(vk_fontset, s, strlen(s), 0, &fi);
#endif
	w = fi.width;

	VKUpdateDockingMessage();
	while( item && item->name ) {
		switch( item->type ) {
			case 0:
				if( !citem )
					menu.items = citem = item;
				else {
					citem->next = (struct vk_menu_item *)item;
					citem = item;
				}

				item = CreateSubMenu(item, &item[1]);
				if( w<citem->width ) w = citem->width;
				break;
			default:
				CalculateItemWidth(citem, item);
				if( w<item->width )	w = item->width;
				if( !citem ) menu.items = item;
				citem = item;
				item++;
				break;
		}
		h++;
	}
	citem->next = NULL;
	CreateMenuWindow(&menu, w, h);
	CalculateItemPosition(&menu);
}
/*----------------------------------------------------------------------------*/
void VKDestroyMenuWindow()
{
	vk_menu_item *item = menu.items;
	while( item ) {
		vk_menu_item *mi = item;
		item = item->next;
		if( mi->menu ) {
			VKUnregisterEvent(mi->menu->win);
			XFreeGC(display, mi->menu->gc);
			XDestroyWindow(display, mi->menu->win);
		}
	}
	VKUnregisterEvent(menu.win);
	XFreeGC(display, menu.gc);
	XDestroyWindow(display, menu.win);
}
/*----------------------------------------------------------------------------*/
void VKHideMenu()
{
	if( menu.sidex && menu.sitem->type==0 )
		XUnmapWindow(display, menu.sitem->menu->win);
	XUnmapWindow(display, menu.win);
	vk_menu_on = False;
}
/*----------------------------------------------------------------------------*/
void DrawMenu(vk_menu *m)
{
	vk_menu_item *item = m->items;
#ifdef USE_XFT
	XftDraw *draw;
	draw = XftDrawCreate(display, m->win, visual, colormap);
#endif
	XClearWindow(display, m->win);
	VKSetColor(display, m->gc, clBackground);
	XFillRectangle(display, m->win, m->gc, 0, 0, m->w, m->h);
	VKSetColor(display, m->gc, clMenuBar);
	XDrawRectangle(display, m->win, m->gc, 1, 1, m->w-3, m->h-3);
	XFillRectangle(display, m->win, m->gc, 1, 1, m->w-3, vk_text_height + 4);
#ifdef USE_XFT
	XftDrawStringUtf8(draw, &clBlack, vk_font, m->tx+1, m->ty+1,
							(XftChar8*)m->name, strlen(m->name));
	XftDrawStringUtf8(draw, &clWhite, vk_font, m->tx, m->ty,
							(XftChar8*)m->name, strlen(m->name));
#else
	VKSetColor(display, m->gc, clBlack);
	XmbDrawString(display, m->win, vk_fontset, m->gc, m->tx+1, m->ty+1,
							m->name, strlen(m->name));
	VKSetColor(display, m->gc, clWhite);
	XmbDrawString(display, m->win, vk_fontset, m->gc, m->tx, m->ty,
							m->name, strlen(m->name));
#endif
	while( item ) {
	#ifdef USE_XFT
		XftColor clItem =
	#else
		ulong clItem =
	#endif
			item->type > 0 && item->vptr ?
			(*item->vptr==item->value ? clText : clGray) :
			clBlack;

	#ifdef USE_XFT
		XftDrawStringUtf8(draw, &clItem, vk_font, item->x, item->y,
								(XftChar8*)item->name, item->length);
	#else
		VKSetColor(display, m->gc, clItem);
		XmbDrawString(display, m->win, vk_fontset, m->gc, item->x, item->y,
								item->name, item->length);
	#endif
		if( item->type==0 ) {
			int x = m->w - 15;
			int y = item->y - vk_text_height/2 + 4;
			VKSetColor(display, m->gc, clBlack);
			XDrawLine(display, m->win, m->gc, x, y-1, x+1, y-1);
			XDrawLine(display, m->win, m->gc, x, y, x+3, y);
			XDrawLine(display, m->win, m->gc, x, y+1, x+1, y+1);
		}
		item = (vk_menu_item *)item->next;
	}
#ifdef USE_XFT
	XftDrawDestroy(draw);
#endif
}
/*----------------------------------------------------------------------------*/
void ShowMenu(vk_menu *p, vk_menu *m)
{
	int px, py;
	
	if( p ) {
		px = p->x + p->w;
		py = p->y + (p->sidex - 1) * (vk_text_height + 4) + 2;
	}
	else {
		px = vk_x;
		py = vk_y;
	}

	if( px+m->w > screen_width )
		m->x = (p ? p->x : screen_width) - m->w;
	else
		m->x = px;

	if( py+m->h > screen_height )
		m->y = (p ? 2*vk_text_height+MENU_PADDING+4 : 0) + py - m->h;
	else
		m->y = p ? py-2 : py + vk_icon_height;

	XMoveWindow(display, m->win, m->x, m->y);
	XMapRaised(display, m->win);

	vk_mouse_clicked = False;
	vk_menu_on = True;
}
/*----------------------------------------------------------------------------*/
void VKShowMenu()
{
	ShowMenu(NULL, &menu);
}
/*----------------------------------------------------------------------------*/
void MenuMousePress(vk_menu *m, XEvent *event)
{
	vk_menu_item *item = m->sitem;

	if( m->sidex )
	switch( item->type ) {
		case -1:
			vk_done = True;
			break;
		case -2:
			VKShowFlash();
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
				VKDrawHotkeyWindow();
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
	#ifdef VK_CHECK_SPELLING
		case 7:
			vk_spelling = (vk_spelling + 1) & 1;
			VKSetSpelling(vk_spelling);
			break;
	#endif
		case 8:
			if( vk_docking != VKD_ON )
				VKDockMainWindow();
			else
				VKUndockMainWindow();
			break;
	}
	VKDrawIcon();
	VKHideMenu();
}
/*----------------------------------------------------------------------------*/
void MenuMouseMove(vk_menu *m, XEvent *event)
{
	int idx = (event->xbutton.y - MENU_PADDING) / (vk_text_height + 4),
		c = m->sidex, n;

	if( c!=idx ) {
		if( c ) {
			VKSetColor(display, m->gc, clWhite);
			XDrawRectangle(display, m->win, m->gc,
							4, c*(vk_text_height+4)+2,
							m->w-9, vk_text_height+2);
			if( m->sitem->type==0 )
				XUnmapWindow(display, m->sitem->menu->win);
		}
		m->sidex = idx;
		if( idx ) {
			vk_menu_item *mi = m->items;
			VKSetColor(display, m->gc, clBlack);
			XDrawRectangle(display, m->win, m->gc,
							4, idx*(vk_text_height+4)+2,
							m->w-9, vk_text_height+2);
			for( n=1; n<idx && mi; n++ )
				mi = mi->next;
			if( mi ) {
				m->sitem = mi;
				if( mi->type==0 )
					ShowMenu(m, mi->menu);
			}
		}
	}
}
/*----------------------------------------------------------------------------*/
void MenuProcess(XEvent *event, void *data)
{
	vk_menu *m = (vk_menu *)data;
	switch( event->type ) {
		case Expose:
		case GraphicsExpose:
			DrawMenu(m);
			break;
		case ButtonPress:
			MenuMousePress(m, event);
			break;
		case MotionNotify:
			MenuMouseMove(m, event);
			break;
	}
}
/*----------------------------------------------------------------------------*/
void VKUpdateDockingMessage()
{
	vk_menu_item *item = &vk_menu_data[vk_interface][DOCK_MSG_IDX];
	item->name = vk_dock_message[vk_interface][vk_docking == VKD_ON];
	item->length = strlen(item->name);
}
/*----------------------------------------------------------------------------*/
