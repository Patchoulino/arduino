/*
 * FRLG Light sensor Arduino leonardo
*/
//#include <Streaming.h>
#include <EEPROM.h>

const bool groov = true;// 8 leds shield

const int OUT[] = {3, 4, 5, 6, 9, 10, 11, 12};
const int OUT_LENGTH = 7;
const int pause_time = 35;
// 4 leds shield
//const int OUT[] = {3, 5, 6, 12};
//const int OUT_LENGTH = 3;
//const int pause_time = 70;
  
const int IN[] = {A0, A1, A2, A3, A4, A5, 8, 7, 2};
const int IN_LENGTH = 8;

const byte T = 100;
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
const int START = 9;
const int SELECT = 8;
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

  if (testAutoSendMode) Joystick.begin();
  else  Joystick.begin(false);

  reset_joysticks();
  Joystick.sendState();
  for (int i = 0; i <= 2; i++)  button(ZL, 250, 250);
  //for (int i = 2; i <= 13; i++)  pinMode(i, OUTPUT);
  //for (int i = 2; i <= 13; i++)  digitalWrite(i, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  paused();
  starter_sh();
}

void starter_sh() {
  while (true){
    restart_game_fast();
    for (int i = 1; i <= 35; i++)  button(A, T, T); // 7 Sec  // Start game
    for (int i = 1; i <= 15; i++)  button(B, T, T); // 3 Sec  // Skip Recap
    for (int i = 1; i <= 16; i++)  button(A, T, T); // 3 Sec  // Select Starter
    for (int i = 1; i <= 60; i++)  button(B, T, T); // 12 Sec // Spam B while rival grabs starter
    button(START, T, T);  // check pokemon
    delay(300);
    for (int i = 1; i <= 10; i++)  button(A, T, T); // 2 Sec
    delay(1000);
    for (int i = 1; i <= 3; i++)  dpad(RIGHT, T, T);
    for (int i = 1; i <= 3; i++)  dpad(LEFT, T, T);
    delay(6000);
    eewrite(eeread(0) + 1, 0);
  }
}

void restart_game_fast() {
  Joystick.pressButton(A);
  Joystick.pressButton(B);
  Joystick.pressButton(X);
  Joystick.pressButton(Y);
  delay(T);
  Joystick.releaseButton(A);
  Joystick.releaseButton(B);
  Joystick.releaseButton(X);
  Joystick.releaseButton(Y);
  delay(T);
}

void button(int btn, int timing_on, int timing_off) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  Joystick.pressButton(btn);
  delay(timing_on);
  Joystick.releaseButton(btn);
  delay(timing_off);
}

void dpad(int btn, int timing_on, int timing_off) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  Joystick.setHatSwitch(btn);
  delay(timing_on);
  Joystick.setHatSwitch(RELEASE);
  delay(timing_off);
}

void reset_joysticks(){
  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
  Joystick.setZAxis(128);
  Joystick.setRzAxis(128);
}

void eewrite(unsigned int value, int address) {
  EEPROM.write(address, value & 0xFF);
  EEPROM.write(address + 1, value >> 8);
}

unsigned int eeread(int address) {
  return  (EEPROM.read(address + 1) << 8) + EEPROM.read(address);
}

void groovy() {
  if (groov) {
    for(int i = 0; i <= OUT_LENGTH; i++) {
      digitalWrite(OUT[i], HIGH);
      delay(pause_time);
      digitalWrite(OUT[i], LOW);
    }
  }
  else {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(250);
  }
}

void paused(){
  reset_joysticks();
  while(!digitalRead(IN[IN_LENGTH]))  groovy();
  while(digitalRead(IN[IN_LENGTH]))   groovy();
  while(!digitalRead(IN[IN_LENGTH]))  groovy();
}