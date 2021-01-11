/*
  SequenceBasicFlash.h - A flashing sequence.
  Tickbased version.
*/
#ifndef SequenceBasicFlash_h
#define SequenceBasicFlash_h

#include "Arduino.h"
#include "Sequence.h"
#include "Led.h"

/**
 * SequenceBasicFlash of DrehDings project, tickbased.
 * 
 * Flashed ones per rotation at a fixed position.
 */
class SequenceBasicFlash: protected Sequence {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param flash_tick_pos // at which hall tick position the LEd to flash
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
};

#endif
