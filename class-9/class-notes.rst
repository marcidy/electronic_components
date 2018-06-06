======
Output
======

Controlling external devices can be done by sending some kind of signal, or by varying power delivered to the device.  As microcontrollers cannot generally provide sufficient power, many external devices need their own power source.  However, this means the microcontroller still needs to send some kind of control signal

Analog
======
Analog outputs will typically a voltage, current or frequency to an external device as a signal.  In reality all 3 are delivered at the same time, though some will be limited.  In the case of frequency, a DC signal is still a frequency, it just happens to be 0.

Applications
____________

Switching
---------

Relay
^^^^^

.. image:: basic-relay.jpg

Relays will switch a power source on and off as controlled by an input source.  Relays are typicaly mechanical, where the input source will trigger an electromagnet to complete or break a circuit.

.. image:: nc-no-co.jpg

- Normally Open (NO) means the realy is off until the input signal is received, which turns if on.  The switch is normally open.
- Normally Closed (NC) is the opposite, normally on until the input signal is received, the siwtch is turned on.

As relays are switches, they follow the same conventions like SPST, SPDT, DPDT, etc.  Basically a single relay can open or one or many switches at the same time, etc.

Relays can have timers also, configurable over a range of intervals.

They also come in a range of power ratings for both input and output.  Some are drivable by a microcontroller, and can switch wall power on and off.

Control:
Control voltage to turn output on or off.

Transistor
^^^^^^^^^^

.. image:: transistor-current-explanation.png

A transistor is taught as a digital switch, which is true, but from an analog perspective, it is really a valve.  The voltage or current into the base will control the output voltage or current.  Hooking them up to a higher power supply will control that supply with a lower voltage, or using voltage dividers can control a lower voltage with a higher one.  

Power is always an issue, however, so be sure the transistor is rated for the power dissapated by it.

Control:

Can use analog input, such as from a DAC, or a digital PWM to control transistor output between low and high voltage.


Motor Control
-------------
Motor control will vary the position, speed, and accelereation of a mechanical object.  This is not always rotation, though other motion usualyl falls under the term actuation. 

To overcome friction and inertia to move and accelerate, the motor must apply a force through a distance, aka, must cponvert electrical energy into kinetic energy.  The amount of energy the motor can output is named torque.  Torque is the measurement of the energy required to start motion, accelerate, and achieve top speed.

To accurately control a motor, one most be aware of the position, speed, and acceleration that is being output by the motor and compare that to the input.  Many motors accumulate an error with each motion, which means when the signal calls for a rotation, the motor will not always rotate the same spot, or may contiually overshoot by more each time.

Some motors are more susceptible to this that others, and some can be reset easier than others.  Control of this error is not going to be covered, but be aware that it exists if you need precise motion.


Brushed DC Motor
^^^^^^^^^^^^^^^^

.. image:: dcmotor.gif

- First kind of electrically driven motor, runs off DC power
- "brushes" are just electrical contacts.  Thin strands are light and do not need lare surface area for contact, but as they are mechanical, they will wear down and need replacing.
- DC Motor rotation
    - Motors use a at least one static magnet with N-S.  This is typically in the "stator" the stationary part of the motor.
    - Applying an electric field to a coil also creates an opposite N-S pull...for 1/2 a turn until the magnets aligg N<->S
    - a "Commutator" will reverse the current through the coil, reversing it's magnetic field, causing the next turn
- At the spot where N-S are aligned, there's a short which occurs, both in the brushes and across the coil.  waste of power.
- a solution is to use multple magnets, where the motor has no "dead zone" otherwise called a pole.

Benefits:

- Powerful
- Simple

Cons:

- wasteful
- mechanical contacts wear out and require maintenance
- requires power to hold position.  No power, goes back to whatever position is dictated by gravity or other external force.


Control:

Voltages for brushed motors are typically high, as to be expected for something which needs to generate significant energy.

Luckily, it's quite easy to control with a single transistor.  This is not the most efficient way, but it does work great for bench testing to where power isn't really an issue.  The transistor is just doing basic amplification of the input signal to a new power level.

For an NPN transistor, the high voltage (power source) connects to the collector, and a PWM signal goes into base.  The emitter goes to ground.  This is an effective way to drive the motor by controlling the power with a PWM signal.

