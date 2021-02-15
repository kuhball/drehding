/*
  Effect.h - Abstract effect class of DrehDings project.
*/
#ifndef Effect_h
#define Effect_h

#include "Arduino.h"

#include "Led.h"

/**
 * Abstract class representing a stroposcopic effect assigned to a single LED.
 * 
 * Use as baseclass for all effect classes.
 */
class Effect {
  public:
    Effect(Led &led): led(led) {};
    Effect(Led &&) = delete;

    /**
     * Call when effect starts.
     */
    virtual void init() = 0;

    /**
     * Call each loop.
     */
    virtual void update() = 0;

  protected:
    Led &led;
};

#endif
