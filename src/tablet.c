/*
 * tablet.c
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

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <xorg/Xwacom.h>
#include <xorg/wacom-properties.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xinerama.h>

#include "tablet.h"

#define X11_DEV_BUFFER_LENGTH	1000

/*------*/
/* DATA */
/*------*/

static struct param {
	const char *x11_name;
	const char *prop_name;
	unsigned short prop_format;
	unsigned short prop_offset;
	bool readonly  : 1;
	bool writeonly : 1;
} parameters[] = {
	{
		/* PARAM_TABLET_AREA */
		"Area",
		WACOM_PROP_TABLET_AREA,
		32,
		0,
		False,
		False,
	},
	{
		/* PARAM_BUTTON_MAPPING */
		"Button",
		WACOM_PROP_BUTTON_ACTIONS,
		0,
		0,
		False,
		False,
	},
	{
		/* PARAM_BIND_TO_SERIAL */
		"Serial",
		WACOM_PROP_SERIAL_BIND,
		32,
		0,
		False,
		False,
	},
	{
		/* PARAM_MAP_OUTPUT */
		"MapToOutput",
		NULL,
		0,
		0,
		False,
		True,
	},
	{
		/* PARAM_MODE */
		"Mode",
		NULL,
		0,
		0,
		False,
		False,
	},
	{
		/* PARAM_PRESSURE_CURVE */
		"PressCurve",
		WACOM_PROP_PRESSURECURVE,
		32,
		0,
		False,
		False,
	},
	{
		/* PARAM_RAW_SAMPLE */
		"RawSample",
		WACOM_PROP_SAMPLE,
		32,
		1,
		False,
		False,
	},
	{
		/* PARAM_ROTATION */
		"Rotate",
		WACOM_PROP_ROTATION,
		0,
		0,
		False,
		False,
	},
	{
		/* PARAM_SUPPRESS */
		"Suppress",
		WACOM_PROP_SAMPLE,
		32,
		0,
		False,
		False,
	},
	{
		/* PARAM_TABLET_DEBUG_LEVEL */
		"CommonDBG",
		WACOM_PROP_DEBUGLEVELS,
		8,
		1,
		False,
		False,
	},
	{
		/* PARAM_HOVER */
		"TPCButton",
		WACOM_PROP_HOVER,
		8,
		0,
		False,
		False,
	},
	{
		/* PARAM_SERIAL_PREVIOUS */
		"ToolSerialPrevious",
		WACOM_PROP_SERIALIDS,
		32,
		1,
		True,
		False,
	},
	{
		/* PARAM_TOUCH */
		"Touch",
		WACOM_PROP_TOUCH,
		8,
		0,
		False,
		False,
	},
	{
		/* PARAM_HW_TOUCH_SWITCH_STATE */
		"HWTouchSwitchState",
		WACOM_PROP_HARDWARE_TOUCH,
		8,
		0,
		True,
		False,
	},
	{
		/* PARAM_CURSOR_PROXIMITY */
		"CursorProx",
		WACOM_PROP_PROXIMITY_THRESHOLD,
		32,
		0,
		False,
		False,
	},
	{
		/* PARAM_THRESHOLD */
		"Threshold",
		WACOM_PROP_PRESSURE_THRESHOLD,
		32,
		0,
		False,
		False,
	},
	{
		/* PARAM_TOOL_DEBUG_LEVEL */
		"DebugLevel",
		WACOM_PROP_DEBUGLEVELS,
		8,
		0,
		False,
		False,
	},
	{
		/* PARAM_PRESSURE_RECALIBRATION */
		"PressureRecalibration",
		WACOM_PROP_PRESSURE_RECAL,
		8,
		0,
		False,
		False,
	},
	{
		/* PARAM_GESTURE_ENABLED */
		"Gesture",
		WACOM_PROP_ENABLE_GESTURE,
		8,
		0,
		False,
		False,
	},
	{
		/* PARAM_GESTURE_TAP_TIME */
		"TapTime",
		WACOM_PROP_GESTURE_PARAMETERS,
		32,
		2,
		False,
		False,
	},
	{
		/* PARAM_GESTURE_ZOOM_DIST */
		"ZoomDistance",
		WACOM_PROP_GESTURE_PARAMETERS,
		32,
		0,
		False,
		False,
	},
	{
		/* PARAM_GESTURE_SCROLL_DIST */
		"ScrollDistance",
		WACOM_PROP_GESTURE_PARAMETERS,
		32,
		1,
		False,
		False,
	},
	{
		/* PARAM_WHEEL_UP_MAPPING */
		"RelWheelUp",
		WACOM_PROP_WHEELBUTTONS,
		8,
		0,
		False,
		False,
	},
	{
		/* PARAM_WHEEL_DOWN_MAPPING */
		"RelWheelDown",
		WACOM_PROP_WHEELBUTTONS,
		8,
		1,
		False,
		False,
	},
	{
		/* PARAM_ABS_WHEEL_UP_MAPPING */
		"AbsWheelUp",
		WACOM_PROP_WHEELBUTTONS,
		8,
		2,
		False,
		False,
	},
	{
		/* PARAM_ABS_WHEEL_DOWN_MAPPING */
		"AbsWheelDown",
		WACOM_PROP_WHEELBUTTONS,
		8,
		3,
		False,
		False,
	},
	{
		/* PARAM_ABS_WHEEL2_UP_MAPPING */
		"AbsWheel2Up",
		WACOM_PROP_WHEELBUTTONS,
		8,
		4,
		False,
		False,
	},
	{
		/* PARAM_ABS_WHEEL2_DOWN_MAPPING */
		"AbsWheel2Down",
		WACOM_PROP_WHEELBUTTONS,
		8,
		5,
		False,
		False,
	},
	{
		/* PARAM_STRIP_LEFT_UP_MAPPING */
		"StripLeftUp",
		WACOM_PROP_STRIPBUTTONS,
		8,
		0,
		False,
		False,
	},
	{
		/* PARAM_STRIP_LEFT_DOWN_MAPPING */
		"StripLeftDown",
		WACOM_PROP_STRIPBUTTONS,
		8,
		1,
		False,
		False,
	},
	{
		/* PARAM_STRIP_RIGHT_UP_MAPPING */
		"StripRightUp",
		WACOM_PROP_STRIPBUTTONS,
		8,
		2,
		False,
		False,
	},
	{
		/* PARAM_STRIP_RIGHT_DOWN_MAPPING */
		"StripRightDown",
		WACOM_PROP_STRIPBUTTONS,
		8,
		3,
		False,
		False,
	},
	{
		/* PARAM_RESET_AREA */
		"ResetArea",
		WACOM_PROP_TABLET_AREA,
		32,
		0,
		False,
		True,
	},
	{
		/* PARAM_TOOL_TYPE */
		"ToolType",
		WACOM_PROP_TOOL_TYPE,
		32,
		0,
		True,
		False,
	},
	{
		/* PARAM_TOOL_SERIAL */
		"ToolSerial",
		WACOM_PROP_SERIALIDS,
		32,
		3,
		True,
		False,
	},
	{
		/* PARAM_TOOL_ID */
		"ToolID",
		WACOM_PROP_SERIALIDS,
		32,
		4,
		True,
		False,
	},
	{
		/* PARAM_TABLET_ID */
		"TabletID",
		WACOM_PROP_SERIALIDS,
		32,
		0,
		True,
		False,
	},
};

