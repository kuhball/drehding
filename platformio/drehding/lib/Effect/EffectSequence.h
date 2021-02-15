/*
  EffectSequence.h - Effect based on flash sequence of DrehDings project.
*/
#ifndef EffectSequence_h
#define EffectSequence_h

#include "Arduino.h"

#include "Effect.h"
#include "Led.h"

/**
 * Flexible effect creation based on a flash sequence at different
 * rotation angles.
 * 
 * Flash logic: Provided with a list of flash angle positions and intervals,
 * flashes at the first position for the length of the first interval, at the
 * second position for the length of the second interval, etc. Loops around
 * after reaching the end.
 */
class EffectSequence: public Effect {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param positions rotation angle in degree at which to flash; must all be 0<=angle<360
     * @param intervals time in milliseconds to stay with the associated rotation angle; must be of same length as positions
     * @param size the size of the positions and intervals arrays
     */
    EffectSequence(Led &led, uint16_t positions[], uint32_t intervals[], uint32_t size);

    void init();
    void update();

    uint16_t *positions;  // sequence on rotation angles in degrees
    uint32_t *intervals;  // sequence of intervalls in milliseconds
    uint32_t size;  // size of above arrays

  private:
    uint32_t _seq_pos = 0;
    uint32_t _last_change = 0;
};

#endif
