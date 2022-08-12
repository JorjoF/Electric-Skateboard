#include <SoftwareServo.h> 
#include <RH_ASK.h>
#include <SPI.h>
#include <ESC.h>

#define LED_PIN (7)
#define BUZZER_PIN (6)
#define MAX_SPEED (2000)
#define MIN_SPEED (1300)



RH_ASK driver(2500, 16,14,10);

ESC myESC (9, MIN_SPEED, MAX_SPEED, 500);

int sensorVal[4] = {0};
int potval;
int curval;

const int MAXSPEED = 180;
const int CONSTRAIN = 100;
const int ACCELERATION = 1;
const int DECCELERATION = 2;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  driver.init();
  escServo.attach(9);
  curval=0;
  myESC.arm();  
  digitalWrite(LED_PIN, HIGH);  
  Serial.begin(9600);
  delay(5000);
  beep(1);

}

void loop() {
    receive();
    potval = sensorVal[1];

    while(curval<potval){
        receive();
        potval = sensorVal[1];
        curval = curval + ACCELERATION;
        curval = min(curval, MAXSPEED);
        esc(curval);
        Serial.println(curval);
        delay(50);
    }

    while(curval>potval){
      receive();
      potval = sensorVal[1];
 
      if(potval < 0){
        curval = curval - DECCELERATION;
        curval = max(curval, 0);
        Serial.println(curval);
        esc(curval);
        delay(50);
      }else{
        curval=curval - 1;
        curval = max(curval, 0);
        Serial.println(curval);
        esc(curval);
        delay(50);
      }
    }
    Serial.println(curval);
    esc(curval);
}

void receive(){
  uint8_t buflen = sizeof(sensorVal);
  driver.recv((uint8_t *)sensorVal, &buflen);
}

void esc(int curval){
  curval = map(curval, 0, MAXSPEED, MIN_SPEED, MAX_SPEED);
  curval = constrain(curval, 1000, 2000);
  myESC.speed(curval);
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
