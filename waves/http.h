#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

String makeTag(String tag, String content, String attributes = "");
String makePage(String title, String content, String style = "");

String get(String host, uint16_t port, String url, HTTPClient& http);
String getSecure(String host, String url, String fingerprint);