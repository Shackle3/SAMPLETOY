//
// Created by Fabian Uni on 12/07/2024.
/*
 * A combination of miscellaneous, logical functions and debug stuff
 * that doesn't actually fit much to any particular implementation...
 */

//

#ifndef SRC_SAMPLETOYUTILITY_H
#define SRC_SAMPLETOYUTILITY_H

//Returns the bit at bitposition for any given "number" in base2 representation.
int getBitinInt(int number, int bitposition);

//adding pairs to C
typedef struct UnsignedPair_32{
    uint32_t int1;
    uint32_t int2;
}upair32;

extern upair32 zero_pair32;

#endif //SRC_SAMPLETOYUTILITY_H
