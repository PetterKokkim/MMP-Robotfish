INTRODUCTION
------------
This project entails the expansion of a fish-shaped robot designed to test biological hypotheses.
Although the objective of this project is not to design and build a complete fish robot, it is my 
obligation to create and test a variety of fish robot tails.This software, which is the primary 
programme for the platform, is built in C++ and mostly use the Blynk library. 


REQUIREMENTS
------------

This require some specific library, this is the Blynk library and here is a step-by-step guide 
on how this can be installed: 

https://docs.blynk.io/en/legacy-platform/legacy-articles/what-do-i-need-to-blynk

or directlty the library: 

https://github.com/blynkkk/blynk-library/releases/tag/v1.0.1

CONFIGURATION
-------------

To make this work with your WiFi, it is necessary to adjust certain parameters; specifically, 
lines 27 and 28 must be modified to reflect the WiFi to which you wish to connect.

char ssid[] = "Your sssid here"; //You can replace the wifi name to your wifi
char pass[] = "Your password here"; //You can replace the wifi password to your wifi



CREATOR
-------

Petter Wessel Kokkim
pwk1@aber.ac.uk