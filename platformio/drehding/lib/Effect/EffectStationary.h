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
     * @param position rotation angle position at which to flash; valid values depend on rotation angle resolution, e.g for degrees 0<=position<360
     */
    EffectStationary(Led &led, uint16_t position);

    void init();
    void update();

    uint16_t position;  // rotation angle in degree
};

#endif
