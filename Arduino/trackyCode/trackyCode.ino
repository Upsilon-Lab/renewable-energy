#include <Servo.h>
#include <EEPROM.h>
#include <math.h>
Servo botServo; // Servo that is at the base
Servo topServo; // Servo at the the top 

void setup() {
  botServo.attach(0);
  topServo.attach(1);
  //Serial.begin(9600);
}
// bottom angle
double theta = EEPROM.read(0);
// Top angle
double phi = EEPROM.read(1);



// Photoresistors
double pin0 = 0; // Top left
double pin1 = 0; // Top right
double pin2 = 0; // Bottom left
double pin3 = 0; // Bottom right
double inc = 0;
const int threshold = 1500;
double diffTD = 0;
double diffLR = 0;

int run_ms = 410; //Do not set this lower than ~50
long prev_ms = 0;
void loop() {
  if (millis()-prev_ms >= run_ms){

  pin0 = ohmRead(0);
  pin1 = ohmRead(1);
  pin2 = ohmRead(2);
  pin3 = ohmRead(3);
  
  diffTD = (pin0 + pin1) - (pin2 + pin3);
  diffLR = (pin0 + pin2) - (pin1 + pin3);
  if (abs(diffTD) > abs(diffLR) && abs(diffTD) > threshold){
    // Top and down code
    if (diffTD > 0){
      inc = calcInc(pin0+pin1, pin2+pin3);
      theta = theta - inc;
      if (theta < 10){
        theta = 10;
      }
      topServo.write(theta);
    } else {
      inc = calcInc(pin2+pin3, pin0+pin1);
      theta = theta + inc;
      if ( theta > 90 ) {
        theta = 90;
      }
      topServo.write(theta);
    }
  } else if (abs(diffLR) > threshold) {
    //side to side code
    if (diffLR > 0){
      inc = calcInc(pin0+pin2, pin1+pin3);
      phi = phi + inc;
      if (phi > 180){
        phi = 180;
      }
      botServo.write(phi);
    } else {
      inc = calcInc(pin1+pin3, pin0+pin2);
      phi = phi - inc;
      if (phi < 0){
        phi = 0;
      }
      botServo.write(phi);
    }
  }
  EEPROM.put(0, (int)theta);
  EEPROM.put(1, (int)phi);
  
  prev_ms = millis();
  }
}

const int   Vin = 5;
const double rawToVolt = 5.0/1024.0;
const int   R1  = 10000;
// Reads the voltage from pin
// Returns Resistance value
// Returns 0 if unable to read
double ohmRead(int pin){
  int raw;
  raw = analogRead(pin);
  if (raw){
    double Vout = 0;
    double res  = 0;
    Vout = raw * rawToVolt;
    res = (Vout*R1)/(Vin - Vout);
    return res;
  }
  else {
    return 0;
  }
}

const float tweakValue = 2; //Make sure that tracky doesn't fly away
double prev_inc = 0;
// Calculates the degrees to move based on arctan of the two directions.

double calcInc(float largerRead, float smallerRead){
  inc = 180/(tweakValue*3.14159) * atan2(largerRead, smallerRead);
  if (abs(prev_inc - inc) < 1){
    inc = inc / 5;
  }
  if (inc < 0.1){
    inc = 0;
  }
  prev_inc = inc;
  return inc;
}
