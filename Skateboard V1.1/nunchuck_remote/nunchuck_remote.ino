#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define analog_x A9
#define analog_y A8
#define c 2
#define z 3

RF24 radio(19, 18);
const byte address[6] = "000001";

int sensorVal[4];


void setup() {
  pinMode(c, INPUT_PULLUP);
  pinMode(z, INPUT_PULLUP);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();

  Serial.begin(9600);
}
  
void loop() {
   sensorVal[0] = analogX(analog_x);
   sensorVal[1] = analogY(analog_y);
   sensorVal[2] = digitalRead(z);
   sensorVal[3] = digitalRead(c);

   radio.write(&sensorVal, sizeof(sensorVal));
   delay(50);
       
}
