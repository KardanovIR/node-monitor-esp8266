#include "server.h"
#include <Arduino.h>
#include <ArduinoJson.h>

#include "http.h"
#include "presethtml.h"
#include "data.h"

void handleRoot()
{
    String br = makeBR();
    String content = makeWavesLogo() + makeWavesLabel() + br;

    String tableContent;
    tableContent += makeTableRow2("Host:", getNodeAddress(), AJAX_HOST);
    String portString(getNodePort());
    tableContent += makeTableRow2("Port:", portString, AJAX_PORT);
    tableContent += makeTableRow2("Regular host:", getOtherNodeAddress(), AJAX_OTHER_HOST);
    String otherPortString(getOtherNodePort());
    tableContent += makeTableRow2("Regular Port:", otherPortString, AJAX_OTHER_PORT);
    tableContent += makeTableRow2("Version:", versionToString(version.get()), AJAX_VERSION);
    String peersString(peers.get());
    tableContent += makeTableRow2("Peers:", peersString, AJAX_PEERS);
    String balanceString(balance.get());
    tableContent += makeTableRow2("Balance:", balanceString, AJAX_BALANCE);
    tableContent += makeTableRow2("Maining:", getMainingString(blocks), AJAX_MAINING);
    switch (nodeStatus.get())
    {
    case 0:
    {
        tableContent += makeTableRow2("Status:", "connection failed", AJAX_NODE_STATUS);
        break;
    }
    case 1:
    {
        tableContent += makeTableRow2("Status:", "request failed", AJAX_NODE_STATUS);
        break;
    }
    case 2:
    {
        tableContent += makeTableRow2("Status:", "ok", AJAX_NODE_STATUS);
        break;
    }
    }
    String timeout(getNodeTimeout());
    tableContent += makeTableRow2("Timeout:", timeout, AJAX_TIMEOUT);
    String heightString(height.get());
    tableContent += makeTableRow2("Height:", height.isInit() ? heightString : CONTENT_NONE, AJAX_HEIGHT);
    tableContent += makeTableRow2("Date:", date.isInit() ? date.get() : CONTENT_NONE, AJAX_DATE);
    String timeString(timeStamp.get());
    tableContent += makeTableRow2("Timestamp:", timeString, AJAX_TIMESTAMP);
    tableContent += makeTableRow2("Address:", getAddress(), AJAX_ADDRESS);
    tableContent += makeTableRow2("", "");
    tableContent += makeTableRow2("", "");
    tableContent += makeTableRow2("", "");

    String chipId(ESP.getChipId());
    tableContent += makeTableRow2("ID:", chipId);
    String freq(ESP.getCpuFreqMHz());
    // tableContent += makeTableRow2("Freq:", freq);
    // tableContent += makeTableRow2("Core:", ESP.getCoreVersion());
    // tableContent += makeTableRow2("SDK:", ESP.getSdkVersion());
    // tableContent += makeTableRow2("MD5:", ESP.getSketchMD5());
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

    server.send(200, "text/html", makePage("WAVES", makeTag(HTTP_DIV_TAG, content, "class='c'"), HTTP_STYLE_DEFAULT));
}

