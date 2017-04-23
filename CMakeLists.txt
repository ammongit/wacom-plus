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

# Set compile flags
set(${CMAKE_C_FLAGS} "${CMAKE_C_FLAGS} -ansi -pedantic")
set(${CMAKE_C_FLAGS} "${CMAKE_C_FLAGS} -Wall -Wshadow -Wextra -Wmissing-prototypes -Wcast-qual")
set(${CMAKE_C_FLAGS} "${CMAKE_C_FLAGS} -pipe -O2")
set(${CMAKE_C_FLAGS} "${CMAKE_C_FLAGS} -D_XOPEN_SOURCE=500 -DGDK_VERSION_MIN_REQUIRE=GTK_VERSION_3_0")

set(${CMAKE_C_FLAGS_RELEASE} "${CMAKE_C_FLAGS_RELEASE} -fstack-protector-strong -Werror")

# Check header files
include(CheckIncludes)

# Create config file
configure_file(
    "${PROJECT_SOURCE_DIR}/src/config.h.in"
    "${PROJECT_SOURCE_DIR}/src/config.h"
    NEWLINE_STYLE UNIX
    )

