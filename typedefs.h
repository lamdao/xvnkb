/*----------------------------------------------------------------------------*/
/*  typedefs.h                                                                */
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
#ifndef __VK_TYPEDEFS_H
#define __VK_TYPEDEFS_H
/*----------------------------------------------------------------------------*/
#include <sys/types.h>
#include "config.h"
/*----------------------------------------------------------------------------*/
typedef enum {
	VKM_OFF, VKM_VNI, VKM_TELEX, VKM_VIQR
} vk_methods;
/*----------------------------------------------------------------------------*/
typedef enum {
	VKC_TCVN, VKC_VNI, VKC_VIQR, VKC_VISCII, VKC_VPS, VKC_UTF8
} vk_charsets;
/*----------------------------------------------------------------------------*/
typedef enum {
	VKD_OFF, VKD_ON, VKD_AUTO
} vk_docking_modes;
/*----------------------------------------------------------------------------*/
#ifdef VK_NEED_UCHAR
typedef unsigned char uchar;
#endif
/*----------------------------------------------------------------------------*/
#ifdef VK_NEED_USHORT
typedef unsigned short ushort;
#endif
/*----------------------------------------------------------------------------*/
#ifdef VK_NEED_UINT
typedef unsigned int uint;
#endif
/*----------------------------------------------------------------------------*/
#ifdef VK_NEED_ULONG
typedef unsigned long ulong;
#endif
/*----------------------------------------------------------------------------*/
#endif
