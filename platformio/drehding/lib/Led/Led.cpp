#include "Arduino.h"
#include "Led.h"

Led::Led(uint8_t pin, bool inverse) 
    : _pin(pin)
{
    pinMode(_pin, OUTPUT);
    if (inverse) {
        _on_val = LOW;
        _off_val = HIGH;
    } else {
        _on_val = HIGH;
        _off_val = LOW;
    }
}

void Led::turn_on_cond(uint16_t tick_no, uint16_t pos) {
    if (!condition_mode) return;

    // if not acted yet this turn and part of turn is reached
    if ((tick_no != tick_no_last_acted) && (pos == flash_at_pos)) {
        tick_no_last_acted = tick_no;
        turn_on_if_cooldown();
    }
}

void Led::turn_off_cond() {
    if (!condition_mode) return;

    if (micros() - _last_switched_on >= on_interval) _turn_off();
}

void Led::turn_on() {
    condition_mode = false;
    _turn_on();
}

void Led::turn_off() {
    condition_mode = false;
    _turn_off();
}

void Led::turn_on_if_cooldown() {
    if (_cooldown_counter >= n_ticks_cooldown) {  // if cooldown passed
        _turn_on();
        _cooldown_counter = 0;  // reset cooldown
        _last_switched_on = micros();  // set timestamp
    } else {  // skip one turning of the motor
        _cooldown_counter++;
    }
}

void Led::_turn_on() {
    digitalWrite(_pin, _on_val);
}

void Led::_turn_off() {
    digitalWrite(_pin, _off_val);
}
