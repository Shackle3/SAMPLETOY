//
// Created by Fabian Uni on 31/03/2024.
//
#ifndef SAMPLETOYC_AUDIOSYNTHESIS_H
#define SAMPLETOYC_AUDIOSYNTHESIS_H
#include <stdint.h>
#include <stdbool.h>
#include "SampletoyMacros.h"
#include "SampletoyUtility.h"
#include <math.h> //math functions, pi
#include "SampletoyGenerator.h"

//an array of mapable midi notes, to their respective frequencies tuned to 440 hz
extern const double NOTE_FREQUENCIES[88];

//functions
double midi_frequency_translator(int midiNoteCode);
/*
Takes a midi note input and translate it to a frequency value, corresponding to the note at code

input:
    midiNoteCode: midi code as encoded, decodes inside function

output:

*/

uint32_t mathgen_generate(uint8_t wave_defined_generator, double phase, uint8_t midicode);

upair32 callGenerateForEvent(generator* target, const uint8_t input_note_midi_code, float* note_phase_pos);

#endif //SAMPLETOYC_AUDIOSYNTHESIS_H
