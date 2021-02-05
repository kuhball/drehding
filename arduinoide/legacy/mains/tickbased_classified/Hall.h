/*
  Hall.h - Library to control Hall sensor of DrehDings project.
  Tickbased version.
*/
#ifndef Hall_h
#define Hall_h

#include "Arduino.h"

/**
 * Hall sensor of DrehDings project, tickbased.
 * 
 * Monitors hall sensor (motor speed) and provides
 * tick reading functionality.
 * 
 * 
 */
class Hall {
  public:
    /**
     * @param pin the pin the Hall sensor is connected to, must be digital pin
     * @param ticks_per_turn // how many ticks per turn the hall sensor sends per complete rotation
     */
    Hall(uint8_t pin, uint8_t ticks_per_turn);

    void set_interrupt_handler(void (*ISR)(void), uint8_t mode = CHANGE);
    void handle_interrupt(void);

    // read the current tick position
    uint8_t get_tick_pos();
    // indicates whether there has been a registered tick since the last tick readout
    volatile bool ticked_since_last_read;    

    uint8_t ticks_per_turn;
    
  private:
    uint8_t _pin;
    volatile uint8_t _tick_pos;
};

#endif
