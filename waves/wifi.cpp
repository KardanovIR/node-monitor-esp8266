#include "wifi.h"
#include <Arduino.h>

#include "constants.h"
#include "eeprom.h"
#include "console.h"
#include "buffer.h"

void initAP()
{
  if (!strlen(readStringEEPROM(AP_PASSWORD_INDEX, AP_PASSWORD_LENGTH)))
  {
    writeStringEEPROM(AP_PASSWORD_INDEX, AP_PASSWORD_DEFAULT);
    readStringEEPROM(AP_PASSWORD_INDEX, AP_PASSWORD_LENGTH);
  }

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  IPAddress ip = WiFi.softAP(AP_SSID, getBuffer());

  Serial.printf_P(PSTR("AP SSID: %s\n"), AP_SSID);
  Serial.printf_P(PSTR("AP PASSWORD: %s\n"), getBuffer());
  Serial.printf_P(PSTR("AP IP: %s\n"), ip.toString().c_str());
  printDelemiter();
}

void initWiFi()
{
  initEEPROM();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP);
  initAP();
}