/*----------------------------------------------------------------------------*/
/*  main.c                                                                    */
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
#include "xconfig.h"
#include "xresource.h"
#include "flash.h"
#include "session.h"
#include "mainwin.h"
#include "systray.h"
#include "menu.h"
#include "hotkey.h"
#include "property.h"
#include "event.h"
#include "msgbox.h"
/*----------------------------------------------------------------------------*/
void VKCheckMouseStatus()
{
	static int rx=-1, ry=-1;
	static unsigned int b = 0;
	Window fw = None;
	int rt;

	XGetInputFocus(display, &fw, &rt);
	if( fw!=None ) {
		Window w;
		unsigned int bb = 0;
		int x, y, wx, wy;

		if( XQueryPointer(display, fw, &w, &w, &x, &y, &wx, &wy, &bb) )
		if( bb>255 && (bb!=b || rx!=x || ry!=y) ) {   
			b = bb;
			rx = x;
			ry = y;
			vk_mouse_clicked = True;
		}
	}
}
/*----------------------------------------------------------------------------*/
void VKRootWindowProcess(XEvent *event, void *data)
{
	char *name;

	if( event->type == ClientMessage ) {
		VKSystrayProcess(event);
		return;
	}

	name = XGetAtomName(display, ((XPropertyEvent *)event)->atom);
	if( name!=NULL ) { 
		if( !strcmp(name, VKP_CHARSET) )
			vk_charset = VKGetValue(display, ((XPropertyEvent *)event)->atom);
		else
		if( !strcmp(name, VKP_USING) )
			vk_using = VKGetValue(display, ((XPropertyEvent *)event)->atom);
		else
		if( !strcmp(name, VKP_METHOD) ) {
			extern void VKDrawIcon();
			vk_method = VKGetValue(display, ((XPropertyEvent *)event)->atom);
			VKDrawIcon();

			TRACE("GUI: %s\n", name);
		}
		XFree(name);
	}
}
/*----------------------------------------------------------------------------*/
void VKRootWindowInit()
{
	XSelectInput(display, root, PropertyChangeMask|StructureNotifyMask);
	VKRegisterEvent(root, VKRootWindowProcess, NULL);
}
/*----------------------------------------------------------------------------*/
void VKMainProcess()
{
	while( !vk_done ) {
		usleep(1000);

		if( vk_timeout && vk_flash_on )
			VKHideFlash();

		VKCheckMouseStatus();
		if( vk_mouse_clicked && vk_menu_on ) {
			vk_mouse_clicked = False;
			VKHideMenu();
		}

		while( XPending(display) ) {
			XEvent event;

			XNextEvent(display, &event);
			VKDispatchEvent(&event);
		}
	}
}
/*----------------------------------------------------------------------------*/
void VKInitialization()
{
	VKSystemInit();
	VKStartXSession();
	VKLoadXResource();
	VKCreateFlash();
	VKSystrayInit();
	VKCreateMainWindow();
	VKCreateMenuWindow();
	VKCreateHotkeyWindow();
	VKRootWindowInit();
}
/*----------------------------------------------------------------------------*/
void VKCheckSystem()
{
	extern char *sys_lang;
	static char *core_messages[] = {
		"The core, xvnkb.so, is not preloaded!\n"
		"We can not work with Vietnamese properly now.\n"
		"Please refer to xvnkb manual to fix this problem.",
		"Phần lõi của xvnkb chưa được nạp!\n"
		"Chúng ta tạm thời không thể gõ được tiếng Việt.\n"
		"Hãy tham khảo tài liệu của xvnkb để khắc phục."
	};
	static char *lang_messages[] = {
		"Current value of LANG is \"%s\".\n"
		"You cannot use Unicode charset to input with this LANG value.\n"
		"Please set LANG to %s.\n"
		"Refer to xvnkb manual about setting LANG & create locale.",
		"Biến môi trường LANG của bạn hiện tại là \"%s\".\n"
		"Bạn không thể dùng bảng mã Unicode với giá trị LANG này.\n"
		"Hãy đặt lại LANG thành %s.\n"
		"Tham khảo thêm tài liệu của xvnkb để chọn LANG và tạo locale."
	};
	static char *locale_messages[] = {
		"Missing locale information for LANG %s in\n"
		"/usr/share/locale/%s.\n"
		"We may not work with Vietnamese properly."
		"Please refer to xvnkb manual to create the information.",
		"Không tìm thấy các thông tin về bản địa cho LANG %s tại\n"
		"/usr/share/locale/%s.\n"
		"Chúng ta có thể sẽ không làm việc được với tiếng Việt.\n"
		"Tham khảo thêm tài liệu của xvnkb để tạo các thông tin này."
	};

	FILE *fp;
	char buf[512];
	char *ld_preload = getenv("LD_PRELOAD");
	int core_ok = 0, lang_ok = 0;

	if( ld_preload && strstr(ld_preload, "xvnkb.so") )
		core_ok = 1;

	if( !core_ok ) {
		fp = fopen("/etc/ld.so.preload", "r");

		if( fp ) {
			while( fgets(buf, sizeof(buf), fp) ) {
				if( strstr(buf, "xvnkb.so") ) {
					core_ok = 1;
					break;
				}
			}
			fclose(fp);
		}

		if( !core_ok )
			VKShowMessage(core_messages[vk_interface]);
	}

	if( core_ok ) {
		if( sys_lang && (strstr(sys_lang, "UTF-8") || strstr(sys_lang, "utf8")) )
			lang_ok = 1;

		if( !lang_ok ) {
			char slang[64];
			if( !sys_lang ) {
				strcpy(slang, vk_interface ?
					"vi_VN.UTF-8 hoặc en_US.UTF-8" :
					"vi_VN.UTF-8 or en_US.UTF-8");
				sys_lang = "";
			}
			else {
				char *p;
				strcpy(slang, sys_lang);
				p = strchr(slang, '.');
				if( p ) *p = 0;
				strcat(slang, ".UTF-8");
			}
			sprintf(buf, lang_messages[vk_interface], sys_lang, slang);
			VKShowMessage(buf);
		}
		else {
			sprintf(buf, "/usr/share/locale/%s/LC_IDENTIFICATION", sys_lang);
			fp = fopen(buf, "r");
			if( fp ) {
				fclose(fp);
				VKShowFlash();
			}
			else {
				sprintf(buf, locale_messages[vk_interface], sys_lang, sys_lang);
				VKShowMessage(buf);
			}
		}
	}
}
/*----------------------------------------------------------------------------*/
void VKFinalization()
{
	VKDestroyFlash();
	VKDestroyHotkeyWindow();
	VKDestroyMenuWindow();
	VKDestroyMainWindow();
	VKFreeXResource();
	VKStopXSession();
}
/*----------------------------------------------------------------------------*/
int main(int argc, char **argv)
{
	VKLoadConfig(argc, argv);
	VKInitialization();
	VKCheckSystem();
	VKMainProcess();
	VKFinalization();
	VKSaveConfig();
	return EXIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
