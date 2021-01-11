/*
  SequenceBasicFlash.h - A flashing sequence.
  Tickbased version.
*/
#ifndef Sequence_h
#define Sequence_h

#include "Arduino.h"
#include "Led.h"

/**
 * SequenceBasicFlash of DrehDings project, tickbased.
 * 
 * Flashed ones per rotation at a fixed position.
 */
class SequenceBasicFlash {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param flash_tick_pos // frequency in Hz of the PWM signal driving the motor; a hardware constant; see motor specification
     */
    SequenceBasicFlash(Led &led, uint8_t flash_tick_pos);

    /**
     * Call each loop.
     */
    void loop_tick();

    /**
     * Call each time the hall tick changed.
     */
    void hall_tick(uint8_t hall_tick_pos);

  private:
    Led &_led;
};

#endif
