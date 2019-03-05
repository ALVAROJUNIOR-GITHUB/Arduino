
// https://www.w3schools.com/html/html_examples.asp
// https://tomeko.net/online_tools/cpp_text_escape.php?lang=en

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
ESP8266WebServer server(80);
#else
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
WebServer server(80);
#endif

const char pagina_html[] PROGMEM = {"<!DOCTYPE html>\n"
"<html>\n"
"<body>\n"
"\n"
"<h2>NODEMCU</h2>\n"
"<p><b>Exemplo de pagina HTML embarcada no NodeMCU</b></p>\n"
"<p>by Alvaro Lopes de Figueiredo Junior</p>\n"
"\n"
"<p>https://www.w3schools.com/html/html_examples.asp</p>\n"
"<p>https://tomeko.net/online_tools/cpp_text_escape.php?lang=en<p>\n"
"\n"
"<img src=\"https://www.w3schools.com/html/w3schools.jpg\" alt=\"W3Schools.com\" width=\"104\" height=\"142\">\n"
"\n"
"</body>\n"
"</html>"}; 

const char* ssid     = "FINADO ZE LINGUINHA";
const char* password = "CB4001982";

#ifdef LED_BUILTIN
const int led = LED_BUILTIN;
#else
const int led = 13;
#endif

void handleRoot() {
  digitalWrite(led, 1);
#ifdef ESP8266
  server.send_P(200, "text/html", pagina_html);
#else
  server.send(200, "text/plain", "hello from esp32!");
#endif
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

#ifdef ESP8266
  if (MDNS.begin("esp8266")) {
#else
  if (MDNS.begin("esp32")) {
#endif
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
