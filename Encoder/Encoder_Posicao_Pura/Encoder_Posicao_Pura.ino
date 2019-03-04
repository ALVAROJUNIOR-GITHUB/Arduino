#include <RotaryEncoder.h>

RotaryEncoder encoder(A2, A3);

int newPos = 0;
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Gire o encoder...");
}

void loop()
{ 
  static int pos = 0;
  encoder.tick();
  
  int newPos = encoder.getPosition();

  if (pos != newPos)
  {
    Serial.print(newPos);
    Serial.println();
    pos = newPos;
  }
}
