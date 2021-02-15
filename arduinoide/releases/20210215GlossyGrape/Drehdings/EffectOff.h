/*
  EffectOff.h - Effect based on flash sequence of DrehDings project.
*/
#ifndef EffectOff_h
#define EffectOff_h

#include "Arduino.h"

#include "Effect.h"
#include "Led.h"

/**
 * Effect switching an LED off.
 * 
 * Flash logic: Led is switched off and stays off during effect.
 */
class EffectOff: public Effect {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     */
    EffectOff(Led &led);

    void init();
    void update();

    uint16_t position;  // rotation angle in degree
};

#endif
