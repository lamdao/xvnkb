/*----------------------------------------------------------------------------*/
/*  property.h                                                                */
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
#ifndef __VK_PROPERTY_H
#define __VK_PROPERTY_H
/*----------------------------------------------------------------------------*/
#define VKP_MAX_LENGTH		1024
/*----------------------------------------------------------------------------*/
#define VKP_CHARSET			"VK_CHARSET"
#define VKP_METHOD			"VK_METHOD"
#define VKP_USING			"VK_USING"
#define VKP_SPELLING		"VK_SPELLING"
#define VKP_HOTKEY			"VK_HOTKEY"
/*----------------------------------------------------------------------------*/
extern Atom vk_using_atom;
extern Atom vk_method_atom;
extern Atom vk_charset_atom;
extern Atom vk_spelling_atom;
extern Atom vk_hotkey_atom;
/*----------------------------------------------------------------------------*/
void VKAtomInit(Display *display);
long VKGetValue(Display *display, Atom key);
void VKSetValue(Display *display, Atom key, long value);
void VKGetValues(Display *display, Atom key, long *values, int n);
void VKSetValues(Display *display, Atom key, long *values, int n);
void VKSetString(Display *display, Atom key, unsigned char *value);
char *VKGetString(Display *display, Atom key);
/*----------------------------------------------------------------------------*/
#endif
