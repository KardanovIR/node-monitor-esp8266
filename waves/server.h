#include <ESP8266WebServer.h>

#include "constants.h"

static ESP8266WebServer server(HTTP_PORT);

void initServer();
void handleServer();