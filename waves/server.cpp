#include "server.h"
#include <Arduino.h>

#include "http.h"

void handleRoot()
{
    String content = makeTag(HTTP_H1_TAG, "Node monitor by WAVES");
    Serial.println(content);
    Serial.println(makePage("Home", content));
    server.send(200, "text/html", makePage("Home", content));
}

void initServer()
{
    server.on("/", handleRoot);
    server.begin();
}

void handleServer()
{
    server.handleClient();
}