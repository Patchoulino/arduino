const int A = 2;
const int T = 100;
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
  speedrun(T, 2);
}

void speedrun(int T, int direction) {
  lstick_fixed(direction);
  button(A, T);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void lstick_fixed(int direction) {
  int X = (((direction - 1) % 3) * 127.5);
  int Y = ( 255 - (((direction - 1) / 3) * 127.5));
  Joystick.setXAxis(X);
  Joystick.setYAxis(Y);
}

void button(int btn, int timing) {
  Joystick.pressButton(btn);
  delay(timing);
  Joystick.releaseButton(btn);
  delay(timing);
}
