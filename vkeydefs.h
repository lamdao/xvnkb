/*----------------------------------------------------------------------------*/
/*  vkeydefs.h                                                                */
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
#ifndef __VKEYDEFS_H
#define __VKEYDEFS_H
/*----------------------------------------------------------------------------*/
#define VK_SHIFT				0x01
#define	VK_CAPS_LOCK			0x02
#define VK_CONTROL				0x04
#define VK_ALT					0x08
#define VK_WINKEY				0x40
#define	VK_NUM_LOCK				0x10
#define	VK_SCROLL_LOCK			0x80
#define	VK_NOTACCEPT_STATES		0x6C
#define VK_UPPERCASE_STATES		(VK_SHIFT|VK_CAPS_LOCK)
/*----------------------------------------------------------------------------*/
#define VK_HOTKEY_STATE			VK_ALT
#define VK_HOTKEY_CODE			XK_Shift_L
#define VK_HOTKEY_STRING		"Alt Shift_L"
/*----------------------------------------------------------------------------*/
#endif
