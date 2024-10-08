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
// put function declarations here:
namespace sampletoyMain{
    void switchRuntimeLogic();
}

//interrupt declarations
namespace interrupts{
    void IRAM_ATTR dacLoadNext();
}

namespace runtimeAssets{
    //debug
    bool first_loop_iteration = true; //debug value used to display a message on the first loop of tests
    int temp_generic = 0;
    bool temp_in_use = false;

    //control variables
    bool loop_mode_play_edit = EDIT; //initialise in edit

    //important, functional, memory allocations
    playlist instance_playlist;
            //add bpm 140 to playlist
    masterchannel session_master_channel;
    // channel sub_channels[TOTAL_CHANNELS]; removed as of implementation of playlist
    uint16_t dac_buffer[DAC_BUFFER_SIZE] = {0};

}
//@todo LABEL YOUR TESTS IN TERMINAL

//test declarations
namespace tests{
    void mainTestCounterOverDACBus(double timeFactor);
    void mainTestAudioSynthesis();
    void mainTestChannelFunctionalities();
    void mainTestPwmIndependence();
    void IRAM_ATTR mainTestInterruptFunctionality();
    void mainReportInterruptOnPin();
    void mainTestMathSynthesisPipeline();
    void mainTestPlaylistFunctionalities();
}

//debugs, tests that should be removed when doing a release build
namespace debug{
    void DumpChannelData(const Channel *target, uint8_t channel_number);
    void DumpMasterData(const MasterChannel *target);
    bool interrupt_reported = false;
}

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
  attachInterrupt(INTERRUPT_PIN_SEND_NEXT_SAMPLE_TO_DAC, interrupts::dacLoadNext, FALLING);

  //Initialise Channels
  for (Channel &this_channel : runtimeAssets::sub_channels){
      reinitialiseChannel(&this_channel);
  }

  reinitialiseMasterChannel(&runtimeAssets::session_master_channel);
  //Initialise IO

  Serial.println("setup finished");
}

void realloop() { //Real loop, change name for testloop below
if (runtimeAssets::loop_mode_play_edit){ //true, PLAY environment is playing
//Setup, change values

//Calculate Synth values, update samples

//Sum to master

//Post, cleanup
}
else{ //EDIT environment

//Setup, change values

//Calculate Synth values, update samples

//Sum to master

//Post, cleanup
}
    runtimeAssets::first_loop_iteration = false;
}

void loop(){ //Test loop, a clean small loop that you enter by changing the name of the function. Its bad, i know :(
    // Call whatever test loop you need here, write tests in src and import here
    //Should be inaccessible to realloop
    if (runtimeAssets::first_loop_iteration){
        tests::mainTestPlaylistFunctionalities();
    }
    runtimeAssets::first_loop_iteration = false;
}


// put function definitions here:
//mititage implementation into this section, to only those which are runtime

