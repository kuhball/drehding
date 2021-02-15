#include "Arduino.h"
#include "Hall.h"

Hall::Hall(uint8_t pin, uint8_t ticks_per_turn)
    : ticks_per_turn(ticks_per_turn),
      pin(pin)
{
    pinMode(pin, INPUT_PULLUP);
}

void Hall::set_interrupt_handler(void (*isr)(void), uint8_t mode) {
    attachInterrupt(digitalPinToInterrupt(pin), isr, mode);
}

void Hall::handle_interrupt(void) {
    tick_pos++;
    if (tick_pos >= ticks_per_turn) {
        tick_pos = 0;  // wrap around after each complete turn
        tick_no++;
    }
    ticked_since_last_read = true;
}

uint8_t Hall::get_tick_pos() {
    cli();
    ticked_since_last_read = false;
    const uint8_t tick_pos_copy = tick_pos;
    sei();
    
    return tick_pos_copy;
}
