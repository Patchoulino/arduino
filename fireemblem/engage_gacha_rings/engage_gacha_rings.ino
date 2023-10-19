/*
 * Engage gacha rings, it enters a map, spam start, and goes to the ring chamber to check if you got any S
*/

const int BUTTON = 2;  // the number of the pushbutton pin

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
  pinMode(BUTTON, INPUT);
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
  for (int i = 0; i <= 2; i++)  dpad(DOWN, 250);  // DPAD does nothing on ring menu
  pair_controller(250);  // Engage does not recognize the controller automatically
}

void loop() {
  gacha_rings(100);
}

void wait(){
  while(digitalRead(BUTTON) == HIGH){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
}

void gacha_rings(int T) { 
  // Exit rings and quit save
  button(A, T);
  for (int i = 1; i <= (2500/T/2); i++)  button(B, T);
  button(PLUS, T);
  dpad(UP, T);
  for (int i = 1; i <= 3; i++)
  {
    dpad(UP, T);
    button(A, T);
  }

  // Enter save again
  for (int i = 1; i <= (8000/T/2); i++)  button(A, T);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  for (int i = 1; i <= (4000/T/2); i++)  button(B, T);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  // Go back to world
  button(PLUS, T);
  for (int i = 1; i <= 2; i++)
  {
    delay(T);
    dpad(UP, T);
    button(A, T);
  }

  // Enter Level
  for (int i = 1; i <= (10000/T/2); i++)  button(PLUS, T);
  for (int i = 1; i <= (1000/T/2); i++)  button(A, T);
  for (int i = 1; i <= (28000/T/2); i++)  button(PLUS, T);

  // Go back to the island
  for (int i = 1; i <= 2; i++)  button(B, T);
  button(A, T);
  for (int i = 1; i <= (10000/T/2); i++)  button(PLUS, T);
  dpad(UP, T);
  for (int i = 1; i <= 2; i++)  button(A, T);

  // Go back to the ring chamber
  delay(25000);
  button(X, T);
  delay(1000);
  for (int i = 1; i <= 2; i++)  dpad(DOWN, T);
  delay(1000);
  for (int i = 1; i <= 2; i++)  
  {
    button(A, T);
    delay(T);
  }
  delay(10000);
  Joystick.setYAxis(UP);
  Joystick.sendState();
  delay(2000);
  Joystick.setYAxis(128);
  Joystick.sendState();

  // Save the game first
  button(PLUS, T);
  delay(T);
  for (int i = 1; i <= 3; i++)  dpad(UP, T);
  button(A, T);
  delay(T);
  dpad(UP, T);
  button(A, T);
  delay(2000);
  button(B, T);
  delay(T);

  button(A, T);
  delay(2000);
  dpad(DOWN, T);
  button(A, T);
  for (int i = 1; i <= 3; i++)  dpad(DOWN, T);
  button(A, T);
  dpad(DOWN, T);
  button(A, T);
  delay(2000);
  button(PLUS, T);
  wait();
}

void button(int btn, int timing) {
  Joystick.pressButton(btn);
  delay(timing);
  Joystick.releaseButton(btn);
  delay(timing);
  delay(timing);
}

void dpad(int btn, int timing) {
  Joystick.setHatSwitch(btn);
  delay(timing);
  Joystick.setHatSwitch(RELEASE);
  delay(timing);
}

void pair_controller(int timing) {
  Joystick.pressButton(L);
  Joystick.pressButton(R);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
  Joystick.releaseButton(L);
  Joystick.releaseButton(R);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
  delay(1000);
  button(A, timing);
  button(A, timing);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(1000);
}