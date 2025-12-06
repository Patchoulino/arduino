/*
PKMN Master Script ZA edition
List of functions:
speedrun (A spam)
run_backnforth
fasttravel
autobattle
zoneX
fossils
*/

const bool groov = true;
const int switcho = 2;
const int gate_time = 2000;
const int backnforth_time = 3500;

// 8 leds shield
//const int OUT[] = {3, 4, 5, 6, 9, 10, 11, 12};
//const int OUT_LENGTH = 7;
//const int pause_time = 35;
// 4 leds shield
const int OUT[] = {3, 5, 6, 12};
const int OUT_LENGTH = 3;
const int pause_time = 70;
  
const int IN[] = {A0, A1, A2, A3, A4, A5, 8, 7, 2};
const int IN_LENGTH = 8;

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
  for (int i = 0; i <= 2; i++)  button(RSTICK, 250);
}

void loop() {
  int x = bin2byte();
  int T = 100;
  int direction = 0;
  int speed = 0;
  switch (x) {  // Lower vaue is the one closest to USB
    case 0:    // 0000 0000
      speedrun(T, 2); // benches
      break;
    case 1:    // 0000 0001
    case 2:    // 0000 0010
    case 3:    // 0000 0011
    case 4:    // 0000 0100
    case 5:    // 0000 0101
    case 6:    // 0000 0110
    case 7:    // 0000 0111
    case 8:    // 0000 1000
    case 9:    // 0000 1001
      fasttravel(T, switcho, x); // fast travel
      break;
    case 16:    // 0001 0000
      direction = 2;
      fasttravel(T, 4, direction); // fast travel same location
      break;
    case 17:    // 0001 0001
    case 18:    // 0001 0010
    case 19:    // 0001 0011
    case 20:    // 0001 0100
    case 21:    // 0001 0101
    case 22:    // 0001 0110
    case 23:    // 0001 0111
    case 24:    // 0001 1000
    case 25:    // 0001 1001
      direction = (x - 16);
      speed = switcho + 1;
      fasttravel(T, speed, direction); // small window or cafeterias
      break;
    case 49:    // 0011 0001
    case 50:    // 0011 0010
    case 51:    // 0011 0011
    case 52:    // 0011 0100
    case 53:    // 0011 0101
    case 54:    // 0011 0110
    case 55:    // 0011 0111
    case 56:    // 0011 1000
    case 57:    // 0011 1001
      direction = (x - 48);
      speed = switcho + 2;
      fasttravel(T, speed, direction); // smaller window or cafeterias
      break;
    case 64:    // 0100 0000
      direction = 8;
      run_backnforth(T, backnforth_time, direction);
      break;
    case 65:    // 0100 0001 (1)
    case 66:    // 0100 0010 (2)
    case 67:    // 0100 0011 (3)
    case 68:    // 0100 0100 (4)
    case 69:    // 0100 0101 (5)
    case 70:    // 0100 0110 (6)
    case 71:    // 0100 0111 (7)
    case 72:    // 0100 1000 (8)
    case 73:    // 0100 1001 (9)
      direction = (x - 64);
      run_backnforth(T, backnforth_time, direction);
      break;
    case 128:    // 1000 0000 (0)
      speedrun(T, 5); // A spam + direction
      break;
    case 129:    // 1000 0001 (1)
    case 130:    // 1000 0010 (2)
    case 131:    // 1000 0011 (3)
    case 132:    // 1000 0100 (4)
    case 133:    // 1000 0101 (5)
    case 134:    // 1000 0110 (6)
    case 135:    // 1000 0111 (7)
    case 136:    // 1000 1000 (8)
    case 137:    // 1000 1001 (9)
      direction = (x - 128);
      speedrun(T, direction); // A spam + direction
      break;
    case 192:    // 1100 0000
      autobattle(50);
      break;
    case 193: // 1100 0001  Zone 01
    case 194: // 1100 0010  Zone 02
    case 195: // 1100 0011  Zone 03
    case 196: // 1100 0100  Zone 04
    case 197: // 1100 0101  Zone 05
    case 198: // 1100 0110  Zone 06
    case 199: // 1100 0111  Zone 07
    case 200: // 1100 1000  Zone 08
    case 201: // 1100 1001  Zone 09
    case 202: // 1100 1010  Zone 10
    case 203: // 1100 1011  Zone 11
    case 204: // 1100 1100  Zone 12
    case 205: // 1100 1101  Zone 13
    case 206: // 1100 1110  Zone 14
    case 207: // 1100 1111  Zone 15
    case 208: // 1101 0000  Zone 16
    case 209: // 1101 0001  Zone 17
    case 210: // 1101 0010  Zone 18
    case 211: // 1101 0011  Zone 19
    case 212: // 1101 0100  Zone 20 water bench
    case 213: // 1101 0101  Zone 20 grass bench
    case 214: // 1101 0110  Zone 20 fire starters
    case 215: // 1101 0111  Sewers litw
    case 216: // 1101 1000  Lab 30f
    case 217: // 1101 1001  Lab 60f
    case 218: // 1101 1010  Lab Switch 1 30f
    case 219: // 1101 1011  Lab Switch 1 60f
    case 220: // 1101 1100  Lab Switch 1 120f
      direction = (x - 192);
      zone(T, direction);
      break;
  }
}

