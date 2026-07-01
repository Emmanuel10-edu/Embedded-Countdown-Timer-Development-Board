Embedded Smart Countdown Timer
Overview

The Embedded Smart Countdown Timer is a standalone ATmega328P-based embedded system designed and built from scratch using KiCad and programmed with the Arduino framework.

The project demonstrates complete embedded hardware design including USB programming, power regulation, display interfacing, PCB layout, and firmware development.

The timer displays countdown information on a seven-segment display while simultaneously updating an OLED display with system status. Audible and visual notifications are provided through an active buzzer and status LED.

Features
Standalone ATmega328P microcontroller
FT232RL USB-to-Serial programming
Single Common Cathode 7-Segment Display
OLED (I²C) Status Display
Active Buzzer
Status LED
External Reset Button
Crystal Oscillator Clock
Battery-powered operation
7805 Voltage Regulator
Custom PCB designed in KiCad
Arduino IDE compatible firmware
Hardware Used
Component	Description
ATmega328P-PU	Main Microcontroller
FT232RL	USB-to-Serial Converter
SSD1306 OLED	I²C Display
7-Segment Display	Countdown Display
74HC595 / MAX7219	Display Driver
16 MHz Crystal	Clock Source
Active Buzzer	Audio Feedback
LEDs	Status Indicators
7805 Regulator	5V Power Supply
9V Battery	Portable Power
Software
Arduino IDE
KiCad 9
Proteus (Simulation)
Functional Description

When powered:

The OLED initializes and displays system information.
The seven-segment display performs the countdown.
Every second:
Display updates.
LED flashes.
Buzzer beeps.
After reaching zero:
OLED displays END
Buzzer sounds.
Pressing the reset button restarts the countdown.
PCB

Designed entirely in KiCad, including:

Schematic Capture
PCB Layout
3D PCB Visualization
Gerber Generation
Future Improvements
Multiple timer presets
EEPROM save function
Rotary encoder interface
Bluetooth control
Battery level monitoring
Low-power sleep mode
Enclosure design
Four-digit display support
Author

Emmanuel Akwesi Abbam Egyin

Electrical & Electronic Engineering Student

Accra Technical University

LinkedIn: www.linkedin.com/in/emmanuel-egyin-341396201
