/*----------------------------------------------------------------------------*/
/*  mode.c                                                                    */
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
#include "property.h"
/*----------------------------------------------------------------------------*/
void VKChangeUsing()
{
	if( display )
		VKSetValue(display, vk_using_atom, vk_using);
}
/*----------------------------------------------------------------------------*/
void VKChangeMethod()
{
	if( display )
		VKSetValue(display, vk_method_atom, vk_method);
}
/*----------------------------------------------------------------------------*/
void VKSwitchMethod()
{
	vk_method = vk_method==VKM_OFF ? vk_using : VKM_OFF;
	VKChangeMethod();
}
/*----------------------------------------------------------------------------*/
void VKChangeCharset(int id)
{
	if( display )
		VKSetValue(display, vk_charset_atom, id);
}
/*----------------------------------------------------------------------------*/
void VKResetMode()
{
	if( display ) {
		VKSetValue(display, vk_using_atom, VKM_OFF);
		VKSetValue(display, vk_method_atom, VKM_OFF);
	}
}
/*----------------------------------------------------------------------------*/
#ifdef VK_CHECK_SPELLING
void VKSetSpelling(int s)
{
	if( display )
		VKSetValue(display, vk_spelling_atom, s);
}
#endif
/*----------------------------------------------------------------------------*/
