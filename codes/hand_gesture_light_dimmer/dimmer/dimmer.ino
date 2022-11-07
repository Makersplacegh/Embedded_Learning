#include <cvzone.h>

SerialData serialData(1, 2);
int valsRec[1];

int dimLevel=0;
int writeVal = 0;
int light = 3;

void setup() 
{
  serialData.begin();
  pinMode(light, OUTPUT);
}

void loop()
{
  serialData.Get(valsRec);
  writeVal = map(valsRec[0], 0, 60, 0, 255);
  analogWrite(light, writeVal);

  delay(10);
}
