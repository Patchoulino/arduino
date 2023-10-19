/*
 * SV Master Script
 * List of functions:
 * box_management
 * egg_pickup
 * run_circles
 * egg_hatcher
 * egg_hatcher_box
 * box_release
 * shift_item
 * speedrun
 * regi_shiny_hunting (actually SWSH)
 * zacianzamazenta_beastball (actually SWSH)
*/

const int IN[] = {A0, A1, A2, A3, A4, A5, 8, 7, 2};
const int IN_LENGTH = 8;
const int OUT[] = {3, 4, 5, 6, 9, 10, 11, 12};
const int OUT_LENGTH = 7;
// 4 leds shield
//const int OUT[] = {3, 5, 6, 12};
//const int OUT_LENGTH = 3;

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

  // Pairing controller
  for (int i = 0; i <= 2; i++)  button(LSTICK, 250);
}

void loop() {
  int x = bin2byte();
  switch (x) {
    case 1:    // 0000 0001
      box_management(200, 20);
      wait();
      break;
    case 3:    // 0000 0011
      box_management(200, 50);
      wait();
      break;
    case 7:    // 0000 0111
      box_management(200, 500);
      wait();
      break;
    case 15:    // 0000 1111
      box_management(200, 999);
      wait();
      break;
    case 2:    // 0000 0010
      egg_pickup(50);
      break;
    case 4:    // 0000 0100
      egg_hatcher(100,5120);
      break;
    case 6:    // 0000 0110
      egg_hatcher_box(100,5120);  // Starters
      break;
    case 134:    // 1000 0110
      egg_hatcher_box(100,1280);  // Magikarp
      break;
    case 70:    // 0100 0110
      egg_hatcher_box(100,2560);
      break;
    case 198:    // 1100 0110
      egg_hatcher_box(100,3840);
      break;
    case 38:    // 0010 0110
      egg_hatcher_box(100,6400);
      break;
    case 166:    // 1010 0110
      egg_hatcher_box(100,7680);  // Spiritomb
      break;
    case 102:    // 0110 0110
      egg_hatcher_box(100,8960);
      break;
    case 230:    // 1110 0110
      egg_hatcher_box(100,10240);
      break;
    case 14:   // 0000 1110
      box_release(150);
      break;
    case 8:    // 0000 1000
      //regi_shiny_hunting(300);
      zacianzamazenta_beastball(300);
      break;
    case 16:   // 0001 0000
      speedrun(100);
      break;
    case 65:   // 0100 0001
      box_management(200, 20);
      shift_item(200, BERRY);
      break;
    case 67:   // 0100 0011
      box_management(200, 50);
      shift_item(200, BERRY);
      break;
    case 71:   // 0100 0111
      for(int i = 0; i <= 5; i++) {
        box_management(200, 500);
        if (i < 5)  shift_item(200, BERRY);
      }
      wait();
      break;
    case 79:   // 0100 1111
      for(int i = 0; i <= 5; i++) {
        box_management(200, 999);
        if (i < 5)  shift_item(200, BERRY);
      }
      wait();
      break;
    case 129:  // 1000 0001
      box_management(200, 20);
      shift_item(200, TM);
      break;
    case 131:  // 1000 0011
      box_management(200, 50);
      shift_item(200, TM);
      break;
    case 135:  // 1000 0111
      box_management(200, 500);
      shift_item(200, TM);
      break;
    case 143:  // 1000 1111
      box_management(200, 999);
      shift_item(200, TM);
      break;
    case 193:  // 1100 0001
      box_management(200, 20);
      shift_item(200, ITEM);
      break;
    case 195:  // 1100 0011
      box_management(200, 50);
      shift_item(200, ITEM);
      break;
    case 199:  // 1100 0111
      box_management(200, 999);
      shift_item(200, BALL);
      break;
    case 207:  // 1100 1111
      box_management(200, 999);
      shift_item(200, ITEM);
      break;
  }
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(100);
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

//void(* resetFunc) (void) = 0; //declare reset function @ address 0

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
  float leds = ((cycle * 8.0) / range);
  for (int i = 0; i <= OUT_LENGTH; i++) {
    if (leds >= (i + 1))  digitalWrite(OUT[i], HIGH);
    else                  digitalWrite(OUT[i], LOW);
  }
}

