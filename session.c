/*----------------------------------------------------------------------------*/
/*  session.c                                                                 */
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
#include "session.h"
#include "property.h"
#include "hotkey.h"
/*----------------------------------------------------------------------------*/
void VKSigAlarm()
{
	vk_timeout = True;
}
/*----------------------------------------------------------------------------*/
void VKSystemInit()
{
	if( fork()>0 ) exit(0);
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
//	signal(SIGTERM, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGALRM, VKSigAlarm);

	if( vk_charset<0 )
		vk_charset = VKC_VIQR;
}
/*----------------------------------------------------------------------------*/
XErrorHandler old_error_handler;
XIOErrorHandler old_io_error_handler;
/*----------------------------------------------------------------------------*/
int VKIOErrorHandler(Display *display)
{
	extern void VKSaveConfig();

	VKSaveConfig();
	return old_io_error_handler(display);
}
/*----------------------------------------------------------------------------*/
int VKErrorHandler(Display *display, XErrorEvent *event)
{
	if( event->error_code==BadWindow ||
		event->error_code==BadDrawable ||
		event->error_code==BadAccess) return(-1);
	return old_error_handler(display, event);
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
	visckey_atom = XInternAtom(display, PROGRAM_NAME, 0);
	main_window = XGetSelectionOwner(display, visckey_atom);
}
/*----------------------------------------------------------------------------*/
void VKStartXSession()
{
	if( !(display = XOpenDisplay(NULL)) ) {
		puts("\nxvnkb: Can't open display!\n");
		exit(0);
	}
	VKInitResource();
	if( main_window!=None ) {
		puts("\n"PROGRAM_NAME" already activated.\n");
		exit(1);
	}
	old_error_handler = XSetErrorHandler(VKErrorHandler);
	old_io_error_handler = XSetIOErrorHandler(VKIOErrorHandler);
	VKAtomInit(display);
	VKChangeCharset(vk_charset);
	VKChangeMethod();
	VKChangeUsing();
#ifdef VK_CHECK_SPELLING
	VKSetSpelling(vk_spelling);
#endif
	if( !vk_hotkey )
		vk_hotkey = strdup(VK_HOTKEY_STRING);
	else {
		int state;
		KeySym sym;
		char *s = strdup(vk_hotkey);
		VKParseHotkey(s, &state, &sym);
		free(s);

		if( state!=0 && sym!=0 )
			VKSetHotkeyProperty(state, sym);
		else {
			free(vk_hotkey);
			vk_hotkey = strdup(VK_HOTKEY_STRING);
			VKSetHotkeyProperty(VK_HOTKEY_STATE, VK_HOTKEY_CODE);
		}
	}
}
/*----------------------------------------------------------------------------*/
void VKStopXSession()
{
	VKResetMode();
	XSync(display, False);
	XSetIOErrorHandler(old_io_error_handler);
	XSetErrorHandler(old_error_handler);
	XCloseDisplay(display);
}
/*----------------------------------------------------------------------------*/
