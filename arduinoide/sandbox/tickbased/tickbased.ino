#define motor 3
#define tacho 14
#define led1 4
#define led2 5
#define led3 6
#define TACHO_SIGNALS_TURN 9  // how often the hallsensor sends a pulse per turn
#define LED_ON_INTERVAL 300  // time the LEDs sjhould stay on in microseconds

// at this position (of TACHO_SIGNALS_TURN singals per round) the LED flashes each turn; zero-based
// wait cooldown turns after each flash before flashing again
static const uint8_t led_1_pos = 0;
static const uint8_t led_1_cooldown = 0;
static const uint8_t led_2_pos = 0;
static const uint8_t led_2_cooldown = 10;
static const uint8_t led_3_pos = 0;
static const uint8_t led_3_cooldown = 40;

unsigned long led_1_switched_on = 0;
unsigned long led_2_switched_on = 0;
unsigned long led_3_switched_on = 0;

uint8_t led_1_c = 0;
uint8_t led_2_c = 0;
uint8_t led_3_c = 0;

volatile uint8_t ic = 0;  // interrupt counter (rather used as motor state aka in which phase of a turn it is)
volatile uint8_t ic_changed = 0;  // reqired when motor is turned manually to avoid multiple reactions to the same interrupt state

void isrService() {
  ic++;
  ic_changed = 1;
}

void turnLedsOff() {
  //Serial.println("turnLedsOff()::called");
  const unsigned long current = micros();

  if (current - led_1_switched_on >= LED_ON_INTERVAL) digitalWrite(led1, HIGH);
  if (current - led_2_switched_on >= LED_ON_INTERVAL) digitalWrite(led2, HIGH);
  if (current - led_3_switched_on >= LED_ON_INTERVAL) digitalWrite(led3, HIGH);
}

void setup() {  
//  Serial.begin(57600);
  // define ports
  pinMode(motor, OUTPUT); // motor pwm
  pinMode(tacho, INPUT_PULLUP); // tacho read
  pinMode(led1, OUTPUT); //led 1
  pinMode(led2, OUTPUT); //led 2
  pinMode(led3, OUTPUT); //led 3

  // start serial port for logging
  Serial.begin(9600);

  // create  pwm for motor
  analogWriteFrequency(motor, 24);
  analogWrite(motor, 40);  // 0-255 aka 0-100% of duty cycle on

  // create interrupt on tacho pin when high pulse is received
  attachInterrupt(digitalPinToInterrupt(tacho), isrService, RISING);
  sei();

}

void loop() {
  turnLedsOff();

  if (ic >= TACHO_SIGNALS_TURN) ic = 0;

  if (ic_changed > 0) {
    ic_changed = 0;
    
    if ((ic == led_1_pos) && (led_1_c >= led_1_cooldown)) {
      digitalWrite(led1, LOW);
      led_1_c = 0;
      led_1_switched_on = micros();
    } else if (ic == led_1_pos) {
      led_1_c++;
    }

    if ((ic == led_2_pos) && (led_2_c >= led_2_cooldown)) {
      digitalWrite(led2, LOW);
      led_2_c = 0;
      led_2_switched_on = micros();
    } else if (ic == led_2_pos) {
      led_2_c++;
    }

    if ((ic == led_3_pos) && (led_3_c >= led_3_cooldown)) {
      digitalWrite(led3, LOW);
      led_3_c = 0;
      led_3_switched_on = micros();
    } else if (ic == led_3_pos) {
      led_3_c++;
    }
  }
}
