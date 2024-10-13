//
// Created by Fabian Uni on 4/09/2024.
//

#ifndef SAMPLETOY_ESP32_ARDUINO_SAMPLETOYMACROS_H
#define SAMPLETOY_ESP32_ARDUINO_SAMPLETOYMACROS_H
//@todo implement all of the macros HERE and not in the individual submodules
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

//MAIN MACROS
//
#define DAC_CLOCK_PIN 23
#define DAC_CLOCK_FREQ 44100
#define DAC_BUS_WIDTH 8
#define INTERRUPT_PIN_SEND_NEXT_SAMPLE_TO_DAC 25
#define DAC_BUFFER_SIZE 128
/// PIN 25 IS DAC CLOCK BIT, it controls which byte audio information is placed onto
/// We have limited IO pins, therefore i'm not allocating a full 16 bit wide bus, but this method. Still need to implement, obvs this requires flipflops
#define TOTAL_CHANNELS 16
#define MAX_DB_VALUE 65535 //max val of uint_16
#define EDIT false
#define PLAY true

//PLAYLIST MACROS:
//
//Max possible synthesizers in playlist
#define MAX_CHANNELS_OR_TRACKS 16 //Current supported max size (from code) is 255 @todo test with increasing or decreasing
//subdivisions per beat, so for the example of 4, it means the shortest note is a semiquaver
#define SUBDIVISIONS_PER_BEAT 4
#define MIDITRACKARRAYSIZE 64
#define DEFAULT_BPM 140

//AUDIO SYNTHESIS MACROS
//
//time interval for once sample (double) in seconds
#define SAMPLERATE 44100
#define SAMPLE_DURATION 0.00002267573 //SAMPLE RATE IS FIXED TO 44.100 khz, WILL CAUSE BUGS IF CHANGED

//CHANNEL MACROS
//
#define uint8_middle 128
#define uint32_middle 2147483648

#endif //SAMPLETOY_ESP32_ARDUINO_SAMPLETOYMACROS_H
