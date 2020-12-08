// Libraries included
#include <Wire.h>
#include "Adafruit_TCS34725.h" //https://github.com/adafruit/Adafruit_TCS34725/releases/tag/1.3.3

// Sorting solenoids pins
const int solenoidA = 1;
const int solenoidB = 1;

// Release solenoids pins
const int solenoidX = 1;
const int solenoidY = 1;

// Ultrasonic pins
#define echoPin 8
#define trigPin 9
// Ultrasonic processed data
float duration, distance; 
bool ballPresent = true;

//Adafruit color sensor library constructor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
byte gammatable[256]; // 


const int motor = 9;
int mot = 0; //# of times arduino detects motor
int rot = 0; //# of rotations
int val;
const int foo = 8;//connect to red led or rgb pin
const int bar = 7;//connect to other led or rgb pin

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  pinMode(motor, INPUT);
  pinMode(foo, OUTPUT);
  pinMode(bar, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  Serial.println(foo);

  // Ultrasonic example sketch (https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380)
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


    val = digitalRead(motor);
  if(val == HIGH){    //counts how many times motor is detected
    mot = mot+1;
                      //tests to see if motor is detected
    digitalWrite(foo,HIGH);
    delay(1000);
    digitalWrite(foo,LOW);
  }
  if(mot == 4){       //counts number of rotations motor makes, change number in if condition to number or steps motor has
    rot = rot + 1;
    mot = 0;
                      //tests to see if rotation is counted  
    digitalWrite(bar,HIGH);
    delay(1000);
    digitalWrite(bar,LOW);
  }

  /*
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
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");
  */
}
