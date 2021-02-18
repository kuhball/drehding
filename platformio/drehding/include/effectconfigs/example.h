
/*
 * effectcfg_*.h - Configuration of the LEDs and their effects.
 * 
 * Example effect configuration file with explanations.
*/
#ifndef EffectCfg_h
#define EffectCfg_h

#include "config.h"
#include "Led.h"
#include "EffectOff.h"
#include "EffectStationary.h"
#include "EffectSequence.h"
#include "EffectRotation.h"

// effect configuration
#define N_EFFECTS 7  // number of effects for each LED; all LEDs must have the same number of effects; effects are defined below

// init led objects (do not change)
Led led1(PIN_LED1, true);
Led led2(PIN_LED2, true);
Led led3(PIN_LED3, true);

// EFFECT DEFINITIONS (LED1-LED3)
// By pushing the rotary encoder button, one can iterate through the effect.
// A number of Effect* classes are provided to create LED effects.
// By setting them for each of the three LEDs and combining them suitably, combined effects are created.
//
// NOTE: the valid values for the flash positions depend on HALL_ROT_ANGLE_RES aka 0<=position<HALL_ROT_ANGLE_RES

// effect 1: all three leds lights at the same position, creating a single stationary object
EffectStationary led1_effect1 = EffectStationary(led1, 0);
EffectStationary led2_effect1 = EffectStationary(led2, 0);
EffectStationary led3_effect1 = EffectStationary(led3, 0);

// effect 2: all three leds lights at slightly different positions, creating three stationary objects, offsetted by 30°
EffectStationary led1_effect2 = EffectStationary(led1, 0);
EffectStationary led2_effect2 = EffectStationary(led2, 30);
EffectStationary led3_effect2 = EffectStationary(led3, 60);

// effect 3: one LED is on, creating a slowly rotating object
EffectRotation led1_effect3 = EffectRotation(led1, 100, HALL_ROT_ANGLE_RES);
EffectOff led2_effect3 = EffectOff(led2);
EffectOff led3_effect3 = EffectOff(led3);

// effect 4: two LEDs are on, rotating in opposite directions
EffectRotation led1_effect4 = EffectRotation(led1, 100, HALL_ROT_ANGLE_RES);
EffectRotation led2_effect4 = EffectRotation(led2, 100, HALL_ROT_ANGLE_RES, true);
EffectOff led3_effect4 = EffectOff(led3);

// effect 5: one LED is on, switching between showing the front and the backside of the object
// Note that this effect can only be observed if you mark the sides of symmetric objects
EffectSequence led1_effect5 = EffectSequence(led1, (uint16_t []) {0, 180}, (uint32_t []) {1000, 1000}, 2);
EffectOff led2_effect5 = EffectOff(led2);
EffectOff led3_effect5 = EffectOff(led3);

// effect 6: two LEDs are on, one switching between showing the front and the backside, the other between the front and a 90° turned version
// Note that this effect can only be observed if you mark the sides of symmetric objects
EffectSequence led1_effect6 = EffectSequence(led1, (uint16_t []) {0, 180}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led2_effect6 = EffectSequence(led2, (uint16_t []) {0, 90}, (uint32_t []) {500, 500}, 2);
EffectOff led3_effect6 = EffectOff(led3);

// effect 7: one LED is on, switching fast between various positions
// Note that this effect can only be observed if you mark the sides of symmetric objects
EffectSequence led1_effect7 = EffectSequence(led1, (uint16_t []) {0, 50, 270, 30, 180, 210, 350, 70}, (uint32_t []) {100, 200, 300, 200, 500, 100, 100, 800}, 8);
EffectOff led2_effect7 = EffectOff(led2);
EffectOff led3_effect7 = EffectOff(led3);


// init effects (adapt to include all effects defined above)
Effect* led1_effects[N_EFFECTS] = {
  &led1_effect1,
  &led1_effect2,
  &led1_effect3,
  &led1_effect4,
  &led1_effect5,
  &led1_effect6,
  &led1_effect7
};

Effect* led2_effects[N_EFFECTS] = {
  &led2_effect1,
  &led2_effect2,
  &led2_effect3,
  &led2_effect4,
  &led2_effect5,
  &led2_effect6,
  &led2_effect7
};

Effect* led3_effects[N_EFFECTS] = {
  &led3_effect1,
  &led3_effect2,
  &led3_effect3,
  &led3_effect4,
  &led3_effect5,
  &led3_effect6,
  &led3_effect7
};

#endif