void handleGetSettings()
{
    String br = makeBR();
    String content = makeWavesLogo() + makeWavesLabel() + br;

    // NODE
    String formContent = makeTag(HTTP_P_TAG, "NODE") + br;

    String NODE_HOST = makeTag(HTTP_TH_TAG, "Host:", "class='r'");
    NODE_HOST += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='text' max='35' name='" + String(NODE_HOST_NAME) + "' size='20' value='") + getNodeAddress() + "'"), "class='r'");
    NODE_HOST = makeTag(HTTP_TR_TAG, NODE_HOST);

    String NODE_PORT = makeTag(HTTP_TH_TAG, "Port:", "class='r'");
    NODE_PORT += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='number' min='1' max='100000' name='" + String(NODE_PORT_NAME) + "' size='20' value='") + String(getNodePort()) + "'"), "class='r'");
    NODE_PORT = makeTag(HTTP_TR_TAG, NODE_PORT);

    String NODE_OTHER_HOST = makeTag(HTTP_TH_TAG, "Regular host:", "class='r'");
    NODE_OTHER_HOST += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='text' max='35' name='" + String(NODE_OTHER_HOST_NAME) + "' size='20' value='") + getOtherNodeAddress() + "'"), "class='r'");
    NODE_OTHER_HOST = makeTag(HTTP_TR_TAG, NODE_OTHER_HOST);

    String NODE_OTHER_PORT = makeTag(HTTP_TH_TAG, "Regular port:", "class='r'");
    NODE_OTHER_PORT += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='number' min='1' max='100000' name='" + String(NODE_OTHER_PORT_NAME) + "' size='20' value='") + String(getOtherNodePort()) + "'"), "class='r'");
    NODE_OTHER_PORT = makeTag(HTTP_TR_TAG, NODE_OTHER_PORT);

    String POLL_TIMEOUT = makeTag(HTTP_TH_TAG, "Poll timeout:", "class='r'");
    POLL_TIMEOUT += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='number' name='" + String(NODE_TIMEOUT_NAME) + "' value='") + String(getNodeTimeout()) + "'"), "class='r'");
    POLL_TIMEOUT = makeTag(HTTP_TR_TAG, POLL_TIMEOUT);

    String ADDRESS = makeTag(HTTP_TH_TAG, "Address:", "class='r'");
    ADDRESS += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='text' max='35' name='" + String(ADDRESS_NAME) + "' size='20' value='") + getAddress() + "'"), "class='r'");
    ADDRESS = makeTag(HTTP_TR_TAG, ADDRESS);

    formContent += makeTag(HTTP_TABLE_TAG, NODE_HOST + NODE_PORT + NODE_OTHER_HOST + NODE_OTHER_PORT + POLL_TIMEOUT + ADDRESS);

    // WIFI AP
    formContent += br + makeTag(HTTP_P_TAG, "WIFI AP") + br;

    String SSID_AP = makeTag(HTTP_TH_TAG, "SSID:", "class='r'");
    SSID_AP += makeTag(HTTP_TH_TAG, "WAVES_NODE_MONITOR", "class='r'");
    SSID_AP = makeTag(HTTP_TR_TAG, SSID_AP);

    String SSID_AP_PASSWORD = makeTag(HTTP_TH_TAG, "Password:", "class='r'");
    SSID_AP_PASSWORD += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='password' name='" + String(AP_PASSWORD_NAME) + "' size='20' value='") + getWiFiApPassword() + "'"), "class='r'");
    SSID_AP_PASSWORD = makeTag(HTTP_TR_TAG, SSID_AP_PASSWORD);

    formContent += makeTag(HTTP_TABLE_TAG, SSID_AP + SSID_AP_PASSWORD);

    // WIFI
    formContent += br + makeTag(HTTP_P_TAG, "WIFI") + br;

    String SSID = makeTag(HTTP_TH_TAG, "SSID:", "class='r'");
    SSID += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='text' name='" + String(WIFI_SSID_NAME) + "' size='20' value='") + getWiFiSsid() + "'"), "class='r'");
    SSID = makeTag(HTTP_TR_TAG, SSID);

    String SSID_PASSWORD = makeTag(HTTP_TH_TAG, "Password:", "class='r'");
    SSID_PASSWORD += makeTag(HTTP_TH_TAG, makeTag(HTTP_INPUT_TAG, "", String("type='password' name='" + String(WIFI_PASSWORD_NAME) + "' size='20' value='") + getWiFiPassword() + "'"), "class='r'");
    SSID_PASSWORD = makeTag(HTTP_TR_TAG, SSID_PASSWORD);

    formContent += makeTag(HTTP_TABLE_TAG, SSID + SSID_PASSWORD);

    // Buttons
    String BUTTONS = br + makeTag(HTTP_TH_TAG, makeTag(HTTP_BUTTON_TAG, "&#9745 Save", "type='submit'"));
    BUTTONS += makeTag(HTTP_TH_TAG, makeTag(HTTP_A_TAG, makeTag(HTTP_BUTTON_TAG, "&#9924 Monitoring", "type='button'"), "href='/'"));
    formContent += makeTag(HTTP_TABLE_TAG, BUTTONS);

    content += makeTag(HTTP_FORM_TAG, formContent, "action='/save-settings' method='post'");
    server.send(200, "text/html", makePage("WAVES", makeTag(HTTP_DIV_TAG, content, "class='c'"), HTTP_STYLE_DEFAULT));
}

