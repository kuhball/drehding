/*
  EffectWave.h - Rotating object with function speed pattern effect of DrehDings project.
*/
#ifndef EffectWave_h
#define EffectWave_h

#include "Arduino.h"

#include "EffectFunction.h"
#include "Led.h"

/**
 * Effect that creates a stable object that rotates at a speed
 * following as wave-like function.
 * 
 * Flash logic: Flashes always at rotation angle A. Increase A
 * following a wave-like function.
 */
class EffectWave: public EffectFunction {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param effect_duration the overall duration of the effect in ms
     * @param rotation_resolution the rotation angle resolution; eg. 360 for degree
     */
    EffectWave(Led &led, uint32_t effect_duration, uint16_t rotation_resolution);

    float fun(float effect_fraction);
};

#endif
