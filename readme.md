# Dreh Ding
An optical illusion.

- [mains/](mains/) - different solution sketches to this project
- [tests/](tests/) - various minimal toy sketches for testing and measuring
- [sandbox/](sandbox/) - place for random sketches and tries
- [ui/](ui/) - user interface tools to interact with the Arduino

## The project
**Dreh Dings** develops around the [stroboscopic effect](https://en.wikipedia.org/wiki/Stroboscopic_effect). The idea is to place a rotating geometrical object (e.g. a cube) in the centre of a stage and light it at specific intervals with flashes from a number of surrounding LED lights. By varying the flash intervals, various optical illusion effects can be generated. See the following images for a high level schema:

![High level schema](images/schema.png)

The project is realized through a number of hardware components and a microprocessor for controlling. Basically, the object turns on a motor whose speed we can modulate. The motor additionally contains a hall sensor (speedometer, clock) to measure the rotation speed. The hall sensor's signal is then used to flash the LEDs at the desired intervals.

The most simple flash configuration is be to flash a single LED always at exactly the same fraction of the object's rotation. Since the object is only illuminated when in the same position, it appears stationary to the observer.

More advanced and interesting flash configurations are also possible.

### The components

#### The processor
The processor lies at the core of the project. Here, all the input signal are gathered and the output signals send to the various components to ensure a seamless interaction. Any programmable microprocessor with digital and at least one analogue PIN can be employed. We use [Arduinos](www.arduino.cc) or their variants for their size and simplicity.


#### The DC motor
The [DC motor](https://en.wikipedia.org/wiki/DC_motor) rotates the illuminated object. It should be powerful enough to drive it fitfully. And it should be of sufficient quality to minimize vibrations, as these weaken the stroboscopic effect. We also want to control the motor's rotation speed, which is usually realized through a [PWM](https://en.wikipedia.org/wiki/Pulse-width_modulation) input. Additionally, the motor should contain a speedometer, usually a hall sensor (see below for more details on this component). All of these controls are already included in modern fan motors, which are therefore our motors of choice.

A typical specification sheet of a fan motor can e.g. look as follows:

![Motor specifications example](images/motor_specs.png)

##### Power supply
Here the black and red wires. Arduino's can only supply 3V or 5V, hence you will need an additional power supply to drive this motor. Take care to keep the power lines separated: Supplying too high voltage to the Arduino or a voltage over 3V to one of the Arduino's input pins can destroy the processor. All ground wires should be connected, though.

##### Speedometer / hall sensor
Here the yellow wire. Analogue output that sends a PWM signal. See below for more details.

##### Rotation speed control
Here the blue wire. Analogue input that expects a PWM signal. This signal is then averaged, and [the average voltage received determines the motor's rotation speed](https://www.electronics-tutorials.ws/blog/pulse-width-modulation.html).

##### Rotation direction control
Here the white wire. Digital input that expects a high or low signal. Depending on the signal, the motor turn clockwise (CW) or counterclockwise (CCW). We do not make use of this wire.



#### The hall sensor (build into the motor)
A hall sensor is a device to measure the magnitude of a magnetic field. To understand how the sensor works in this setup, we must first look at the DC motor's inner workings:

![DC motor schema](images/motor_dc_schema.png)

The *stator* is the stationary casing, the *rotor* the movable inner element. The former contains wire *windings*, the latter is covered with a number of *permanent magnets* with alternating polarity. When power is supplied, the wirings are switched on and off in order, creating a magnetic current that attracts or repels the permanent magnets depending on their polarity, and, ultimately, causes the rotor to turn. There are other types of DC motors, but they work similarly.

Now let's look at an equivalent schema, but with an hall sensor added:

![DC motor schema with hall sensor](images/motor_dc_hallsensor.png)

The *hall sensor* (H1) is placed at a fixed position between two wirings in the stator. Every time a permanent magnet passes, it registers a change in the magnetic field. Or, more simple, when it has an N-polarity magnet in front of it, it creates an output. And when it has an S-polarity magnet in front of it, it does not create an output. When the motor is rotating, the permanent magnets pass continuously in front of the hall sensor, causing it to generate a PWM signal as can be seen on the right.

The generated PWM has a fixed-length duty cycle of 50% (aka it is on 50% of the signal time), since the permanent magnets are of equal length. It's frequency (rate), on the other hand, depends directly on the motor's rotation speed. That's why the signal can be utilized as a speedometer.

When connected to an input pin of the microcontroller, we will see a LOW->HIGH signal transition each time a N->S permanent magnet transition passes in front of the hall sensor. And a HIGH->LOW signal transition each time a S->N permanent magnet transition passes in front of the hall sensor (Not sure about the N->S, S->N order, though. But it doesn't matter for our application). These are usually captured with hardware interrupt signal in the microcontroller's code (more on this in the code section). Important is, that to know the rotation speed of the motor, we must know the number of permanent magnets it contains, as these determines the number of signals we will receive per motor rotation.

This value should be given in the motor specifications. If it is not supplied, you can find some code in the [tests/](tests/) folder to experimentally determining the number. Usual values are somewhere between four and 24 magnets. If you count only the LOW->HIGH or the HIGH->LOW transitions, you will receive exactly half the number of signals. If you count both, you will receive as many signals as there are permanent magnets.

Although unusual, some motors have e.g. 18 permanent magnets, which results in an uneven number of nine signals when counting only the LOW->HIGH transitions. In these cases it might be advantageous to count all transitions to achieve a signal number of 18, which is easier dividable.

##### Pull up resistor
The hall sensor must be connected to it's pin with a pull-up resistor set-up, as shown in the following image:

![Hall sensor pull-up schema](images/hall_pullup.jpeg)

This is necessary, as the signal it produces is relatively unstable and of varying and (probably) unknown voltage. Furthermore, this causes a noise signal on the wire if the hall sensor is of (aka the motor not turning). Such a pull-up resistor set-up [can also be enabled on the microprocessor directly](https://www.arduino.cc/en/Tutorial/BuiltInExamples/InputPullupSerial), without the need of an external resistor and additional power supply. Simply set the chosen [digital input pin](https://www.arduino.cc/en/Tutorial/Foundations/DigitalPins) as follows:

```cpp
pinMode(PIN_HALL, INPUT_PULLUP);
```

Note that this will invert the HIGH and LOW signals.

##### Pin 13 or the LED pin
Most Arduino boards have one pin (usually 13) with a directly connected LED. This is a useful set-up to visually confirm that a signal arrives at the pin. But the hard-wired LED makes it a unsuitable choice for a pin in `INPUT_PULLUP` mode. Don't use this particular pin as input for the hall sensor.


#### The LEDs, with LED driver board
The LEDs are usually not directly connected to the microcontroller, but rather to an LED driver board. That way, an external power supply can drive the LEDs safely and reliably. The connection to the microcontroller's pin can be either a source or a sink. If pin is used as LED sink, you set the register of the pin to LOW to turn the LED on. And vice-versa.

For maximum effect variability, choose LEDs of different colours in different positions.

The pins should be digital. We put them OUTPUT mode and set to one level (HIGH or LOW) to switch the LED on. And to the other level to switch it off.

#### The power supply
The microcontroller can be supplied with power through the USB connection. If you want to run the set-up also separated from the PC, you will have to supply power from another source, too. Since both, the motor and the LEDs, are ideally also supplied by an external power supply, you can supply all components together, as long as their requirements match.

Note that all sinks should be connected, even if multiple power sources are used.

See the schemas in the project variants below for the exact set-up.

#### The rotating object
The object can be anything. Depending on its shape, you can achieve different stroboscopic effects. Typical choices are 3D geometrical shapes, such as cubes, octahedrons, tetrahedrons, etc. But you can also mount a 3D printed anime figurine on the motor, if you wish.

### Hardware variant I (small setup)

!TODO:
- concrete components and their specifications
- schema of wiring
- special considerations for this set-up
- photo of set-up

Teensy 4.0, Arduino compatible
[processor specifications()]

[motor specifications](https://ae01.alicdn.com/kf/HTB1I91_IpXXXXb9XpXXq6xXFXXXc/221879944/HTB1I91_IpXXXXb9XpXXq6xXFXXXc.jpg)
- Note that no FG singal is described here. In the specs of the bigger motor (https://ae01.alicdn.com/kf/H9b7d23087b9f4301bd53cda0bcdb2bbfT.jpg) it is.
- The smaller nevertheless seems to have a tacho that sends a signal on the yellow cable (we measured it). How exactely it is defined remains a mystery.

- hall sensor has 9 LOW->HIGH signal per rotation, that means 18 if also HIGH->LOW is measured
- LEDs: A HIGH signal switches them off, a LOW switches them on!
- LEDs: The fastest still visible flash (on time interval) is 100 microseconds aka 0.1 milliseconds


### Hardware variant II (large setup)

!TODO:
- concrete components and their specifications
- schema of wiring
- special considerations for this set-up
- photo of set-up

[motor specifications](https://ae01.alicdn.com/kf/H9b7d23087b9f4301bd53cda0bcdb2bbfT.jpg)

## The software

!TODO:
- describe main software design pattern here

## Flash configurations

!TODO:
- describe different configurations for the flashes here and what effects they cause
- depends on objects used
- see also [stroboscopic effect](https://en.wikipedia.org/wiki/Stroboscopic_effect)

- single LED flash = stationary object
- multiple LED flash = multiple interleaved stationary objects
- single LED flash, then slowly changing flashpoint = stationary object that slowly moves
- two LEDs flash, then slowly changing flashpoints, both in opposite directions = two stationary objects rotating against each other
- one LED at it's flashpoint on; after some time, switch off and second on, then off and third on, usw.
	- first long on-times for each LED; then shorter, then longer again
	- = multiple objects switching in and out, sometimes faster, sometimes slower
- put an object on one side of the octahedrons
	- = can we make that appear and disappear by using a single LED and switching flashpoints?
	- maybe some more ideas with this?

## Idea collection

- write a function to detrmine the rounds-per-minute/second/micros
	- count interrupts with interrupt counter
	- add computeRpm function to loop
	- uses time to read time passed, reads interrupt counter, divides by interrupts-per-round, divides by time in seconds, rounds
	- returns rpm/rps
	
```cpp
int rps():
	ic = interrupt_counter / HALLS_IPT
	unsigned long current = millis();
	rps = ic / (last - current) * 1000
	last = current
	ic = 0
	return rps
```

- write function that flashes LED at flashes / round
	- we know the rps value
	- means LED should flash X=s/rps times per second
	- implement with micros/millis
	
- add fraction delay form round start
	- somehow synchronize starting point of LEDs time in previous function
	- then flash them again X times
	- but shift starting point by a milli/micro value
	- should cause unsynced LEDs
	
- loop() called ca. at 117 kHz aka 117,000 times/second?
	- Could be more or less, depends on board, code in loop, etc.
	- Not a good value to build anything on. Use rather micro or milliseconds
	
- write time-based version of code
	- measures rotations-per-micros
	- controls LEDs with parameters:
		- flash each fraction (<1) or multiple (>=1) of rotations
	- provides better granularity control
	- might de-sync after some runtime
		- figure out a way to re-sync with hall signal from time to time

- write an LED class
	should contain LED functionality, counters, steering methods, parameters, etc.

- change to measure also HIGH->LOW with interrupts -> better number (18 instead of 9) for dividing

## Appendix / Notes / Legacy

### Interrupt pins
All input pins can be designated as interrupt pins. But there are some dedicated hardware interrupt pins that could also be used. Not sure if one has an advantage over the other.
able (we measured it). How exactely it is defined remains a mystery.
