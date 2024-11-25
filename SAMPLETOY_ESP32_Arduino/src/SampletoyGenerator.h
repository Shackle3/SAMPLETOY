//
// Created by Fabian Uni on 25/11/2024.
//

#ifndef SAMPLETOY_ESP32_ARDUINO_SAMPLETOYGENERATOR_H
#define SAMPLETOY_ESP32_ARDUINO_SAMPLETOYGENERATOR_H
#include <stdint.h>

typedef struct Generator{
    bool generator_type; //t = MATHGEN, f = WAVETABLE
    uint8_t define_wave; //number corresponds to a wave
    uint16_t frequency;
} generator;

#endif //SAMPLETOY_ESP32_ARDUINO_SAMPLETOYGENERATOR_H
