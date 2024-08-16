#include <Arduino.h>
#include "TestsSampletoy.h"
#include <vector>
#include <chrono>

extern "C"{ //C header inclusions
    #include "SampletoyUtility.h"
    #include "SampletoyIO.h"
    #include "SampletoyChannel.h"
}

const int DAC_OUT_BUS[] {5, 19, 22, 26, 4, 18, 21, 25}; //bit 1,2,3,4,5,6,7,8
#define DAC_CLOCK_PIN 23
#define DAC_BUS_WIDTH 8
/// PIN 25 IS DAC CLOCK BIT, it controls which byte audio information is placed onto
/// We have limited IO pins, therefore i'm not allocating a full 16 bit wide bus, but this method. Still need to implement, obvs this requires flipflops

#define TOTAL_CHANNELS 16
#define MAX_DB_VALUE 65535 //max val of uint_16

//declare memory allocations
uint8_t dac_port = 0;
Channel sub_channels[TOTAL_CHANNELS];
MasterChannel session_master_channel;



// put function declarations here:
void placeDacPortOnPins();
void sumChannelsOnDacPort();

//test declarations
void mainTestCounterOverDACBus(double timeFactor);

//Global variables
  //Debug
  bool first_runtime = true; //debug value used to display a message on the first loop of tests

  //System Setup
  int beats_per_minute = 140; //@todo implement this as struct in a Generation Coordinator struct system

//@todo LABEL YOUR TESTS IN TERMINAL

void setup() {
  Serial.begin(115200); //setup baud
  Serial.println("Init SAMPLETOY build 0.2, Written by Fabian Lee! Hello Developer and or Hackerman!");

  //setup DAC output bus
  for (uint8_t pin : DAC_OUT_BUS){
    pinMode(pin, OUTPUT);
  }
  pinMode(DAC_CLOCK_PIN, OUTPUT);

  //Initialise Channels
  for (Channel this_channel : sub_channels){
      reinitialiseChannel(&this_channel);
  }

  reinitialiseMasterChannel(&session_master_channel);
  //Initialise IO

  Serial.println("setup finished");
}

void realLoop() { //Real loop, change name for testloop below
//Below is the basis for the running music generation loop
//Setup, change values

//Calculate Synth values, update samples

//Sum to master

//Post, cleanup

    first_runtime = false;
}

void loop(){ //Test loop, a clean small loop that you enter by changing the name of the function. Its bad, i know :(
    // Call whatever test loop you need here, write tests in src and import here
    //Should be inaccessible to realloop
    first_runtime = false;
}


// put function definitions here:
//mitigate functions here, should only be session functions if possible
void placeDacPortOnPins(){
  /*
   *  Takes information in dacPort and places it on pins as hi/lo values
  */
    for (uint8_t bit = 0; bit < DAC_BUS_WIDTH; bit++){ //bit in range 0 to bus width
        digitalWrite(DAC_OUT_BUS[bit], getBitinInt(dac_port, bit)); //set output to hi or low
    }
}

void sumChannelsOnDacPort(){ //@todo REWRITE FOR NEW CHANNEL SYSTEM
    /*
    * Takes all the channels and sums value to dac port
    */
    dac_port = 0; //reset dac Port
    for (Channel channel : sub_channels)
    {
        //master_channel = master_channel + channel;
    }
}

//Tests definitions (run and chrono multiple tests)
namespace tests {
    void mainTestCounterOverDACBus(double timeFactor) {
        //test pinout
        if (first_runtime) {
            Serial.println("running test counter over DAC pins, pins show boolean value of a counting uint8 ");
            Serial.println("output pins in LSB to MSB order is 5, 19, 22, 26, 4, 18, 21, 25");
            first_runtime = false; // don't display message again
        }
        double blink_interval = 25 * timeFactor;
        placeDacPortOnPins();
        delay(blink_interval);
        dac_port++;
    }

    void mainTestAudioSynthesis() {
        //test audio synthesis functions
    }

    void mainTestChannelfunctionalities() {
        if (first_runtime) {
            Serial.println("running tests on the implementation and functionality of SampletoyChannel.c/h");
            Serial.println("Beginning tests on functions:");
            delay(5000);
            //Assign increasing values for different channels using SET, then print it to terminal using GET. Sweep all channels
            //Reset
            //Recheck all values are reset
            delay(5000);
            //run same test on Master
            //test resetting only gain
            //test superposition
            //test reset
            //check all values are reset
        }
    }
}
namespace debug {
    void DumpChannelData(const Channel *target, uint8_t channel_number) {
        Serial.println("DEBUG:::dumping channel information for channel: %d", channel_number);
        Serial.println(channel_number);
        Serial.println("in format L, R, ms, g, lrp");
        Serial.println(channelGetLevelLeft(target));
        Serial.println(channelGetLevelRight(target));
        Serial.println(channelGetMonoSide(target));
        Serial.println(channelGetGain(target));
        Serial.println(channelGetLR(target));
    }

    void DumpMasterData(MasterChannel *target) {
        Serial.println("DEBUG:::dumping master information");
        Serial.println("in format L, R, g, pre, ms");
        Serial.println(masterGetLevelLeft(target));
        Serial.println(masterGetLevelRight(target));
        Serial.println(masterGetGain(target));
        Serial.println(masterGetPrescale(target));
        Serial.println(masterGetMS(target));
    }
}