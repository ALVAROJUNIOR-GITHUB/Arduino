void setup()
{
  Serial.begin(9600);
  Serial.println("----------------------------------");
  Serial.println("SEM Estabilização do Potenciometro");
  Serial.println("----------------------------------");
  Serial.println();  
}

void loop()
{
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(250);       
}
