/*
 * core.h
 *
 * wacom-plus - A simple QOTD daemon.
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

#ifndef _CORE_H_
#define _CORE_H_

#include <stddef.h>

#include "config.h"

/* Definitions */

#if defined(__clang__)
# define COMPILER_NAME				"Clang/LLVM"
# define COMPILER_VERSION			__clang_version__
#elif defined(__ICC) || defined(__INTEL_COMPILER)
# define COMPILER_NAME				"Intel ICC"
# define COMPILER_VERSION			__INTEL_COMPILER
#elif defined(__MINGW32__)
# define COMPILER_NAME				"Mingw"
# define COMPILER_VERSION			__VERSION__
#elif defined(__GNUC__) || defined(__GNUG__)
# define COMPILER_NAME				"GCC"
# define COMPILER_VERSION			__VERSION__
#elif defined(__HP_cc) || defined(__HP_aCC)
# define COMPILER_NAME				"Hewlett-Packard C"
# define COMPILER_VERSION			__HP_cc
#elif defined(__IBMC__) || defined(__IBMCPP__)
# define COMPILER_NAME				"IBM XL C"
# define COMPILER_VERSION			__xlc__
#elif defined(_MSC_VER)
# define COMPILER_NAME				"Microsoft Visual Studio"
# define COMPILER_VERSION			_MSC_VER
#elif defined(__PGI)
# define COMPILER_NAME				"Portland Group PGCC"
# define COMPILER_VERSION			__PGIC__
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
# define COMPILER_NAME				"Oracle Solaris Studio"
# define COMPILER_VERSION			__SUNPRO_C
#else
# define COMPILER_NAME				"Unknown"
# define COMPILER_VERSION			"compiler"
#endif

/* Macros and inline functions */

#define UNUSED(x)				((void)(x))
#define DEFAULT(x,alt)				((x) ? (x) : (alt))
#define STATIC_ASSERT(x)			((void)sizeof(char[2 * (!!(x)) - 1]))
#define ARRAY_SIZE(x)				(sizeof(x) / (sizeof((x)[0])))

/* GNU Extensions */

#if defined(__GNUC__)
# define noreturn				__attribute__((noreturn))
# define likely(x)				(__builtin_expect(!!(x), 1))
# define unlikely(x)				(__builtin_expect(!!(x), 0))
#else
# define noreturn
# define likely(x)				(x)
# define unlikely(x)				(x)
#endif /* __GNUC__ */

/* External functions */

void *xmalloc(size_t size);
#define xfree(x)	free(x)

#endif /* _CORE_H_ */

