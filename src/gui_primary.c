/*
 * gui_primary.c
 *
 * wacom-plus - Linux GUI configuration for Wacom tablets
 * Copyright (c) 2015-2016 Ammon Smith
 *
 * wacom-plus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * wacom-plus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with wacom-plus.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdlib.h>

#include "gui_primary.h"

/* Menus */
static void submenu_append(const char *label, GtkWidget *menu)
{
	GtkWidget *menu_item;

	menu_item = gtk_menu_item_new_with_label(label);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
	gtk_widget_show(menu_item);
}

static GtkWidget *make_file_menu(void)
{
	GtkWidget *menu;

	menu = gtk_menu_new();
	submenu_append("New...", menu);
	submenu_append("Open...", menu);
	submenu_append("Save", menu);
	submenu_append("Save As...", menu);
	submenu_append("Close", menu);
	submenu_append("Quit", menu);
	return menu;
}

static GtkWidget *make_help_menu(void)
{
	GtkWidget *menu;

	menu = gtk_menu_new();
	submenu_append("Help", menu);
	submenu_append("About", menu);
	return menu;
}

static void menu_append(const char *label, GtkMenuShell *shell, GtkWidget *menu)
{
	GtkWidget *menu_item;

	menu_item = gtk_menu_item_new_with_label(label);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), menu);
	gtk_menu_shell_append(shell, menu_item);
	gtk_widget_show(menu_item);
}

static GtkWidget *make_menu_bar(void)
{
	GtkWidget *menu_bar;

	menu_bar = gtk_menu_bar_new();
	gtk_widget_set_hexpand(menu_bar, TRUE);

	menu_append("File", GTK_MENU_SHELL(menu_bar), make_file_menu());
	menu_append("Help", GTK_MENU_SHELL(menu_bar), make_help_menu());
	return menu_bar;
}

/* Externals */
void gui__primary_activate(GtkApplication *app, gpointer arg)
{
	GtkWidget *win, *box, *menu_bar;

	UNUSED(arg);

	/* Window */
	win = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(win), "Wacom Plus");
	gtk_window_set_default_size(GTK_WINDOW(win), 700, 850);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	g_signal_connect(win, "destroy", gui_primary_destroy, win);

	/* Box */
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(win), box);
	gtk_widget_show(box);

	/* Menu Bar */
	menu_bar = make_menu_bar();
	gtk_box_pack_start(GTK_BOX(box), menu_bar, FALSE, FALSE, 0);
	gtk_widget_show(menu_bar);

	/* Finish */
	gtk_widget_show(win);
}

void gui__primary_destroy(GtkApplication *app, gpointer arg)
{
	UNUSED(app);
	UNUSED(arg);
}

void gui__primary_open(GtkApplication *app, gpointer arg)
{
}

void gui__primary_saveas(GtkApplication *app, gpointer arg)
{
}

void gui__primary_about(GtkApplication *app, gpointer arg)
{
	GtkWidget *win;

	/* Window */
	win = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(win), "About Wacom Plus");
	gtk_window_set_default_size(GTK_WINDOW(win), 350, 500);

	/* Finish */
	gtk_widget_show_all(win);
}
