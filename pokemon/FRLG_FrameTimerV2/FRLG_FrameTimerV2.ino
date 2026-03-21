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
        case 'Z': // Demo press all buttons
          while (true) {
            for (int i = 3; i <= 12; i++){
              digitalWrite(i, LOW);
              delay(100);
              digitalWrite(i, HIGH);
              delay(100);
            }
          }
          break;
        case 'b':
          restart_game_fast();
          break;
        case 'B':
          restart_game();
          break;
        case '!':
          frlg_rng_starter();
          break;
        case '@':
          while (Serial.available() > 0)  inChar = Serial.read();
          pkmn_select = serial_input();
          frlg_gamecorner(pkmn_select);  // 0 Abra | 1 Clef | 2 Dratini | 3 Scy | 4 Pory
          break;
        case '#':
          frlg_sweet_scent();
          break;
        case '$':
          frlg_legendary();
          break;
        case 'E':
          frlg_eevee();
          break;
        case 'I':
          frlg_hitmon();
          break;
        case 'A':
          frlg_lapras();
          break;
        case 'm':
          frlg_magikarp();
          break;
        case 'S':
          frlg_snorlax();
          break;
        case 'D':
          frlg_deoxys();
          break;
        case 'U':
          frlg_lugia();
          break;
        case 'H':
          frlg_hooh();
          break;
        case 'O':
          frlg_roaming();
          break;
        case 'M':
          frlg_mewtwo();
          break;
        case 'F':
          frlg_fossils();
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

