/*----------------------------------------------------------------------------*/
/*  xvnkb_ctrl.c                                                              */
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
#include "property.h"
#include "xconfig.h"
/*----------------------------------------------------------------------------*/
#define VK_CTRL_DISABLE		0
#define VK_CTRL_ENABLE		1
#define VK_CTRL_TOGGLE		2
/*----------------------------------------------------------------------------*/
extern int (*VKExtraOption)(char *a);
extern void VKUsage(char *program);
/*----------------------------------------------------------------------------*/
XErrorHandler old_error_handler;
/*----------------------------------------------------------------------------*/
char *help =
	"\nVietnamese keyboard for XWindow - xvnkb controler version "VERSION"\n"
	"* Usage:\n"
	" - Command line:\n"
	"   %s <action> [option=value]\n"
	" Actions:\n"
	"     -e, --enable   activate xvnkb core\n"
	"     -d, --disable  deactivate xvnkb core\n"
	"     -t, --toggle   toggle status of xvnkb core\n"
	"     -h, --help     display this help\n"
	" Options:\n"
	"     -m, --method   set default input method (value=vni,telex,viqr)\n"
	"     -c, --charset  set default charset (value=utf8,tcvn,viscii,vps,viqr)\n"
	"   ex:\n"
	"       %s --method=vni\n"
	"     or\n"
	"       %s --method=telex\n\n";
/*----------------------------------------------------------------------------*/
int mode = -1;
/*----------------------------------------------------------------------------*/
int VKCtrlExtraOption(char *a)
{
	static char *opts = "|-d|-e|-t|";
	switch( strstr(opts, a)-opts ) {
		case 0:
			mode = VK_CTRL_DISABLE;
			break;
		case 3:
			mode = VK_CTRL_ENABLE;
			break;
		case 6:
			mode = VK_CTRL_TOGGLE;
			break;
		default:
			return -1;
	}
	return 0;
}
/*----------------------------------------------------------------------------*/
int VKErrorHandler(Display *display, XErrorEvent *event)
{
	if( event->error_code==BadWindow ||
		event->error_code==BadDrawable ||
		event->error_code==BadAccess) return(-1);
	return old_error_handler(display, event);
}
/*----------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	int v;

	VKExtraOption = VKCtrlExtraOption;

	VKLoadConfig(argc, argv);
	display = XOpenDisplay(NULL);
	if( !display ) {
		printf("Error: cannot open display!");
		exit(-1);
	}
	screen = DefaultScreen(display);
	root = RootWindow(display, screen);
	old_error_handler = XSetErrorHandler(VKErrorHandler);

	VKAtomInit(display);
	switch( mode ) {
		case VK_CTRL_DISABLE:
			VKResetMode();
			break;
		case VK_CTRL_ENABLE:
			VKChangeCharset(vk_charset);
			VKChangeMethod();
			VKChangeUsing();
			break;
		case VK_CTRL_TOGGLE:
			v = VKGetValue(display, vk_using_atom);
			if( v>VKM_OFF ) {
				vk_method = VKGetValue(display, vk_method_atom);
				vk_method = vk_method==VKM_OFF ? vk_using : VKM_OFF;
				VKChangeMethod();
			}
			else {
				printf("c=%d,u=%d,m=%d\n", vk_charset, vk_using, vk_method);
				VKChangeCharset(vk_charset);
				VKChangeMethod();
				VKChangeUsing();
			}
			break;
		default:
			VKUsage(argv[0]);
	}
	XSync(display, False);
    XSetErrorHandler(old_error_handler);

	XCloseDisplay(display);
	if( mode>=0 ) VKSaveConfig();
	return 0;
}
