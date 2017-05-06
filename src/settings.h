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
#include "tablet.h"

#define SETTINGS_SERIAL_VERSION		0

struct settings {
	struct tablet_points pressure_curve;
	struct settings_area {
		enum {
			AREA_OUTPUT,
			AREA_POINTS,
			AREA_DEFAULT
		} t;

		union {
			const char *output;
			struct tablet_points points;
		} u;
	} area;

	enum tablet_mode mode;
	int tip_feel;
	int double_click_dist;
	int threshold;
	int bind_to_serial;
	int raw_sample;
	int rotation;
	int suppress;
	int cursor_prox;
	int gesture_tap_time;
	int gesture_zoom_dist;
	int gesture_scroll_dist;
	int tablet_debug_level;
	int tool_debug_level;

	bool force_perceptions  : 1;
	bool touch              : 1;
	bool hover              : 1;
	bool hw_touch_switch_st : 1;
	bool pressure_recalib   : 1;
	bool gesture_enabled    : 1;
};

int read_settings(struct settings *st, const char *path);
int write_settings(const struct settings *st, const char *path);

#endif /* _SETTINGS_H_ */

