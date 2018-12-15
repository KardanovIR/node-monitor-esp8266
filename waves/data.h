#include "Arduino.h"
#include "lazy.h"

static const int BLOCKS_LENGTH = 25;
static const int BLOCK_GET_LENGTH = 10;

struct Version
{
    int major;
    int minor;
    int fix;
};

struct BlockMaining
{
    int start;
    int stop;
    int value;
};

extern Lazy<bool> wifiStatus;
extern Lazy<long> height;
extern Lazy<byte> nodeStatus;
extern Lazy<Version> version;
extern Lazy<String> date;
extern Lazy<String> timeStamp;
extern Lazy<int> peers;
extern Lazy<String> balance;

extern Lazy<long> otherHeight;
extern Lazy<String> otherDate;
extern Lazy<String> otherTimeStamp;
extern BlockMaining blocks[BLOCKS_LENGTH];

String getWiFiApPassword();
void setWiFiApPassword(String value);

String getWiFiSsid();
void setWiFiSsid(String value);

String getWiFiPassword();
void setWiFiPassword(String value);

String getNodeAddress();
void setNodeAddress(String value);

uint16_t getNodePort();
void setNodePort(uint16_t value);

byte getNodeTimeout();
void setNodeTimeout(byte value);

String getOtherNodeAddress();
void setOtherNodeAddress(String value);

uint16_t getOtherNodePort();
void setOtherNodePort(uint16_t value);

String getAddress();
void setAddress(String value);

String getMainingString(BlockMaining[]);