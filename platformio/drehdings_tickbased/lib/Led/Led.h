/*
  Led.h - Library to control LEDs of DrehDings project.
*/
#ifndef Led_h
#define Led_h

#include "Arduino.h"

/**
 * LEDs of DrehDings project.
 * 
 * Allows to switch on and off the LEDs based on:
 * - the current part of the motor rotation reached
 * - a cooldown parameter, and
 * - a minimum on-time parameter
 */
class Led {
  public:
    /**
     * @param pin the pin the LED is connected to, must be digital pin
     * @param inverse usually, a HIGH switches the LED on; set this to inverse
     */
    Led(uint8_t pin, bool inverse = false);

    /**
     * Turn LED on, if conditions are met.
     * Does nothing if condition_mode is disabled.
     * 
     * @param tick_no current tick no of the motor, aka tick counter
     * @param part current roation part, e.g. degree
     */
    void turn_on_cond(uint16_t tick_no, uint16_t part);

    /**
     * Turn LED off, if conditions are met.
     * Does nothing if condition_mode is disabled.
     */
    void turn_off_cond();

    /**
     * Turn LED on (and keep on).
     * Disables condition_mode.
     */
    void turn_on();

    /**
     * Turn LED off (and keep off).
     * Disables condition_mode.
     */
    void turn_off();

    // at which turn part of the motor the LED should flash
    uint16_t flash_at_part = 0;
    // number of rotations cooldown (waiting) after each flash before flashing again
    uint8_t n_ticks_cooldown = 0;
    // time (in micros) the LED should stay on; choose lowest value that still produces sufficient illumination; see tests/determineledminblinktime
    uint64_t on_interval = 300;
    // set condition LED turn on/off
    bool condition_mode = true;

  protected:
    // turn led on if cooldown has passed
    void turn_on_if_cooldown() ;
    // the tick no at which the last action was performed
    uint16_t tick_no_last_acted = 0;
    

  private:
    void _turn_on();
    void _turn_off();

    uint8_t _pin;
    uint8_t _on_val;
    uint8_t _off_val;
    
    uint64_t _last_switched_on;
    uint8_t _cooldown_counter;
};

#endif
