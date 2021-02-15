
#include <SimpleRotary.h>

// Pin A, Pin B, Button Pin
SimpleRotary rotary(10, 11, 12);

int ctr = 0;
byte lastDir = 0;

void setup() {
  Serial.begin(9600);
}

void loop(){
  int rDir = rotary.rotate();
  int rBtn = rotary.push();
  int rLBtn = rotary.pushLong(1000);

  // Check direction
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
