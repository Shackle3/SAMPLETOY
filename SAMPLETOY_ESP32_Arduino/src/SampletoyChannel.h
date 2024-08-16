//
// Created by Fabian Uni on 14/07/2024.
//

#ifndef SAMPLETOY_ESP32_ARDUINO_SAMPLETOYCHANNEL_H

#include <stdint.h>

#define SAMPLETOY_ESP32_ARDUINO_SAMPLETOYCHANNEL_H
//extern typedef struct Channel Channel;
typedef struct Channel Channel;
typedef struct MasterChannel MasterChannel;

struct Channel{
    uint32_t level_left;
    uint32_t level_right;
    uint8_t gain;
    uint8_t left_right_pan;
    uint8_t mono_side_correlation;
};

struct MasterChannel{
    uint32_t level_left;
    uint32_t level_right;
    uint8_t gain;
    float output_prescaling;
    uint8_t mono_side_correlation;
};

//returns level
uint32_t channelGetLevelLeft(const Channel* target);
uint32_t channelGetLevelRight(const Channel* target);
//returns gain
uint8_t channelGetGain(const Channel* target);
//returns Left Right pan
uint8_t channelGetLR(const Channel* target);
//returns Mono Side correlation bias
uint8_t channelGetMonoSide(const Channel* target);
//resets values to originals, as defined in SampletoyChannel.c
void reinitialiseChannel(Channel* target);
//sets level of channel to new value
void setChannelLevel(Channel* target, uint32_t new_level_left, uint32_t new_level_right);
//sets new gain value to channel
void setChannelGain(Channel* target, uint8_t new_gain);
//sets new Left-Right pan value to channel.
void setChannelLR(Channel* target, uint8_t new_LR);
//sets new Mid-Side correlation value
void setChannelMS(Channel* target, uint8_t new_MS);

//Returns master Level
uint32_t masterGetLevelLeft(const MasterChannel* target);
uint32_t masterGetLevelRight(const MasterChannel* target);
//Returns Gain value on master
uint8_t  masterGetGain(const MasterChannel* target);
//Returns the Prescale float applied to all inputs to master
float masterGetPrescale(const MasterChannel* target);
//Returns the Left Right pan of the Master
uint8_t  masterGetMS(const MasterChannel* target);
//Sets a new Level value
void masterSetLevel(MasterChannel* target, uint32_t new_level_left, uint32_t new_level_right);
//Superpositions another channels level onto master
void addSignalToMasterLevelLeft(MasterChannel* target, uint32_t new_level);
void addSignalToMasterLevelRight(MasterChannel* target, uint32_t new_level);
//Resets only the master level to the init value, use at start of loop
void resetMasterLevelToMiddle(MasterChannel* target);
//Sets Gain scaling value of master
void masterSetGain(MasterChannel* target, uint8_t new_gain);
//sets Prescale constant applied to all incoming signals added to master
void masterSetPrescale(MasterChannel* target, float new_prescaler);
//Sets new Mid Side correlation bias value
void masterSetMS(MasterChannel* target, uint8_t new_MS);
//Resets the master channel to its predefined initial values
void reinitialiseMasterChannel(MasterChannel* master);

#endif //SAMPLETOY_ESP32_ARDUINO_SAMPLETOYCHANNEL_H
