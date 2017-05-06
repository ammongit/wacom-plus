#
# flags.mk
#
# wacom-plus - Linux GUI configuration for Wacom tablets
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

include packages.mk

PACKAGES := $(PACKAGES_$(shell tr [a-z] [A-Z] <<< '$(PACKAGE_SET)'))

CC_FLAGS := \
	-ansi \
	-pedantic \
	-I. \
	-Wall \
	-Wextra \
	-Wshadow \
	-Wmissing-prototypes \
	-Wcast-qual \
	-D_XOPEN_SOURCE=500 \
	-DGIT_HASH='"$(shell git rev-parse --short HEAD)"' \
	-DGDK_VERSION_MIN_REQUIRED=GDK_VERSION_3_0 \
	$(shell pkg-config --cflags $(PACKAGES) | sed 's|-I|-isystem |g')

LD_FLAGS := \
	$(shell pkg-config --libs $(PACKAGES))

all: FLAGS += -pipe
all: $(EXECUTABLE)

debug: FLAGS += -pipe -g
debug: $(EXECUTABLE)

release: FLAGS += -pipe -DNDEBUG -fstack-protector-strong
release: $(EXECUTABLE)
	$(ECHO_STP) $<

