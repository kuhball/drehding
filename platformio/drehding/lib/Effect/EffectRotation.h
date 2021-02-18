/*
  EffectRotation.h - Rotating object effect of DrehDings project.
*/
#ifndef EffectRotation_h
#define EffectRotation_h

#include "Arduino.h"

#include "Effect.h"
#include "Led.h"

/**
 * Effect that creates a stable object that rotates at the desired speed
 * and in the desired direction.
 * 
 * Flash logic: Flashes always at rotation angle A. At fixes intervals,
 * increases (or decreases) A.
 */
class EffectRotation: public Effect {
  public:
    /**
     * @param led the pin the motor is connected to, can be digital or analogue pin; try not to use pin 5 and 6, because of interactions with the millis() and delay() functions
     * @param step_interval after this many milliseconds, change the angle position one degree (aka 360 steps for one rotation)
     * @param rotation_resolution the rotation angle resolution; eg. 360 for degree
     * @param reverse set to true to turn reversed
     */
    EffectRotation(Led &led, uint32_t step_interval, uint16_t rotation_resolution, bool reverse = false);

    void init();
    void update();

    const uint32_t step_interval;
    const uint16_t rotation_resolution;
    const bool reverse;

  private:
    uint32_t _last_change = 0;
};

#endif
