#include "Arduino.h"
#include "Led.h"
#include "EffectOff.h"
 
EffectOff::EffectOff(Led &led)
    : Effect(led)
{};

void EffectOff::init() {
    led.turn_off();
}

void EffectOff::update() {}
