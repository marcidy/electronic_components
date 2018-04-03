========================
Class 1: Blinking an LED
========================

**Meta**

* set timers for 30m

**Noisebridge**

*Anti-harassment*

- gender
- gender identity and expression
- sexual orientation
- disability
- physical appearance
- body size 
- race, religion
- housing status 
- language

You can be expelled from the space for breaching any rules, and likewise, if anyone is making you feel uncomfortable, please ask them to leave, or ask for help asking them to leave.  If you are asked to leave the space, do so immediately, pack up your belongings and go without pressing a case.  There are other opportunities for mediation, please see the website for more details

*Donations*

If you find this class useful or this space useful, please donate.  You may be aware NB is facing ahousing crisis, all donations help.  Please consider making a recurring donation on the Patreon page, or jjust toss some cash in the bins around the space.  There's a bug one on the refridgerator.

If you dont find this class useful, consider donating anyways.  Maybe they'll find a better instructor.

---------------------
Welcome to Datasheets
---------------------

- Who has read a datasheet before?
- Who was programmed an arduino before?
- Anyone totally new to electronics?

This class is not about anything **specific** beyond reading datasheets, however, we will be going over specific **components** in order to understand datasheets better.  In this vein, the classes are split into varoius topics, available on the github.  

**Note**

* rearrainge class, bring power frward and final 4 classes will be the ATmega specoific stuff

**Datasheets**

- Give us the information to use the product.
- think of it more as marketing material:  If you can't use the product, why would you buy it?  Aimed at engineers, but the company wants people to buy them.

**Rough Section List**

- Electrical characteristics
- Power ratings
- Thermal metrics
- Mechanics specifications
- Packaging
- Sample aplications
- Protocols

**Questions?**

_______
Circuit
_______

- Functional Components
   * RGB LED
   * LED PWM driver
   * Arduino
      + Microprocessor - ATmega328P
      + USB-Serial converter - FTDI 232R
      + Voltage Regulator - UA78M05
      + Connectors
         - USB-MINI-B
         - ICSP
         - **Glue**
   * **Glue**

^^^^^^^
RGB LED
^^^^^^^
- Circuit is wrong, so lets figure out what I did rather than fix it.
   * I guess since I'm bringing it up here, that's a pretty big hit as to where the issue lies.
   * Ok so this is super easy but this is about reading datasheets, and this datasheet has important sections
     and characteristics important to all LEDS as well as electrical devices.


1. Front Page

   a. Features - What the device is good at
      
2. Packaging

   a. Physical characteristics of device

      i. What is it telling us about the pins?

   b. "Engineering Dimensions"

      i. :math:`\phi`

      ii. [ ]

      iii. :math:`_{-0}^{+3}`

      iv. 3 diodes, SURK, QB-D, ZG

   c. What direction does current flow through a diode with respect to the triangle?

   d. What's going to get hooked where and to what to make this glow?

3. Electrical

   a. Lens Type

   b. iv (mcd) @ 20A
      
      i. flux: :math:`- \ominus \rightarrow`

   c. viewing angle

   d. Wavelengths: Peak, Dominant, Spectral Line half width

   e. Capacitance: why is this here?  Vf;f=1Mhz ?

   f. Vf and Ir

4. Maximum Ratings

   a. Why is TA=25C there?  Does 25C matter specifically?

   b. Power Dissapation: why are they different?

   c. DC forward current vs. peak forward current ?

   d. Reverse voltage - what will happen if exceeded?

   e. Storage and soldering

5. Charts

   a. What's independant and dependant?
      
      i. I find this very important

      ii. what did the engineer vary, and what is the result?

      iii. For If vs Vf, does this imply a resistance?

   b. Luminous Intensity vs If

      i. Nice an linear.

      ii. Important to know this kind of characteristic.

   c. Forward Current derating curve

      i. Derating - operation as power drops

      ii. Nice and linear.

      iii. What's that drop off?  Why is it happening at ~85%?

   d. Luminous Intensity vs Ambient
   
      i. When might this be interesting?

   e. What's spatial distribution?

6. Packaging

   a. It comes in one.

   b. Soldering Profile

      i. What is wave soldering?

      ii. . Follow profile in time

   c. Mounting

      i. What is pitch?

      ii. What's heat shrink?

      iii. Why are there so many rules to mounting this LED?



^^^^^^^
uA78M28
^^^^^^^
- Voltage Regulator for USB power.  
   * What is USB capable of producing?  
   * What does it need to be regulated?


