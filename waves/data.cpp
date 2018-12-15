#include "data.h"

#include "eeprom.h"
#include "constants.h"

#include <EEPROM.h>

Lazy<String> apPassword;
Lazy<String> wifiSsid;
Lazy<String> wifiPassword;
Lazy<String> nodeHost;
Lazy<uint16_t> nodePort;
Lazy<byte> nodeTimeout;
Lazy<String> otherHost;
Lazy<String> address;
Lazy<int> otherPort;
Lazy<String> balance;

Lazy<bool> wifiStatus;
Lazy<long> height;
Lazy<byte> nodeStatus;
Lazy<Version> version;
Lazy<String> date;
Lazy<String> timeStamp;
Lazy<int> peers;
Lazy<long> otherHeight;
Lazy<String> otherDate;
Lazy<String> otherTimeStamp;

BlockMaining blocks[BLOCKS_LENGTH] = {0, 0, 0};

String getWiFiApPassword()
{
    if (!apPassword.isInit())
        apPassword.set(readStringEEPROM(AP_PASSWORD_INDEX, AP_PASSWORD_LENGTH + 1));
    return apPassword.get();
}

void setWiFiApPassword(String value)
{
    apPassword.set(value);
    writeStringEEPROM(AP_PASSWORD_INDEX, value.c_str());
}

String getWiFiSsid()
{
    if (!wifiSsid.isInit())
        wifiSsid.set(readStringEEPROM(WIFI_SSID_INDEX, WIFI_SSID_LENGTH + 1));
    return wifiSsid.get();
}

void setWiFiSsid(String value)
{
    wifiSsid.set(value);
    writeStringEEPROM(WIFI_SSID_INDEX, value.c_str());
}

String getWiFiPassword()
{
    if (!wifiPassword.isInit())
        wifiPassword.set(readStringEEPROM(WIFI_PASSWORD_INDEX, WIFI_PASSWORD_LENGTH + 1));
    return wifiPassword.get();
}

void setWiFiPassword(String value)
{
    wifiPassword.set(value);
    writeStringEEPROM(WIFI_PASSWORD_INDEX, value.c_str());
}

String getNodeAddress()
{
    if (!nodeHost.isInit())
        nodeHost.set(readStringEEPROM(NODE_HOST_INDEX, NODE_HOST_LENGTH + 1));
    return nodeHost.get();
}

void setNodeAddress(String value)
{
    nodeHost.set(value);
    writeStringEEPROM(NODE_HOST_INDEX, value.c_str());
}

uint16_t getNodePort()
{
    if (!nodePort.isInit())
        nodePort.set(readUint16EEPROM(NODE_PORT_INDEX));
    return nodePort.get();
}

void setNodePort(uint16_t value)
{
    nodePort.set(value);
    writeUint16EEPROM(NODE_PORT_INDEX, value);
}

byte getNodeTimeout()
{
    if (!nodeTimeout.isInit())
        nodeTimeout.set(readByteEEPROM(NODE_TIMEOUT_INDEX));
    return nodeTimeout.get();
}

void setNodeTimeout(byte value)
{
    nodeTimeout.set(value);
    writeByteEEPROM(NODE_TIMEOUT_INDEX, value);
}

String getOtherNodeAddress()
{
    if (!otherHost.isInit())
        otherHost.set(readStringEEPROM(NODE_OTHER_HOST_INDEX, NODE_OTHER_HOST_LENGTH + 1));
    return otherHost.get();
}

void setOtherNodeAddress(String value)
{
    otherHost.set(value);
    writeStringEEPROM(NODE_OTHER_HOST_INDEX, value.c_str());
}

uint16_t getOtherNodePort()
{
    if (!otherPort.isInit())
        otherPort.set(readUint16EEPROM(NODE_OTHER_PORT_INDEX));
    return otherPort.get();
}

void setOtherNodePort(uint16_t value)
{
    otherPort.set(value);
    writeUint16EEPROM(NODE_OTHER_PORT_INDEX, value);
}

String getAddress()
{
    if (!address.isInit())
        address.set(readStringEEPROM(ADDRESS_INDEX, ADDRESS_LENGTH + 1));
    return address.get();
}

void setAddress(String value)
{
    address.set(value);
    writeStringEEPROM(ADDRESS_INDEX, value.c_str());
}

String getMainingString(BlockMaining blocks[])
{
    String result;

    for (int i = 0; i < BLOCKS_LENGTH; i++)
    {
        if (blocks[i].start == 0 && blocks[i].stop == 0)
        {
            result += "";
        }
        else if (blocks[i].value > 0)
        {
            result += "#";
        }
        else
        {
            result += ".";
        }
    }

    return result;
}