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

#include <xorg/Xwacom.h>
#include <xorg/wacom-properties.h>

#include "tablet.h"

#define X11_DEV_IN_BUFFER_LENGTH	1000
#define X11_DEV_OUT_BUFFER_LENGTH	128

/*------*/
/* DATA */
/*------*/

static struct param {
	const char *x11_name;
	const char *prop_name;
	unsigned int prop_offset;
	unsigned int prop_format : 1;
	unsigned int readonly    : 1;
} parameters[] = {
	{
		/* PARAM_TABLET_AREA */
		"Area",
		WACOM_PROP_TABLET_AREA,
		0,
	},
	{
		/* PARAM_BUTTON_MAPPING */
		"Button",
		WACOM_PROP_BUTTON_ACTIONS,
		0,
	},
	{
		/* PARAM_BIND_TO_SERIAL */
		"Serial",
		WACOM_PROP_SERIAL_BIND,
		0,
	},
	{
		/* PARAM_MAP_OUTPUT */
		"MapToOutput",
		NULL,
		0,
	},
	{
		/* PARAM_MODE */
		"Mode",
		NULL,
		0,
	},
	{
		/* PARAM_PRESSURE_CURVE */
		"PressCurve",
		WACOM_PROP_PRESSURECURVE,
		0,
	},
	{
		/* PARAM_RAW_SAMPLE */
		"RawSample",
		WACOM_PROP_SAMPLE,
		1,
	},
	{
		/* PARAM_ROTATION */
		"Rotate",
		WACOM_PROP_ROTATION,
		0,
	},
	{
		/* PARAM_SUPPRESS */
		"Suppress",
		WACOM_PROP_SAMPLE,
		0,
	},
	{
		/* PARAM_TABLET_DEBUG_LEVEL */
		"CommonDBG",
		WACOM_PROP_DEBUGLEVELS,
		1,
	},
	{
		/* PARAM_HOVER */
		"TPCButton",
		WACOM_PROP_HOVER,
		0,
	},
	{
		/* PARAM_SERIAL_PREVIOUS */
		"ToolSerialPrevious",
		WACOM_PROP_SERIALIDS,
		1,
	},
	{
		/* PARAM_TOUCH */
		"Touch",
		WACOM_PROP_TOUCH,
		0,
	},
	{
		/* PARAM_HW_TOUCH_SWITCH_STATE */
		"HWTouchSwitchState",
		WACOM_PROP_HARDWARE_TOUCH,
		0,
	},
	{
		/* PARAM_CURSOR_PROXIMITY */
		"CursorProx",
		WACOM_PROP_PROXIMITY_THRESHOLD,
		0,
	},
	{
		/* PARAM_THRESHOLD */
		"Threshold",
		WACOM_PROP_PRESSURE_THRESHOLD,
		0,
	},
	{
		/* PARAM_TOOL_DEBUG_LEVEL */
		"DebugLevel",
		WACOM_PROP_DEBUGLEVELS,
		0,
	},
	{
		/* PARAM_PRESSURE_RECALIBRATION */
		"PressureRecalibration",
		WACOM_PROP_PRESSURE_RECAL,
		0,
	},
	{
		/* PARAM_GESTURE_ENABLED */
		"Gesture",
		WACOM_PROP_ENABLE_GESTURE,
		0,
	},
	{
		/* PARAM_GESTURE_TAP_TIME */
		"TapTime",
		WACOM_PROP_GESTURE_PARAMETERS,
		2,
	},
	{
		/* PARAM_GESTURE_ZOOM_DIST */
		"ZoomDistance",
		WACOM_PROP_GESTURE_PARAMETERS,
		0,
	},
	{
		/* PARAM_GESTURE_SCROLL_DIST */
		"ScrollDistance",
		WACOM_PROP_GESTURE_PARAMETERS,
		1,
	},
	{
		/* PARAM_WHEEL_UP_MAPPING */
		"RelWheelUp",
		WACOM_PROP_WHEELBUTTONS,
		0,
	},
	{
		/* PARAM_WHEEL_DOWN_MAPPING */
		"RelWheelDown",
		WACOM_PROP_WHEELBUTTONS,
		1,
	},
	{
		/* PARAM_ABS_WHEEL_UP_MAPPING */
		"AbsWheelUp",
		WACOM_PROP_WHEELBUTTONS,
		2,
	},
	{
		/* PARAM_ABS_WHEEL_DOWN_MAPPING */
		"AbsWheelDown",
		WACOM_PROP_WHEELBUTTONS,
		3,
	},
	{
		/* PARAM_ABS_WHEEL2_UP_MAPPING */
		"AbsWheel2Up",
		WACOM_PROP_WHEELBUTTONS,
		4,
	},
	{
		/* PARAM_ABS_WHEEL2_DOWN_MAPPING */
		"AbsWheel2Down",
		WACOM_PROP_WHEELBUTTONS,
		5,
	},
	{
		/* PARAM_STRIP_LEFT_UP_MAPPING */
		"StripLeftUp",
		WACOM_PROP_STRIPBUTTONS,
		0,
	},
	{
		/* PARAM_STRIP_LEFT_DOWN_MAPPING */
		"StripLeftDown",
		WACOM_PROP_STRIPBUTTONS,
		1,
	},
	{
		/* PARAM_STRIP_RIGHT_UP_MAPPING */
		"StripRightUp",
		WACOM_PROP_STRIPBUTTONS,
		2,
	},
	{
		/* PARAM_STRIP_RIGHT_DOWN_MAPPING */
		"StripRightDown",
		WACOM_PROP_STRIPBUTTONS,
		3,
	},
	{
		/* PARAM_RESET_AREA */
		"ResetArea",
		WACOM_PROP_TABLET_AREA,
		0,
	},
	{
		/* PARAM_TOOL_TYPE */
		"ToolType",
		WACOM_PROP_TOOL_TYPE,
		0,
	},
	{
		/* PARAM_TOOL_SERIAL */
		"ToolSerial",
		WACOM_PROP_SERIALIDS,
		3,
	},
	{
		/* PARAM_TOOL_ID */
		"ToolID",
		WACOM_PROP_SERIALIDS,
		4,
	},
	{
		/* PARAM_TABLET_ID */
		"TabletID",
		WACOM_PROP_SERIALIDS,
		0,
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
			 const union tablet_argument *arg)
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
			       X11_DEV_OUT_BUFFER_LENGTH,
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

	//

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
			 union tablet_argument *arg)
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
			       X11_DEV_OUT_BUFFER_LENGTH,
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

	/* TODO */
printf("<%s>\n", data);

	ret = 0;
end:
	XFree(data);
	return ret;
}
