/*----------------------------------------------------------------------------*/
/*  systray.c                                                                 */
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
#include "systray.h"
/*----------------------------------------------------------------------------*/
#define SYSTEM_TRAY_REQUEST_DOCK	0
#define SYSTEM_TRAY_BEGIN_MESSAGE	1
#define SYSTEM_TRAY_CANCEL_MESSAGE	2
/*----------------------------------------------------------------------------*/
VKSystrayInfo systray;
/*----------------------------------------------------------------------------*/
void VKSystrayInit()
{
	systray.window = XInternAtom(display, "WINDOW", False);
	systray.manager = XInternAtom(display, "MANAGER", False);
	systray.handler = XInternAtom(display, "_NET_SYSTEM_TRAY_S0", False);
	systray.request = XInternAtom(display, "_NET_SYSTEM_TRAY_OPCODE", False);
	systray.owner = XGetSelectionOwner(display, systray.handler);
	VKSystrayCalcIconSize();
}
/*----------------------------------------------------------------------------*/
void VKSystrayCalcIconSize()
{
	if( VKIsDockable() ) {
		Window r;
		int x, y;
		uint w, h, b, d;
		XGetGeometry(display, systray.owner, &r, &x, &y, &w, &h, &b, &d);
		vk_icon_width = w;
		vk_icon_height = h;
	}
}
/*----------------------------------------------------------------------------*/
void VKSystrayProcess(XEvent *event)
{
	if( event->xclient.type == systray.manager ||
		event->xclient.type == systray.window ) {
		TRACE("Systray owner changed to 0x%08X\n", event->xclient.data.l[2]);
		systray.owner = XGetSelectionOwner(display, systray.handler);
		if( systray.redocking ) {
			extern void VKDockMainWindow();
			systray.redocking = 0;
			VKDockMainWindow();
		}
	}
}
/*----------------------------------------------------------------------------*/
void VKRequestDocking()
{
	if( VKIsDockable() ) {
		XEvent e;

		memset(&e, 0, sizeof(e));
		e.xclient.type = ClientMessage;
		e.xclient.window = systray.owner;
		e.xclient.message_type = systray.request;
		e.xclient.format = 32;
		e.xclient.data.l[0] = CurrentTime;
		e.xclient.data.l[1] = SYSTEM_TRAY_REQUEST_DOCK;
		e.xclient.data.l[2] = main_window;
		e.xclient.data.l[3] = 0;
		e.xclient.data.l[4] = 0;
		XSendEvent(display, systray.owner, False, NoEventMask, &e);
		XSync(display, False);
	}
}
/*----------------------------------------------------------------------------*/
