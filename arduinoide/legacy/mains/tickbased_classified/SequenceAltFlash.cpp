#include "Arduino.h"
#include "Led.h"
#include "SequenceAltFlash.h"

SequenceAltFlash::SequenceAltFlash(Led &led, uint8_t flash_tick_pos, uint8_t flash_tick_pos_alt, uint64_t flash_tick_pos_freq)
    : Sequence(led),
      flash_tick_pos(flash_tick_pos),
      flash_tick_pos_alt(flash_tick_pos_alt),
      flash_tick_pos_freq(flash_tick_pos_freq)
{
    _led.flash_tick_pos = flash_tick_pos;
    _led.n_ticks_cooldown = 0;
    _led.condition_mode = true;
}

void SequenceAltFlash::loop_tick() {
    _led.turn_off_cond();
}

void SequenceAltFlash::hall_tick(uint8_t hall_tick_pos) {
    //if (millis() - _flash_tick_pos_alt_last_active >= _flash_tick_pos_alt_keep_active) {
    //    _led.flash_tick_pos = flash_tick_pos;
    if (millis() - _flash_tick_pos_alt_last_active > flash_tick_pos_freq) {
        if (_led.flash_tick_pos == flash_tick_pos_alt) _led.flash_tick_pos = flash_tick_pos;
        else _led.flash_tick_pos = flash_tick_pos_alt;
        _flash_tick_pos_alt_last_active = millis();
    }
    _led.turn_on_cond(hall_tick_pos);
}
