/*
  Motor.h - Library to control Motor of DrehDings project.
  Tickbased version.
*/
#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

/**
 * Motor of DrehDings project, tickbased.
 * 
 * Allows to set the motor speed via a PWM signal.
 * 
 * 
 */
class Motor {
  public:
    /**
     * @param pin the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param frequency // frequency in Hz of the PWM signal driving the motor; a hardware constant; see motor specification
     */
    Motor(uint8_t pin, uint64_t frequency);
    
    // start motor at currently set speed; note: if speed=0, will not do anything
    void start();
    // stop motor
    void stop();
    /**
     * Set motor speed.
     * Also starts motor if not already running.
     * 
     * @param speed betwee 0 (off) and 255 (full speed); aka 0-100% of duty cycle on
     */
    void set_speed(uint8_t speed);

    uint64_t frequency;

    static const uint8_t DUTY_CYCLE_RESOLUTION;
    static const uint8_t DUTY_CYCLE_DEFAULT;

  private:
    uint8_t _pin;
    // which fraction of the motor's PWM signal to send HIGH; [0,255]; determines motor turning speed
    uint8_t _duty_cycle;
    
};

#endif
