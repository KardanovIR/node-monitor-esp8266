#include "dns.h"
#include "constants.h"
#include "wifi.h"

void initDNS()
{
    dnsServer.setTTL(300);
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(53, AP_DNS, apIP);
}

void handleDNS()
{
    dnsServer.processNextRequest();
}