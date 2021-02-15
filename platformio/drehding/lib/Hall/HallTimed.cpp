#include "Arduino.h"
#include "HallTimed.h"

#define ALPHA 0.5  // decay parameter for expontential moving average

HallTimed::HallTimed(uint8_t pin, uint8_t ticks_per_turn)
    : Hall(pin, ticks_per_turn) {}

void HallTimed::handle_interrupt(void) {
    Hall::handle_interrupt();
    if (tick_pos == 0) {
        const uint32_t now = micros();
        speed = ALPHA * (now - turn_start) + (1 - ALPHA) * speed;
        turn_start = now;
    }
}

uint16_t HallTimed::get_degree() {
    return (uint16_t)(360 * get_fraction());
}

float HallTimed::get_fraction() {

    cli();
    const float fraction = (float)(micros() - turn_start) / (float)speed;
    sei();

    return fraction;
}
