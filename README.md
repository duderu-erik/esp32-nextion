/* Erik Nielsen - POC on ESP32 with Nextion 3.5 Basic Display
*	Developed on Generic ESP32-WROOM32-DevkitC using the esp-edf v3.1Dev branch from GitHub 
*
*	README.md
*
* ----------------------------------------------------------------------------
* "THE BEER-WARE LICENSE":
* <duderu> hanging at gmail- wrote this file.  As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a beer in return. duderu
* ----------------------------------------------------------------------------
  This software is FREE and thus distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
  CONDITIONS OF ANY KIND, either express or implied.
*/

Developed off of the asynchronous UART example in the 3.1Dev branch of the ESP-IDF from Expressif.
Utilizing the Nextion 3.5inch Basic Screen on a ESP32 WROOM DevkitC on UART2 pins 16,17

I haven't seen much out there with just basic esp-idf to Nextion interaction. Most is Arduino which is fine but I'm old school. This utilized the 
uart_async_rxtxtasks example that came with the esp-idf.

--Nextion NX4832T035_011 basic display
--Generic ESP32-WROOM32-DevkitC ---- Chip is ESP32D0WDQ6 (revision 1)
--Built using the ESP-IDF v3.1-dev-304-gd8c80509-dirty 2nd stage bootloader
--Graphics used off the web and modified using GIMP. You can make fun of my graphics skills. Yes, I suck.
--Nextion editor v0.53 -- https://nextion.itead.cc/
--Debug output is at "Info Level" and comes accross UART0 on pins GPIO1-TX and GPIO3-RX on the USB port of the DevkitC I'm using.
--Compiled and run using MSYS on Windows... yea shut up, my main development environment is Linux. Currently set to COM13 for programming/debugging.


-- AT the very least, you will need to configure your comport or tty device in 'make menuconfig'


So far so Good?
=============
I took the chance and did not use any level shifting despite the Nextion being a 5v device and the ESP32 being 3.3v.
I interpreted the Nextion datasheets to show that the RX and TX lines play friendly with 3.3 pins but don't hold me to it. 
I ran power for Nextion off the 5v rail of Devkitc and of course all needs a common ground.
READ THE DATA SHEETS!!! I'm not responsible for any magical smoke or any damage to your equipment or ego.




FILES:
======
-README.md	- this file
-sdkconfig	- Do not Edit; Use 'make menuconfig'
-Makefile 	- change the project name to your liking
----------main
			|
			--esp32-nextion.c = pretty much main.c
			--esp32-nextion.h = would love to see someone run with this and create structures for the various Nextion commands, etc.
			--component.mk	   = See expressif documentation at esp32.com. Do not need to touch for this demo.
			
----------nextion
			|
			--esp32-nextion35.HMI = source file for Nextion editor v0.53
			--esp32-nextion35.tft = compiled file from Nextion editor v0.53
			
			
			


Stuff you can do in this demo(most should be obvious):
=====================================
-- From the main screen(Page0) go to SETUP>ABOUT>DEBUG to enter random text to send to ESP32. watch it come across in 'make monitor' or Putty on the your comport
-- Run 'make monitor' to see the received data from Nextion-reference Nextion Help for return codes and formats.
-- Set Screen timeout in minutes and watch what codes are returned to 'make monitor' when the Nextion goes to sleep(0x86,0xff,0xff) and wakes(0x87,0xff,0xff) up
-- You can reset the Nextion display and the ESp32 from the SETUP screen. Note the beavior and this would need to be coordinated in a serious project.


TO_DO:
======
-- ummmmm... a whole bunch. Like creating proper structures for all the possible Nextion commands and return values in the header file.
-- accomodate the Enhanced Nextion displays



===========================================================================================
Yes, I realize this is barely even Alpha quality code but it works and you can take it and run with it.
No "keyboard-warrior" comments and Sorry... Please No Arduino questions or requests. duderu