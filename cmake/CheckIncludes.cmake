#
# CheckIncludes.cmake
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

include(CheckIncludeFiles)
include(CheckFunctionExists)

macro(CHECK_INCLUDE_VAR VARIABLE MSG)
    if(NOT ${VARIABLE})
        message(FATAL_ERROR ${MSG})
    endif()
endmacro()

check_include_files("errno.h;stdio.h;stdlib.h;string.h;time.h" HAVE_STDC)
check_include_var(HAVE_STDC "Missing C standard library headers")
