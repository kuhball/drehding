/*
 * Script to test a rotary encoder.
 * 
 * Uses a library that supports the rotary encoder as
 * well as the integrated button: Both simple and extended clicks.
 * 
 * https://github.com/mprograms/SimpleRotary
 * 
 * Turning will increase resp. decrease the counter. Pressing the button
 * will move the counter +/-100 depending on last turning direction.
 * Pressing the button long will reset the counter to zero.
 * 
 * Written for the AZDelivery KY-040 Rotary Encoder Module for Arduino,
 * but can be adapted to others.
 * 
 * Connect the rotary encoder to power (5V, but 3V works, too) and ground.
 * Connect the SW (button press interrupt), CLK (A-singal) and DT (B-signal)
 * to the Teensy 4.0 at any digital pin (all but PIN 13).
 * 
 * Define the correct pin numbers below.
 * 
 * Additionally, on your PC, open Tools > Serial Monitor to read the logs
 * (this might cause an error, follow the permission setting instructions
 * there). Make sure that the Bauds are set to the same number as in the
 * Serial.begin() method below.
 * 
 * Then compile, upload, and run.
 * 
 * In the serial monitor you should see outputs like:
 * 11:16:53.165 -> Counter = -192
 * 11:16:54.327 -> Counter = -92
 * 11:16:55.322 -> Counter = 8
 * 11:16:57.513 -> Counter = 108
 * 11:16:59.107 -> Counter = 208
 * 11:17:00.733 -> Counter = 308
 */

#include <SimpleRotary.h>

// pin configuration
#define PIN_CLK 10  // A
#define PIN_DT 11  // B
#define PIN_SW 12  // button

// Pin A, Pin B, Button Pin
SimpleRotary rotary(PIN_CLK, PIN_DT, PIN_SW);

int ctr = 0;
byte lastDir = 0;

void setup() {
  Serial.begin(9600);
}

void loop(){
  int rDir = rotary.rotate();
  int rBtn = rotary.push();
  int rLBtn = rotary.pushLong(1000);

  // Check direction (0 means no change)
  if ( rDir == 1  ) {
      // CW
      ctr++;
      lastDir = rDir;
  }
  if ( rDir == 2 ) {
      // CCW
      ctr--;
      lastDir = rDir;
  }

  if ( rBtn == 1 ) {
    switch (lastDir) {
      case 1:
        ctr += 100;
        break;
      case 2:
        ctr -= 100;
        break;
    }
  }

  if ( rLBtn == 1 ) {
    ctr = 0;
  }

  // Only Serial.print when there is user input.
  // Constant serial printing without delay can introduce lag where rotary encoder rotation pulses can be missed.
  if ( rDir == 1 || rDir == 2 || rBtn == 1 || rLBtn == 1 ){
    Serial.print("Counter = ");
    Serial.print(ctr);
    Serial.println();
  }
}
