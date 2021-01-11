/**
 * DrehDings project: tick-based version. Sequence: Turning stationary object
 * 
 * A turning geometrical object is highlighted by LED flashes at
 * regular intervals, producing an optical illusion of stationary
 * versions of the object.
 * 
 * This version flashed the LEDs based on ticks per round measured
 * by a hallsensor (tacho) as the motor turns the object.
 */

// pin setup (all digital)
#define PIN_MOTOR 3  // motor speed control
#define PIN_HALL 14  // do not use the pin with the board LED attached (usually 13)
#define PIN_LED1 4
#define PIN_LED2 5
#define PIN_LED3 6

// base configuration
#define HALL_PULSE_PER_TURN 18  // how often the hall-sensor sends a pulse per turn; a hardware constant; see hall-sensor specification or tests/hallsensorpulses
#define LED_INTERVAL_ON 300    // time the LEDs should stay on in microseconds; choose lowest value that still produces sufficient illumination; see tests/determineledminblinktime
#define MOTOR_PWM_HZ 100       // frequency of the PWM signal driving the motor; a hardware constant; see motor specification

// flash configuration
// _pos : when the motor is in this position (one of [0, HALL_PULSE_PER_TURN)), the LED flashes
// _cooldown : wait this many motor rotations after each flash before flashing again; default is 0
static uint8_t led_1_pos = 0;
static const uint8_t led_1_cooldown = 0;
static const uint8_t led_2_pos = 0;
static const uint8_t led_2_cooldown = 255;
static const uint8_t led_3_pos = 0;
static const uint8_t led_3_cooldown = 255;

static long led_1_move_last = 0;
static long led_1_move_interval = 1000000;
static const long led_1_move_interval_change = 10000;

// motor configuration
static const uint8_t motor_pulse_length = 40;  // which fraction of the motor's PWM signal to send HIGH; [0,255]; determines motor turning speed


// variables (do not change)
unsigned long led_1_switched_on = 0;  // time when last switched on
unsigned long led_2_switched_on = 0;
unsigned long led_3_switched_on = 0;

uint8_t led_1_c = 0; // cooldown counter
uint8_t led_2_c = 0;
uint8_t led_3_c = 0;

volatile uint8_t motor_position = 0;  // interrupt counter; rather used as motor position state aka in which phase of a turn it is; takes values in [0,HALL_PULSE_PER_TURN)
volatile uint8_t motor_position_changed = 0;  // reqired when motor is turned manually to avoid multiple reactions to the same motor position state


/**
 * Function called on interrupt.
 */
void isr() {
  motor_position++;
  motor_position_changed = 1;
}

/**
 * Turns all LEDs off that have been on for LED_INTERVAL_ON microseconds or longer.
 */
void leds_turn_off() {
  const unsigned long current = micros();
  if (current - led_1_switched_on >= LED_INTERVAL_ON) digitalWrite(PIN_LED1, HIGH);
  if (current - led_2_switched_on >= LED_INTERVAL_ON) digitalWrite(PIN_LED2, HIGH);
  if (current - led_3_switched_on >= LED_INTERVAL_ON) digitalWrite(PIN_LED3, HIGH);
}

/**
 * Setup the routine.
 */
void setup() {  
  // setup pins
  pinMode(PIN_MOTOR, OUTPUT);
  pinMode(PIN_HALL, INPUT_PULLUP);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);

  // create PWM singal for motor
  analogWriteFrequency(PIN_MOTOR, MOTOR_PWM_HZ);
  analogWrite(PIN_MOTOR, motor_pulse_length);  // 0-255 aka 0-100% of duty cycle on

  // create interrupt on hall-sensor pin when high pulse is received
  attachInterrupt(digitalPinToInterrupt(PIN_HALL), isr, CHANGE);
  sei();  // start interrupts
}

/**
 * Loop execute indefinitiely.
 */
void loop() {
  leds_turn_off();

  if (motor_position >= HALL_PULSE_PER_TURN) motor_position = 0;  // go repeatedly through motor positions states

  if (micros() - led_1_move_last >= led_1_move_interval) {
    led_1_move_last = micros();
    led_1_pos++;
    if (led_1_pos >= HALL_PULSE_PER_TURN) led_1_pos = 0;
    led_1_move_interval = led_1_move_interval - led_1_move_interval_change;
    if (led_1_move_interval <= led_1_move_interval_change) led_1_move_interval = 1000000;
  }

  if (motor_position_changed > 0) {  // only act if there has been a change since last action
    motor_position_changed = 0;
    
    if ((motor_position == led_1_pos) && (led_1_c >= led_1_cooldown)) {  // if in right position and cooldown passed
      digitalWrite(PIN_LED1, LOW);  // switch LED on
      led_1_c = 0;  // reset cooldown
      led_1_switched_on = micros();  // set timestamp
    } else if (motor_position == led_1_pos) {  // skip one turning of the motor
      led_1_c++;
    }

    if ((motor_position == led_2_pos) && (led_2_c >= led_2_cooldown)) {
      digitalWrite(PIN_LED2, LOW);
      led_2_c = 0;
      led_2_switched_on = micros();
    } else if (motor_position == led_2_pos) {
      led_2_c++;
    }

    if ((motor_position == led_3_pos) && (led_3_c >= led_3_cooldown)) {
      digitalWrite(PIN_LED3, LOW);
      led_3_c = 0;
      led_3_switched_on = micros();
    } else if (motor_position == led_3_pos) {
      led_3_c++;
    }
  }
}
