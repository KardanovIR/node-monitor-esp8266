#include "node.h"

#include "data.h"
#include "http.h"
#include "constants.h"
#include "alarm.h"
#include "display.h"

#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

WiFiClient client;
HTTPClient http;

int needUpdatePeer = 0;
int needUpdateMainingHistory = 0;
const int UPDATE_TIME_PEER = 10;
const int UPDATE_TIME_MAINING_HISTORY = 10;
bool fullBlockHistory = false;
const int MAX_HEIGHT_DIFFERENCE = 5;
int lastMainingCount = 0;

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

bool updateHeight()
{
    String res = get(getNodeAddress(), getNodePort(), "/node/status", http);
    if (res.length() > 10)
    {
        nodeStatus.set(2);
        StaticJsonBuffer<1024> buffer;
        JsonObject &root = buffer.parseObject(res);
        height.set(root[AJAX_HEIGHT]);
        date.set(root[AJAX_DATE]);
        timeStamp.set(root[AJAX_TIMESTAMP]);
    }
    else
    {
        return false;
    }

    return true;
}

void updateOtherHeight()
{
    String res = get(getOtherNodeAddress(), getOtherNodePort(), "/node/status", http);
    if (res.length() > 10)
    {
        nodeStatus.set(2);
        StaticJsonBuffer<1024> buffer;
        JsonObject &root = buffer.parseObject(res);
        otherHeight.set(root[AJAX_HEIGHT]);
        otherDate.set(root[AJAX_DATE]);
        otherTimeStamp.set(root[AJAX_TIMESTAMP]);
    }
}

void updateVersion()
{
    String res = get(getNodeAddress(), getNodePort(), "/node/version", http);
    if (res.length() > 10)
    {
        nodeStatus.set(2);
        StaticJsonBuffer<1024> buffer;
        JsonObject &root = buffer.parseObject(res);
        version.set(stringToVersion(root[AJAX_VERSION]));
    }

    // res = getSecure("api.github.com", "/repos/wavesplatform/Waves/releases/latest", GITHUB_FINGERPRINT);
    // if (res.length() > 10)
    // {
    //     nodeStatus.set(2);
    //     buffer.clear();
    //     JsonObject &root = buffer.parseObject(res);
    //     version.set(stringToVersion(root[AJAX_VERSION]));
    // } else {
    //     Serial.println("ERROR");
    // }

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
    if (client.connect(getNodeAddress().c_str(), getNodePort()))
    {
        client.print(String("GET /peers/connected HTTP/1.1\r\nHost: " + getNodeAddress() + "\r\nUser-Agent: ESP8266\r\nConnection: close\r\n\r\n"));
        while (client.connected())
        {
            String line = client.readStringUntil('\n');
            if (line == "\r")
                break;
        }

        int count = 0;
        while (client.connected())
        {
            String line = client.readStringUntil('}');
            count++;
        }

        peers.set(count > 1 ? count - 1 : 0);
    }
}

void updateBalance()
{
    if (getAddress())
    {
        String res = get(getOtherNodeAddress(), getOtherNodePort(), "/addresses/effectiveBalance/" + getAddress(), http);
        if (res.length() > 10)
        {
            nodeStatus.set(2);
            StaticJsonBuffer<1024> buffer;
            JsonObject &root = buffer.parseObject(res);
            balance.set(root[AJAX_BALANCE]);
        }
    }
}

int calculateMaining(int start, int end, String address)
{
    int result = 0;

    if (client.connect(getNodeAddress().c_str(), getNodePort()))
    {
        client.print(String("GET /blocks/headers/seq/" + String(start) + "/" + String(end) + " HTTP/1.1\r\nHost: " + getNodeAddress() + "\r\nUser-Agent: ESP8266\r\nConnection: close\r\n\r\n"));
        while (client.connected())
        {
            String line = client.readStringUntil('\n');
            if (line == "\r")
                break;
        }

        int count = 0;
        while (client.connected())
        {
            if (client.readStringUntil('\n').indexOf(address) == 17)
                result++;
        }
    }

    return result;
}

void updateMaining()
{
    // update blocks :)
    for (int i = 0; i < BLOCKS_LENGTH; i++)
    {
        if (blocks[i].start <= height.get() && blocks[i].stop >= height.get())
        {
            blocks[i].value = calculateMaining(blocks[i].start, blocks[i].stop, getAddress());
            if (blocks[i].value > lastMainingCount)
                mainingAlarm();
            lastMainingCount = blocks[i].value;
            return;
        }
    }

    // search insert new block
    for (int i = 0; i < BLOCKS_LENGTH; i++)
    {
        if (blocks[i].start == 0 && blocks[i].stop == 0)
        {
            blocks[i].start = i > 0 ? blocks[i - 1].stop + 1 : height.get();
            blocks[i].stop = blocks[i].start + BLOCK_GET_LENGTH;
            blocks[i].value = calculateMaining(blocks[i].start, blocks[i].stop, getAddress());
            lastMainingCount = blocks[i].value;
            return;
        }
    }

    fullBlockHistory = true;

    // if full
    for (int i = 1; i < BLOCKS_LENGTH; i++)
    {
        blocks[i - 1].start = blocks[i].start;
        blocks[i - 1].stop = blocks[i].stop;
        blocks[i - 1].value = blocks[i].value;
    }
    blocks[BLOCKS_LENGTH - 1].start = blocks[BLOCKS_LENGTH - 2].stop + 1;
    blocks[BLOCKS_LENGTH - 1].stop = blocks[BLOCKS_LENGTH - 1].start + BLOCK_GET_LENGTH;
    blocks[BLOCKS_LENGTH - 1].value = calculateMaining(blocks[BLOCKS_LENGTH - 1].start, blocks[BLOCKS_LENGTH - 1].start, getAddress());
    lastMainingCount = blocks[BLOCKS_LENGTH - 1].value;
}

void updateNodeInformation()
{
    if (!updateHeight())
        return;

    updateOtherHeight();

    if (abs(height.get() - otherHeight.get()) > MAX_HEIGHT_DIFFERENCE)
        heightDifferenceAlarm();

    updateVersion();
    updateBalance();

    if (needUpdatePeer >= UPDATE_TIME_PEER)
    {
        updatePeers();
        needUpdatePeer = 0;
    }
    needUpdatePeer++;

    if (needUpdateMainingHistory >= UPDATE_TIME_MAINING_HISTORY)
    {
        updateMaining();

        // Download history :)
        if (!fullBlockHistory)
        {
            for (int i = BLOCKS_LENGTH - 1; i > 0; i--)
            {
                blocks[i].start = blocks[i - 1].start;
                blocks[i].stop = blocks[i - 1].stop;
                blocks[i].value = blocks[i - 1].value;
            }

            blocks[0].stop = blocks[1].start - 1;
            blocks[0].start = blocks[0].stop - BLOCK_GET_LENGTH;
            blocks[0].value = calculateMaining(blocks[0].start, blocks[0].stop, getAddress());
        }
        needUpdateMainingHistory = 0;
    }
    needUpdateMainingHistory++;
    updateDisplay();
}