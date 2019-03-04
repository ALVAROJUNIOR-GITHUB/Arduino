#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5   // PINO 2 (D1) DO NODEMCU

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

const char* ssid        = "FINADO ZE LINGUINHA";
const char* password    = "CB4001982";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

long  lastMsg  = 0;
int   inPin    = 5;
float temp     = 0;
float temp_aux = 0;

float temp_MIN = 100;
float temp_MAX = 0;

bool  primeira = true;

void setup_wifi()
{
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() 
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("arduinoClient_temperature_sensor"))
    {
      Serial.println("connected");
      digitalWrite(BUILTIN_LED, LOW);
      delay(5000);
    }
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      digitalWrite(BUILTIN_LED, LOW);
      delay(5000);
    }
  }
}
 
void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);    
  digitalWrite(BUILTIN_LED, HIGH);
  Serial.begin(115200);
  setup_wifi(); 
  client.setServer(mqtt_server, 1883);
  pinMode(inPin, INPUT);
  sensors.begin();
}

void loop()
{
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) 
  {
    lastMsg = now;
    sensors.setResolution(12);
    sensors.requestTemperatures();  

    if (primeira == true)
    {  
        temp = sensors.getTempCByIndex(0);
       
        temp_MIN = temp;
        temp_MAX = temp;

        Serial.print("ToC: ");
        Serial.print(temp,1);
        Serial.print("  Min: ");   
        Serial.print(temp_MIN,1);
        Serial.print("  Max: ");
        Serial.println(temp_MAX,1);
        
        client.publish("teste/temp",     String(temp,1).c_str());
        client.publish("teste/temp_MIN", String(temp_MIN,1).c_str());
        client.publish("teste/temp_MAX", String(temp_MAX,1).c_str());       
      
        digitalWrite(BUILTIN_LED, LOW);
        delay(500);
        digitalWrite(BUILTIN_LED, HIGH);
        delay(500); 
    
        primeira = false;
    }
    
 
    
    if (primeira == false)
    {  
        temp_aux = temp;
        
        temp = sensors.getTempCByIndex(0);
          
        if (temp != temp_aux)
        {       
           
          if (temp < temp_MIN)
              temp_MIN = temp; 
          if (temp > temp_MAX)
              temp_MAX = temp; 
          
          Serial.print("ToC: ");
          Serial.print(temp,1);
          Serial.print("  Min: ");   
          Serial.print(temp_MIN,1);
          Serial.print("  Max: ");
          Serial.println(temp_MAX,1);
        
          client.publish("teste/temp",     String(temp,1).c_str());
          client.publish("teste/temp_MIN", String(temp_MIN,1).c_str());
          client.publish("teste/temp_MAX", String(temp_MAX,1).c_str()); 
            
          digitalWrite(BUILTIN_LED, LOW);
          delay(500);
          digitalWrite(BUILTIN_LED, HIGH);
          delay(500); 
        }
     }
  }
}