1. Front Page

   a. More features

      i. Chip Package

      ii. Output current

      iii. No external Components

      iv. High Power dissapation

      v.  Why are these items listed explicitly on the front page?  Differentiation and component selection.

   b. Applications

      i. Stuff you can use it in

      ii. Sometimes a very lol-worthy section as it's mostly from marketers

   c. Simplified Schematic

      i. visual example of how easy it is to use

2. Packaging
   
   a. Hey look, stuff

3. Specifications

   a. Maximum ratings

   b. ESD ratings

      i. What's all this then

   c. Operating Conditions
   
      i. why is output voltage not listed?

      ii. why is current only 500mA

      iii.  Virtual junction temperature?

   d. Thermal

      i. Junction to ambient

      ii. Junction to case (top)

      iii. Junction to case (bottom)

      iv. See more thermal spe information

      v.  Why is this section getting so much treatment compared to the LED?

         - Magic Smoke
         - Look at the input / output voltages at constant current.  Where's all that excess power going?

   e. Electrical
      
      i. Lets explain all the test conditions.

      ii. Output Voltage

      iii. Input Voltage - What's this saying?

      iv. Ripple rejection

      v. Temp Coefficient of output voltage - losing volts as temperature increases

      vi. Dropout Voltage - doesn't work anymore

      vii. bias currents - what are bias currents?

      viii. short circuit output current - 300mA?  why not 500mA?

      ix. Peak output current again - why is this larger than 500mA?

      x. Functoin Block diagram

4. Application

   a. What's this note, ...not part of component specification...  - they won't stand by the design, but here it is anyways.

   b. aside about capacitors

   c. Applicatoin curves

5. Layout

   a. PCB stuff

   b. Why is the common trace through the package?  What's that tab under COMMON?

6. Packaging

   a. Reel, Tape, Tape Dimensions - Why?  Do you know what a pick and place machine is (field trip)

   b. package dimensions:  what dimentions are these?  gauge plane?

   c. Land Pattern Data - bare minimum information, no real overlap.  What's total width?  minimum bounds box?

   d. What's solder mask?

   e. KVU0003A - why all those little squares?



^^^^^^^^^^^^^^^^^^
FT232R USB UART IC
^^^^^^^^^^^^^^^^^^
* Translates USB to UART (serial) signals
   - See things not sure about DEFINITELY look them up
      + Termination resistors
      + EEPROM
      + Virtual COM ports (?)
      + Unique Serial number
      + Level converter
      + Power on Reset

1. Front Page

   a. Ayy, look at all that cool stuff

2. Typical applications

   a. Lol worthy

      i. Set top box PC

      ii. Bar Code readers

      iii.  Just funny because hyper specific.  Can use with anything USB -> Serial.

3. Driver support

   i. Why is this necessary?  Hooking up to computer for sure

   ii. COM port -> for anyone who has used Arduino, what's this for?

   iii. USB compliance, why is this here?

4. Block diagram

   i. chip function: input output, how pins influence behavior of chip

   ii. FIFO tx/rx buffers, what do they do?

   iii. USB protocol engine, what's it most likely do?

3. Device pinouts and schematic diagram

   i. Schematic diagram devices aside: placing pins can be an art, this helps put that right on the schematic with inputs/outputs facing right direction

   ii. note the minimum VCC note

   iii. CBUS signals: lets just go through and discuss

4. Functoin description

   i. Why do we need USB -> Serial conversions?

   ii. USB termination resistors again.  Why?

   iii. Bit Bang!!  da fug is that.

   iv. Functional block diagram  take a few mins, read, raise questions

   v.  What's going to happen if FIFO buffers fill?

5. Device characteristics

   i. Note that these arn't such a huge deal because the chip is all digital.  They must be respected, but as long as within rated values, will function, not function differently based on "glue"

   ii. go through, note logical levels, different VCCs, hysterisis, different charts for different VCCIOs, what's all that about

   iii. Clock characteristics

   iv. Thermal

6. USB Power configs

   i. What's the shield

   ii.  Let's look for the config used by the Nano (pull up schematic 

   iii.  what's USB powered device mean?

7. Application Examples

   i. RS232 - anyone rememberDSUB 9 connectors?  You are old.

   ii.  USB to MCU UART interface?  Interesante.

8. Internal EEPROM

   i. Skip, not really relevent

   ii. Real quick: anyone know why it does what it does?

