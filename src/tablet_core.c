/*
 * tablet_core.c
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

#include <libwacom/libwacom.h>

#include "tablet_core.h"

static WacomDeviceDatabase *db;
static WacomError *err;
static WacomDevice **list;

int tablet_init(void)
{
	db = libwacom_database_new();
	err = libwacom_error_new();
	if (!db || !err)
		return -1;
	return 0;
}

void tablet_cleanup(void)
{
	libwacom_database_destroy(db);
	libwacom_error_free(&err);
}


int tablet_refresh_list(void)
{
	free(list);
	list = libwacom_list_devices_from_database(db, err);
	if (!list)
		return -1;
	return 0;
}

int tablets_device_iterate(Display *dpy, tablets_device_list_cbf cbf, void *arg)
{
	XDeviceInfo *devices;
	int i, num_devices, ret;

	devices = XListInputDevices(dpy, &num_devices);
	if (!devices)
		return -1;

	ret = 0;
	for (i = 0; i < num_devices; i++) {
		if (cbf(arg, devices[i].id, devices[i].name, devices[i].type)) {
			ret = -1;
			break;
		}
	}
	XFreeDeviceList(devices);
	return ret;
}
