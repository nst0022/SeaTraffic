# SeaTraffic plugin for X-Plane<sup>®</sup>

&nbsp;

SeaTraffic is an [X-Plane](x-plane.com) plugin that displays ships moving along real-life routes.   

This repository contains a complete plugin distribution for **the Linux version of X-Plane 11.50+** (including some ship models) as well as the source code for the X-Plane plugin.   
User oriented documention is contained in the file [SeaTraffic-ReadMe.html](http://htmlpreview.github.io/?https://raw.githubusercontent.com/Marginal/SeaTraffic/master/SeaTraffic-ReadMe.html).

&nbsp;

## Requirements

- Linux (an up-to-date distro)
- [X-Plane 11](https://www.x-plane.com/) (11.50 or higher)
- [OpenSceneryX](https://www.opensceneryx.com/)
- Python 2.x (for building/updating the routes list)

&nbsp;

## Installation

Copy the "SeaTraffic" folder into

	X-Plane 11/Resources/Plugins
	
&nbsp;


## (Re)Building the plugin

To clean a previous build from the _"build"_ and _"SeaTraffic/64"_ subfolders (if present):
	
	make clean
	
To compile a new _lin.xpl_ file, output in _"build"_
	
	make
	
To move _lin.xpl_ from the _"build"_ subfolder to the _"SeaTraffic/64"_ subfolder
	
	make install

&nbsp;	

## Building the routes list

The routes list is built from the `SeaTraffic` directory, and requires Python 2.x.

    buildroutes.py
    
&nbsp;

## Fork/Update history

&nbsp;

#### Fork by JT8D-17 (2020-08-27)

- Made XPLMInstanceRef for the wakes in seatraffic.h static to permit compilation (on my system)
- Gave nst0022 some credit in the plugin description
- Rebuilt makefile from scratch (64bit Linux only)
- Included prebuilt 64bit lin.xpl file in plugin folder
- Included SDK folder
- Updated this document


&nbsp;

#### Update by nst0022 (2020-08-25)

- Version 2.0
- replaced "drawing" by "instancing"
- replaced "draw callback" by "flightloop callback"
- de-activate "menu item" and "draw on local map"
- shows wakes always, not dependent on reflection slider
- Known issues:
	- "draw on local map" needs to be redesigned to use the X-Plane 11 Map API
	- "wakes" appear only sporadically, this needs to be investigated
	- reflection slider coding does not work when activated, this needs to be investigated
	- none of the assert messages come through to stderr (w/ or w/o NDEBUG), they need to be replaced by messages to Log.txt

&nbsp;

#### Fork by nst0022 (2020-08-23)

I have changed the code from XPLMDrawObjects to XPLMInstancing, which is mandatory for X-Plane 11.50 Vulkan.   
As I am on Linux, I could not compile for Windows or Mac, but tested the changes in a separate configuration (64-bit Linux only).   
In the make files for Windows and Mac, XPSDK213 needs probably to be replaced by XPSDK302, like in the make file for Linux, but I did not want to touch these files, nor did I change the version number.   
I have marked all changes with 'nst0022' in the source code, which might be better readable than the diff here on GitHub.   
I will not maintain the source code further on, because I have only a rudimentary understanding of what happens internally. This source code is an offer for scenery maintainers, who want to consider the changes for their own purposes.