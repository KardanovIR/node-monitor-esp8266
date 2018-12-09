#include "node.h"

#include "data.h"
#include "http.h"
#include "constants.h"

#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

WiFiClient client;
HTTPClient http;

StaticJsonBuffer<1024> buffer;

void updateHeight()
{
    String res = get(getNodeAddress() + "/blocks/height", http);
    if (res.length() > 10) {
        buffer.clear();
        JsonObject& root = buffer.parseObject(res);
        height.set(root[AJAX_HEIGHT]);
    }
}

void updateNodeInformation()
{
    updateHeight();
}