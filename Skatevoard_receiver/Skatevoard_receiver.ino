#include <SoftwareServo.h> 
#include <RH_ASK.h>
#include <SPI.h>



RH_ASK driver(2500, 16,14,10);
Adafruit_SoftServo escServo;

int sensorVal[4] = {0};
int potval;
int curval;

const int MAXSPEED = 180;
const int ACCELERATION = 1;
const int DECCELERATION = 2;

void setup() {
  driver.init();
  escServo.attach(9);
  curval=0;
  Serial.begin(9600);

}

void loop() {
    receive();
    potval = sensorVal[1];

    while(curval<potval){
        receive();
        potval = sensorVal[1];
        curval = curval + ACCELERATION;
        curval = min(curval, MAXSPEED);
        escServo.write(curval);
        delay(50);
    }

    while(curval>potval){
      receive();
      potval = sensorVal[1];
 
      if(potval < 0){
        curval = curval - DECCELERATION;
        curval = max(curval, 0);
         escServo.write(curval);
        delay(50);
      }else{
        curval=curval - 1;
        curval = max(curval, 0);
         escServo.write(curval);
        delay(50);
      }
        
    }
     escServo.write(curval);
}

void receive(){
  uint8_t buflen = sizeof(sensorVal);
  driver.recv((uint8_t *)sensorVal, &buflen);
}
