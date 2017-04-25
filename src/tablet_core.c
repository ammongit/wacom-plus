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

#include "tablet_core.h"

static WacomDeviceDatabase *db;
static WacomError *err;

int tablet_init(void)
{
	if ((db = libwacom_database_new()) == NULL)
		return -1;
	if ((err = libwacom_error_new()) == NULL)
		return -1;
	return 0;
}

void tablet_cleanup(void)
{
	libwacom_database_destroy(db);
	libwacom_error_free(&err);
}


int tablet_refresh_list(void);
