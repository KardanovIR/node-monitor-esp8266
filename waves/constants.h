// WiFi AP
static const char AP_SSID[] = "WAVES_NODE_MONITOR";
static const char AP_PASSWORD_DEFAULT[] = "WAVES4FUN";
static const char AP_DNS[] = "waves-node.com";
// DATA
static const int AP_PASSWORD_INDEX = 0;
static const int AP_PASSWORD_LENGTH = 19;
static const int WIFI_SSID_INDEX = 20;
static const int WIFI_SSID_LENGTH = 19;
static const int WIFI_PASSWORD_INDEX = 40;
static const int WIFI_PASSWORD_LENGTH = 19;
static const int NODE_HOST_INDEX = 60;
static const int NODE_HOST_LENGTH = 37;
static const int NODE_TIMEOUT_INDEX = 99;
static const int NODE_PORT_INDEX = 100;
static const int NODE_OTHER_HOST_INDEX = 105;
static const int NODE_OTHER_HOST_LENGTH = 37;
static const int NODE_OTHER_PORT_INDEX = 145;
static const int ADDRESS_INDEX = 150;
static const int ADDRESS_LENGTH = 49;

// Server
static const int HTTP_PORT = 80;
static const int JSON_BUFFER_LENGTH = 1024;
// HTTP
static const char HTTP_DOCTYPE[] = "<!DOCTYPE html>";
static const char HTTP_UTF8[] = "<meta charset=\"utf-8\"/>";
static const char HTTP_TAG[] = "html";
static const char HTTP_HEAD_TAG[] = "head";
static const char HTTP_BODY_TAG[] = "body";
static const char HTTP_STYLE_TAG[] = "style";
static const char HTTP_OPEN_TAG[] = "<";
static const char HTTP_CLOSE_TAG[] = ">";
static const char HTTP_END_TAG[] = "/";
static const char HTTP_TITLE_TAG[] = "title";
static const char HTTP_H1_TAG[] = "h1";
static const char HTTP_P_TAG[] = "p";
static const char HTTP_B_TAG[] = "b";
static const char HTTP_A_TAG[] = "a";
static const char HTTP_TABLE_TAG[] = "table";
static const char HTTP_SCRIPT_TAG[] = "script";
static const char HTTP_TH_TAG[] = "th";
static const char HTTP_TR_TAG[] = "tr";
static const char HTTP_FORM_TAG[] = "form";
static const char HTTP_INPUT_TAG[] = "input";
static const char HTTP_BUTTON_TAG[] = "button";
static const char HTTP_SUP_TAG[] = "sup";
static const char HTTP_DIV_TAG[] = "div";
static const char HTTP_STYLE_DEFAULT[] = "*{font-family:sans-serif;text-align:center;margin:0;} html,body,table{width:100%;} .c{display:table;margin:20px auto;} th{font-size:14px;font-weight:100;} .r{text-align:right;} .l{text-align:left;}";
// Content
static const char CONTENT_LABEL[] = "NODE MONITOR";
static const char CONTENT_NONE[] = "-/-";
// FORM DATA
static const char AP_PASSWORD_NAME[] = "ap";
static const char WIFI_SSID_NAME[] = "ws";
static const char WIFI_PASSWORD_NAME[] = "wp";
static const char NODE_HOST_NAME[] = "nh";
static const char NODE_PORT_NAME[] = "np";
static const char NODE_TIMEOUT_NAME[] = "nt";
static const char NODE_OTHER_HOST_NAME[] = "onh";
static const char NODE_OTHER_PORT_NAME[] = "onp";
static const char ADDRESS_NAME[] = "ad";
// AJAX
static const char AJAX_TICK[] = "tick";
static const char AJAX_VOLTAGE[] = "voltage";
static const char AJAX_FREE[] = "free";
static const char AJAX_RSSI[] = "rssi";
static const char AJAX_WIFI[] = "wifi";
static const char AJAX_TIMEOUT[] = "timeout";
static const char AJAX_HOST[] = "host";
static const char AJAX_PORT[] = "port";
static const char AJAX_HEIGHT[] = "blockchainHeight";
static const char AJAX_NODE_STATUS[] = "status";
static const char AJAX_VERSION[] = "version";
static const char AJAX_DATE[] = "updatedDate";
static const char AJAX_TIMESTAMP[] = "updatedTimestamp";
static const char AJAX_PEERS[] = "peers";
static const char AJAX_OTHER_HOST[] = "regHost";
static const char AJAX_OTHER_PORT[] = "regPort";
static const char AJAX_ADDRESS[] = "address";
static const char AJAX_BALANCE[] = "balance";
static const char AJAX_MAINING[] = "maining";
// Version
static String DIGITS = "0123456789";
// HTTPS
const String GITHUB_FINGERPRINT = "5F F1 60 31 09 04 3E F2 90 D2 B0 8A 50 38 04 E8 37 9F BC 76";
