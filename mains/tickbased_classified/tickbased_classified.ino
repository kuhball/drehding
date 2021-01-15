/**
 * DrehDings project: tick-based version.
 * 
 * A turning geometrical object is highlighted by LED flashes at
 * regular intervals, producing an optical illusion of stationary
 * versions of the object.
 * 
 * This version flashed the LEDs based on ticks per round measured
 * by a hallsensor (tacho) as the motor turns the object.
 */

#include "Arduino.h"

#include "Motor.h"
#include "Hall.h"
#include "Led.h"

#include "SequenceAltFlash.h"
#include "SequenceBasicFlash.h"
#include "SequenceTurningStaticObject.h"


// pin setup (all digital)
#define PIN_MOTOR 3  // motor speed control
#define PIN_HALL 14  // do not use the pin with the board LED attached (usually 13)
#define PIN_LED1 4
#define PIN_LED2 5
#define PIN_LED3 6

// base configuration
#define HALL_TICKS_PER_TURN 18  // how often the hall-sensor sends a pulse per turn; a hardware constant; see hall-sensor specification or tests/hallsensorpulses
#define MOTOR_PWM_HZ 100       // frequency of the PWM signal driving the motor; a hardware constant; see motor specification


// variables (do not change)
Led led1(PIN_LED1, true);
Led led2(PIN_LED2, true);
Led led3(PIN_LED3, true);

SequenceAltFlash seq1(led1, 0, 9, 500);
//SequenceTurningStaticObject seq1(led1, 500, HALL_TICKS_PER_TURN);
//SequenceTurningStaticObject seq2(led2, 500, HALL_TICKS_PER_TURN, true);
//SequenceBasicFlash seq1(led1, 0);
SequenceBasicFlash seq2(led2, 0);
SequenceBasicFlash seq3(led3, 0);

Hall hall(PIN_HALL, HALL_TICKS_PER_TURN);
Motor motor(PIN_MOTOR, MOTOR_PWM_HZ);

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
  led2.turn_off();
  led3.turn_off();
  motor.start();
  hall.set_interrupt_handler(isr);
  sei();  // start interrupts
}

/**
 * Loop execute indefinitiely.
 */
void loop() {
  seq1.loop_tick();
  seq2.loop_tick();
  seq3.loop_tick();

  if (hall.ticked_since_last_read) {  // only act if there has been a change since last action
    uint8_t tick_pos = hall.get_tick_pos();
    seq1.hall_tick(tick_pos);
    seq2.hall_tick(tick_pos);
    seq3.hall_tick(tick_pos);
  }
}