void handleSetSettings()
{
    bool isReconnect = server.arg(AP_PASSWORD_NAME) != getWiFiApPassword();

    setWiFiApPassword(server.arg(AP_PASSWORD_NAME));
    setWiFiSsid(server.arg(WIFI_SSID_NAME));
    setWiFiPassword(server.arg(WIFI_PASSWORD_NAME));
    setNodeAddress(server.arg(NODE_HOST_NAME));
    setNodePort(server.arg(NODE_PORT_NAME).toInt());
    setNodeTimeout(server.arg(NODE_TIMEOUT_NAME).toInt());
    setOtherNodeAddress(server.arg(NODE_OTHER_HOST_NAME));
    setOtherNodePort(server.arg(NODE_OTHER_PORT_NAME).toInt());
    setAddress(server.arg(ADDRESS_NAME));

    if (isReconnect)
    {
        String br = makeBR();
        String content = makeWavesLogo() + makeWavesLabel() + br + br;
        content += makeTag(HTTP_P_TAG, "You're change password for AP, reconnect manual and go home page", "style='font-size:14px'");
        content += br;
        content += makeTag(HTTP_A_TAG, makeTag(HTTP_BUTTON_TAG, "&#9924 Go home"), "href='/'");
        server.send(200, "text/html", makePage("WAVES ERROR PAGE", makeTag(HTTP_DIV_TAG, content, "class='c'"), HTTP_STYLE_DEFAULT));
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
    server.send(200, "text/html", makePage("WAVES ERROR PAGE", makeTag(HTTP_DIV_TAG, content, "class='c'"), HTTP_STYLE_DEFAULT));
}

void handleGetState()
{
    String content;
    StaticJsonBuffer<JSON_BUFFER_LENGTH> json;
    JsonObject &root = json.createObject();

    // OTHER
    root[AJAX_TICK] = ESP.getCycleCount();
    root[AJAX_VOLTAGE] = ESP.getVcc();
    root[AJAX_FREE] = ESP.getFreeHeap();
    root[AJAX_RSSI] = WiFi.RSSI();
    root[AJAX_WIFI] = wifiStatus.isInit() && wifiStatus.get() ? "on" : "off";
    switch (nodeStatus.get())
    {
    case 0:
    {
        root[AJAX_NODE_STATUS] = "connection failed";
        break;
    }
    case 1:
    {
        root[AJAX_NODE_STATUS] = "request failed";
        break;
    }
    case 2:
    {
        root[AJAX_NODE_STATUS] = "ok";
        break;
    }
    }
    root[AJAX_WIFI] = wifiStatus.isInit() && wifiStatus.get() ? "on" : "off";
    // NODE
    root[AJAX_HOST] = getNodeAddress();
    root[AJAX_PORT] = getNodePort();
    root[AJAX_OTHER_HOST] = getOtherNodeAddress();
    root[AJAX_OTHER_PORT] = getOtherNodePort();
    root[AJAX_TIMEOUT] = getNodeTimeout();
    root[AJAX_HEIGHT] = String(height.get()) + (otherHeight.get() ? "(" + String(otherHeight.get() - height.get()) + ")" : "");
    root[AJAX_VERSION] = versionToString(version.get());
    root[AJAX_DATE] = date.get();
    root[AJAX_TIMESTAMP] = timeStamp.get() + (otherTimeStamp.get() ? "(" + String(String(otherTimeStamp.get()).toInt() - String(timeStamp.get()).toInt()) + ")" : "");
    root[AJAX_PEERS] = peers.get();
    root[AJAX_ADDRESS] = getAddress();
    root[AJAX_BALANCE] = balance.get();
    root[AJAX_MAINING] = getMainingString(blocks);

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