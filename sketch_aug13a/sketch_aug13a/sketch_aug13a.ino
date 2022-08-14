#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define y A8
#define x A9




void setup() {
  Serial.begin(9600);

}

void loop() {
 Serial.println(analogRead(x));

}
