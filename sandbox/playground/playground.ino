/*
  Random code. Just a place to try out things.
 */

// PIN number of LED
int led = 4;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  //delay(1);               // wait for a second
  digitalWrite(led, HIGH);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}
