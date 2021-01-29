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
#include "HallTimed.h"
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

Led leds[N_LEDS] = {
  Led(PIN_LED1, true),
  Led(PIN_LED2, true),
  Led(PIN_LED3, true)
};

// rotation configuration
static const uint32_t change_millis = 100;  // after how many millis to change
static const uint16_t speed_degree = 1;  // how many degrees to change

// rotation variables
uint32_t last_change = 0;
uint16_t current_degree = 0;

// variables (do not change)
HallTimed hall(PIN_HALL, HALL_TICKS_PER_TURN);
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

  //leds[1].turn_off();
  leds[2].turn_off();
  last_change = millis();

  hall.set_interrupt_handler(isr);
  sei();  // start interrupts
}

/**
 * Loop execute indefinitiely.
 */
void loop() {
  for (size_t i = 0; i < N_LEDS; ++i) leds[i].turn_off_cond();

  // object rotation sequence steering
  if (millis() - last_change >= change_millis) {
    last_change = millis();
    leds[0].flash_at_part = current_degree;
    leds[1].flash_at_part = 360 - current_degree;
    current_degree += speed_degree;
    if (current_degree >= 360) current_degree = 0;
  }

  // for each LED check if action required at current position
  const uint16_t degree = hall.get_degree();
  for (size_t i = 0; i < N_LEDS; ++i) leds[i].turn_on_cond(hall.tick_no, degree);
}
