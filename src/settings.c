/*
 * settings.c
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
#include <stdio.h>

#include <xorg/Xwacom.h>
#include <json.h>

#include "settings.h"

#define JSON_ADD(obj, key, n, type)				\
	do {							\
		struct json_object *__wrap_;			\
		__wrap_ = (json_object_new_ ## type)(n);	\
		json_object_object_add((obj), (key), __wrap_);	\
	} while (0)

#define JSON_ADD_OBJ(obj, key, n)				\
	do {							\
		struct json_object *__obj_ = (n);		\
		json_object_object_add((obj), (key), __obj_);	\
	} while (0)

/*-----------*/
/* UTILITIES */
/*-----------*/

static struct json_object *make_meta_obj(void)
{
	struct json_object *obj;

	obj = json_object_new_object();
	JSON_ADD(obj, "version", SETTINGS_SERIAL_VERSION, int);
	return obj;
}

static struct json_object *make_tablet_area_obj(const struct settings_area *area)
{
	struct json_object *obj;

	obj = json_object_new_object();

	switch (area->t) {
	case AREA_OUTPUT:
		JSON_ADD(obj, "type", "output", string);
		JSON_ADD(obj, "output", area->u.output, string);
		break;
	case AREA_POINTS:
		JSON_ADD(obj, "type", "points", string);
		JSON_ADD(obj, "x1", area->u.points.x1, int);
		JSON_ADD(obj, "y1", area->u.points.y1, int);
		JSON_ADD(obj, "x2", area->u.points.x2, int);
		JSON_ADD(obj, "y2", area->u.points.y2, int);
		break;
	case AREA_DEFAULT:
		JSON_ADD(obj, "type", "default", string);
		break;
	default:
		abort();
	}
	return obj;
}

static struct json_object *make_mapping_obj(void)
{
	struct json_object *obj;

	obj = json_object_new_object();
	/* TODO */ JSON_ADD(obj, "TODO", 0, int);
	return obj;
}

static struct json_object *make_points_obj(const struct tablet_points *points)
{
	struct json_object *obj;

	obj = json_object_new_object();
	JSON_ADD(obj, "x1", points->x1, int);
	JSON_ADD(obj, "y1", points->y1, int);
	JSON_ADD(obj, "x2", points->x2, int);
	JSON_ADD(obj, "y2", points->y2, int);
	return obj;
}

static struct json_object *make_gesture_obj(const struct settings *st)
{
	struct json_object *obj;

	obj = json_object_new_object();
	JSON_ADD(obj, "enabled", st->gesture_enabled, boolean);
	if (!st->gesture_enabled)
		return obj;

	JSON_ADD(obj, "tap-time", st->gesture_tap_time, int);
	JSON_ADD(obj, "zoom-distance", st->gesture_zoom_dist, int);
	JSON_ADD(obj, "scroll-distance", st->gesture_scroll_dist, int);
	return obj;
}

static const char *make_mode_str(enum tablet_mode mode)
{
	switch (mode) {
	case MODE_ABSOLUTE:
		return "absolute";
	case MODE_RELATIVE:
		return "relative";
	default:
		abort();
	}
}

static const char *make_rotation_str(int rotation)
{
	switch (rotation) {
	case ROTATE_NONE:
		return "none";
	case ROTATE_CW:
		return "clockwise";
	case ROTATE_CCW:
		return "counter-clockwise";
	case ROTATE_HALF:
		return "half";
	default:
		abort();
	}
}

/*------------*/
/* CONVERSION */
/*------------*/

static struct json_object *to_json(const struct settings *st)
{
	struct json_object *obj;

	obj = json_object_new_object();
	JSON_ADD_OBJ(obj, "meta", make_meta_obj());
	JSON_ADD_OBJ(obj, "tablet-area", make_tablet_area_obj(&st->area));
	JSON_ADD_OBJ(obj, "button-mapping", make_mapping_obj());
	JSON_ADD(obj, "bind-to-serial", st->bind_to_serial, int);
	JSON_ADD(obj, "mode", make_mode_str(st->mode), string);
	JSON_ADD_OBJ(obj, "pressure-curve", make_points_obj(&st->pressure_curve));
	JSON_ADD(obj, "raw-sample", st->raw_sample, int);
	JSON_ADD(obj, "rotation", make_rotation_str(st->rotation), string);
	JSON_ADD(obj, "supress", st->suppress, int);
	JSON_ADD(obj, "tablet-debug-level", st->tablet_debug_level, int);
	JSON_ADD(obj, "hover", st->hover, boolean);
	JSON_ADD(obj, "touch", st->touch, boolean);
	JSON_ADD(obj, "hw-touch-switch-state", st->hw_touch_switch_st, boolean);
	JSON_ADD(obj, "cursor-proximity", st->cursor_prox, int);
	JSON_ADD(obj, "threshold", st->threshold, int);
	JSON_ADD(obj, "tool-debug-level", st->tool_debug_level, int);
	JSON_ADD(obj, "pressure-recalibration", st->pressure_recalib, boolean);
	JSON_ADD_OBJ(obj, "gesture", make_gesture_obj(st));
	return obj;
}

/* TODO */
static int from_json(struct settings *st, const struct json_object *obj);

/*-----------*/
/* EXTERNALS */
/*-----------*/

/* TODO */
int read_settings(struct settings *st, const char *path);

int write_settings(const struct settings *st, const char *path)
{
	FILE *fh;
	struct json_object *obj;

	obj = to_json(st);
	if (!obj) {
		/* last_err_str already set */
		return -1;
	}

	fh = fopen(path, "w");
	if (!fh) {
		last_err_str = "Unable to open settings file for reading";
		return -1;
	}
	if (fputs(json_object_to_json_string(obj), fh) == EOF) {
		last_err_str = "Unable to write to settings file";
		return -1;
	}
	fclose(fh);
	return 0;
}
