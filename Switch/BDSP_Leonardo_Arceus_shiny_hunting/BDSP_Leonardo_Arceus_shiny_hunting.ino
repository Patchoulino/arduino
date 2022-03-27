/*
 * BDSP Arceus shiny hunting
 * buttons needed
 * HOME X A UP
*/

const int T = 300;
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

  if (testAutoSendMode)
  {
    Joystick.begin();
  }
  else
  {
    Joystick.begin(false);
  }

  Joystick.setXAxis(128);
  Joystick.setYAxis(128);
  Joystick.setZAxis(128);
  Joystick.setRzAxis(128);
  Joystick.sendState();

  /* for some reason Joystick won't listen to the buttons from void loop()
   *  even if you try a delay of 1, 2 or 3 sec, it won't listen..
   *  but if you do 2 button presses with a decent delay then
   *  it will listen to the buttons on the main void loop()
   */
  for (int i = 0; i <= 1; i++){
    dpad(DOWN, T);
  }

}

void loop() { // Start at battle with arceus so reset of the arduino will open home and restart game
  // Restart game
  button(HOME, T);
  delay(500);
  button(X, T);
  //button(A, T);
  //button(A, T);
  //button(A, T);

  for (int i = 0; i <= (40000/T/2); i++){ // 40 sec to load 
    button(A, T);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  dpad(UP, T); // Walk to god

  for (int i = 0; i <= (17500/T/2); i++){ // 17.5 sec Arceus animation
    button(A, T);
  }

  while (true) { // Blink LED_BUILTIN waiting for a reset
    button_old(LED_BUILTIN, 100);
  }
  
}

void button(int btn, int timing) {
  Joystick.pressButton(btn);
  //Joystick.sendState();
  delay(timing);
  Joystick.releaseButton(btn);
  //Joystick.sendState();
  delay(timing);
}

void dpad(int btn, int timing) {
  Joystick.setHatSwitch(btn);
  //Joystick.sendState();
  delay(timing);
  Joystick.setHatSwitch(RELEASE);
  //Joystick.sendState();
  delay(timing);
}

void button_old(int btn, int timing) {
  digitalWrite(btn, LOW);
  delay(timing);
  digitalWrite(btn, HIGH);
  delay(timing);
}
