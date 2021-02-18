#include "Arduino.h"
#include "Led.h"
#include "EffectStationary.h"

EffectStationary::EffectStationary(Led &led, uint16_t position)
    : Effect(led),
      position(position)
{};

void EffectStationary::init() {
    led.flash_at_pos = position;
    led.n_ticks_cooldown = 0;
    led.condition_mode = true;
}

void EffectStationary::update() {}
