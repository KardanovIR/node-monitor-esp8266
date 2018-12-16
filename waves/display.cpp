#include "display.h"

#include "data.h"
#include <SPI.h>
#include "SH1106Spi.h"

SH1106Spi display(D1, D2, D8);

void initDisplay()
{
    display.init();
    display.clear();
    display.display();
}

void displayLogo()
{
    display.setFont(ArialMT_Plain_10);
    display.drawString(25, 0, "NODE MONITOR");
    display.drawString(60, 15, "by");
    display.setFont(ArialMT_Plain_24);
    display.drawString(23, 25, "WAVES");
    display.display();
}


void updateDisplay()
{
    display.clear();
    display.setFont(ArialMT_Plain_10);

    display.drawString(0, 0, "B: " + balance.get());
    display.drawString(0, 12, "H: " + String(height.get()) + " (" + String(height.get() - otherHeight.get()) + ")");
    display.drawString(75, 12, "V: " + versionToString(version.get()));
    display.drawString(0, 24, "T: " + String(timeStamp.get()) + " (" + String(String(timeStamp.get()).toInt() - String(otherTimeStamp.get()).toInt()) + ")");
    display.drawString(0, 36, "A: " + getAddress());
    display.drawString(0, 48, "M: " + getMainingString(blocks));

    display.display();
}