#include "eeprom.h"
#include <EEPROM.h>
#include <Arduino.h>

void initEEPROM()
{
    EEPROM.begin(512);
}

void endEEPROM()
{
    EEPROM.end();
}

String readStringEEPROM(int startIndex, int maxLength)
{
    initEEPROM();
    String result;
    byte length = EEPROM.read(startIndex);

    // If incorrect length
    if (length <= 0 || length > maxLength)
        return result;

    for (int i = 0; i < length; i++)
    {
        char s = (char)EEPROM.read(i + startIndex + 1);
        if (s == 0 || s == 255)
            break;
        else
            result += s;
    }
    endEEPROM();

    return result;
}

void writeStringEEPROM(int index, const char *data)
{
    initEEPROM();
    EEPROM.write(index, strlen(data));
    for (int i = 0; i <= strlen(data); i++)
    {
        EEPROM.write(i + index + 1, (uint8_t)data[i]);
    }
    EEPROM.commit();
    endEEPROM();
}

byte readByteEEPROM(int index)
{
    initEEPROM();
    byte result = EEPROM.read(index);
    endEEPROM();
    return result;
}

void writeByteEEPROM(int index, byte data)
{
    initEEPROM();
    EEPROM.write(index, data);
    EEPROM.commit();
    endEEPROM();
}