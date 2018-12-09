#include "Arduino.h"
#include "lazy.h"

extern Lazy<bool> wifiStatus;
extern Lazy<long> height;

String getWiFiApPassword();
void setWiFiApPassword(String value);

String getWiFiSsid();
void setWiFiSsid(String value);

String getWiFiPassword();
void setWiFiPassword(String value);

String getNodeAddress();
void setNodeAddress(String value);

byte getNodeTimeout();
void setNodeTimeout(byte value);