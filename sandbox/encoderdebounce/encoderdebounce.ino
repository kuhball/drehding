#define PIN_CLK 10
#define PIN_DT 11

unsigned int thr = 100;

volatile unsigned long lastA;
volatile unsigned long lastB;

void setup() {
  pinMode(PIN_CLK, INPUT_PULLUP);
  pinMode(PIN_DT, INPUT_PULLUP);

  Serial.begin(9600);
  
  lastA = millis();
  lastB = millis();

  attachInterrupt(digitalPinToInterrupt(PIN_CLK), interruptA, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_DT), interruptB, RISING);
}

void loop() {

}

void interruptA() {
  if (millis() - lastA > thr) {  // debounce to fast changes
    if (digitalRead(PIN_CLK) == HIGH) {
      if (digitalRead(PIN_DT) == LOW) {
        Serial.println("CW");
      }
      lastA = millis();
    }
  }
}

void interruptB() {
  if (millis() - lastB > thr) {  // debounce to fast changes
    if (digitalRead(PIN_DT) == HIGH) {
      if (digitalRead(PIN_CLK) == LOW) {
        Serial.println("CCW");
      }
      lastB = millis();
    }
  }
}


/*
# CW

is: both open, both high
next: both closed, both low
order: A changed first

is: both closed, both low
next: both open, both high
oder: A changed first

# CCW
is: both open, both high
next: both closed, both low
order: B changed first

is: both closed, both low
next: both open, both high
order: B changed first

# ALG I
trigger: rising on A

## CW
is: close
next: open
A=HIGH & B=LOW

## CCW
is: close
next: open
A=HIGH & B=HIGH

process only one A rising every X ms
*/
