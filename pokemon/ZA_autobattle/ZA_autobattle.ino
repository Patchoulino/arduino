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
const int SELECT = 8;
const int START = 9;
const int LSTICK = 10;
const int RSTICK = 11;
const int HOME = 12;
const int CAPTURE = 13;
const int UP = 0;
const int RIGHT = 90;
const int DOWN = 180;
const int LEFT = 270;
const int RELEASE = -1;

#include "SwitchJoystick.h"
SwitchJoystick_ Joystick;
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
}

void loop() {
  autobattle(50);
}

void autobattle(int T) {
  button_hold(ZL, T);
  for (int i = 0; i < 3; i++)  button(A, T);
  button(X, T);
  button_release(ZL, T);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void button_hold(int btn, int timing) {
  Joystick.pressButton(btn);
  delay(timing);
}

void button_release(int btn, int timing) {
  Joystick.releaseButton(btn);
  delay(timing);
}

void button(int btn, int timing) {
  Joystick.pressButton(btn);
  delay(timing);
  Joystick.releaseButton(btn);
  delay(timing);
}
