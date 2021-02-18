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
#include "EffectOff.h"
#include "EffectStationary.h"
#include "EffectSequence.h"
#include "EffectRotation.h"


/*** START: CONFIGURATION **/

// pin setup
// for all: do not use the pin with the board LED attached (usually 13)
// for all: use only digital PINs
// @see https://www.pjrc.com/store/teensy40.html for PIN diagram
#define PIN_MOTOR 11  // motor speed control, use pin that is PWM enabled
#define PIN_HALL 8  // motor's hallsensor's signal, usually termed FG
#define PIN_LED1 17
#define PIN_LED2 18
#define PIN_LED3 19
#define PIN_ENCODER_CLK 4  // rotary encoder's CLK signal, also called A signal
#define PIN_ENCODER_DT 5  // rotary encoder's DT signal, also called B signal
#define PIN_ENCODER_SW 1  // either signal of rotary encoder's integrated push-button or any other push-button

// base configuration
#define HALL_TICKS_PER_TURN 18  // how often the hall-sensor sends a pulse per turn; a hardware constant; see hall-sensor specification or tests/hallsensorpulses
#define HALL_ROT_ANGLE_RES 360 // resolution of the rotation angle (e.g. 360 for degree); higher value lead to more smooth transition; too high value can lead to flashes being missed; must be valid unit16_t number
#define MOTOR_PWM_HZ 200  // frequency of the PWM signal driving the motor; a hardware constant; see motor specification
#define GEAR_RATIO 1.0  // if gearing employed, set this to the ratio; >1.0 means object turns faster than motor, <1.0 means object turns slower than motor


// effect configuration
#define N_EFFECTS 17  // number of effects for each LED; all LEDs must ahve the same number of effects

// init led objects (do not change)
Led led1(PIN_LED1, true);
Led led2(PIN_LED2, true);
Led led3(PIN_LED3, true);