/*-----------*/
/* UTILITIES */
/*-----------*/

static Bool test_property(const struct tablet *tablet, Atom prop)
{
	Atom *properties;
	Bool found;
	int i, nprops;

	if (!prop)
		return True;

	properties = XListDeviceProperties(tablet->dpy,
					   tablet->dev,
					   &nprops);
	assert(properties);

	found = False;
	for (i = 0; i < nprops; i++) {
		if (properties[i] == prop) {
			found = True;
			break;
		}
	}

	XFree(properties);
	return found;
}

static Bool need_xinerama(Display *dpy)
{
	int opcode, event, error;
	int major, minor;

	if (!XQueryExtension(dpy, "RANDR", &opcode, &event, &error))
		return True;
	if (!XRRQueryVersion(dpy, &major, &minor)) {
		if ((major * 1000 + minor) < 1002) {
			return True;
		}
	}
	if (XQueryExtension(dpy, "NV-CONTROL", &opcode, &event, &error))
		return True;
	return False;
}

static const struct param *get_param(const struct tablet *tablet,
				     enum tablet_parameter param_e,
				     Atom *prop)
{
	const struct param *param;

	assert(param_e >= NUM_PARAMS);

	param = &parameters[param_e];
	if (param->prop_name) {
		*prop = XInternAtom(tablet->dpy, param->prop_name, True);
		if (!prop || !test_property(tablet, *prop))
			return NULL;
	} else {
		prop = None;
	}
	return param;
}

