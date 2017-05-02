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

#include <xorg/Xwacom.h>
#include <xorg/wacom-properties.h>

#include "tablet.h"

static struct param {
	const char *x11name;
	const char *prop_name;
} parameters[] = {
	{
		/* PARAM_TABLET_AREA */
		"Area",
		WACOM_PROP_TABLET_AREA,
	},
	{
		/* PARAM_BUTTON_MAPPING */
		"Button",
		WACOM_PROP_BUTTON_ACTIONS,
	},
	{
		/* PARAM_BIND_TO_SERIAL */
		"Serial",
		WACOM_PROP_SERIAL_BIND,
	},
	{
		/* PARAM_MAP_OUTPUT */
		"MapToOutput",
		NULL,
	},
	{
		/* PARAM_MODE */
		"Mode",
		NULL,
	},
	{
		/* PARAM_PRESSURE_CURVE */
		"PressCurve",
		WACOM_PROP_PRESSURECURVE,
	},
	{
		/* PARAM_RAW_SAMPLE */
		"RawSample",
		WACOM_PROP_SAMPLE,
	},
	{
		/* PARAM_ROTATION */
		"Rotate",
		WACOM_PROP_ROTATION,
	},
	{
		/* PARAM_SUPPRESS */
		"Suppress",
		WACOM_PROP_SAMPLE,
	},
	{
		/* PARAM_TABLET_DEBUG_LEVEL */
		"CommonDBG",
		WACOM_PROP_DEBUGLEVELS,
	},
	{
		/* PARAM_HOVER */
		"TPCButton",
		WACOM_PROP_HOVER,
	},
	{
		/* PARAM_SERIAL_PREVIOUS */
		"ToolSerialPrevious",
		WACOM_PROP_SERIALIDS,
	},
	{
		/* PARAM_TOUCH */
		"Touch",
		WACOM_PROP_TOUCH,
	},
	{
		/* PARAM_HW_TOUCH_SWITCH_STATE */
		"HWTouchSwitchState",
		WACOM_PROP_HARDWARE_TOUCH,
	},
	{
		/* PARAM_CURSOR_PROXIMITY */
		"CursorProx",
		WACOM_PROP_PROXIMITY_THRESHOLD,
	},
	{
		/* PARAM_THRESHOLD */
		"Threshold",
		WACOM_PROP_PRESSURE_THRESHOLD,
	},
	{
		/* PARAM_TOOL_DEBUG_LEVEL */
		"DebugLevel",
		WACOM_PROP_DEBUGLEVELS,
	},
	{
		/* PARAM_PRESSURE_RECALIBRATION */
		"PressureRecalibration",
		WACOM_PROP_PRESSURE_RECAL,
	},
	{
		/* PARAM_GESTURE_ENABLED */
		"Gesture",
		WACOM_PROP_ENABLE_GESTURE,
	},
	{
		/* PARAM_GESTURE_TAP_TIME */
		"TapTime",
		WACOM_PROP_GESTURE_PARAMETERS,
	},
	{
		/* PARAM_GESTURE_ZOOM_DIST */
		"ZoomDistance",
		WACOM_PROP_GESTURE_PARAMETERS,
	},
	{
		/* PARAM_GESTURE_SCROLL_DIST */
		"ScrollDistance",
		WACOM_PROP_GESTURE_PARAMETERS,
	},
	{
		/* PARAM_WHEEL_UP_MAPPING */
		"RelWheelUp",
		WACOM_PROP_WHEELBUTTONS,
	},
	{
		/* PARAM_WHEEL_DOWN_MAPPING */
		"RelWheelDown",
		WACOM_PROP_WHEELBUTTONS,
	},
	{
		/* PARAM_ABS_WHEEL_UP_MAPPING */
		"AbsWheelUp",
		WACOM_PROP_WHEELBUTTONS,
	},
	{
		/* PARAM_ABS_WHEEL_DOWN_MAPPING */
		"AbsWheelDown",
		WACOM_PROP_WHEELBUTTONS,
	},
	{
		/* PARAM_ABS_WHEEL2_UP_MAPPING */
		"AbsWheel2Up",
		WACOM_PROP_WHEELBUTTONS,
	},
	{
		/* PARAM_ABS_WHEEL2_DOWN_MAPPING */
		"AbsWheel2Down",
		WACOM_PROP_WHEELBUTTONS,
	},
	{
		/* PARAM_STRIP_LEFT_UP_MAPPING */
		"StripLeftUp",
		WACOM_PROP_STRIPBUTTONS,
	},
	{
		/* PARAM_STRIP_LEFT_DOWN_MAPPING */
		"StripLeftDown",
		WACOM_PROP_STRIPBUTTONS,
	},
	{
		/* PARAM_STRIP_RIGHT_UP_MAPPING */
		"StripRightUp",
		WACOM_PROP_STRIPBUTTONS,
	},
	{
		/* PARAM_STRIP_RIGHT_DOWN_MAPPING */
		"StripRightDown",
		WACOM_PROP_STRIPBUTTONS,
	},
	{
		/* PARAM_RESET_AREA */
		"ResetArea",
		WACOM_PROP_TABLET_AREA,
	},
	{
		/* PARAM_TOOL_TYPE */
		"ToolType",
		WACOM_PROP_TOOL_TYPE,
	},
	{
		/* PARAM_TOOL_SERIAL */
		"ToolSerial",
		WACOM_PROP_SERIALIDS,
	},
	{
		/* PARAM_TOOL_ID */
		"ToolID",
		WACOM_PROP_SERIALIDS,
	},
	{
		/* PARAM_TABLET_ID */
		"TabletID",
		WACOM_PROP_SERIALIDS,
	},
};

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
			 enum tablet_parameter param,
			 const union tablet_argument *arg)
{
}

int tablet_get_parameter(const struct tablet *tablet,
			 enum tablet_parameter param,
			 union tablet_argument *arg)
{
}
