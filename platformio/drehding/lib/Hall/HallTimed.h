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

    /**
     * Current rotation angle position in degree.
     * 
     * The estimated position in degree of the rotating objects current turn.
     * 
     * @return rotation angle degree, 0<=degree<360
     */
    uint16_t get_degree();

    /**
     * Current rotation angle position in given resolution.
     * 
     * The estimated position of the rotating objects current turn in given resolution.
     * 
     * @param resolution desired rotation angle resolution, e.g. 360 for degree
     * @return rotation angle position, 0<=position<resolution
     */
    uint16_t get_angle(uint16_t resolution);

    /**
     * Current rotation angle position as fraction of the complete turn.
     * 
     * Can return values greater or equal to one in some cases where the update is delayed.
     * Use get_angle() or get_degree() for a safe version.
     * 
     * @return rotation angle fraction, usually 0<=fraction<1
     */
    float get_fraction();

    // rotation speed in micros
    volatile uint32_t speed = 0;

  protected:
    volatile uint32_t turn_start = 0;

};

#endif
