==============
Pwning Arduino
==============

>>	*Quite possibly the most complicated way to blink an LED that does not require vapor deposition*


This series of classes will use close readings of datasheets and programming manuals to reverse engineer a circuit which blinks an LED using an Arduino Nano and an LED controller.  First, we program an Arduino Nano to use the i2c bus to communicate with the LED driver to blink an LED.  Once understanding inter-chip communication, the ATmega328 microcontroller is explored in depth and we learn to interface with it directly over USB, skipping a programmer altogether!  Next, we'll look at the firmware (e.g. compiled code) directly and figure out how to reverse engineer it, learning about binary files, assembly, and compilation along the way.  The series will close out with a discussion of power.


Goal
----

*Self-sufficiency with electronic components.*  Understand component selection based on electrical, functional, and power requirements, as well as constraints.  Move beyond the Arduino ecosystem: the only shield you need is +2/+4 against dark elves.


Knowledge
---------

	- **Electrical:** A basic knowledge of Voltage and Current is all that is required.  
	
   	- **Coding:**  Having created, compiled ('verify'), uploaded, and tested any simple program to an Arduino is good background, but I will not be covering anything specific except the Wire library.  Even then, it will be towards a specific end, not to understand the code.  That being said, there are activities which can only be done with a chip. 


Materials
---------

The class will run from downloadable datasheets and some code examples.  An Arduino is not necessary, but is helpful.  If you want an Arduino and can't get one, let me know sooner than later.

When first looking at datasheets the size of an ATmega328, a paper copy is helpful to take notes.  It also kills some trees.  Something will be necessary for class, however.  

Having access to a machine that can run the Arduino IDE, especially in class, is best, but I will make best efforts to have all files projected on a screen.

If you install the IDE, you should find the following:

- avr-* commands
- Where does your ide put the binary files created after pressing "verify"?
- Where are the libraries on disk, specifically the Wire library?  (twi.c and Wire.cpp)

twi.c and Wire.cpp can alternatively found here: https://github.com/Arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire/src

I will be using the Nano for class, but other Arduinos can substitute when looking at code.  When we hit class 6, it will be beneficial to have ANY Arduino thats is programmable.  Doesn't matter which one.  Maybe there are some sitting around the space.  


Class 1: Blinking an LED
------------------------

>>	*The easy way.*

We'll be reading the datasheets for an RGB LED, a LED PWM controller, and the Arduino Nano board in depth.  Note we will not go over the ATmega328 controller, saved for a later class.  We'll interact with the hardware by sending instructions from the Arduino to the PWM controller via i2c to blink the LED.

Datasheets
__________

- RGB LED: https://www.Arduino.cc/documents/datasheets/LEDRGB-L-154A4SURK.pdf 
- LED Controller: http://www.ti.com/lit/ds/symlink/tlc59116.pdf
- FTDI-USB: http://www.ftdichip.com/Documents/DataSheets/ICs/DS_FT232R.pdf
- Arduino Nano: https://www.Arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf

Other Material
______________

- https://en.wikipedia.org/wiki/List_of_integrated_circuit_packaging_types


Class 2: Communication
----------------------

>>	*WHAT?!*

Interface and Protocol
______________________

- Walkie Talkie

>	*No you go, no, ok, go ahea- what?  oh, ok, i mean, wait, no no, you- i was gonn-  no reall...*
		
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

Material
________

- http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf
	+ **Section 26 only**


Class 3: ATmega328 Components and Registers, Arduino Wire Library
-----------------------------------------------------------------

>>	*I kinda thought a microcontroller was just one thing.*

Basic programming knowledge is a strong suggestion: setting variables, defining and calling functions, and flow control.  :code:`twi.c` and :code:`Wire.cpp` will be covered in depth.  This library was used in the first class and discussed in the second class.  Breaking down the protocol and then reading about an implementation provides insight into all protocols, especially those used to program the Arduino.

Material
________

- http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf
- https://github.com/Arduino/Arduino/tree/master/hardware/arduino/avr/libraries/Wire/src
	+ twi.c and Wire.cpp only
   
Bonus
_____

- Reverse Polish Notation

Class 4: Binary Logic: The magic of Ada Lovelace and a two state system
-------------------------------------------------------------------------

>>	*A bit?  A bit of WHAT?!*
	
>>	*2B or not 2B, that is...always going to evaluate to True.*

- AND/OR/NAND/NOR/XOR
- Binary arithmetic
- Ripple carry adder
- ALU

Bad Physics Lesson
__________________

- JFETs
	+ https://en.wikipedia.org/wiki/JFET

Bonus
_____
- Listen to a decaying mind try to remember FPGAs
- Why is everything in 2 digit hex, e.g. 0xAD
- 0xDEADBEEF


