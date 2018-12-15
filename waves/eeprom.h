#include <Arduino.h>

String readStringEEPROM(int startIndex, int maxLength);
void writeStringEEPROM(int index, const char *data);
byte readByteEEPROM(int index);
void writeByteEEPROM(int index, byte data);
uint16_t readUint16EEPROM(int index);
void writeUint16EEPROM(int index, uint16_t data);