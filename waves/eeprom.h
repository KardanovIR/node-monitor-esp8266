#include <Arduino.h>

String readStringEEPROM(int startIndex, int maxLength);
void writeStringEEPROM(int index, const char *data);
byte readByteEEPROM(int index);
void writeByteEEPROM(int index, byte data);