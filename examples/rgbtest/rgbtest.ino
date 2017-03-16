#include "rgbled.h"


rgbled my_rgbled(9,10,11, 'c');

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  my_rgbled.out(100,0,0);  // red
  delay(2000);
  my_rgbled.out(0,100,0);  // green
  delay(2000);
  my_rgbled.out(0,0,100);  // blue
  delay(2000);
  my_rgbled.out(0,0,0);  // off
  my_rgbled.preset(1);
  delay(2000);
  my_rgbled.out(0,0,0);  // off
  my_rgbled.preset(2);
  delay(2000);
  my_rgbled.out(0,0,0);  // off
  my_rgbled.preset(3);
  delay(2000);
  my_rgbled.out(0,0,0);  // off
} 
