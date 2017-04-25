/*
 * gui_primary.h
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

#ifndef _GUI_PRIMARY_H_
#define _GUI_PRIMARY_H_

#include "gui_core.h"

void gui__primary_activate(GtkApplication *app, gpointer arg);
void gui__primary_refresh(GtkApplication *app, gpointer arg);
void gui__primary_configure(GtkApplication *app, gpointer arg);
void gui__primary_about(GtkApplication *app, gpointer arg);
void gui__primary_close(GtkApplication *app, gpointer arg);

#define gui_primary_activate		_GUI_CBF(primary, activate)
#define gui_primary_refresh		_GUI_CBF(primary, refresh)
#define gui_primary_configure		_GUI_CBF(primary, configure)
#define gui_primary_about		_GUI_CBF(primary, about)
#define gui_primary_close		_GUI_CBF(primary, close)

#endif /* _GUI_PRIMARY_H_ */

