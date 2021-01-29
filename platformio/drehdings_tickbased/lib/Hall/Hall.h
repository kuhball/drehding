/*
  Hall.h - Library to control Hall sensor of DrehDings project.
  Tickbased version.
*/
#ifndef Hall_h
#define Hall_h

#include "Arduino.h"

/**
 * Hall sensor of DrehDings project.
 * 
 * Monitors hall sensor (motor speed) and provides
 * tick reading functionality.
 * 
 * Tickbased, that means at each tick of the hall sensor
 * an action is possible. The number of ticks of the hall
 * sensor determines the possible resolution.
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
    // the number of the current tick, incremental counter, wraps around
    volatile uint16_t tick_no = 0;
    
    uint8_t ticks_per_turn;
    
  protected:
    uint8_t pin;
    volatile uint8_t tick_pos;
};

#endif
