
/*
 * effectcfg_*.h - Configuration of the LEDs and their effects.
 * 
 * Defines a list of seventeen simple effects over three LEDs.
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
#define N_EFFECTS 17  // number of effects for each LED; all LEDs must have the same number of effects

// init led objects (do not change)
Led led1(PIN_LED1, true);
Led led2(PIN_LED2, true);
Led led3(PIN_LED3, true);

// effect definitions (LED1-LED3)
// NOTE: the valid values for the flash positions depend on HALL_ROT_ANGLE_RES aka 0<=position<HALL_ROT_ANGLE_RES
EffectStationary led1_effect1 = EffectStationary(led1, 0);
EffectStationary led1_effect2 = led1_effect1;
EffectStationary led1_effect3 = led1_effect1;
EffectStationary led1_effect4 = led1_effect1;
EffectSequence led1_effect5 = EffectSequence(led1, (uint16_t []) {0, 180}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led1_effect6 = EffectSequence(led1, (uint16_t []) {0, 90}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led1_effect7 = EffectSequence(led1, (uint16_t []) {0, 45}, (uint32_t []) {1000, 1000}, 2);
EffectRotation led1_effect8 = EffectRotation(led1, 100, HALL_ROT_ANGLE_RES);
EffectRotation led1_effect9 = led1_effect8;
EffectRotation led1_effect10 = led1_effect8;
EffectRotation led1_effect11 = led1_effect8;
EffectRotation led1_effect12 = led1_effect8;
EffectRotation led1_effect13 = led1_effect8;
EffectRotation led1_effect14 = led1_effect8;
EffectStationary led1_effect15 = led1_effect1;
EffectSequence led1_effect16 = EffectSequence(led1, (uint16_t []) {0, 10}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led1_effect17 = EffectSequence(led1, (uint16_t []) {0, 10, 20, 30, 40, 50, 60, 70, 80}, (uint32_t []) {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000}, 9);

EffectStationary led2_effect1 = EffectStationary(led2, 0);
EffectStationary led2_effect2 = led2_effect1;
EffectStationary led2_effect3 = EffectStationary(led2, 30);
EffectOff led2_effect4 = EffectOff(led2);
EffectOff led2_effect5 = led2_effect4;
EffectOff led2_effect6 = led2_effect4;
EffectOff led2_effect7 = led2_effect4;
EffectOff led2_effect8 = led2_effect4;
EffectStationary led2_effect9 = led2_effect1;
EffectSequence led2_effect10 = EffectSequence(led2, (uint16_t []) {0, 180}, (uint32_t []) {1000, 1000}, 2);
EffectRotation led2_effect11 = EffectRotation(led2, 100, HALL_ROT_ANGLE_RES, true);
EffectRotation led2_effect12 = led2_effect11;
EffectRotation led2_effect13 = led2_effect11;
EffectRotation led2_effect14 = led2_effect11;
EffectStationary led2_effect15 = led2_effect3;
EffectSequence led2_effect16 = EffectSequence(led2, (uint16_t []) {30, 40}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led2_effect17 = EffectSequence(led2, (uint16_t []) {30, 40, 50, 60, 70, 80, 90, 100, 110}, (uint32_t []) {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000}, 9);

EffectStationary led3_effect1 = EffectStationary(led3, 0);
EffectStationary led3_effect2 = EffectStationary(led3, 45);
EffectStationary led3_effect3 = EffectStationary(led3, 60);
EffectOff led3_effect4 = EffectOff(led3);
EffectOff led3_effect5 = led3_effect4;
EffectOff led3_effect6 = led3_effect4;
EffectOff led3_effect7 = led3_effect4;
EffectOff led3_effect8 = led3_effect4;
EffectOff led3_effect9 = led3_effect4;
EffectOff led3_effect10 = led3_effect4;
EffectOff led3_effect11 = led3_effect4;
EffectStationary led3_effect12 = led3_effect1;
EffectSequence led3_effect13 = EffectSequence(led3, (uint16_t []) {0, 180}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led3_effect14 = EffectSequence(led3, (uint16_t []) {0, 45}, (uint32_t []) {1000, 1000}, 2);
EffectStationary led3_effect15 = led3_effect3;
EffectSequence led3_effect16 = EffectSequence(led3, (uint16_t []) {60, 70}, (uint32_t []) {1000, 1000}, 2);
EffectSequence led3_effect17 = EffectSequence(led3, (uint16_t []) {60, 70, 80, 90, 100, 110, 120, 130, 140}, (uint32_t []) {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000}, 9);

// init effects
Effect* led1_effects[N_EFFECTS] = {
  &led1_effect1,
  &led1_effect2,
  &led1_effect3,
  &led1_effect4,
  &led1_effect5,
  &led1_effect6,
  &led1_effect7,
  &led1_effect8,
  &led1_effect9,
  &led1_effect10,
  &led1_effect11,
  &led1_effect12,
  &led1_effect13,
  &led1_effect14,
  &led1_effect15,
  &led1_effect16,
  &led1_effect17
};

Effect* led2_effects[N_EFFECTS] = {
  &led2_effect1,
  &led2_effect2,
  &led2_effect3,
  &led2_effect4,
  &led2_effect5,
  &led2_effect6,
  &led2_effect7,
  &led2_effect8,
  &led2_effect9,
  &led2_effect10,
  &led2_effect11,
  &led2_effect12,
  &led2_effect13,
  &led2_effect14,
  &led2_effect15,
  &led2_effect16,
  &led2_effect17
};

Effect* led3_effects[N_EFFECTS] = {
  &led3_effect1,
  &led3_effect2,
  &led3_effect3,
  &led3_effect4,
  &led3_effect5,
  &led3_effect6,
  &led3_effect7,
  &led3_effect8,
  &led3_effect9,
  &led3_effect10,
  &led3_effect11,
  &led3_effect12,
  &led3_effect13,
  &led3_effect14,
  &led3_effect15,
  &led3_effect16,
  &led3_effect17
};

#endif