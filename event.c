/*----------------------------------------------------------------------------*/
/*  event.c                                                                   */
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
#include "event.h"
/*----------------------------------------------------------------------------*/
typedef struct {
	Window			window;
	VKEventAction	action;
	void			*data;
} VKEventHandler;
/*----------------------------------------------------------------------------*/
#define MAX_HANDLERS	32
/*----------------------------------------------------------------------------*/
static VKEventHandler handlers[MAX_HANDLERS] = { [0 ... MAX_HANDLERS-1] = {0,0} };
/*----------------------------------------------------------------------------*/
Window wfocus = None;
/*----------------------------------------------------------------------------*/
void VKGrabFocus(Window window)
{
	wfocus = window;
}
/*----------------------------------------------------------------------------*/
void VKReleaseFocus()
{
	wfocus = None;
}
/*----------------------------------------------------------------------------*/
void VKRegisterEvent(Window window, VKEventAction action, void *data)
{
	int i;
	for( i=0; i<MAX_HANDLERS; i++ )
		if( !handlers[i].action || handlers[i].window==window ) {
			handlers[i].window = window;
			handlers[i].action = action;
			handlers[i].data = data;
			return;
		}
}
/*----------------------------------------------------------------------------*/
void VKUnregisterEvent(Window window)
{
	int i;
	for( i=0; i<MAX_HANDLERS; i++ )
		if( handlers[i].window == window ) {
			handlers[i].action = NULL;
			return;
		}
}
/*----------------------------------------------------------------------------*/
void VKDispatchEvent(XEvent *event)
{
	int i;
	Window w = wfocus!=None ? wfocus : event->xany.window;
	for( i=0; i<MAX_HANDLERS; i++ )
		if( handlers[i].action && w == handlers[i].window ) {
			handlers[i].action( event, handlers[i].data );
			return;
		}
}
/*----------------------------------------------------------------------------*/
