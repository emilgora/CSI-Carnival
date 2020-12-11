// Libraries that we used:
#include <Wire.h>
#include "Adafruit_TCS34725.h" //https://github.com/adafruit/Adafruit_TCS34725/releases/tag/1.3.3

// LDR - Will
const int ldrPin = 9;
// Data
int brightness = 0;  
const int triggerMax = 315; // Threshold for when the ball IS NOT present
const int triggerMin = 230; // Threshold for when the ball IS present
bool ballPresent = false; // For the first few seconds the game will assume that a ball isn't present.

// Adafruit color sensor library constructor - Emil 
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
// Data - Most of the integers used by the adafruit library are defined later in the sketch.
byte gammatable[256]; 

// Rods - Jacob
const int rodLeft = 7;
const int rodRight = 6;
// Data
int motLeft = 0; // # of times the left button has been pressed
int motRight = 0; // # of times the right button has been pressed
int rotLeft = 0; // # of times the left rod had rotated
int rotRight = 0; // # of times the right rod had rotated 
int valLeft; // Stores if the left button is high or low
int valRight; // Stores if the right button is high or low

// Ball counters
int whiteBallsPassed = 0;
int orangeBallsPassed = 0;

// Release solenoids
const int solenoidX = 16;
const int solenoidY = 10;
// Sorting solenoids
const int solenoidA = 15;
const int solenoidB = 14;

void setup() {

  // The LDR doesn't use pinMode because it uses the built-in analog converter.
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
  
  if(brightness > triggerMax){
    ballPresent = false;
  }
  
    if(brightness < triggerMin){
    ballPresent = true;
  }

  
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
  
  // Color sense example sketch (https://github.com/adafruit/Adafruit_TCS34725/blob/master/examples/tcs34725/tcs34725.ino
  // The adafruit library refers to the red value as "r" so I kept the integer name. -emil
  uint16_t r, g, b, c;
  tcs.getRawData(&r, &g, &b, &c);
  Serial.print("Red value: "); Serial.println(r, DEC);  // Outputs red color value to Serial monitor

    // Release balls logic:
    if(rotLeft == 50){
      digitalWrite(solenoidX, HIGH);
      delay(10000);
      digitalWrite(solenoidX, LOW);
    }

    if(rotRight == 50){
      digitalWrite(solenoidY, HIGH);
      delay(10000);
      digitalWrite(solenoidY, LOW);
    }

    // Sort balls logic:
    if(ballPresent == true && r > 4100){
      digitalWrite(solenoidA, HIGH);
      delay(1000);
      digitalWrite(solenoidA, LOW);
      whiteBallsPassed + 1;
    }
        if(ballPresent == true && r < 4100){
      digitalWrite(solenoidB, HIGH);
      delay(1000);
      digitalWrite(solenoidB, LOW);
      orangeBallsPassed + 1;
    }

    // Announce winner through serial monitor:
    if(whiteBallsPassed == 20){
    Serial.println("The left player has won!");
    }

    if(orangeBallsPassed == 20){
    Serial.println("The right player has won!");
    }
    // Potential improvement: write NodeJS script that listens to the arduino's COM port and uses an HTML + EJS page to show a winner/keep track of rotations.
      
    // At this point you can the game is over and you can press the reset button.
    
}
