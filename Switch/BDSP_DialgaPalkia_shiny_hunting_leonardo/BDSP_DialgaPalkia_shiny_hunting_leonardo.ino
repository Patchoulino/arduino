/*
 * BDSP Dialga/Palkia shiny hunting
 * buttons needed
 * HOME X A UP
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

SwitchJoystick_ Joystick;
const bool testAutoSendMode = true;

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

  for (int i = 0; i <= 1; i++){
    dpad(DOWN, T);
  }

}

void loop() { // Start at battle so reset of the arduino will open home and restart game
  // Restart game
  button(HOME, T);
  delay(500);
  button(X, T);

  for (int i = 0; i <= (40000/T/2); i++){ // 40 sec to load 
    button(A, T);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  dpad(UP, T); // Engage

  for (int i = 0; i <= (7000/T/2); i++){ // 7 sec animation
    button(A, T);
  }

  blinke = 1;
  for (int i = 0; i <= (15000/T/2); i++){ // blink and spam first move, waiting for reset
    button(A, T);
  }
  blinke = 0;
  digitalWrite(LED_BUILTIN, LOW);
}

void button(int btn, int timing) {
  Joystick.pressButton(btn);
  if (blinke) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
  Joystick.releaseButton(btn);
  if (blinke) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
}

void dpad(int btn, int timing) {
  Joystick.setHatSwitch(btn);
  delay(timing);
  Joystick.setHatSwitch(RELEASE);
  delay(timing);
}
