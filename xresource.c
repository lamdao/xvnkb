/*----------------------------------------------------------------------------*/
/*  xresource.c                                                               */
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
#include "data.h"
#include <locale.h>
/*----------------------------------------------------------------------------*/
int sys_utf8 = 1;
/*----------------------------------------------------------------------------*/
void VKLocaleInit()
{
	char *lang = getenv("LANG");
	lang = lang ? strdup(lang) : strdup("en_US");
	if( !strstr(lang, ".UTF-8") ) {
		char env[256];
		char *p = strchr(lang, '.');
		if( p ) *p = 0;
		if( !strcmp(lang, "C") )
			p = strdup("vi_VN.UTF-8");
		else {
			p = (char *)malloc(strlen(lang)+8);
			sprintf(p, "%s%s", lang, ".UTF-8");
		}
		snprintf(env, sizeof(env), "LANG=%s", p);
		putenv(env);
		free(lang);
		lang = p;
	}
	if( !setlocale(LC_ALL, "") ) {
#ifndef USE_XFT
		// Cannot use XmbDrawingString in this case
		// to draw UTF-8 string => force back to English
		vk_interface = 0;
		sys_utf8 = 0;
#endif
	}
	free(lang);
}
/*----------------------------------------------------------------------------*/
#ifndef USE_XFT
char *VKXftFont2XFont(char *name)
{
	static char fn[128], *sep = ":";

	char s[128], *p, *face, *style = 0;
	int bold = 0, mode = 'r';

	strcpy(s, name);
	face = strtok(s, sep);
	p = strtok(NULL, sep);
	while( p ) {
		if( !strncasecmp(p, "style=", 6) )
			style = p+6;
		p = strtok(NULL, sep);
	}
	if( style ) {
		p = strtok(style, " ");
		while( p ) {
			if( !strcasecmp(p, "bold") )
				bold = 1;
			else
			if( !strcasecmp(p, "italic") ||
				!strcasecmp(p, "oblique") )
				mode = 'i';
			p = strtok(NULL, " ");
		}
	}

	snprintf(fn, sizeof(fn), "*-%s-%s-%c-normal--*",
								face, bold ? "bold" : "medium",	mode);
	return fn;
}
/*----------------------------------------------------------------------------*/
void VKUseDefaultFont()
{
	if( vk_font_name ) free(vk_font_name);
	vk_font_name = vk_interface==VK_ENGLISH ?
		strdup(screen_width<=800 ? VK_FONT_SMALL : VK_FONT_LARGE) :
		strdup(VK_VN_FONT);
}
/*----------------------------------------------------------------------------*/
void VKFontSetInit()
{
	int missing_count;
	char **missing_list;
	char *def_string;
	char *backup = NULL;

	vk_fontset = XCreateFontSet(display, vk_font_name, &missing_list,
								&missing_count, &def_string);
	if( !vk_fontset ) {
		char *p = strchr(vk_font_name, ':');
		if( p ) {
			TRACE("It seems XFT font name,"
				" strip extended info and try to reload fontset.\n");
			backup = vk_font_name;
			vk_font_name = strdup(VKXftFont2XFont(vk_font_name));
		}
		else {
			TRACE("Unknown fontname style.\n"
				"Try to load fontset with default font.\n");
			VKUseDefaultFont();
		}
		vk_fontset = XCreateFontSet(display, vk_font_name, &missing_list,
									&missing_count, &def_string);
	}
	if( !vk_fontset ) {
		if( backup ) {
			VKUseDefaultFont();
			vk_fontset = XCreateFontSet(display, vk_font_name, &missing_list,
									&missing_count, &def_string);
		}
		if( !vk_fontset ) error("Error: cannot load font set.\n");
	}
	if( backup ) {
		free(vk_font_name);
		vk_font_name = backup;
	}
}
#endif
/*----------------------------------------------------------------------------*/
inline void VKAllocColorName(char *name, ulong *color)
{
	XColor c;
	XParseColor(display, colormap, name, &c);
	XAllocColor(display, colormap, &c);
	*color = c.pixel;
}
/*----------------------------------------------------------------------------*/
void VKLoadPalette()
{
#ifdef USE_XFT
	XftColorAllocName(display, visual, colormap, "red", &clRed );
	XftColorAllocName(display, visual, colormap, "yellow", &clYellow );
	XftColorAllocName(display, visual, colormap, "white", &clWhite );
	XftColorAllocName(display, visual, colormap, "black", &clBlack );
	XftColorAllocName(display, visual, colormap, "blue", &clBlue );
	XftColorAllocName(display, visual, colormap, "gray", &clGray );
	XftColorAllocName(display, visual, colormap, "SteelBlue", &clMenuBar );
#else
	VKAllocColorName("red", &clRed);
	VKAllocColorName("yellow", &clYellow);
	VKAllocColorName("white", &clWhite);
	VKAllocColorName("black", &clBlack);
	VKAllocColorName("blue", &clBlue);
	VKAllocColorName("gray", &clGray);
	VKAllocColorName("SteelBlue", &clMenuBar);
#endif
}
/*----------------------------------------------------------------------------*/
void VKLoadXResource()
{
	VKLocaleInit();
	VKLoadPalette();

	if( !vk_font_name )
		vk_font_name = strdup(screen_width<=800 ? VK_FONT_SMALL : VK_FONT_LARGE);

	if( !vk_font_name ) error("Error: not enough memory!");
#ifdef USE_XFT
	vk_font = XftFontOpenName(display, 0, vk_font_name);
	if( !vk_font )
		vk_font = XftFontOpenXlfd(display, 0, vk_font_name);
#else
	vk_font = XLoadQueryFont(display, vk_font_name);
	if( !vk_font )
		vk_font = XLoadQueryFont(display, screen_width<=800 ? VK_FONT_SMALL : VK_FONT_LARGE);
	VKFontSetInit();
#endif
	if( !vk_font ) error("Cannot load font %s\n", vk_font_name);

	vk_hand = XCreateFontCursor(display, XC_hand2);
	vk_cursor = XCreateFontCursor(display, XC_left_ptr);
	vk_attrib.override_redirect = True;
#ifdef USE_XFT
	vk_text_height = vk_font->height;
	vk_text_ascent = vk_font->ascent;
#else
	{
		XFontSetExtents *fse = XExtentsOfFontSet(vk_fontset);
		vk_text_height = fse->max_logical_extent.height + 4;
		vk_text_ascent = vk_font->ascent + 3;
	}
#endif
}
/*----------------------------------------------------------------------------*/
void VKFreeXResource()
{
	XFreeCursor(display, vk_hand);
	XFreeCursor(display, vk_cursor);
#ifdef USE_XFT
	XftColorFree(display, visual, colormap, &clRed);
	XftColorFree(display, visual, colormap, &clYellow);
	XftColorFree(display, visual, colormap, &clWhite);
	XftColorFree(display, visual, colormap, &clBlack);
	XftColorFree(display, visual, colormap, &clBlue);
	XftColorFree(display, visual, colormap, &clGray);
	XftColorFree(display, visual, colormap, &clMenuBar);
	XftFontClose(display, vk_font);
#else
	XFreeFontSet(display, vk_fontset);
	XFreeFont(display, vk_font);
#endif
}
/*----------------------------------------------------------------------------*/
