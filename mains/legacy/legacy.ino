#define motor 3
#define tacho 13
#define led1 4
#define led2 5
#define led3 6

// divider is used for waiting x interrupts from the tacho signal
static uint8_t led_1_divider = 2;
// counter to count the waiting interrupts
static uint8_t led_1_counter = 0;

static uint8_t led_2_divider = 4;
static uint8_t led_2_counter = 0;

static uint8_t led_3_divider = 8;
static uint8_t led_3_counter = 0;

// handeling the routine outside of the isr
uint8_t flash = 0;

elapsedMicros current;

void isrService() {
  //Serial.println("isrService()::called");
  flash=1;
}

void turnLedsOn(){
  Serial.println("turnLedsOn()::called");
  if (led_1_counter < led_1_divider){
    led_1_counter++;
    if (led_1_counter == 1){
      digitalWrite(led1, LOW);
    }
  }
  if (led_2_counter < led_2_divider){
    led_2_counter++;
    if (led_2_counter == 1){
      digitalWrite(led2, LOW);
    }
  }
  if (led_3_counter < led_3_divider){
    led_3_counter++;
    if (led_3_counter == 1){
      digitalWrite(led3, LOW);
    }
  }
}

void turnLedsOff() {
  Serial.println("turnLedsOff()::called");
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
}

void setup() {  
//  Serial.begin(57600);
  // define ports
  pinMode(motor,OUTPUT); // motor pwm
  pinMode(tacho,INPUT); // tacho read
  pinMode(led1, OUTPUT); //led 1
  pinMode(led2, OUTPUT); //led 2
  pinMode(led3, OUTPUT); //led 3

  // start serial port for logging
  Serial.begin(9600);

  // create  pwm for motor
  analogWriteFrequency(motor, 24);
  analogWrite(motor, 64);  // 0-255 aka 0-100% of duty cycle on

  // create interrupt on tacho pin when high pulse is received
  attachInterrupt(digitalPinToInterrupt(tacho), isrService, HIGH);
  sei();

}

void loop() {
  if (flash == 1){
    Serial.println("is::flash==1");
    current = 0;
    turnLedsOn();
    flash = 0;
  }
  Serial.println(current);
  if (current >= 100){
    Serial.println("is::current>=100");
    turnLedsOff();
  }
  if (led_1_counter == led_1_divider){
      led_1_counter = 0;
  }
  if (led_2_counter == led_2_divider){
      led_2_counter = 0;
  }
  if (led_3_counter == led_3_divider){
      led_3_counter = 0;
  }
}
