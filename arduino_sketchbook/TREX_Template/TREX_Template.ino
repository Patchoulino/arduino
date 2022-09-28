/*
 * Servos
 * 5, 6, 7, 8, 12, 13
 * 
 * Encoders
 * 5, 6
 * 
 * DC Motor 1
 * 
 * 11 -   Vcc Gnd
 * 10 -   Cambio de giro
 * 9  -   !Enable BREAK
 * 
 * DC Motor 2
 * 
 * 3  -   Gnd Vcc
 * 2  -   Cambio de giro
 * 4  -   !Enable BRAKE
 */

//    Servos    //
#include <Servo.h> 

Servo S5;   int S5_pos = 0;
Servo S6;   int S6_pos = 45;
Servo S7;   int S7_pos = 90;
Servo S8;   int S8_pos = 90;
Servo S12;  int S12_pos = 135;
Servo S13;  int S13_pos = 180;

//    DC MOTORS   //
const int ML = 11;        const int MR = 3;
const int ML_dir = 10;    const int MR_dir = 2;   
const int ML_brk = 9;     const int MR_brk = 4;
int ML_spd = 0;           int MR_spd = 0;   

//    ACCELEROMETER   //
const int AccelPin_X = A0;  int Accel_X = 0;
const int AccelPin_Y = A1;  int Accel_Y = 0;
const int AccelPin_Z = A2;  int Accel_Z = 0;

//    VARIABLES   //
int i = 0;
int Byte;

void setup() {
  S5.attach(5);
  S6.attach(6);
  S7.attach(7);
  S8.attach(8);
  S12.attach(12);
  S13.attach(13);
  
  pinMode(ML, OUTPUT);
  pinMode(ML_dir, OUTPUT);
  pinMode(ML_brk, OUTPUT);
  digitalWrite(ML, LOW);
  digitalWrite(ML_dir, LOW);
  digitalWrite(ML_brk, LOW);
  
  pinMode(MR, OUTPUT);
  pinMode(MR_dir, OUTPUT);
  pinMode(MR_brk, OUTPUT);
  digitalWrite(MR, LOW);
  digitalWrite(MR_dir, LOW);
  digitalWrite(MR_brk, LOW);
  
  Serial.begin(9600);   
}

void loop() {

  if(i == 4)  i = 0;

  switch(i)
  {
    case 0:
      analogWrite(ML, 0);
      digitalWrite(MR, HIGH);
    break;
    case 1:
      analogWrite(ML, 85);
    break;
    case 2:
      analogWrite(ML, 170);
    break;
    case 3:
      analogWrite(ML, 255);
    break;
  }
  
  //Serial.println(i);
  i = i + 1;

  S5.write(S5_pos);
  S6.write(S6_pos);
  S7.write(S7_pos);
  S8.write(S8_pos);
  S12.write(S12_pos);
  S13.write(S13_pos);
  
  Accel_X = analogRead(AccelPin_X);
  Accel_Y = analogRead(AccelPin_Y);
  Accel_Z = analogRead(AccelPin_Z);
  /*  //  Accelerometer test
  Serial.print("||X:");
  Serial.print(Accel_X);
  Serial.print("||Y:");
  Serial.print(Accel_Y);
  Serial.print("||Z:");
  Serial.print(Accel_Z);
  Serial.print("||");
  */
  /*  // Bluetooth test
  if(Serial.available())
  {
    Byte = Serial.read();
    Serial.write(Byte);
  }*/
  
  delay(100);
}
