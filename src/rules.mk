#
# rules.mk
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

include output.mk

.SUFFIXES:
.PHONY: all debug release clean

$(EXECUTABLE): $(OBJECTS)
	$(ECHO_LD) $(FLAGS) $(LDFLAGS) $(LD_FLAGS) -o $@ $^

$(STATIC_LIB): $(OBJECTS)
	$(ECHO_AR) rcs $@ $^

$(SHARED_LIB): $(OBJECTS)
	$(ECHO_LD) $(FLAGS) $(LDFLAGS) $(LD_FLAGS) -o $@ $^

%.o: %.c
	$(ECHO_CC) $(FLAGS) $(CFLAGS) $(CC_FLAGS) -c -o $@ $<

%.d: %.c
	$(ECHO_DEP) $(FLAGS) $(CFLAGS) $(CC_FLAGS) -MM $< > $@

clean:
	$(ECHO_CLN) $(EXECUTABLE) *.[oad] *.so *.dylib

