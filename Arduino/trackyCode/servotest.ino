#include<Servo.h>
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

const int increment = 1;
const int threshold = 1500;

void loop() {
  pin0 = ohmRead(0);
  pin1 = ohmRead(1);
  pin2 = ohmRead(2);
  pin3 = ohmRead(3);

  //top to bottom
  if (abs((pin0 + pin1) - (pin2 + pin3)) < threshold ){
    theta = theta;
  } 
  else if ((pin0 + pin1) > (pin2 + pin3)){
    theta = theta - increment;
  } else {
    theta = theta + increment;
  }
  if (theta < 10){
    theta = 10;
  } else if ( theta > 90 ) {
    theta = 90;
  }
  topServo.write(theta);
  
  pin0 = ohmRead(0);
  pin1 = ohmRead(1);
  pin2 = ohmRead(2);
  pin3 = ohmRead(3);
  //side to side
  if (abs((pin0 + pin2) - (pin1 + pin3)) < threshold){
    phi = phi;
  }
  else if ((pin0 + pin2) > (pin1 + pin3)){
    phi = phi + increment;
  } else {
    phi = phi - increment;
  }
  if (phi < 0){
    phi = 0;
  } else if (phi > 180){
    phi = 180;
  }
  
  botServo.write(phi);
  
  delay(30);
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
