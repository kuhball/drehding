
/*
 * effectcfg_*.h - Configuration of the LEDs and their effects.
 * 
 * Playground configuration for testing and development.
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
#define N_EFFECTS 2  // number of effects for each LED; all LEDs must have the same number of effects

// init led objects (do not change)
Led led1(PIN_LED1, true);
Led led2(PIN_LED2, true);
Led led3(PIN_LED3, true);

// effect definitions (LED1-LED3)
// NOTE: the valid values for the flash positions depend on HALL_ROT_ANGLE_RES aka 0<=position<HALL_ROT_ANGLE_RES
EffectStationary led1_effect1 = EffectStationary(led1, 0);
EffectRotation led1_effect2 = EffectRotation(led1, 100, HALL_ROT_ANGLE_RES);


EffectStationary led2_effect1 = EffectStationary(led2, 0);
EffectOff led2_effect2 = EffectOff(led2);


EffectStationary led3_effect1 = EffectStationary(led3, 0);
EffectOff led3_effect2 = EffectOff(led3);


// init effects
Effect* led1_effects[N_EFFECTS] = {
  &led1_effect1,
  &led1_effect2
};

Effect* led2_effects[N_EFFECTS] = {
  &led2_effect1,
  &led2_effect2
};

Effect* led3_effects[N_EFFECTS] = {
  &led3_effect1,
  &led3_effect2
};

#endif