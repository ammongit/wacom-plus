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

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Git hash flag
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
string(SUBSTRING ${GIT_SHA1} 0 7 GIT_HASH)
add_definitions("-DGIT_HASH=\"${GIT_HASH}\"")

# Add sources
include_directories("${PROJECT_SOURCE_DIR}/src")
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)

# pkg-config checks
include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED gtk+-3.0)
pkg_check_modules(LIBWACOM REQUIRED libwacom)

set(${CMAKE_C_FLAGS} "${CMAKE_C_FLAGS} ${GTK_CFLAGS} ${LIBWACOM_CFLAGS}")

# Set compile flags
set(${CMAKE_C_FLAGS} "${CMAKE_C_FLAGS} -ansi -pedantic")
set(${CMAKE_C_FLAGS} "${CMAKE_C_FLAGS} -Wall -Wshadow -Wextra -Wmissing-prototypes -Wcast-qual")
set(${CMAKE_C_FLAGS} "${CMAKE_C_FLAGS} -pipe -O2")
set(${CMAKE_C_FLAGS} "${CMAKE_C_FLAGS} -D_XOPEN_SOURCE=500 -DGDK_VERSION_MIN_REQUIRE=GTK_VERSION_3_0")

set(${CMAKE_C_FLAGS_RELEASE} "${CMAKE_C_FLAGS_RELEASE} ${CMAKE_C_FLAGS}")
set(${CMAKE_C_FLAGS_RELEASE} "${CMAKE_C_FLAGS_RELEASE} -fstack-protector-strong -Werror")

# Main executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GTK_LDFLAGS})
target_link_libraries(${PROJECT_NAME} ${LIBWACOM_LDFLAGS})

