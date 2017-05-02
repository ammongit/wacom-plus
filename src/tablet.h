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

int tablet_obj_init(void);
void tablet_obj_cleanup(void);


union tablet_argument {
	struct {
		unsigned int x1, y1;
		unsigned int x2, y2;
	} points;

	struct {
		const char *num;
		const char *map;
		/* TODO? */
	} mapping;

	enum {
		MODE_ABSOLUTE,
		MODE_RELATIVE
	} mode;

	const char *str;
	long num;
	Bool boolean;
	XID xid;
};

/*
 * Order matters, since it corresponds to the
 * "parameters" struct in tablet.c
 */
enum tablet_parameter {
	PARAM_TABLET_AREA,		/* points */
	PARAM_BUTTON_MAPPING,		/* mapping */
	PARAM_BIND_TO_SERIAL,		/* num */
	PARAM_MAP_OUTPUT,		/* str */
	PARAM_MODE,			/* mode */
	PARAM_PRESSURE_CURVE,		/* points */
	PARAM_RAW_SAMPLE,		/* num */
	PARAM_ROTATION,			/* num */
	PARAM_SUPPRESS,			/* num */
	PARAM_TABLET_DEBUG_LEVEL,	/* num */
	PARAM_HOVER,			/* boolean */
	PARAM_SERIAL_PREVIOUS,		/* boolean */
	PARAM_TOUCH,			/* boolean */
	PARAM_HW_TOUCH_SWITCH_STATE,	/* boolean */
	PARAM_CURSOR_PROXIMITY,		/* num */
	PARAM_THRESHOLD,		/* num */
	PARAM_TOOL_DEBUG_LEVEL,		/* num */
	PARAM_PRESSURE_RECALIBRATION,	/* boolean */
	PARAM_GESTURE_ENABLED,		/* boolean */
	PARAM_GESTURE_TAP_TIME,		/* num */
	PARAM_GESTURE_ZOOM_DIST,	/* num */
	PARAM_GESTURE_SCROLL_DIST,	/* num */
	PARAM_WHEEL_UP_MAPPING,		/* mapping */
	PARAM_WHEEL_DOWN_MAPPING,	/* mapping */
	PARAM_ABS_WHEEL_UP_MAPPING,	/* mapping */
	PARAM_ABS_WHEEL_DOWN_MAPPING,	/* mapping */
	PARAM_ABS_WHEEL2_UP_MAPPING,	/* mapping */
	PARAM_ABS_WHEEL2_DOWN_MAPPING,	/* mapping */
	PARAM_STRIP_LEFT_UP_MAPPING,	/* mapping */
	PARAM_STRIP_LEFT_DOWN_MAPPING,	/* mapping */
	PARAM_STRIP_RIGHT_UP_MAPPING,	/* mapping */
	PARAM_STRIP_RIGHT_DOWN_MAPPING,	/* mapping */
	PARAM_RESET_AREA,		/* (none) */
	PARAM_TOOL_TYPE,		/* xid */
	PARAM_TOOL_SERIAL,		/* xid */
	PARAM_TOOL_ID,			/* xid */
	PARAM_TABLET_ID,		/* xid */

	NUM_PARAMS
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
			 const union tablet_argument *val);
int tablet_get_parameter(const struct tablet *tablet,
			 enum tablet_parameter param,
			 union tablet_argument *val);

#endif /* _TABLET_H_ */

