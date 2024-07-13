#include <Arduino.h>
#include "TestsSampletoy.h"
extern "C"{ //C header inclusions
    //#include "SampletoyUtility.h"
    #include "SampletoyIO.h"
}

const int DAC_OUT_BUS[] {5, 19, 22, 26, 4, 18, 21, 25}; //bit 1,2,3,4,5,6,7,8
#define DAC_CLOCK_PIN 23
#define DAC_BUS_WIDTH 8
/// PIN 25 IS DAC CLOCK BIT, it controls which byte audio information is placed onto
/// We have limited IO pins, therefore i'm not allocating a full 16 bit wide bus, but this method. Still need to implement, obvs this requires flipflops

//declare memory allocations
uint8_t dacPort = 0;

// put function declarations here:
void placeDacPortOnPins();

//test declarations
void mainTestCounterOverDACBus(double timeFactor);

//Global variables
bool display_test_message = true; //debug value used to display a message on the first loop of tests
//@todo LABEL YOUR TESTS IN TERMINAL

void setup() {
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
  mainTestCounterOverDACBus(1);
}


// put function definitions here:
int getBitinInt(int number, int bitposition){ return (number & (1<<bitposition)) != 0;}

void placeDacPortOnPins(){
    for (uint8_t bit = 0; bit < DAC_BUS_WIDTH; bit++){ //bit in range 0 to bus width
        digitalWrite(DAC_OUT_BUS[bit], getBitinInt(dacPort, bit)); //set output to hi or low
    }
}

//Tests definitions
void mainTestCounterOverDACBus(double timeFactor){

    if (display_test_message){
      Serial.println("running test counter over DAC pins, pins show boolean value of a counting uint8 ");
      Serial.println("output pins in LSB to MSB order is 5, 19, 22, 26, 4, 18, 21, 25");
      display_test_message = false; // don't display message again
    }
    double blink_interval = 25 * timeFactor;
    placeDacPortOnPins();
    delay(blink_interval);
    dacPort++;
}