static void write_prop(const struct param *param,
		       unsigned char *data,
		       size_t index,
		       long val)
{
	union {
		char *bytes;
		long *longs;
	} u;

	switch (param->prop_format) {
	case 8:
		u.bytes = (char *)data;
		u.bytes[param->prop_offset + index] = val;
		break;
	case 32:
		u.longs = (long *)data;
		u.longs[param->prop_offset + index] = val;
		break;
	}
}

static long read_prop(const struct param *param,
		      const unsigned char *data,
		      size_t index)
{
	union {
		const char *bytes;
		const long *longs;
	} u;

	switch (param->prop_format) {
	case 8:
		u.bytes = (const char *)data;
		return u.bytes[param->prop_offset + index];
	case 32:
		u.longs = (const long *)data;
		return u.longs[param->prop_offset + index];
	}
	assert(0);
	return -1;
}

/* Assumes "matrix" is exactly length 9 */
static int set_matrix_prop(const struct tablet *tablet,
			   float *fmatrix)
{
	Atom matrix_prop, type;
	long matrix[9] = {0};
	float *data;
	unsigned long nitems, bytes_after;
	int format;
	size_t i;

	matrix_prop = XInternAtom(tablet->dpy,
				  "Coordinate Transformation Matrix",
				  True);
	if (!matrix_prop)
		return -1;

	for (i = 0; i < 9; i++) {
		union {
			long l;
			float f;
		} u;

		u.f = fmatrix[i];
		matrix[i] = u.l;
	}

	if (XGetDeviceProperty(tablet->dpy,
			       tablet->dev,
			       matrix_prop,
			       0,
			       9,
			       False,
			       AnyPropertyType,
			       &type,
			       &format,
			       &nitems,
			       &bytes_after,
			       (unsigned char **)(&data)))
		return -1;

	assert(format == 32);
	assert(type == XInternAtom(tablet->dpy, "FLOAT", True));

	XChangeDeviceProperty(tablet->dpy,
			      tablet->dev,
			      matrix_prop,
			      type,
			      format,
			      PropModeReplace,
			      (unsigned char *)matrix,
			      9);
	XFree(data);
	XFlush(tablet->dpy);
	return 0;
}

static int set_output_area(const struct tablet *tablet,
			   int off_x,
			   int off_y,
			   int out_width,
			   int out_height)
{
	int width, height;
	float x, y, w, h;
	float matrix[9] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};

	width = DisplayWidth(tablet->dpy, DefaultScreen(tablet->dpy));
	height = DisplayHeight(tablet->dpy, DefaultScreen(tablet->dpy));
	x = 1.0 * off_x / width;
	y = 1.0 * off_y / height;
	w = 1.0 * out_width / width;
	h = 1.0 * out_height / height;

	matrix[2] = x;
	matrix[5] = y;
	matrix[0] = w;
	matrix[4] = h;

	return set_matrix_prop(tablet, matrix);
}

static int set_output_xrandr(const struct tablet *tablet,
			     const char *output)
{
	int x, y, width, height;
	int i, ret;
	XRRScreenResources *res;
	XRROutputInfo *output_info;
	XRRCrtcInfo *crtc_info;

	res = XRRGetScreenResources(tablet->dpy,
				    DefaultRootWindow(tablet->dpy));
	for (i = 0; i < res->noutput; i++) {
		output_info = XRRGetOutputInfo(tablet->dpy,
					       res,
					       res->outputs[i]);
		if (!output_info->crtc ||
		     output_info->connection != RR_Connected)
			continue;

		crtc_info = XRRGetCrtcInfo(tablet->dpy,
					   res,
					   output_info->crtc);
		x = crtc_info->x;
		y = crtc_info->y;
		width = crtc_info->width;
		height = crtc_info->height;
		XRRFreeCrtcInfo(crtc_info);

		if (!strcmp(output_info->name, output)) {
			ret = set_output_area(tablet, x, y, width, height);
			goto end;
		}
	}
	ret = -1;
end:
	XRRFreeScreenResources(res);
	return ret;
}

static int set_output_xinerama(const struct tablet *tablet,
			       int head)
{
	XineramaScreenInfo *screens;
	int event, error, nscreens, ret;

	if (!XineramaQueryExtension(tablet->dpy,
				    &event,
				    &error))
		return -1;

	screens = XineramaQueryScreens(tablet->dpy, &nscreens);
	if (!nscreens || nscreens <= head) {
		ret = -1;
		goto end;
	}

	ret = set_output_area(tablet,
			      screens[head].x_org,
			      screens[head].y_org,
			      screens[head].width,
			      screens[head].height);
end:
	XFree(screens);
	return ret;
}

