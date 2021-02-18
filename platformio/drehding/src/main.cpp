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

/*** START: CONFIGURATION **/
#include "config.h"
#include "effectconfigs/playground.h"  // choose the effect config you would like to include
/*** END: CONFIGURATION **/

#include "SimpleRotary.h"
#include "Motor.h"
#include "HallTimed.h"
#include "Led.h"
#include "EffectOff.h"
#include "EffectStationary.h"
#include "EffectSequence.h"
#include "EffectRotation.h"


// init controll objects
HallTimed hall(PIN_HALL, HALL_TICKS_PER_TURN);
Motor motor(PIN_MOTOR, MOTOR_PWM_HZ);
SimpleRotary rotary(PIN_ENCODER_CLK, PIN_ENCODER_DT, PIN_ENCODER_SW);

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
