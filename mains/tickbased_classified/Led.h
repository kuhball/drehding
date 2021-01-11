/*
  Led.h - Library to control LEDs of DrehDings project.
  Tickbased version.
*/
#ifndef Led_h
#define Led_h

#include "Arduino.h"

/**
 * LEDs of DrehDings project, tickbased.
 * 
 * Allows to switch on and off the LEDs based on the
 * current hall sensor tick, a cooldown parameter, and
 * a minimum on-time parameter.
 * 
 */
class Led {
  public:
    /**
     * @param pin the pin the LED is connected to, must be digital pin
     * @param inverse usually, a HIGH switches the LED on; set this to inverse
     */
    Led(uint8_t pin, bool inverse = false);

    /**
     * Turn the LED on, if conditions are met.
     */
    void turn_on(uint8_t hall_tick);

    /**
     * Turn the LED off, if conditions are met.
     */
    void turn_off();

    // hall sensor tick at which the LED should flash; one of [0, HALL_TICKS_PER_TURN)
    uint8_t flash_tick_pos = 0;
    // number of rotations cooldown (waiting) after each flash before flashing again
    uint8_t n_ticks_cooldown = 0;
    // time (in micros) the LED should stay on; choose lowest value that still produces sufficient illumination; see tests/determineledminblinktime
    uint64_t on_interval = 300;

  private:
    uint8_t _pin;
    uint8_t _on_val;
    uint8_t _off_val;
    
    uint64_t _last_switched_on;
    uint8_t _cooldown_counter;
};

#endif
