#include <Arduino.h>
#include "TestsSampletoy.h"
extern "C"{ //C header inclusions
    // #include "SampletoyUtility.h"
    #include "SampletoyIO.h"
}

const int DAC_OUT_BUS[] {35, 26, 14, 12, 34, 25, 27, 13};
#define DAC_CLOCK_PIN 25
#define DAC_BUS_WIDTH 8
/// PINS 2, 4, 17, 18, 21, 23, 36, 34 DEFINE DAC OUT BYTE BUS
/// PIN 25 IS DAC CLOCK BIT, it controls which byte audio information is placed onto
/// We have limited IO pins, therefore i'm not allocating a full 16 bit wide bus, but this method. Still need to implement, obvs this requires flipflops

//declare memory allocations
uint8_t dacPort = 0;

// put function declarations here:
void placeDacPortOnPins();

//test declarations
void mainTestCounterOverpins(double timeFactor);

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

  //Initialise IO
}

void realloop() { //Real loop, change name for testloop below
}

void loop(){ //Test loop, a clean small loop that you enter by changing the name of the function. Its bad, i know :(
  // Call whatever test loop you need here, write tests in src and import here
  mainTestCounterOverpins(1);
}


// put function definitions here:
int getBitinInt(int number, int bitposition){ return (number & (1<<bitposition)) != 0;}

void placeDacPortOnPins(){
    for (uint8_t bit = 0; bit < DAC_BUS_WIDTH; bit++){
        digitalWrite(DAC_OUT_BUS[bit], getBitinInt(dacPort, bit));
        if (DAC_OUT_BUS[bit] == 17) {
          switch (getBitinInt(dacPort, 2))
          {
          case 0:
            Serial.println("Lo");
            break;
          case 1:
            Serial.println("Hi");
          default:
            Serial.println("Guy");
            break;
          }
        }
    }
}

//Tests definitions
void mainTestCounterOverpins(double timeFactor){
    double blink_interval = 25 * timeFactor;
    placeDacPortOnPins();
    delay(blink_interval);
    dacPort++;
}
