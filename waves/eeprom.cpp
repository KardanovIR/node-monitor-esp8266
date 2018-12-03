#include "eeprom.h"
#include <EEPROM.h>
#include <Arduino.h>

#include "buffer.h"

void initEEPROM()
{
    EEPROM.begin(100);
}

char *readStringEEPROM(int startIndex, int maxLength)
{
    clearBuffer();
    byte length = EEPROM.read(startIndex);

    // If incorrect length
    if (length <= 0 || length > maxLength)
        return getBuffer();

    for (int i = 0; i < length; i++)
    {
        getBuffer()[i] = (char)EEPROM.read(i + startIndex + 1);
        if (getBuffer()[i] == 0)
            break;
    }

    return getBuffer();
}

void writeStringEEPROM(int index, const char *data)
{
    EEPROM.write(index, strlen(data));
    for (int i = 0; i <= strlen(data); i++)
    {
        EEPROM.write(i + index + 1, (uint8_t)data[i]);
    }
    EEPROM.commit();
}