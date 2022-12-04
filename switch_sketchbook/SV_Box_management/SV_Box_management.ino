/*
 * SV Box management ;)
 * 1 item evey 18~ sec
 * 30 min for 100
 * 5 hrs for 999
*/

const int IN[] = {A0, 7, 2};
const int LENGTH = 2;
const int T = 250;

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
//const bool testAutoSendMode = false;

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

  /* for some reason Joystick won't listen to the buttons from void loop()
   *  even if you try a delay of 1, 2 or 3 sec, it won't listen..
   *  but if you do 2 button presses with a decent delay then
   *  it will listen to the buttons on the main void loop()
   */
  for (int i = 0; i <= 2; i++){
    dpad(DOWN, T);
  }

}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() { // Have your box 1 highlighted and empty to load faster, miraidon/koraidon clone on party slot 2, and looking at it

// A uu AAAA r dd A XX L A uuu A B l
  for (int i = 0; i <= 20; i++){
    switch (i) {
      case 0:
        button(A, T);
        break;
      case 1:
      case 2:
        dpad(UP, T);
        break;
      case 3:
        button(A, T);
        delay(1000);
        break;
      case 4:
        button(A, T);
        break;
      case 5:
        button(A, T);
        delay(2100);
        break;
      case 6:
        button(A, T);
        break;
      case 7:
        dpad(RIGHT, T);
        break;
      case 8:
      case 9:
        dpad(DOWN, T);
        break;
      case 10:
        button(A, T);
        delay(2100);
        break;
      case 11:
      case 12:
        button(X, T);
        break;
      case 13:
        button(L, T);
        break;
      case 14:
        button(A, T);
        break;
      case 15:
      case 16:
      case 17:
        dpad(UP, T);
        break;
      case 18:
        button(A, T);
        delay(200);
        break;
      case 19:
        button(B, T);
        delay(2300);
        break;
      case 20:
        dpad(LEFT, T);
        break;
    }
  }
}

void button(int btn, int timing) {
  for(int i = 0; i <= LENGTH-1; i++)  if(digitalRead(IN[i]))  resetFunc();
  if(!digitalRead(IN[2]))  resetFunc();
  Joystick.pressButton(btn);
  delay(timing);
  Joystick.releaseButton(btn);
  delay(timing);
}

void dpad(int btn, int timing) {
  for(int i = 0; i <= LENGTH-1; i++)  if(digitalRead(IN[i]))  resetFunc();
  if(!digitalRead(IN[2]))  resetFunc();
  Joystick.setHatSwitch(btn);
  delay(timing);
  Joystick.setHatSwitch(RELEASE);
  delay(timing);
}
