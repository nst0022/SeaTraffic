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

## Changes from original plugin

&nbsp;

#### By JT8D-17
- Updated this Readme
- Reactivated hidden wakes when ships are static, too slow or not moving forward
- Decreased minimum speed for wakes from 5 to 4 m/s
- Added wakes.h for XPLMInstanceRef headers for the wakes
- Included prebuilt 64bit lin.xpl file in plugin folder
- Included X-Plane SDK folder
- Rebuilt makefile from scratch (64bit Linux only)
- Gave nst0022 some credit in the plugin description

#### By nst0022
- Bumped version number to 2.0
- Deactivated menu items and drawing on map
- Replaced XPLMDrawObjects by XPLM's instancing system (required for XP 11.50+ Vulkan)
- Replaced draw callbacks with flightloop callbacks

&nbsp;

##Known issues / Help required

- No Windows build ; requires external input
- No MacOS build ; requires external input
- Does not draw on X-Plane map anymore; requires redesiging to use the X-Plane 11 API
- Reflection slider does not have any effect on wakes ; requires investigation
- Assert messages need to be piped through the XPLMDebugMessage system to be viewable outside of the terminal ; requires rewite