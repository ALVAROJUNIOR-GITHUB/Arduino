
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* SSID        = "FINADO ZE LINGUINHA"; 
const char* PASSWORD    = "CB4001982";  
                           
const char* BROKER_MQTT = "test.mosquitto.org";  
//const char* BROKER_MQTT = "iot.eclipse.org";  


int BROKER_PORT         = 1883;  



void initPins();
void initSerial();
void initWiFi();
void initMQTT();



WiFiClient espClient;
PubSubClient MQTT(espClient);  



void setup()
{  
  initPins();
  
  Serial.begin(115200);
  
  initWiFi();
  initMQTT();
  pinMode(LED_BUILTIN, OUTPUT);
}



void loop()
{
  if (!MQTT.connected()) 
  {
    reconnectMQTT();
  }
  recconectWiFi();
  MQTT.loop();
}



void initPins() 
{
  pinMode(D1, OUTPUT);
  digitalWrite(D1, 0);

  pinMode(D2, OUTPUT);
  digitalWrite(D2, 0);

  pinMode(D3, OUTPUT);
  digitalWrite(D3, 0);

  pinMode(D4, OUTPUT);
  digitalWrite(D4, 0);

  digitalWrite(LED_BUILTIN, LOW); 
  

  delay(2000);


  pinMode(D1, OUTPUT);
  digitalWrite(D1, 1);

  pinMode(D2, OUTPUT);
  digitalWrite(D2, 1);

  pinMode(D3, OUTPUT);
  digitalWrite(D3, 1);

  pinMode(D4, OUTPUT);
  digitalWrite(D4, 1);

  digitalWrite(LED_BUILTIN, HIGH); 
}



void initWiFi()
{
  delay(10);
  Serial.println("Conectando-se em: " + String(SSID));

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado na Rede " + String(SSID) + " | IP => ");
  Serial.println(WiFi.localIP());
}



void initMQTT() 
{
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(mqtt_callback);
}



void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
  String message;
  for (int i = 0; i < length; i++) 
  {
    char c = (char)payload[i];
    message += c;
  }
  
  Serial.println("Tópico => " + String(topic) + " | Valor => " + String(message));

  if (message == "R1_OFF") 
  {
    pinMode(D5, OUTPUT);
    digitalWrite(D5, 1);
    digitalWrite(LED_BUILTIN, HIGH); 
  }
  if (message == "R1_ON")
  {
    pinMode(D5, OUTPUT);
    digitalWrite(D5, 0);
    digitalWrite(LED_BUILTIN, LOW); 
  }

  if (message == "R2_OFF") 
  {
    pinMode(D6, OUTPUT);
    digitalWrite(D6, 1);
    digitalWrite(LED_BUILTIN, HIGH); 
  }
  if (message == "R2_ON")
  {
    pinMode(D6, OUTPUT);
    digitalWrite(D6, 0);
    digitalWrite(LED_BUILTIN, LOW); 
  }

  if (message == "R3_OFF") 
  {
    pinMode(D7, OUTPUT);
    digitalWrite(D7, 1);
    digitalWrite(LED_BUILTIN, HIGH); 
  }
  if (message == "R3_ON")
  {
    pinMode(D7, OUTPUT);
    digitalWrite(D7, 0);
    digitalWrite(LED_BUILTIN, LOW); 
  }


  if (message == "R4_OFF") 
  {
    pinMode(D8, OUTPUT);
    digitalWrite(D8, 1);
    digitalWrite(LED_BUILTIN, HIGH); 
  }
  if (message == "R4_ON")
  {
    pinMode(D8, OUTPUT);
    digitalWrite(D8, 0);
    digitalWrite(LED_BUILTIN, LOW); 
  }
  
  Serial.flush();
}



void reconnectMQTT()
{
  while (!MQTT.connected())
  {
    Serial.println("Tentando se conectar ao Broker MQTT: " + String(BROKER_MQTT));
    if (MQTT.connect("ESP8266-ESP12")) 
    {
      Serial.println("Conectado");
      MQTT.subscribe("RELE_AUX");
    } else {
      Serial.println("Falha ao Reconectar");
      Serial.println("Tentando se reconectar em 2 segundos");
      delay(2000);
    }
  }
}



void recconectWiFi()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
}
