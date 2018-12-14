#include "data.h"

#include "eeprom.h"
#include "constants.h"

#include <EEPROM.h>

Lazy<String> apPassword;
Lazy<String> wifiSsid;
Lazy<String> wifiPassword;
Lazy<String> nodeHost;
Lazy<byte> nodeTimeout;

Lazy<bool> wifiStatus;
Lazy<long> height;
Lazy<byte> nodeStatus;
Lazy<Version> version;
Lazy<String> date;
Lazy<String> timeStamp;

String getWiFiApPassword()
{
    return apPassword.isInit() ? apPassword.get() : readStringEEPROM(AP_PASSWORD_INDEX, AP_PASSWORD_LENGTH + 1);
}

void setWiFiApPassword(String value)
{
    apPassword.set(value);
    writeStringEEPROM(AP_PASSWORD_INDEX, value.c_str());
}

String getWiFiSsid()
{
    return wifiSsid.isInit() ? wifiSsid.get() : readStringEEPROM(WIFI_SSID_INDEX, WIFI_SSID_LENGTH + 1);
}

void setWiFiSsid(String value)
{
    wifiSsid.set(value);
    writeStringEEPROM(WIFI_SSID_INDEX, value.c_str());
}

String getWiFiPassword()
{
    return wifiPassword.isInit() ? wifiPassword.get() : readStringEEPROM(WIFI_PASSWORD_INDEX, WIFI_PASSWORD_LENGTH + 1);
}

void setWiFiPassword(String value)
{
    wifiPassword.set(value);
    writeStringEEPROM(WIFI_PASSWORD_INDEX, value.c_str());
}

String getNodeAddress()
{
    return nodeHost.isInit() ? nodeHost.get() : readStringEEPROM(NODE_HOST_INDEX, NODE_HOST_LENGTH + 1);
}

void setNodeAddress(String value)
{
    nodeHost.set(value);
    writeStringEEPROM(NODE_HOST_INDEX, value.c_str());
}

byte getNodeTimeout()
{
    return nodeTimeout.isInit() ? nodeTimeout.get() : readByteEEPROM(NODE_TIMEOUT_INDEX);
}

void setNodeTimeout(byte value)
{
    nodeTimeout.set(value);
    writeByteEEPROM(NODE_TIMEOUT_INDEX, value);
}