static int set_output(const struct tablet *tablet,
		      const char *output)
{
	if (need_xinerama(tablet->dpy)) {
		char *ptr;
		int head;

		if (strncasecmp(output, "HEAD-", 5))
			return -1;
		output += 5;
		head = strtol(output, &ptr, 10);
		if (!*output || *ptr)
			return -1;

		return set_output_xinerama(tablet, head);
	} else {
		return set_output_xrandr(tablet, output);
	}
}

/*-----------*/
/* EXTERNALS */
/*-----------*/

int tablet_obj_init(void)
{
	STATIC_ASSERT(ARRAY_SIZE(parameters) == NUM_PARAMS);
	STATIC_ASSERT(NUM_PARAMS == 37);

	return 0;
}

void tablet_obj_cleanup(void)
{
	/* nothing to do */
}

int tablet_open(struct tablet *tablet, Display *dpy, XID id)
{
	XDevice *dev;

	dev = XOpenDevice(dpy, id);
	if (!dev)
		return -1;

	tablet->dpy = dpy;
	tablet->dev = dev;
	return 0;
}

void tablet_close(struct tablet *tablet)
{
	XCloseDevice(tablet->dpy, tablet->dev);
}

int tablet_set_parameter(struct tablet *tablet,
			 enum tablet_parameter param_e,
			 const union tablet_argument *val)
{
	const struct param *param;
	Atom prop, type;
	unsigned char *data;
	unsigned long nitems, bytes_after;
	int ret, format;

	param = get_param(tablet, param_e, &prop);
	if (!param)
		return -1;

	if (XGetDeviceProperty(tablet->dpy,
			       tablet->dev,
			       prop,
			       0,
			       X11_DEV_BUFFER_LENGTH,
			       False,
			       AnyPropertyType,
			       &type,
			       &format,
			       &nitems,
			       &bytes_after,
			       &data)) {
		ret = -1;
		goto end;
	}
	if (nitems <= param->prop_offset) {
		ret = -1;
		goto end;
	}

	if (format != param->prop_format || type != XA_INTEGER) {
		ret = -1;
		goto end;
	}

	switch (param_e) {
	case PARAM_TABLET_AREA:
	case PARAM_PRESSURE_CURVE:
		write_prop(param, data, 0, val->points.x1);
		write_prop(param, data, 1, val->points.y1);
		write_prop(param, data, 2, val->points.x2);
		write_prop(param, data, 3, val->points.y2);
		break;
	case PARAM_BUTTON_MAPPING:
	case PARAM_WHEEL_UP_MAPPING:
	case PARAM_WHEEL_DOWN_MAPPING:
	case PARAM_ABS_WHEEL_UP_MAPPING:
	case PARAM_ABS_WHEEL_DOWN_MAPPING:
	case PARAM_ABS_WHEEL2_UP_MAPPING:
	case PARAM_ABS_WHEEL2_DOWN_MAPPING:
	case PARAM_STRIP_LEFT_UP_MAPPING:
	case PARAM_STRIP_LEFT_DOWN_MAPPING:
	case PARAM_STRIP_RIGHT_UP_MAPPING:
	case PARAM_STRIP_RIGHT_DOWN_MAPPING:
		/* TODO set_map() */
		break;
	case PARAM_MAP_OUTPUT:
		set_output(tablet, val->str);
		break;
	case PARAM_MODE:
		write_prop(param, data, 0, val->mode);
		break;
	case PARAM_BIND_TO_SERIAL:
	case PARAM_RAW_SAMPLE:
	case PARAM_ROTATION:
	case PARAM_SUPPRESS:
	case PARAM_TABLET_DEBUG_LEVEL:
	case PARAM_CURSOR_PROXIMITY:
	case PARAM_THRESHOLD:
	case PARAM_TOOL_DEBUG_LEVEL:
	case PARAM_GESTURE_TAP_TIME:
	case PARAM_GESTURE_ZOOM_DIST:
	case PARAM_GESTURE_SCROLL_DIST:
		write_prop(param, data, 0, val->num);
		break;
	case PARAM_HOVER:
	case PARAM_SERIAL_PREVIOUS:
	case PARAM_TOUCH:
	case PARAM_HW_TOUCH_SWITCH_STATE:
	case PARAM_PRESSURE_RECALIBRATION:
	case PARAM_GESTURE_ENABLED:
		write_prop(param, data, 0, val->boolean);
		break;
	case PARAM_TOOL_TYPE:
	case PARAM_TOOL_SERIAL:
	case PARAM_TOOL_ID:
	case PARAM_TABLET_ID:
		write_prop(param, data, 0, val->xid);
		break;
	case PARAM_RESET_AREA:
	case NUM_PARAMS:
		/* do nothing */
		break;
	}

	XChangeDeviceProperty(tablet->dpy,
			      tablet->dev,
			      prop,
			      type,
			      format,
			      PropModeReplace,
			      data,
			      nitems);
	XFlush(tablet->dpy);
	ret = 0;
end:
	XFree(data);
	return ret;
}