Other controls like reverse will be covered below.


DC Brushless Motor
^^^^^^^^^^^^^^^^^^

.. image:: brushless.gif

- DC powered but uses a switching powersupply or an inverter.
    - produces an AC current which drives each "phase" of the motor
    - made possible by transistors
      - Rotor has magnets which change polarity with electric current (electro-magnets)
    - Stator has stationary magnets
- Industrial automation
    - high power, good speed-torque, high efficiency, low maintenance.
- closed loop control system for accurate control (like negative feedback)
- Servos are generally DC brushles, see below
- Very useful in transportation due to high torque.

Benefits:

- powerful
- far less wastefull
- no brushes = less maintenance

Cons:

- requires significant external circuitry to control
- Still requires holding power

Control:

It may seem like Brushless and Brushed are similar enough to be driven the same way, but unfortunately that's not the case.  Crushless motors work far better with cleaner input signals like a pure sine wave, and require some relatively complex signalling compared to the simple brushed to stop and reverse direction.

These requirements are handled by a ESC, Electronic Speed Controller.  These can be built by hand and that is a good exercise in both electronics and programming.  They can also be purchased off the shelf.  ESCs may or may not provide the functionality you require, however, like reversing the motor and good braking.  These are the same type of units found in rotocoptors or RC planes and cars.

Note:

Some ESC's require an arming sequence.  As they are designed for RC cars or rotocopters, they are meant to be "armed" via stick controls.  This needs to be emulated by the arduino for such ESCs.  

See here for code which controls an ESC:
https://gist.github.com/vitorleal/9083802


Stepper Motor
^^^^^^^^^^^^^
.. image::  StepperMotor.gif

- Stepper motors are driven by power inputs, but use multiple inputs to drive the motor in steps.
    - A step is set by the motor physics, or manufacturer, and denoted by an angle.
    - A stepper with 256 steps would have 360 degrees / 256 steps = 1.4 degrees per step
      - This is a **Full Step**
      - it is possible to drive the motor by **Half Steps** which in this case is just 1.4/2 = 0.7 degrees.
- The inputs to a stepper motor are called phases

Benefits:

- good holding power characteristics.  
- Will sit at current possition without needing to draw current. (detent or residual torque)
- Can hold a load in place while supplying current, limited by the max current available and torque sensitivity, which is found on the datasheet.
- position control is roughly handled by counting the steps required to make a full turn in a specific direction and doesn't require feedback control

Cons:

- position may drift if constantly shifting between directions
- accurate only to the resolution provided by the number of steps.
- when driving loads, the motor can lose steps as the load gets heavier, and control is lost without feedback
- Driving steppers generally requires an H-bridge circuit, and 4 output pins.

Control:

The arduino Stepper library makes using steppers easy once the H-bridge is set up.  H-bridges can be built failry easily and Stepper controllers can be purchased as well.  The h-bridge allows the driving signals to reverse the signals.  (Note you'll see darlington transistors mentioned.  That's the type of transistor used in the H-bridge.)

https://itp.nyu.edu/physcomp/labs/motors-and-transistors/lab-controlling-a-stepper-motor-with-an-h-bridge/

Control is done by changing the current through electro magnets which pull the rotor to a new position.  Once in a new position, the current is changed to go through different wires, creating a new pull.

No libray Arduino example:

http://42bots.com/tutorials/bipolar-stepper-motor-control-with-arduino-and-an-h-bridge/

Servo Motor
^^^^^^^^^^^

Servo motors are brushed or brushless DC motors, generally with a couple control features.

1. The only rotate through a fixed degree, like 360 or 180.  They are mechanically limited to these rotations
2. They are externally powered and can be driven by linear or PWM signals


Benefits:

- Will always turn to angle set by controller
- Good control of position, speed, and acceleration

Cons:

- requires feedback to perform control, such as an encoder and a control circuit
- Only 180 degress total rotation, cannot keep spinning.

Note:

Continuous Servos have the limit from 1. removed.  Basically you can break the limiter in the motor, or just buy one.  But this basically ruins any internal feedback circuit, so the control now needs to be handled externally.


The arduino servo motor libray is very easu, but fundametnally they are driven by any PWM.  The longer the duty cycle, the farther the motor will rotate towards it's maximum.  This is because there is a controller inside the servo producing the right position for the input using feedback control on an internal circuit.  Servos are always externally powered since the PWM signal is not nearly enough to drive them.

