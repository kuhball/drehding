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

void Led::turn_on(uint8_t hall_tick) {
    if (hall_tick == flash_tick_pos) {  // if in right position
        if (_cooldown_counter >= n_ticks_cooldown) {  // if cooldown passed
            digitalWrite(_pin, _on_val);  // switch LED on
            _cooldown_counter = 0;  // reset cooldown
            _last_switched_on = micros();  // set timestamp
        } else {  // skip one turning of the motor
            _cooldown_counter++;
        }
    }
}

void Led::turn_off() {
    if (micros() - _last_switched_on >= on_interval) digitalWrite(_pin, _off_val);
}