int tablet_get_parameter(const struct tablet *tablet,
			 enum tablet_parameter param_e,
			 union tablet_argument *val)
{
	const struct param *param;
	Atom prop, type;
	unsigned char *data;
	unsigned long nitems, bytes_after;
	int ret, format;

	param = get_param(tablet, param_e, &prop);
	if (!param)
		return -1;

	if (XGetDeviceProperty(tablet->dpy,
			       tablet->dev,
			       prop,
			       0,
			       X11_DEV_BUFFER_LENGTH,
			       False,
			       AnyPropertyType,
			       &type,
			       &format,
			       &nitems,
			       &bytes_after,
			       &data)) {
		ret = -1;
		goto end;
	}
	if (nitems <= param->prop_offset) {
		ret = -1;
		goto end;
	}

	switch (param_e) {
	case PARAM_TABLET_AREA:
	case PARAM_PRESSURE_CURVE:
		val->points.x1 = read_prop(param, data, 0);
		val->points.y1 = read_prop(param, data, 1);
		val->points.x2 = read_prop(param, data, 2);
		val->points.y2 = read_prop(param, data, 3);
		break;
	case PARAM_BUTTON_MAPPING:
	case PARAM_WHEEL_UP_MAPPING:
	case PARAM_WHEEL_DOWN_MAPPING:
	case PARAM_ABS_WHEEL_UP_MAPPING:
	case PARAM_ABS_WHEEL_DOWN_MAPPING:
	case PARAM_ABS_WHEEL2_UP_MAPPING:
	case PARAM_ABS_WHEEL2_DOWN_MAPPING:
	case PARAM_STRIP_LEFT_UP_MAPPING:
	case PARAM_STRIP_LEFT_DOWN_MAPPING:
	case PARAM_STRIP_RIGHT_UP_MAPPING:
	case PARAM_STRIP_RIGHT_DOWN_MAPPING:
		/* TODO get_map() */
		break;
	case PARAM_MAP_OUTPUT:
		/* TODO get_area() */
		break;
	case PARAM_MODE:
		val->mode = read_prop(param, data, 0);
		assert(val->mode == MODE_ABSOLUTE || val->mode == MODE_RELATIVE);
		break;
	case PARAM_BIND_TO_SERIAL:
	case PARAM_RAW_SAMPLE:
	case PARAM_ROTATION:
	case PARAM_SUPPRESS:
	case PARAM_TABLET_DEBUG_LEVEL:
	case PARAM_CURSOR_PROXIMITY:
	case PARAM_THRESHOLD:
	case PARAM_TOOL_DEBUG_LEVEL:
	case PARAM_GESTURE_TAP_TIME:
	case PARAM_GESTURE_ZOOM_DIST:
	case PARAM_GESTURE_SCROLL_DIST:
		val->num = read_prop(param, data, 0);
		break;
	case PARAM_HOVER:
	case PARAM_SERIAL_PREVIOUS:
	case PARAM_TOUCH:
	case PARAM_HW_TOUCH_SWITCH_STATE:
	case PARAM_PRESSURE_RECALIBRATION:
	case PARAM_GESTURE_ENABLED:
		val->boolean = read_prop(param, data, 0);
		assert(val->boolean == !!val->boolean);
		break;
	case PARAM_TOOL_TYPE:
	case PARAM_TOOL_SERIAL:
	case PARAM_TOOL_ID:
	case PARAM_TABLET_ID:
		val->xid = read_prop(param, data, 0);
		break;
	case PARAM_RESET_AREA:
	case NUM_PARAMS:
		/* do nothing */
		break;
	}

	ret = 0;
end:
	XFree(data);
	return ret;
}
