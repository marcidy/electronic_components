=================================
Class 8: Programming the Hard Way
=================================

How does the ATmega328P actually get programmed?  We know the chip has instructions to load data, and we know that the data electrically comes over the USB <-> FTDI interface.  The programmins is based on SPI, Serial Peripheral Interface bus.  We know that the data is clocked in, and it is made up of packets, each packet will contain some kind of informatiton like command, address, data.

Something like:

.. code-block::

    Serial.write(<cmd>, <addr high>, <addr low>, <data high>, <data low>)
    Serial.write( 0xAA,  0xC5         0x5C,       0xFF,        0x00     )

In order for USB -> Serial interface to program the chip, what needs to happen?

ATmega Datasheet:

30.3.2. BLS – Boot Loader Section
    While the Application section is used for storing the application code, the Boot Loader software must be located in the BLS since the SPM instruction can initiate a programming when executing from the BLS only. The SPM instruction can access the entire Flash, including the BLS itself. The protection level for the Boot Loader section can be selected by the Boot Loader Lock bits (Boot Lock bits 1).

SPM - Store Program Memory
    SPM can be used to erase a page in the Program memory, to write a page in the Program memory (that is already erased), and to set Boot Loader Lock bits.  
    `AVR Instruction Set Manual 116.1 <http://ww1.microchip.com/downloads/en/devicedoc/atmel-0856-avr-instruction-set-manual.pdf>`_ 

16-bit op-code
    +------+------+------+------+
    | 1001 | 0101 | 1110 | 1000 |
    +------+------+------+------+

30.6. Entering the Boot Loader Program
    Entering the Boot Loader takes place by a **jump or call** from the **application program**. This may be initiated
    by a trigger such as a command **received via USART, or SPI interface**. Alternatively, the Boot Reset Fuse
    can be programmed so that **the Reset Vector is pointing to the Boot Flash start address after a reset**. In
    this case, the Boot Loader is started after a reset. After the application code is loaded, the program can
    start executing the application code. The fuses cannot be changed by the MCU itself. This means that
    **once the Boot Reset Fuse is programmed, the Reset Vector will always point to the Boot Loader Reset
    and the fuse can only be changed through the serial or parallel programming interface**.

Reset Vector
    The address to which the program will jump on a "Reset Interrupt," "Reset Event." etc.  not technically an interrupt, but...resetting pretty much interrupts everything whatever.

For example, put the boot loaded address location in the register labelled Reset Vector.  See Datasheet section 16. Interrupts for more information on vectors.


30.8. Self-Programming the Flash
    The program memory is updated in a page by page fashion. Before programming a page with the data
    stored in the temporary page buffer, the page must be erased. The temporary page buffer is filled one
    word at a time using SPM and the buffer can be filled either before the Page Erase command or between
    a Page Erase and a Page Write operation

30.8.2. Filling the Temporary Buffer (Page Loading)
    To write an instruction word:

    1. set up the **address in the Z-pointer** and 
    2. **data in [R1:R0]**
    3. write “0x00000001” to SPMCSR and execute SPM **within four clock cycles** after writing SPMCSR. 

    The content of PCWORD([Z5:Z1]) in the Z-register is used to address the data in the temporary buffer.
    
    It is not possible to write more than one time to each address without erasing the temporary buffer. 

    If the EEPROM is written in the middle of an SPM Page Load operation, all data loaded will be lost.


31.8. Serial Downloading
    Both the Flash and EEPROM memory arrays can be programmed using the **serial SPI bus** while **RESET**
    is pulled to **GND**. The serial interface consists of pins **SCK, MOSI (input) and MISO (output)**. After
    **RESET is set low**, the **Programming Enable instruction** needs to be executed first before program/erase
    operations can be executed.

31.8.1 Serial Programming Pin Mapping 
    A mini interface!

31.8.2 Serial Programming Algorithm
    A mini program!

31.8.3 Serial Programming Instruction Set
    A mini language!


What?
=====

