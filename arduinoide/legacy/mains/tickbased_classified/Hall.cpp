#include "Arduino.h"
#include "Hall.h"

Hall::Hall(uint8_t pin, uint8_t ticks_per_turn)
    : ticks_per_turn(ticks_per_turn),
      _pin(pin)
{
    pinMode(_pin, INPUT_PULLUP);
}

void Hall::set_interrupt_handler(void (*isr)(void), uint8_t mode) {
    attachInterrupt(digitalPinToInterrupt(_pin), isr, mode);
}

void Hall::handle_interrupt(void) {
    _tick_pos++;
    if(_tick_pos >= ticks_per_turn) _tick_pos = 0;  // wrap around after each complete turn
    ticked_since_last_read = true;
}

uint8_t Hall::get_tick_pos() {
    ticked_since_last_read = false;
    return _tick_pos;
}
