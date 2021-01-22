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
#include <assert.h>

#include "Arduino.h"

#include "Motor.h"
#include "Hall.h"
#include "Led.h"


// pin setup (all digital)
#define PIN_MOTOR 3  // motor speed control
#define PIN_HALL 14  // do not use the pin with the board LED attached (usually 13)
#define PIN_LED1 4
#define PIN_LED2 5
#define PIN_LED3 6

// base configuration
#define HALL_TICKS_PER_TURN 18  // how often the hall-sensor sends a pulse per turn; a hardware constant; see hall-sensor specification or tests/hallsensorpulses
#define MOTOR_PWM_HZ 100       // frequency of the PWM signal driving the motor; a hardware constant; see motor specification

// sequence configuration
#define N_LEDS 3
#define SEQ_N_ELEMENTS 155

//static const uint64_t seq_inter[SEQ_N_ELEMENTS] = {2000, 200, 1000, 300, 1500, 300, 1000};  // in millis
static const uint64_t seq_inter[SEQ_N_ELEMENTS] = {  // in millis
  3000,
  500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
  200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
  200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200
};
static const uint8_t seq_tickp[N_LEDS][SEQ_N_ELEMENTS] = {  // hall sensor tick positions at which to flash
  {0,
   0, 9, 0, 9, 0, 9, 0, 9, 0, 9,
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
   17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
   17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
   0, 1, 2, 3, 4, 5, 6, 7, 8,
   0, 1, 2, 3, 4, 5, 6, 7, 8,
   0, 1, 2, 3, 4, 5, 6, 7, 8,
   0, 1, 2, 3, 4, 5, 6, 7, 8,
   0, 3, 12, 14, 6, 2, 4, 8, 17, 9, 3, 8, 12, 11, 16, 2, 5,
   0, 3, 12, 14, 6, 2, 4, 8, 17, 9, 3, 8, 12, 11, 16, 2, 5},
  {},
  {}
};
// {0, 3, 12, 14, 6, 2, 4, 8, 17, 9, 3, 8, 12, 11, 16, 2, 5}  // pseudo-random flipping (@>=200msn=18)
// {0, 1, 2, 3, 4, 5, 6, 7, 8}  // slowly turning, then flipping halfway through (@200ms,n=9)
// {17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}  // slowly turning CCW (@200ms,n=18)
// {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}  // slowly turning CW (@200ms,n=18)
// {0, 9}  // flip sides (@>=500ms,n=2)
// {0}  // stationary image (@>=500ms,n=1)
Led leds[N_LEDS] = {Led(PIN_LED1, true), Led(PIN_LED2, true), Led(PIN_LED3, true)};

// variables (do not change)
uint8_t seq_c = 0;
uint64_t seq_last_changed = 0;

// variables (do not change)
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
  motor.start();

  leds[1].turn_off();
  leds[2].turn_off();

  seq_last_changed = millis();

  hall.set_interrupt_handler(isr);
  sei();  // start interrupts
}

/**
 * Loop execute indefinitiely.
 */
void loop() {
  for (size_t i = 0; i < N_LEDS; ++i) leds[i].turn_off_cond();

  // check if time to go to next sequence check
  if (millis() - seq_last_changed >= seq_inter[seq_c]) {
    seq_last_changed = millis();
    
    seq_c++;
    if (seq_c >= SEQ_N_ELEMENTS) seq_c = 0;

    for (size_t i = 0; i < N_LEDS; ++i) leds[i].flash_tick_pos = seq_tickp[i][seq_c];
  }

  if (hall.ticked_since_last_read) {  // only act if there has been a change since last action
    uint8_t tick_pos = hall.get_tick_pos();
    for (size_t i = 0; i < N_LEDS; ++i) leds[i].turn_on_cond(tick_pos);
  }
}
