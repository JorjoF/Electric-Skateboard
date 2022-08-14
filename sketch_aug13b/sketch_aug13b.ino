#include <SPI.h>
#include "printf.h"
#include "RF24.h"

RF24 radio(18, 19);
const byte address[6] = "000001";
int sensorVal[4];

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  Serial.begin(9600);

}

void loop() {
  if(radio.available()){
    radio.read(&sensorVal, sizeof(sensorVal));
    Serial.println(sensorVal[1]);
  }

}
