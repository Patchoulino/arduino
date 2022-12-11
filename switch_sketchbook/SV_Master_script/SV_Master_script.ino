/*
 * SV Master Script
*/

const int IN[] = {A0, A1, A2, A3, A4, A5, 8, 7, 2};
const int LENGTH = 8;

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

  for(int i = 0; i <= LENGTH; i++)  pinMode(IN[i], INPUT);
  
  if (testAutoSendMode) Joystick.begin();
  else  Joystick.begin(false);

  reset_joysticks();
  Joystick.sendState();

  // Pairing controller
  for (int i = 0; i <= 2; i++)  button(LSTICK, 250);
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop() {
  int x = bin2byte();
  switch (x) {
    case 1:
      box_management(200, 999);
      wait();
      break;
    case 2:
      egg_pickup(50);
      break;
    case 4:
      egg_hatcher(100);
      break;
    case 8:
      egg_hatcher_box(100);
      break;
    case 16:
      box_release(150);
      break;
    case 32:
      speedrun(100);
      break;
    case 64:
      box_management(200, 999);
      shift_item(200);
      box_management(200, 999);
      wait();
      break;
    case 128:
      //box_management(200, 100);
      box_management(200, 21);
      wait();
      break;
  }
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(100);
}

byte bin2byte(){
  int c = 0;
  for(int i = 0; i <= LENGTH-1; i++)
  {
    if(!digitalRead(IN[i]))  
    {
      if(i <= 1)  c = c + pow(2,i);
      else        c = c + pow(2,i) + 1;
    }
  }
  return c;
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

void box_management(int T, int items) { // Have your box 1 highlighted and empty to load faster, miraidon/koraidon clone on party slot 2, and looking at it
  for (int item = 1; item <= items; item++){  // A up*2 A*4 right down*2 A X*2 L A up*3 A B left
    for (int i = 0; i <= 25; i++){
      switch (i) {
        case 0:
        case 3:
        case 5:
        case 6:
        case 8:
        case 12:
        case 17:
        case 21:
          button(A, T);
          break;
        case 23:
          button(B, T);
          break;
        case 14:
        case 15:
          button(X, T);
          break;
        case 16:
          button(L, T);
          break;
        case 1:
        case 2:
        case 18:
        case 19:
        case 20:
          dpad(UP, T);
          break;
        case 10:
        case 11:
          dpad(DOWN, T);
          break;
        case 9:
          dpad(RIGHT, T);
          break;
        case 25:
          dpad(LEFT, T);
          break;
        case 4:
          delay(1000);
          break;
        case 7:
          delay(1900);
          break;
        case 13:
        case 24:
          delay(1500);
          break;
        case 22:
          delay(200);
          break;
      }
    }
  }
  //wait();
}

void egg_pickup(int T) { // Look at the picnic and wait 
  for (int c = 1; c <= 15; c++){  // 30min 15*2m
    delay(2 * 60UL * 910);
    for (int i = 0; i <= (9800/T/2); i++)  button(A, T);
    for (int i = 0; i <= (1000/T/2); i++)  button(B, T);
  }
  wait();
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

void box_release(int T) { // Look at box slot 1,1
  int orientation = 1;  // 1 = Right
  for (int y = 0; y <= 4; y++) {
    for (int x = 0; x <= 5; x++) {
      if (x > 0) {  // Shift L/R not on first mon
        if (orientation == 1) dpad(RIGHT, T);
        else  dpad(LEFT, T);
      }
      for (int i = 0; i <= 9; i++){
        switch (i) {
          case 0:
          case 3:
          case 6:
          case 8:
            button(A, T);
            break;
          case 1:
          case 2:
          case 5:
            dpad(UP, T);
            break;
          case 4:
            delay(700);
            break;
          case 7:
            delay(1300);
            break;
          case 9:
            delay(600);
            break;
        }
      }
    }
    if (y < 4) {  // Change orentiation and shift down
      if (orientation == 1) orientation = 0;
      else  orientation = 1;
      dpad(DOWN, T);
    }
  }
  wait();
}

void speedrun(int T) {
  while (true){
    button(A, T);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}

void shift_item(int T) {  // starts looking at koraidon/miraidon
    dpad(RIGHT, T);
    button(A, T);
    delay(1500);
    dpad(LEFT, T);
    dpad(DOWN, T);
    button(X, T);
    button(A, T);
    dpad(DOWN, T);
    button(A, T);
    // does swap item works with box full?
    for (int i = 0; i <= 3; i++) dpad(RIGHT, T);  //items
    dpad(DOWN, T);
    button(A, T);
    dpad(DOWN, T);
    button(A, T);
    delay(1500);
    dpad(DOWN, T);
    button(A, T);
    delay(1500);
    button(A, T);
    delay(1500);
    button(A, T);
    button(B, T);
    delay(1500);
    dpad(DOWN, T);
    dpad(LEFT, T);
}

void button(int btn, int timing) {
  if(!digitalRead(IN[LENGTH]))  resetFunc();
  Joystick.pressButton(btn);
  delay(timing);
  Joystick.releaseButton(btn);
  delay(timing);
}

void dpad(int btn, int timing) {
  if(!digitalRead(IN[LENGTH]))  resetFunc();
  Joystick.setHatSwitch(btn);
  delay(timing);
  Joystick.setHatSwitch(RELEASE);
  delay(timing);
}
