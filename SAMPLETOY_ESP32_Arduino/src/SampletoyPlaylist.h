//
// Created by Fabian Uni on 4/09/2024.
//

//@todo depending on final solution, could be seperate files

#ifndef SAMPLETOY_ESP32_ARDUINO_SAMPLETOYPLAYLIST_H
#include <stdint.h>
#include "AudioSynthesis.h"
#include "SampletoyChannel.h"
#include "SampletoyMacros.h"
#define SAMPLETOY_ESP32_ARDUINO_SAMPLETOYPLAYLIST_H

typedef struct MidiEvent{
    /*
    * @brief singular midi event. Works by having 3 variables
    uint16_t point_to, a 1d vector that points from the start of the playlist to the event
    uint8_t length, length of event
    uint8_t midi_code, midi event code

    - all time measurements are in playlist subdivisions
    
    - the point of this is top remove empty data throughout the playlist, trying to implement a vector
    array instead of a matrix
    */
   uint16_t point_to;
   uint8_t length;
   uint8_t midi_code;
} midinote;

typedef struct MidiTrack{
/*
* Dynamically allocated list of midi event vectors, for information on the datatype
stored in this list see Midievent struct
*/
midinote miditrack[64]; //@todo will need to increase or decrease allocation
} miditrack;

typedef struct Track{
    /*
    A unique instance within the playlist, contains track information
    */
   Channel track_channel;
   generator track_source;
   miditrack track_midi;
} track;

typedef struct Playlist{
    /*
    A single instance, gateway from which the main loop accesses information within the playlist heirarchy
    */

    //programmable properties
    uint8_t bpm;
    // SUBDIVISIONS_PER_BEAT = 4 (SampletoyMacros.h)
    track playlist_tracks[MAX_CHANNELS_OR_TRACKS]; 
} playlist;

#endif //SAMPLETOY_ESP32_ARDUINO_SAMPLETOYPLAYLIST_H
