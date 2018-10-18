# megacli - A CLI interface to Arduino Mega, with special support for Mega based RAMPS and MKSGEN 1.4 boards

This is a multi-threaded control system implementation that provides a command line (CLI)
interface to control the Arduino.

This code runs on any Arduino Mega, with special support for versatile RAMPS/MKS GEN 1.4 boards that are
based on Arduino Mega 2560. These boards are designed to be used as a 3D Printer controller, but can be put
to many good uses as a generic robotic contoller.

These two boards aregenerally run the Marlin firmware that is focussed on making these boards work as 3D
printer controller. The *megacli* library makes these boards useful as a general purpose controller.

The companion **megapy** Python package provides an object-oriented interface to this CLI. You can install it
on any Linux based system (including Raspberry Pi) to control your Arduino Mega (or its derivatives) over USB.

The companion **megarest** Python package provides an RESTful API interface to this CLI through *megapy* package.
You can install it on any Linux based system (including Raspberry Pi) to control your Arduino Mega (or its derivatives)
over USB.

Documentation for the above two projects can be found on their Github page.
