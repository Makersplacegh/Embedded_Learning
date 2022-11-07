#include <Arduino.h>
#include <EloquentTinyML.h>
#include "model.h"


#define NB_INPUTS 1
#define NB_OUTPUTS 1
#define Tensor_arena 2*1024

Eloquent::TinyML::TfLite<NB_INPUTS, NB_OUTPUTS, Tensor_arena> my_model;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  my_model.begin(model);
}

void loop() {
  // put your main code here, to run repeatedly:
  float x = random(20) + (random(10)/10);
  float input[NB_INPUTS] = {x};
  float output = my_model.predict(input);

  Serial.print("x : ");
  Serial.print(x);
  Serial.print(" y : ");
  Serial.print(2*x+1);
  Serial.print(" prdeicted y : ");
  Serial.println(output);
  delay(1000);
}