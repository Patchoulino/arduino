#include <EEPROM.h>
#include <Streaming.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  Serial << "EEPROM length: " << EEPROM.length() << endl;
  
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  eewrite(eeread(0) + 1, 0);
  Serial << "Int: " << eeread(0) << " byte(0): " << EEPROM.read(0) << " byte(1): " << EEPROM.read(1) << endl;
  delay(500);
}

void eewrite(unsigned int value, int address) {
  EEPROM.write(address, value & 0xFF);
  EEPROM.write(address + 1, value >> 8);
}

unsigned int eeread(int address) {
  return  (EEPROM.read(address + 1) << 8) + EEPROM.read(address);
}
