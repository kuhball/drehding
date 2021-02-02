
#include "RotaryEncoder.h"

RotaryEncoder rotary(10, 11, 12);

void setup()
{
 Serial.begin(9600);
 
 rotary.minimum(0);
 rotary.maximum(100);
 rotary.position(20);
}


void loop()
{
 if(rotary.pressed())
 {
   Serial.print("Sensibility: ");
   Serial.print(rotary.position());
   Serial.print("%\n");
   delay(200);
 }
}
