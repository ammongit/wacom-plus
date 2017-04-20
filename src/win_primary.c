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

#include "core.h"
#include "win_primary.h"

void win__primary_activate(GtkApplication *app, gpointer arg)
{
	GtkWidget *win, *row1, *row2, *col;
	GtkWidget *listbox, *ref_btn, *conf_btn;
	GtkWidget *abt_btn, *close_btn;

	UNUSED(arg);

	/* Listbox */
	listbox = NULL;

	/* Refresh button */
	ref_btn = NULL;

	/* Configure button */
	conf_btn = NULL;

	/* About button */
	abt_btn = NULL;

	/* Close button */
	close_btn = NULL;

	/* Window */
	win = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(win), "Wacom Plus");
	gtk_window_set_default_size(GTK_WINDOW(win), 600, 700);

	/* Listbox buttons */
	row1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(row1), ref_btn);
	gtk_container_add(GTK_CONTAINER(row1), conf_btn);

	/* Window buttons */
	row2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_add(GTK_CONTAINER(row2), abt_btn);
	gtk_container_add(GTK_CONTAINER(row2), close_btn);

	/* Primary column */
	col = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_add(GTK_CONTAINER(col), listbox);
	gtk_container_add(GTK_CONTAINER(col), row1);
	gtk_container_add(GTK_CONTAINER(col), row2);

	gtk_widget_show_all(win);
}
