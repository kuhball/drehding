/*
  Check whether an input pin receives a PWM signal.

  Alternative, non-blocking method using interrupts. As opposed to
  pulseIn(), here we perform the timing on our own.

  Put the PWM line to the designated pin, then start the signal. On your PC, 
  open Tools > Serial Plotter to read the logs (this might cause an error,
  follow the permission setting instructions there). Make sure that the 
  Bauds are set to the same number as in the Serial.begin() method below.

  You should see a constant stream of numbers, which denote the length of the
  received PWM pulses in microseconds (duration from HIGH to LOW).

  Note that an input pin for a PWM signal should have a pull-up resistor.
  This can be either realized in hardware, or, like here, by setting the
  pinMode to INPUT_PULLUP. THis inverts the HIGH/LOW signals.
  If this is not set, random fluctuations will influence the signal, especially
  if there is not PWM signal for some time.

  Do not use the pin with the hardwired LED on the board for INPUT_PULLUP
  (usually pin 13).

  Source: https://www.benripley.com/diy/arduino/three-ways-to-read-a-pwm-signal-with-arduino/
 */

// pin configuration
#define PIN_PWM 14  // PIN where the PWM singal arrives

// global variables
volatile unsigned int pwm_value = 0;  // use volatile keyword vor variables that can be changed by interrupt signals
volatile unsigned int prev_time = 0;  // see https://barrgroup.com/embedded-systems/how-to/c-volatile-keyword
 
void rising() {
  attachInterrupt(digitalPinToInterrupt(PIN_PWM), &falling, FALLING);  // when PIN_PWM goes LOW, call falling()
  prev_time = micros();
}
 
void falling() {
  attachInterrupt(digitalPinToInterrupt(PIN_PWM), &rising, RISING);  // when PIN_PWM goes HIGH, call rising()
  pwm_value = micros() - prev_time;
  Serial.println(pwm_value);
}
 
void setup() {
  pinMode(PIN_PWM, INPUT_PULLUP);

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(PIN_PWM), &rising, RISING);  // when PIN_PWM goes HIGH, call rising()
  sei();  // enable interrupts
}
 
void loop() { }
