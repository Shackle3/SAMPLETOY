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
#include "SampletoyPlaylist.h"
#include "SampletoyUtility.h"
#include <math.h> //math functions, pi
#include <stdint.h> //uint_8

//const variables
//
//https://newt.phys.unsw.edu.au/jw/notes.html

//not in macros because its actually a memory allocation. Only used here

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

//Functions:
//
//Assuming midiIn is >= 21, inline translates a midi code into a frequency.
double midi_frequency_translator(unsigned midiNoteCode){return NOTE_FREQUENCIES[midiNoteCode - 21];}

//private wave functions (example sine)

uint32_t mathgen_generate(uint8_t wave_defined_generator, double phase, uint8_t midicode){
    double wave_container = 0; //defines a wave 
    uint32_t output_container = uint32_middle; // setup new empty sig

    switch(wave_defined_generator){
        case MUTE: wave_container = 0; break;
        case SINE: wave_container = sin(phase); break;
        // @todo extend for further cases
    }

    //case sine = 1, output container add to maximum (a second uint32_middle - 1)
    //case sine = -1, vice versa
    //all wave functions satisfy this range

    output_container = uint32_middle + (uint32_middle - 1) * wave_container;
    return output_container;
}

upair32 callGenerateForEvent(generator* target, midinote* input_note){
    //for now, we mono @todo stereo capabilities, rand phase when adding midi notes
    uint32_t temp_output_container;
    //recaulcuate phase interval 
    //see documentation, for calculation specifics
    float deltaphase = (2 * PI * midi_frequency_translator(input_note->midi_code)) * SAMPLE_DURATION;
    switch(target->generator_type){
        case MATHSYNTH:
            temp_output_container = mathgen_generate(target->define_wave, input_note->phase_position, input_note->midi_code);
            input_note->phase_position = (float) fmod((input_note->phase_position + deltaphase), (2 * PI));
            return (upair32){temp_output_container, temp_output_container}; //break redundant
        case WAVETABLESYNTH:
            //@todo implement
            return (upair32){0,0};
    }
}
