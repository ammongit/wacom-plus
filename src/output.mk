#
# meta.mk
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

V          ?= 0

ECHO_DEP_0  = @echo '[DEP] $@'; $(CC)
ECHO_DEP_1  = $(CC)
ECHO_DEP    = $(ECHO_DEP_$(V))

ECHO_CC_0   = @echo '[CC]  $@'; $(CC)
ECHO_CC_1   = $(CC)
ECHO_CC     = $(ECHO_CC_$(V))

ECHO_LD_0   = @echo '[LD]  $@'; $(CC)
ECHO_LD_1   = $(CC)
ECHO_LD     = $(ECHO_LD_$(V))

ECHO_STP_0  = @echo '[STP] $@'; $(STRIP)
ECHO_STP_1  = $(STRIP)
ECHO_STP    = $(ECHO_STP_$(V))

ECHO_CLN_0  = @echo '[CLN]'; $(RM) -f
ECHO_CLN_1  = $(RM) -f
ECHO_CLN    = $(ECHO_CLN_$(V))

