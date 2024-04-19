[![BR-M5 | Open-Source Bluetooth Remote for Canon DSLRs](./.github/cover.png)](https://youtu.be/Gh5uEc2dNJM "BR-M5 | Open-Source Bluetooth Remote for Canon DSLRs")

# BR-M5: An open-source Bluetooth Remote for Canon DSLRs

This is a ported version of https://github.com/ArthurFDLR/br-m5 for the M5StickC PLUS2 ESP32 Mini IoT - https://shop.m5stack.com/products/m5stickc-plus2-esp32-mini-iot-development-kit

My reason for the port:- I do a lot of mulitcamera recording of Bands and theater performance with cheap Canon cameras ( EOS 200D and EOS 250D ). The 30min recording time is a real pain.

https://www.youtube.com/channel/UCrkzUdPsQ1rgC_ePmlbMHoQ
https://www.youtube.com/channel/UCptzIwpNmc4RrXqMqZMZVzQ

So I have added video start/stop from the remote for these cameras. (It will probablly work with the R series and any others that the Canon BL-E1 works with).

When the video start is initiated a 29min 59sec timer is started. When the timer times out the video is stopped and restarted. Resulting in a much shorter break in the recording than I can manually achieve and also mean that I don't forget to restart the camera.

When in video mode First press of the "A" main button starts the camera recoring and the timer. A second press stops and resets the timer. This puts the controller back to the start/stop control.

This version still has the timer function.


## Installation

* Install [Visual Studio Code](https://code.visualstudio.com/download) and the [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) extension.
* Clone this repository - ```git clone https://github.com/hughlewisuk/BL-E1-M5StickC-2/br-m5``` -, open it as project in PlatformIO and upload - ```Ctrl+Alt+u``` - to a M5Stick-Cplus connected to your PC.

## How-To-Use

* Power on by pressing the left-side button and power off with a 6 seconds press on the same button.
* Hold the centre button down when switching on to pair.
* You can connect to your Canon DSLR as soon as the remote is powered on and displays *Pairing in progress*.
* To change the interval, press the right-side button for half a second and use the same button to increase and the center button to decrease the timelapse interval. Once set, press the right-side button for half a second again.
* Start and stop time-lapses using the center button. The remote takes single shots if the interval is set to 0 seconds.

## To-do

[ ] Add the features from https://github.com/combatistor/BR-M5-custom


Feel free to contribute!
