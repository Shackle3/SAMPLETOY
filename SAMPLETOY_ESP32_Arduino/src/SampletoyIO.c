//
// Created by Fabian Uni on 12/07/2024.
//
#define DAC_CLOCK_PIN 25
#define DAC_BUS_WIDTH 8
/// PINS 2, 4, 17, 18, 21, 23, 36, 34 DEFINE DAC OUT BYTE BUS
/// PIN 25 IS DAC CLOCK BIT, it controls which byte audio information is placed onto
/// We have limited IO pins, therefore i'm not allocating a full 16 bit wide bus, but this method. Still need to implement, obvs this requires flipflops

#include "SampletoyIO.h"
#include <Arduino.h>
