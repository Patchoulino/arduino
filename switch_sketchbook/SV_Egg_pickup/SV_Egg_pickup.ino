/*
 * SV Egg picking 
 * every 4min
 * 20 sec of turbo A
*/

const int IN[] = {A0, 7, 2};
const int LENGTH = 2;
const int T = 50;

const int Y = 0;
const int B = 1;
const int A = 2;
const int X = 3;
const int L = 4;
const int R = 5;
const int ZL = 6;
const int ZR = 7;
const int MINUS = 8;
const int PLUS = 9;
const int LSTICK = 10;
const int RSTICK = 11;
const int HOME = 12;
const int CAPTURE = 13;
const int UP = 0;
const int RIGHT = 90;
const int DOWN = 180;
const int LEFT = 270;
const int RELEASE = -1;

//https://github.com/HackerLoop/Arduino-JoyCon-Library-for-Nintendo-Switch/blob/master/examples/SwitchJoystickTest/SwitchJoystickTest.ino
//C:\Users\USER\AppData\Local\Arduino15\packages\arduino\hardware\avr\current_version\boards.txt
#include "SwitchJoystick.h"

// Create Joystick
SwitchJoystick_ Joystick;

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
const bool testAutoSendMode = true;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  for(int i = 0; i <= LENGTH; i++)
  {
    pinMode(IN[i], INPUT);
  }
  
  if (testAutoSendMode)
  {
    Joystick.begin();
  }
  else
  {
    Joystick.begin(false);
  }

  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
  Joystick.setZAxis(128);
  Joystick.setRzAxis(128);
  Joystick.sendState();

  // Pairing controller
  for (int i = 0; i <= 2; i++){
    button(X, T);  // X does not do anything while on picnic
  }

}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() { // Look at the picnic and wait 
  for (int c = 0; c < 7; c++){  // 30min/7 = 4min 17.14sec
    delay(4 * 60UL * 1000); // wait 4min
    for (int i = 0; i <= (16000/T/2); i++){ // spam A for 16 sec
      button(A, T);
    }
    for (int i = 0; i <= (1000/T/2); i++){ // spam B for 1 sec
      button(B, T);
    }
  }
  while(true){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
}

void button(int btn, int timing) {
  for(int i = 0; i <= LENGTH; i++)  if(!digitalRead(IN[i]))  resetFunc();
  Joystick.pressButton(btn);
  delay(timing);
  Joystick.releaseButton(btn);
  delay(timing);
}

void dpad(int btn, int timing) {
  for(int i = 0; i <= LENGTH; i++)  if(!digitalRead(IN[i]))  resetFunc();
  Joystick.setHatSwitch(btn);
  delay(timing);
  Joystick.setHatSwitch(RELEASE);
  delay(timing);
}
