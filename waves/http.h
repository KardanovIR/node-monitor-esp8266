#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

String makeTag(String tag, String content, String attributes = "");
String makePage(String title, String content, String style = "");

String get(String url, HTTPClient& http);