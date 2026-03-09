/*
 * FRLG Arduino assisted FlowTimer Switch edition
 */
#include <Streaming.h>
#include <EEPROM.h>

// Arduino variables
String inString1 = "";  // string to hold input
String inString2 = "";  // string to hold input
boolean shift = 0;
int last_char = 0;
int new_char = 0;
boolean serial_monitor = 0;
// Timing variables
const byte T = 100;
double timer_frame_ms_math = 0;
unsigned long timer_frame_ms = 0;
unsigned long timer_frame = 0;
unsigned long timer_seed = 0;
unsigned long offset_btn = 0;
int offset = 0;
// Game variables
int pkmn_select = 1;
// Button variables
const byte HOME = 2;
const byte UP = 3;
const byte RIGHT = 4;
const byte DOWN = 5;
const byte LEFT = 6;
const byte B = 7;
const byte A = 8;
const byte START = 9;
const byte X = 9;
const byte SELECT = 10;
const byte Y = 10;
const byte R = 11;
const byte L = 12;

// Analog
int sensorValue = 0;
const int analogInPin = A3;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  for (int i = 2; i <= 13; i++)  pinMode(i, OUTPUT);
  for (int i = 2; i <= 13; i++)  digitalWrite(i, HIGH);
  //digitalWrite(POWER, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      if ( shift == 0 ) inString1 += (char)inChar;
      else              inString2 += (char)inChar;
    }
    else  
    {
      switch (inChar) {
        case '/':
          shift++;
          break;
        case 'Z': // Demo
          while (true) {
            for (int i = 3; i <= 12; i++){
              digitalWrite(i, 0);
              delay(100);
              digitalWrite(i, 1);
              delay(100);
            }
          }
          break;
        case 'R':
          restart_game_fast();
          break;
        case 'z':
          button(HOME, T, T);
          break;
        case 'f':
          button(A, T, T);
          break;
        case 'r':
          button(B, T, T);
          break;
        case 'w':
          button(UP, T, T);
          break;
        case 's':
          button(DOWN, T, T);
          break;
        case 'a':
          button(LEFT, T, T);
          break;
        case 'd':
          button(RIGHT, T, T);
          break;
        case 'q':
          button(L, T, T);
          break;
        case 'e':
          button(R, T, T);
          break;
        case 'c':
          button(START, T, T);
          break;
        case 'x':
          button(SELECT, T, T);
          break;
        case '\n':
          //serial_monitor = 1;
          if (isDigit(last_char)) timer_update();
          break;
        case 'A': // To read the Analog pin and EEPROM
          sensorValue = analogRead(analogInPin);
          Serial << "Counter: " << eeread(0) << " byte(0): " << EEPROM.read(0) << " byte(1): " << EEPROM.read(1) << " | Analog Read: " << sensorValue << endl;
          break;
        case 'S': // Started via soft reset
          starter_sh();
          break;
        case '!':
          frlg_rng_starter();
          break;
        case '@':
          while (Serial.available() > 0)  inChar = Serial.read();
          pkmn_select = serial_input();
          frlg_gamecorner(pkmn_select);  // 1 Abra | 2 Clef | 3 Dratini | 4 Scy | 5 Pory
          break;
        case '#':
          frlg_sweet_scent();
          break;
        case '$':
          frlg_legendary();
          break;
        case '%':
          frlg_magikarp();
          break;
        case '*':
          for (int i = 1; i <= 2100; i++)  button(A, T, T); // 7 min of A spam
          break;
        case ',':
          frlg_new_save();
          name_patch();
          frlg_pid_sid();
          break;
        case '<':
          frlg_new_save();
          name_pau();
          frlg_pid_sid();
          break;
      }
    }
    last_char = inChar;
  }
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
    Serial << "Counter: " << eeread(0) << " byte(0): " << EEPROM.read(0) << " byte(1): " << EEPROM.read(1) << " | Analog Read: " << sensorValue << " | Previous Value: " << previous_value << endl;
    if (sensorValue < (previous_value - 6)) {  // Shiny found! ( diff is very small, 10 out of the 1024/5V scale)
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

void clear_variables() { 
  inString1 = "";
  inString2 = "";
  shift = 0;
}

void timer_update() {
  timer_frame = inString1.toInt();
  timer_seed = inString2.toInt();
  Serial << "FRLG timer: " << timer_frame << "/" << timer_seed << endl;
  clear_variables();
}

void restart_game_fast() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(X, LOW);
  digitalWrite(Y, LOW);
  delay(T);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(X, HIGH);
  digitalWrite(Y, HIGH);
  delay(T);
}

void restart_game() {
  button(HOME, T, T);
  delay(500);
  button(X, T, T);
  //for (int i = 1; i <= 15; i++)  button(A, T, T); // 3 Sec
  delay(500);
  button(A, T, T);
  delay(700);
  button(A, T, T);
  delay(1000);
  button(A, T, 0);
}

