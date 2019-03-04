#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* ssid     = "FINADO ZE LINGUINHA";
const char* password = "CB4001982";

char* topic          = "/teste/esp8266";
char* mqtt_server    = "test.mosquitto.org";

int  x = 0;

WiFiClient espClient;

PubSubClient client(espClient);

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
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("alvaro")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  setup_wifi(); 
  client.setServer(mqtt_server, 1883);
}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();
  
  x = x + 1;
  
  //String payload = "\"Amostra\": ";
  String payload = "Amostra: "; 
  payload += x;
 
  
  
  if (client.connected()){
    Serial.print("Sending payload: ");
    Serial.println(x);

    if (client.publish(topic, (char*) payload.c_str()))
    {
      Serial.println("Publish ok");
    }
    else
    {
      Serial.println("Publish failed");
    }
  }
  delay(1000);
}


