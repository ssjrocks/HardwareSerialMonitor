# HardwareSerialMonitor with formatting for an arduino-nextion setup
Gnat Stats PC Harware Performance Monitor Windows Client
  
  GNATSTATS OLED PC Performance Monitor / HardwareSerialMonitor -  Rupert Hirst & Colin Conway © 2016-2018
  http://tallmanlabs.com  & http://runawaybrainz.blogspot.com/
  
  https://hackaday.io/project/19018-gnat-stats-tiny-oled-pc-performance-monitor



  modified by ssjrocks to reformat output for arduino->nextion adaption

  requires easy nextion library for arduino https://github.com/Seithan/EasyNextionLibrary

  for now only compatible with arduino mega, as i have not sorted softwareserial out for the nextion library

  ![Screen Output](https://images2.imgbox.com/de/0f/YIBIetT5_o.jpg)


  please note, i am very new to coding and arduino, use any of this software or my method of implementation at your own risk, no guarantees


# needed:

  arduino mega(shouldnt be to hard to adapt to software serial for uno just have not sorted this myself)
  nextion 240x320 2.8" screen ... im using nx3224TO28_011, others would work but might need some modifications... or just clone the him for your screen

# how i put it together:

  using the hardware serial program, i modified it to encapsulate specific values and change the format it outputs over the serial so i could
  process the values in an arduino and then have the arduino do the nextion communication
  the reason for this is i am unable to figure out how to use the nextion direct from the hardware serial monitor application due to lack of coding     knowledge/skills

# physical setup:

  an arduino mega plugged in via usb recieves the hardware serial monitor output through the usb connection.
  the arduino reads the values coming in from Serial and splits the data into 8 variables

cpu load

cpu temp

gpu load

gpu temp

cpu clock

gpu clock

it also maps the percentage for cpu load to the angles required for the gauge values

and then uses the easy nextion library to pass these values to the screen via Serial1(tx1(pin 19) and rx1(pin 18))


  hardware serial monitor must be run as administrator and auto detect port seems to work fine

  Licence
  -------

  Attribution-NonCommercial-ShareAlike  CC BY-NC-SA

  This license lets others remix, tweak, and build upon your work non-commercially, as long as they credit you and license their new creations under the identical terms.

  https://creativecommons.org/licenses/