1. Plug some wire into some pins
2. 1s and 0s come over the SPI bus, a two wire interface, into MISO and MOSI
3. That data is intepretted via the algorithm to correspond to the instructions used to load program memory.

Not complicated at all.

========
AVR Dude
========

uh, ok...

How?
====

AVR Dude
    AVR Downloader Uploader
    

Let's use output form Arduino IDE as the first stab at this thing.

Turn on "File / preferences / Show verbose output during:" tick both

Compile Empty Program(sketch) with Verbose Output
_________________________________________________

.. code-block::

    void setup() {
        // put your setup code here, to run once:
    }

    void loop() {
    // put your main code here, to run repeatedly:
    }

This is totally empty.  What microcontrollar can this run on?  More specifically, how many?  More than 1?  What if they have different instruction sets?


::

    $ arduino
    -builder -dump-prefs 
    -logger=machine 
    -hardware /hardware 
    -hardware /home/marcidy/.arduino15/packages 
    -hardware /home/marcidy/Arduino/hardware 
    -tools /tools
    -builder 
    -tools /hardware/tools/avr 
    -tools /home/marcidy/.arduino15/packages 
    -built-in
    -libraries /libraries 
    -libraries /home/marcidy/Arduino/libraries 
    -fqbn=SparkFun:avr:promicro:cpu=8MHzatmega32U4 
    -ide-version=10802 
    -build-path /tmp/arduino_build_204514 -warnings=all 
    -build-cache /tmp/arduino_cache_615219 
    -prefs=build.warn_data_percentage=75 
    -prefs=runtime.tools.arduinoOTA.path=/home/marcidy/.arduino15/packages/arduino/tools/arduinoOTA/1.1.1 
    -prefs=runtime.tools.avrdude.path=/home/marcidy/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino9 
    -prefs=runtime.tools.avr-gcc.path=/home/marcidy/.arduino15/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2 
    -verbose 
    /tmp/untitled442549665.tmp/sketch_may29a/sketch_may29a.ino

    $ arduino
    -builder -compile -logger=machine 
    -hardware /hardware 
    -hardware /home/marcidy/.arduino15/packages 
    -hardware /home/marcidy/Arduino/hardware 
    -tools /tools
    -builder 
    -tools /hardware/tools/avr 
    -tools /home/marcidy/.arduino15/packages 
    -built-in
    -libraries /libraries 
    -libraries /home/marcidy/Arduino/libraries 
    -fqbn=SparkFun:avr:promicro:cpu=8MHzatmega32U4 -ide-version=10802 
    -build-path /tmp/arduino_build_204514 -warnings=all 
    -build-cache /tmp/arduino_cache_615219 
    -prefs=build.warn_data_percentage=75 
    -prefs=runtime.tools.arduinoOTA.path=/home/marcidy/.arduino15/packages/arduino/tools/arduinoOTA/1.1.1 
    -prefs=runtime.tools.avrdude.path=/home/marcidy/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino9 
    -prefs=runtime.tools.avr-gcc.path=/home/marcidy/.arduino15/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2 
    -verbose 
    /tmp/untitled442549665.tmp/sketch_may29a/sketch_may29a.ino

Using board 'promicro' from platform in folder: /home/marcidy/.arduino15/packages/SparkFun/hardware/avr/1.1.7

Using core 'arduino' from platform in folder: /home/marcidy/.arduino15/packages/arduino/hardware/avr/1.6.20

Detecting libraries used...

::

    $ "/home/marcidy/.arduino15/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" 
    -c -g -Os -w -std=gnu++11 
    -fpermissive 
    -fno-exceptions 
    -ffunction-sections 
    -fdata-sections 
    -fno-threadsafe-statics  
    -flto -w -x c++ -E -CC 
    -mmcu=atmega32u4 
    -DF_CPU=8000000L 
    -DARDUINO=10802 
    -DARDUINO_AVR_PROMICRO 
    -DARDUINO_ARCH_AVR  
    -DUSB_VID=0x1b4f 
    -DUSB_PID=0x9204 '
    -DUSB_MANUFACTURER="Unknown"' '
    -DUSB_PRODUCT="SparkFun Pro Micro"' 
    "-I/home/marcidy/.arduino15/packages/arduino/hardware/avr/1.6.20/cores/arduino" 
    "-I/home/marcidy/.arduino15/packages/SparkFun/hardware/avr/1.1.7/variants/promicro" 
    "/tmp/arduino_build_204514/sketch/sketch_may29a.ino.cpp" 
    -o "/dev/null"


