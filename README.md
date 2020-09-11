# arduinopctemps
A program made for reading PC temperatures using OpenHardwareMonitor, Arduino and a simple Python script.

Download OpenHardwareMonitor, set it up to run at start up.
Set the python script to run at start up too, using Task Scheduler.
Upload the program into your Arduino and the screen should be showing the temps for CPU and GPU.
The screen is 16x2, I've used an Arduino Uno.

The temps are put in integer variables so you can use them to control something else (ie. fans).
I'll be updating this to control my cooling and addressable lighting strips, maybe more.
