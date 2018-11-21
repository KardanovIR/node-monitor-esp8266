#include "nodemcu.h"
#include "console.h"

void printHardwareInformation()
{
  printDelemiter();
  Serial.println(F("WAVES NODE MONITOR"));
  Serial.printf_P(PSTR("Chip ID: %d\n"), ESP.getChipId());
  Serial.printf_P(PSTR("Core version: %s\n"), ESP.getCoreVersion().c_str());
  Serial.printf_P(PSTR("CPU freq[MHz]: %d\n"), ESP.getCpuFreqMHz());
  printDelemiter();
}