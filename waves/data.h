#include "Arduino.h"
#include "lazy.h"

struct Version
{
    int major;
    int minor;
    int fix;
};

extern Lazy<bool> wifiStatus;
extern Lazy<long> height;
extern Lazy<byte> nodeStatus;
extern Lazy<Version> version;
extern Lazy<String> date;
extern Lazy<String> timeStamp;

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