#include "Arduino.h"
#include "Led.h"
#include "SequenceTurningStaticObject.h"

SequenceTurningStaticObject::SequenceTurningStaticObject(Led &led, uint64_t flash_tick_pos_change_interval, uint8_t ticks_per_turn)
    : Sequence(led),
      flash_tick_pos_change_interval(flash_tick_pos_change_interval),
      ticks_per_turn(ticks_per_turn)
{
    _led.flash_tick_pos = 0;
    _led.n_ticks_cooldown = 0;
    _led.condition_mode = true;
}

void SequenceTurningStaticObject::loop_tick() {
    _led.turn_off_cond();
    if (millis() - _flash_tick_pos_last_change >= flash_tick_pos_change_interval) {
        _flash_tick_pos_last_change = millis();
        _led.flash_tick_pos++;
        if (_led.flash_tick_pos > ticks_per_turn) _led.flash_tick_pos = 0;
    }
}

void SequenceTurningStaticObject::hall_tick(uint8_t hall_tick_pos) {
    _led.turn_on_cond(hall_tick_pos);
}
