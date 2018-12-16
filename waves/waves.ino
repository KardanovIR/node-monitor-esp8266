#include "nodemcu.h"
#include "dns.h"
#include "server.h"
#include "wifi.h"
#include "data.h"
#include "node.h"
#include "display.h"
#include "alarm.h"

ADC_MODE(ADC_VCC);

unsigned long pollTime;

void setup()
{
    initAlarm();
    Serial.begin(9600);
    Serial.println();

    printHardwareInformation();
    initWiFi();
    initServer();
    initDNS();
    initDisplay();
    displayLogo();

    // for (int i = 0; i < 20; i++)
    // {
    //     tone(D0, i*100);
    //     delay(500);
    // }

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
