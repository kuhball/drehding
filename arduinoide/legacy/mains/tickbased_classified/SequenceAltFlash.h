/*
  SequenceAltFlash.h - A flashing sequence.
  Tickbased version.
*/
#ifndef SequenceAltFlash_h
#define SequenceAltFlash_h

#include "Arduino.h"
#include "Sequence.h"
#include "Led.h"

/**
 * SequenceAltFlash of DrehDings project, tickbased.
 * 
 * Flashed ones per rotation at a fixed position. At fixed
 * intervalls flashes shortly at an alternative position.
 */
class SequenceAltFlash: protected Sequence {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param flash_tick_pos at which hall tick position the LED to flash
     * @param flash_tick_pos_alt atlernative flash tick position
     * @param after how many millis to flash once at flash_tick_pos_alt
     */
    SequenceAltFlash(Led &led, uint8_t flash_tick_pos, uint8_t flash_tick_pos_alt, uint64_t flash_tick_pos_freq);

    /**
     * Call each loop.
     */
    void loop_tick();

    /**
     * Call each time the hall tick changed.
     */
    void hall_tick(uint8_t hall_tick_pos);

    uint8_t flash_tick_pos;
    uint8_t flash_tick_pos_alt;
    uint64_t flash_tick_pos_freq;

  private:
    uint64_t _flash_tick_pos_alt_last_active = 0;
    uint64_t _flash_tick_pos_alt_keep_active = 250;
};

#endif
