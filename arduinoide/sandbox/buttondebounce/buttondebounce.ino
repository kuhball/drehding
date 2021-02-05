#define PIN_BUTTON 12

boolean buttonState = LOW;

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  if(debounceButton(buttonState) == HIGH && buttonState == LOW) {
    buttonState = HIGH;
    Serial.println("Pressed");
  }
  else if(debounceButton(buttonState) == LOW && buttonState == HIGH) {
    buttonState = LOW;
  }
}

boolean debounceButton(boolean state) {
  boolean stateNow = digitalRead(PIN_BUTTON);
  if(state != stateNow) {
    delay(10);
    stateNow = digitalRead(PIN_BUTTON);
  }
  return stateNow;
}