Motor Resources
_______________

https://dovermotion.com/resources/motion-control-handbook/

https://en.wikipedia.org/wiki/Brushed_DC_electric_motor

http://www.instructables.com/id/BLDC-Motor-Control-with-Arduino-salvaged-HD-motor/

https://learn.adafruit.com/adafruit-motor-selection-guide/continuous-rotation-servos


Interfaces
__________
How do we know we can hook things together?  Just read the electricla charactierists of the datasheets.  Things like Maximum output voltage being less than or equal to maximum input voltage.  Same with current, the maximum input currect should be less than the maximum output current.  Frequency doesn't matter here, exactly.  More specifically, as long as the DC maximums are respected, frequency wont matter.  Sometimes Max Peak volatages are higher than Maximum input voltages, as long as it's for some small number of seconds.  This is related to frequency.

That's fairly simple.  but what if these ratings are different and you really want to use devices together?  Especially from a cost perspective?  Remember, this is analog, not digital.  No logic level shifters yet.

Attenuation
___________
Attenuation is the opposite of amplification.  It's exactly making something smaller as much as it is shrinking the amplitide, which for a AC signal aroud 0, is shrinking the absolute value.  In the genereal case, a AC signal could be around a different DC voltage.  Attentuation would be shrinking the deviation from that DC voltage.

Voltage Divider
---------------

.. image:: volt-div.png

The simplest way to lower voltage is to split it acorss two resistors.  One resisitor disappates unused power which is useless and the other drives the load.  This is find for both DC and AC signals, because a resistor is pure V/I and has not "reactive" component like a capacitor or inductor.  Pure resistor circuits can be more compled, but 

https://www.allaboutcircuits.com/textbook/semiconductors/chpt-1/attenuators/

Current Limiter
---------------

Current limiting is trickier than voltage because current behaves differently.  It usually requires transistors to turn on and off current sources based on the load current.

putting resistors in parallel will not work, for example, as the load will draw whatever is required to pull it's voltage up regardless of what's in the control circuit.  

Amplification
-------------
Anmplifying appears straight forward but there are important detals to keep signals the right shape.  Beyond the methods mentioned above, amplifying the power of a circuit requires a network of transistors and  usualyl an op-amp.

An op amp stands for Operational Amplifier.  Rarely is a single Op-amp used to amplify power, usually one is used to amplifiy either voltage or current, with voltage being more common.  However, amplifier is a bit of a misnomber.  They amplify, but with respect to a control system, or signal processing.  For example, if you want two voltages to remain the same, an op-amp will amplify the DIFFERENCE between the voltages to take a small different into a huge signal.  This is not the same as amplifying power.

Op amps need a circuit of power supplies and resistors to form a real power amplifiery.  As we have discussed, other glue like capacitors and inductors are used to filter out noise.

There are 4 kinds of opamps based on input signal and output amplification:
Voltage signal, Voltage output
Voltage signal, Current output
Current Signal, Current output
Current Signal, Voltage Output.

Power amplification comes from a circuit.  A common circuit well worth understanding is the push-pull amplifier, very usefil for audio, as they produce signifcantly less distortion during operation.

Amplification can be a messy business, any error or noise in the input will also be magnified.

.. image:: amp24.gif

Miscelaneous Control
____________________

Breaking
--------
Breaking a motor electrically is far less eficient than doing so mechanically.  A normally closed electromagnet that snaps closed a sa break will use no power to hold the motor in place.

Regenerative breaking is when the force used to break the motor feeds into a generator creating power.  Circuits for such can be found on the web, it's a common topic.

Rotary Encoders
---------------

.. image:: rotary.jpg

To track position, speed, and acceleration, DC motors use rotary encoders.  Some uselight, some use electrical contacts.  The idea is to put sign posts that can be detected and feed that motion back to the controller.

They are called encoders as they encode the position in binary.  It's useful to look this up, as the encoding is fairly clever, called Grey codes.

.. image:: rotary-grey-code.png

.. image:: rotary-flattened.jpg

H-Bridge
--------

.. image:: h-bridge.png

