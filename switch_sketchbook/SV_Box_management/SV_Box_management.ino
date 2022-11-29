/*
 * SV Box management ;)
 * 1 item evey 19~20 sec
*/

const int T = 300;
int blinke = 0;

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

void loop() { // Have your box 1 highlighted, miraidon/koraidon clone on party slot 2, and looking at it

// A uu AAAA r dd A delay XX L A uuu A B delay l
  for (int i = 0; i <= 26; i++){
    switch (i) {
      case 0:
        button(A, T);
        break;
      case 1:
      case 2:
        dpad(UP, T);
        break;
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
        button(A, T);
        break;
      case 11:
        dpad(RIGHT, T);
        break;
      case 12:
      case 13:
        dpad(DOWN, T);
        break;
      case 14:
        button(A, T);
        break;
      case 15:
        delay(3000);
        break;
      case 16:
      case 17:
        button(X, T);
        break;
      case 18:
        button(L, T);
        break;
      case 19:
        button(A, T);
        break;
      case 20:
      case 21:
      case 22:
        dpad(UP, T);
        break;
      case 23:
        button(A, T);
        break;
      case 24:
        button(B, T);
        break;
      case 25:
        delay(2000);
        break;
      case 26:
        dpad(LEFT, T);
        break;
    }
  }
}

void button(int btn, int timing) {
  Joystick.pressButton(btn);
  //Joystick.sendState();
  if (blinke) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
  Joystick.releaseButton(btn);
  //Joystick.sendState();
  if (blinke) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
}

void dpad(int btn, int timing) {
  Joystick.setHatSwitch(btn);
  //Joystick.sendState();
  delay(timing);
  Joystick.setHatSwitch(RELEASE);
  //Joystick.sendState();
  delay(timing);
}
