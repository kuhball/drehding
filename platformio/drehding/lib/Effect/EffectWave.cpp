#include "Arduino.h"
#include "Led.h"
#include "EffectWave.h"

EffectWave::EffectWave(Led &led, uint32_t effect_duration, uint16_t rotation_resolution)
    : EffectFunction(led, effect_duration, rotation_resolution)
{}

float EffectWave::fun(float effect_fraction) {
    // weird function, see https://www.wolframalpha.com/input/?i=plot+exp%28-0.1+%2B+6.6+*+x+-+7+*+pow%282.2+*+x+-+0.7%2C+3%29%29+%2F+16.0+from+0+to+1
    return exp(-0.1 + 6.6 * effect_fraction - 7 * pow(2.2 * effect_fraction - 0.7, 3)) / 16.0;
}

