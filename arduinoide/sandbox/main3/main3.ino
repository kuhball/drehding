#define motor 3
#define tacho 14
#define led1 4
#define led2 5
#define led3 6
#define TACHO_SIGNALS_TURN 9

// at this position (of TACHO_SIGNALS_TURN singals per round) the LED flashes each turn; zero-based
static uint8_t led_1_pos = 0;
static uint8_t led_1_cooldown = 0;
static uint8_t led_2_pos = 4;
static uint8_t led_2_cooldown = 0;
static uint8_t led_3_pos = 4;
static uint8_t led_3_cooldown = 255;

uint8_t led_1_c = 0;
uint8_t led_2_c = 0;
uint8_t led_3_c = 0;

uint8_t ic = 0;  // interrupt counter
uint8_t ic_changed = 0;

elapsedMicros usTimer;
long int last = 0;

void isrService() {
  ic++;
  ic_changed = 1;
}

void turnLedsOff() {
  //Serial.println("turnLedsOff()::called");
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
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
  analogWrite(motor, 64);  // 0-255 aka 0-100% of duty cycle on

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
      delay(1);
    } else if (ic == led_1_pos) {
      led_1_c++;
    }

    if ((ic == led_2_pos) && (led_2_c >= led_2_cooldown)) {
      digitalWrite(led2, LOW);
      led_2_c = 0;
      delay(1);
    } else if (ic == led_2_pos) {
      led_2_c++;
    }

    if ((ic == led_3_pos) && (led_3_c >= led_3_cooldown)) {
      digitalWrite(led3, LOW);
      led_3_c = 0;
      delay(1);
    } else if (ic == led_3_pos) {
      led_3_c++;
    }
  }
  
  //if (ic == led_2_pos) digitalWrite(led2, LOW);
  //if (ic == led_3_pos) digitalWrite(led3, LOW);
  
  
  //Serial.println(current);
  //if (current >= 100){
  //  Serial.println("is::current>=100");
  //  turnLedsOff();
}


// idea: try to count rounds/sec of motor
// then flash the LEDs accordingly aka according to a flash/sec value
