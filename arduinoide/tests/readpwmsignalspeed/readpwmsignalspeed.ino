/*
 * Read a PWM signal from a PIN and, every second, print the interrupts per minute.
 * 
 * Put the PWM line to the designated pin, then start the signal. On your PC, 
 * open Tools > Serial Plotter to read the logs (this might cause an error,
 * follow the permission setting instructions there). Make sure that the 
 * Bauds are set to the same number as in the Serial.begin() method below.
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

// global variables
volatile unsigned int  itrc;  // interrupt counter
unsigned int intrpm;  // computed interrupts per minute

// function called by interrupt
void inc_itrc () {
  itrc++;
}
 
void setup() {
  pinMode(PIN_PWM, INPUT_PULLUP);
  Serial.begin(9600);  // open serial monitor in arduino IDE to read (set to same baud rate)
  attachInterrupt(digitalPinToInterrupt(PIN_PWM), inc_itrc, RISING);  // every time signal switches from LOW to HIGH, the rpm() function is called
}
 
void loop () {
  itrc = 0;
  
  sei();  // enable interrupts
  delay(1000);  // wait one second, does not block interrupts
  cli();  // disable interrupts

  intrpm = itrc * 60;  // compute interrupts per minute (counted per second)

  Serial.println(intrpm);  // print as decimal number
} 
