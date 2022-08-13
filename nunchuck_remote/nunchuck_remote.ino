#include <RH_ASK.h>
#include <SPI.h>

#define analog_x A2
#define analog_y A3
#define c 2
#define z 3


RH_ASK driver(2000,  16,  14, 10);

int sensorVal[4];


void setup() {
  pinMode(c, INPUT_PULLUP);
  pinMode(z, INPUT_PULLUP);

  driver.init();

  Serial.begin(9600);
}
  
void loop() {
   sensorVal[0] = analogX(analog_x);
   sensorVal[1] = analogY(analog_y);
   sensorVal[2] = digitalRead(z);
   sensorVal[3] = digitalRead(c);

   driver.send((uint8_t*)sensorVal, sizeof(sensorVal));
   
}
