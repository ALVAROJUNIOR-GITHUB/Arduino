 
#include <TimeLib.h> 
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

//pino 2 do node ligar SDA
//pino 0 do node ligar SCL
U8X8_SSD1306_128X32_UNIVISION_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

const char ssid[] = "FINADO ZE LINGUINHA"; // your network SSID (name)
const char pass[] = "CB4001982";           // your network password

// NTP Servers:
IPAddress timeServer(132, 163, 4, 101);    // time-a.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 102); // time-b.timefreq.bldrdoc.gov
// IPAddress timeServer(132, 163, 4, 103); // time-c.timefreq.bldrdoc.gov

const int timeZone = -2;    // Brasil -2 com horario verao
//const int timeZone = 1;   // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)


WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets

boolean toggle = false;

void setup() 
{
  pinMode(15, OUTPUT);
  
  u8x8.begin();
  u8x8.setPowerSave(0);
     
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  delay(250);
  Serial.println("TimeNTP Example");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  
  Serial.print("IP number assigned by DHCP is ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());
  Serial.println("waiting for sync");
  setSyncProvider(getNtpTime);
}

time_t prevDisplay = 0; // when the digital clock was displayed

void loop()
{  
  if (timeStatus() != timeNotSet) {
    if (now() != prevDisplay) { //update the display only if time has changed
      prevDisplay = now();
      digitalClockDisplay();  
    }
  }
}

void digitalClockDisplay(){

  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  
  Serial.print(" ");

  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");

  Serial.print(year()); 
  Serial.println(); 

  //u8x8.inverse();
  //u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_f);

  //---------------------------
  u8x8.setCursor(0,1);

  if (hour()<10)
    u8x8.print('0'); 
  
  u8x8.print(hour());

  u8x8.print(":");  
  
  if (minute()<10)
    u8x8.print('0');
    
  u8x8.print(minute());

  u8x8.print(":");  
  
  if (second()<10)
    u8x8.print('0');
    
  u8x8.print(second());
  //----------------------------
  
  u8x8.setCursor(0,0);
  
  if (day()<10)
    u8x8.print('0');
    
  u8x8.print(day());
  
  u8x8.print("/");

  if (month()<10)
    u8x8.print('0');
    
  u8x8.print(month());
  
  u8x8.print("/");

  u8x8.print(year()-2000);
  //u8x8.refreshDisplay();  

   


  toggle = !toggle;
  digitalWrite(15,toggle);

}



void printDigits(int digits)
{
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48;     // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  
  //display.setCursor(3,32);
  //display.print("DATA: ");
  //display.setCursor(3,41);
  //display.print("HORA: ");
  //display.display();
  
  while (Udp.parsePacket() > 0);    // discard any previously received packets
  Serial.println("Transmit NTP Request");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");

  
  //display.setCursor(3,32);
  //display.print(" FALHA 'NTP'");
  //display.setCursor(3,41);
  //display.print(" RESET AGORA");
  //display.display();
  
  //digitalWrite(15,HIGH);
  
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  //Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.beginPacket("pool.ntp.br", 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
