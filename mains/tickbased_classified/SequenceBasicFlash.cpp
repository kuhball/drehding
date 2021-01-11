#include "Arduino.h"
#include "SequenceBasicFlash.h"

SequenceBasicFlash::SequenceBasicFlash(Led &led, uint8_t flash_tick_pos)
    : _led(led)
{
    _led.flash_tick_pos = flash_tick_pos;
    _led.n_ticks_cooldown = 0;
    _led.condition_mode = true;
}

void SequenceBasicFlash::loop_tick() {
    _led.turn_off_cond();
}

void SequenceBasicFlash::hall_tick(uint8_t hall_tick_pos) {
    _led.turn_on_cond(hall_tick_pos);
}
