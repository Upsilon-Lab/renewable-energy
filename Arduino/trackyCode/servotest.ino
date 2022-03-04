#include <Servo.h>
#include <math.h>
Servo botServo; // Servo that is at the base
Servo topServo; // Servo at the the top 

void setup() {
  botServo.attach(0);
  topServo.attach(1);
}
int theta = 45; // bottom angle
int phi = 45;   // Top angle

// Photoresistors
float pin0 = 0; // Top left
float pin1 = 0; // Top right
float pin2 = 0; // Bottom left
float pin3 = 0; // Bottom right

float inc = 0;
const int threshold = 1500;
float diff = 0;

void loop() {
  pin0 = ohmRead(0);
  pin1 = ohmRead(1);
  pin2 = ohmRead(2);
  pin3 = ohmRead(3);

  //top to bottom

  diff = (pin0 + pin1) - (pin2 + pin3);
  inc = calcInc(diff);
  
  if (abs(diff) < threshold ){}
  else if (diff > 0){
    theta = theta - inc;
    if (theta < 10){
      theta = 10;
    }
    topServo.write(theta);
  } else {
    theta = theta + inc;
    if ( theta > 90 ) {
      theta = 90;
    }
    topServo.write(theta);
  }
  
  
  pin0 = ohmRead(0);
  pin1 = ohmRead(1);
  pin2 = ohmRead(2);
  pin3 = ohmRead(3);
  //side to side

  diff = (pin0 + pin2) - (pin1 + pin3);
  inc = calcInc(diff);
  
  if (abs(diff) < threshold){}
  else if (diff > 0){
    phi = phi + inc;
    if (phi > 180){
      phi = 180;
    }
    botServo.write(phi);
  } else {
    phi = phi - inc;
      if (phi < 0){
      phi = 0;
    }
    botServo.write(phi);
  }  
  delay(90);
}

const int   Vin = 5;
const float rawToVolt = 5.0/1024.0;
const int   R1  = 10000;
// Reads the voltage from pin
// Returns Resistance value
// Returns 0 if unable to read
float ohmRead(int pin){
  int raw;
  raw = analogRead(pin);
  if (raw){
    float Vout = 0;
    float res  = 0;
    Vout = raw * rawToVolt;
    res = (Vout*R1)/(Vin - Vout);
    return res;
  }
  else {
    return 0;
  }
}

const int minInc = 0.5;
const int maxInc = 2;
float calcInc(float diff){
  inc = abs(diff)/(threshold);
  if (inc > maxInc){
    inc = maxInc;
  } else if (inc < minInc){
    inc = minInc;
  }
  return inc;
}
