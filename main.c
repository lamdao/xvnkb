/*----------------------------------------------------------------------------*/
/*  main.c                                                                    */
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
#include "xconfig.h"
#include "xresource.h"
#include "flash.h"
#include "session.h"
#include "mainwin.h"
#include "menu.h"
#include "hotkey.h"
#include "property.h"
#include "event.h"
/*----------------------------------------------------------------------------*/
void VKCheckMouseStatus()
{
	static int rx=-1, ry=-1;
	static unsigned int b = 0;
	Window fw = None;
	int rt;

	XGetInputFocus(display, &fw, &rt);
	if( fw!=None ) {
		Window w;
		unsigned int bb = 0;
		int x, y, wx, wy;

		if( XQueryPointer(display, fw, &w, &w, &x, &y, &wx, &wy, &bb) )
		if( bb>255 && (bb!=b || rx!=x || ry!=y) ) {   
			b = bb;
			rx = x;
			ry = y;
			vk_mouse_clicked = True;
		}
	}
}
/*----------------------------------------------------------------------------*/
void VKRootWindowProcess(XEvent *event, void *data)
{
	char *name = XGetAtomName(display, ((XPropertyEvent *)event)->atom);
	if( name!=NULL ) { 
		if( !strcmp(name, VKP_CHARSET) )
			vk_charset = VKGetValue(display, ((XPropertyEvent *)event)->atom);
		else
		if( !strcmp(name, VKP_USING) )
			vk_using = VKGetValue(display, ((XPropertyEvent *)event)->atom);
		else
		if( !strcmp(name, VKP_METHOD) ) {
			extern void VKDrawIcon();
			vk_method = VKGetValue(display, ((XPropertyEvent *)event)->atom);
			VKDrawIcon();

			TRACE("GUI: %s\n", name);
		}
		XFree(name);
	}
}
/*----------------------------------------------------------------------------*/
void VKMainProcess()
{
	XSelectInput(display, root, PropertyChangeMask);
	VKRegisterEvent(root, VKRootWindowProcess, NULL);
	while( !vk_done ) {
		usleep(1000);

		if( vk_timeout && vk_flash_on )
			VKHideFlash();

		VKCheckMouseStatus();
		if( vk_mouse_clicked && vk_menu_on ) {
			vk_mouse_clicked = False;
			VKHideMenu();
		}

		while( XPending(display) ) {
			XEvent event;

			XNextEvent(display, &event);
			VKDispatchEvent(&event);
		}
	}
}
/*----------------------------------------------------------------------------*/
void VKInitialization()
{
	VKSystemInit();
	VKStartXSession();
	VKLoadXResource();
	VKCreateFlash();
	VKShowFlash();
	VKCreateMainWindow();
	VKCreateMenuWindow();
	VKCreateHotkeyWindow();
}
/*----------------------------------------------------------------------------*/
void VKFinalization()
{
	VKDestroyFlash();
	VKDestroyHotkeyWindow();
	VKDestroyMenuWindow();
	VKDestroyMainWindow();
	VKFreeXResource();
	VKStopXSession();
}
/*----------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	VKLoadConfig(argc, argv);
	VKInitialization();
	VKMainProcess();
	VKFinalization();
	VKSaveConfig();
	return EXIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
