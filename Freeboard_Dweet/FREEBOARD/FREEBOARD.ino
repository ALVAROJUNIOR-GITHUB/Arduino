//https://freeboard.io/board/THxpLr
//https://dweet.io/follow/ALVAROJR
#include <SPI.h>
#include <Ethernet.h>

const int analogIn = A0;
int analogVal = 0;
const int label = 23;
int NUM = random(1,100);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 14);

EthernetClient client;

char server[] = "www.dweet.io";

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 100L * 1L;   // delay between updates, in milliseconds // the "L" is needed to use long type numbers

void setup()
{ Serial.begin(9600);
  Serial.println("--- Start ---");
  delay(1000);
  Ethernet.begin(mac, ip); 
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP()); }

void loop() 
{  if (client.available()) {
      char c = client.read();
      Serial.write(c); }
   if (millis() - lastConnectionTime > postingInterval) {
      httpRequest(); }}

void httpRequest()
{  client.stop();
   if (client.connect(server, 80)) {
      Serial.println("connected");
     
      analogVal = analogRead(analogIn);
    
      String s = "POST /dweet/for/ALVAROJR?A0=";
      s.concat(analogVal);
      Serial.print(s); 
      client.print(s);

      Serial.println(random(1,10)); 
      client.print("&label=");
      client.println(random(1,10));

      client.println("Host: www.dweet.io");
      client.println("Connection: close");
      client.println();

      lastConnectionTime = millis(); }
    else { Serial.println("connection failed"); }}
