#include <Arduino.h>
#include "TestsSampletoy.h"

#define DAC_OUT_BUS {2, 4, 17, 18, 21, 23, 36, 34}
#define DAC_CLOCK_PIN 25
/// PINS 2, 4, 17, 18, 21, 23, 36, 34 DEFINE DAC OUT BYTE BUS
/// PIN 25 IS DAC CLOCK BIT, it controls which byte audio information is placed onto
/// We have limited IO pins, therefore i'm not allocating a full 16 bit wide bus, but this method. Still need to implement, obvs this requires flipflops


// put function declarations here:
int testDacOutputPins(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //setup baud
  Serial.println("Init SAMPLETOY build 0.01, Written by Fabian Lee! Hello Developer and or Hackerman!");
  //setup DAC output bus
  for (uint8_t pin : DAC_OUT_BUS){
    pinMode(pin, OUTPUT);
  }
  pinMode(DAC_CLOCK_PIN, OUTPUT);

  Serial.println("setup finished");
}

void realloop() { //Real loop, change name for testloop below
}

void loop(){ //Test loop, a clean small loop that you enter by changing the name of the function. Its bad, i know :(
  // Call whatever test loop you need here, write tests in src and import here

}


// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}