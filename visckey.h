/*----------------------------------------------------------------------------*/
/*  visckey.h                                                                 */
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
#ifndef __VISCKEY_H
#define __VISCKEY_H
/*----------------------------------------------------------------------------*/
#include "typedefs.h"
/*----------------------------------------------------------------------------*/
extern inline long VKAddKey(char key);
extern inline void VKClearBuffer();
extern inline long VKBackspaceDelete();
extern inline void VKSwitchMethod();
extern inline void VKChangeCharset(int id);
extern inline void VKSetSpelling(int s);
/*----------------------------------------------------------------------------*/
extern int vk_using;
extern int vk_method;
extern int vk_charset;
extern int vk_spelling;
/*----------------------------------------------------------------------------*/
extern char vk_buffer[256];
extern int vk_blength;
extern int vk_plength;
/*----------------------------------------------------------------------------*/
#endif
