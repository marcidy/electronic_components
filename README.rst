===============================
Noise-bridge - Pwnning the Nano
===============================

   *Quite possibly the most complicated way to blink an LED that does not require vapor deposition*


This series of classes will use close readings of datasheets and programming manuals to reverse engineer a circuit which blinks an LED using an Arduino Nano and an LED controller.  First, we program an Arduino Nano to program an i2c device to blinks an LED.  Once understading inter-chip communication, the AtMEGA 328P microcontrolller is explored and we learn to interface with it directly, skipping programming altogether.  Next, we'll look at the firmware directly and figure out how to reverse engineer it, learning about binary files, assembly, and compilation along the way.  The series will close out with transistors, and a discussion of power.


Goal
----

Self-sufficiency in electronics.   Understsand how to select components based on electrical, functional, and power requirements, as well as understand constraints.  Move beyond the arduino ecosystem: the only shield you need is +2/+4 against dark elves.


Knowledge
---------

   - Electrical: 
     A basic knowledge of Voltage and Current is all that is required.  
   - Coding:  
     Having created, compiled ('verify'), uploaded, and tested any simple program to an arduino it good background, but I will not be covering anything specific except the Wire library.  Even then, it will be towards a specific end, not to understand the code.  That being said, there are activities which can only be done with a chip. 


Materials
---------

My goal is to run the class off downloadable datasheets and some code examples, requiring any coding beyond what I show.  However, if you want an Arduino and can't get one, let me know sooner than later.

When first looking at datasheets the sice of an ATMEGA, a paper copy is helpful to take notes.  

Having access to a machine that can run the Arduino IDE, especially in class, is best.

With the IDE installed, you should find the following:

  - avr-* commands
  - Where does your ide put the binary files created after pressing "verify"?
  - Where are the libraries on disk, specifically the Wire library?  twi.c and and Wire.cpp
    alternatively found here: https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire/src


Other Arduino's can substitute when looking at code.  When we hit class 6, it will be beneficial to have ANY arduino thats is programmable.  Doesn't matter which one.  Maybe there are some sitting around the space.  



Class 1: Blinking an LED
------------------------

   *The easy way.*

We'll be reading the documentation for an RGB LED, a LED PWM controller, and the Arduino Nano board, but not the ATMEGA controller.  We'll interact with the hardware by sending instructions from the Arduino to the PWM controller via i2c to blink the LED.

Datasheets:

   - RGB LED: https://www.arduino.cc/documents/datasheets/LEDRGB-L-154A4SURK.pdf 
   - LED Controller: http://www.ti.com/lit/ds/symlink/tlc59116.pdf
   - Arduino Nano: https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf

Other Material:

   - https://en.wikipedia.org/wiki/List_of_integrated_circuit_packaging_types


Class 2: Communication
----------------------

   *WHAT?!*

Interface and Protocol

   - Walkie Talkie
      *No you go, no, ok, go ahea- what?  oh, ok, i mean, wait, no no, you- i was gonn-  no reall...*
   - Clocking
      + Voltage High
      + Voltage Low
      + Rise Time
      + Edges
   - Binary Counter
   - Clock Scaler
   - In Depth: i2c
   - Interru-

      A class room protocol

      /proc/interrupts

      IRQs

Material:

   - http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf
     Section 26
