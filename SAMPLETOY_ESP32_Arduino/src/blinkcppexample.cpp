//Here is a simple implementation of BLINK.cpp, and some other really useful commands

#include <Arduino.h>

#define LED_BUILTIN 2

// put function declarations here:
int demomyFunction(int, int);

//Allocate variables

void demosetup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //setup baud
  Serial.println("Init here. blah blah test test written by big dingus");
  int result = demomyFunction(2, 3);
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void demoloop() {
  // put your main code here, to run repeatedly:
  // turn the LED on (HIGH is the voltage level)
  Serial.println("LED HI");
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  Serial.println("LED LO");
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println(demomyFunction(2,3));
  // wait for a second
  delay(1000);
}

// put function definitions here:
int demomyFunction(int x, int y) {
  return x + y;
}

