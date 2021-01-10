/*
 * Simple script to manually determine the pulses-per-round of a hallsensor
 * attached to a motor.
 * 
 * Basically a script that listens to a PWM input signal and flashes an LED
 * every X pulses received.
 * 
 * Put the hallsensors PWM output (tacho) line to the designated pin, attach
 * an LED to the led pin, and put no power to the motor driver (aka the motor
 * should stay still).
 * In this script, configure the pulses-per-round you suspect the hallsensor
 * to send. Then upload the script.
 * To test your hypothesis, turn the motor by hand until the LED flashes once
 * (starting position). Then carefully turn the motor, ideally without stopping,
 * one whole round. The LED will flash again when the suspected pulses-per-round
 * have been reached. If this coincides with one turn of the motor, your hypothesis
 * has been confirmed.
 * 
 * Note that you will most probably have to repeat the process multiple times
 * and with multiple values to get to the real pulses-per-round value of your
 * hallsensor.
 * 
 * Additionally, on your PC, open Tools > Serial Plotter to read the logs
 * (this might cause an error, follow the permission setting instructions
 * there). Make sure that the Bauds are set to the same number as in the
 * Serial.begin() method below. The script will write a log entry every
 * time it receives an interrupt from the PWM input.
 * 
 * Note that an input pin for a PWM signal should have a pull-up resistor.
 * This can be either realized in hardware, or, like here, by setting the
 * pinMode to INPUT_PULLUP. THis inverts the HIGH/LOW signals.
 * If this is not set, random fluctuations will influence the signal, especially
 * if there is not PWM signal for some time.
 * 
 * Do not use the pin with the hardwired LED on the board for INPUT_PULLUP
 * (usually pin 13).
 * 
 * Inspired by: www.theorycircuit.com and http://thebestcasescenario.com
 */

// pin configuration
#define PIN_PWM 14  // PIN where the PWM singal arrives
#define PIN_LED 4  // PIN of the LED

// configuration
const unsigned int pulses_per_round = 9;  // set this to the hallsensor value you suspect

// global variables
volatile unsigned int itrc = 0;  // interrupt counter

// function called by interrupt
void inc_itrc () {
  Serial.println("Interrupt received");
  itrc++;
}
 
void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_PWM, INPUT_PULLUP);
  
  Serial.begin(9600);  // open serial monitor in arduino IDE to read (set to same baud rate)
  
  attachInterrupt(digitalPinToInterrupt(PIN_PWM), inc_itrc, RISING);  // every time signal switches from LOW to HIGH, the rpm() function is called
  sei(); // enable interrupts
}
 
void loop () {
  if (itrc >= pulses_per_round) {
    digitalWrite(PIN_LED, LOW);
    delay(1);
    digitalWrite(PIN_LED, HIGH);
    
    itrc = 0;
  }
}
