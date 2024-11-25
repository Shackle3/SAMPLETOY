//
// Created by Fabian Uni on 4/09/2024.
//

#include "SampletoyPlaylist.h"

//creating generic version of an empty midi note to be copied
const midinote empty_midi_note_generic = {0, 0, UINT8_MAX, 0}; //UiNT8_MAX is FLAG FOR EMPTY EVENT @todo test correct allocation of flag
//assuming only one playlist instance

playlist* playlist_instance;
//initialisers

void reinitialiseMiditrack(miditrack* target){
    for (uint8_t i = 0; i < MIDITRACKARRAYSIZE; i++){
        target->midi_note_array[i] = empty_midi_note_generic;
    }
}

void reassignPlaylistInstance(playlist* new_playlist_pointer){
    //do once in setup
    playlist_instance = new_playlist_pointer;
}

void reinitialisePlaylist(){
    playlist_instance->bpm = DEFAULT_BPM; //reset bpm to default
    playlist_instance->playhead_position_subdivision = 0;
    playlist_instance->track_length_beats = 16 * 4; //16 bars
    for (int channel_or_track; channel_or_track < MAX_CHANNELS_OR_TRACKS; channel_or_track++){
        playlist_instance->subchannel_sample_outputs[channel_or_track] = zero_pair32;
        playlist_instance->elapsed_length_on_midievent[channel_or_track] = 0;
        channelReinitialise(&playlist_instance->playlist_tracks->track_channel);
        playlist_instance->playlist_tracks[channel_or_track].track_number = channel_or_track;
    }
}

//Midievent methods
uint16_t midinoteReturnTimePointer(const midinote* target){return target->point_to;}

uint8_t midinoteReturnLength(const midinote* target){return target->length;}

uint8_t midinoteReturnMidiCode(const midinote* target){return target->midi_code;}

midinote generateMidiEventFromVariables(uint16_t midi_start_subdivisions, uint16_t event_length, uint8_t event_midi_code){
    midinote temp_midi_event;
    temp_midi_event.point_to = midi_start_subdivisions;
    temp_midi_event.length = event_length;
    temp_midi_event.midi_code = event_midi_code;
    temp_midi_event.phase_position = 0; //@todo generate random phase here
    return temp_midi_event;
}


bool midieventCheckInsidePlayheadBounds(const midinote* target){
    //check if empty event, immediately excludes the right bound
    uint8_t target_midi_code = target->midi_code;
    if (target_midi_code == empty_midi_note_generic.midi_code){
        return false; //event is empty
    }
    //check left then right bound
    if (target->point_to > playlist_instance->playhead_position_subdivision){
        int event_end = target->point_to + target->length;
        if(event_end < playlist_instance->playhead_position_subdivision){
            //both conditions passed, end and report positive case
            return true;
        }
    } //all conditions passed, assume false
    return false;
}

//MidiTrack Methods

void trackUpdateActiveMidiEvents(miditrack* target){
    //reset no. of active midi events
    target->count_active_midi_events = 0; //doubles as counter
    for (uint8_t event = 0; event < target->total_number_of_midi_events; event++){
        if (target->count_active_midi_events > MAXIMUM_NUMBER_OF_MIDI_EVENTS_PLAYING){
            break; //max active notes reached, do not exceed
        }
        midinote* target_event_loop_iteration = &target->midi_note_array[event];
        if(midieventCheckInsidePlayheadBounds(target_event_loop_iteration)){ //true if in playhead boundaries
            target->active_midi_events[target->count_active_midi_events] = *target_event_loop_iteration; //add midi event to active events array
            target->count_active_midi_events++; 
        }
    } //all active notes are in array, ideally don't call at every n subsample but only at start of playhead n samples generate call
} //events are like a stack from 0 (oldest note) to n (newest note), [phase is saved in the note]

void miditrackAddMidiEvent(miditrack* target, midinote event){
    target->midi_note_array[target->total_number_of_midi_events] = event;
    target->total_number_of_midi_events++;
}

//void miditrackRemoveMidiEvent @todo important

//Track methods



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

uint8_t playlistGetBPM(){
    return playlist_instance->bpm;
}

track playlistGetTrack(int track_number){
    return playlist_instance->playlist_tracks[track_number];
}

uint16_t playlistGetTrackLength(){
    return playlist_instance->track_length_beats;
}

uint32_t playlistGetPlayheadPosition(){
    return playlist_instance->playhead_position_subdivision;
}
upair32 playlistGetSubchannelOutput(int track_number){
    return playlist_instance->subchannel_sample_outputs[track_number];
}

uint8_t playlistReturnElapsedTimeOnMidiEvent(int track_number){
    return playlist_instance->elapsed_length_on_midievent[track_number];
}

void playlistHeirarchyReinitialise(){
    //reinit variables based on heirary
    //playlist reinit
    reinitialisePlaylist();
    //track reinit
    //miditrack reinit
    //@todo implement
}