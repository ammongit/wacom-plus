#
# packages.mk
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

PACKAGES_gui := \
	gtk+-3.0

PACKAGES_settings := \
	json-c

PACKAGES_wacom := \
	xorg-wacom \
	libwacom \

PACKAGES_x11 := \
	x11 \
	xi \
	xinerama \
	xrandr

PACKAGES_all := \
	$(PACKAGES_gui) \
	$(PACKAGES_settings) \
	$(PACKAGES_wacom) \
	$(PACKAGES_x11)

