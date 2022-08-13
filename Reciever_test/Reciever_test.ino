#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000, 16,14,10);

int sensorVal[4] = {0};


void setup() {
  if(driver.init()) ;
  Serial.begin(9600);
}

void loop() {
  uint8_t buflen = sizeof(sensorVal);
  driver.recv((uint8_t *)sensorVal, &buflen);
  Serial.println(sensorVal[2]);
}
