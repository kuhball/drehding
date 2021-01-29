/*
  Sequence.h - Abstract sequence class of DrehDings project.
  Tickbased version.
*/
#ifndef Sequence_h
#define Sequence_h

#include "Arduino.h"

/**
 * Sequence abstract class of DrehDings project, tickbased.
 * 
 * Use as baseclass for all sequence classes.
 */
class Sequence {
  public:
    Sequence(Led &led): _led(led) {};
    /**
     * Call each loop.
     */
    virtual void loop_tick() = 0;

    /**
     * Call each time the hall tick changed.
     */
    virtual void hall_tick(uint8_t hall_tick_pos) = 0;

  protected:
    Led &_led;
};

#endif
