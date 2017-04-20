## wacom-plus
An Wacom tablet configuration GUI for Linux. There are a few already in existence, but I found them to be quite lacking and out-of-date. This project seeks to make tablet configuration as easy as it is on Windows.

### Requirements
* GNU Make
* ANSI C Compiler
* `pkg-config`
* GTK 3.0
* `xf86-input-wacom`
* `libwacom`

### Compilation
Invoke `make release` in `src/`. The final binary will be located at `src/wacom-plus`.

Available under the GPL, version two or later.

