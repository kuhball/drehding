#include "Arduino.h"
#include "Led.h"
#include "EffectFunction.h"

EffectFunction::EffectFunction(Led &led, uint32_t effect_duration, uint16_t rotation_resolution)
    : Effect(led),
      effect_duration(effect_duration),
      rotation_resolution(rotation_resolution)
{}

void EffectFunction::init() {
    led.flash_at_pos = 0;
    led.n_ticks_cooldown = 0;
    led.condition_mode = true;
    _ms_timer = 0;
}

void EffectFunction::update() {
    const uint32_t effect_millis_into = _ms_timer % effect_duration;
    _ms_timer = effect_millis_into;
    const float fraction = (float)effect_millis_into / (float)effect_duration;
    uint16_t position = (uint16_t)(fun(fraction) * rotation_resolution);
    led.flash_at_pos = position;
}
