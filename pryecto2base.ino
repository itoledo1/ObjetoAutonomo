/****************************************************************************************************************************
  basic_pwm.ino
  For RP2040 boards
  Written by Dr. Benjamin Bird

  A basic example to get you up and running.

  Library by Khoi Hoang https://github.com/khoih-prog/RP2040_PWM
  Licensed under MIT license

  The RP2040 PWM block has 8 identical slices. Each slice can drive two PWM output signals, or measure the frequency
  or duty cycle of an input signal. This gives a total of up to 16 controllable PWM outputs. All 30 GPIO pins can be driven
  by the PWM block
*****************************************************************************************************************************/

#define _PWM_LOGLEVEL_        3
#include "RP2040_PWM.h"

//creates pwm instance
RP2040_PWM* PWM_Instance;
float freq1;
float freq2;
float freq3;
float freq4;
float freq5;
float tonos[4];
float vol;
int pin = 0;
int i = 0;
#define pinToUse     pin 


void setup()
{
  Serial.begin(115200);
  PWM_Instance = new RP2040_PWM(pinToUse, 20000, 0);
}

void loop()
{
  freq1 = analogRead(A0)+400; //La frecuencia depende del primer fotosensor.
  freq2 = analogRead(A1)*5; //La frecuencia depende del segundo y tercer fotosensor.
  freq3 = analogRead(A2) + 200;
  freq4 = analogRead(A1)/4;
  freq5 = analogRead(A2)*2;
  tonos[0]=freq1;
  tonos[1]=freq2;
  tonos[2]=freq3;
  tonos[3]=freq4;
  tonos[4]=freq5;
  vol = map(analogRead(A2),0,1024,5,20); // El volumen dependerá del segundo fotosensor.
  Serial.println(i);
  Serial.println(tonos[i]);
  
  if (analogRead(A2)<400){
    pin=1;
  }
  else {
    pin = 0;
  }
  PWM_Instance->setPWM(pin, tonos[i], vol);
  delay(analogRead(A1)/10);
  PWM_Instance->setPWM(pin, tonos[i], 0);
  delay(analogRead(A0)/10);
  i++;

  if (i>4){
    i=0;
  }
}