Generating function prototypes...

::

    $ "/home/marcidy/.arduino15/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" 
    -c -g -Os -w -std=gnu++11 
    -fpermissive 
    -fno-exceptions 
    -ffunction-sections 
    -fdata-sections 
    -fno-threadsafe-statics  
    -flto -w -x c++ -E -CC 
    -mmcu=atmega32u4 
    -DF_CPU=8000000L 
    -DARDUINO=10802 
    -DARDUINO_AVR_PROMICRO 
    -DARDUINO_ARCH_AVR  
    -DUSB_VID=0x1b4f 
    -DUSB_PID=0x9204 '
    -DUSB_MANUFACTURER="Unknown"' '
    -DUSB_PRODUCT="SparkFun Pro Micro"' 
    "-I/home/marcidy/.arduino15/packages/arduino/hardware/avr/1.6.20/cores/arduino" 
    "-I/home/marcidy/.arduino15/packages/SparkFun/hardware/avr/1.1.7/variants/promicro" 
    "/tmp/arduino_build_204514/sketch/sketch_may29a.ino.cpp" 
    -o "/tmp/arduino_build_204514/preproc/ctags_target_for_gcc_minus_e.cpp"
    
::

    $ "/tools-builder/ctags/5.8-arduino11/ctags"
    -u --language
    -force=c++ 
    -f - --c++-kinds=svpf 
    --fields=KSTtzns --line-directives 
    "/tmp/arduino_build_204514/preproc/ctags_target_for_gcc_minus_e.cpp"

Compiling sketch...

::

    $ "/home/marcidy/.arduino15/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" 
    -c -g -Os -Wall -Wextra -std=gnu++11 
    -fpermissive 
    -fno-exceptions 
    -ffunction-sections 
    -fdata-sections 
    -fno-threadsafe-statics -MMD 
    -flto -mmcu=atmega32u4 
    -DF_CPU=8000000L 
    -DARDUINO=10802 
    -DARDUINO_AVR_PROMICRO 
    -DARDUINO_ARCH_AVR  
    -DUSB_VID=0x1b4f 
    -DUSB_PID=0x9204 '
    -DUSB_MANUFACTURER="Unknown"' '
    -DUSB_PRODUCT="SparkFun Pro Micro"' 
    "-I/home/marcidy/.arduino15/packages/arduino/hardware/avr/1.6.20/cores/arduino" 
    "-I/home/marcidy/.arduino15/packages/SparkFun/hardware/avr/1.1.7/variants/promicro" 
    "/tmp/arduino_build_204514/sketch/sketch_may29a.ino.cpp" 
    -o "/tmp/arduino_build_204514/sketch/sketch_may29a.ino.cpp.o"

Compiling libraries...

Compiling core...

Using precompiled core

Linking everything together...

::

    $ "/home/marcidy/.arduino15/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" 
    -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections 
    -mmcu=atmega32u4
    -o "/tmp/arduino_build_204514/sketch_may29a.ino.elf" 
    "/tmp/arduino_build_204514/sketch/sketch_may29a.ino.cpp.o"
    "/tmp/arduino_build_204514/../arduino_cache_615219/core/core_SparkFun_avr_promicro_cpu_8MHzatmega32U4_af422d297eac2f8364c1557e6fc14ae0.a"
    "-L/tmp/arduino_build_204514" 
    -lm 