int bin2byte(){
  int c = 0;
  for(int i = 0; i < IN_LENGTH; i++)
  {
    if(!digitalRead(IN[i]))  
    {
      double result = pow(2, i);
      int result_int = (int)(result + 0.5);
      c = c + result_int;
    }
  }
  return c;
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

void wait_forever(){
  reset_joysticks();
  while(true){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
}

void wait(int total_time){
  unsigned int interval = 10;
  for (unsigned int i = 0; i < total_time; i += interval) {
    if(!digitalRead(IN[IN_LENGTH]))  paused();
    delay(interval);
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

void button_hold(int btn, int timing) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  Joystick.pressButton(btn);
  delay(timing);
}

void button_release(int btn, int timing) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
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

void lstick(int direction, int timing) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  int X = (int)((((direction - 1) % 3) * 127.5) + 0.5);
  int Y = (int)(255 - (((direction - 1) / 3) * 127.5 + 0.5));
  Joystick.setXAxis(X);
  Joystick.setYAxis(Y);
  wait(timing);
  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
}

void lstick_fixed(int direction) {
  if(!digitalRead(IN[IN_LENGTH]))  paused();
  int X = (int)((((direction - 1) % 3) * 127.5) + 0.5);
  int Y = (int)(255 - (((direction - 1) / 3) * 127.5 + 0.5));
  Joystick.setXAxis(X);
  Joystick.setYAxis(Y);
}

void speedrun(int T, int direction) {
  lstick_fixed(direction);
  button(A, T);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void fasttravel_confirmation(int T){
  int time = 0;
  wait(300);
  for (int i = 0; i <= (1800/T/2); i++)  button(A, T);  // 2 sec
  time = 10800 + (-4200 * switcho);  // loading screen time for each switcho
  wait(time);
}

void fasttravel(int T, int timing, int direction) {
  int time = 0;
  button(START, T);
  time = 220 + (-50 * timing);      // variable time left stick
  lstick(direction, time);
  fasttravel_confirmation(T);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void autobattle(int T) {
  button_hold(ZL, T);
  for (int i = 0; i < 3; i++)  button(A, T);
  button(B, T);
  button_release(ZL, T);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void run_line(int T, int duration, int direction) {
    lstick_fixed(direction);
    button(B, T);
    wait(duration);
    lstick(5, T);
}

void walk_line(int T, int duration, int direction) {
    lstick_fixed(direction);
    wait(duration);
    lstick(5, T);
}

void run_backnforth(int T, int duration, int direction) {
  for (int i = 1; i <= 2; i++) {
    run_line(T, duration, direction);
    wait(100);
    direction = 10 - direction;
    duration = duration + 7; // 10 too down, 5 too front
  }
}

void enter_zone(int T){ // walk forward and press A
  run_line(T, 500, 8);
  button(A, T);
  wait(gate_time);
}

void soft_reset(int T) {
  button(HOME, T);
  wait(800);
  button(X, T);
  wait(400);
  for (int i = 0; i <= (12000/T/2); i++)  button(A, T);  // Exit and Start game
}

void fossils(int T, int cycles) {
  soft_reset(T);
  for (int i = 1; i < cycles; i++){  // 30 fossils
    if (groov) led_progress(i, cycles);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    for (int i = 0; i <= (15350/50/2); i++)  button(A, 50); // 15600
  }
  for (int i = 0; i <= (6000/T/2); i++)  button(B, T);
  button(X, T);
  wait(400);
  button(A, T);
  wait(2000);
  dpad(UP, T);
  paused();
  for (int i = 0; i <= 2; i++)  button(RSTICK, 250);  // in case the switch fell asleep
}

void zone(int T, int zone){
  int time = 0;
    switch (zone) {
    case 1:   // 1100 0001
      break;
    case 2:   // 1100 0010
      break;
    case 3:   // 1100 0011
      break;
    case 4:   // 1100 0100
      break;
    case 5:   // 1100 0101
      break;
    case 6:   // 1100 0110  bunearys
      run_line(T, 500, 4);
      button(START, T);
      lstick(8, 100);
      fasttravel_confirmation(T);
      break;
    case 7:   // 1100 0111
      break;
    case 8:   // 1100 1000
      break;
    case 9:   // 1100 1001
      break;
    case 10:  // 1100 1010
      break;
    case 11:  // 1100 1011
      break;
    case 12:  // 1100 1100
      break;
    case 13:  // 1100 1101  scyther
      enter_zone(T);
      run_line(T, 1500, 7);
      button(START, T);
      fasttravel_confirmation(T);
      break;
    case 14:  // 1100 1110  heliolisk
      enter_zone(T);
      run_backnforth(T, 1500, 8);
      button(A, T);
      wait(gate_time);
      button(START, T);
      lstick(2, 50);
      fasttravel_confirmation(T);
      break;
    case 15:  // 1100 1111
      break;
    case 16:  // 1101 0000  drampa soft resets
      soft_reset(T);
      wait(3000); // drampa spawn
      for (int i = 1; i <= 18; i++){ // 280ms every groove = 8 * 35ms || 18 = 5040ms
        groovy();
      }
      break;
    case 17:  // 1101 0001  drampa walks
      for (int i = 1; i <= 25; i++){ 
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        run_line(T, 500, 7);
        run_line(T, 2000, 4);
        run_line(T, 1000, 7);
        button(START, T);
        lstick(4, 50);
        fasttravel_confirmation(T);
      }
      button(HOME, T);
      paused();
      break;
    case 18:  // 1101 0010  clefairy walks
      for (int i = 1; i <= 60; i++){ 
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        run_line(T, 500, 7);
        run_line(T, 2000, 4);
        run_line(T, 1000, 7);
        button(START, T);
        lstick(4, 50);
        fasttravel_confirmation(T);
      }
      button(HOME, T);
      paused();
      break;
    case 19:  // 1101 0011  Zone 19 - does not work with clefa/drampa
      run_line(T, 500, 7);
      run_line(T, 2000, 4);
      run_line(T, 1000, 7);
      button(START, T);
      lstick(4, 50);
      fasttravel_confirmation(T);
      break;
    case 20:  // 1101 0100  Zone 20 tower - 6 alphas bench next to water
      run_backnforth(T, 1500, 8);
      lstick_fixed(2);
      for (int i = 0; i <= (3000/T/2); i++)  button(A, T);  // 3 sec # bench
      reset_joysticks();
      wait(14800);
      break;
    case 21:  // 1101 0101  Zone 20 tower - 6 alphas bench next to grass
      run_line(T, 500, 6);
      button(L, T);
      run_line(T, 400, 2);
      run_line(T, 10, 6);
      for (int i = 0; i <= (3000/T/2); i++)  button(A, T);  // 3 sec # bench
      reset_joysticks();
      wait(14800);
      break;
    case 22:  // 1101 0110  Zone 20 - fire starters
      run_line(T, 3000, 7);
      run_line(T, 1000, 4);
      run_line(T, 2000, 7);
      button(START, T);
      wait(200);
      button(Y, T);
      fasttravel_confirmation(T);
      break;
    case 23:  // 1101 0111  sewers 1 litwick
      run_line(T, 4000, 8);
      wait(100);
      run_line(T, 4100, 2);
      wait(100);
      break;
    case 24:  // 1101 1000  Lab 30f
      fossils(T, 30);
      break;
    case 25:  // 1101 1001  Lab 60f
      fossils(T, 60);
      break;
    case 26:  // 1101 1010  Lab Switch1 30f
      fossils(T, 35);
      break;
    case 27:  // 1101 1011  Lab Switch2 60f
      fossils(T, 70);
      break;
    case 28:  // 1101 1011  Lab Switch2 120f
      fossils(T, 140);
      break;
  }
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}