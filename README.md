SeaTraffic plugin for X-Plane<sup>®</sup>
====

This [X-Plane](x-plane.com) plugin displays ships moving along real-life routes.

The repo contains the artwork assets and the source code for the X-Plane plugin. User oriented documention is contained in the file [SeaTraffic-ReadMe.html](http://htmlpreview.github.io/?https://raw.githubusercontent.com/Marginal/SeaTraffic/master/SeaTraffic-ReadMe.html).

Building the plugin
----
The plugin is built from the `src` directory.

Mac 32 & 64 bit fat binary:

    make -f Makefile.mac

Linux 32 & 64 bit binaries:

    make -f Makefile.lin

Windows 32 or 64 bit binary:

    vcvarsall [target]
    nmake -f Makefile.win

Building the routes list
----
The routes list is built from the `SeaTraffic` directory, and requires Python 2.x.

    buildroutes.py

This fork by nst0022 (2020-08-23)
----

I have changed the code from XPLMDrawObjects to XPLMInstancing, which is mandatory for X-Plane 11.50 Vulkan.

As I am on Linux, I could not compile for Windows or Mac, but tested the changes in a separate configuration (64-bit Linux only).

In the make files for Windows and Mac, XPSDK213 needs probably to be replaced by XPSDK302, like in the make file for Linux, but I did not want to touch these files, nor did I change the version number.

I have marked all changes with 'nst0022' in the source code, which might be better readable than the diff here on GitHub.

I will not maintain the source code further on, because I have only a rudimentary understanding of what happens internally. This source code is an offer for scenery maintainers, who want to consider the changes for their own purposes.

Update by nst0022 (2020-08-25)
----

Version 2.0

- replace "drawing" by "instancing"
- replace "draw callback" by "flightloop callback"
- de-activate "menu item" and "draw on local map"
- show wakes always, not dependent on reflection slider

Known issues:

- "draw on local map" needs to be redesigned to use the X-Plane 11 Map API
- "wakes" appear only sporadically, this needs to be investigated
- reflection slider coding does not work when activated, this needs to be investigated
- none of the assert messages come through to stderr (w/ or w/o NDEBUG), they need to be replaced by messages to Log.txt

Update by nst0022 (2020-08-27)
----

- fix a reported compile error

I did not change the version number, because the functionality of the plugin has not changed.

Update by nst0022 (2020-08-29)
----

Version 2.1

- implement draw on Map

Handling is described in SeaTraffic-ReadMe.html, chapter "Drawing on X-Plane's Map".

Update by nst0022 (2020-09-01)
----

- convert buildroutes.py and Aframax_tanker.py from Python2 to Python3

The reason for this change is, that Debian will not support Python2 anymore starting on 2021-01-01.

I did not change the version number, because the functionality of the plugin has not changed.
