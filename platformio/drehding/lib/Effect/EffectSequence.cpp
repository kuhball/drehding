#include "Arduino.h"
#include "Led.h"
#include "EffectSequence.h"

EffectSequence::EffectSequence(Led &led, uint16_t positions[], uint32_t intervals[], uint32_t size)
    : Effect(led),
      positions(positions),
      intervals(intervals),
      size(size)
{};

void EffectSequence::init() {
    led.flash_at_pos = positions[_seq_pos];
    led.n_ticks_cooldown = 0;
    led.condition_mode = true;
    _last_change = millis();
}

void EffectSequence::update() {
    if (millis() - _last_change >= intervals[_seq_pos]) {
        _seq_pos++;
        if (_seq_pos >= size) _seq_pos = 0;
        led.flash_at_pos = positions[_seq_pos];
        _last_change = millis();
    }
}
