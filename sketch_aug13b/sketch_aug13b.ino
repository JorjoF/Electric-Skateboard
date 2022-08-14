#include <SPI.h>
#include "printf.h"
#include "RF24.h"

RF24 radio(18, 19);
const byte address[6] = "00001";

int sensorVal[4];
int potval;
int button;

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  Serial.begin(9600);

}

void loop() {
  receive();
  Serial.println(potval);
  while(button == 0){
    receive();
    Serial.println(potval);
  }
  delay(50);
}

void receive(){
  radio.read(&sensorVal, sizeof(sensorVal));
  button = sensorVal[2];
  potval = sensorVal[1];
}
