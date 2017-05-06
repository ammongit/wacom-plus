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

PACKAGES_GUI := \
	gtk+-3.0

PACKAGES_SETTINGS := \
	json-c

PACKAGES_WACOM := \
	xorg-wacom \
	libwacom \

PACKAGES_X11 := \
	x11 \
	xi \
	xinerama \
	xrandr

PACKAGES_ALL := \
	$(PACKAGES_GUI) \
	$(PACKAGES_SETTINGS) \
	$(PACKAGES_WACOM) \
	$(PACKAGES_X11)

