#include <RH_ASK.h>
#include <SPI.h>

#define LED_PIN (7)
#define BUZZER_PIN (6)


RH_ASK driver(2000, 16,14,10);

int sensorVal[4] = {0};
int potval;
int curval;

const int MAXSPEED = 255;
const int ACCELERATION = 5;
const int DECCELERATION = 7;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(3, OUTPUT);
  if(driver.init()) ;
  curval=0;
  Serial.begin(9600);
}

void loop() {
  receive();
  while(sensorVal[2] == 0){
      receive();
      potval = sensorVal[1];
  
      while(curval<potval){
          receive();
          potval = sensorVal[1];
          curval = curval + ACCELERATION;
          curval = min(curval, MAXSPEED);
          analogWrite(3,curval);
          delay(50);
      }
  
      while(curval>potval){
        receive();
        potval = sensorVal[1];
   
        if(potval < 0){
          curval = curval - DECCELERATION;
          curval = max(curval, 0);
          analogWrite(3,curval);
          delay(50);
        }else{
          curval=curval - ACCELERATION;
          curval = max(curval, 0);
          analogWrite(3,curval);
          delay(50);
        }
      }
      analogWrite(3,curval);
  }
  potval = 0;
  while(curval>potval){
    curval=curval - DECCELERATION;
    curval = max(curval, 0);
    analogWrite(3,curval); 
    delay(50);
  }
  analogWrite(3,curval);  
}
  

void receive(){
  uint8_t buflen = sizeof(sensorVal);
  driver.recv((uint8_t *)sensorVal, &buflen);  
  
}


void beep(int a){
  switch(a){
    case 1:
      analogWrite(BUZZER_PIN,200);
      delay(250);
      analogWrite(BUZZER_PIN,0);
      delay(250);
      analogWrite(BUZZER_PIN,255);
      delay(250);
      analogWrite(BUZZER_PIN,0);
      break;
  }
}
