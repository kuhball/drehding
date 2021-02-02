/*
 * Script to test a rotary encoder.
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
unsigned long lastButtonPress = 0;

void setup() {
  
  // Set encoder pins as inputs
  pinMode(PIN_CLK, INPUT);
  pinMode(PIN_DT, INPUT);
  pinMode(PIN_SW, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(PIN_CLK);
}

void loop() {
  
  // Read the current state of CLK
  currentStateCLK = digitalRead(PIN_CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CW so increment
    if (digitalRead(PIN_DT) != currentStateCLK) {
      counter++;
      currentDir ="CW";
    } else {
      // Encoder is rotating CCW so decrement
      counter--;
      currentDir ="CCW";
    }

    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(PIN_SW);

  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      Serial.println("Button pressed!");
    }

    // Remember last button press event
    lastButtonPress = millis();
  }

  // Put in a slight delay to help debounce the reading
  delay(1);
}
