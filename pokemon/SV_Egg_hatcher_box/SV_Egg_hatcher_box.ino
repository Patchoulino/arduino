/*
 * SV Egg hatcher
*/
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
  for (int i = 0; i <= 2; i++)  button(L, 250);  // L to re-focus camera
}

void loop() {
  egg_hatcher_box(100);
}

void wait(){
  while(true){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
}

void reset_joysticks(){
  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
  Joystick.setZAxis(128);
  Joystick.setRzAxis(128);
}

void run_circles(int T) {
  button(L, T);
  Joystick.setYAxis(0);   // Left joystick UP
  Joystick.setZAxis(255); // Right joystick RIGHT (camera left)
  for (int i = 0; i < ((3 * 60UL * 930)/T/4); i++){ // spam A and LSTICK for 3~ min
    button(LSTICK, T);
    button(A, T);
  }
  reset_joysticks();
}

void egg_hatcher(int T) {
  run_circles(T);
  wait();
}

void egg_hatcher_box(int T) {
  int t = 200;
  for (int x = 0; x <= 5; x++){
    run_circles(T);
    button(X, t);
    delay(1500);
    button(A, t);
    delay(1500);
    dpad(LEFT, t);
    dpad(DOWN, t);
    button(MINUS, t);
    for (int i = 0; i < 4; i++) dpad(DOWN, t);
    button(A, t);
    for (int i = 0; i < (x + 1); i++) dpad(RIGHT, t);
    dpad(UP, t);
    button(A, t);
    if (x == 5) wait();
    dpad(RIGHT, t);
    button(MINUS, t);
    for (int i = 0; i < 4; i++) dpad(DOWN, t);
    button(A, t);
    for (int i = 0; i < (x + 2); i++) dpad(LEFT, t);
    dpad(DOWN, t);
    button(A, t);
    button(B, t);
    delay(1500);
    button(B, t);
  }
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
