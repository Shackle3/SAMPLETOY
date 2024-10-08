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

void reinitialisePlaylist(){
    playlist_instance->bpm = 140;   
}

