/*
 * PKMN Master Script ZA edition
 * List of functions:
 * speedrun
 * down_speedrun (ZA buildings and benches)
 * fasttravel_ZA
*/

const int switcho = 2;

// 8 leds shield
const int OUT[] = {3, 4, 5, 6, 9, 10, 11, 12};
const int OUT_LENGTH = 7;
// 4 leds shield
//const int OUT[] = {3, 5, 6, 12};
//const int OUT_LENGTH = 3;
    
const int IN[] = {A0, A1, A2, A3, A4, A5, 8, 7, 2};
const int IN_LENGTH = 8;

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

  for(int i = 0; i <= IN_LENGTH; i++)   pinMode(IN[i], INPUT);
  for(int i = 0; i <= OUT_LENGTH; i++)  pinMode(OUT[i], OUTPUT);
  groovy();
  
  if (testAutoSendMode) Joystick.begin();
  else  Joystick.begin(false);

  reset_joysticks();
  Joystick.sendState();
  for (int i = 0; i <= 2; i++)  button(ZL, 250);
}

void loop() {
  int T = 100;
  int x = bin2byte();
  switch (x) {  // Lower vaue is the one closest to USB
    case 1:    // 0000 0001
    case 2:    // 0000 0010
    case 3:    // 0000 0011
    case 4:    // 0000 0100
    case 5:    // 0000 0101
    case 6:    // 0000 0110
    case 7:    // 0000 0111
    case 8:    // 0000 1000
    case 9:    // 0000 1001
      fasttravel_ZA(T, switcho, x);
      break;
    case 128:   // 1000 0000
      speedrun(T, 5); // A spam
      break;
    case 129:   // 1000 0001
      speedrun(T, 2); // DOWN A spam
      break;
  }
}

byte bin2byte(){
  int c = 0;
  for(int i = 0; i <= IN_LENGTH-1; i++)
  {
    if(!digitalRead(IN[i]))  
    {
      if(i <= 1)  c = c + pow(2,i);
      else        c = c + pow(2,i) + 1;
    }
  }
  return c;
}

void groovy() {
  for(int i = 0; i <= OUT_LENGTH; i++) {
    digitalWrite(OUT[i], HIGH);
    delay(30);
    digitalWrite(OUT[i], LOW);
  }
}

void paused(){
  reset_joysticks();
  while(!digitalRead(IN[IN_LENGTH]))  groovy();
  while(digitalRead(IN[IN_LENGTH]))   groovy();
  while(!digitalRead(IN[IN_LENGTH]))  groovy();
}

void wait(){
  reset_joysticks();
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

void led_progress(int cycle, int range){
  float leds = ((cycle * (OUT_LENGTH + 1)) / range);  // previously 8.0
  for (int i = 0; i <= OUT_LENGTH; i++) {
    if (leds >= (i + 1))  digitalWrite(OUT[i], HIGH);
    else                  digitalWrite(OUT[i], LOW);
  }
}

void button(int btn, int timing) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  Joystick.pressButton(btn);
  delay(timing);
  Joystick.releaseButton(btn);
  delay(timing);
}

void dpad(int btn, int timing) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  Joystick.setHatSwitch(btn);
  delay(timing);
  Joystick.setHatSwitch(RELEASE);
  delay(timing);
}

void lstick_fixed(int direction) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  int X = (((direction - 1) % 3) * 127.5);
  int Y = ( 255 - (((direction - 1) / 3) * 127.5));
  Joystick.setXAxis(X);
  Joystick.setYAxis(Y);
}

void lstick(int direction, int timing) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  int X = (((direction - 1) % 3) * 127.5);
  int Y = ( 255 - (((direction - 1) / 3) * 127.5));
  Joystick.setXAxis(X);
  Joystick.setYAxis(Y);
  delay(timing);
  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
}

void speedrun(int T, int direction) {
  while (true){
    lstick_fixed(direction);
    button(A, T);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}

void fasttravel_ZA(int T, int switcho, int direction) {
  button(START, T);
  lstick(direction, 150);
  for (int i = 0; i <= (2000/T/2); i++)  button(A, T);  // 2 sec
  delay(4500/switcho);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
