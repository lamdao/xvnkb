/*----------------------------------------------------------------------------*/
/*  xvnkb_gtk.c                                                               */
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
#ifdef VK_SUPPORT_GTK2
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
/*----------------------------------------------------------------------------*/
#include <glib-object.h>
#include <gtk/gtktypeutils.h>
#include <gtk/gtkentry.h>
#include <gtk/gtktextview.h>
#define GTK_ENABLE_BROKEN
#include <gtk/gtktext.h>
#undef GTK_ENABLE_BROKEN
/*----------------------------------------------------------------------------*/
#include "debug.h"
#include "xvnkb_dll.h"
/*----------------------------------------------------------------------------*/
typedef void (*GtkEditableInit)(GtkEditableClass *iface);
/*----------------------------------------------------------------------------*/
typedef struct {
	GtkType type;
	GtkClassInitFunc init;
	GtkEditableInit editable_init;
	gboolean (*key_press)(GtkWidget *widget, GdkEventKey *event);
	void (*insert_text)(GtkEditable *editable, const gchar *new_text,
						gint new_text_length, gint *position);
	void (*set_position)(GtkEditable *editable, gint position);
	void (*insert_at_cursor)(GtkTextView *, const gchar *);
} GtkHandler;
/*----------------------------------------------------------------------------*/
typedef struct {
	char *name;
	GtkHandler *handler;
	GtkClassInitFunc class_init;
} GtkHandlerInfo;
/*----------------------------------------------------------------------------*/
GtkHandler entry = { 0, 0, 0, 0, 0, 0, 0 };
GtkHandler text = { 0, 0, 0, 0, 0, 0, 0 };
GtkHandler textview = { 0, 0, 0, 0, 0, 0, 0 };
/*----------------------------------------------------------------------------*/
int gtk_1x_app = 0;
/*----------------------------------------------------------------------------*/
/* GtkEntry's handlers                                                        */
/*----------------------------------------------------------------------------*/
static gint xvnkb_entry_key_press(GtkWidget *widget, GdkEventKey *event)
{
	if( !entry.key_press )
		return FALSE;
	if( GTK_ENTRY(widget)->editable && event->keyval==0 ) {
		gint p = GTK_ENTRY(widget)->current_pos;
		if( entry.insert_text ) {
			entry.insert_text(GTK_EDITABLE(widget), event->string,
							strlen(event->string), &p);
			entry.set_position(GTK_EDITABLE(widget), p);
		}
		return TRUE;
	}
	return entry.key_press(widget, event);
}
/*----------------------------------------------------------------------------*/
static void xvnkb_entry_init(GtkEntryClass *class)
{
	if( !entry.init )
		return;
	entry.init(class);
	{
		GtkWidgetClass *widget_class = (GtkWidgetClass *)class;
		entry.key_press = widget_class->key_press_event;
		widget_class->key_press_event = xvnkb_entry_key_press;
		TRACE((stderr, "xvnkb: entry.key_press=%p\n", entry.key_press));
	}
}
/*----------------------------------------------------------------------------*/
static void xvnkb_entry_editable_init(GtkEditableClass *iface)
{
	if( !entry.editable_init )
		return;
	entry.editable_init(iface);
	entry.insert_text = iface->insert_text;
	entry.set_position = iface->set_position;
	TRACE((stderr, "xvnkb: entry.insert_text=%p\n", entry.insert_text));
	TRACE((stderr, "xvnkb: entry.set_position=%p\n", entry.set_position));
}
/*----------------------------------------------------------------------------*/
/* GtkText's handlers                                                         */
/*----------------------------------------------------------------------------*/
static gint xvnkb_text_key_press(GtkWidget *widget, GdkEventKey *event)
{
	if( !text.key_press )
		return FALSE;
	if( GTK_OLD_EDITABLE(GTK_TEXT(widget))->editable && event->keyval==0 ) {
		gint p = gtk_text_get_point(GTK_TEXT(widget));
		if( text.insert_text ) {
			text.insert_text(GTK_EDITABLE(widget), event->string,
									strlen(event->string), &p);
			gtk_text_set_point(GTK_TEXT(widget), p);
		}
		return TRUE;
	}
	return text.key_press(widget, event);
}
/*----------------------------------------------------------------------------*/
static void xvnkb_text_init(GtkTextClass *class)
{
	if( !text.init )
		return;
	TRACE((stderr, "xvnkb: text.init\n"));
	text.init(class);
	{
		GtkWidgetClass *widget_class = (GtkWidgetClass *)class;
		text.key_press = widget_class->key_press_event;
		widget_class->key_press_event = xvnkb_text_key_press;
		TRACE((stderr, "xvnkb: text.key_press=%p\n", text.key_press));
	}
}
/*----------------------------------------------------------------------------*/
static void xvnkb_text_editable_init(GtkEditableClass *iface)
{
	if( !text.editable_init )
		return;
	text.editable_init(iface);
	text.insert_text = iface->insert_text;
	text.set_position = iface->set_position;
	TRACE((stderr, "xvnkb: text.insert_text=%p\n", text.insert_text));
	TRACE((stderr, "xvnkb: text.set_position=%p\n", text.set_position));
}
/*----------------------------------------------------------------------------*/
/* GtkTextView's handlers                                                     */
/*----------------------------------------------------------------------------*/
static gint xvnkb_textview_key_press(GtkWidget *widget, GdkEventKey *event)
{
	if( !textview.key_press )
		return FALSE;
	if( GTK_TEXT_VIEW(widget)->editable && event->keyval==0 ) {
		if( textview.insert_at_cursor )
			textview.insert_at_cursor(GTK_TEXT_VIEW(widget), event->string);
		return TRUE;
	}
	return textview.key_press(widget, event);
}
/*----------------------------------------------------------------------------*/
static void xvnkb_textview_init(GtkTextViewClass *klass)
{
	if( !textview.init )
		return;
	TRACE((stderr, "xvnkb: textview.init\n"));
	textview.init(klass);
	{
		GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
		textview.insert_at_cursor = klass->insert_at_cursor;
		textview.key_press = widget_class->key_press_event;
		widget_class->key_press_event = xvnkb_textview_key_press;
		TRACE((stderr, "xvnkb: textview.key_press=%p\n", textview.key_press));
		TRACE((stderr, "xvnkb: textview.insert_at_cursor=%p\n", textview.insert_at_cursor));
	}
}
/*----------------------------------------------------------------------------*/
char *xvnkb_check_gtk1x_apps()
{
	static int pid = 0;
	static char *gtk_1x_lib = NULL;

	if( !pid ) {
		char s[1024];
		FILE *p;

		pid = getpid();

		sprintf(s, "LD_PRELOAD='' LD_TRACE_LOADED_OBJECTS=1 "
					"/lib/ld-linux.so.2 /proc/%d/exe", pid);
		p = popen(s, "r");
		while( fgets(s, sizeof(s), p) ) {
			static char fp[1024];

			long addr;
			char lib[1024];

			if( sscanf(s, "\t%s => %s (%x)", lib, fp, &addr)!=3 ) continue;
			if( !strncmp(lib, "libgtk-1.", 9) ) {
				gtk_1x_app = 1;
				gtk_1x_lib = fp;
				TRACE((stderr, "%p: %s <=> %s\n", addr, lib, fp));
				break;
			}
		}
		fclose(p);
	}
	return gtk_1x_lib;
}
/*----------------------------------------------------------------------------*/
/* GtkType's handlers                                                         */
/*----------------------------------------------------------------------------*/
GtkType gtk_type_unique(GtkType parent_type, const GtkTypeInfo *gtkinfo)
{
	static GtkType (*f)(GtkType, const GtkTypeInfo *) = 0;
	static GtkHandlerInfo info[] = {
		{ "GtkEntry",    &entry,    (GtkClassInitFunc)xvnkb_entry_init    },
		{ "GtkText",     &text,     (GtkClassInitFunc)xvnkb_text_init     },
		{ "GtkTextView", &textview, (GtkClassInitFunc)xvnkb_textview_init },
		{ 0, 0, 0 }
	};

	if( !f ) {
		char *lib = xvnkb_check_gtk1x_apps();

		if( lib )
			f = get_func_entry(lib, lib, "gtk_type_unique");
		else
			f = get_func_entry("libgtk-x11-2.0.so", "libgtk-x11-2.0.so.0",
														"gtk_type_unique");
		if( !f ) return -1;
	}

	if( !gtk_1x_app && gtkinfo->type_name!=0 ) {
		GtkHandlerInfo *p = info;
		for( ; p->name; p++ )
		if( !strcmp(gtkinfo->type_name, p->name) ) {
			p->handler->init = gtkinfo->class_init_func;
			TRACE((stderr, "xvnkb: %s.init=%p\n", p->name));
			((GtkTypeInfo *)gtkinfo)->class_init_func = p->class_init;
			return p->handler->type = f(parent_type, gtkinfo);
		}
	}

	return f(parent_type, gtkinfo);
}
/*----------------------------------------------------------------------------*/
void g_type_add_interface_static(GType instance_type, GType interface_type,
										const GInterfaceInfo *info)
{
	static void (*f)(GType, GType, const GInterfaceInfo *) = 0;

	if( !f ) {
		char *lib = xvnkb_check_gtk1x_apps();

		if( lib )
			f = get_func_entry(lib, lib, "g_type_add_interface_static");
		else
			f = get_func_entry("libgobject-2.0.so", "libgobject-2.0.so.0",
												"g_type_add_interface_static");
		if( !f ) return;
	}

	if( !gtk_1x_app && interface_type==GTK_TYPE_EDITABLE ) {
		if( entry.type==instance_type ) {
			entry.editable_init = (GtkEditableInit)info->interface_init;
			((GInterfaceInfo *)info)->interface_init = 
								(GInterfaceInitFunc)xvnkb_entry_editable_init;
			TRACE((stderr, "xvnkb: entry.editable_init=%p\n", entry.editable_init));
		}
		else
		if( text.type==instance_type ) {
			text.editable_init = (GtkEditableInit)info->interface_init;
			((GInterfaceInfo *)info)->interface_init = 
								(GInterfaceInitFunc)xvnkb_text_editable_init;
			TRACE((stderr, "xvnkb: text.editable_init=%p\n", text.editable_init));
		}
	}

	f(instance_type, interface_type, info);
}
/*----------------------------------------------------------------------------*/
#endif
