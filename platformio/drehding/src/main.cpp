/**
 * DrehDings project.
 * 
 * A turning geometrical object is highlighted by LED flashes at
 * regular intervals, producing an optical illusion of stationary
 * versions of the object.
 * 
 * This version flashed the LEDs based on object rotation speed
 * derived from the ticks per round measured by a
 * hallsensor (tacho) as the motor turns the object.
 */
#include "Arduino.h"
#include "SimpleRotary.h"

#include "Motor.h"
#include "HallTimed.h"
#include "Led.h"
//#include "EffectRotation.h"
//#include "EffectSequence.h"


/*** START: CONFIGURATION **/

// pin setup
// for all: do not use the pin with the board LED attached (usually 13)
// for all: use only digital PINs
// @see https://www.pjrc.com/store/teensy40.html for PIN diagram
#define PIN_MOTOR 15  // motor speed control, use pin that is PWM enabled
#define PIN_HALL 14  // motor's hallsensor's signal, usually termed FG
#define PIN_LED1 1
#define PIN_LED2 2
#define PIN_LED3 3
#define PIN_ENCODER_CLK 10  // rotary encoder's CLK signal, also called A signal
#define PIN_ENCODER_DT 11  // rotary encoder's DT signal, also called B signal
#define PIN_ENCODER_SW 12  // either signal of rotary encoder's integrated push-button or any other push-button

// base configuration
#define HALL_TICKS_PER_TURN 18  // how often the hall-sensor sends a pulse per turn; a hardware constant; see hall-sensor specification or tests/hallsensorpulses
#define MOTOR_PWM_HZ 100  // frequency of the PWM signal driving the motor; a hardware constant; see motor specification
#define GEAR_RATIO 1.0  // if gearing employed, set this to the ratio; >1.0 means object turns faster than motor, <1.0 means object turns slower than motor

// effect configurations
// LED1 (CW) and LED2 (CCW) rotation configuration
static const uint32_t change_millis = 100;  // after how many millis to change
static const uint16_t speed_degree = 1;  // how many degrees to change

/*** END: CONFIGURATION **/

// init led objects
Led led1(PIN_LED1, true);
Led led2(PIN_LED2, true);
Led led3(PIN_LED3, true);

// init controll objects
HallTimed hall(PIN_HALL, HALL_TICKS_PER_TURN);
Motor motor(PIN_MOTOR, MOTOR_PWM_HZ);
SimpleRotary rotary(PIN_ENCODER_CLK, PIN_ENCODER_DT, PIN_ENCODER_SW);

//EffectRotation ef1(leds[0], 25);
//uint16_t a[] = {0, 45};
//uint32_t b[] = {100, 100};
//EffectSequence ef1(leds[0], (uint16_t []) {0, 45}, (uint32_t []) {100, 100}, 2);
//EffectRotation ef2(leds[0], 25);

// rotation variables
//uint32_t last_change = 0;
//uint16_t current_degree = 0;
//elapsedMillis ellapsed;u

/**
 * Function called on interrupt.
 */
void isr() {
  hall.handle_interrupt();
}

/**
 * Setup the routine.
 */
void setup() {
  // start motor initially
  motor.start();

  // LED sequence control
  led1.flash_at_part = 0;
  led2.flash_at_part = 45;
  led3.flash_at_part = 60;

  //last_change = millis();

  hall.set_interrupt_handler(isr);
  sei();  // start interrupts
}

/**
 * Loop execute indefinitiely.
 */
void loop() {
  // led turn off
  led1.turn_off_cond();
  led2.turn_off_cond();
  led3.turn_off_cond();

  /*
  if (millis() - last_change > 200) {
    if(leds[0].flash_at_part == 0) {
      leds[0].flash_at_part = 45;
    } else {
      leds[0].flash_at_part = 0;
    }
    last_change = millis();
  }
  */
  
  // adapt motor speed if changed
  const byte direction = rotary.rotate();
  if ( direction == 1  ) motor.inc_speed();
  else if ( direction == 2 ) motor.dec_speed();

  // for each LED check if action required at current position
  const uint16_t degree = (uint16_t)((float)hall.get_degree() * GEAR_RATIO) % 360;  // motor degree to object degree, wrap around to ensure valid angle
  cli();
  const uint16_t tick_no = hall.tick_no;
  sei();
  led1.turn_on_cond(tick_no, degree);
  led2.turn_on_cond(tick_no, degree);
  led3.turn_on_cond(tick_no, degree);
  
  //ef2.update();
  //ef1.update();
  
}
