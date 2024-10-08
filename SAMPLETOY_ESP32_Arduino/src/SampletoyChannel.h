//
// Created by Fabian Uni on 14/07/2024.
//

#ifndef SAMPLETOY_ESP32_ARDUINO_SAMPLETOYCHANNEL_H

#include <stdint.h>

#define SAMPLETOY_ESP32_ARDUINO_SAMPLETOYCHANNEL_H
//extern typedef struct Channel Channel;

typedef struct Channel{
    uint32_t level_left;
    uint32_t level_right;
    uint8_t gain;
    uint8_t left_right_pan;
    uint8_t mono_side_correlation;
} channel;

typedef struct MasterChannel{
    uint32_t level_left;
    uint32_t level_right;
    uint8_t gain;
    float output_prescaling;
    uint8_t mono_side_correlation;
} masterchannel;

//returns level
uint32_t channelGetLevelLeft(const channel* target);
uint32_t channelGetLevelRight(const channel* target);
//returns gain
uint8_t channelGetGain(const channel* target);
//returns Left Right pan
uint8_t channelGetLR(const channel* target);
//returns Mono Side correlation bias
uint8_t channelGetMonoSide(const channel* target);
//resets values to originals, as defined in SampletoyChannel.c
void reinitialiseChannel(channel* target);
//sets level of channel to new value
void setChannelLevel(channel* target, uint32_t new_level_left, uint32_t new_level_right);
//sets new gain value to channel
void setChannelGain(channel* target, uint8_t new_gain);
//sets new Left-Right pan value to channel.
void setChannelLR(channel* target, uint8_t new_LR);
//sets new Mid-Side correlation value
void setChannelMS(channel* target, uint8_t new_MS);

//Returns master Level
uint32_t masterGetLevelLeft(const masterchannel* target);
uint32_t masterGetLevelRight(const masterchannel* target);
//Returns Gain value on master
uint8_t  masterGetGain(const masterchannel* target);
//Returns the Prescale float applied to all inputs to master
float masterGetPrescale(const masterchannel* target);
//Returns the Left Right pan of the Master
uint8_t  masterGetMS(const masterchannel* target);
//Sets a new Level value
void masterSetLevel(masterchannel* target, uint32_t new_level_left, uint32_t new_level_right);
//Superpositions another channels level onto master
void addSignalToMasterLevelLeft(masterchannel* target, uint32_t new_level);
void addSignalToMasterLevelRight(masterchannel* target, uint32_t new_level);
//Resets only the master level to the init value, use at start of loop
void resetMasterLevelToMiddle(masterchannel* target);
//Sets Gain scaling value of master
void masterSetGain(masterchannel* target, uint8_t new_gain);
//sets Prescale constant applied to all incoming signals added to master
void masterSetPrescale(masterchannel* target, float new_prescaler);
//Sets new Mid Side correlation bias value
void masterSetMS(masterchannel* target, uint8_t new_MS);
//Resets the master channel to its predefined initial values
void reinitialiseMasterChannel(masterchannel* master);

#endif //SAMPLETOY_ESP32_ARDUINO_SAMPLETOYCHANNEL_H
