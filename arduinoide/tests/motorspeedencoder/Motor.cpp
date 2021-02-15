#include "Arduino.h"
#include "Motor.h"

const uint8_t Motor::DUTY_CYCLE_RESOLUTION = 8;
const uint8_t Motor::DUTY_CYCLE_DEFAULT = 127;

Motor::Motor(uint8_t pin, uint64_t frequency)
    : frequency(frequency),
      _pin(pin),
      _duty_cycle(Motor::DUTY_CYCLE_DEFAULT)
{
    pinMode(_pin, OUTPUT);
    //analogWriteResolution(Motor::DUTY_CYCLE_RESOLUTION);  // currently not implemented
    analogWriteFrequency(_pin, frequency);
    analogWrite(_pin, 0UL);  // 0-255 aka 0-100% of duty cycle on; start stopped
}

void Motor::start() {
    analogWrite(_pin, _duty_cycle);
}

void Motor::stop() {
    analogWrite(_pin, 0UL);
}

void Motor::set_speed(uint8_t speed) {
    _duty_cycle = speed;
    start();
}

void Motor::inc_speed(uint8_t val) {
    _duty_cycle = (_duty_cycle + val <= 255) ? _duty_cycle + val : 255;
    start();
}

void Motor::dec_speed(uint8_t val) {
    _duty_cycle = (_duty_cycle - val >= 0) ? _duty_cycle - val : 0;
    start();
}