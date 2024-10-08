//
// Created by Fabian Uni on 4/09/2024.
//

#include "SampletoyPlaylist.h"

//creating generic version of an empty midi note to be copied
const midinote empty_midi_note_generic = {0, 0, 0};
//assuming only one playlist instance
playlist* playlist_instance;

//Midievent functions
uint16_t midinoteReturnTimePointer(const midinote* target){return target->point_to;}

uint8_t midinoteReturnLength(const midinote* target){return target->length;}

uint8_t midinoteReturnMidiCode(const midinote* target){return target->midi_code;}

midinote generateMidiEventFromVariables(uint16_t midi_start_subdivisions, uint8_t event_length, uint8_t event_midi_code){
    midinote temp_midi_event;
    temp_midi_event.point_to = midi_start_subdivisions;
    temp_midi_event.length = event_length;
    temp_midi_event.midi_code = event_midi_code;
    return temp_midi_event;
}

//initialisers
void definePlaylistInstance(playlist* target){
    playlist_instance = target;
}

void reinitialiseMiditrack(miditrack* target){
    for (uint8_t i = 0; i < MIDITRACKARRAYSIZE; i++){
        target->miditrackArray[i] = empty_midi_note_generic;
    }

}

//playlist methods
int recalculateSamplesPerSubdivision(uint8_t new_bpm){
    //function is kind of inefficient on memory, but i'm assuming its not happening in runtime so i'ma write it more readable
    uint16_t subdivisions_per_minute = new_bpm * SUBDIVISIONS_PER_BEAT;
    float sub_per_second = subdivisions_per_minute/60;
    float time_for_one_sub = 1/sub_per_second;
    //typecast time for one subdivision into int, after turning it into x number of samples that fit into it
    int samples_per_sub = (int) time_for_one_sub / SAMPLE_DURATION;
    return samples_per_sub;
}

void reinitialisePlaylist(){
    playlist_instance->bpm = DEFAULT_BPM; //reset bpm to default
    playlist_instance->samples_per_subdivision = recalculateSamplesPerSubdivision(DEFAULT_BPM);
    playlist_instance->playhead_position_subdivision = 0;
    playlist_instance->track_length_beats = 16 * 4; //16 bars
    for (int channel_or_track; channel_or_track < MAX_CHANNELS_OR_TRACKS; channel_or_track++){
        playlist_instance->subchannel_sample_outputs[channel_or_track] = zero_pair32;
        playlist_instance->elapsed_length_on_midievent[channel_or_track] = 0;
    }
}

void //@todo write the code that takes current playhead, and 

