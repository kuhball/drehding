#include "Arduino.h"
#include "Led.h"
#include "EffectMultiSin.h"

EffectMultiSin::EffectMultiSin(Led &led, uint32_t effect_duration, uint16_t rotation_resolution)
    : EffectFunction(led, effect_duration, rotation_resolution)
{}

float EffectMultiSin::fun(float effect_fraction) {
    // weird functtion, see https://www.wolframalpha.com/input/?i=plot+%28sin%28x+*+31.61592653589793%29+%2B+cos%28x+*+31.61592653589793+*+PI%2F2%29+%2B+2%29+%2F+4+from+0+to+1
    return (sin(effect_fraction * 31.61592653589793) + cos(effect_fraction * 31.61592653589793 * PI/2) + 2) / 4;
}

