//
// Edited Fabian on 03/06/2024. Ver 0.2
/*  Change notes: ver 0.2
 *      - Changed the 2d array of synth information to be a 1d array of structs
 *      - Renamed said array to represent the new data it holds.
 *
 * */
//

#include "AudioSynthesis.h"
#include "SampletoyMacros.h"
#include <math.h> //math functions, pi
#include <stdint.h> //uint_8

//const variables
//
//https://newt.phys.unsw.edu.au/jw/notes.html
const double NOTE_FREQUENCIES[] = {27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891,
                                   41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27,
                                   61.735, 65.406, 69.296, 73.416, 77.782, 82.407,
                                   87.307, 92.499, 97.999, 103.83, 110, 116.54,
                                   123.47, 130.81, 138.59, 146.83, 155.56, 164.81,
                                   174.61, 185, 196, 207.65, 220, 233.08, 246.94,
                                   261.63, 277.18, 293.67, 311.13, 329.63, 349.23,
                                   369.99, 392, 415.3, 440, 466.16, 493.88, 523.25,
                                   554.37, 587.33, 622.25, 659.26, 698.46, 739.99,
                                   783.99, 830.61, 880, 932.33, 987.77, 1046.5,
                                   1108.7, 1174.7, 1244.5, 1318.5, 1396.9, 1480,
                                   1568, 1661.2, 1760, 1864.7, 1975.5, 2093, 2217.5,
                                   2349.3, 2489, 2637, 2793, 2960, 3136, 3322.4,
                                   3520, 3729.3, 3951.1, 4186};

//Public Variables:
//
//List of how many samples a note_on has been signaled to synth, index corresponds to playlist order.
//

//initialising on bpm is set to 130
//float samplePerSmallestSubdivision = 1/((130/60) * SUBDIVISIONS_PER_BEAT * SAMPLE_DURATION);

/// List of currently playing notes (nDFAWInfo[i] != 0),
/// how long (in samples) each note will be held for, and at what duration one phase has in time
mathsynth mathSynthInstances[MAX_CHANNELS_OR_TRACKS]; //size max synths x 2
/*
 * For implementation see MathSynthHost struct in Audiosynthesis.h
 *
 * When currentPlayingSampleNumber = noteDurationSamples, complete last wave computation and then
 * set noteDurationSamples[i] back to 0
 */

unsigned int currentPlayingSampleNumber[MAX_CHANNELS_OR_TRACKS];
// Index corresponds to synth

//Functions:
//
//Assuming midiIn is >= 21, inline translates a midi code into a frequency.
double midi_frequency_translator(unsigned midiNoteCode){return NOTE_FREQUENCIES[midiNoteCode - 21];}

void update_samples_per_smallest_subdiv(uint8_t bpm){
    samplePerSmallestSubdivision = 1/((bpm/60) * SUBDIVISIONS_PER_BEAT * SAMPLE_DURATION);
}

void parse_midi_input(unsigned noteCode, uint8_t velocity, unsigned duration,
                      unsigned synthNumber, uint8_t wave){
    mathSynthInstances[synthNumber].samplesHeldFor = duration;
    mathSynthInstances[synthNumber].notePeriod = 1 / midi_frequency_translator(noteCode);
    mathSynthInstances[synthNumber].noteAmplitude = velocity / 127;
    mathSynthInstances[synthNumber].waveType = wave;

}

double math_wave_gen(uint8_t synthesiserNumber){
    /*
     * Generates value that a synthesiser returns at the current sample
     *
     * Inputs:
     *  synthesiserNumber: used to access information of that synthesiser and the various wave properties.
     *
     * Outputs:
     *  double: returns function value at that phase
     */

    //Get note properties
    double phaseDuration = mathSynthInstances[synthesiserNumber].notePeriod; //in seconds
    float amplitude = mathSynthInstances[synthesiserNumber].noteAmplitude;
    //calculate time
    //we know frequency, follows time for one phase = 1/frequency
    // time/T1Phase * 2pi = phase
    double time = currentPlayingSampleNumber[synthesiserNumber] * SAMPLE_DURATION;
    double phase = (time/phaseDuration) * 2 *  PI;
    //Increment phase values
    currentPlayingSampleNumber[synthesiserNumber]++;
    //Generate function output
    switch (mathSynthInstances[synthesiserNumber].waveType) {
        case 0:
            return 0;
        case 1:
            return sin(phase) * amplitude;
        case 2:
            return cos(phase) * amplitude;
        default:
            return 0;
    }
}

void cleanup_finished_midi(){
    for (uint8_t synth = 0; synth < MAX_CHANNELS_OR_TRACKS; synth++)
    {
        if (mathSynthInstances[synth].samplesHeldFor != 0){ //ignore not playing synths
            if (mathSynthInstances[synth].samplesHeldFor < currentPlayingSampleNumber[synth]){
                //case, the synth sample exceeds the duration specified on the creation
                //reset note in memory
                currentPlayingSampleNumber[synth] = 0;
                mathSynthInstances[synth].samplesHeldFor = 0;
                mathSynthInstances[synth].notePeriod = 0;
                mathSynthInstances[synth].noteAmplitude = 0;
                mathSynthInstances[synth].waveType = 0;
            }
        }
    }
}

void initialise_the_mathsynths(){
    for (uint8_t i = 0; i < MAX_CHANNELS_OR_TRACKS; i++){
        mathSynthInstances[i].samplesHeldFor = 0;
        mathSynthInstances[i].notePeriod = 0;
        mathSynthInstances[i].noteAmplitude = 0;
        mathSynthInstances[i].waveType = 0;
    }
}


