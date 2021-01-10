/*
  Sets PIN 13 (attached to internal LED) to input mode for PWM signal receival.

  One pin on the board (usually 13) is directly wired to the on-board LED
  and a resistor. Upon receiving a signal, the LED flashes hardware driven.
  This is a good indicator whether a signal arrives at al.
 */

// pin configuration
#define PIN_PWM 13  // PIN connected to on-board LED (usually 13)

void setup() {
  pinMode(PIN_PWM, INPUT);
}

void loop() {
  delay(1000);
}
