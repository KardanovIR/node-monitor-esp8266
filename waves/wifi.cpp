#include "wifi.h"
#include <Arduino.h>

#include "constants.h"
#include "eeprom.h"
#include "console.h"

void initAP()
{
  String apPassword = readStringEEPROM(AP_PASSWORD_INDEX, AP_PASSWORD_LENGTH);
  if (apPassword.length() == 0)
  {
    writeStringEEPROM(AP_PASSWORD_INDEX, AP_PASSWORD_DEFAULT);
    readStringEEPROM(AP_PASSWORD_INDEX, AP_PASSWORD_LENGTH);
  }

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  IPAddress ip = WiFi.softAP(AP_SSID, apPassword.c_str());

  Serial.printf_P(PSTR("AP SSID: %s\n"), AP_SSID);
  Serial.printf_P(PSTR("AP PASSWORD: %s\n"), apPassword.c_str());
  Serial.printf_P(PSTR("AP IP: %s\n"), ip.toString().c_str());
  printDelemiter();
}

void initSTA()
{
  String password = readStringEEPROM(WIFI_PASSWORD_INDEX, WIFI_PASSWORD_LENGTH);
  String ssid = readStringEEPROM(WIFI_SSID_INDEX, WIFI_SSID_LENGTH);
  WiFi.begin(ssid.c_str(), password.c_str());
}

void initWiFi()
{
  WiFi.disconnect(true);
  WiFi.mode(WIFI_AP_STA);
  initAP();
  initSTA();
}