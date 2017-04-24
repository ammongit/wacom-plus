/*
 * win_primary.h
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

#ifndef _WIN_PRIMARY_H_
#define _WIN_PRIMARY_H_

#include "win_core.h"

void win__primary_activate(GtkApplication *app, gpointer arg);
void win__primary_refresh(GtkApplication *app, gpointer arg);
void win__primary_configure(GtkApplication *app, gpointer arg);
void win__primary_about(GtkApplication *app, gpointer arg);
void win__primary_close(GtkApplication *app, gpointer arg);

#define win_primary_activate	_CBF(primary, activate)
#define win_primary_refresh	_CBF(primary, refresh)
#define win_primary_configure	_CBF(primary, configure)
#define win_primary_about	_CBF(primary, about)
#define win_primary_close	_CBF(primary, close)

#endif /* _WIN_PRIMARY_H_ */

