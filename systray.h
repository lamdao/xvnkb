/*----------------------------------------------------------------------------*/
/*  systray.h                                                                 */
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
#ifndef __VK_SYSTRAY_H
#define __VK_SYSTRAY_H
/*----------------------------------------------------------------------------*/
typedef struct {
	Atom window;
	Atom manager;
	Atom handler;
	Atom request;
	Window owner;
	int redocking;
} VKSystrayInfo;
/*----------------------------------------------------------------------------*/
#define VKIsDockable()		(systray.owner != None)
#define VKSetAutoDocking(a)	(systray.redocking = a, vk_docking = VKD_AUTO)
/*----------------------------------------------------------------------------*/
void VKSystrayInit();
void VKSystrayCalcIconSize();
void VKSystrayProcess(XEvent *event);
void VKRequestDocking();
/*----------------------------------------------------------------------------*/
extern VKSystrayInfo systray;
/*----------------------------------------------------------------------------*/
#endif
