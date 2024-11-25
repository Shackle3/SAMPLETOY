//
// Created by Fabian Uni on 12/07/2024.
//

#include "SampletoyUtility.h"

upair32 zero_pair32 = {0, 0};
upair16 zero_pair16 = {0, 0};

int getBitinInt(int number, int bitposition){
    return (number & (1<<bitposition)) != 0;
}

uint16_t downscale_int32_to_int16(uint32_t input){
    int temp = input + 1;
    return (uint16_t)(temp / 65536); //divide by a factor of 16 bits, contained in the lower 2 bytes
}