void box_management(int T, int items) { // Have your box 1 highlighted and empty to load faster, miraidon/koraidon clone on party slot 2, and looking at it
  for (int item = 1; item <= items; item++){  // A up*2 A*4 right down*2 A X*2 L A up*3 A B left
    led_progress(item, items);
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
}

void egg_pickup(int T) { // Look at the picnic and wait 
  for (int c = 1; c <= 15; c++){  // 30min 15*2m
    led_progress(c, 15);
    delay(2 * 60UL * 908);
    for (int i = 0; i <= (10000/T/2); i++)  button(A, T);
    for (int i = 0; i <= (100/T/2); i++)  button(B, T);
  }
  wait();
}

void run_circles(int T, int egg_steps) {
  button(L, T); //20s hatching time, 120s hatching total
  float range = ((egg_steps * 9.2578125) + 120000); // 9.2578125
  range = (range/T/4);
  //int range = ((3 * 60UL * 930)/T/4); // 930 (5120) starters | 1062 spiritomb (7680)
  for (int i = 0; i <= range; i++){ // spam A and LSTICK for 3~ min
    led_progress(i, range);
    Joystick.setYAxis(0);   // Left joystick UP
    Joystick.setZAxis(255); // Right joystick RIGHT (camera left)
    button(LSTICK, T);
    button(A, T);
  }
  reset_joysticks();
}

void egg_hatcher(int T, int egg_steps) {
  run_circles(T, egg_steps);
  wait();
}

void egg_hatcher_box(int T, int egg_steps) {
  int t = 200;
  for (int x = 0; x <= 5; x++){
    run_circles(T, egg_steps);
    led_progress(x, 5);
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
  int c = 0;
  for (int y = 0; y <= 4; y++) {
    for (int x = 0; x <= 5; x++) {
      c++;
      led_progress(c, 30);
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
            delay(800);
            break;
          case 7:
            delay(1400);
            break;
          case 9:
            delay(700);
            break;
        }
      }
    }
    if (y < 4) {  // Change orentiation and shift down, not on last row
      if (orientation == 1) orientation = 0;
      else  orientation = 1;
      dpad(DOWN, T);
    }
  }
  wait();
}

void shift_item(int T, int category) {  // starts looking at koraidon/miraidon
  // Boxes
  dpad(RIGHT, T);
  button(A, T);
  delay(1500);
  // Take item
  dpad(LEFT, T);
  dpad(DOWN, T);
  button(X, T);
  button(A, T);
  dpad(DOWN, T);
  dpad(DOWN, T);
  button(A, T);
  delay(500);
  // Give a new item
  button(A, T);
  button(A, T);
  delay(1200);
  for (int i = 0; i <= category; i++) dpad(RIGHT, T);  //2 Berrys | 3 Items | 4 TMs
  dpad(DOWN, T);
  button(A, T);
  button(A, T);
  delay(1200);
  button(B, T);
  button(B, T);
  delay(1200);
  button(B, T);
  delay(1200);
  dpad(LEFT, T);
}

void speedrun(int T) {
  while (true){
    button(A, T);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}

void regi_shiny_hunting(int T) {
  button(HOME, T);
  delay(500);
  button(X, T);
  for (int i = 1; i < (40000/T/2); i++)  button(A, T);
}

void zacianzamazenta_beastball(int T) {
  button(HOME, T);
  delay(500);
  button(X, T);
  for (int i = 1; i < (40000/T/2); i++)  button(A, T);
  for (int i = 1; i < (13000/T/2); i++)  button(X, T);
  button(X, T);
  delay(500);
  button(A, T);
  for (int i = 1; i < (18000/T/2); i++)  button(B, T);
  button(X, T);
  delay(500);
  button(A, T);
  for (int i = 1; i < (10000/T/2); i++)  button(B, T);
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