::

    $ "/home/marcidy/.arduino15/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-objcopy" 
    -O ihex 
    -j .eeprom 
    --set-section -flags=.eeprom=alloc,load 
    --no-change-warnings --change-section-lma .eeprom=0  
    "/tmp/arduino_build_204514/sketch_may29a.ino.elf"
    "/tmp/arduino_build_204514/sketch_may29a.ino.eep"

::

    $ "/home/marcidy/.arduino15/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-objcopy" 
    -O ihex 
    -R .eeprom  
    "/tmp/arduino_build_204514/sketch_may29a.ino.elf" 
    "/tmp/arduino_build_204514/sketch_may29a.ino.hex"


Sketch uses 3616 bytes (12%) of program storage space. Maximum is 28672 bytes.
Global variables use 149 bytes (5%) of dynamic memory, leaving 2411 bytes for local variables. Maximum is 2560 bytes.


Breakdown
_________


Tasks
-----

arduino Dump-perfs
    grabbing preferences set in the application

arduino Compile
    gathering data about the arduino file / project

Detecting libraries
    determining which native and user libraries need to be included

Generating Function Prototypes
    Function prototypes are what go in ".h" or header files.  They are "declarations" of the funtion.  We don't write them in "sketches" so they must be constructed before true compilation.

Compiling Sketch
    Actually compiling the code in the coding sense.

Compiling Core
    This is compiling the code that is specific to the core used.  The core is the microcontroller architecture.  Different Arduinos may use the same microcontroller, and even similar microcontrollers may use the same core.

Linking
    Linking is when all the different conpile code is brought together, and al lthe symbols are matched in all the files to their sources.  For example, if I defined "function_beta" in "beta.h" but use it in "neat.cpp", I need to "link" the "symbol" <function_beta> to it's definition, probably in "beta.cpp"


Commands
--------

- arduino
- avr-g++
- avr-gcc
- avr-objcopya

These commands are the "avr" counterparts to the non-avr commands we find in all programming environments.  They do the same thigns, just by targetting avr specifics.


There's a lot going on but a lot if it you don't need to know right now.

**arduino**
    - Look at the "-tools" "-hardware" and "-libraries" flags.  Very useful information to get an idea of what is happening and where it's happening.
    - note the final path: "/tmp/.../"  that's where stuff will be stored related to this compilation. DEFINITELY LOOK IN THIS PATH
        - why?  cool stuff!  we'll see below.
    - who wants to take a stab at fqbn ?  F Q * N ?

**avr-g++**
    - "g++" gnu c plus plus compilier
    - autogenerates some code and compiles the sketch
    - mmcu=atmega32u4
    - f<whatever> eh, look it up.
    - -D ...hey, DF_CPU=8000000L ?
    - -D ARDUINO_AVR_PROMICRO
    - -D ARDUINO_ARCH_AVR
    - -D USB_VID=0x1b4f
        + What's this?
    - -D USB_PID=0x9204  
        + and this?
    - -o means "the next label is the output file"
    - pre-processes the actual cpp file...leaves it somewhere in tmp!

**avr-gcc**
    - "gcc" gnu c compiler
    - elf file!
    - .o (object files) .a (archive files) "places where code i need are"

**avr-objcopy**
    - hex? eeprom? elf? eep?
    - EEP!

|

.. image:: img/dmesg.png

|

.. image:: img/port.png

Program
_______

::

    $ avrdude 
    -Cavrdude.conf -v 
    -patmega32u4 
    -cavr109 
    -P/dev/ttyACM0 
    -b57600 
    -D 
    -Uflash:w:/tmp/arduino_build_204514/sketch_may29a.ino.hex:i

Typing the above on the commandline will program your microcontroller the exact same way the IDE did it.

::

    -C : some configuration file
    -p : microcontroller core
    -c : programmer id
    -P : port
    -b : baud rate for serial communication
    -D : disable auto-erase for flash
    -U : see below

Most options are fairly obvious or simple, but -U is fairly special.  from the documentation:

::

    -U memtype:op:filename[:format]