9. Packaging

   i. QFN-22- not what we have, but what's that fat pad in the middle for?

   ii. Solder paste Diagram?

10. Appendix A

    i. all these other docs

    ii. mark of a complicated chip

11. Appendix C

    i. important if used older version in a design to know about mistakes



^^^^^^^^^^^^^^^^^^^^^^
LED Driver - TLV59116F
^^^^^^^^^^^^^^^^^^^^^^

* Controls 16 LEDs based on commands sent over i2c by *something* (an MCU in this case)
   - Configuratoin is **stored** meaning the MCU can disconnect and go to something else
   - new interesting features are communicatoin and configurability, we will focus on those rather than other characateristics unless questions.

1. Front Page

   a. Constant Current (Remember this?)

   b. 256-step group brightness (why 256?)

   c. What a duty cycle?

   d. Why need address pins?

   e. External resistor sets output currect

      i. Here's an explanation of some **glue**

2. Applications

   a. Gaming (wut), Small signage, Sinage

   b. Basically anything that needs a few LEDs to blink and stuff

3. Description

   a. Says RGBA LEDs, we'll see why shortly

7. Skiiiiiip to 7.6 Timing requirements [skkjip this for lesson 2]

   a. First look at information related to a protocol

      i. What's a protocol, and how is it different from an interface?

   b. (go through page, need definitions for below)

   c. Typical Charateristics briefly

8. Here we go, Parameter measurement

   a. What's a clock signal

      i. Why are clocks necessaray, what are they doing?  (synchronising logic signals)

   b. How does i2c work exactly?  Assumed that you know otherwise you wouldn't be buying i2c chip.  Google!
   
      i. It's not really outlined here, but SCL is the clock signals AND the indication that communication is about to start by going low

      ii. Reset Timing

      iii. Protocol

         - Start condition

         - A1 MSB (what?)

         - A6-...?

         - D?...D0?

         - A?

         - P?

      iv. Definition of Timing

         - Thought this was just a square wave, what's all thing then

         - Why are the lines diagonal? (tr, tf)

         - HD;STA, SU;DAT, tHD;DAT, TVD;DAT, tVD;ACK, TSU;STO

            + HD - Hold

            + SU - Setup time 

            + VD - Valid

      v. Two wire   

         - Requires all this info to work, why?

            * how knows when to start?  
 
            * how knows which chip?  
 
            * What is data for chip?  
 
            * That it received data? 
 
            * When to stop?

9. Function Block diagram

   a. Note registers, have not not seen these yet

      i. what are they?  what are they for?

      ii. do a little diagram - address: data

   b. Individual brightness control

      i. 97kHz signal with 256 steps + comple other signals

      ii. 97kHz is how quickly a blink would happen, or how quickly a LED can cycle through a brightness

      iii.  Others are similar, letting you control whole group (not defined yet) of LEDs

   c. Register Maps

      i. ok so what does this mean exactly?  

      ii. Datasheets are usually ordered by detail, with lease detail first.  This is just an overview of what will come next

   d. Mode register

      i. What is it's address? and what does that mean?

      ii. Skip for now, most complicated.  Leave all defauls (what's the binary and hex value for all defaults?)

   e. Mode2

      i. bit 5, bit 3

      ii. What are the default values?

      iii. What do I write to this register to set group blinking and outputs change ok ACK?

   f. Brightness Control registers

      i. Whats all this aboot?

   g. Group duty cycle

   h. group frequency

   i. LED driver output state

      i. What does this mean?  What do i write to it to turn specific LED's on?  controled by PWM?

   j. Output Gain Control

      i. That resistor, how does it work?

10. Application Implementation

    a. Setting address

    b. i2c Bit Transfer

    c. Start and Stop conditions

    d. Acknowledge

    e. Different patterns of setings bits

    f. can read registers

    g. system config (multiple slaves/masters

11. Layout

    a. Which way are the LED's going?  When are they on vs. off?

12. End notes

    a. go through rather quick, thermal pad


^^^^^^^^^^^^
Arduino Nano
^^^^^^^^^^^^

* What is the Nano exactly?
   - It's the coombination of all those things and a circuit board.  It's not a single component, but the sum of all the components.

1. Not much going on at all!!

   a. BOM

   b. neat!

2. Let's mess with the LEDs instead.

   a. All on

   b. Turn off

   c. One for 1/2 s, then off

      i. in arduino code

      ii. using registers on TLC

   d. PWM only, half brightness

   e. Blinking only

   f. grp frequency

   
