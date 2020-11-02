#include <Wire.h>
#include "Adafruit_TCS34725.h" //https://github.com/adafruit/Adafruit_TCS34725/releases/tag/1.3.3

#define redpin 3
#define greenpin 5
#define bluepin 6

//Adafruit library configuration
#define commonAnode true 
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

byte gammatable[256]; // 

String foo = "Bar";

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(foo);
}
