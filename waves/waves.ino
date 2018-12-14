#include "nodemcu.h"
#include "dns.h"
#include "server.h"
#include "wifi.h"
#include "data.h"
#include "node.h"

ADC_MODE(ADC_VCC);

unsigned long pollTime;

void setup()
{
    Serial.begin(9600);
    Serial.println();

    printHardwareInformation();
    initWiFi();
    initServer();
    initDNS();

    pollTime = millis();
}

void loop()
{
    handleServer();
    handleDNS();

    if (millis() - pollTime > 1000 || millis() < pollTime)
    {
        pollTime = millis();
        if (WiFi.status() == WL_CONNECTED)
        {
            wifiStatus.set(true);
            nodeStatus.set(1);
            updateNodeInformation();
        }
        else
        {
            nodeStatus.set(0);
            wifiStatus.set(false);
        }
    }
}
