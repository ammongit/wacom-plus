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
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}/src")
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)

# pkg-config checks
include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED gtk+-3.0)
pkg_check_modules(LIBWACOM REQUIRED libwacom)

add_definitions(${GTK_CFLAGS} ${LIBWACOM_CFLAGS})

# Main executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GTK_LDFLAGS})
target_link_libraries(${PROJECT_NAME} ${LIBWACOM_LDFLAGS})

