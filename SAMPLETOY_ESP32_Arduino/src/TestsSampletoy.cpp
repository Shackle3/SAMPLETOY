//
// Created by Fabian Uni on 12/07/2024.
//
//Main tests in main
//Cpp headers
#ifdef SAMPLETOY_ESP32_ARDUINO_SAMPLETOYCHANNEL_H
#include <Arduino.h>
//C headers
extern "C"{
    #include "SampletoyChannel.h"
}

#endif

/* IMPORTANT NOTE ON FORMATTING TESTS
 *
 * Please use the STTest_ prefix when naming test functions for readability
 * and to make removing tests easier later
 *
 * Thank you :)
 *
 * eg: STTest_testChannelSet(Channel* target){...}
*/

//tests on STChannel
std::vector