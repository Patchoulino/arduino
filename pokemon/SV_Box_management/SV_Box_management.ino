/*
 * SV Box management ;) with pause
 * T 200 14.5s
 * 999 4hr 1.425min
 * 30min 124 iems
*/

const int BALL = 0;
const int BERRY = 2;
const int ITEM = 3;
const int TM = 4;

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
  
  if (testAutoSendMode) Joystick.begin();
  else  Joystick.begin(false);

  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
  Joystick.setZAxis(128);
  Joystick.setRzAxis(128);
  Joystick.sendState();

  // Pairing controller
  for (int i = 0; i <= 2; i++)  button(ZR, 250);  // ZR does not do anything while menu open

}

void loop() {
  box_management(200, 999);
  shift_item(200, BALL);
  /*for(int i = 0; i <= 5; i++) {
    box_management(200, 999);
    if (i < 5)  shift_item(200, BERRY);
  }*/
  //wait();
}

void wait(){
  while(true){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
}

void box_management(int T, int items) { // Have your box 1 highlighted and empty to load faster, miraidon/koraidon clone on party slot 2, and looking at it
  for (int item = 1; item <= items; item++){  // A up*2 A*4 right down*2 A X*2 L A up*3 A B left
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
}

void shift_item(int T, int category) {  // starts looking at koraidon/miraidon
  // Boxes
  dpad(RIGHT, T);
  button(A, T);
  delay(1500);
  // Take item
  dpad(LEFT, T);
  dpad(DOWN, T);
  button(X, T);
  button(A, T);
  dpad(DOWN, T);
  dpad(DOWN, T);
  button(A, T);
  delay(500);
  // Give a new item
  button(A, T);
  button(A, T);
  delay(1200);
  for (int i = 0; i <= category; i++) dpad(RIGHT, T);  //2 Berrys | 3 Items | 4 TMs
  dpad(DOWN, T);
  button(A, T);
  button(A, T);
  delay(1200);
  button(B, T);
  button(B, T);
  delay(1200);
  button(B, T);
  delay(1200);
  dpad(LEFT, T);
}

void button(int btn, int timing) {
  Joystick.pressButton(btn);
  delay(timing);
  Joystick.releaseButton(btn);
  delay(timing);
}

void dpad(int btn, int timing) {
  Joystick.setHatSwitch(btn);
  delay(timing);
  Joystick.setHatSwitch(RELEASE);
  delay(timing);
}
