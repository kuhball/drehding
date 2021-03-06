/*
  EffectMultiSin.h - Rotating object with function speed pattern effect of DrehDings project.
*/
#ifndef EffectMultiSin_h
#define EffectMultiSin_h

#include "Arduino.h"

#include "EffectFunction.h"
#include "Led.h"

/**
 * Effect that creates a stable object that rotates at a speed
 * following as multi-sinus-like function.
 * 
 * Flash logic: Flashes always at rotation angle A. Increase A
 * following a multi-sinus-like function.
 */
class EffectMultiSin: public EffectFunction {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param effect_duration the overall duration of the effect in ms
     * @param rotation_resolution the rotation angle resolution; eg. 360 for degree
     */
    EffectMultiSin(Led &led, uint32_t effect_duration, uint16_t rotation_resolution);

    float fun(float effect_fraction);
};

#endif
