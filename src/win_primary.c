/*
 * win_primary.c
 *
 * wacom-plus - A simple QOTD daemon.
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

#include "win_primary.h"

void win__primary_activate(GtkApplication *app, gpointer arg)
{
	GtkWidget *win, *row1, *row2, *col;
	GtkWidget *listbox, *ref_btn, *conf_btn;
	GtkWidget *abt_btn, *close_btn;

	UNUSED(arg);

	/* Window */
	win = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(win), "Wacom Plus");
	gtk_window_set_default_size(GTK_WINDOW(win), 600, 700);

	/* Listbox */
	listbox = gtk_list_box_new();

	/* Refresh button */
	ref_btn = gtk_button_new_with_label("Refresh");
	g_signal_connect(ref_btn, "clicked", win_primary_refresh, NULL);

	/* Configure button */
	conf_btn = gtk_button_new_with_label("Configure");
	g_signal_connect(conf_btn, "clicked", win_primary_configure, NULL);

	/* About button */
	abt_btn = gtk_button_new_from_stock(GTK_STOCK_ABOUT);
	g_signal_connect(abt_btn, "clicked", win_primary_about, NULL);

	/* Close button */
	close_btn = gtk_button_new_from_stock(GTK_STOCK_CLOSE);
	g_signal_connect(close_btn, "clicked", win_primary_close, NULL);

	/* Listbox buttons */
	row1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(row1), ref_btn);
	gtk_container_add(GTK_CONTAINER(row1), conf_btn);
	gtk_widget_set_halign(row1, GTK_ALIGN_CENTER);

	/* Window buttons */
	row2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(row2), abt_btn);
	gtk_container_add(GTK_CONTAINER(row2), close_btn);
	gtk_widget_set_halign(row2, GTK_ALIGN_END);

	/* Primary column */
	col = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(col), listbox);
	gtk_container_add(GTK_CONTAINER(col), row1);
	gtk_container_add(GTK_CONTAINER(col), row2);
	gtk_widget_set_halign(col, GTK_ALIGN_CENTER);

	/* Finish */
	gtk_container_add(GTK_CONTAINER(win), col);
	gtk_widget_show_all(win);
}

void win__primary_refresh(GtkApplication *app, gpointer arg)
{
}

void win__primary_configure(GtkApplication *app, gpointer arg)
{
}

void win__primary_about(GtkApplication *app, gpointer arg)
{
	GtkWidget *win;

	/* Window */
	win = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(win), "About Wacom Plus");
	gtk_window_set_default_size(GTK_WINDOW(win), 350, 500);

	/* Finish */
	gtk_widget_show_all(win);
}

void win__primary_close(GtkApplication *app, gpointer arg)
{
	UNUSED(app);
	UNUSED(arg);

	exit(EXIT_SUCCESS);
}
