#include <DNSServer.h>

#include "constants.h"
#include "wifi.h"

DNSServer dnsServer;

void initDNS()
{
    dnsServer.setTTL(300);
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(HTTP_PORT, "www.example.com", apIP);
}

void handleDNS()
{
    dnsServer.processNextRequest();
}