\

    *Perform a memory operation. Multiple ‘-U’ options can be specified in order to operate on multiple memories on the same command-line invocation. The memtype field specifies the memory type to operate on. Use the ‘-v’ option on the command line or the part command from terminal mode to display all the memory types supported by a particular device. Typically, a device’s memory configuration at least contains the memory types flash and eeprom.*

memtype can be:

::

    eeprom
    flash
    fuses
    locks
    boot
    ... others


op can be:

::
    
    r - read
    w - write
    v - verify

filename - name of file to be read

format - optional

::
    
    i - intel hex
    s - Motorolla S-recod
    r - raw binary
    e - ELF (executable and Linkable Format)
    m - immediate, actual byte values
    a - autodetect

output formats (used with read op)

::

    d - decimal
    h - hex ('0x'n)
    o - octal ('o'n)
    b - binary ('0b'n)

special

::

    -v - enable verbosity, move -v, more verbose
    -V - disable automatic verify


Using '-U' with combinations of the above, different memories of the chip can be accessed and written.


Going Further
=============

Using this one line, outside the ide, will get you far, however, the other ones, the compiling ones, are where it really starts to get tricky.  Let's do a very simplie twi example.

::

    #include "Wire.h"
    
    void setup() {
      // put your setup code here, to run once:
      Wire.begin();
    
    }
    
    void loop() {
      // put your main code here, to run repeatedly:
    
      Wire.write("Hi!");
      Wire.requestFrom(1,1);
      char c = Wire.read();
      delay(1000);
      
    }

Compile..

Detecting libraries used...

::

    $ avr-g++ 
    <same stuff>
    "-I/arduino/hardware/avr/1.6.20/libraries/Wire/src" 
    "/tmp/arduino_build_204514/sketch/sketch_may29a.ino.cpp" 
    -o "/dev/null"

Using cached library dependencies for file: /arduino/hardware/avr/1.6.20/libraries/Wire/src/Wire.cpp

Using cached library dependencies for file: /arduino/hardware/avr/1.6.20/libraries/Wire/src/utility/twi.c

Generating function prototypes...

::

    $ avr-g++ 
    <same stuff>
    "-I/home/marcidy/.arduino15/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" 
    "/tmp/arduino_build_204514/sketch/sketch_may29a.ino.cpp" 
    -o "/tmp/arduino_build_204514/preproc/ctags_target_for_gcc_minus_e.cpp"


Compiling sketch...

::

    $ avr-g++
    "-I/home/marcidy/.arduino15/packages/arduino/hardware/avr/1.6.20/libraries/Wire/src" 
    "/tmp/arduino_build_204514/sketch/sketch_may29a.ino.cpp" 
    -o "/tmp/arduino_build_204514/sketch/sketch_may29a.ino.cpp.o"

Compiling libraries...

Compiling library "Wire"

Using previously compiled file: /tmp/arduino_build_204514/libraries/Wire/Wire.cpp.o

Using previously compiled file: /tmp/arduino_build_204514/libraries/Wire/utility/twi.c.o

Compiling core...

Using precompiled core

Linking everything together...

::

    $ avr-gcc
    <same stuff>
    "/tmp/arduino_build_204514/libraries/Wire/utility/twi.c.o" 
    "/tmp/arduino_build_204514/../arduino_cache_615219/core/core_SparkFun_avr_promicro_cpu_8MHzatmega32U4_af422d297eac2f8364c1557e6fc14ae0.a" 
    "-L/tmp/arduino_build_204514" 
    -lm


By including that library, all these new lines are required.  there are ways to handle this, called Makefiles, and are available on the web, but that's required to make a nice tool to handle this outside the ide.

To truly break free, you also need to move to c++ completely, no more .ino files.  You need to write the .h and .cpp files directly.  It's not hard, but it's more to learn.

avr-objdump
    You can take the elf file and convert it to a mixture of assembly and code.  This is an excellent way to learn both how the code is compiled down to assembly without learning the intermediate steps, and also what the assembly does since you can map it back to your intention.


