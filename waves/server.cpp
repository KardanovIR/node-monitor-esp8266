#include "server.h"
#include <Arduino.h>
#include <ArduinoJson.h>

#include "http.h"
#include "presethtml.h"
#include "data.h"

StaticJsonBuffer<JSON_BUFFER_LENGTH> json;
JsonObject& root = json.createObject();

void handleRoot()
{
    String br = makeBR();
    String content = makeWavesLogo() + makeWavesLabel() + br;
    
    String tableContent;
    tableContent += makeTableRow2("Address:", getNodeAddress(), AJAX_HOST);
    String timeout(getNodeTimeout());
    tableContent += makeTableRow2("Timeout:", timeout, AJAX_TIMEOUT);
    String heightString(height.get());
    tableContent += makeTableRow2("Height:", height.isInit() ? heightString : CONTENT_NONE, AJAX_HEIGHT);
    tableContent += makeTableRow2("", "");
    tableContent += makeTableRow2("", "");
    tableContent += makeTableRow2("", "");

    String chipId(ESP.getChipId());
    tableContent += makeTableRow2("ID:", chipId);
    String freq(ESP.getCpuFreqMHz());
    tableContent += makeTableRow2("Freq:", freq);
    tableContent += makeTableRow2("Core:", ESP.getCoreVersion());
    tableContent += makeTableRow2("SDK:", ESP.getSdkVersion());
    tableContent += makeTableRow2("MD5:", ESP.getSketchMD5());
    String cycleCount(ESP.getCycleCount());
    tableContent += makeTableRow2("Tick:", cycleCount, AJAX_TICK);
    String vcc(ESP.getVcc());
    tableContent += makeTableRow2("Voltage:", vcc, AJAX_VOLTAGE);
    String freeHeap(ESP.getFreeHeap());
    tableContent += makeTableRow2("Free:", freeHeap, AJAX_FREE);
    tableContent += makeTableRow2("WiFi:", wifiStatus.isInit() && wifiStatus.get() ? "on" : "off", AJAX_WIFI);
    String rssi(WiFi.RSSI());
    tableContent += makeTableRow2("RSSI:", rssi, AJAX_RSSI);
    content += makeTag(HTTP_TABLE_TAG, tableContent);

    content += br + makeTag(HTTP_TH_TAG, makeTag(HTTP_A_TAG, makeTag(HTTP_BUTTON_TAG, "&#9881 Settings", "type='button'"), "href='/settings'"));
    content += makeTag(HTTP_SCRIPT_TAG, makeAjax(getNodeTimeout()));

    server.send(200, "text/html", makePage("WAVES", makeTag(HTTP_DIV_TAG, content, "class='content'"), HTTP_STYLE_DEFAULT));
}

void handleGetSettings()
{
    String br = makeBR();
    String content = makeWavesLogo() + makeWavesLabel() + br;

    // NODE
    String formContent = makeTag(HTTP_P_TAG, "NODE") + br;

    String NODE_HOST = makeTag(HTTP_TH_TAG, "Address:", "class='right'");
    NODE_HOST += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='text' max='35' name='" + String(NODE_HOST_NAME) + "' size='20' value='") + getNodeAddress() + "'"), "class='right'");
    NODE_HOST = makeTag(HTTP_TR_TAG, NODE_HOST);

    String POLL_TIMEOUT = makeTag(HTTP_TH_TAG, "Poll timeout:", "class='right'");
    POLL_TIMEOUT += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='number' name='" + String(NODE_TIMEOUT_NAME) + "' min='1' max='255' value='") + getNodeTimeout() + "'"), "class='right'");
    POLL_TIMEOUT = makeTag(HTTP_TR_TAG, POLL_TIMEOUT);

    formContent += makeTag(HTTP_TABLE_TAG, NODE_HOST + POLL_TIMEOUT);

    // WIFI AP
    formContent += br + makeTag(HTTP_P_TAG, "WIFI AP") + br;

    String SSID_AP = makeTag(HTTP_TH_TAG, "SSID:", "class='right'");
    SSID_AP += makeTag(HTTP_TH_TAG, "WAVES_NODE_MONITOR", "class='right'");
    SSID_AP = makeTag(HTTP_TR_TAG, SSID_AP);

    String SSID_AP_PASSWORD = makeTag(HTTP_TH_TAG, "Password:", "class='right'");
    SSID_AP_PASSWORD += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='password' name='" + String(AP_PASSWORD_NAME) + "' size='20' value='") + getWiFiApPassword() + "'"), "class='right'");
    SSID_AP_PASSWORD = makeTag(HTTP_TR_TAG, SSID_AP_PASSWORD);

    formContent += makeTag(HTTP_TABLE_TAG, SSID_AP + SSID_AP_PASSWORD);

    // WIFI
    formContent += br + makeTag(HTTP_P_TAG, "WIFI") + br;

    String SSID = makeTag(HTTP_TH_TAG, "SSID:", "class='right'");
    SSID += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='text' name='" + String(WIFI_SSID_NAME) + "' size='20' value='") + getWiFiSsid() + "'"), "class='right'");
    SSID = makeTag(HTTP_TR_TAG, SSID);

    String SSID_PASSWORD = makeTag(HTTP_TH_TAG, "Password:", "class='right'");
    SSID_PASSWORD += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='password' name='" + String(WIFI_PASSWORD_NAME) + "' size='20' value='") + getWiFiPassword() + "'"), "class='right'");
    SSID_PASSWORD = makeTag(HTTP_TR_TAG, SSID_PASSWORD);

    formContent += makeTag(HTTP_TABLE_TAG, SSID + SSID_PASSWORD);

    // Buttons
    String BUTTONS = br + makeTag(HTTP_TH_TAG, makeTag(HTTP_BUTTON_TAG, "&#9745 Save", "type='submit'"));
    BUTTONS += makeTag(HTTP_TH_TAG, makeTag(HTTP_A_TAG, makeTag(HTTP_BUTTON_TAG, "&#9924 Monitoring", "type='button'"), "href='/'"));
    formContent += makeTag(HTTP_TABLE_TAG, BUTTONS);

    content += makeTag(HTTP_FORM_TAG, formContent, "action='/save-settings' method='post'");
    server.send(200, "text/html", makePage("WAVES", makeTag(HTTP_DIV_TAG, content, "class='content'"), HTTP_STYLE_DEFAULT));
}