void poweron_sequence() {
  restart_game();
  offset = 4110;  // No GBA boot logo
  unsigned long timer_seed_fix = timer_seed - offset;
  //Serial << "timer_seed: " << timer_seed << " timer_seed_fix:" << timer_seed_fix << endl;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(timer_seed_fix);
  digitalWrite(LED_BUILTIN, LOW);
  button(A, 3500, 200);
  offset_btn = 0;
  button(A, T, T);
  for (int i = 1; i <= 17; i++)  button(B, T, T); // 4 Sec  Skip recap FRLG
}

void frlg_gamecorner(int select) {  // 1 Abra | 2 Clef | 3 Dratini | 4 Scy | 5 Pory
  int timer_offset = 111; //FR_Og
  timer_frame_ms_math = ((timer_frame + timer_offset) * 1000) / 60;
  timer_frame_ms = lround(timer_frame_ms_math); 
  Serial << "FRLG gamecorner: " << timer_frame_ms << "/" << timer_seed << " | Selected: " << pkmn_select << endl;
  poweron_sequence();
  for (int i = 1; i <= 7; i++)  button(A, T, T); 
  for (int i = 1; i <= select; i++)  button(DOWN, T, T);
  for (int i = 1; i <= 2; i++)  button(A, T, T);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(timer_frame_ms);
  digitalWrite(LED_BUILTIN, LOW);
  button(A, T, T);
  check_pkmn();
}

void frlg_sweet_scent() {
  int timer_offset = -231;  // FR_Og WIP
  timer_frame_ms_math = ((timer_frame + timer_offset) * 1000) / 60;
  timer_frame_ms = lround(timer_frame_ms_math); 
  Serial << "FRLG sweetscent: " << timer_frame_ms << "/" << timer_seed << endl;
  poweron_sequence();
  delay(100);
  button(START, T, T);
  button(DOWN, T, T);
  button(A, T, T);
  delay(1000);
  button(DOWN, T, T);
  button(A, T, T);
  button(DOWN, T, T);
  delay(timer_frame_ms - offset_btn);
  button(A, T, T);
}

int serial_input() {
  Serial << "FRLG selected: ";
  while (Serial.available() == 0) delay(100);
  int input_char2 = Serial.read() - '0';
  Serial << input_char2 << endl;
  return input_char2;
}

void check_pkmn() {
  for (int i = 1; i <= 20; i++)  button(B, T, T); // 4 Sec
  button(START, T, T);
  delay(100);
  button(DOWN, T, T);
  delay(300);
  button(A, T, T);
  delay(1500);
  button(UP, T, T);
  button(UP, T, T);
  for (int i = 1; i <= 3; i++)  button(A, T, T); // 1 Sec
  delay(5000);
  button(RIGHT, T, T);
}

void catch_pokemon() {
  for (int i = 1; i <= 55; i++)  button(B, T, T); // 11 Sec
  button(RIGHT, T, T);
  button(A, T, 2000);
  button(RIGHT, T, 1000);
  button(RIGHT, T, 1000);
  button(DOWN, T, 200);
  button(DOWN, T, 200);
  button(DOWN, T, 200);
  button(A, T, 200);
  button(A, T, 200);
  for (int i = 1; i <= 75; i++)  button(B, T, T); // 15 Sec
}

void frlg_legendary() { // $
  int timer_offset = 68; // 497 + 3 from (+24 ms delay) but reduced to 18 buttons from poweron_sequence
  timer_frame_ms_math = ((timer_frame - timer_offset) * 1000.0) / 120.0;
  Serial << "FRLG static_legendary: " << timer_frame_ms << "/" << timer_seed << endl;
  poweron_sequence();
  digitalWrite(LED_BUILTIN, HIGH);
  timer_frame_ms = timer_frame_ms_math - offset_btn; 
  delay(timer_frame_ms);
  digitalWrite(LED_BUILTIN, LOW);
  button(A, T, T);
  catch_pokemon(); // Birds
  check_pkmn();
}

void frlg_magikarp() {  // %
  int timer_offset = 0;
  timer_frame_ms_math = ((timer_frame + timer_offset) * 1000.0) / 120.0;
  Serial << "FRLG magikarp: " << timer_frame_ms << "/" << timer_seed << endl;
  poweron_sequence();
  for (int i = 1; i <= 15; i++)  button(A, T, T); 
  digitalWrite(LED_BUILTIN, HIGH);
  timer_frame_ms = timer_frame_ms_math - offset_btn; 
  delay(timer_frame_ms);
  digitalWrite(LED_BUILTIN, LOW);
  button(A, T, T);
  check_pkmn();
}

void frlg_rng_starter() {
  int timer_offset = 0;
  timer_frame_ms_math = ((timer_frame + timer_offset) * 1000.0) / 120.0;
  Serial << "FRLG starter: " << timer_frame_ms << "/" << timer_seed << endl;
  poweron_sequence();
  for (int i = 1; i <= 15; i++)  button(A, T, T); // 3 Sec
  timer_frame_ms = timer_frame_ms_math - offset_btn; 
  delay(timer_frame_ms);
  button(A, T, T);
  for (int i = 1; i <= 65; i++)  button(B, T, T); // 13 Sec
  button(START, T, T);
  delay(300);
  for (int i = 1; i <= 10; i++)  button(A, T, T); // 2 Sec
  delay(2000);
  button(RIGHT, T, T);
}

