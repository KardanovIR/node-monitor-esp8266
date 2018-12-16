#include "alarm.h"

#include <Arduino.h>
// #include "DFRobotDFPlayerMini.h"
// #include <SoftwareSerial.h>

// SoftwareSerial mp3Serial(D4, D3);
// DFRobotDFPlayerMini player;

void initAlarm()
{
    pinMode(D0, OUTPUT);
    digitalWrite(D0, HIGH);
}

void heightDifferenceAlarm()
{
    Serial.println("ALARM HEIGHT");
}

void mainingAlarm()
{
    Serial.println("ALARM NEW MAINING");
    tone(D0, 0);
    delay(200);
    noTone(D0);
    delay(500);
    tone(D0, 0);
    delay(200);
    noTone(D0);
    digitalWrite(D0, HIGH);
}