/*
  Hall.h - Library to control Hall sensor of DrehDings project.
  Timed version.
*/
#ifndef HallTimed_h
#define HallTimed_h

#include "Arduino.h"
#include "Hall.h"

/**
 * Hall sensor of DrehDings project.
 * 
 * Monitors hall sensor (motor speed) and provides
 * time based functionality.
 * 
 * Extends the tickbased version by a timed functionality
 * for greater resolution. Possibly at the costs of accuracy,
 * as all postions between ticks are estimated.
 */
class HallTimed: public Hall {
  public:
    /**
     * @param pin the pin the Hall sensor is connected to, must be digital pin
     * @param ticks_per_turn // how many ticks per turn the hall sensor sends per complete rotation
     */
    HallTimed(uint8_t pin, uint8_t ticks_per_turn);

    void handle_interrupt(void);

    // current rotation angle position in degree, estimated
    uint16_t get_degree();

    // current rotation fraction position, 0<=f<1, estimated
    float get_fraction();

    // rotation speed in micros
    volatile uint32_t speed = 0;

  protected:
    volatile uint32_t turn_start = 0;

};

#endif
