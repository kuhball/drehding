# Ideas
Random ideas and notes and such. Can be deleted at any time.

- make code in libs/ into proper libs with versioning

- rewrite timers to use Teensy specific timer settings (not micors, rather https://www.pjrc.com/teensy/td\_timing.html, e.g. ellapseMicros)

- check all interrupt routines is follow the programming guides: https://www.pjrc.com/teensy/interrupts.html

- find a better way to inject LED effects (should be add effect and that's it)

- find a better way to determine number of LED's (not in code, should iterate over array somehow; but caused memory glitches in first attempt)

- when +/- stable function, rewrite code to speed up (if required)


- write a sequence flashing processor [done]
	- aka tell each LED at which tick to flash and for how long in millis
	- allows for flexible flash configuration testing
	- e.g.
		- LED1_ticks = [0,8,4,7]
		- LED1_intervals = [500, 100, 200, 500]
	- wraps around after the end

- write a function to detrmine the rounds-per-minute/second/micros [done]
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

- write function that flashes LED at flashes / round [done]
	- we know the rps value
	- means LED should flash X=s/rps times per second
	- implement with micros/millis
	
- add fraction delay form round start [not required, starting point is first hall signal]
	- somehow synchronize starting point of LEDs time in previous function
	- then flash them again X times
	- but shift starting point by a milli/micro value
	- should cause unsynced LEDs
	
- loop() called ca. at 117 kHz aka 117,000 times/second? [can ignore, time based flashing works very well, processor obviously fast enough]
	- Could be more or less, depends on board, code in loop, etc.
	- Not a good value to build anything on. Use rather micro or milliseconds
	
- write time-based version of code [done]
	- measures rotations-per-micros
	- controls LEDs with parameters:
		- flash each fraction (<1) or multiple (>=1) of rotations
	- provides better granularity control
	- might de-sync after some runtime [does not, works perfectly]
		- figure out a way to re-sync with hall signal from time to time

- write an LED class [done]
	should contain LED functionality, counters, steering methods, parameters, etc.

- change to measure also HIGH->LOW with interrupts -> better number (18 instead of 9) for dividing [done]

- lookup stobe-gifs and get inspired [done]
