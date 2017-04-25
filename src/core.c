/*
 * core.c
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

#include <gtk/gtk.h>

#include <stdlib.h>
#include <stdio.h>

#include "core.h"
#include "gui_core.h"
#include "tablet_core.h"

void init(void)
{
	size_t i;
	struct {
		int (*cbf)(void);
	} init_funcs[] = {
		{ gui_init },
		{ tablet_init }
	};

	atexit(cleanup);

	for (i = 0; i < ARRAY_SIZE(init_funcs); i++) {
		if (init_funcs[i].cbf()) {
			fputs("Initialization failed.\n", stderr);
			exit(EXIT_FAILURE);
		}
	}
}

void cleanup(void)
{
	size_t i;
	struct {
		void (*cbf)(void);
	} cleanup_funcs[] = {
		{ gui_cleanup },
		{ tablet_cleanup }
	};

	for (i = 0; i < ARRAY_SIZE(cleanup_funcs); i++)
		cleanup_funcs[i].cbf();
}

void *xmalloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr) {
		g_error("Out of memory");
		abort();
	}
	return ptr;
}
