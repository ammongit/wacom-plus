/*
 * tablet_core.h
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

#ifndef _TABLET_CORE_H_
#define _TABLET_CORE_H_

#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>

#include "core.h"

int tablet_core_init(void);
void tablet_core_cleanup(void);

/*
 * Refreshes the internal list of Wacom devices.
 * This is not performed by tablet_init()
 */
int tablet_refresh_list(void);

typedef int (*tablets_device_list_cbf)(
		void *arg,
		XID id,
		const char *name,
		Atom type);

int tablets_device_iterate(Display *dpy,
			   tablets_device_list_cbf cbf,
			   void *arg);

#endif /* _TABLET_CORE_H_ */

