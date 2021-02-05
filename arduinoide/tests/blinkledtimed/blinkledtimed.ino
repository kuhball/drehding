/*
  Turns on an LED on for one second, then off for one second, repeatedly.
  Alternative version which does not use the blocking delay(),
  but rather a timer.

  Note that this requires the external power supply to be on.
  Note that some LEDs are turn on with HIGH, others with LOW.
  Can be on together with the power supplied by the USB cable.
 */

// pin configuration
#define PIN_LED 4  // PIN number of LED

// settings
const unsigned long INTERVAL = 1000;  // in millis (1000 milliseconds = 1 second)

// global variables
uint8_t led_state = HIGH;
unsigned long led_last_change = 0;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(PIN_LED, OUTPUT);  // initialize the digital pin as an output.
}

// the loop routine runs over and over again forever:
void loop() {
	unsigned long current = millis();
	
	if (current - led_last_change >= INTERVAL) {
		led_last_change = current;
		
		if (led_state == LOW) led_state = HIGH;
		else led_state = LOW;
		
		digitalWrite(PIN_LED, led_state);
	}              
}
