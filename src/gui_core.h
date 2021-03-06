/*
 * gui_core.h
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

#ifndef _GUI_CORE_H_
#define _GUI_CORE_H_

#include <gtk/gtk.h>

#include "core.h"

#define _GUI_CBF(x, y)		(G_CALLBACK(gui__ ## x ## _ ## y))

int gui_init(void);
void gui_cleanup(void);

void gui_quit(gpointer app);

#endif /* _GUI_CORE_H_ */

