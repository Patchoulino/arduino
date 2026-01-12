/*
 * BDSP Darkrai shiny hunting (4 days)
 * buttons needed
 * HOME X A UP
 */

// 8 leds shield
const int OUT[] = {3, 4, 5, 6, 9, 10, 11, 12};
const int OUT_LENGTH = 7;
// 4 leds shield
//const int OUT[] = {3, 5, 6, 12};
//const int OUT_LENGTH = 3;
    
const int IN[] = {A0, A1, A2, A3, A4, A5, 8, 7, 2};
const int IN_LENGTH = 8;

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

  for(int i = 0; i <= IN_LENGTH; i++)   pinMode(IN[i], INPUT);
  for(int i = 0; i <= OUT_LENGTH; i++)  pinMode(OUT[i], OUTPUT);
  groovy();

  if (testAutoSendMode) Joystick.begin();
  else  Joystick.begin(false);

  reset_joysticks();
  Joystick.sendState();
  for (int i = 0; i <= 2; i++)  button(LSTICK, 250);
}

void loop() { // Start at battle with darkrai so reset of the arduino will open home and restart game
  // Restart game
  button(HOME, T);
  delay(500);
  button(X, T);

  for (int i = 0; i <= (35000/T/2); i++)  button(A, T);
  digitalWrite(LED_BUILTIN, HIGH);
  for (int i = 0; i <= (15000/T/2); i++)  button(A, T);
  blinke = 1;
  for (int i = 0; i <= (10000/T/2); i++)  button(A, T);
  blinke = 0;
  digitalWrite(LED_BUILTIN, LOW);
}

void paused(){
  reset_joysticks();
  while(!digitalRead(IN[IN_LENGTH]))  groovy();
  while(digitalRead(IN[IN_LENGTH]))   groovy();
  while(!digitalRead(IN[IN_LENGTH]))  groovy();
}

void groovy() {
  for(int i = 0; i <= OUT_LENGTH; i++) {
    digitalWrite(OUT[i], HIGH);
    delay(30);
    digitalWrite(OUT[i], LOW);
  }
}

void button(int btn, int timing) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  Joystick.pressButton(btn);
  if (blinke) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
  Joystick.releaseButton(btn);
  if (blinke) digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(timing);
}

void dpad(int btn, int timing) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  Joystick.setHatSwitch(btn);
  delay(timing);
  Joystick.setHatSwitch(RELEASE);
  delay(timing);
}

void reset_joysticks(){
  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
  Joystick.setZAxis(128);
  Joystick.setRzAxis(128);
}
