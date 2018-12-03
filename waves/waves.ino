#include "nodemcu.h"
#include "dns.h"
#include "server.h"
#include "eeprom.h"
#include "wifi.h"

void setup()
{
    Serial.begin(9600);
    Serial.println();

    initEEPROM();

    printHardwareInformation();
    initWiFi();
    initServer();
    initDNS();
}

void loop()
{
    handleServer();
    handleDNS();
}
