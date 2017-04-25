/*
 * gui_core.c
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

#include "gui_core.h"

int gui_init(void)
{
	/* nothing to do */

	return 0;
}

void gui_cleanup(void)
{
	/* nothing to do */
}

void gui_quit(gpointer app)
{
	GtkWidget *win;
	GList *list;

	list = gtk_application_get_windows(app);
	while (list) {
		win = list->data;
		list = list->next;
		gtk_widget_destroy(GTK_WIDGET(win));
	}
}
