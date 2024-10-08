//
// Created by Fabian Uni on 14/07/2024.
//

#include "SampletoyChannel.h"
#include "SampletoyMacros.h"
#include <stdint.h>


//SET INITIAL GAIN TO 70% (179)
//MIDDLE OF A uint8 is 128, so lr is set to middle (no pan)
//MIDDLE OF uint32 is 2,147,483,648

//Investigate methods further, its C tho so oyu know how it works :/
//Channel Funtions



uint32_t channelGetLevelLeft(const channel* target){
    return target->level_left;
}

uint32_t channelGetLevelRight(const channel* target){
    return target->level_right;
}

uint8_t channelGetGain(const channel* target){
    return target->gain;
}

uint8_t channelGetLR(const channel* target){
    return target->left_right_pan;
}

uint8_t channelGetMonoSide(const channel* target){
    return target->mono_side_correlation;
}

void reinitialiseChannel(channel* target){
    target->level_left = uint32_middle;
    target->level_right = uint32_middle;
    target->gain = 179;
    target->mono_side_correlation = uint8_middle;
    target->left_right_pan = uint8_middle;
}

void setChannelLevel(channel* target, uint32_t new_level_left, uint32_t new_level_right){
    target->level_left = new_level_left;
    target->level_right = new_level_right;
}

void setChannelGain(channel* target, uint8_t new_gain){
    target->gain = new_gain;
}

void setChannelLR(channel* target, uint8_t new_LR){
    target->left_right_pan = new_LR;
}

void setChannelMS(channel* target, uint8_t new_MS){
    target->mono_side_correlation = new_MS;
}

//Master channel functions

uint32_t masterGetLevelLeft(const masterchannel* target){
    return target->level_left;
}
uint32_t masterGetLevelRight(const masterchannel* target){
    return target->level_right;
}
uint8_t masterGetGain(const masterchannel* target){
    return target->gain;
}
 float masterGetPrescale(const masterchannel* target){
    return target->output_prescaling;
}

uint8_t masterGetMS(const masterchannel* target){
    return target->mono_side_correlation;
}

void masterSetLevel(masterchannel* target, uint32_t new_level_left, uint32_t new_level_right){
    target->level_left = new_level_left;
    target->level_right = new_level_right;
}

void addSignalToMasterLevelLeft(masterchannel* target, uint32_t new_level){
    target->level_left = target->level_left + (new_level - uint32_middle) ; //wave superposition
}

void addSignalToMasterLevelRight(masterchannel* target, uint32_t new_level){
    target->level_right = target->level_right + (new_level - uint32_middle); //wave superposition
}

// @todo * target->output_prescaling doesn't work as intended, requires prescale to be a signed int

void resetMasterLevelToMiddle(masterchannel* target){
    target->level_left = uint32_middle;
    target->level_right = uint32_middle;
}

void masterSetGain(masterchannel* target, uint8_t new_gain){
    target->gain = new_gain;
}

void masterSetPrescale(masterchannel* target, float new_prescaler){
    target->output_prescaling = new_prescaler;
}

void masterSetMS(masterchannel* target, uint8_t new_MS){
    target->mono_side_correlation = new_MS;
}

void reinitialiseMasterChannel(masterchannel* master){
    master->level_left = uint32_middle;
    master->level_right = uint32_middle;
    master->gain = 179;
    master->output_prescaling = 0.6;
    master->mono_side_correlation = uint8_middle;
}