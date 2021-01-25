/*
 * Script to measure and plot the microseconds a motor turn takes. Beside
 * the measured value also plots the moving average.
 * 
 * Put the hallsensors PWM output (tacho) line to the designated pin, attach
 * the motor driver to the motor pin.
 * 
 * Configure the motor speed by setting the pulse length for the motor signal.
 * Alternatively, you can controll the motor driver with a PWM singal generator.
 * 
 * Configure the hall sensor by setting the number of signals send per turn.
 * 
 * Additionally, on your PC, open Tools > Serial Plotter to read the logs
 * (this might cause an error, follow the permission setting instructions
 * there). Make sure that the Bauds are set to the same number as in the
 * Serial.begin() method below. The script will write out the motor speed
 * at every completed turn.
 * 
 * Note that an input pin for a PWM signal should have a pull-up resistor.
 * This can be either realized in hardware, or, like here, by setting the
 * pinMode to INPUT_PULLUP. THis inverts the HIGH/LOW signals.
 * If this is not set, random fluctuations will influence the signal, especially
 * if there is not PWM signal for some time.
 * 
 * Do not use the pin with the hardwired LED on the board for INPUT_PULLUP
 * (usually pin 13).
 * 
 * Inspired by: www.theorycircuit.com and http://thebestcasescenario.com
 */

// pin configuration
#define PIN_PWM 14  // PIN where the PWM singal arrives
#define PIN_MOTOR 2  // motor speed control
#define MOTOR_PWM_HZ 100        // frequency of the PWM signal driving the motor; a hardware constant; see motor specification

#define MOVING_AVG_SIZE 10  // size of the moving average buffer for smoother values

// motor configuration
static const uint8_t motor_pulse_length = 38;  // which fraction of the motor's PWM signal to send HIGH; [0,255]; determines motor turning speed

// hall sensor configuration
const uint8_t pulses_per_round = 9;  // set this to the hallsensor's pulses per turn

// global variables
volatile uint32_t itrc = 0;  // interrupt counter
uint32_t then;  // timer
uint32_t moving_avg[MOVING_AVG_SIZE] = { };
uint8_t moving_avg_pos = 0;

// moving average functions
void ma_add(uint32_t val) {
  moving_avg[moving_avg_pos] = val;
  moving_avg_pos++;
  if (moving_avg_pos >= MOVING_AVG_SIZE) moving_avg_pos = 0;
}

uint32_t ma_avg() {
  uint32_t sum = 0;
  for (size_t i = 0; i < MOVING_AVG_SIZE; i++) {
    sum += moving_avg[i];
  }
  return sum / MOVING_AVG_SIZE;
}

// function called by interrupt
void inc_itrc () {
  itrc++;
}
 
void setup() {
  pinMode(PIN_MOTOR, OUTPUT);
  pinMode(PIN_PWM, INPUT_PULLUP);

  // create PWM singal for motor
  analogWriteFrequency(PIN_MOTOR, MOTOR_PWM_HZ);
  analogWrite(PIN_MOTOR, motor_pulse_length);  // 0-255 aka 0-100% of duty cycle on
  
  Serial.begin(9600);  // open serial monitor in arduino IDE to read (set to same baud rate)
  
  attachInterrupt(digitalPinToInterrupt(PIN_PWM), inc_itrc, RISING);  // every time signal switches from LOW to HIGH, the rpm() function is called
  sei(); // enable interrupts

  then = micros();  // init
}
 
void loop () {
  if (itrc >= pulses_per_round) {
    const uint32_t now = micros();
    const uint32_t passed = now - then;
    ma_add(passed);
    uint32_t avg = ma_avg();
    
    
    //Serial.println(6e+7 / passed);  // turns-per-minute
    //Serial.println(1e+6 / passed);  // turns-per-second
    //Serial.println(1e+3 / passed);  // turns-per-millis
    //Serial.println(1.0 / passed);   // turns-per-micros

    Serial.print("measured:");
    Serial.print(passed);
    Serial.print(",");
    Serial.print("moving_avg:");
    Serial.println(avg);         // micros-per-turn
    
    then = now;
    itrc = 0;
  }
}
