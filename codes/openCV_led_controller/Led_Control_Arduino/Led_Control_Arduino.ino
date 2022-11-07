#include <cvzone.h>

SerialData serialData(1, 1); //(numOfValsRec,digitsPerValRec)
/*
   0 or 1 - 1 digit
   0 to 99 - 2 digits
   0 to 999 - 3 digits
*/

int valsRec[1]; // array of int with size numOfValsRec
//whatever value is received from python is stored in this array
//even if it is one value, we still have to create an array

int led1 = 2;
int led2 = 3;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  /*initialize our library
     we can include a baud rate but if it is not included,
     the default is 9600
  */
  serialData.begin();
}

void loop() {

  serialData.Get(valsRec);  //command to receive the value
  if (valsRec[0] == 0) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
 if (valsRec[0] == 1) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
   if (valsRec[0] == 2) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  delay(10);
}
