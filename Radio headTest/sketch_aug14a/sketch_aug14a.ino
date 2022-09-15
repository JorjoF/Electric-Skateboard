#include <SPI.h>
#include "printf.h"
#include "RF24.h"

RF24 radio(18, 19);
const byte address[6] = "00001";

int sensorVal[3];
int potval = 0;
int negval = 0;
int curval = 0;
int slowval = 0;

const int MAXSPEED = 255;
const int ACCELERATION = 5;
const int DECCELERATION = 7;

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  curval=0;
  slowval = 0;
  Serial.begin(9600);

}

void loop() {
  if(radio.available()){
    radio.read(&sensorVal, sizeof(sensorVal));
    
    while(sensorVal[1] == 0){
      radio.read(&sensorVal, sizeof(sensorVal));
      potval = sensorVal[0];

          while(curval<potval){
            slowval = 0;
            radio.read(&sensorVal, sizeof(sensorVal));
            potval = sensorVal[0];
            curval = curval + ACCELERATION;
            curval = min(curval, MAXSPEED);
            sPrint(curval, slowval);
            delay(50);
          }
        
          while(curval>potval){
            radio.read(&sensorVal, sizeof(sensorVal));
            potval = sensorVal[0];

            if(potval < 0){
              curval = 0;
              negval = -potval;
              slowval = slowval + ACCELERATION;
              slowval = min(slowval, negval);
            }else{
              curval = curval - ACCELERATION;
              curval = max(curval, 0);   
            }   
            sPrint(curval,slowval);
            delay(50);
            
          }
          sPrint(curval, slowval);
          delay(50);
      
    }
    
  slowval = 0;
  potval = 0;
  while(curval>potval){
    curval=curval - ACCELERATION;
    curval = max(curval, 0);
    sPrint(curval, slowval);
    delay(50);
  }
  sPrint(curval, slowval);
  delay(50);
  }
}

void sPrint(int a, int b){
  analogWrite(5, a);
  analogWrite(6, b);
}
