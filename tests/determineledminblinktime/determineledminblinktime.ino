/*
  Turns on an LED for a very short amount of time, then switches it off
  for a longer period, and so on.

  Uses a version that is non-blocking.

  Use this to determine the speed you can turn your LED on and then off
  again while still producing a perceptible flash. Simply slowly lower
  the INTERVAL_ON number until the last version you can still perceive
  a flash. Start with a high number, e.g., 100,000.
  
  Note that some LEDs are turn on with HIGH, others with LOW.
 */

// pin configuration
#define PIN_LED 4  // PIN number of LED

// settings
const unsigned long INTERVAL_ON = 100;  // in micros
const unsigned long INTERVAL_OFF = 1000000;  // in micros (leave at 1,000,000 for best effect)

// global variables
uint8_t led_state = HIGH;
unsigned long led_last_change = 0;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(PIN_LED, OUTPUT);  // initialize the digital pin as an output.
}

// the loop routine runs over and over again forever:
void loop() {
	unsigned long current = micros();

  if (led_state == HIGH) {  // aka LED off
    if (current - led_last_change >= INTERVAL_OFF) {  // off interval has passed
      led_state = LOW;  // switch on
      digitalWrite(PIN_LED, led_state);
      led_last_change = current;
    }
  } else {  // aka LED on
    if (current - led_last_change >= INTERVAL_ON) {  // on interval has passed
      led_state = HIGH;  // switch off
      digitalWrite(PIN_LED, led_state);
      led_last_change = current;
    }
  }
}
