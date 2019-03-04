#include <RotaryEncoder.h>

RotaryEncoder encoder(A2, A3);

int newPos = 0;
int  valor = 7;

void setup()
{ 
  Serial.begin(9600); 
  
  pinMode(8,  OUTPUT);
  pinMode(9,  OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{ 
  static int pos = 0;
   
  encoder.tick();
    
  int newPos = encoder.getPosition();
   
  if (newPos > pos)
  {   if (valor == 11)
      {   valor = 7; }  
      valor ++;
      Serial.println(valor); }

  if (newPos < pos)
  {   if (valor <= 8)
      {   valor = 12; }
      valor --;
      Serial.println(valor); }

  digitalWrite(valor, HIGH);    
  delay(2);                       
  digitalWrite(valor, LOW); 
  delay(2); 
     
  pos = newPos;
  
  
}