void name_puto() {
  for (int i = 1; i <= 2; i++)  button(DOWN, T, T);
  for (int i = 1; i <= 3; i++)  button(RIGHT, T, T);
  button(A, T, T);  // P
  for (int i = 1; i <= 2; i++)  button(LEFT, T, T);
  button(DOWN, T, T);
  button(A, T, T);  // u
  button(LEFT, T, T);
  button(A, T, T);  // t
  button(SELECT, T, T); // lowercase
  delay(500);
  button(SELECT, T, T); // Numbers
  delay(500);
  for (int i = 1; i <= 3; i++)  button(UP, T, T);
  button(A, T, T);  // 0
  button(START, T, T);
}

void name_patch() {
  for (int i = 1; i <= 2; i++)  button(DOWN, T, T);
  for (int i = 1; i <= 3; i++)  button(RIGHT, T, T);
  button(A, T, T);  // P
  button(SELECT, T, T); // lowercase
  delay(500);
  for (int i = 1; i <= 3; i++)  button(LEFT, T, T);
  for (int i = 1; i <= 2; i++)  button(UP, T, T);
  button(A, T, T);  // a
  for (int i = 1; i <= 3; i++)  button(DOWN, T, T);
  button(A, T, T);  // t
  for (int i = 1; i <= 3; i++)  button(UP, T, T);
  for (int i = 1; i <= 2; i++)  button(RIGHT, T, T);
  button(A, T, T);  // c 
  button(DOWN, T, T);
  button(LEFT, T, T);
  button(A, T, T);  // h
  button(START, T, T);
}

void name_pau() {
  for (int i = 1; i <= 2; i++)  button(DOWN, T, T);
  for (int i = 1; i <= 3; i++)  button(RIGHT, T, T);
  button(A, T, T);  // P
  button(SELECT, T, T); // lowercase
  delay(500);
  for (int i = 1; i <= 3; i++)  button(LEFT, T, T);
  for (int i = 1; i <= 2; i++)  button(UP, T, T);
  button(A, T, T);  // a
  for (int i = 1; i <= 3; i++)  button(DOWN, T, T);
  button(RIGHT, T, T);
  button(A, T, T);  // u
  button(START, T, T);
}

void frlg_pid_sid() {
  /*
  * Tools > Researcher https://www.youtube.com/watch?v=xXz2GCSy6HA
  * TID DEC to HEX, use as seed
  * Custom1 16Bit High / 1
  * Initial Advances 1147, or just 1149
  * Max Advances 5
  * Generate
  */
  int timer_offset = -243;  // don't remember
  //offset_btn = 6200; // Extra buttons delay in ms from rival name + delay before
  timer_frame_ms_math = ((1149.0 + timer_offset) * 1000.0) / 60.0;
  //timer_frame_ms = 15100;
  //timer_frame_ms = 15101;  //1149!! or 13.14273281 ms per frame

  for (int i = 1; i <= 33; i++) button(A, T, T); // 6.6 Sec
  delay(100);
  button(A, T, T);  // Rival name
  delay(900);
  name_puto();
  button(A, T, T);
  delay(300);

  for (int i = 1; i <= 24; i++) button(A, T, T); // 4.8 Sec
  timer_frame_ms = timer_frame_ms_math - offset_btn; 
  Serial << "timer_frame_ms: " << timer_frame_ms << " | offset_btn: " << offset_btn << endl;
  delay(timer_frame_ms);
  button(A, T, T);
  digitalWrite(LED_BUILTIN, HIGH);
  for (int i = 1; i <= 35; i++) button(B, T, T);
  button(START, T, T);
  button(DOWN, T, T);
  button(A, T, T);
  digitalWrite(LED_BUILTIN, LOW);
}

void frlg_new_save() {
  restart_game();
  for (int i = 1; i <= 43; i++)  button(A, T, T); // 8.4 Sec
  delay(400);
  button(DOWN, T, T);
  delay(400);
  for (int i = 1; i <= 113; i++) button(A, T, T); // 22.6 Sec
  delay(200);
  button(DOWN, T, T); // GIRL
  for (int i = 1; i <= 15; i++)  button(A, T, T); // 3 Sec
}

void button(int btn, int timing_on, int timing_off) {
  if (serial_monitor) Serial << "Button [" << btn << "]: on " << timing_on << endl;
  digitalWrite(btn, LOW);
  delay(timing_on);
  if (serial_monitor) Serial << "Button [" << btn << "]: off " << timing_off << endl;
  digitalWrite(btn, HIGH);
  delay(timing_off);
  offset_btn = offset_btn + timing_on + timing_off;
}

void eewrite(unsigned int value, int address) {
  EEPROM.write(address, value & 0xFF);
  EEPROM.write(address + 1, value >> 8);
}

unsigned int eeread(int address) {
  return  (EEPROM.read(address + 1) << 8) + EEPROM.read(address);
}