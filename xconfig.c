/*----------------------------------------------------------------------------*/
/*  xconfig.c                                                                 */
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
#include "xconfig.h"
#include "property.h"
/*----------------------------------------------------------------------------*/
typedef struct {
	char *name;
	int *vptr;
	int value;
} vk_rcinfo;
/*----------------------------------------------------------------------------*/
vk_rcinfo vk_ropts[] = {
	{"left",	&vk_x},
	{"top",		&vk_y},
	{"method",	&vk_method},
	{"enable",	&vk_using},
	{"charset",	&vk_charset},
	{"docking",	&vk_docking},
	{0}
};
/*----------------------------------------------------------------------------*/
vk_rcinfo vk_mopts[] = {
	{"vni",		&vk_method, VKM_VNI},
	{"telex",	&vk_method, VKM_TELEX},
	{"viqr",	&vk_method, VKM_VIQR},
	{0}
};
/*----------------------------------------------------------------------------*/
vk_rcinfo vk_copts[] = {
	{"tcvn",	&vk_charset, VKC_TCVN},
	{"vni",		&vk_charset, VKC_VNI},
	{"viqr",	&vk_charset, VKC_VIQR},
	{"viscii",	&vk_charset, VKC_VISCII},
	{"vps",		&vk_charset, VKC_VPS},
	{"utf8",	&vk_charset, VKC_UTF8},
	{0}
};
/*----------------------------------------------------------------------------*/
int (*VKExtraOption)(char *a) = NULL;
/*----------------------------------------------------------------------------*/
int VKSetResourceInfo(vk_rcinfo *rc, char *key, int value)
{
	for( ; rc->name; rc++ )
		if( !strcasecmp(key, rc->name) ) {
			*rc->vptr = value < 0 ? rc->value : value;
			return 1;
		}
	return 0;
}
/*----------------------------------------------------------------------------*/
void VKUsage(char *program)
{
#ifdef XVNKB_TOOL
	extern char *help;
#else
	char *help =
		"\nVietnamese keyboard for XWindow - xvnkb version "VERSION"\n"
		"* Usage:\n"
		" - Command line:\n"
		"   %s [option=value]\n"
		" Options:\n"
		"     -h, --help     display this help\n"
		"     -m, --method   set default input method (value=vni,telex,viqr)\n"
		"     -c, --charset  set default charset (value=utf8,tcvn,viscii,vps,viqr)\n"
		"   ex:\n"
		"       %s --method=vni\n"
		"     or\n"
		"       %s --method=telex\n"
		" - GUI - Using mouse buttons:\n"
		"   o Left:\tswitch input method\n"
		"   o Middle:\texit\n"
		"   o Right:\tpopup configuration menu\n\n";
#endif
	printf( help, program, program, program );
	exit(2);
}
/*----------------------------------------------------------------------------*/
static int vk_firstboot = 0;
/*----------------------------------------------------------------------------*/
void VKLoadConfig(int argc, char **argv)
{
	FILE *fp;
	char *conf = ".xvnkbrc";
	char *home = getenv("HOME");
	char buffer[256], *p;
	char *key, *svalue;
	int l, n=0, value;

	if( !home ) home = "./";
	vk_config_file = (char *)malloc(strlen(home)+strlen(conf)+2);
	sprintf(vk_config_file, "%s/%s", home, conf);

	fp = fopen(vk_config_file, "r");
	if( fp ) {
		while( fgets(buffer, sizeof(buffer), fp) ) {
			n++;
			l = strlen(buffer);
			if( buffer[l-1]!='\n' ) {
				printf("Error in %s file: line %d is too long\n", conf, n);
				while( fgets(buffer, sizeof(buffer), fp) && buffer[strlen(buffer)-1]!='\n' );
			}
			else {
				p = buffer;
				p[l-1] = 0;
				while( isspace(*p) ) p++;
				if( *p==0 || *p=='#' ) continue;
				key = strtok(p, " ");
				svalue = strtok(NULL, "\0");
				if( !svalue ) {
					printf("Error in %s file: line %d has wrong format\n", conf, n);
					continue;
				}
				if( !strcasecmp(key, "font") ) {
					vk_font_name = strdup(svalue);
					continue;
				}
				if( !strcasecmp(key, "interface") ) {
					vk_interface = atoi(svalue) & 1;
					continue;
				}
				if( !strcasecmp(key, "spelling") ) {
					vk_spelling = atoi(svalue) & 1;
					continue;
				}
				if( !strcasecmp(key, "hotkey") ) {
					vk_hotkey = strdup(svalue);
					continue;
				}
				value = atoi(svalue);
				if( !VKSetResourceInfo(vk_ropts, key, value<0 ? -value : value) )
					printf("Error in %s file: line %d has wrong option %s\n", conf, n, key);
			}
		}
		fclose(fp);
	}

	key = buffer;
	for( n=1; n<argc; n++ ) {
		static char *opts = "|-h|-m|-c|--help|--method|--charset|";

		sprintf(key, "|%s|", strtok(argv[n], "="));
		p = strtok(NULL, "=");
		switch( l=strstr(opts, key)-opts ) {
			case 0:
			case 9:
				VKUsage(argv[0]);
				break;
			case 3:
			case 16:
				if( p && *p && VKSetResourceInfo(vk_mopts, p, -1) )
					vk_using = vk_method;
				break;
			case 6:
			case 25:
				if( p && *p ) VKSetResourceInfo(vk_copts, p, -1);
				break;
			default:
			#ifdef XVNKB_TOOL
				if( VKExtraOption )
					l = VKExtraOption(key);
			#endif
				if( l<0 )
					printf("*Error: unknown option %s!\n", argv[n]);
		}
	}

	if( vk_using<VKM_OFF || vk_using>VKM_VIQR )
		vk_using = VKM_VNI;

	if( vk_method<VKM_OFF || vk_method>VKM_VIQR )
		vk_method = VKM_OFF;

	if( vk_method!=VKM_OFF && vk_method!=vk_using )
		vk_using = vk_method;

	vk_charset = vk_charset<0 ? VKC_UTF8 : vk_charset % 6;

	if( !fp ) {
		vk_firstboot = 1;
		vk_using = vk_method = VKM_TELEX;
		vk_charset = VKC_UTF8;
		vk_docking = VKD_ON;
		VKSaveConfig();
	}
}
/*----------------------------------------------------------------------------*/
void VKSaveConfig()
{
	FILE *fp = fopen(vk_config_file, "w+");
	char *vk_config_form =
		"# xvnkb (VISC Key) configuration file.\n"
		"# This file will be automatically updated after each session of xvnkb.\n"
		"#  left: 0 - screenwidth, top: 0 - screenheight --- Icon's position.\n"
		"#  enable: 0-3 ~ (Off,Vni,Telex,Viqr) --- Allow Input method.\n"
		"#  method: 0-3 ~ (Off,Vni,Telex,Viqr) --- Current Input method.\n"
		"#  charset: 0-5 ~ (Tcvn,Vni,Viscii,Vps,Utf8) --- Input charset.\n"
		"#  font: fontname --- Display font (All items of xvnkb - flash,icon,menu).\n"
		"#  interface: 0 - English, 1 - Vietnamese.\n"
		"#  hotkey: use Key Symbols (e.g. Alt Shift_L).\n"
		"left %d\ntop %d\nmethod %d\nenable %d\ncharset %d\nspelling %d\n"
		"interface %d\ndocking %d\n";

	if( !fp )
		printf("Write configuration error!\n");
	else {
		fprintf(fp, vk_config_form,
			vk_x, vk_y,
			vk_method, vk_using,
			vk_charset, vk_spelling, vk_interface, vk_docking);
		if( vk_font_name ) {
			fprintf(fp, "font %s\n", vk_font_name);
			free(vk_font_name);
		}
		if( vk_hotkey ) {
			fprintf(fp, "hotkey %s\n", vk_hotkey);
			free(vk_hotkey);
		}
		fclose(fp);
	}

	if (vk_firstboot)
		vk_firstboot = 0;
	else
		free(vk_config_file);
}
/*----------------------------------------------------------------------------*/