Class 5: ATMega328 Core
-----------------------

>>	*This is not a joke*

- What is Architecture?  Core?  Periphery?
   	- What is overclocking?
   	- Organization of RAM
   
This class will cover the ATmega328 in serious detail from a hardware perspective.  Reading dataseets with this rich of deatil should not be intimidating, just incredibly frustrating and boring, so let's get you there.

Material
________

- http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42735-8-bit-AVR-Microcontroller-ATmega328-328P_Datasheet.pdf


Class 6: Coding vs Programming
------------------------------

>>	*...and don't get me started on scripting*

Material
________

- https://en.wikipedia.org/wiki/Atmel_AVR_instruction_set
	+ A good "more than an" overview, perhaps read before class
- http://ww1.microchip.com/downloads/en/devicedoc/atmel-0856-avr-instruction-set-manual.pdf
	+ This is what we will be using in class


Class 7: Programming a microcontroller the hard way
---------------------------------------------------

>>	*What if we take this thing here, and put it over there?*

Material
________

- AVRDUDE: http://www.nongnu.org/avrdude/user-manual/avrdude.html
- section 31.7.4 from Atmel Datasheet

- avrdude terminal mode
	+ dump
	+ erase
	+ send
		* Where can you get to from here?
        * Can you set registers?
		* Can you read what's in code memory?  Write?
		* Can you blink the LED from here?
- fuse bits, program memory, boot process

Bonus:
Programming registers and outputs using binary


Class 8: Binary
---------------
>  *'Why do they keep calling it _a_ binary? It IS binary.'  - Me, at my first job*
- Briefly on binary formats, endian, LSB, MSB
- hex/bin output from avrdude compilation
- dumping and examining firmware aka microcontroller code
- Intro to reverse engineering software
- Drivers

Material
_______

- avrdude output from compilation and dump from microcontroller
	+ These can be found in the 'asm' directory


Class 9: Program Compilation and Execution
------------------------------------------

>>	*Anyone ever used the Boss Key?*

- preprocessing: *adding a bunch of stuff*
- assembly: *uh, putting it together?*
- compilation:  *err...putting it MORE together?*
- linking: *putting it together with even MORE stuff?  ug.*

- disassembly, *or why everything get cracked all the time forever*
	+ Two way vs one way functions
	+ you know who ELSE used one way functions?

- Program Execution
- The Stack
- The Stack Pointer
- Saving State on the Stack
- Restoring State

Discussion Bonus
________________

- Code is in memory
- The microcontroller can access that memory, aka read and (over-)write the code itself while it is excuting.
- If you become aware of your surroundings inside the microcontroller at a pause in execution, what would you do first?
- Could you self replicate and send a copy of yourself somewhere?
- what about load a small program into memory? Jump to that location? Start a small shell open on port 1023?
	+ bonus for why 1023 and not 1025

Self Study: Language
____________________

- What is a language?  Who is Chompsky?  Why are computer languages, uh, languages?  More importantly, who is SasQ?
- Grammar
- Parsing
- Tokenizing
- Lexing
- Abstract Syntax Tree
- ENBF

	https://stackoverflow.com/questions/2842809/lexers-vs-parsers - SasQ comments are the best


Class 10: Power
---------------

>>	*Have you tried turning if off and turning it back on again?*

- Supply
   + Rectifiers/Inverters
   + Switching
   + Step-up, step-down, boost, buck
   
- Fooling mother nature, aka, you cant.  
	+ Power In = Power Out *In this house we obey the 2nd law of thermodynamics!*
	+ Heat, Flow, Dissipation, Cooling

- Batteries
   + Primary / Secondary 
   + Lithium (coin)
   + Li+ / Li-Po / Li-Ion **>>>DANGER<<<**
      * The Bulge
   + Charging **>>>EVEN MORE DANGER<<<**
   + Protection Circuits (CPB/CPM) **>>>SLIGHTLY LESS DANGER<<<**
   + Just go here and read: **batteryuniversity.com**

- Buttons
   + Debouncing


Material
________

- https://www.recom-power.com/pdf/Powerline-AC-DC/RAC03-SC.pdf
- https://www.cui.com/product/resource/vof-10b.pdf
- http://www.ti.com/lit/ds/symlink/lmz21701.pdf
- http://www.ti.com/lit/ds/symlink/mc33063a.pdf
- http://www.mccsemi.com/up_pdf/MB05S-MB10S(MBS-1).pdf
- https://cdn-shop.adafruit.com/product-files/1317/C1515_-_Li-Polymer_402025_150mAh_3.7V_with_PCM.pdf


Further Reading
_______________

- https://www.androidauthority.com/lithium-ion-vs-lithium-polymer-whats-the-difference-27608/


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
      
