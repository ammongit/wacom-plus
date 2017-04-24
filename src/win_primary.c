/*
 * win_primary.c
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

#include "win_primary.h"

void win__primary_activate(GtkApplication *app, gpointer arg)
{
	GtkWidget *win, *grid;
	GtkWidget *listbox, *ref_btn, *conf_btn;

	UNUSED(arg);

	/* Window */
	win = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(win), "Wacom Plus");
	gtk_window_set_default_size(GTK_WINDOW(win), 600, 700);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);

	/* Listbox */
	listbox = gtk_list_box_new();

	/* Refresh button */
	ref_btn = gtk_button_new_with_label("Refresh");
	g_signal_connect(ref_btn, "clicked", win_primary_refresh, NULL);

	/* Configure button */
	conf_btn = gtk_button_new_with_label("Configure");
	g_signal_connect(conf_btn, "clicked", win_primary_configure, NULL);

	/* Grid placement */
	grid = gtk_grid_new();
	gtk_container_set_border_width(GTK_CONTAINER(grid), 5);
	gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid), FALSE);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_grid_attach(GTK_GRID(grid),
			listbox,
			/* col */ 0,
			/* row */ 0,
			/* width */ 8,
			/* height */ 12);
	gtk_grid_attach(GTK_GRID(grid),
			ref_btn,
			/* col */ 0,
			/* row */ 12,
			/* width */ 4,
			/* height */ 2);
	gtk_grid_attach(GTK_GRID(grid),
			conf_btn,
			/* col */ 4,
			/* row */ 12,
			/* width */ 4,
			/* height */ 2);

	/* Finish */
	gtk_container_add(GTK_CONTAINER(win), grid);
	gtk_widget_show_all(win);
}

void win__primary_refresh(GtkApplication *app, gpointer arg)
{
}

void win__primary_configure(GtkApplication *app, gpointer arg)
{
}

#if 0
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
#endif
