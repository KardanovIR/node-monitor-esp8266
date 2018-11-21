#include "server.h"

void handleRoot(){
  server.send(200, "text/html", "<h1>You are connected</h1>");
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