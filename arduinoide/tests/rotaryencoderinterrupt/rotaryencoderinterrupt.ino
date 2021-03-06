/*
 * Script to test a rotary encoder.
 * 
 * Same as rotaryencoder script, but utilizing interrupts.
 * 
 * Written for the AZDelivery KY-040 Rotary Encoder Module for Arduino,
 * but can be adapted to others.
 * 
 * Connect the rotary encoder to power (5V, but 3V works, too) and ground.
 * Connect the SW (button press interrupt), CLK (A-singal) and DT (B-signal)
 * to the Teensy 4.0 at any digital pin.
 * 
 * Define the correct pin numbers below.
 * 
 * Additionally, on your PC, open Tools > Serial Monitor to read the logs
 * (this might cause an error, follow the permission setting instructions
 * there). Make sure that the Bauds are set to the same number as in the
 * Serial.begin() method below. The script will write out the motor speed
 * at every completed turn.
 * 
 * Then compile, upload, and run.
 * 
 * In the serial monitor you should see outputs like:
 * 19:04:26.018 -> Direction: CW | Counter: -11
 * 19:04:26.118 -> Direction: CCW | Counter: -12
 * 19:04:26.184 -> Direction: CW | Counter: -11
 * 19:04:28.740 -> Button pressed!
 */

// pin configuration
#define PIN_CLK 10
#define PIN_DT 11
#define PIN_SW 12

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";

void setup() {
  
  // Set encoder pins as inputs
  pinMode(PIN_CLK, INPUT_PULLUP);
  pinMode(PIN_DT, INPUT_PULLUP);
  pinMode(PIN_SW, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(PIN_CLK);
  
  // Call associated interrupts when change occures
  attachInterrupt(digitalPinToInterrupt(PIN_CLK), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_DT), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_SW), updateButton, FALLING);
}

void loop() {
  //Do some useful stuff here
}

void updateEncoder() {
  // Read the current state of CLK
  currentStateCLK = digitalRead(PIN_CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(PIN_DT) != currentStateCLK) {
      counter --;
      currentDir ="CCW";
    } else {
      // Encoder is rotating CW so increment
      counter ++;
      currentDir ="CW";
    }

    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}

void updateButton() {
  Serial.println("Button pressed!");
}
