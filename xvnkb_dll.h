/*----------------------------------------------------------------------------*/
/*  xvnkb_dll.h                                                               */
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
#ifndef __XVNKB_DLL_H
#define __XVNKB_DLL_H
/*----------------------------------------------------------------------------*/
#include <dlfcn.h>
/*----------------------------------------------------------------------------*/
static inline void *get_func_entry(char *lib1, char *lib2, char *fn)
{
	void *fptr = 0;

#ifdef RTLD_NEXT
	fptr = dlsym(RTLD_NEXT, fn);
#else
	void *dlh = NULL;

	if( lib1 )
		dlh = dlopen(lib1, RTLD_GLOBAL | RTLD_NOW);
	if( !dlh && lib2 )
		dlh = dlopen(lib2, RTLD_GLOBAL | RTLD_NOW);
		
	if( !dlh )
		DUMP("xvnkb: %s\n", dlerror());
	else
		fptr = dlsym(dlh, fn);

#endif
	if( !fptr )
		DUMP("xvnkb: dlsym: %s\n", dlerror());
	else {
		TRACE("xvnkb: %s is at %p\n", fn, fptr);
	}

	return fptr;
}
/*----------------------------------------------------------------------------*/
#endif