void handleSetSettings()
{
    bool isReconnect = server.arg(AP_PASSWORD_NAME) != getWiFiApPassword();

    setWiFiApPassword(server.arg(AP_PASSWORD_NAME));
    setWiFiSsid(server.arg(WIFI_SSID_NAME));
    setWiFiPassword(server.arg(WIFI_PASSWORD_NAME));
    setNodeAddress(server.arg(NODE_HOST_NAME));
    setNodeTimeout(server.arg(NODE_TIMEOUT_NAME).toInt());

    if (isReconnect)
    {
        String br = makeBR();
        String content = makeWavesLogo() + makeWavesLabel() + br + br;
        content += makeTag(HTTP_P_TAG, "You're change password for AP, reconnect manual and go home page", "style='font-size:14px'");
        content += br;
        content += makeTag(HTTP_A_TAG, makeTag(HTTP_BUTTON_TAG, "&#9924 Go home"), "href='/'");
        server.send(200, "text/html", makePage("WAVES ERROR PAGE", makeTag(HTTP_DIV_TAG, content, "class='content'"), HTTP_STYLE_DEFAULT));
    }
    else
    {
        server.sendHeader("Location", "/", true);
        server.send(302, "text/plane", "");
    }

    // TODO APPLY PASSWORD AND SSID
}

void handleError()
{
    String br = makeBR();
    String content = makeWavesLogo() + makeWavesLabel() + br + br;
    content += makeTag(HTTP_P_TAG, "Sory, this page is sick", "style='font-size:14px'");
    content += br;
    content += makeTag(HTTP_A_TAG, makeTag(HTTP_BUTTON_TAG, "&#9924 Go home"), "href='/'");
    server.send(200, "text/html", makePage("WAVES ERROR PAGE", makeTag(HTTP_DIV_TAG, content, "class='content'"), HTTP_STYLE_DEFAULT));
}

void handleGetState()
{
    String content;
    // json.clear();

    // OTHER
    root[AJAX_TICK] = ESP.getCycleCount();
    root[AJAX_VOLTAGE] = ESP.getVcc();
    root[AJAX_FREE] = ESP.getFreeHeap();
    root[AJAX_RSSI] = WiFi.RSSI();
    root[AJAX_WIFI] = wifiStatus.isInit() && wifiStatus.get() ? "on" : "off";
    // NODE
    root[AJAX_HOST] = getNodeAddress();
    root[AJAX_TIMEOUT] = getNodeTimeout();
    root[AJAX_HEIGHT] = height.get();

    root.printTo(content);
    server.send(200, "application/json", content);
}

void initServer()
{
    server.on("/", HTTP_GET, handleRoot);
    server.on("/settings", HTTP_GET, handleGetSettings);
    server.on("/save-settings", HTTP_POST, handleSetSettings);
    server.on("/state", HTTP_GET, handleGetState);
    server.onNotFound(handleError);
    server.begin();
}

void handleServer()
{
    server.handleClient();
}