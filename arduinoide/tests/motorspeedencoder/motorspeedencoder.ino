/*
 * Script to test a rotary encoder to control the motor speed.
 * 
 * Turning will increase resp. decrease the motor speed.
 * 
 * Written for the AZDelivery KY-040 Rotary Encoder Module for Arduino,
 * but can be adapted to others.
 * 
 * Connect the rotary encoder to power (5V, but 3V works, too) and ground.
 * Connect the SW (button press interrupt), CLK (A-singal) and DT (B-signal)
 * to the Teensy 4.0 at any digital pin (all but PIN 13).
 * 
 * Connect the motor PWM controll signal to it's own PIN.
 * 
 * Define the correct pin numbers below.
 * 
 * Then compile, upload, and run. Turn the rotary encoder to contoll
 * the motor speed.
 */

#include <SimpleRotary.h>
#include "Motor.h"

// pin configuration
#define PIN_CLK 10  // A
#define PIN_DT 11  // B
#define PIN_SW 12  // button (unused)
#define PIN_MOTOR 15  // motor speed control, use pin that is PWM enabled
#define MOTOR_PWM_HZ 100  // frequency of the PWM signal driving the motor; a hardware constant; see motor specification

// init objects
Motor motor(PIN_MOTOR, MOTOR_PWM_HZ);
SimpleRotary rotary(PIN_CLK, PIN_DT, PIN_SW);

int ctr = 0;
byte lastDir = 0;

void setup() {
  Serial.begin(9600);
}

void loop(){
  int rDir = rotary.rotate();

  // Check direction (0 means no change)
  if ( rDir == 1  ) {
      // CW
      ctr++;
      lastDir = rDir;
      motor.inc_speed();
  }
  if ( rDir == 2 ) {
      // CCW
      ctr--;
      lastDir = rDir;
      motor.dec_speed();
  }


  // Only Serial.print when there is user input.
  // Constant serial printing without delay can introduce lag where rotary encoder rotation pulses can be missed.
  if ( rDir == 1 || rDir == 2 ){
    Serial.print("Counter = ");
    Serial.print(ctr);
    Serial.println();
  }
}
