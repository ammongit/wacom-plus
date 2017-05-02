/*
 * tablet.h
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

#ifndef _TABLET_H_
#define _TABLET_H_

#include "tablet_core.h"

struct tablet_points {
	unsigned int x1, y1;
	unsigned int x2, y2;
};

struct button_mapping {
	const char *num;
	const char *map;
};

enum tablet_mode {
	MODE_ABSOLUTE,
	MODE_RELATIVE
};

enum tablet_rotation {
	TBL_ROTATE_NONE, /* No rotation */
	TBL_ROTATE_HALF, /* Rotated by 180 degrees (upside-down) */
	TBL_ROTATE_CW,   /* Rotate 90 degrees clockwise */
	TBL_ROTATE_CCW   /* Rotate 90 degrees counter-clockwise */
};

union tablet_argument {
	struct tablet_points area;
	struct button_mapping btn_map;
	const char *serial;
	const char *output;
	enum tablet_mode mode;
	struct tablet_points bez_curve;
	unsigned short raw_sample;
	enum tablet_rotation rotation;
	unsigned short suppress;
	unsigned short debug_level;
	Bool hover; /* TabletPCButton */
	Bool serial_prev;
	Bool touch;
	Bool hw_touch_st;
	unsigned short cursor_proximity;
	unsigned short threshold;
	unsigned short tool_debug_level;
	Bool pressure_recalib;
	Bool gestures;
	unsigned short gesture_tap_time;
	unsigned short gesture_zoom_dist;
	unsigned short gesture_scroll_dist;
	struct button_mapping rel_wh_up;
	struct button_mapping rel_wh_down;
	struct button_mapping abs_wh_up;
	struct button_mapping abs_wh_down;
	struct button_mapping strip_left_up;
	struct button_mapping strip_left_down;
	struct button_mapping strip_right_up;
	struct button_mapping strip_right_down;
	/* reset_area has no fields */
	XID tool_type;
	XID tool_serial;
	XID tool_id;
	XID tablet_id;
};

/*
 * Order matters, since it corresponds to the
 * "parameters" struct in tablet.c
 */
enum tablet_parameter {
	PARAM_TABLET_AREA,
	PARAM_BUTTON_MAPPING,
	PARAM_BIND_TO_SERIAL,
	PARAM_MAP_OUTPUT,
	PARAM_MODE,
	PARAM_PRESSURE_CURVE,
	PARAM_RAW_SAMPLE,
	PARAM_ROTATION,
	PARAM_SUPPRESS,
	PARAM_TABLET_DEBUG_LEVEL,
	PARAM_HOVER,
	PARAM_SERIAL_PREVIOUS,
	PARAM_TOUCH,
	PARAM_HW_TOUCH_SWITCH_STATE,
	PARAM_CURSOR_PROXIMITY,
	PARAM_THRESHOLD,
	PARAM_TOOL_DEBUG_LEVEL,
	PARAM_PRESSURE_RECALIBRATION,
	PARAM_GESTURE_ENABLED,
	PARAM_GESTURE_TAP_TIME,
	PARAM_GESTURE_ZOOM_DIST,
	PARAM_GESTURE_SCROLL_DIST,
	PARAM_WHEEL_UP_MAPPING,
	PARAM_WHEEL_DOWN_MAPPING,
	PARAM_ABS_WHEEL_UP_MAPPING,
	PARAM_ABS_WHEEL_DOWN_MAPPING,
	PARAM_ABS_WHEEL2_UP_MAPPING,
	PARAM_ABS_WHEEL2_DOWN_MAPPING,
	PARAM_STRIP_LEFT_UP_MAPPING,
	PARAM_STRIP_LEFT_DOWN_MAPPING,
	PARAM_STRIP_RIGHT_UP_MAPPING,
	PARAM_STRIP_RIGHT_DOWN_MAPPING,
	PARAM_RESET_AREA,
	PARAM_TOOL_TYPE,
	PARAM_TOOL_SERIAL,
	PARAM_TOOL_ID,
	PARAM_TABLET_ID
};

struct tablet {
	Display *dpy;
	XDevice *dev;
};

int tablet_open(struct tablet *tablet,
		Display *dpy,
		XID id);
void tablet_close(struct tablet *tablet);

int tablet_set_parameter(struct tablet *tablet,
			 enum tablet_parameter param,
			 const union tablet_argument *arg);
int tablet_get_parameter(const struct tablet *tablet,
			 enum tablet_parameter param,
			 union tablet_argument *arg);

#endif /* _TABLET_H_ */

