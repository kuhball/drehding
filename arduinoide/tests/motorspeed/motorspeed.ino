/*
  Sets PIN to the motor's PWM speed control input.

  Test various settings fro Hz and pulse length until you
  got a feeling for your motor.
 */

// pin setup (all digital)
#define PIN_MOTOR 2  // motor speed control
#define MOTOR_PWM_HZ 100        // frequency of the PWM signal driving the motor; a hardware constant; see motor specification

// motor configuration
static const uint8_t motor_pulse_length = 38;  // which fraction of the motor's PWM signal to send HIGH; [0,255]; determines motor turning speed

void setup() {
  pinMode(PIN_MOTOR, OUTPUT);
  
  // create PWM singal for motor
  analogWriteFrequency(PIN_MOTOR, MOTOR_PWM_HZ);
  analogWrite(PIN_MOTOR, motor_pulse_length);  // 0-255 aka 0-100% of duty cycle on
}

void loop() {}
