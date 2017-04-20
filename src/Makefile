#
# Makefile
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

.SUFFIXES:
.PHONY: all release debug clean

V         ?= 0

ECHO_CC_0  = @echo '[CC]  $@'; $(CC)
ECHO_CC_1  = $(CC)
ECHO_CC    = $(ECHO_CC_$(V))

ECHO_LD_0  = @echo '[LD]  $@'; $(CC)
ECHO_LD_1  = $(CC)
ECHO_LD    = $(ECHO_LD_$(V))

ECHO_DEP_0 = @echo '[DEP] $@'; $(CC)
ECHO_DEP_1 = $(CC)
ECHO_DEP   = $(ECHO_DEP_$(V))

SOURCES   := $(wildcard *.c)
OBJECTS   := $(SOURCES:.c=.o)
DEPENDS   := $(SOURCES:.c=.d)
EXE       := wacom-plus

CC_FLAGS  := \
	-ansi \
	-pedantic \
	-I. \
	-isystem /usr/include/gtk-3.0 \
	-Wall \
	-Wextra \
	-Wmissing-prototypes \
	-Wcast-qual

LD_FLAGS  := \
	-lgtk \
	-lgdk \
	-lglib \
	-lX11 \
	-lXext \
	-lm

all: CFLAGS += -pipe -O2
all: $(EXE)

release: CFLAGS += -pipe -DNDEBUG -Werror
release: CFLAGS += -O2 -fstack-protector-strong
release: $(EXE)

debug: CFLAGS += -pipe -g
debug: $(EXE)

$(EXE): $(OBJECTS)
	$(ECHO_LD) $(LD_FLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(ECHO_CC) $(CC_FLAGS) $(CFLAGS) -c -o $@ $<

%.d: %.c
	$(ECHO_DEP) $(CC_FLAGS) $(CFLAGS) -MM $< > $@

clean:
	rm -f $(EXE) *.o *.d *.a *~ *.bak

-include $(DEPENDS)