int serial_input() {
  Serial << "FRLG selected: ";
  while (Serial.available() == 0) delay(100);
  int input_char2 = Serial.read() - '0';
  Serial << input_char2 << endl;
  return input_char2;
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

void frlg_rng_starter() { // ! This POKeMON is really quite energetic!
  frlg_rng(A, 46, A, 15, "FRLG starter"); 
  for (int i = 1; i <= 65; i++)  button(B, T, T); // 13 Sec
  button(START, T, T);  // No Pokedex so can't use check_pkmn()
  delay(300);
  for (int i = 1; i <= 10; i++)  button(A, T, T); // 2 Sec
  delay(2000);
  button(RIGHT, T, T);
}

void frlg_fossils() { // F  Your fossil is back to life! It was ___ like I think!
  frlg_rng(A, 47, A, 4, "FRLG Fossils");
  check_pkmn();
}

void frlg_mewtwo() { // M
  frlg_rng(A, 288, A, 0, "FRLG Mewtwo");
  catch_pokemon();
  check_pkmn();
}

void frlg_roaming() { // F Thanks to you, my dream came true... so can't hit below 1560~
  frlg_rng(A, 59, A, 90, "FRLG Roaming legendary");
  digitalWrite(LEFT, LOW);  // Leave the building
  delay(1400);
  digitalWrite(LEFT, HIGH);
  digitalWrite(DOWN, LOW);
  delay(2500);
  digitalWrite(DOWN, HIGH);
}

void frlg_hooh() { // H
  frlg_rng(UP, 813, A, 0, "FRLG Ho-oH");
  //for (int i = 1; i <= 20; i++)  button(B, T, T); 
  catch_pokemon();
  check_pkmn();
}

void frlg_lugia() { // U
  frlg_rng(A, 610, A, 0, "FRLG Lugia");
  //for (int i = 1; i <= 15; i++)  button(B, T, T); 
  catch_pokemon();
  check_pkmn();
}

void frlg_deoxys() { // D
  frlg_rng(A, 1058, A, 0, "FRLG Deoxys");
  //for (int i = 1; i <= 25; i++)  button(B, T, T); 
  catch_pokemon();
  check_pkmn();
}

void frlg_snorlax() {  // S
  frlg_rng(A, 64, A, 25, "FRLG Snorlax");
  catch_pokemon();
  check_pkmn();
}

void frlg_magikarp() {  // M
  frlg_rng(A, 64, A, 15, "FRLG Magikarp");
  check_pkmn();
}

void frlg_lapras() { // L
  frlg_rng(A, 64, A, 10, "FRLG Lapras");
  //for (int i = 1; i <= 15; i++)  button(B, T, T); 
  check_pkmn();
}

void frlg_hitmon() { // H
  frlg_rng(A, 71, A, 1, "FRLG Hitmon");
  //for (int i = 1; i <= 5; i++)  button(B, T, T); 
  check_pkmn();
}

void frlg_eevee() { // E
  frlg_rng(A, 68, A, 0, "FRLG Eevee");
  //for (int i = 1; i <= 5; i++)  button(B, T, T); 
  check_pkmn();
}

void frlg_legendary() { // $
  frlg_rng(A, 68, A, 0, "FRLG static_legendary");
  catch_pokemon();
  check_pkmn();
}

void frlg_gamecorner(int select) {  // @0 Abra | @1 Clef | @2 Dratini | @3 Scy | @4 Pory
  int timer_offset = 41;
  timer_frame_ms_math = ((timer_frame - timer_offset) * 1000.0) / 120.0;
  Serial << "FRLG gamecorner: " << timer_frame_ms_math << "/" << timer_seed << endl;
  poweron_sequence();

  for (int i = 1; i <= 7; i++)  button(A, T, T); 
  for (int i = 1; i <= select; i++)  button(DOWN, T, T);
  for (int i = 1; i <= 2; i++)  button(A, T, T);
  digitalWrite(LED_BUILTIN, HIGH);
  timer_frame_ms = timer_frame_ms_math - offset_btn; // -5600 from button presses
  delay(timer_frame_ms);
  digitalWrite(LED_BUILTIN, LOW);
  button(A, T, T);
  Serial << "FRLG Debug: " << timer_frame_ms << "ms | " << timer_frame_ms_math << "/" << timer_seed << endl;

  check_pkmn();
}

void frlg_rng(byte BTN, int timer_offset, byte BTN2, int loop, String message){
  timer_frame_ms_math = ((timer_frame - timer_offset) * 1000.0) / 120.0;
  Serial << message << ": " << timer_frame_ms_math << "/" << timer_seed << endl;
  poweron_sequence();

  for (int i = 1; i <= loop; i++)  button(BTN2, T, T); 

  digitalWrite(LED_BUILTIN, HIGH);
  timer_frame_ms = timer_frame_ms_math - offset_btn;
  delay(timer_frame_ms);
  digitalWrite(LED_BUILTIN, LOW);
  button(BTN, T, T);
  Serial << "FRLG Debug: " << timer_frame_ms << "ms | " << timer_frame_ms_math << "/" << timer_seed << endl;
}

void poweron_sequence() {
  restart_game();
  //offset = 4110;  // No GBA boot logo
  offset = 336; // old 417 | 428 FR || LG 352 336
  unsigned long timer_seed_fix = timer_seed - offset_btn + offset;
  //Serial << "timer_seed: " << timer_seed << " timer_seed_fix:" << timer_seed_fix << endl;
  delay(timer_seed_fix);
  digitalWrite(LED_BUILTIN, LOW);
  button(A, 3200, 200);   // 3500 OG
  offset_btn = 0;
  delay(16); // TO SKIP FRAMES AT TITLE SCREEN BEFORE SELECT/START
  button(A, T, T);
  for (int i = 1; i <= 17; i++)  button(B, T, T); // 4 Sec  Skip recap FRLG
}

void restart_game() {
  button(HOME, T, T);
  delay(500);
  button(X, T, T);
  delay(500);
  button(A, T, T);
  delay(700);
  button(A, T, T);
  delay(1000);
  button(A, T, T);

  delay(1000);
  button(HOME, T, T);
  delay(1500);
  offset_btn = 40;  // To match seeds, removed 1s delay and adding button as well, 1240ms total
  digitalWrite(LED_BUILTIN, HIGH);
  button(HOME, T, T);
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
  for (int i = 1; i <= 65; i++)  button(B, T, T);
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
  pause(500);
  button(SELECT, T, T); // Numbers
  pause(500);
  for (int i = 1; i <= 3; i++)  button(UP, T, T);
  button(A, T, T);  // 0
  button(START, T, T);
}

void name_bitch() {
  button(RIGHT, T, T);
  button(A, T, T);  // B
  button(SELECT, T, T); // lowercase
  pause(500);
  button(SELECT, T, T); // Numbers
  pause(500);
  button(A, T, T);  // 1
  button(SELECT, T, T); // uppercase
  pause(500);
  for (int i = 1; i <= 3; i++)  button(DOWN, T, T);
  button(LEFT, T, T);
  button(A, T, T);  // T
  for (int i = 1; i <= 2; i++)  button(RIGHT, T, T);
  for (int i = 1; i <= 3; i++)  button(UP, T, T);
  button(A, T, T);  // C
  button(DOWN, T, T);
  button(LEFT, T, T);
  button(A, T, T);  // H
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
  //int timer_offset = -243;  // don't remember
  //timer_frame_ms_math = ((1149.0 + timer_offset) * 1000.0) / 60.0;
  //timer_frame_ms = 15100;
  //timer_frame_ms = 15101;  //1149!! or 13.14273281 ms per frame
  timer_frame_ms_math = (2300.0 * 1000.0) / 120.0;
  offset_btn = 0;

  for (int i = 1; i <= 33; i++) button(A, T, T); // 6.6 Sec
  pause(100);
  button(A, T, T);  // Rival name
  pause(900);
  //name_puto();
  name_bitch();
  button(A, T, T);
  pause(300);

  for (int i = 1; i <= 24; i++) button(A, T, T); // 4.8 Sec
  timer_frame_ms = timer_frame_ms_math - offset_btn; 
  Serial << "timer_frame_ms: " << timer_frame_ms << " | offset_btn: " << offset_btn << " | timer_frame_ms_math: "<< timer_frame_ms_math << endl;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(timer_frame_ms);
  button(A, T, T);
  digitalWrite(LED_BUILTIN, LOW);
  for (int i = 1; i <= 35; i++) button(B, T, T);
  button(START, T, 200);
  button(DOWN, T, T);
  button(A, T, T);
}

void frlg_new_save() {
  restart_game_fast();
  for (int i = 1; i <= 31; i++)  button(A, T, T);
  delay(400);
  button(DOWN, T, T);
  delay(400);
  for (int i = 1; i <= 113; i++) button(A, T, T); // 22.6 Sec
  delay(200);
  button(DOWN, T, T); // GIRL
  for (int i = 1; i <= 15; i++)  button(A, T, T); // 3 Sec
}

void pause(int time) {
  delay(time);
  offset_btn = offset_btn + time;
}

void button(int btn, int timing_on, int timing_off) {
  //if (serial_monitor) Serial << "Button [" << btn << "]: on " << timing_on << endl;
  digitalWrite(btn, LOW);
  delay(timing_on);
  //if (serial_monitor) Serial << "Button [" << btn << "]: off " << timing_off << endl;
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