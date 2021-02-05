/*
  Turns on an LED on for one second, then off for one second, repeatedly.

  Note that this requires the external power supply to be on.
  Note that some LEDs are turn on with HIGH, others with LOW.
  Can be on together with the power supplied by the USB cable.
 */

// pin configuration
#define PIN_LED 4  // PIN number of LED

// the setup routine runs once when you press reset:
void setup() {
  pinMode(PIN_LED, OUTPUT);  // initialize the digital pin as an output.
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(PIN_LED, LOW);   // turn the LED on
  delay(1000);                  // wait for a second (1000 milliseconds)
  digitalWrite(PIN_LED, HIGH);  // turn the LED off
  delay(1000);               
}
