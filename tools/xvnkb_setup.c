/*----------------------------------------------------------------------------*/
/*  xvnkb_setup.c                                                             */
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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
/*----------------------------------------------------------------------------*/
#include "data.h"
#include "event.h"
#include "button.h"
#include "xresource.h"
#include "msgbox.h"
/*----------------------------------------------------------------------------*/
#define TESTING
/*----------------------------------------------------------------------------*/
#define	RADIOBUTTON		0
#define CHECKBUTTON		1
/*----------------------------------------------------------------------------*/
#define SETUP_WIDTH		400
#define SETUP_HEIGHT	360
/*----------------------------------------------------------------------------*/
typedef struct {
	char type;
	char *text;
	char checked;
	char enabled;

	int x, y;
	int w, h;
	Window win;
	GC gc;
} VKStatusButton;
/*----------------------------------------------------------------------------*/
typedef struct {
	char *lang;
	char *location;
	char missing;
	VKStatusButton button;
} VKLocaleInfo;
/*----------------------------------------------------------------------------*/
char localedef[256];
VKLocaleInfo locale[2] = {
	{0, "/usr/lib/locale", 1, {CHECKBUTTON, 0, 1, 0}},
	{0, "/usr/share/locale", 1, {CHECKBUTTON, 0, 1, 0}},
};
/*----------------------------------------------------------------------------*/
VKStatusButton lang[4] = {
	{ RADIOBUTTON, "UTF-8", 0, 1, 0, 0, 1, 1, 0, 0 },
	{ RADIOBUTTON, "", 0, 1, 0, 0, 1, 1, 0, 0 },
	{ RADIOBUTTON, "vi_VN.UTF-8", 0, 1, 0, 0, 1, 1, 0, 0 },
	{ RADIOBUTTON, "Keep current setting", 1, 1, 0, 0, 1, 1, 0, 0 }
};
VKStatusButton *slang = &lang[3];
/*----------------------------------------------------------------------------*/
VKButtonControl ok;
/*----------------------------------------------------------------------------*/
XErrorHandler old_error_handler;
Atom close_request;
Cursor busy_cursor;
/*----------------------------------------------------------------------------*/
int VKErrorHandler(Display *display, XErrorEvent *event)
{
	if( event->error_code==BadWindow ||
		event->error_code==BadDrawable ||
		event->error_code==BadAccess) return(-1);
	return old_error_handler(display, event);
}
/*----------------------------------------------------------------------------*/
void VKSystemInit()
{
#ifndef TESTING
	int i;

	if( fork()>0 ) exit(0);

	setpgrp();
	if( (i = open("/dev/tty", O_RDWR)) > 0) {
		ioctl(i, TIOCNOTTY, 0);
		close(i);
	}
#endif
#if 0
	signal(SIGFPE, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGILL, SIG_IGN);
#endif
	signal(SIGSYS, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTRAP, SIG_IGN);
	signal(SIGIOT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);

#ifndef TESTING
	if( fork()>0 ) exit(0);
	for( i=0; i<256; i++ ) close(i);
#endif
}
/*----------------------------------------------------------------------------*/
void VKInitResource()
{
	screen = DefaultScreen(display);
	screen_width = DisplayWidth(display, screen);
	screen_height = DisplayHeight(display, screen);
	colormap = DefaultColormap(display, screen);
	visual = DefaultVisual(display, screen);
	root = RootWindow(display, screen);
	old_error_handler = XSetErrorHandler(VKErrorHandler);
	vk_font_name = VK_FONT_SMALL;
}
/*----------------------------------------------------------------------------*/
void VKStartSession()
{
	if( !(display = XOpenDisplay(NULL)) ) {
		int i, m[] = {O_RDONLY, O_WRONLY, O_WRONLY};
		for( i=0; i<3; i++ ) {
			close(i);
			open("/dev/console", m[i]);
		}
		execlp("/bin/sh", "/bin/sh", "/usr/local/bin/xvnkb_setup.sh", NULL);
		fprintf(stderr, "Error: Cannot load /usr/local/bin/xvnkb_setup.sh\n");
		return;
	}
	VKInitResource();
	VKLoadXResource();
	busy_cursor = XCreateFontCursor(display, XC_watch);
}
/*----------------------------------------------------------------------------*/
void VKStopSession()
{
	if( !display ) return;

	VKFreeXResource();
	XSync(display, False);
	XSetErrorHandler(old_error_handler);
	XCloseDisplay(display);
}
/*----------------------------------------------------------------------------*/
void VKCheckLocaledef()
{
	static char *paths[] = {
		"/bin", "/sbin", "/usr/bin", "/usr/sbin",
		"/usr/local/bin", "/usr/local/sbin",
		0
	};

	int i;
	for( i=0; paths[i]; i++ ) {
		FILE *fp;

		sprintf(localedef, "%s/localedef", paths[i]);
		fp = fopen(localedef, "r");
		if( fp ) {
			fclose(fp);
			break;
		}
	}

	if( !paths[i] ) {
		*localedef = 0;
		return;
	}
}
/*----------------------------------------------------------------------------*/
void VKCreateLocale()
{
	//FILE *fp;
	char cmd[1024];

	VKCheckLocaledef();
	if( !*localedef ) {
		// display error message here
		return;
	}

	if( locale[0].missing && locale[0].button.checked ) {
		if( !locale[1].missing )
			sprintf(cmd, "ln -sf %s/%s %s", locale[1].location, slang->text,
											locale[0].location);
		else
			sprintf(cmd, "%s -ci %s -f UTF-8 %s/%s",
				localedef, locale[0].lang, locale[0].location, slang->text);
		locale[0].missing = 0;
		system(cmd);
		printf("%s\n", cmd);
	}

	if( locale[1].missing && locale[1].button.checked ) {
		if( !locale[0].missing )
			sprintf(cmd, "ln -sf %s/%s %s", locale[0].location, slang->text,
											locale[1].location);
		else
			sprintf(cmd, "%s -ci %s -f UTF-8 %s/%s",
				localedef, locale[1].lang, locale[1].location, slang->text);
		system(cmd);
		printf("%s\n", cmd);
	}
}
/*----------------------------------------------------------------------------*/
void VKCheckLocale()
{
	int i;
	FILE *fp;
	char *p, *s;
	void VKDrawStatusButton(VKStatusButton *b);
	char lc[1024];

#ifdef USE_XFT
	XftDraw *draw;
#endif

	/* Do not modify */
	if( slang==&lang[3] ) {
		locale[0].button.checked = 0;
		locale[1].button.checked = 0;
		locale[0].button.enabled = 0;
		locale[1].button.enabled = 0;

		VKSetColor(display, main_gc, clWhite);
		XFillRectangle(display, main_window, main_gc,
							20, locale[0].button.y,
							SETUP_WIDTH-32, locale[0].button.h*2+8);
	#ifdef USE_XFT
		draw = XftDrawCreate(display, main_window, visual, colormap);
		for( i=0; i<2; i++ ) {
			sprintf(lc, "[%s]", locale[i].location);
			XftDrawStringUtf8(draw, &clGray, vk_font,
							locale[i].button.h+24, locale[i].button.y+vk_text_ascent+4,
							(XftChar8*)lc, strlen(lc));
		}
		XftDrawDestroy(draw);
	#else
		XSetForeground(display, main_gc, clGray);
		for( i=0; i<2; i++ ) {
			sprintf(lc, "[%s]", locale[i].location);
			XmbDrawString(display, main_window, vk_fontset, main_gc,
							locale[0].button.h+24, locale[0].button.y+vk_text_ascent+4,
							lc, strlen(lc));
		}
	#endif
		VKDrawStatusButton(&locale[0].button);
		VKDrawStatusButton(&locale[1].button);
		return;
	}

	s = strdup(slang->text);
	p = strchr(s, '.');
	if( p )
		*(p+1) = 0;
	else
		*s = 0;

	for( i=0; i<2; i++ ) {
		sprintf(lc, "%s/%sUTF-8/LC_IDENTIFICATION", locale[i].location, s);
		fp = fopen(lc, "r");
		if( fp ) {
			locale[i].missing = 0;
			locale[i].button.checked = 0;
			fclose(fp);
		}
		else {
			locale[i].missing = 1;
			locale[i].button.checked = 1;
		}
		// save lang
		if( locale[i].lang )
			free(locale[i].lang);
		if( *s )
			locale[i].lang = strdup(s);
		else
			locale[i].lang = strdup("en_US");
		p = strchr(locale[i].lang, '.');
		if( p ) *p = 0;
		// display location
		sprintf(lc, "[%s/%sUTF-8]", locale[i].location, s);
		VKSetColor(display, main_gc, clWhite);
		XFillRectangle(display, main_window, main_gc,
							20, locale[i].button.y,
							SETUP_WIDTH-32, locale[i].button.h);
	#ifdef USE_XFT
		draw = XftDrawCreate(display, main_window, visual, colormap);
		XftDrawStringUtf8(draw, &clText, vk_font,
							locale[i].button.h+24, locale[i].button.y+vk_text_ascent+4,
							(XftChar8*)lc, strlen(lc));
		XftDrawDestroy(draw);
	#else
		XSetForeground(display, main_gc, clText);
		XmbDrawString(display, main_window, vk_fontset, main_gc,
							locale[i].button.h+24, locale[i].button.y+vk_text_ascent+4,
							lc, strlen(lc));
	#endif
		locale[i].button.enabled = 1;
		VKDrawStatusButton(&locale[i].button);
	}
	free(s);
}
/*----------------------------------------------------------------------------*/
void VKSetupLang()
{
	char *s = getenv("LANG");

	if( !s )
		s = "en_US";
	else {
		char *p = strchr(s, '.');
		if( p ) *p = 0;
		if( !strcmp(s, "UTF-8") || !strcmp(s, "vi_VN") )
			s = "en_US";
	}
	lang[1].text = malloc(strlen(s) + 7);
	sprintf(lang[1].text, "%s.UTF-8", s);
}
/*----------------------------------------------------------------------------*/
void VKProcessEvent()
{
	void VKDrawMain();

	while( XPending(display) ) {
		XEvent event;
		XNextEvent(display, &event);
		if( event.xany.window!=main_window )
			VKDispatchEvent(&event);
		else
		switch( event.type ) {
			case Expose:
			case GraphicsExpose:
				VKDrawMain();
				break;
			case ClientMessage:
				if( event.xclient.data.l[0] == close_request ) {
					XDestroyWindow(display, main_window);
					vk_done = 1;
				}
		}
	}
}
/*----------------------------------------------------------------------------*/
void VKSetup()
{
	static int setting = 0;
	void VKDrawStatusButton(VKStatusButton *b);
	int i;

	if( setting ) return;

	setting = 1;
	for( i=0; i<4; i++ ) {
		lang[i].enabled = 0;
		VKDrawStatusButton(&lang[i]);
		XDefineCursor(display, lang[i].win, busy_cursor);
	}
	for( i=0; i<2; i++ ) {
		locale[i].button.enabled = 0;
		VKDrawStatusButton(&locale[i].button);
		XDefineCursor(display, locale[i].button.win, busy_cursor);
	}
	XDefineCursor(display, main_window, busy_cursor);

	VKShowMessage("Copy X init resource script for xvnkb...");
	i = 0;
	while( i < 100000 ) {
		VKProcessEvent();
		usleep(10);
		i++;
	}
	//system("/bin/cp /usr/local/share/xvnkb/xvnkb.sys.sh /etc/X11/xinit/xinitrc.d/xvnkb.sh");
	VKShowMessage("Check and creacte locale...");
	i = 0;
	while( i < 100000 ) {
		VKProcessEvent();
		usleep(10);
		i++;
	}
	//VKCreateLocale();
	VKShowMessage("Check and set i18n information...");
	i = 0;
	while( i < 100000 ) {
		VKProcessEvent();
		usleep(10);
		i++;
	}
	//VKCheckI18n();

	vk_done = 1;
	setting = 0;
}
/*----------------------------------------------------------------------------*/
void VKDrawStatusButton(VKStatusButton *b)
{
#ifdef USE_XFT
	XftColor color = b->enabled ? clText : clGray;
#else
	ulong color = b->enabled ? clText : clGray;
#endif
	XClearWindow(display, b->win);
	VKSetColor(display, b->gc, color);
	if( b->type == RADIOBUTTON ) {
		XDrawArc(display, b->win, b->gc, 4, 4, b->h-9, b->h-9, 0, 360*64);
		if( b->checked )
			XFillArc(display, b->win, b->gc, 6, 6, b->h-13, b->h-13, 0, 360*64);
	}
	else {
		XDrawRectangle(display, b->win, b->gc, 4, 4, b->h-9, b->h-9);
		if( b->checked ) {
			XDrawLine(display, b->win, b->gc, 4, 4, b->h-6, b->h-6);
			XDrawLine(display, b->win, b->gc, 4, b->h-5, b->h-5, 4);
		}
	}

	if( b->text ) {
		int x = b->h;
		int y = vk_text_ascent + 6;
		int l = strlen(b->text);
	#ifdef USE_XFT
		XftDraw *draw;
		draw = XftDrawCreate(display, b->win, visual, colormap);
		XftDrawStringUtf8(draw, &color, vk_font, x, y, (XftChar8*)b->text, l);
		XftDrawDestroy(draw);
	#else
		XSetForeground(display, b->gc, color);
		XmbDrawString(display, b->win, vk_fontset, b->gc, x, y, b->text, l);
	#endif
	}
}
/*----------------------------------------------------------------------------*/
void VKProcessButtonEvent(XEvent *event, void *data)
{
	VKStatusButton *b = (VKStatusButton *)data;
	switch( event->type ) {
		case Expose:
		case GraphicsExpose:
			VKDrawStatusButton(b);
			break;
		case ButtonPress:
			if( !b->enabled ) break;
			if( b->type == RADIOBUTTON ) {
				slang->checked = 0;
				VKDrawStatusButton(slang);
				(slang = b)->checked = 1;
				VKDrawStatusButton(slang);
				VKCheckLocale();
			}
			else {
				b->checked = !b->checked;
				VKDrawStatusButton(b);
			}
	}
}
/*----------------------------------------------------------------------------*/
void VKCreateStatusButton(int x, int y, VKStatusButton *b)
{
	b->x = x;
	b->y = y;
	if( !b->text || !*b->text )
		b->w = 32;
	else {
	#ifdef USE_XFT
		XGlyphInfo fi;
		XftTextExtentsUtf8(display, vk_font, (uchar *)b->text, strlen(b->text), &fi);
		b->w = fi.width + 32;
	#else
		b->w = XTextWidth(vk_font, b->text, strlen(b->text)) + 32;
	#endif
	}
	b->h = 8 + vk_text_height;

#ifndef USE_XFT
	b->win = XCreateSimpleWindow(display, main_window, x, y, b->w, b->h,
									0, clBlack, clWhite);
#else
	b->win = XCreateSimpleWindow(display, main_window, x, y, b->w, b->h,
									0, clBlack.pixel, clWhite.pixel);
#endif
	b->gc = XCreateGC(display, b->win, 0, 0);

	XSelectInput(display, b->win, ExposureMask|ButtonPressMask);
	XDefineCursor(display, b->win, vk_hand);
#ifndef USE_XFT
	XSetFont(display, b->gc, vk_font->fid);
#endif
	XMapWindow(display, b->win);

	VKRegisterEvent(b->win, VKProcessButtonEvent, b);
}
/*----------------------------------------------------------------------------*/
void VKProcessMessage(XEvent *event, void *data)
{
	switch( event->type ) {
		case Expose:
		case GraphicsExpose:
			VKShowMessage(NULL);
			break;
	}
}
/*----------------------------------------------------------------------------*/
void VKCreateMainWindow()
{
	int i;
	XWMHints  hints;
	XSizeHints shints;

#ifndef USE_XFT
	main_window = XCreateSimpleWindow(display, root, 0, 0,
										SETUP_WIDTH, SETUP_HEIGHT,
										1, clBlack, clWhite);
#else
	main_window = XCreateSimpleWindow(display, root, 0, 0,
										SETUP_WIDTH, SETUP_HEIGHT,
										1, clBlack.pixel, clWhite.pixel);
#endif
	XStoreName(display, main_window, "xvnkb "VERSION" setup");
	hints.flags = InputHint;
	hints.input = True;
	XSetWMHints(display, main_window, &hints);
	shints.min_width = shints.max_width = SETUP_WIDTH;
	shints.min_height = shints.max_height = SETUP_HEIGHT;
	shints.flags = PMinSize | PMaxSize;
	XSetNormalHints(display, main_window, &shints);
	close_request = XInternAtom(display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(display, main_window, &close_request, 1);
	XSelectInput(display, main_window, ExposureMask);

	main_gc = XCreateGC(display, main_window, 0, 0);
	XDefineCursor(display, main_window, vk_cursor);
#ifndef USE_XFT
	XSetFont(display, main_gc, vk_font->fid);
#endif
	XMapWindow(display, main_window);

	for( i=0; i<4; i++ )
		VKCreateStatusButton(20, 40+i*(vk_text_height+8), &lang[i]);

	i = lang[3].y+lang[3].h;
	VKCreateStatusButton(20, i+60, &locale[0].button);
	VKCreateStatusButton(20, i+100, &locale[1].button);

	ok.x = (SETUP_WIDTH - 120)/2;
	ok.y = i+160;
	ok.h = vk_text_height + 8;
	ok.w = 120;
	ok.text = "OK";
	ok.action = VKSetup;
	VKCreateButton(main_window, &ok);
	VKShowButtons(&ok, 1);
}
/*----------------------------------------------------------------------------*/
void VKDrawMain()
{
	int y;
#ifdef USE_XFT
	XftDraw *draw;
#endif

	XClearWindow(display, main_window);
	VKSetColor(display, main_gc, clBlack);

	y = lang[3].y+lang[3].h;
	// LANG box
	XDrawRectangle(display, main_window, main_gc,
					8, 16, SETUP_WIDTH-16, y);
	// Locale box
	XDrawRectangle(display, main_window, main_gc,
					8, y+vk_text_height+16, SETUP_WIDTH-16, 4*vk_text_height+16);
	VKSetColor(display, main_gc, clWhite);
	XFillRectangle(display, main_window, main_gc,
					32, 8, 100, vk_text_height);
	XFillRectangle(display, main_window, main_gc,
					32, y+vk_text_height+8, 250, vk_text_height);

#ifdef USE_XFT
	draw = XftDrawCreate(display, main_window, visual, colormap);
	XftDrawStringUtf8(draw, &clText, vk_font,
						38, 8+vk_text_ascent, (XftChar8*)"Set LANG", 8);
	XftDrawStringUtf8(draw, &clText, vk_font,
						38, y+vk_text_height+8+vk_text_ascent,
						(XftChar8*)"Create Locale Information", 25);
	XftDrawDestroy(draw);
#else
	XSetForeground(display, main_gc, clText);
	XmbDrawString(display, main_window, vk_fontset, main_gc,
						36, 8+vk_text_ascent, "Set LANG", 8);
	XmbDrawString(display, main_window, vk_fontset, main_gc,
						36, y+vk_text_height+8+vk_text_ascent,
						"Create Locale Information", 25);
#endif
	VKSetColor(display, main_gc, clText);
	XDrawLine(display, main_window, main_gc, 0, y+5*vk_text_height+42,
							SETUP_WIDTH, y+5*vk_text_height+42);
	
	VKCheckLocale();
}
/*----------------------------------------------------------------------------*/
void VKProcessing()
{
	VKSetupLang();
	VKCreateMainWindow();
	while( !vk_done ) {
		XEvent event;
		XNextEvent(display, &event);
		if( event.xany.window!=main_window )
			VKDispatchEvent(&event);
		else
		switch( event.type ) {
			case Expose:
			case GraphicsExpose:
				VKDrawMain();
				break;
			case ClientMessage:
				if( event.xclient.data.l[0] == close_request ) {
					XDestroyWindow(display, main_window);
					vk_done = 1;
				}
		}
	}
}
/*----------------------------------------------------------------------------*/
int main()
{
	VKSystemInit();
	VKStartSession();
	VKProcessing();
	VKStopSession();
	return 0;
}
/*----------------------------------------------------------------------------*/
