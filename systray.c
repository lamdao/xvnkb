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
int docking = 0;
/*----------------------------------------------------------------------------*/
Window systray = None;
/*----------------------------------------------------------------------------*/
void VKCheckSystray()
{
	Atom systray_atom = XInternAtom(display, "_NET_SYSTEM_TRAY_S0", False);
	systray = XGetSelectionOwner(display, systray_atom);
}
/*----------------------------------------------------------------------------*/
void VKRequestDocking()
{
	if( VKIsDockable() ) {
		XEvent e;

		memset(&e, 0, sizeof(e));
		e.xclient.type = ClientMessage;
		e.xclient.window = systray;
		e.xclient.message_type = XInternAtom(display, "_NET_SYSTEM_TRAY_OPCODE", False);
		e.xclient.format = 32;
		e.xclient.data.l[0] = CurrentTime;
		e.xclient.data.l[1] = SYSTEM_TRAY_REQUEST_DOCK;
		e.xclient.data.l[2] = main_window;
		e.xclient.data.l[3] = 0;
		e.xclient.data.l[4] = 0;
		XSendEvent(display, systray, False, NoEventMask, &e);
		XSync(display, False);
	}
}
/*----------------------------------------------------------------------------*/
