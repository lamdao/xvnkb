/*----------------------------------------------------------------------------*/
/*  debug.h                                                                   */
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
#ifndef __VK_DEBUG_H
#define __VK_DEBUG_H
/*----------------------------------------------------------------------------*/
#define DUMP(args...)	fprintf(stderr, args)
/*----------------------------------------------------------------------------*/
#ifndef TRACE
	#ifdef DEBUG
		#define TRACE(args...)	fprintf(stderr, args)
	#else
		#define TRACE(args...)
	#endif
#endif
/*----------------------------------------------------------------------------*/
#define error(args...) { DUMP(args); exit(-1); }
/*----------------------------------------------------------------------------*/
#endif
