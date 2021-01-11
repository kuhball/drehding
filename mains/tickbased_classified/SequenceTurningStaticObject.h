/*
  SequenceTurningStaticObject.h - A flashing sequence.
  Tickbased version.
*/
#ifndef SequenceTurningStaticObject_h
#define SequenceTurningStaticObject_h

#include "Arduino.h"
#include "Sequence.h"
#include "Led.h"

/**
 * SequenceTurningStaticObject of DrehDings project, tickbased.
 * 
 * Flashed ones per rotation at a fixed position, then
 * changes the position, creating the illusion of the 
 * stationary object turning.
 */
class SequenceTurningStaticObject: protected Sequence {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param flash_tick_pos_change_interval // change flash tick position this often; in milliseconds
     * @param ticks_per_turn // how many ticks per turn the hall sensor sends per complete rotation
     */
    SequenceTurningStaticObject(Led &led, uint64_t flash_tick_pos_change_interval, uint8_t ticks_per_turn);

    /**
     * Call each loop.
     */
    void loop_tick();

    /**
     * Call each time the hall tick changed.
     */
    void hall_tick(uint8_t hall_tick_pos);

    uint64_t flash_tick_pos_change_interval;
    uint8_t ticks_per_turn;

  protected:
    uint64_t _flash_tick_pos_last_change = 0;
};

#endif
