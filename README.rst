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

Datasheets
__________

   - RGB LED: https://www.arduino.cc/documents/datasheets/LEDRGB-L-154A4SURK.pdf 
   - LED Controller: http://www.ti.com/lit/ds/symlink/tlc59116.pdf
   - Arduino Nano: https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf

Other Material
______________

   - https://en.wikipedia.org/wiki/List_of_integrated_circuit_packaging_types


Class 2: Communication
----------------------

   *WHAT?!*

Interface and Protocol
______________________

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
      + A class room protocol
      + /proc/interrupts
      + IRQs

Material
________

   - http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf
     + Section 26 only


Class 3: ATMEGA328 Components and Registers, Arduino Wire Library
-----------------------------------------------------------------
   *Holy shit there's a lot in a microcontroller, I kinda thought it was just one thing, you know?*

   Basic programming knowledge is a strong suggestion; setting variables, defining and calling functions, and flow control.  :code:`twi.c` and :code:`Wire.cpp` will be covered.  This library was used in the first class and discussed in the second class.  Breaking down the protol and then reading about an implementation provides insight into accessing and setting registers in the ATMEGA.

Material
________

   - http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf
   - https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire/src
     + twi.c and Wire.cpp only
   
Bonus
_____

   - Reverse Polish Notation


Class 3.5: Binary Logic: The magic of Ada Lovelace and a two state system
-------------------------------------------------------------------------

   *A bit?  A bit of WHAT?!*

I'm not sure what to do with this class.  It's unrelated to the topic at hand, but very useful to know in general.  Let's talk about it and figure out who's interested and when to do it.

   - AND/OR/NAND/NOR/XOR
   - Binary arithmatic
   - Ripple carry adder
   - ALU

Bad Physics Lesson
__________________

   - JFETs

Bonus
_____
   - Listen to a decaying mind try to remember FPGAs
   - Why is everying in 2 digit hex, e.g. 0xAD
   - 0xDEADBEEF


Class 4: ATMega328 Core
-----------------------

   *This is not a joke*

   - What is Architecture?  Core?  Periphery?
   - What is overclocking?
   - Organization of RAM

Material
________

   - http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf

Class 5: Coding vs Programming
------------------------------

   *...and don't get me started on scripting*

Material
________

   - https://en.wikipedia.org/wiki/Atmel_AVR_instruction_set
   - http://ww1.microchip.com/downloads/en/devicedoc/atmel-0856-avr-instruction-set-manual.pdf
     + This is what we will be using in class


Class 6: Programming a microcontroller the hard way
___________________________________________________

   *What if we take this thing here, and put it over there?*

Material
________

   - AVRDUDE: http://www.nongnu.org/avrdude/user-manual/avrdude.html
   - section 31.7.4 for Atmel Datasheet

   - avrdude terminal mode
     + dump
     + erase
     + send
       * Can you blink the LED from here?
       * Where can you get to from here?
       * Can you read what's in memory?  Write?
   - fuse bits, program memory, boot process


Class 7: wtf is a binary
------------------------

   - Briefly on binary formats, like endian
   - hex/bin output from avrdude compilation
   - dumping and examining firmware aka microcontroller code
   - Intro to reverse engineering software
   - Drivers

Material
_______

   - avrdude output from compilation and dump from microcontroller


Class 8: Program Compilation and Execution
------------------------------------------

   *Anyone ever used the Boss Key?*

   - preprocessing: adding a bunch of stuff
   - assembly: uh, putting it together?
   - compilation:  err...putting it MORE together?
   - linking: putting it together with even MORE stuff?  ug.

   - disassemply, or why everything get cracked all the time forever
      + Two way vs one way functions
      + you know who ELSE used one way functions?  Hitler.

   - Program Execution
   - The Stack
   - The Stack Pointer
   - Saving State on the Stack
   - Restoring State

Discussion Bonus
________________
   - Code is in memory
   - The microcontroller can access that memory, aka read and (over-)write the code itself
   - If you become aware of your surroundings inside the microcontroller, what would yo do first?
   - could you self replicate and send a copy of yourself somewhere?
   - what about load a small program into memory, jump to that location, and start a small shell open on port 1023?
     + bonus for why 1023 and not 1025

Self Study: Language
____________________
	- What is a language?  Who is Chompsy?  Why are computer languages, uh, languages?  More importantly, who is SasQ?
	- Grammar
	- Parsing
	- Tokenizing
	- Lexing
	- Abstract Syntax Tree
	- ENBF

	https://stackoverflow.com/questions/2842809/lexers-vs-parsers - SasQ comments are the best


Class 9: FETs, Logic Gates:
---------------------------

   *2B or not 2B, that is...always going to evaluate to True.*

   [Need Materials and class desc]

Class 10: Power
---------------

   *Have you tried turning if off and turning it back on again?*

   - Supply
      + Rectifiers/Inverters
      + Switching
      + Step-up, step-down, boost, buck
   
   - Fooling mother nature, aka, you cant.  
      + Power In = Power Out *In this house we obey the 2nd law of thermodynamics!*
      + Heat, Flow, Disapation, Cooling

   - Batteries
      + LiPo  >>>DANGER<<<
        * The Bulge
      + Charging >>>EVEN MORE DANGER<<<
      + Protection Circuits >>>SLIGHTLY LESS DANGER<<<
      + Further reading: Battery University

   [Datasheets]

Bonus
_____

   - Do NOT build energy weapons, like a stun gun.  
   - Just because it's easy and cheap does not mean you should do it, it's illegal.  
   - And if you're going to, don't put it in innocuously shaped object easy to conceal.  
   - They can run on as little as 9V, so don't google it and find the exact circuit you need pretty easily.  
   - Just don't do it with LiPos(SERIOUSLY).  Or ever.


Discussion: What's next?
________________________

   - https://en.wikichip.org/wiki/amd/microarchitectures/zen
     + You should be able to read this and have a good idea of what's going on.
   - https://en.wikipedia.org/wiki/Speculative_execution
   - https://github.com/marcan/speculation-bugs
      
