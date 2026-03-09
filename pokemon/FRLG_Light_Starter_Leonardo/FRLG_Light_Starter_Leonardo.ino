/*
 * FRLG Light sensor Arduino leonardo
*/
//#include <Streaming.h>
#include <EEPROM.h>

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

// Analog
int sensorValue = 0;
const int analogInPin = A3;

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
  starter_sh();
}

void starter_sh() {
  int previous_value = 0;
  while (true){
    for (int i = 1; i <= 35; i++)  button(A, T, T); // 7 Sec  // Start game
    for (int i = 1; i <= 15; i++)  button(B, T, T); // 3 Sec  // Skip Recap
    for (int i = 1; i <= 16; i++)  button(A, T, T); // 3 Sec  // Select Starter
    for (int i = 1; i <= 60; i++)  button(B, T, T); // 12 Sec // Spam B while rival grabs starter
    button(START, T, T);  // check pokemon
    delay(300);
    for (int i = 1; i <= 10; i++)  button(A, T, T); // 2 Sec
    delay(1000);
    //delay(1000);
    //button(RIGHT, T, T);
    //delay(5000);
    sensorValue = analogRead(analogInPin);
    //Serial << "Counter: " << eeread(0) << " byte(0): " << EEPROM.read(0) << " byte(1): " << EEPROM.read(1) << " | Analog Read: " << sensorValue << " | Previous Value: " << previous_value << endl;
    if (sensorValue < (previous_value - 5)) {  // Shiny found! ( diff is very small, 10 out of the 1024/5V scale)
      while (true) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(100);
      }
    }
    previous_value = sensorValue;
    eewrite(eeread(0) + 1, 0);
    restart_game_fast();
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
  Joystick.pressButton(btn);
  delay(timing_on);
  Joystick.releaseButton(btn);
  delay(timing_off);
}

void dpad(int btn, int timing_on, int timing_off) {
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
