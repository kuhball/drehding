#include "Arduino.h"
#include "Led.h"
#include "EffectSinusoidal.h"

EffectSinusoidal::EffectSinusoidal(Led &led, uint32_t effect_duration, uint16_t rotation_resolution)
    : EffectFunction(led, effect_duration, rotation_resolution)
{}

float EffectSinusoidal::fun(float effect_fraction) {
    return sin(effect_fraction * PI);  // sinusoid
    //return fmod(effect_fraction, 1);  // sawtooth, aka normal turning :)
}

