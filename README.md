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

- fix two Mac compiler warnings

I did not change the version number, because the functionality of the plugin has not changed.

Update by nst0022 (2020-09-03)
----

- remove all 32bit targets in all make files

See [here](https://forums.x-plane.org/index.php?/forums/topic/225473-seatraffic-plugin-for-x1150-vulkan/&do=findComment&comment=2035158) why.

- remove CFLAGS '-mmacosx-version-min=10.4' from Makefile.mac

This restriction appears to be overdone, see [here](https://forums.x-plane.org/index.php?/forums/topic/225473-seatraffic-plugin-for-x1150-vulkan/&do=findComment&comment=2035129) why.

- set XPSDK303 in all make files

This is the most recent SDK version for x11.50, which replaced XPSDK302.

I have kept the install targets in all make files, which currently point to X-Plane 10, as placeholders for users, who want to adjust them to their own needs.

I did not change the version number, because the functionality of the plugin has not changed.

Update by nst0022 (2020-09-05)
----

Version 2.2

- fix wake problem (workaround)

Wakes are risen now 40 cm above their calculated level. This is a medium value, some ships need more, some ships need less, or even nothing, but all ships I visited during testing had now visible wakes, even if some are slightly distorted. All in all, this appears to be a tolerable compromise.

Update by nst0022 (2020-09-09)
----

Bugfix release, minor changes.

Version 2.3

- do not draw inactive routes on Map anymore
- remove performance sort, because we do not draw directly anymore
- remove rendering options, that used a sim/private/ dataref, which is generally deprecated

Status quo by nst0022 (2020-09-12)
----

- as of version 2.3, the plugin runs under 64-bit Linux and 64-bit Mac
- there has been no feedback yet from a 64-bit Windows user

Needs to be investigated:

- the plugin picks randomely a subset of the available routes for the active region
- it is unclear why and if that should be changed

See [this](https://forums.x-plane.org/index.php?/forums/topic/225473-seatraffic-plugin-for-x1150-vulkan/) thread for a history on how this fork evolved

The plugin has currently no owner

A potential volunteer needs to:

- have a thorough understanding of the inner workings of the plugin
- have a thorough understanding of the X-Plane API
- be able to develop for three platforms (Windows, Mac, Linux)

This fork has now been frozen
