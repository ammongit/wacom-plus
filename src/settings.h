/*
 * settings.h
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

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <stdbool.h>

#include "core.h"

/*
 * We'll bump this to 1 when we leave the
 * "playing around with serialization" stage
 * and begin the "serious capturing of
 * configuration settings" stage.
 *
 * Until then, the save format is subject to
 * change for any reason at any time.
 */
#define SETTINGS_SERIAL_VERSION		0

struct settings {
	enum hand {
		LEFT,
		RIGHT
	} tablet_orientation;

	unsigned int tip_feel;
	unsigned int double_click_dist;

	bool force_perceptions;
};

int read_settings(struct settings *st, const char *path);
int write_settings(const struct settings *st, const char *path);

#endif /* _SETTINGS_H_ */

