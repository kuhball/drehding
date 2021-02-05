# Flash effects
A collection of different flash effects that could be programmed.

- describe different configurations for the flashes here and what effects they cause
- depends on objects used
- see also [stroboscopic effect](https://en.wikipedia.org/wiki/Stroboscopic_effect)

- single LED flash = stationary object
- multiple LED flash = multiple interleaved stationary objects
	- not very distinguishable, maybe requires different LED colours or bigger object
- single LED flash, then slowly changing flashpoint = stationary object that slowly moves
- two LEDs flash, then slowly changing flashpoints, both in opposite directions = two stationary objects rotating against each other
	- looks very nice with time-based flashing
- one LED at it's flashpoint on; after some time, switch off and second on, then off and third on, usw.
	- first long on-times for each LED; then shorter, then longer again
	- = multiple objects switching in and out, sometimes faster, sometimes slower
- put an object on one side of the octahedron
	- = can we make that appear and disappear by using a single LED and switching flashpoints?
		- yes, looks very nice
	- works well with face put one two side (one smiling, one frowning)
- face on one side
	- make it move by one LED, stationary with another
	- make object side without face stationary, then shortly blink over to face (shock), then off again
		- maybe at random intervals, so observers have to wait
- other objects on one or more sides
	- can cause interleaving and spiralling effects
- mount other objects on the motor
	- I would fancy a spiral
	- Try first with Küchenmaschiene
		- Looks nice with Kuechenmachine
		- Keep object motor running two: PWM can be used to change flashing speed until matches Kuechenmachine
- softstart motor (start slow, then to target speed)
- faces on two sides
	- one smiling, one sad
	- two leds, both faces smiling
	- from time to time, one flips to sad state
	- look nice!
- now that lamps are restricted in where they can shine: Place one to highlight the upper, another to highlight the lower part of the object. Idea by Christ (works, try some more Oskar)
	- looks nice with both sides moving in opposite directions