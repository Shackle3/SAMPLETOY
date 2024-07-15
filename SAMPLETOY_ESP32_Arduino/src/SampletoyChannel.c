//
// Created by Fabian Uni on 14/07/2024.
//

#include "SampletoyChannel.h"
#include <stdint.h>
const uint8_t uint8_middle = 128;
const uint32_t uint32_middle = 2147483648;


//SET INITIAL GAIN TO 70% (179)
//MIDDLE OF A uint8 is 128, so lr is set to middle (no pan)
//MIDDLE OF uint32 is 2,147,483,648

/*
struct Channel{
    uint32_t level;
    uint8_t gain;
    uint8_t left_right_pan;
    uint8_t mono_side_correlation;
};*/
//Update me :)

//Investigate methods further, its C tho so oyu know how it works :/
//Channel Funtions

uint32_t channelGetLevel(const Channel* target){
    return target->level;
}

uint8_t channelGetGain(const Channel* target){
    return target->gain;
}

uint8_t channelGetLR(const Channel* target){
    return target->left_right_pan;
}

uint8_t channelGetMonoSide(const Channel* target){
    return target->mono_side_correlation;
}

void reinitialiseChannel(Channel* target){
    target->level = uint32_middle;
    target->gain = 179;
    target->mono_side_correlation = uint8_middle;
    target->left_right_pan = uint8_middle;
}

void setChannelLevel(Channel* target, uint32_t new_level){
    target->level = new_level;
}

void setChannelGain(Channel* target, uint8_t new_gain){
    target->gain = new_gain;
}

void setChannelLR(Channel* target, uint8_t new_LR){
    target->left_right_pan = new_LR;
}

void setChannelMS(Channel* target, uint8_t new_MS){
    target->mono_side_correlation = new_MS;
}

//Master channel functions

uint32_t masterGetLevel(const MasterChannel* target){
    return target->level;
}
uint8_t masterGetGain(const MasterChannel* target){
    return target->gain;
}
 float masterGetPrescale(const MasterChannel* target){
    return target->output_prescaling;
}

uint8_t masterGetLR(const MasterChannel* target){
    return target->mono_side_correlation;
}

void masterSetLevel(MasterChannel* target, uint32_t new_level){
    target->level = new_level;
}

void addSignalToMasterLevel(MasterChannel* target, uint32_t new_level){
    target->level = target->level + (new_level - uint32_middle) * target->output_prescaling; //wave superposition
}

void resetMasterLevelToMiddle(MasterChannel* target){
    target->level = uint32_middle;
}

void masterSetGain(MasterChannel* target, uint8_t new_gain){
    target->gain = new_gain;
}

void masterSetPrescale(MasterChannel* target, float new_prescaler){
    target->output_prescaling = new_prescaler;
}

void masterSetMS(MasterChannel* target, uint8_t new_MS){
    target->mono_side_correlation = new_MS;
}

void reinitialiseMasterChannel(MasterChannel* master){
    master->level = uint32_middle;
    master->gain = 179;
    master->output_prescaling = 0.6;
    master->mono_side_correlation = uint8_middle;
}