#
# CMakeLists.txt
#
# wacom-plus - A simple QOTD daemon.
# Copyright (c) 2015-2016 Ammon Smith
#
# wacom-plus is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# wacom-plus is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with wacom-plus.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 2.6)
project(wacom-plus C)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 2)

add_subdirectory(src)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Compile flags
add_definitions("-ansi -pedantic -Wall -Wextra -Wshadow -Wmissing-prototypes -Wcast-qual")
add_definitions("-pipe -O2")
add_definitions("-D_XOPEN_SOURCE=500 -DGDK_VERSION_MIN_REQUIRE=GTK_VERSION_3_0")

# Check header files
include(CheckIncludes)

# Create config file
configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_SOURCE_DIR}/src/config.h"
    NEWLINE_STYLE UNIX
    )

