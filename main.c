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
#include "systray.h"
#include "menu.h"
#include "hotkey.h"
#include "property.h"
#include "event.h"
#include "msgbox.h"
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
	char *name;

	if( event->type == ClientMessage ) {
		VKSystrayProcess(event);
		return;
	}

	name = XGetAtomName(display, ((XPropertyEvent *)event)->atom);
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
void VKRootWindowInit()
{
	XSelectInput(display, root, PropertyChangeMask|StructureNotifyMask);
	VKRegisterEvent(root, VKRootWindowProcess, NULL);
}
/*----------------------------------------------------------------------------*/
void VKMainProcess()
{
	int xfd = ConnectionNumber(display);

	while( !vk_done ) {
		struct timeval tv = {1, 0};
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(xfd, &rfds);
		select(xfd+1, &rfds, 0, 0, &tv);

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
	VKSystrayInit();
	VKCreateMainWindow();
	VKCreateMenuWindow();
	VKCreateHotkeyWindow();
	VKRootWindowInit();
}
/*----------------------------------------------------------------------------*/
void VKCheckSystem()
{
	static char *core_messages[] = {
		"The core, xvnkb.so, is not preloaded!\n"
		"We can not work with Vietnamese properly now.\n"
		"Please refer to xvnkb manual to fix this problem.",
		"Phần lõi của xvnkb chưa được nạp!\n"
		"Chúng ta tạm thời không thể gõ được tiếng Việt.\n"
		"Hãy tham khảo tài liệu của xvnkb để khắc phục."
	};

	FILE *fp;
	char buf[512];
	char *ld_preload = getenv("LD_PRELOAD");
	int core_ok = 0;

	if( ld_preload && strstr(ld_preload, "xvnkb.so") )
		core_ok = 1;

	if( !core_ok ) {
		fp = fopen("/etc/ld.so.preload", "r");

		if( fp ) {
			while( fgets(buf, sizeof(buf), fp) ) {
				if( strstr(buf, "xvnkb.so") ) {
					core_ok = 1;
					break;
				}
			}
			fclose(fp);
		}

		if( !core_ok )
			VKShowMessage(core_messages[vk_interface]);
	}
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
	VKCheckSystem();
	VKMainProcess();
	VKFinalization();
	VKSaveConfig();
	return EXIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
