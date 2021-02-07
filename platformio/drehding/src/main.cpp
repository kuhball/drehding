/**
 * DrehDings project.
 * 
 * A turning geometrical object is highlighted by LED flashes at
 * regular intervals, producing an optical illusion of stationary
 * versions of the object.
 * 
 * This version flashed the LEDs based on object rotation speed
 * derived from the ticks per round measured by a
 * hallsensor (tacho) as the motor turns the object.
 */
#include "Arduino.h"
#include "Encoder.h"
#include "Bounce.h"

#include "Motor.h"
#include "HallTimed.h"
#include "Led.h"


/*** START: CONFIGURATION **/

// pin setup
// for all: do not use the pin with the board LED attached (usually 13)
// for all: use only digital PINs
// @see https://www.pjrc.com/store/teensy40.html for PIN diagram
#define PIN_MOTOR 15  // motor speed control, use pin that is PWM enabled
#define PIN_HALL 14  // motor's hallsensor's signal, usually termed FG
#define PIN_LED1 4
#define PIN_LED2 5
#define PIN_LED3 6
#define PIN_ENCODER_CLK 10  // rotary encoder's CLK signal, also called A signal
#define PIN_ENCODER_DT 11  // rotary encoder's DT signal, also called B signal
#define PIN_ENCODER_SW 12  // either signal of rotary encoder's integrated push-button or any other push-button

// base configuration
#define HALL_TICKS_PER_TURN 18  // how often the hall-sensor sends a pulse per turn; a hardware constant; see hall-sensor specification or tests/hallsensorpulses
#define MOTOR_PWM_HZ 100  // frequency of the PWM signal driving the motor; a hardware constant; see motor specification
#define GEAR_RATIO 1.0  // if gearing employed, set this to the ratio; >1.0 means object turns faster than motor, <1.0 means object turns slower than motor

// effect configurations
// LED1 (CW) and LED2 (CCW) rotation configuration
static const uint32_t change_millis = 100;  // after how many millis to change
static const uint16_t speed_degree = 1;  // how many degrees to change

/*** END: CONFIGURATION **/


// LED objects init
Led leds[3] = {
  Led(PIN_LED1, true),
  Led(PIN_LED2, true),
  Led(PIN_LED3, true)
};

// controll objects init
HallTimed hall(PIN_HALL, HALL_TICKS_PER_TURN);
Motor motor(PIN_MOTOR, MOTOR_PWM_HZ);
Encoder motorspeed(PIN_ENCODER_CLK, PIN_ENCODER_DT);
Bounce button = Bounce(PIN_ENCODER_SW, 50); 

// rotation variables
uint32_t last_change = 0;
uint16_t current_degree = 0;

// speed control variables
uint8_t speed = 0;


/**
 * Function called on interrupt.
 */
void isr() {
  hall.handle_interrupt();
}

/**
 * Setup the routine.
 */
void setup() {
  // init motor speed controll
  motorspeed.write((int32_t)Motor::DUTY_CYCLE_DEFAULT);

  Serial.begin(9600);

  // LED sequence control
  leds[2].flash_at_part = 0;
  //leds[2].turn_off();
  last_change = millis();

  hall.set_interrupt_handler(isr);
  sei();  // start interrupts
}

/**
 * Loop execute indefinitiely.
 */
void loop() {
  for (size_t i = 0; i < sizeof(leds); ++i) leds[i].turn_off_cond();

  // object rotation effect steering
  if (millis() - last_change >= change_millis) {
    last_change = millis();
    leds[0].flash_at_part = current_degree;
    leds[1].flash_at_part = 360 - current_degree;
    current_degree += speed_degree;
    if (current_degree >= 360) current_degree = 0;
  }

  // for each LED check if action required at current position
  uint16_t degree = (uint16_t)((float)hall.get_degree() * GEAR_RATIO);  // motor degree to object degree
  while (degree > 360) degree = degree - 360;  // wrap around to ensure valid angle
  for (size_t i = 0; i < sizeof(leds); ++i) leds[i].turn_on_cond(hall.tick_no, degree);

  // adapt motor speed if changed
  const int32_t encoder_pos = motorspeed.read();
  const uint8_t speed_new = constrain(encoder_pos, 0, 255);
  motorspeed.write((int32_t)speed_new);
  if (speed_new != speed) {
    motor.set_speed(speed);
    speed = speed_new;
  }

  // react to button press (LED3 effect)
  if (button.update()) {
    if (button.fallingEdge()) {
      //Serial.print("Button pressed: ");
      if (leds[2].flash_at_part == 0) {
        leds[2].flash_at_part = 45;
        //Serial.println("45");
      } else {
        leds[2].flash_at_part = 0;
        //Serial.println("0");
      }
    }
  }
  
}
