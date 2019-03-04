
void setup() 
{
  
  Serial.begin(9600);
  
  float A1    = 0;
  float A2    = 0;
  float saida = 0;
  
  Serial.println("---------------------------");
  Serial.println("Estabilização Potenciometro");
  Serial.println("---------------------------");
  Serial.println();
  
}

void loop() 
{ 
  
  float fator1 = 0.1;
  float fator2 = 0.9;
  
  // primeira leitura
  //---------------------------------------

  int entrada  = analogRead(A0);
  float A1     = entrada * fator1;
  float saida  = A1;
  float atraso = A1;
  float A2     = atraso * fator2;
  saida        = A1 + A2;
  
  //Serial.print("entrada1: ");
  //Serial.print(entrada);
  //Serial.print("\t");
    
  //Serial.print("A1: ");
  Serial.print((float)A1,1);
  Serial.print("\t");

  //Serial.print("A2: ");
  Serial.print((float)A2,1);
  Serial.print("\t");
  
  //Serial.print("Saida1: ");
  Serial.println((float)saida,1);
  
  delay(100);   


  // segunda leitura
  //---------------------------------------
  while(true)
  {
    
    float entrada2 = analogRead(A0);
    float A1_p     = entrada2 * fator1;
    float A2_p     = saida * fator2;
    saida          = A1_p + A2_p;
  
    //---------------------------------------
    
    //Serial.print("entrada2: ");
    Serial.print(entrada2);
    Serial.print("\t");
      
    //Serial.print("Saida2: ");
    Serial.println(ceil((float)saida),2);
  
    delay(250);   }
        
}
