#include <Wire.h>
#include "Adafruit_TCS34725.h" //https://github.com/adafruit/Adafruit_TCS34725/releases/tag/1.3.3

// Sorting solenoids pins
const int solenoidA = 1;
const int solenoidB = 1;

// Release solenoids pins
const int solenoidX = 1;
const int solenoidY = 1;

// Ultrasonic pins
const int trigPin = 9;
const int echoPin = 8;
// Ultrasonic data
float duration, distance; 

//Adafruit color sensor library constructor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
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

  // Ultrasonic activation (https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Ultrasonic data processing
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

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
  
}
