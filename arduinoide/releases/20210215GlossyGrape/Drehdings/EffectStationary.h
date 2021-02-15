/*
  EffectStationary.h - Effect based on flash sequence of DrehDings project.
*/
#ifndef EffectStationary_h
#define EffectStationary_h

#include "Arduino.h"

#include "Effect.h"
#include "Led.h"

/**
 * Effect creating a stationary object.
 * 
 * Flash logic: Provided with an angle positions, will always
 * flash when the object is at that exact rotation angle.
 */
class EffectStationary: public Effect {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param position rotation angle in degree at which to flash
     */
    EffectStationary(Led &led, uint16_t position);

    void init();
    void update();

    uint16_t position;  // rotation angle in degree
};

#endif