namespace sampletoyMain{
    void switchRuntimeLogic(){
        /*
        @brief changes the main loop to go from writing mode to playing mode
        */
        if (runtimeAssets::loop_mode_play_edit){
            runtimeAssets::loop_mode_play_edit = EDIT;
            runtimeAssets::first_loop_iteration = true;
        } else {
            runtimeAssets::loop_mode_play_edit = PLAY;
            runtimeAssets::first_loop_iteration = true;
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

//Tests definitions #remove in final version
namespace tests {
    void mainTestCounterOverDACBus(double timeFactor) {
        /*
        Somewhat redundant function now, checks that the output pins are truely outputting and unlinked
        */
        //test pinout
        if (runtimeAssets::first_loop_iteration) {
            Serial.println("running test counter over DAC pins, pins show boolean value of a counting uint8 ");
            Serial.println("output pins in LSB to MSB order is 5, 19, 22, 26, 4, 18, 21, 25");
            runtimeAssets::first_loop_iteration = false; // don't display message again
        }
        double blink_interval = 25 * timeFactor;
        placeDacPortOnPins();
        delay(blink_interval);
        //dac_port++;
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
        if (runtimeAssets::first_loop_iteration){ //DAC CLOCK blinks every 0.25 seconds.
            //analogWriteFrequency(4);
            Serial.println("first runtime check successful");
        }

        if (debug::interrupt_reported){
            if(runtimeAssets::temp_generic % 44100 == 0){
                Serial.printf("button pressed %u times... \n" , runtimeAssets::temp_generic);
            }
            //Serial.printf("button pressed %u times... \n" , temp_generic);
            debug::interrupt_reported = false;
        }
        //note. THIS WORKS HOLY SHIT YES!!!!

    }

    void mainTestMidiPlaylistDebugSetup1(){
        //Creates sustained note on C4, lasts 1 second on, one second off
    }

    void mainTestMathSynthesisPipeline(){
        //setup midi information
    }

    void mainTestPlaylistFunctionalities(){
            //test 1
        Serial.println("test1: Testing generic empty midi event really is generic empty");
        // create empty event, compare to generic empty, make sure they're the same
        midinote debug_empty_midi_event = generateMidiEventFromVariables(0, 0, 0);
        Serial.printf("%u == %u \n", midinoteReturnTimePointer(&debug_empty_midi_event), midinoteReturnTimePointer(&empty_midi_note_generic));
        Serial.printf("%u == %u \n", midinoteReturnLength(&debug_empty_midi_event), midinoteReturnLength(&empty_midi_note_generic));
        Serial.printf("%u == %u \n", midinoteReturnMidiCode(&debug_empty_midi_event), midinoteReturnMidiCode(&empty_midi_note_generic));
        Serial.println("format debug = generic, any mismatches are bugs, end test1 \n");
            //test 2
        Serial.println("test2: ");
    }

     void mainTestChannelFunctionalities() {
        /*
        Tests that the channels, and their methods are implemented correctly with all the pointer bullshit i wrote in there.
        Mostly just editing and reading out of the memory
        */
        channel sub_channels[TOTAL_CHANNELS]; //legacy implementation, but useful for testing

        if (runtimeAssets::first_loop_iteration) {
            Serial.println("running tests on the implementation and functionality of SampletoyChannel.c/h");
            Serial.println("Beginning tests on functions:");
            delay(5000);
            //Assign increasing values for different channels using SET, then print it to terminal using GET. Sweep all channels
            int counter = 0;            
            for (Channel &channel_target : sub_channels){
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
            for (Channel &this_channel : sub_channels){
                debug::DumpChannelData(&this_channel, channel_counter);
                channel_counter++;
            }
            //Reset
            for (Channel &this_channel : sub_channels){
                reinitialiseChannel(&this_channel);
            }
            channel_counter = 1;
            for (Channel &this_channel : sub_channels){
                debug::DumpChannelData(&this_channel, channel_counter);
                channel_counter++;
            }
            Serial.println("testing master in 5 seconds...");
            delay(5000);
            //run same test on Master
            masterSetLevel(&runtimeAssets::session_master_channel, counter * 10, (counter + 1) * 10);
            counter = counter + 2;
            Serial.println("intermediate test on setlevel");
            debug::DumpMasterData(&runtimeAssets::session_master_channel);
            //testing first of the two add to level functions
            resetMasterLevelToMiddle(&runtimeAssets::session_master_channel);
            addSignalToMasterLevelLeft(&runtimeAssets::session_master_channel, counter);
            counter++;
            addSignalToMasterLevelRight(&runtimeAssets::session_master_channel, counter);
            counter++;
            masterSetGain(&runtimeAssets::session_master_channel, counter);
            counter++;
            masterSetPrescale(&runtimeAssets::session_master_channel, counter);
            counter++;
            masterSetMS(&runtimeAssets::session_master_channel, counter);
            counter++;
            debug::DumpMasterData(&runtimeAssets::session_master_channel);
            //reset, check reset is correct
            reinitialiseMasterChannel(&runtimeAssets::session_master_channel);
            debug::DumpMasterData(&runtimeAssets::session_master_channel);
        }
    }

    void IRAM_ATTR mainTestInterruptFunctionality(){
        runtimeAssets::temp_in_use = true;
        runtimeAssets::temp_generic++;
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
    void IRAM_ATTR dacLoadNext(){
        //placeDacPortOnPins(); //or some shit like this when i actually implement it
    }
}