// effect definitions (LED1-LED3)
// NOTE: the valid values for the flash positions depend on HALL_ROT_ANGLE_RES aka 0<=position<HALL_ROT_ANGLE_RES
EffectStationary led1_effect1 = EffectStationary(led1, 0);
EffectStationary led1_effect2 = led1_effect1;
EffectStationary led1_effect3 = led1_effect1;
EffectStationary led1_effect4 = led1_effect1;
EffectSequence led1_effect5 = EffectSequence(led1, (uint16_t []) {0, 180}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led1_effect6 = EffectSequence(led1, (uint16_t []) {0, 90}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led1_effect7 = EffectSequence(led1, (uint16_t []) {0, 45}, (uint32_t []) {1000, 1000}, 2);
EffectRotation led1_effect8 = EffectRotation(led1, 100, HALL_ROT_ANGLE_RES);
EffectRotation led1_effect9 = led1_effect8;
EffectRotation led1_effect10 = led1_effect8;
EffectRotation led1_effect11 = led1_effect8;
EffectRotation led1_effect12 = led1_effect8;
EffectRotation led1_effect13 = led1_effect8;
EffectRotation led1_effect14 = led1_effect8;
EffectStationary led1_effect15 = led1_effect1;
EffectSequence led1_effect16 = EffectSequence(led1, (uint16_t []) {0, 10}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led1_effect17 = EffectSequence(led1, (uint16_t []) {0, 10, 20, 30, 40, 50, 60, 70, 80}, (uint32_t []) {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000}, 9);

EffectStationary led2_effect1 = EffectStationary(led2, 0);
EffectStationary led2_effect2 = led2_effect1;
EffectStationary led2_effect3 = EffectStationary(led2, 30);
EffectOff led2_effect4 = EffectOff(led2);
EffectOff led2_effect5 = led2_effect4;
EffectOff led2_effect6 = led2_effect4;
EffectOff led2_effect7 = led2_effect4;
EffectOff led2_effect8 = led2_effect4;
EffectStationary led2_effect9 = led2_effect1;
EffectSequence led2_effect10 = EffectSequence(led2, (uint16_t []) {0, 180}, (uint32_t []) {1000, 1000}, 2);
EffectRotation led2_effect11 = EffectRotation(led2, 100, HALL_ROT_ANGLE_RES, true);
EffectRotation led2_effect12 = led2_effect11;
EffectRotation led2_effect13 = led2_effect11;
EffectRotation led2_effect14 = led2_effect11;
EffectStationary led2_effect15 = led2_effect3;
EffectSequence led2_effect16 = EffectSequence(led2, (uint16_t []) {30, 40}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led2_effect17 = EffectSequence(led2, (uint16_t []) {30, 40, 50, 60, 70, 80, 90, 100, 110}, (uint32_t []) {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000}, 9);

EffectStationary led3_effect1 = EffectStationary(led3, 0);
EffectStationary led3_effect2 = EffectStationary(led3, 45);
EffectStationary led3_effect3 = EffectStationary(led3, 60);
EffectOff led3_effect4 = EffectOff(led3);
EffectOff led3_effect5 = led3_effect4;
EffectOff led3_effect6 = led3_effect4;
EffectOff led3_effect7 = led3_effect4;
EffectOff led3_effect8 = led3_effect4;
EffectOff led3_effect9 = led3_effect4;
EffectOff led3_effect10 = led3_effect4;
EffectOff led3_effect11 = led3_effect4;
EffectStationary led3_effect12 = led3_effect1;
EffectSequence led3_effect13 = EffectSequence(led3, (uint16_t []) {0, 180}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led3_effect14 = EffectSequence(led3, (uint16_t []) {0, 45}, (uint32_t []) {1000, 1000}, 2);
EffectStationary led3_effect15 = led3_effect3;
EffectSequence led3_effect16 = EffectSequence(led3, (uint16_t []) {60, 70}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led3_effect17 = EffectSequence(led3, (uint16_t []) {60, 70, 80, 90, 100, 110, 120, 130, 140}, (uint32_t []) {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000}, 9);

/*** END: CONFIGURATION **/

// init controll objects
HallTimed hall(PIN_HALL, HALL_TICKS_PER_TURN);
Motor motor(PIN_MOTOR, MOTOR_PWM_HZ);
SimpleRotary rotary(PIN_ENCODER_CLK, PIN_ENCODER_DT, PIN_ENCODER_SW);

// init effects
Effect* led1_effects[N_EFFECTS] = {
  &led1_effect1,
  &led1_effect2,
  &led1_effect3,
  &led1_effect4,
  &led1_effect5,
  &led1_effect6,
  &led1_effect7,
  &led1_effect8,
  &led1_effect9,
  &led1_effect10,
  &led1_effect11,
  &led1_effect12,
  &led1_effect13,
  &led1_effect14,
  &led1_effect15,
  &led1_effect16,
  &led1_effect17
};

Effect* led2_effects[N_EFFECTS] = {
  &led2_effect1,
  &led2_effect2,
  &led2_effect3,
  &led2_effect4,
  &led2_effect5,
  &led2_effect6,
  &led2_effect7,
  &led2_effect8,
  &led2_effect9,
  &led2_effect10,
  &led2_effect11,
  &led2_effect12,
  &led2_effect13,
  &led2_effect14,
  &led2_effect15,
  &led2_effect16,
  &led2_effect17
};

Effect* led3_effects[N_EFFECTS] = {
  &led3_effect1,
  &led3_effect2,
  &led3_effect3,
  &led3_effect4,
  &led3_effect5,
  &led3_effect6,
  &led3_effect7,
  &led3_effect8,
  &led3_effect9,
  &led3_effect10,
  &led3_effect11,
  &led3_effect12,
  &led3_effect13,
  &led3_effect14,
  &led3_effect15,
  &led3_effect16,
  &led3_effect17
};

// effect variables
uint8_t effect_id = 0;  // current effect id

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

  // LED effect init
  led1_effects[0]->init();
  led2_effects[0]->init();
  led3_effects[0]->init();

  // interrupt init
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
  
  // adapt motor speed on rotary knob turn
  const byte direction = rotary.rotate();
  if ( direction == 1  ) motor.inc_speed();
  else if ( direction == 2 ) motor.dec_speed();

  // change effect on button press
  const byte pressed = rotary.push();
  if ( pressed == 1 ) {
    effect_id++;
    if ( effect_id >= N_EFFECTS) effect_id = 0;
    led1_effects[effect_id]->init();
    led2_effects[effect_id]->init();
    led3_effects[effect_id]->init();
  }

  // update effects
  led1_effects[effect_id]->update();
  led2_effects[effect_id]->update();
  led3_effects[effect_id]->update();

  // for each LED check if action required at current position
  const uint16_t position = (uint16_t)((float)hall.get_angle(HALL_ROT_ANGLE_RES) * GEAR_RATIO) % HALL_ROT_ANGLE_RES;  // motor rotation angle position, wrap around to ensure valid value
  cli();
  const uint16_t tick_no = hall.tick_no;
  sei();
  led1.turn_on_cond(tick_no, position);
  led2.turn_on_cond(tick_no, position);
  led3.turn_on_cond(tick_no, position);
}