A H-bridge s used to reverse the direection of a motor by switching the signal paths from input to outputs.  Any kind of switching can be used, like relays or transistors.  the key is, as always, to match input-output characteristics.  

Constsructing an h-bridge is fairly simple from DPDT switches.  It's possible to find relays with exactly this configuration.

.. image:: motor-h-bridge.gif

Motor Controller Boards
-----------------------

There's a bunch of off the shelf motor controllers available, like "shields" or specific controllers which run on i2c or something.  Defnitely worth using after getting a handle on their operation.  May come with one of all of the controls above to play with.


Digital
=======
We've spoken about the majoiity of digital outputs, being logic values, communication, and PWM.  PWM is interesting
so we'll go overit again, as it is a way to transform a frequency output into a voltage value.


PWM
___

A type of digital to analog converstion using a frequency and a duty cycle.  The frequency is fast enough to the input of the device such that it is indistinguisable as a constant signal.  The signal is digital, form (let's say) 5V to 0v.  The duty cycle is how long the signal is a 5V compared to the full width of the cycle.  Varying the duty cycle from 0 to 100% determines the voltage seen at the device.

The number of steps available inthe duty cycle is limited to the number of bits available to the clock creating the signal.  This again gives a resultion of the duty cycle , 5V/255 steps ~.02 volts per step.

.. image:: pwm.gif

DAC/ADC
_______

.. image:: ADC.gif

Digial to Analog converstion and Analog to Digital converstion are the opposites of each other.  The concept is simple, using some number of available bits, convert between the two representations of the same value.  so a 0v-5V range can be represented as an analog value, or as the digital number in that range, 255 for 5V and 0 for 0V.

Once again, there is a resolution.  If resolution higher than the native available on the chip is required, then new hardware is required.

It's possible to change the *range* of a DAC or ADC, but not the resolution, by stringing them together in series.


DAC/ADC **sample** the input signals.  What this means is they take discrete values to try to reconstruct a continuous signal.  In the DC case, it's fairly straight forward, limited only by resolution.  In some bad situations, you can be right on the line of 127 and 128, and the sampled point jumps around.  This is handled in software via debouncing.

.. image:: sample.gif

In the AC case, The DAC is trying to create a continuous wave such as a sine wave.  The ADC is trying to store a samples of magnitude of the wave at various points in time.  Consider digital audio, it only contains bits.  Some bits store the amplitude, some store the frequency.

To create a smooth wave from a digital signal, filtering is required on the output of the DAC.  This can be passive filters like combinations of inductors, capacitors, and resistors, or active filters using op amps.

Clearly DACs are used to control analong devices.  The arduino code will use the "analongWrite" function to set the value in the DAC.  the output is a single pin, typucally named with a leading "A."

Likewise, to use the ADC, the arduino uses the same analog pins.  In this case, tthe analog signal is input into the pin, and read with "analogRead".  The internal ADC will convert this to a 8 bit number from 0 to 255.

Meaasuring signals larger or smaller than the logic levels allowed on the pin can be handled using voltage dividers where appropriate. Using external DACs and ADCs is best when outside those bounds because of resultion or other issues.  There would usualyl communicate via an interface like i2c.

.. image:: ADC-internal.gif


Sample Time
-----------
As we know, things take time in a microcontroller.  When the ADC takes a measurement, it takes a few clock cycles for the value to be calculatd and stored before the next measurement.  Just like measuring the logic level of a signal required a hold time, so does the converstion.  This has an implication for the frequency of the analog signal that can be measured.  If it's varying too fast, no reliable measurement can be made, or most specifically, the measurement might be consistntly wrong.

In information theory there is a number called the Nyquist Frequency.  This is the rate of the sampling which can accurately measure an AC signal.  It's can be slower than the signal, but shoudl conform to certain ruless.  This is where sampling rates come from.  The human ear generally only hears up to 22Kh.  By sampling at 44Khz, the full analog waveform is guaranteed to be stored without loss.

So there is some resultion of amplitude which is determined by the number of bits you have the converter, and the resultion of time you have to create of measure a signal.  What smaple rate is to the ADC, smoothing is to the DAC.a

.. image:: DAC-error.gif

http://www.bb-elec.com/Learning-Center/All-White-Papers/Data-Aquisition-and-IO/The-Fine-Art-of-Analog-Signal-Sampling.aspx


