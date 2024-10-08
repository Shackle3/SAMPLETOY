//
// Created by Fabian Uni on 12/07/2024.
//

#include "SampletoyUtility.h"

upair32 zero_pair32 = {0, 0};

int getBitinInt(int number, int bitposition){
    return (number & (1<<bitposition)) != 0;
}
