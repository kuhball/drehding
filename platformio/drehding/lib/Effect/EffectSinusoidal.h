/*
  EffectSinusoidal.h - Rotating object with sinusoidal speed pattern effect of DrehDings project.
*/
#ifndef EffectSinusoidal_h
#define EffectSinusoidal_h

#include "Arduino.h"

#include "EffectFunction.h"
#include "Led.h"

/**
 * Effect that creates a stable object that rotates at a speed
 * following as sinus function.
 * 
 * Flash logic: Flashes always at rotation angle A. Increase A
 * following a sinus function.
 */
class EffectSinusoidal: public EffectFunction {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param effect_duration the overall duration of the effect in ms
     * @param rotation_resolution the rotation angle resolution; eg. 360 for degree
     */
    EffectSinusoidal(Led &led, uint32_t effect_duration, uint16_t rotation_resolution);

    float fun(float effect_fraction);
};

#endif
