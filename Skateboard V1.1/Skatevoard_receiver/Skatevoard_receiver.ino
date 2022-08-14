#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define LED_PIN (10)
#define go (6)
#define slow (5)

RF24 radio(18, 19);
const byte address[6] = "000001";

int sensorVal[4] = {0};
int potval;
int curval;
int slowval;

const int MAXSPEED = 255;
const int ACCELERATION = 5;
const int DECCELERATION = 7;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(go, OUTPUT);
  pinMode(slow, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  curval=0;
  Serial.begin(9600);
}

void loop() {
     while(sensorVal[2] == 0){
      radio.read(&sensorVal, sizeof(sensorVal));
      potval = sensorVal[1];
  
      while(curval<potval){
          radio.read(&sensorVal, sizeof(sensorVal));
          potval = sensorVal[1];
          curval = curval + ACCELERATION;
          curval = min(curval, MAXSPEED);
          analogWrite(go,curval);
          delay(50);
      }
  
      while(curval>potval){
        radio.read(&sensorVal, sizeof(sensorVal));
        potval = sensorVal[1];
   
        if(potval < 0){
          curval = curval - DECCELERATION;
          curval = min(curval, MAXSPEED);
          analogWrite(go,curval);
          delay(50);
        }else{
          curval = curval - ACCELERATION;
          curval = min(curval, MAXSPEED);
          analogWrite(go,curval);
          delay(50);
        }
      }
      analogWrite(go,curval);  
    }
    potval = 0;
    while(curval>potval){
      curval = curval - DECCELERATION;
      curval = min(curval, MAXSPEED);
      analogWrite(go,curval);
      delay(50);
    }
    analogWrite(go,curval);
}
