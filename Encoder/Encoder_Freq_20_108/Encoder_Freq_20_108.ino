#include <RotaryEncoder.h>

RotaryEncoder encoder(A2, A3);

int newPos = 0;
int valor  = 7;

void setup()
{
  Serial.begin(9600);
  Serial.println(newPos);
}

void loop()
{ 
  static int pos = 0;
  encoder.tick();
  
  int newPos = encoder.getPosition();

  if (newPos < pos)
  {      
    if (valor >= 8)
    {   valor -= 1;
        Serial.println(valor);
        Serial.println(newPos);
        pos = newPos = 0;
    }
    pos = newPos;
  }

  if (newPos > pos)
  { 
    if (valor < 11)
    {   valor += 1;
        Serial.println(valor);
        Serial.println(newPos);
        pos = newPos = 0;
    }
    pos = newPos;

  }
  
}
