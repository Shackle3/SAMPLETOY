//mainloop written by fabian, add your name here if you contribute

#include <Arduino.h>
#include <vector>
#include <chrono>
#include <esp32-hal-ledc.h>

extern "C"{ //C header inclusions
    #include "SampletoyUtility.h"
    #include "SampletoyIO.h"
    #include "SampletoyChannel.h"
    #include "SampletoyPlaylist.h"
}

const int DAC_OUT_BUS[] {5, 19, 22, 26, 4, 18, 21, 25}; //@todo remove these, opt for different system wherein information is dealt
#define DAC_CLOCK_PIN 23
#define DAC_CLOCK_FREQ 44100
#define DAC_BUS_WIDTH 8
#define INTERRUPT_PIN_SEND_NEXT_SAMPLE_TO_DAC 25
#define DAC_BUFFER_SIZE 64
/// PIN 25 IS DAC CLOCK BIT, it controls which byte audio information is placed onto
/// We have limited IO pins, therefore i'm not allocating a full 16 bit wide bus, but this method. Still need to implement, obvs this requires flipflops
#define TOTAL_CHANNELS 16
#define MAX_DB_VALUE 65535 //max val of uint_16
#define EDIT false
#define PLAY true
// put function declarations here:
namespace SampletoyMain{
    void switchRuntimeLogic();
}

//test declarations
namespace debug{
    void DumpChannelData(const Channel *target, uint8_t channel_number);
    void DumpMasterData(MasterChannel *target);
    bool interrupt_reported = false;
}

namespace tests{
    void mainTestCounterOverDACBus(double timeFactor);
    void mainTestAudioSynthesis();
    void mainTestChannelFunctionalities();
    void mainTestPwmIndependence();
    void IRAM_ATTR mainTestInterruptFunctionality();
    void mainReportInterruptOnPin();
    void mainTestMathSynthesisPipeline();
}

//interrupt declarations
namespace interrupts{
    void IRAM_ATTR dacLoadNextSignalInterrupt();
}

namespace runtime_assets{
    //debug
    bool first_loop_iteration = true; //debug value used to display a message on the first loop of tests
    int temp_generic = 0;
    bool temp_in_use = false;

    //control variables
    bool loop_mode_play_edit = EDIT; //initialise in edit

    //runtime assets/variables, memory allocations
    playlist instance_playlist;
            //add bpm 140 to playlist
    masterchannel session_master_channel;
    channel sub_channels[TOTAL_CHANNELS];
    uint16_t dac_buffer[DAC_BUFFER_SIZE] = {0};

}
//@todo LABEL YOUR TESTS IN TERMINAL

void setup() {
  Serial.begin(115200); //setup baud
  Serial.println("Init SAMPLETOY build 0.2, Written by Fabian Lee! Hello Developer and or Hackerman!");

  //setup DAC output bus
  /*for (uint8_t pin : DAC_OUT_BUS){
    pinMode(pin, OUTPUT);
  } @todo reimplement the following back into code as 2 pin shift register setup*/

    //setup DAC signal
  pinMode(DAC_CLOCK_PIN, OUTPUT);
  analogWriteFrequency(DAC_CLOCK_FREQ); //initialise interrupt clock
  analogWrite(DAC_CLOCK_PIN, 1); // assign clock
    //setup interrupt reciever pin for sending samples to dac
  pinMode(INTERRUPT_PIN_SEND_NEXT_SAMPLE_TO_DAC, INPUT_PULLUP);
  
  //attach interrupts, set to interrupt when falling signal. Use Pullup across project for consistency
  attachInterrupt(INTERRUPT_PIN_SEND_NEXT_SAMPLE_TO_DAC, tests::mainTestInterruptFunctionality, FALLING);

  //Initialise Channels
  for (Channel &this_channel : runtime_assets::sub_channels){
      reinitialiseChannel(&this_channel);
  }

  reinitialiseMasterChannel(&runtime_assets::session_master_channel);
  //Initialise IO

  Serial.println("setup finished");
}

void realloop() { //Real loop, change name for testloop below
if (runtime_assets::loop_mode_play_edit){ //true, logic is playing
//Setup, change values

//Calculate Synth values, update samples

//Sum to master

//Post, cleanup
}
else{
    //Setup, change values

//Calculate Synth values, update samples

//Sum to master

//Post, cleanup
}
    runtime_assets::first_loop_iteration = false;
}

void loop(){ //Test loop, a clean small loop that you enter by changing the name of the function. Its bad, i know :(
    // Call whatever test loop you need here, write tests in src and import here
    //Should be inaccessible to realloop
    if (runtime_assets::first_loop_iteration){
        
    }
    tests::mainReportInterruptOnPin();
    runtime_assets::first_loop_iteration = false;
}


// put function definitions here:
//mititage implementation into this section, to only those which are runtime

namespace SampletoyMain{
    void switchRuntimeLogic(){
        /*
        @brief changes the main loop to go from writing mode to playing mode
        */
        if (runtime_assets::loop_mode_play_edit){
            runtime_assets::loop_mode_play_edit = EDIT;
            runtime_assets::first_loop_iteration = true;
        } else {
            runtime_assets::loop_mode_play_edit = PLAY;
            runtime_assets::first_loop_iteration = true;
        }
    }
}

namespace PlayFunctions{
    //write play runtime functions here
}

namespace WriteFunctions{
    //write Write runtime functions here
}

namespace SampletoyIO{ //mostly runtime so IO is implemented within main
}

