//
// Created by Fabian Uni on 14/07/2024.
//

#include "SampletoyChannel.h"

//Investigate methods further, its C tho so oyu know how it works :/
//Channel Funtions
bool signalCheckClipping(const int signal1, const int signal2){
    //assumes both signals are centered around 0V = uint32 middle
    int sigsum = (signal1 - uint32_middle) + (signal2 - uint32_middle);
    if (abs(sigsum) >= uint32_middle){
        return true;
    }
    return false; //if case not reached, assume false for all other cases
}

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

void channelReinitialise(channel* target){
    target->level_left = uint32_middle;
    target->level_right = uint32_middle;
    target->gain = 150;
    target->mono_side_correlation = uint8_middle;
    target->left_right_pan = uint8_middle;
}

void channelResetLevelToMiddle(channel* target){
    target->level_left = uint32_middle;
    target->level_right = uint32_middle;
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

void channelAddSynthesizerSignal(channel* target, uint32_t add_signal_left, uint32_t add_signal_right){
    uint32_t container_scaled_left_signal = (uint32_t)add_signal_left * (target->gain / UINT8_MAX); //scale signals with gain
    uint32_t container_scaled_right_signal = (uint32_t)add_signal_right * (target->gain / UINT8_MAX); //scale signals with gain
    //convert to delta
    int delta_left = add_signal_left - uint32_middle;
    int delta_right = add_signal_right - uint32_middle;
    //add to channel level
    target->level_left = (uint32_t) target->level_left + delta_left; //cast away clipping
    target->level_right = (uint32_t) target->level_right + delta_right;
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

uint8_t masterGetMS(const masterchannel* target){
    return target->mono_side_correlation;
}

void masterSetLevel(masterchannel* target, uint32_t new_level_left, uint32_t new_level_right){
    target->level_left = new_level_left;
    target->level_right = new_level_right;
}

void masterAddSignalToLevelLeft(masterchannel* target, int new_level){
    target->level_left = target->level_left + new_level; //wave superposition
}

void masterAddSignalToLevelRight(masterchannel* target, int new_level){
    target->level_right = target-> level_right + new_level; //wave superposition
}

void masterAddSignalPair(masterchannel* target, upair32 signal_to_add){
    int signal_left = signal_to_add.int1 - uint32_middle;
    int signal_right = signal_to_add.int2 - uint32_middle;
    //apply prescaling
    signal_left = (int)signal_left * (target->gain / UINT8_MAX);
    signal_right = (int)signal_right * (target->gain / UINT8_MAX);
    //add onto bus
    //LEFT
    //check for clipping
    if (signalCheckClipping(target->level_left, signal_left + uint32_middle)){
        //approximate if negative or positive clipping, assuming based on added signal
        //obtain sign of signalL/R, divide by abs of itself
        int sign = signal_left / abs(signal_left); //(+1 or -1 depending on sign)
        target->level_left = uint32_middle + (sign * uint32_middle) - (sign * 1); //stops absolute clipping
    } else {
        masterAddSignalToLevelLeft(target, signal_left);
    } //repeat for RIGHT
    if (signalCheckClipping(target->level_right, signal_right + uint32_middle)){
        int sign = signal_right / abs(signal_right); //(+1 or -1 depending on sign)
        target->level_right = uint32_middle + (sign * uint32_middle) - (sign * 1); //stops absolute clipping
    } else {
        masterAddSignalToLevelRight(target, signal_right);
    }
}

// @todo * target->output_prescaling doesn't work as intended, requires prescale to be a signed int

void masterResetLevelToMiddle(masterchannel* target){
    target->level_left = uint32_middle;
    target->level_right = uint32_middle;
}

void masterSetGain(masterchannel* target, uint8_t new_gain){
    target->gain = new_gain;
}

void masterSetMS(masterchannel* target, uint8_t new_MS){
    target->mono_side_correlation = new_MS;
}

void masterChannelReinitialise(masterchannel* master){
    master->level_left = uint32_middle;
    master->level_right = uint32_middle;
    master->gain = 120;
    master->mono_side_correlation = uint8_middle;
}