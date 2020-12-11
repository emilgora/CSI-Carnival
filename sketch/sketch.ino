// Libraries that we used:
#include <Wire.h>
#include "Adafruit_TCS34725.h" //https://github.com/adafruit/Adafruit_TCS34725/releases/tag/1.3.3

// Super-duper secret controls (reset button is wired to the built-in RST)
const int startButton = 18;
bool gameState = false;

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
int mot = 0; //# of times arduino detects motor
int rot = 0; //# of rotations
int val;

// Sorting solenoids
const int solenoidA = 15;
const int solenoidB = 14;
// Release solenoids
const int solenoidX = 16;
const int solenoidY = 10;

void setup() {
  pinMode(startButton, INPUT);

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
  
  val = digitalRead(rodLeft);
  if(val == HIGH){    //counts how many times motor is detected
    mot = mot+1;
                      //tests to see if motor is detected
  }
  if(mot == 4){       //counts number of rotations motor makes, change number in if condition to number or steps motor has
    rot = rot + 1;
    mot = 0;
                      //tests to see if rotation is counted  
  }
  
  
  
  // Color sense example sketch (https://github.com/adafruit/Adafruit_TCS34725/blob/master/examples/tcs34725/tcs34725.ino)
  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);
  // Output color values to Serial monitor
  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  

  

  Serial.print(" ");
  Serial.println("<- this is the red value");
  
}
