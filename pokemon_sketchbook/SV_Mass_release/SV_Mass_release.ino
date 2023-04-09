/*
 * SV Mass release
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

  for(int i = 0; i <= LENGTH; i++)  pinMode(IN[i], INPUT);
  
  if (testAutoSendMode) Joystick.begin();
  else  Joystick.begin(false);

  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
  Joystick.setZAxis(128);
  Joystick.setRzAxis(128);
  Joystick.sendState();

  // Pairing controller
  for (int i = 0; i <= 2; i++)  button(ZR, 250);  // ZR does not do anything while on box

}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() { // Look at box slot 1,1
  int orientation = 1;  // 1 = Right
  for (int y = 0; y <= 4; y++) {
    for (int x = 0; x <= 5; x++) {
      if (x > 0) {  // Shift L/R not on first mon
        if (orientation == 1) dpad(RIGHT, T);
        else  dpad(LEFT, T);
      }
      for (int i = 0; i <= 9; i++){
        switch (i) {
          case 0:
          case 3:
          case 6:
          case 8:
            button(A, T);
            break;
          case 1:
          case 2:
          case 5:
            dpad(UP, T);
            break;
          case 4:
            delay(700);
            break;
          case 7:
            delay(1300);
            break;
          case 9:
            delay(600);
            break;
        }
      }
    }
    if (y < 4) {  // Change orentiation and shift down
      if (orientation == 1) orientation = 0;
      else  orientation = 1;
      dpad(DOWN, T);
    }
  }

  while(true){  // change box and reset
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
