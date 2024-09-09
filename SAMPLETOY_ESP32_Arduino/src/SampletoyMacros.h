//
// Created by Fabian Uni on 4/09/2024.
//

#ifndef SAMPLETOY_ESP32_ARDUINO_SAMPLETOYMACROS_H
#define SAMPLETOY_ESP32_ARDUINO_SAMPLETOYMACROS_H
//@todo implement all of the macros HERE and not in the individual submodules
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

//PLAYLIST MACROS:
//
//Max possible synthesizers in playlist
#define MAX_SYNTHESIZERS 16 //Current supported max size (from code) is 255
//subdivisions per beat, so for the example of 4, it means the shortest note is a semiquaver
#define SUBDIVISIONS_PER_BEAT 4

//AUDIO SYNTHESIS MACROS
//
//time interval for once sample (double) in seconds
#define SAMPLE_DURATION 0.00002267573 //SAMPLE RATE IS FIXED TO 44.100 khz, WILL CAUSE BUGS IF CHANGED

#endif //SAMPLETOY_ESP32_ARDUINO_SAMPLETOYMACROS_H