namespace SampletoyInterrupts{

}

//Tests definitions
namespace tests {
    void mainTestCounterOverDACBus(double timeFactor) {
        /*
        Somewhat redundant function now, checks that the output pins are truely outputting and unlinked
        */
        //test pinout
        if (runtime_assets::first_loop_iteration) {
            Serial.println("running test counter over DAC pins, pins show boolean value of a counting uint8 ");
            Serial.println("output pins in LSB to MSB order is 5, 19, 22, 26, 4, 18, 21, 25");
            runtime_assets::first_loop_iteration = false; // don't display message again
        }
        double blink_interval = 25 * timeFactor;
        placeDacPortOnPins();
        delay(blink_interval);
        //dac_port++;
    }

    void mainTestChannelFunctionalities() {
        /*
        Tests that the channels, and their methods are implemented correctly with all the pointer bullshit i wrote in there.
        Mostly just editing and reading out of the memory
        */
        if (runtime_assets::first_loop_iteration) {
            Serial.println("running tests on the implementation and functionality of SampletoyChannel.c/h");
            Serial.println("Beginning tests on functions:");
            delay(5000);
            //Assign increasing values for different channels using SET, then print it to terminal using GET. Sweep all channels
            int counter = 0;            
            for (Channel &channel_target : runtime_assets::sub_channels){
                setChannelLevel(&channel_target, counter, counter + 1);
                counter = counter + 2;
                setChannelGain(&channel_target, counter);
                counter++;
                setChannelLR(&channel_target, counter);
                counter++;
                setChannelMS(&channel_target, counter);
                counter++;
                
            }
            //unique values on all channels
            int channel_counter = 1;
            for (Channel &this_channel : runtime_assets::sub_channels){
                debug::DumpChannelData(&this_channel, channel_counter);
                channel_counter++;
            }
            //Reset
            for (Channel &this_channel : runtime_assets::sub_channels){
                reinitialiseChannel(&this_channel);
            }
            channel_counter = 1;
            for (Channel &this_channel : runtime_assets::sub_channels){
                debug::DumpChannelData(&this_channel, channel_counter);
                channel_counter++;
            }
            Serial.println("testing master in 5 seconds...");
            delay(5000);
            //run same test on Master
            masterSetLevel(&runtime_assets::session_master_channel, counter * 10, (counter + 1) * 10);
            counter = counter + 2;
            Serial.println("intermediate test on setlevel");
            debug::DumpMasterData(&runtime_assets::session_master_channel);
            //testing first of the two add to level functions
            resetMasterLevelToMiddle(&runtime_assets::session_master_channel);
            addSignalToMasterLevelLeft(&runtime_assets::session_master_channel, counter);
            counter++;
            addSignalToMasterLevelRight(&runtime_assets::session_master_channel, counter);
            counter++;
            masterSetGain(&runtime_assets::session_master_channel, counter);
            counter++;
            masterSetPrescale(&runtime_assets::session_master_channel, counter);
            counter++;
            masterSetMS(&runtime_assets::session_master_channel, counter);
            counter++;
            debug::DumpMasterData(&runtime_assets::session_master_channel);
            //reset, check reset is correct
            reinitialiseMasterChannel(&runtime_assets::session_master_channel);
            debug::DumpMasterData(&runtime_assets::session_master_channel);
        }
    }

    void mainTestPwmIndependence(){ 
        /*
        Tests and demonstrates the functionality of analogue write, as well as its code independence.
        */
        analogWriteFrequency(4); //frequency
        analogWrite(DAC_CLOCK_PIN, 1); // pin, scaling factor x
        for(;;){
            Serial.println("code is theoretically frozen on this line! If light is blinking pwm is runtime independent");
        } //runtime independent

    }

    void mainReportInterruptOnPin(){ 
        /*
        Our goal here to to check, that pin PWM signals can trigger interrupts by routing the DAC Clock pin to the DAC interrupt, and
        successfully recieving/performing an interrupt operation.

        Mind you interrupts are finniky, at the moment it reports like thousands of interrupts
        */
        if (runtime_assets::first_loop_iteration){ //DAC CLOCK blinks every 0.25 seconds.
            //analogWriteFrequency(4);
            Serial.println("first runtime check successful");
        }

        if (debug::interrupt_reported){
            if(runtime_assets::temp_generic % 44100 == 0){
                Serial.printf("button pressed %u times... \n" , runtime_assets::temp_generic);
            }
            //Serial.printf("button pressed %u times... \n" , temp_generic);
            debug::interrupt_reported = false;
        }
        //note. THIS WORKS HOLY SHIT YES!!!!

    }

    void mainTestMathSynthesisPipeline(){
        //setup midi information
    }

    void IRAM_ATTR mainTestInterruptFunctionality(){
        runtime_assets::temp_in_use = true;
        runtime_assets::temp_generic++;
        // Serial.printf("button pressed %u times... \n" , temp_generic); ILLEGAL, interrupt cannot output to serial
        // probably do to its memory allocation :/
        debug::interrupt_reported = true;
    }
}

//generic debug operations
namespace debug {
    void DumpChannelData(const Channel *target, uint8_t channel_number) {
        Serial.println("DEBUG:::dumping channel information for channel:");
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

namespace interrupts{
    /// DO NOTE THAT INTERRUPTS CANT DO PRINT, so i have found out. 
    void IRAM_ATTR dacLoadNextSignalInterrupt(){
        //placeDacPortOnPins(); //or some shit like this when i actually implement it
    }
}