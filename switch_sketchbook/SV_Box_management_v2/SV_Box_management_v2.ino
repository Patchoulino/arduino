/*
 * SV Box management ;) with pause
 * 1 item evey 12.4~ sec
 * 30 min for 145
 * 3 hrs 26.46 min for 999
*/

const int IN[] = {A0, 7, 2};
const int LENGTH = 2;
const int T = 150;

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
    button(ZR, 250);  // ZR does not do anything while menu open
  }

}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() { // Have your box 1 highlighted and empty to load faster, miraidon/koraidon clone on party slot 2, and looking at it
// A up*2 A*4 right down*2 A X*2 L A up*3 A B left
  for (int i = 0; i <= 25; i++){
    switch (i) {
      case 0:
      case 3:
      case 5:
      case 6:
      case 8:
      case 12:
      case 17:
      case 21:
        button(A, T);
        break;
      case 23:
        button(B, T);
        break;
      case 14:
      case 15:
        button(X, T);
        break;
      case 16:
        button(L, T);
        break;
      case 1:
      case 2:
      case 18:
      case 19:
      case 20:
        dpad(UP, T);
        break;
      case 10:
      case 11:
        dpad(DOWN, T);
        break;
      case 9:
        dpad(RIGHT, T);
        break;
      case 25:
        dpad(LEFT, T);
        break;
      case 4:
        delay(1000);
        break;
      case 7:
        delay(1900);
        break;
      case 13:
      case 24:
        delay(1500);
        break;
      case 22:
        delay(200);
        break;
    }
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