/*
 * FRLG Arduino assisted FlowTimer
 */
#include <Streaming.h>

// Bootleg variables
const boolean bootleg = 1;  // 0 being the original
const int bootleg_loop = 9; // 8 FR | 9 LG
// Arduino variables
String inString1 = "";  // string to hold input
String inString2 = "";  // string to hold input
boolean shift = 0;
int last_char = 0;
int new_char = 0;
boolean serial_monitor = 0;
// Timing variables
const byte T = 100;
double timer_frame_ms = 0;
unsigned long timer_frame = 0;
unsigned long timer_seed = 0;
unsigned long offset_btn = 0;
int offset = 0;
// Game variables
int pkmn_select = 1;
// Button variables
const byte POWER = 2;
const byte START = 5;
const byte SELECT = 3;
const byte A = 11;
const byte B = 10;
const byte UP = 4;
const byte DOWN = 7;
const byte LEFT = 6;
const byte RIGHT = 8;
const byte L = 9;
const byte R = 12;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  for (int i = 2; i <= 13; i++)  pinMode(i, OUTPUT);
  for (int i = 3; i <= 13; i++)  digitalWrite(i, HIGH);
  digitalWrite(POWER, LOW);
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
        case 'Z':
          digitalWrite(POWER, !digitalRead(POWER));
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
          frlg_static_legendary();
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
        case '.':
          frlg_pid_sid();
          break;
      }
    }
    last_char = inChar;
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

void poweron_sequence() {
  digitalWrite(POWER, HIGH);
  delay(1000);
  digitalWrite(POWER, LOW);
  delay(100);
  digitalWrite(POWER, HIGH);
  offset = -469;
  if (bootleg) {
    switch (bootleg_loop) {
      case 8: // FR
        offset = -101;
        break;
      case 9: // LG
        offset = 486;
        break;
    }
  }
  delay(timer_seed + offset);
  offset_btn = 0;
  button(A, 3500, 200);
  button(A, T, T);
  if (bootleg) for (int i = 1; i <= bootleg_loop; i++)  button(A, T, T);
  for (int i = 1; i <= 17; i++)  button(B, T, T); // 4 Sec
}

void frlg_rng_starter() {
  int timer_offset = 102; //LG
  timer_frame_ms = ((timer_frame + timer_offset) * 1000) / 60;
  Serial << "FRLG starter: " << timer_frame_ms << "/" << timer_seed << endl;
  poweron_sequence();
  for (int i = 1; i <= 15; i++)  button(A, T, T); // 3 Sec
  //if (bootleg)  offset = 34;
  //else          offset = 66;
  delay(timer_frame_ms - offset_btn);
  button(A, T, T);
  for (int i = 1; i <= 65; i++)  button(B, T, T); // 13 Sec
  button(START, T, T);
  delay(300);
  for (int i = 1; i <= 10; i++)  button(A, T, T); // 2 Sec
  delay(2000);
  button(RIGHT, T, T);
}

void frlg_gamecorner(int select) {  // 1 Abra | 2 Clef | 3 Dratini | 4 Scy | 5 Pory
  int timer_offset = 111; //FR_Og
  timer_frame_ms = ((timer_frame + timer_offset) * 1000) / 60;
  Serial << "FRLG gamecorner: " << timer_frame_ms << "/" << timer_seed << " | Selected: " << pkmn_select << endl;
  poweron_sequence();
  for (int i = 1; i <= 7; i++)  button(A, T, T); 
  for (int i = 1; i <= select; i++)  button(DOWN, T, T);
  for (int i = 1; i <= 2; i++)  button(A, T, T);
  //if (bootleg)  offset = 34;
  //else          offset = 66;
  delay(timer_frame_ms - offset_btn);
  button(A, T, T);
  for (int i = 1; i <= 20; i++)  button(B, T, T); // 4 Sec
  button(START, T, T);
  delay(100);
  button(DOWN, T, T);
  delay(300);
  for (int i = 1; i <= 10; i++)  button(A, T, T); // 2 Sec
  for (int i = 1; i <= 13; i++)  button(DOWN, T, T);
  delay(2000);
  button(RIGHT, T, T);
  delay(2000);
}

void frlg_static_legendary() {
  int timer_offset = -10; // FR_Og
  timer_frame_ms = ((timer_frame + timer_offset) * 1000) / 60;
  Serial << "FRLG static_legendary: " << timer_frame_ms << "/" << timer_seed << endl;
  poweron_sequence();
  delay(timer_frame_ms - offset_btn);
  button(A, T, T);
  for (int i = 1; i <= 20; i++)  button(B, T, T); // 4 Sec
}

void frlg_sweet_scent() {
  int timer_offset = -240;  // FR_Og WIP
  timer_frame_ms = ((timer_frame + timer_offset) * 1000) / 60;
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
  //if (bootleg)  offset = 34;
  //else          offset = 66;
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

void frlg_new_save() {
  button(POWER, T, T);
  for (int i = 1; i <= 57; i++)  button(A, T, T); // 11.4 Sec
  if (bootleg) for (int i = 1; i <= bootleg_loop; i++)  button(A, T, T);
  button(DOWN, T, T);
  for (int i = 1; i <= 117; i++) button(A, T, T); // 23.4 Sec
  delay(200);
  button(DOWN, T, T); // GIRL
  for (int i = 1; i <= 15; i++)  button(A, T, T); // 3 Sec
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
    * Tools > Researcher
    * TID DEC to HEX, use as seed
    * Custom1 16Bit High / 1
    * Initial Advances 1147, or just 1149
    * Max Advances 5
    * Generate
    */
   int flatms = 15101;  //1149!! or 13.14273281 ms per frame
   offset_btn = 0;
   for (int i = 1; i <= 33; i++) button(A, T, T); // 6.6 Sec
   button(DOWN, T, T);
   for (int i = 1; i <= 24; i++) button(A, T, T); // 4.8 Sec
   delay(flatms - offset_btn);
   button(A, T, T);
   for (int i = 1; i <= 35; i++) button(B, T, T);
   button(START, T, T);
   button(DOWN, T, T);
   button(A, T, T);
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
