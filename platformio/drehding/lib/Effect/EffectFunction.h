/*
  EffectFunction.h - Base class for all function based movement effects of DrehDings project.
*/
#ifndef EffectFunction_h
#define EffectFunction_h

#include "Arduino.h"

#include "Effect.h"
#include "Led.h"

/**
 * Abstract Effect to implement movement patterns that are based on
 * a function.
 * 
 * Flash logic: Employs a function that translate the effect fractin (time based)
 * to the rotation angle at which to blink.
 * 
 * To implement such an effect, inherit from this class and implement fun().
 */
class EffectFunction: public Effect {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param effect_duration the overall duration of the effect in ms
     * @param rotation_resolution the rotation angle resolution; eg. 360 for degree
     */
    EffectFunction(Led &led, uint32_t effect_duration, uint16_t rotation_resolution);

    void init();
    void update();

    /**
     * Takes the current fraction of the effect duration
     * and returns the position at which to flash
     * based on it.
     */
    virtual float fun(float effect_fraction) = 0;

    const uint32_t effect_duration;
    const uint16_t rotation_resolution;

  private:
    elapsedMillis _ms_timer;
};

#endif
