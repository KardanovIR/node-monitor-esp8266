#include "http.h"

#include "constants.h"
#include <WiFiClientSecure.h>

String makeTag(String tag, String content, String attributes)
{
    String result = HTTP_OPEN_TAG;
    result += tag + (attributes.length() ? " " : "") + attributes;
    result += HTTP_CLOSE_TAG;
    result += content;
    result += HTTP_OPEN_TAG;
    result += HTTP_END_TAG;
    result += tag;
    result += HTTP_CLOSE_TAG;
    return result;
}

String makeHead(String title, String style)
{
    String result = makeTag(HTTP_TITLE_TAG, title);
    result += HTTP_UTF8;
    result += style.length() ? makeTag(HTTP_STYLE_TAG, style) : "";
    return makeTag(HTTP_HEAD_TAG, result);
}

String makePage(String title, String content, String style)
{
    String preambule = HTTP_DOCTYPE;
    String head = makeHead(title, style);
    String body = makeTag(HTTP_BODY_TAG, content);
    return preambule + makeTag(HTTP_TAG, head + body);
}

String get(String host, uint16_t port, String url, HTTPClient &http)
{
    String result;
    if (http.begin(host, port, url))
    {
        int httpCode = http.GET();

        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
        {
            result = http.getString();
        }
    }

    return result;
}

String getSecure(String host, String url, String fingerprint)
{
    WiFiClientSecure client;
    String result;
    if (!client.connect(host, 443)) {
        Serial.println("connection failed");
        return result;
    }
    
    if (client.verify(fingerprint.c_str(), host.c_str())) {
        Serial.println("certificate matches");
    } else {
        Serial.println("certificate doesn't match");
    }

    // Send GET
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");
    
    Serial.println("GET sent");
    while (client.connected()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        // if (line.startsWith("HTTP/1.1")) {
            // Get HTTP return code
            // return line;
        // }
    }
    
    return result;
}