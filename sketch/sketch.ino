// Libraries that we used:
#include <Wire.h>
#include "Adafruit_TCS34725.h" //https://github.com/adafruit/Adafruit_TCS34725/releases/tag/1.3.3

// LDR - Will
const int ldrPin = 9;
// Data
int brightness = 0;
bool ballPresent = false;

//Adafruit color sensor library constructor - Emil
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
// Data
byte gammatable[256]; // 

// Rods - Jacob
const int rodLeft = 7;
const int rodRight = 6;
// Data
int motLeft = 0; // # of 
int motRight = 0; // # of 
int rotLeft = 0; // # of 
int rotRight = 0; // # of 
int valLeft; // # of times the left rod had rotated
int valRight; // # of 

// Sorting solenoids
const int solenoidA = 15;
const int solenoidB = 14;
// Release solenoids
const int solenoidX = 16;
const int solenoidY = 10;

void setup() {

  // The LDR doesn't use pinMode because it's uses the built-in analog converter.
  // The color sensor also doesn't because it's over the I2C bus. 

  pinMode(rodLeft, INPUT);
  pinMode(rodRight, INPUT);

  pinMode(solenoidA, OUTPUT);
  pinMode(solenoidB, OUTPUT);
  pinMode(solenoidX, OUTPUT);
  pinMode(solenoidY, OUTPUT);

  // Starts the serial monitor for output data.
  Serial.begin(9600);
}

void loop() {
  
  brightness = analogRead(ldrPin);
  
  valLeft = digitalRead(rodLeft);
  valRight = digitalRead(rodRight);
  
  if(valLeft == HIGH){    // Counts how many times motor is detected
    motLeft = motLeft+1; // Tests to see if motor is detected      
  }
  if(motLeft == 2){       // Counts number of rotations motor makes, change number in if condition to number or steps motor has
    rotLeft = rotLeft + 1;
    motLeft = 0;  // Tests to see if rotation is counted  
  }
  
    if(valRight == HIGH){    // Counts how many times motor is detected
    motRight = motRight+1; // Tests to see if motor is detected      
  }
  if(motRight == 2){       // Counts number of rotations motor makes, change number in if condition to number or steps motor has
    rotRight = rotRight + 1;
    motRight = 0;  // Tests to see if rotation is counted  
  }
  
  // Color sense example sketch (https://github.com/adafruit/Adafruit_TCS34725/blob/master/examples/tcs34725/tcs34725.ino)
  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);
  // Output color valLeftues to Serial monitor
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  
  Serial.println("<- this is the red valLeftue");
  
}
