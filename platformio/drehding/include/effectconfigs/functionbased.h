
/*
 * effectcfg_*.h - Configuration of the LEDs and their effects.
 * 
 * Example file to show off the function based effects.
*/
#ifndef EffectCfg_h
#define EffectCfg_h

#include "config.h"
#include "Led.h"
#include "EffectOff.h"
#include "EffectStationary.h"
#include "EffectSequence.h"
#include "EffectRotation.h"
#include "EffectSinusoidal.h"
#include "EffectWave.h"
#include "EffectMultiSin.h"

// effect configuration
#define N_EFFECTS 4  // number of effects for each LED; all LEDs must have the same number of effects

// init led objects (do not change)
Led led1(PIN_LED1, true);
Led led2(PIN_LED2, true);
Led led3(PIN_LED3, true);

// effect definitions (LED1-LED3)
// NOTE: the valid values for the flash positions depend on HALL_ROT_ANGLE_RES aka 0<=position<HALL_ROT_ANGLE_RES
EffectSinusoidal led1_effect1 = EffectSinusoidal(led1, 10000, HALL_ROT_ANGLE_RES);
EffectWave led1_effect2 = EffectWave(led1, 10000, HALL_ROT_ANGLE_RES);
EffectMultiSin led1_effect3 = EffectMultiSin(led1, 20000, HALL_ROT_ANGLE_RES);
EffectMultiSin led1_effect4 = EffectMultiSin(led1, 20000, HALL_ROT_ANGLE_RES);


EffectOff led2_effect1 = EffectOff(led2);
EffectOff led2_effect2 = EffectOff(led2);
EffectOff led2_effect3 = EffectOff(led2);
EffectWave led2_effect4 = EffectWave(led2, 10000, HALL_ROT_ANGLE_RES);


EffectOff led3_effect1 = EffectOff(led3);
EffectOff led3_effect2 = EffectOff(led3);
EffectOff led3_effect3 = EffectOff(led3);
EffectSinusoidal led3_effect4 = EffectSinusoidal(led3, 15000, HALL_ROT_ANGLE_RES);


// init effects
Effect* led1_effects[N_EFFECTS] = {
  &led1_effect1,
  &led1_effect2,
  &led1_effect3,
  &led1_effect4
};

Effect* led2_effects[N_EFFECTS] = {
  &led2_effect1,
  &led2_effect2,
  &led2_effect3,
  &led2_effect4
};

Effect* led3_effects[N_EFFECTS] = {
  &led3_effect1,
  &led3_effect2,
  &led3_effect3,
  &led3_effect4
};

#endif