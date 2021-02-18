/*
  maincfg.h - Primary hardware setup configuration file.
*/
#ifndef MainCfg_h
#define MainCfg_h

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

#endif