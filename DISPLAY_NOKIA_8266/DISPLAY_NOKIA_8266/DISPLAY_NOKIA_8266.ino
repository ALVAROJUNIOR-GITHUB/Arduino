#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"
                                        
Adafruit_PCD8544 display = Adafruit_PCD8544(D3, D4, D5, D7, D6); // CLK, DIN, DC, CE, RST // BACKLIGHT TERRA-->
void setup() 
{
  display.begin();
  display.setContrast(40);
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(BLACK,WHITE);
  display.setCursor(0,0);
  display.println(" IOT by Alvaro ");

  display.setTextSize(0);
  display.setTextColor(BLACK,WHITE);
  display.setCursor(0,8);
  display.println(" Temp: 4,7C");
  
  display.display();
}

void loop()
{
  // put your main code here, to run repeatedly:
}
