#include "Arduino.h"
#include "Led.h"
#include "EffectRotation.h"

EffectRotation::EffectRotation(Led &led, uint32_t step_interval, bool reverse)
    : Effect(led),
      step_interval(step_interval),
      reverse(reverse)
{}

void EffectRotation::init() {
    led.flash_at_part = 0;
    led.n_ticks_cooldown = 0;
    led.condition_mode = true;
    _last_change = millis();
}

void EffectRotation::update() {
    if (millis() - _last_change >= step_interval) {
        _last_change = millis();
        if (reverse) {
            led.flash_at_part--;
            if (led.flash_at_part >= 360) led.flash_at_part = 360;
        } else {
            led.flash_at_part++;
            if (led.flash_at_part >= 360) led.flash_at_part = 0;
        }
    }
}
