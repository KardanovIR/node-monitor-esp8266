#include "node.h"

#include "data.h"
#include "http.h"
#include "constants.h"

#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

WiFiClient client;
WiFiClientSecure clientSecure;
HTTPClient http;

StaticJsonBuffer<2048> buffer;

enum ParseState
{
    WAITING_VERSION,
    PARSE_END,
    PARSE_VERSION
};

Version stringToVersion(String str)
{
    Version v = {0, 0, 0};
    String temp;
    int stage = 0;
    ParseState s = WAITING_VERSION;
    while (s != PARSE_END)
    {
        switch (s)
        {
        case WAITING_VERSION:
        {
            if (str.length() >= 6)
            {
                if (str[0] == 'v' && DIGITS.indexOf(str[1]) != -1)
                    s = PARSE_VERSION;

                str.remove(0, 1);
            }
            else
                s = PARSE_END;
            break;
        }
        case PARSE_VERSION:
        {
            if (str.length())
            {
                if (DIGITS.indexOf(str[0]) != -1)
                {
                    temp += str[0];
                }
                else if (str[0] == '.')
                {
                    switch (stage)
                    {
                    case 0:
                    {
                        v.major = temp.toInt();
                        break;
                    }
                    case 1:
                    {
                        v.minor = temp.toInt();
                        break;
                    }
                    case 2:
                    {
                        v.fix = temp.toInt();
                        break;
                    }
                    default:
                        s = PARSE_END;
                    }
                    temp = "";
                    stage++;
                }
                str.remove(0, 1);
            }
            else
            {
                if (stage == 2)
                {
                    v.fix = temp.toInt();
                }
                s = PARSE_END;
            }
            break;
        }
        }
    }

    return v;
}

void updateHeight()
{
    String res = get(getNodeAddress() + "/node/status", http);
    if (res.length() > 10)
    {
        nodeStatus.set(2);
        buffer.clear();
        JsonObject &root = buffer.parseObject(res);
        height.set(root[AJAX_HEIGHT]);
        date.set(root[AJAX_DATE]);
        timeStamp.set(root[AJAX_TIMESTAMP]);
    }
}

void updateVersion()
{
    String res = get(getNodeAddress() + "/node/version", http);
    if (res.length() > 10)
    {
        nodeStatus.set(2);
        buffer.clear();
        JsonObject &root = buffer.parseObject(res);
        version.set(stringToVersion(root[AJAX_VERSION]));
    }

    // if (clientSecure.verify(GITHUB_FINGER_PRINT, "api.github.com"))
    // {
    //     clientSecure.print(String("GET ") + "/repos/wavesplatform/Waves/releases/latest" + " HTTP/1.1\r\n" + "Host: " + "api.github.com" + "\r\n" + "User-Agent: BuildFailureDetectorESP8266\r\n" + "Connection: close\r\n\r\n");
    //     while (clientSecure.connected())
    //     {
    //         String line = clientSecure.readStringUntil('\n');
    //         if (line == "\r")
    //             break;
    //     }

    //     String line = clientSecure.readStringUntil('\r');
    //     Serial.println(line);
    // } else {
    //     Serial.println("NOOOO");
    // }
}

void updatePeers()
{
    Serial.println(getNodeAddress().c_str());
    if (client.connect(getNodeAddress().c_str(), 80))
    {
        client.print(String("GET /peers/conected HTTP/1.1\r\nHost:" + getNodeAddress() + "\r\nUser-Agent: ESP8266\r\nConnection: close\r\n\r\n"));
        while (client.connected())
        {
            String line = client.readStringUntil('\n');
            if (line == "\r")
                break;

            line = client.readStringUntil('}');
            Serial.println(line);
        }
    } else {
        Serial.println("NO CONNECT");
    }
    // String res = get(getNodeAddress() + "/peers/connected", http);
    // if (res.length() > 10)
    // {
    //     nodeStatus.set(2);
    //     int count = 0;
    //     for (int i = 0; i < res.length(); i++)
    //     {
    //         if (res[i] == '{')
    //         {
    //             count++;
    //         }
    //     }
    //     peers.set(count > 1 ? count - 1 : 0);
    // }
}

void updateNodeInformation()
{
    updateHeight();
    updateVersion();
    updatePeers();
}