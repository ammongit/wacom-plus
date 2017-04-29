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

#include <stdio.h>

#include <json.h>

#include "settings.h"

#define JSON_ADD(obj, key, n, type)				\
	do {							\
		json_object *__wrap_;				\
		__wrap_ = (json_object_new_ ## type)(n);	\
		json_object_object_add((obj), (key), __wrap_);	\
	} while (0)

/* Conversion to JSON */
static struct json_object *to_json(const struct settings *st)
{
	struct json_object *obj;

	obj = json_object_new_object();

	/* Meta */
	JSON_ADD(obj, "version", SETTINGS_SERIAL_VERSION, int);

	/* Fields */
	JSON_ADD(obj, "tip-feel", st->tip_feel, int);
	JSON_ADD(obj, "double-click-distance", st->double_click_dist, int);
	JSON_ADD(obj, "force-perceptions", st->force_perceptions, boolean);

	return obj;
}

static int from_json(struct settings *st, const struct json_object *obj)
{
	/* TODO */
}

/* Externals */
int read_settings(struct settings *st, const char *path)
{
	/* TODO */
}

int write_settings(const struct settings *st, const char *path)
{
	FILE *fh;
	struct json_object *obj;

	obj = to_json(st);
	if (!obj)
		return -1;

	fh = fopen(path, "w");
	if (!fh) {
		perror("Unable to open settings file for reading");
		return -1;
	}
	if (fputs(json_object_to_json_string(obj), fh) == EOF) {
		perror("Unable to write to settings file");
		return -1;
	}
	fclose(fh);
	return 0;
}
