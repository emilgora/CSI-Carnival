#include <Arduino.h>

int output = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(output);  
  delay(50);
}
